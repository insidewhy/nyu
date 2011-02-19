#ifndef nyu_grammar_nyah_HPP
#define nyu_grammar_nyah_HPP

#include <nyu/grammar/nyu.hpp>

namespace nyu { namespace grammar { namespace nyah {

namespace chpar = chilon::parser;

typedef TODO_parent_rule Id;

typedef TODO_parent_rule ScopedId;

typedef chpar::many_plus<
    chpar::char_range<
        TODO
    >
> UnsignedInteger;

typedef chpar::sequence<
    chpar::key<
        Id
    >,
    chpar::sequence<
        chpar::char_<'='>,
        UnsignedInteger
    >
> EnumEntry;

struct Enum : simple_node<
    Enum,
    chpar::sequence<
        chpar::char_<'e', 'n', 'u', 'm'>,
        chpar::key<
            Id
        >,
        chpar::char_<'{'>,
        chpar::many<
            EnumEntry
        >,
        chpar::char_<'}'>
    >
> {};

typedef ScopedId AssignExpression;

typedef ScopedId Type;

struct Attribute : simple_node<
    Attribute,
    chpar::sequence<
        chpar::key<
            Id
        >,
        chpar::char_<':'>,
        Type
    >
> {};

struct AssignedAttribute : simple_node<
    AssignedAttribute,
    chpar::sequence<
        chpar::key<
            Id
        >,
        chpar::char_<':'>,
        chpar::char_<'='>,
        AssignExpression
    >
> {};

struct Class : simple_node<
    Class,
    chpar::sequence<
        chpar::char_<'c', 'l', 'a', 's', 's'>,
        chpar::key<
            Id
        >,
        chpar::char_<'{'>,
        chpar::many<
            chpar::choice<
                Attribute,
                AssignedAttribute,
                Enum
            >
        >,
        chpar::char_<'}'>
    >
> {};

typedef chpar::choice<
    Class,
    Enum
> Grammar;

} } }
#endif
