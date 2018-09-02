/**
 * @file
 */
#include "libbirch/Map.hpp"

#include <algorithm>

bi::Map::Map() :
    entries(nullptr),
    nentries(0),
    nreserved(0) {
  //
}

bi::Map::~Map() {
  joint_entry_type* entries1 = (joint_entry_type*)entries;
  for (size_t i = 0; i < nentries; ++i) {
    joint_entry_type entry = entries1[i];
    if (entry.key) {
      entry.value->decShared();
    }
  }
  deallocate(entries, nentries * sizeof(entry_type));
}

bool bi::Map::empty() const {
  return nentries == 0;
}

void bi::Map::startRead() {
  lock.share();
}

void bi::Map::startWrite() {
  reserve();
  lock.share();
}

size_t bi::Map::hash(const key_type key) const {
  assert(nentries > 0);
  return (reinterpret_cast<size_t>(key) >> 5ull) & (nentries - 1ull);
}

bi::Map::value_type bi::Map::get(const key_type key, size_t& i) {
  /* pre-condition */
  assert(key);
  assert(0 <= i && i < nentries);

  key_type k = entries[i].split.key.load(std::memory_order_relaxed);
  while (k && k != key) {
    i = (i + 1) & (nentries - 1);
    k = entries[i].split.key.load(std::memory_order_relaxed);
  }

  value_type result;
  if (k == key) {
    result = entries[i].split.value.load(std::memory_order_relaxed);
  } else {
    result = nullptr;
  }
  return result;
}

bi::Map::value_type bi::Map::put(const key_type key, const value_type value,
    size_t& i) {
  /* pre-condition */
  assert(key);
  assert(value);
  assert(0 <= i && i < nentries);

  value->incShared();
  joint_entry_type expected = { nullptr, nullptr };
  joint_entry_type desired = { key, value };
  while (!entries[i].joint.compare_exchange_strong(expected, desired,
      std::memory_order_relaxed) && expected.key != key) {
    i = (i + 1) & (nentries - 1);
    expected = {nullptr, nullptr};
  }

  value_type result;
  if (expected.key == key) {
    unreserve();  // key exists, cancel reservation for insert
    result = entries[i].split.value.load(std::memory_order_relaxed);
    value->decShared();
  } else {
    result = value;
  }
  return result;
}

bi::Map::value_type bi::Map::set(const key_type key, const value_type value,
    size_t& i) {
  /* pre-condition */
  assert(key);
  assert(value);
  assert(0 <= i && i < nentries);

  value->incShared();
  joint_entry_type expected = { nullptr, nullptr };
  joint_entry_type desired = { key, value };
  while (!entries[i].joint.compare_exchange_strong(expected, desired,
      std::memory_order_relaxed) && expected.key != key) {
    i = (i + 1) & (nentries - 1);
    expected = {nullptr, nullptr};
  }

  if (expected.key == key) {
    unreserve();  // key exists, cancel reservation for insert
    while (!entries[i].joint.compare_exchange_weak(expected, desired,
        std::memory_order_relaxed));
    expected.value->decShared();
  }
  return value;
}

void bi::Map::finishRead() {
  lock.unshare();
}

void bi::Map::finishWrite() {
  lock.unshare();
}

size_t bi::Map::crowd() const {
  /* the table is considered crowded if more than three-quarters of its
   * entries are occupied */
  return (nentries >> 1ull) + (nentries >> 2ull);
}

void bi::Map::reserve() {
  size_t nreserved1 = nreserved.fetch_add(1u) + 1u;
  if (nreserved1 > crowd()) {
    /* obtain resize lock */
    lock.keep();

    /* check that no other thread has resized in the meantime */
    if (nreserved1 > crowd()) {
      /* save previous table */
      size_t nentries1 = nentries;
      joint_entry_type* entries1 = (joint_entry_type*)entries;

      /* initialize new table */
      size_t nentries2 = std::max(2ull * nentries1, 256ull);
      joint_entry_type* entries2 = (joint_entry_type*)allocate(
          nentries2 * sizeof(entry_type));
      std::memset(entries2, 0, nentries2 * sizeof(entry_type));

      /* copy contents from previous table */
      nentries = nentries2;
      for (size_t i = 0u; i < nentries1; ++i) {
        joint_entry_type entry = entries1[i];
        if (entry.key) {
          size_t j = hash(entry.key);
          while (entries2[j].key) {
            j = (j + 1u) & (nentries2 - 1u);
          }
          entries2[j] = entry;
        }
      }
      entries = (entry_type*)entries2;

      /* deallocate previous table */
      deallocate(entries1, nentries1 * sizeof(joint_entry_type));
    }

    /* release resize lock */
    lock.unkeep();
  }
}

void bi::Map::unreserve() {
  nreserved.fetch_sub(1u, std::memory_order_relaxed);
}
