#ifndef nyu_grammar_nyu_HPP
#define nyu_grammar_nyu_HPP

#include <chilon/parser.hpp>

#include <nyu/grammar/NyuRule.hpp>

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

struct CharacterRange : chpar::simple_node<
    CharacterRange,
    chpar::lexeme<
        chpar::char_<'['>,
        chpar::many<
            chpar::choice<
                chpar::lexeme<
                    chpar::store<
                        chpar::char_<'\\'>
                    >,
                    chpar::choice<
                        chpar::char_<'\\'>,
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
                    chpar::any_char,
                    chpar::char_<'-'>,
                    chpar::any_char
                >,
                chpar::tbpeg_not<
                    chpar::char_<']'>
                >
            >
        >,
        chpar::char_<']'>
    >
> {};

typedef chpar::lexeme<
    chpar::store<
        chpar::char_<'\\'>
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
        chpar::char_<'\\'>
    >
> Escape;

struct String : chpar::simple_node<
    String,
    chpar::choice<
        chpar::lexeme<
            chpar::char_<'"'>,
            chpar::many_range<
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
            chpar::many_range<
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
    chpar::many<
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

struct Expression;

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
        chpar::node<Expression>,
        chpar::char_<')'>
    >
> Primary;

struct Suffix : chpar::simple_node<
    Suffix,
    chpar::sequence<
        Primary,
        chpar::tree_optional<
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

struct Prefix : chpar::simple_node<
    Prefix,
    chpar::sequence<
        chpar::tree_optional<
            chpar::choice<
                chpar::char_<'&', '!'>,
                chpar::char_<'#', '+'>,
                chpar::char_from<'&', '!', '#'>
            >
        >,
        Suffix
    >
> {};

struct Join : chpar::simple_node<
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

struct Joined : chpar::simple_node<
    Joined,
    chpar::tree_joined<
        chpar::char_<'^'>,
        chpar::choice<
            Join,
            Prefix
        >
    >
> {};

struct Sequence : chpar::simple_node<
    Sequence,
    chpar::tree_many<
        Joined
    >
> {};

struct OrderedChoice : chpar::simple_node<
    OrderedChoice,
    chpar::tree_joined<
        chpar::char_<'/'>,
        Sequence
    >
> {};

struct Expression : chpar::simple_node<
    Expression,
    OrderedChoice
> {};

struct Rule : NyuRule, chpar::simple_node<
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
