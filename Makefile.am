AUTOMAKE_OPTIONS = subdir-objects

# precompiled header; note $(CXXCOMPILE) has a -include flag for the header,
# ensure that this won't use the old precompiled header by removing it first
bi/birch.hpp.gch: bi/birch.hpp
	rm -f $@
	mkdir -p bi/$(DEPDIR) && \
	$(CXXCOMPILE) -M -MF bi/$(DEPDIR)/birch.gch.Plo -MT $@ $< && \
	$(CXXCOMPILE) -o $@ $<

#include bi/$(DEPDIR)/birch.gch.Plo

# Flex/Bison setup
AM_YFLAGS = -d
AM_FLAGS =

# compiler setup
AM_CPPFLAGS = -DDATADIR="$(datadir)" -DINCLUDEDIR="$(includedir)" -DLIBDIR="$(libdir)"
AM_CXXFLAGS = -include bi/birch.hpp
ACLOCAL_AMFLAGS = -I m4

# driver program
bin_PROGRAMS = birch

# common sources for driver and compiler programs
COMMON_SOURCES = \
  bi/build/Compiler.cpp \
  bi/build/Driver.cpp \
  bi/build/misc.cpp \
  bi/common/Annotated.cpp \
  bi/common/Argumented.cpp \
  bi/common/Based.cpp \
  bi/common/Braced.cpp \
  bi/common/Bracketed.cpp \
  bi/common/Conditioned.cpp \
  bi/common/Couple.cpp \
  bi/common/Dictionary.cpp \
  bi/common/Located.cpp \
  bi/common/Location.cpp \
  bi/common/Name.cpp \
  bi/common/Named.cpp \
  bi/common/Numbered.cpp \
  bi/common/Overloaded.cpp \
  bi/common/OverloadedDictionary.cpp \
  bi/common/Parameterised.cpp \
  bi/common/Parenthesised.cpp \
  bi/common/ReturnTyped.cpp \
  bi/common/Reference.cpp \
  bi/common/Scope.cpp \
  bi/common/Scoped.cpp \
  bi/common/Single.cpp \
  bi/common/Typed.cpp \
  bi/common/Valued.cpp \
  bi/exception/AmbiguousCallException.cpp \
  bi/exception/AssignmentOperatorException.cpp \
  bi/exception/AssignmentException.cpp \
  bi/exception/BaseException.cpp \
  bi/exception/CallException.cpp \
  bi/exception/CastException.cpp \
  bi/exception/CompilerException.cpp \
  bi/exception/ConditionException.cpp \
  bi/exception/ConstructorException.cpp \
  bi/exception/ConversionOperatorException.cpp \
  bi/exception/DriverException.cpp \
  bi/exception/Exception.cpp \
  bi/exception/FiberTypeException.cpp \
  bi/exception/FileNotFoundException.cpp \
  bi/exception/GenericException.cpp \
  bi/exception/GetException.cpp \
  bi/exception/IndexException.cpp \
  bi/exception/InitialValueException.cpp \
  bi/exception/MemberException.cpp \
  bi/exception/NotAssignableException.cpp \
  bi/exception/NotFunctionException.cpp \
  bi/exception/PreviousDeclarationException.cpp \
  bi/exception/QueryException.cpp \
  bi/exception/ReadOnlyException.cpp \
  bi/exception/ReturnException.cpp \
  bi/exception/ReturnTypeException.cpp \
  bi/exception/SequenceException.cpp \
  bi/exception/SliceException.cpp \
  bi/exception/SuperException.cpp \
  bi/exception/SuperBaseException.cpp \
  bi/exception/ThisException.cpp \
  bi/exception/UnresolvedException.cpp \
  bi/exception/UnsupportedOptionTypeException.cpp \
  bi/exception/YieldException.cpp \
  bi/exception/YieldTypeException.cpp \
  bi/expression/Assign.cpp \
  bi/expression/Binary.cpp \
  bi/expression/BinaryCall.cpp \
  bi/expression/Cast.cpp \
  bi/expression/Call.cpp \
  bi/expression/EmptyExpression.cpp \
  bi/expression/Expression.cpp \
  bi/expression/ExpressionIterator.cpp \
  bi/expression/ExpressionList.cpp \
  bi/expression/Generic.cpp \
  bi/expression/Get.cpp \
  bi/expression/Global.cpp \
  bi/expression/Identifier.cpp \
  bi/expression/Index.cpp \
  bi/expression/LambdaFunction.cpp \
  bi/expression/Literal.cpp \
  bi/expression/LocalVariable.cpp \
  bi/expression/Member.cpp \
  bi/expression/Nil.cpp \
  bi/expression/OverloadedIdentifier.cpp \
  bi/expression/Parameter.cpp \
  bi/expression/Parentheses.cpp \
  bi/expression/Query.cpp \
  bi/expression/Range.cpp \
  bi/expression/Sequence.cpp \
  bi/expression/Slice.cpp \
  bi/expression/Span.cpp \
  bi/expression/Super.cpp \
  bi/expression/This.cpp \
  bi/expression/UnaryCall.cpp \
  bi/io/cpp/CppBaseGenerator.cpp \
  bi/io/cpp/CppConstructorGenerator.cpp \
  bi/io/cpp/CppClassGenerator.cpp \
  bi/io/cpp/CppFiberGenerator.cpp \
  bi/io/cpp/CppMemberFiberGenerator.cpp \
  bi/io/cpp/CppPackageGenerator.cpp \
  bi/io/cpp/CppRawGenerator.cpp \
  bi/io/bi_ostream.cpp \
  bi/io/cpp_ostream.cpp \
  bi/io/indentable_ostream.cpp \
  bi/io/md_ostream.cpp \
  bi/primitive/encode.cpp \
  bi/primitive/poset.cpp \
  bi/statement/Assert.cpp \
  bi/statement/AssignmentOperator.cpp \
  bi/statement/Assignment.cpp \
  bi/statement/Basic.cpp \
  bi/statement/BinaryOperator.cpp \
  bi/statement/Braces.cpp \
  bi/statement/Class.cpp \
  bi/statement/ConversionOperator.cpp \
  bi/statement/DoWhile.cpp \
  bi/statement/EmptyStatement.cpp \
  bi/statement/Explicit.cpp \
  bi/statement/ExpressionStatement.cpp \
  bi/statement/Fiber.cpp \
  bi/statement/File.cpp \
  bi/statement/For.cpp \
  bi/statement/Function.cpp \
  bi/statement/GlobalVariable.cpp \
  bi/statement/If.cpp \
  bi/statement/MemberFiber.cpp \
  bi/statement/MemberFunction.cpp \
  bi/statement/MemberVariable.cpp \
  bi/statement/Package.cpp \
  bi/statement/Program.cpp \
  bi/statement/Raw.cpp \
  bi/statement/Return.cpp \
  bi/statement/Statement.cpp \
  bi/statement/StatementIterator.cpp \
  bi/statement/StatementList.cpp \
  bi/statement/UnaryOperator.cpp \
  bi/statement/While.cpp \
  bi/statement/Yield.cpp \
  bi/type/ArrayType.cpp \
  bi/type/BasicType.cpp \
  bi/type/BinaryType.cpp \
  bi/type/ClassType.cpp \
  bi/type/EmptyType.cpp \
  bi/type/FiberType.cpp \
  bi/type/FunctionType.cpp \
  bi/type/GenericType.cpp \
  bi/type/NilType.cpp \
  bi/type/OptionalType.cpp \
  bi/type/OverloadedType.cpp \
  bi/type/PointerType.cpp \
  bi/type/SequenceType.cpp \
  bi/type/TupleType.cpp \
  bi/type/Type.cpp \
  bi/type/TypeConstIterator.cpp \
  bi/type/UnknownType.cpp \
  bi/type/TypeIterator.cpp \
  bi/type/TypeList.cpp \
  bi/visitor/Cloner.cpp \
  bi/visitor/Gatherer.cpp \
  bi/visitor/Instantiater.cpp \
  bi/visitor/Modifier.cpp \
  bi/visitor/Resolver.cpp \
  bi/visitor/ResolverHeader.cpp \
  bi/visitor/ResolverSource.cpp \
  bi/visitor/ResolverSuper.cpp \
  bi/visitor/Typer.cpp \
  bi/visitor/Visitor.cpp \
  bi/lexer.lpp \
  bi/parser.ypp

