#ifndef nyu_grammar_nyu_HPP
#define nyu_grammar_nyu_HPP

#include <chilon/parser.hpp>

namespace nyu { namespace grammar { namespace nyu {

namespace chpar = chilon::parser;

typedef chpar::many_plus<
    chpar::choice<
        chpar::char_from<'\n', '\t', ' '>,
        chpar::lexeme<
            chpar::char_<'/', '/'>,
            chpar::many<
                chpar::tbpeg_not<
                    chpar::char_<'\n'>
                >
            >,
            chpar::char_<'\n'>
        >
    >
> Spacing;

typedef chpar::char_<'.'> AnyCharacter;

struct CharacterRange : simple_node<
    CharacterRange,
    chpar::lexeme<
        chpar::char_<'['>,
        chpar::many<
            chpar::choice<
                chpar::lexeme<
                    chpar::choice<
                        chpar::char_<'\'>
                    >,
                    chpar::choice<
                        chpar::char_<'\'>,
                        chpar::char_<']'>,
                        chpar::char_<'s'>,
                        chpar::char_<'S'>,
                        chpar::char_<'n'>,
                        chpar::char_<'N'>,
                        chpar::char_<'t'>,
                        chpar::char_<'T'>
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
    chpar::choice<
        chpar::char_<'\'>
    >,
    chpar::choice<
        chpar::char_<'s'>,
        chpar::char_<'S'>,
        chpar::char_<'n'>,
        chpar::char_<'N'>,
        chpar::char_<'t'>,
        chpar::char_<'T'>,
        chpar::char_<'.'>,
        chpar::char_<'"'>,
        chpar::char_<'\''>,
        chpar::char_<'&'>,
        chpar::char_<'!'>,
        chpar::char_<'+'>,
        chpar::char_<'*'>,
        chpar::char_<'\'>
    >
> Escape;

struct String : simple_node<
    String,
    chpar::choice<
        chpar::lexeme<
            chpar::char_<'"'>,
            chpar::many_plus<
                chpar::choice<
                    Escape,
                    chpar::tbpeg_not<
                        chpar::char_<'"'>
                    >
                >
            >,
            chpar::char_<'"'>
        >,
        chpar::lexeme<
            chpar::char_<'\''>,
            chpar::many_plus<
                chpar::choice<
                    Escape,
                    chpar::tbpeg_not<
                        chpar::char_<'\''>
                    >
                >
            >,
            chpar::char_<'\''>
        >
    >
> {};

typedef chpar::lexeme<
    chpar::choice<
        chpar::char_range<'a','z'>,
        chpar::char_range<'A','Z'>,
        chpar::char_<'_'>
    >,
    chpar::many_plus<
        chpar::choice<
            chpar::char_range<'a','z'>,
            chpar::char_range<'A','Z'>,
            chpar::char_range<'0','9'>,
            chpar::char_<'_'>
        >
    >
> Id;

typedef chpar::joined_plus<
    chpar::char_<'.'>,
    Id
> ScopedId;

typedef chpar::joined_plus<
    chpar::char_<':', ':'>,
    Id
> ScopedRule;

typedef chpar::choice<
    String,
    CharacterRange,
    Escape,
    AnyCharacter,
    chpar::sequence<
        ScopedRule,
        chpar::not_<
            chpar::char_<'<'>
        >
    >,
    chpar::sequence<
        chpar::char_<'('>,
        Expression,
        chpar::char_<')'>
    >
> Primary;

struct Suffix : simple_node<
    Suffix,
    chpar::sequence<
        Primary,
        chpar::TODO_suffix_|?<
            chpar::choice<
                chpar::char_from<'?', '*', '+'>,
                chpar::char_<'^', '+'>,
                chpar::char_<'^', '*'>,
                chpar::char_<'|', '+'>,
                chpar::char_<'|', '?'>
            >
        >
    >
> {};

struct Prefix : simple_node<
    Prefix,
    chpar::sequence<
        chpar::TODO_suffix_|?<
            chpar::choice<
                chpar::char_<'&', '!'>,
                chpar::char_<'#', '+'>,
                chpar::char_from<'&', '!', '#'>
            >
        >,
        Suffix
    >
> {};

struct Join : simple_node<
    Join,
    chpar::sequence<
        Prefix,
        chpar::choice<
            chpar::char_<'^', '%'>,
            chpar::char_<'%', '+'>,
            chpar::char_<'%'>,
            chpar::char_<'|', '%'>,
            chpar::char_<'|', '^', '%'>
        >,
        Prefix
    >
> {};

struct Joined : simple_node<
    Joined,
    chpar::tree_joined<
        chpar::char_<'^'>,
        chpar::choice<
            Join,
            Prefix
        >
    >
> {};

struct Sequence : simple_node<
    Sequence,
    chpar::TODO_suffix_|+<
        Joined
    >
> {};

struct OrderedChoice : simple_node<
    OrderedChoice,
    chpar::tree_joined<
        chpar::char_<'/'>,
        Sequence
    >
> {};

struct Expression : simple_node<
    Expression,
    OrderedChoice
> {};

struct Rule : simple_node<
    Rule,
    chpar::sequence<
        chpar::key<
            Id
        >,
        chpar::char_<'<'>,
        chpar::joined<
            chpar::char_<','>,
            ScopedId
        >,
        chpar::char_from<'-', '='>,
        Expression
    >
> {};

typedef chpar::many_plus<
    Rule
> Grammar;

} } }
#endif
