#ifndef nyu_grammar_nyu_HPP
#define nyu_grammar_nyu_HPP

#include <chilon/parser.hpp>

namespace nyu { namespace grammar { namespace nyu {

namespace chpar = chilon::parser;

typedef chpar::many_plus<
    chpar::TODO_choice<
        TODO_escape_sequence,
        chpar::lexeme<
            chpar::char_<'/', '/'>,
            chpar::many<
                chpar::TODO_prefix<
                    TODO_escape_sequence
                >
            >,
            TODO_escape_sequence
        >
    >
> Spacing;

typedef chpar::char_<'.'> AnyCharacter;

struct CharacterRange : simple_node<
    CharacterRange,
    chpar::lexeme<
        chpar::char_<'['>,
        chpar::many<
            chpar::TODO_choice<
                chpar::lexeme<
                    chpar::char_range<
                        TODO
                    >,
                    chpar::char_range<
                        TODO
                    >
                >,
                chpar::lexeme<
                    chpar::char_<'.'>,
                    chpar::char_<'-'>,
                    chpar::char_<'.'>
                >,
                chpar::char_<'.'>
            >
        >,
        chpar::char_<']'>
    >
> {};

typedef chpar::lexeme<
    chpar::char_range<
        TODO
    >,
    chpar::char_range<
        TODO
    >
> Escape;

struct String : simple_node<
    String,
    chpar::TODO_choice<
        chpar::lexeme<
            chpar::char_<'"'>,
            chpar::TODO_suffix<
                chpar::TODO_choice<
                    TODO_rule,
                    chpar::TODO_prefix<
                        chpar::char_<'"'>
                    >
                >
            >,
            chpar::char_<'"'>
        >,
        chpar::lexeme<
            chpar::char_<'\''>,
            chpar::TODO_suffix<
                chpar::TODO_choice<
                    TODO_rule,
                    chpar::TODO_prefix<
                        chpar::char_<'\''>
                    >
                >
            >,
            chpar::char_<'\''>
        >
    >
> {};

typedef chpar::lexeme<
    chpar::char_range<
        TODO
    >,
    chpar::many_plus<
        chpar::char_range<
            TODO
        >
    >
> Id;

typedef chpar::joined_plus<
    TODO
> ScopedId;

typedef chpar::joined_plus<
    TODO
> ScopedRule;

typedef chpar::TODO_choice<
    TODO_rule,
    TODO_rule,
    TODO_rule,
    TODO_rule,
    chpar::sequence<
        TODO
    >,
    chpar::sequence<
        TODO
    >
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
    chpar::tree_joined<
        TODO
    >
> {};

struct Sequence : simple_node<
    Sequence,
    chpar::TODO_suffix<
        TODO_rule
    >
> {};

struct OrderedChoice : simple_node<
    OrderedChoice,
    chpar::tree_joined<
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
    TODO_rule
> Grammar;

} } }
#endif
