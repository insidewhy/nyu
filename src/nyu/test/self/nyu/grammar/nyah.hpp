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
    chpar::TODO_prefix<
        TODO_rule
    >,
    chpar::sequence<
        chpar::char_<'='>,
        TODO_rule
    >
> EnumEntry;

struct Enum : simple_node<
    Enum,
    chpar::sequence<
        chpar::char_<'e', 'n', 'u', 'm'>,
        chpar::TODO_prefix<
            TODO_rule
        >,
        chpar::char_<'{'>,
        chpar::many<
            TODO_rule
        >,
        chpar::char_<'}'>
    >
> {};

typedef TODO_rule AssignExpression;

typedef TODO_rule Type;

struct Attribute : simple_node<
    Attribute,
    chpar::sequence<
        chpar::TODO_prefix<
            TODO_rule
        >,
        chpar::char_<':'>,
        TODO_rule
    >
> {};

struct AssignedAttribute : simple_node<
    AssignedAttribute,
    chpar::sequence<
        chpar::TODO_prefix<
            TODO_rule
        >,
        chpar::char_<':'>,
        chpar::char_<'='>,
        TODO_rule
    >
> {};

struct Class : simple_node<
    Class,
    chpar::sequence<
        chpar::char_<'c', 'l', 'a', 's', 's'>,
        chpar::TODO_prefix<
            TODO_rule
        >,
        chpar::char_<'{'>,
        chpar::many<
            chpar::choice<
                TODO_rule,
                TODO_rule,
                TODO_rule
            >
        >,
        chpar::char_<'}'>
    >
> {};

typedef chpar::choice<
    TODO_rule,
    TODO_rule
> Grammar;

} } }
#endif
