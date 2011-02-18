#ifndef nyu_grammar_nyu_HPP
#define nyu_grammar_nyu_HPP

#include <chilon/parser.hpp>

namespace nyu { namespace grammar { namespace nyu {

namespace chpar = chilon::parser;

typedef chpar::many_plus<
    TODO
> Spacing;

typedef chpar::char_<
    TODO
> AnyCharacter;

struct CharacterRange : simple_node<
    CharacterRange,
    chpar::joined<
        TODO
    >
> {};

typedef chpar::joined<
    TODO
> Escape;

struct String : simple_node<
    String,
    chpar::choice<
        TODO
    >
> {};

typedef chpar::joined<
    TODO
> Id;

typedef chpar::join<
    TODO
> ScopedId;

typedef chpar::join<
    TODO
> ScopedRule;

typedef chpar::choice<
    TODO
> Primary;

struct Suffix : simple_node<
    Suffix,
    chpar::sequence<
        TODO
    >
> {};

struct Prefix : simple_node<
    Prefix,
    chpar::sequence<
        TODO
    >
> {};

struct Join : simple_node<
    Join,
    chpar::sequence<
        TODO
    >
> {};

struct Joined : simple_node<
    Joined,
    chpar::join<
        TODO
    >
> {};

struct Sequence : simple_node<
    Sequence,
    chpar::unknown_suffix<
        TODO
    >
> {};

struct OrderedChoice : simple_node<
    OrderedChoice,
    chpar::join<
        TODO
    >
> {};

struct Expression : simple_node<
    Expression,
    TODO_rule
> {};

struct Rule : simple_node<
    Rule,
    chpar::sequence<
        TODO
    >
> {};

typedef chpar::many_plus<
    TODO
> Grammar;

} } }
#endif
