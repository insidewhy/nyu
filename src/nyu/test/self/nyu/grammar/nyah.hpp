#ifndef nyu_grammar_nyah_HPP
#define nyu_grammar_nyah_HPP

#include <nyu/grammar/nyu.hpp>

#include <nyu/grammar/WithStatus.hpp>

namespace nyu { namespace grammar { namespace nyah {

namespace chpar = chilon::parser;

typedef nyu::Id Id;

typedef nyu::ScopedId ScopedId;

typedef nyu::Grammar NyuGrammar;

typedef chpar::many_plus<
    chpar::char_range<'0','9'>
> UnsignedInteger;

typedef chpar::sequence<
    chpar::key<
        Id
    >,
    chpar::optional<
        chpar::sequence<
            chpar::char_<'='>,
            UnsignedInteger
        >
    >
> EnumEntry;

struct Enum : chpar::simple_node<
    Enum,
    chpar::sequence<
        chpar::char_<'e', 'n', 'u', 'm'>,
        chpar::key<
            Id
        >,
        chpar::char_<'{'>,
        chpar::joined<
            chpar::char_<','>,
            EnumEntry
        >,
        chpar::char_<'}'>
    >
> {};

typedef ScopedId AssignExpression;

typedef ScopedId Type;

struct Attribute : chpar::simple_node<
    Attribute,
    chpar::sequence<
        chpar::key<
            Id
        >,
        chpar::char_<':'>,
        Type
    >
> {};

struct AssignedAttribute : chpar::simple_node<
    AssignedAttribute,
    chpar::sequence<
        chpar::key<
            Id
        >,
        chpar::char_<':'>,
        chpar::optional<
            Type
        >,
        chpar::char_<'='>,
        AssignExpression
    >
> {};

struct Class : WithStatus, chpar::simple_node<
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