# sources
birch_SOURCES = \
  $(COMMON_SOURCES) \
  bi/birch.cpp
birch_CXXFLAGS = $(AM_CXXFLAGS)
  
noinst_HEADERS = \
  bi/build/Compiler.hpp \
  bi/build/Driver.hpp \
  bi/build/misc.hpp \
  bi/common/Annotated.hpp \
  bi/common/Argumented.hpp \
  bi/common/Based.hpp \
  bi/common/Braced.hpp \
  bi/common/Bracketed.hpp \
  bi/common/Conditioned.hpp \
  bi/common/Couple.hpp \
  bi/common/Dictionary.hpp \
  bi/common/Located.hpp \
  bi/common/Location.hpp \
  bi/common/Name.hpp \
  bi/common/Named.hpp \
  bi/common/Numbered.hpp \
  bi/common/Overloaded.hpp \
  bi/common/OverloadedDictionary.hpp \
  bi/common/Parameterised.hpp \
  bi/common/Parenthesised.hpp \
  bi/common/Reference.hpp \
  bi/common/ReturnTyped.hpp \
  bi/common/Scope.hpp \
  bi/common/Scoped.hpp \
  bi/common/Single.hpp \
  bi/common/Typed.hpp \
  bi/common/Valued.hpp \
  bi/exception/all.hpp \
  bi/exception/AmbiguousCallException.hpp \
  bi/exception/AssignmentException.hpp \
  bi/exception/AssignmentOperatorException.hpp \
  bi/exception/BaseException.hpp \
  bi/exception/CallException.hpp \
  bi/exception/CompilerException.hpp \
  bi/exception/ConditionException.hpp \
  bi/exception/ConstructorException.hpp \
  bi/exception/ConversionOperatorException.hpp \
  bi/exception/DriverException.hpp \
  bi/exception/FiberTypeException.hpp \
  bi/exception/FileNotFoundException.hpp \
  bi/exception/GenericException.hpp \
  bi/exception/GetException.hpp \
  bi/exception/IndexException.hpp \
  bi/exception/MemberException.hpp \
  bi/exception/NotAssignableException.hpp \
  bi/exception/NotFunctionException.hpp \
  bi/exception/PreviousDeclarationException.hpp \
  bi/exception/QueryException.hpp \
  bi/exception/ReadOnlyException.hpp \
  bi/exception/ReturnException.hpp \
  bi/exception/ReturnTypeException.hpp \
  bi/exception/SequenceException.hpp \
  bi/exception/SliceException.hpp \
  bi/exception/SuperBaseException.hpp \
  bi/exception/SuperException.hpp \
  bi/exception/ThisException.hpp \
  bi/exception/UnresolvedException.hpp \
  bi/exception/UnsupportedOptionTypeException.hpp \
  bi/exception/YieldException.hpp \
  bi/exception/YieldTypeException.hpp \
  bi/expression/all.hpp \
  bi/expression/Assign.hpp \
  bi/expression/Binary.hpp \
  bi/expression/BinaryCall.hpp \
  bi/expression/Cast.hpp \
  bi/expression/Call.hpp \
  bi/expression/EmptyExpression.hpp \
  bi/expression/Expression.hpp \
  bi/expression/ExpressionIterator.hpp \
  bi/expression/ExpressionList.hpp \
  bi/expression/Generic.hpp \
  bi/expression/Get.hpp \
  bi/expression/Global.hpp \
  bi/expression/Identifier.hpp \
  bi/expression/Index.hpp \
  bi/expression/LambdaFunction.hpp \
  bi/expression/Literal.hpp \
  bi/expression/LocalVariable.hpp \
  bi/expression/Member.hpp \
  bi/expression/Nil.hpp \
  bi/expression/OverloadedIdentifier.hpp \
  bi/expression/Parameter.hpp \
  bi/expression/Parentheses.hpp \
  bi/expression/Query.hpp \
  bi/expression/Range.hpp \
  bi/expression/Sequence.hpp \
  bi/expression/Slice.hpp \
  bi/expression/Span.hpp \
  bi/expression/Super.hpp \
  bi/expression/This.hpp \
  bi/expression/UnaryCall.hpp \
  bi/io/cpp/CppBaseGenerator.hpp \
  bi/io/cpp/CppConstructorGenerator.hpp \
  bi/io/cpp/CppClassGenerator.hpp \
  bi/io/cpp/CppFiberGenerator.hpp \
  bi/io/cpp/CppMemberFiberGenerator.hpp \
  bi/io/cpp/CppPackageGenerator.hpp \
  bi/io/cpp_ostream.hpp \
  bi/io/bi_ostream.hpp \
  bi/io/bih_ostream.hpp \
  bi/io/hpp_ostream.hpp \
  bi/io/indentable_ostream.hpp \
  bi/io/md_ostream.hpp \
  bi/primitive/definitely.hpp \
  bi/primitive/encode.hpp \
  bi/primitive/poset.hpp \
  bi/statement/all.hpp \
  bi/statement/AssignmentOperator.hpp \
  bi/statement/Assignment.hpp \
  bi/statement/Basic.hpp \
  bi/statement/BinaryOperator.hpp \
  bi/statement/Braces.hpp \
  bi/statement/Class.hpp \
  bi/statement/ConversionOperator.hpp \
  bi/statement/DoWhile.hpp \
  bi/statement/EmptyStatement.hpp \
  bi/statement/Explicit.hpp \
  bi/statement/ExpressionStatement.hpp \
  bi/statement/Fiber.hpp \
  bi/statement/File.hpp \
  bi/statement/For.hpp \
  bi/statement/Function.hpp \
  bi/statement/GlobalVariable.hpp \
  bi/statement/If.hpp \
  bi/statement/MemberFiber.hpp \
  bi/statement/MemberFunction.hpp \
  bi/statement/MemberVariable.hpp \
  bi/statement/Package.hpp \
  bi/statement/Program.hpp \
  bi/statement/Raw.hpp \
  bi/statement/Return.hpp \
  bi/statement/Statement.hpp \
  bi/statement/StatementIterator.hpp \
  bi/statement/StatementList.hpp \
  bi/statement/UnaryOperator.hpp \
  bi/statement/While.hpp \
  bi/statement/Yield.hpp \
  bi/type/all.hpp \
  bi/type/ArrayType.hpp \
  bi/type/BasicType.hpp \
  bi/type/BinaryType.hpp \
  bi/type/ClassType.hpp \
  bi/type/EmptyType.hpp \
  bi/type/FiberType.hpp \
  bi/type/FunctionType.hpp \
  bi/type/GenericType.hpp \
  bi/type/NilType.hpp \
  bi/type/OptionalType.hpp \
  bi/type/OverloadedType.hpp \
  bi/type/PointerType.hpp \
  bi/type/SequenceType.hpp \
  bi/type/TupleType.hpp \
  bi/type/Type.hpp \
  bi/type/TypeConstIterator.hpp \
  bi/type/UnknownType.hpp \
  bi/type/TypeIterator.hpp \
  bi/type/TypeList.hpp \
  bi/visitor/all.hpp \
  bi/visitor/Cloner.hpp \
  bi/visitor/Gatherer.hpp \
  bi/visitor/Instantiater.hpp \
  bi/visitor/Modifier.hpp \
  bi/visitor/Resolver.hpp \
  bi/visitor/ResolverHeader.hpp \
  bi/visitor/ResolverSource.hpp \
  bi/visitor/ResolverSuper.hpp \
  bi/visitor/Typer.hpp \
  bi/visitor/Visitor.hpp \
  bi/birch.hpp \
  bi/doxygen.hpp \
  bi/lexer.hpp \
  bi/parser.hpp

dist_pkgdata_DATA = \
  share/gitignore \
  share/ax_check_define.m4 \
  share/ax_cxx_compile_stdcxx.m4 \
  share/autogen.sh \
  share/configure.ac \
  share/LICENSE \
  share/Makefile.am \
  share/META.json \
  share/README.md

BUILT_SOURCES = bi/birch.hpp.gch bi/parser.hpp
CLEANFILES = $(BUILT_SOURCES)
