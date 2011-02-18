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
    TODO
> {}

typedef chpar::joined<
    TODO
> Escape;

struct String : simple_node<
    String,
    TODO
> {}

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
    TODO
> {}

struct Prefix : simple_node<
    Prefix,
    TODO
> {}

struct Join : simple_node<
    Join,
    TODO
> {}

struct Joined : simple_node<
    Joined,
    TODO
> {}

struct Sequence : simple_node<
    Sequence,
    TODO
> {}

struct OrderedChoice : simple_node<
    OrderedChoice,
    TODO
> {}

struct Expression : simple_node<
    Expression,
    TODO
> {}

struct Rule : simple_node<
    Rule,
    TODO
> {}

typedef chpar::many_plus<
    TODO
> Grammar;

} } }
#endif
