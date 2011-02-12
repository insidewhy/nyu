#ifndef nyu_grammar_nyah_HPP
#define nyu_grammar_nyah_HPP

#include <nyu/grammar/nyu.hpp>

namespace nyu { namespace grammar { namespace nyah {

namespace chpar = chilon::parser;

typedef TODO_rule Id;

typedef TODO_rule ScopedId;

typedef chpar::TODO_suffix<> UnsignedInteger;

typedef chpar::sequence<
> EnumEntry;

struct Enum : simple_node<Enum, TODO> {}

typedef TODO_rule AssignExpression;

typedef TODO_rule Type;

struct Attribute : simple_node<Attribute, TODO> {}

struct AssignedAttribute : simple_node<AssignedAttribute, TODO> {}

struct Class : simple_node<Class, TODO> {}

typedef chpar::choice<
> Grammar;

} } }
#endif
