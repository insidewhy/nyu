#ifndef nyu_grammar_nyah_HPP
#define nyu_grammar_nyah_HPP

#include <nyu/grammar/nyu.hpp>

namespace nyu { namespace grammar { namespace nyah {

namespace chpar = chilon::parser;

typedef TODO_rule Id;

typedef TODO_rule ScopedId;

typedef chpar::many_plus<
    chpar::char_range<
        TODO
    >
> UnsignedInteger;

typedef chpar::sequence<
    TODO
> EnumEntry;

struct Enum : simple_node<
    Enum,
    chpar::sequence<
        TODO
    >
> {};

typedef TODO_rule AssignExpression;

typedef TODO_rule Type;

struct Attribute : simple_node<
    Attribute,
    chpar::sequence<
        TODO
    >
> {};

struct AssignedAttribute : simple_node<
    AssignedAttribute,
    chpar::sequence<
        TODO
    >
> {};

struct Class : simple_node<
    Class,
    chpar::sequence<
        TODO
    >
> {};

typedef chpar::TODO_choice<
    TODO_rule,
    TODO_rule
> Grammar;

} } }
#endif
