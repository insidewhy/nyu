#ifndef NYU_GRAMMAR_GRAMMAR_HPP
#define NYU_GRAMMAR_GRAMMAR_HPP

#include <nyu/grammar/NyuRule.hpp>

#include <chilon/parser.hpp>

namespace nyu { namespace grammar {

namespace nyu {

using namespace chilon::parser;
using namespace chilon::parser::ascii;

// for compatibility with generated code
namespace chpar = chilon::parser;

typedef chpar::choice<
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
> Spacing;

typedef char_<'.'> AnyCharacter;

struct CharacterRange : simple_node<CharacterRange, lexeme<
    char_<'['>,
    many<
        choice<
            lexeme<
                store<char_<'\\'>>,
                char_from<'\\',']',s,S,n,N,t,T> >,
            lexeme< not_char<']'>, char_<'-'>, not_char<']'> >,
            not_char<']'> > >,
    char_<']'>
> > {};

typedef lexeme<
    store<char_<'\\'>>,
    char_from<s,S,n,N,t,T,'.','"','\'','&','!','+','*','\\'>> Escape;

struct String : simple_node<String, choice<
    lexeme< char_<'"'>,
        many_range< choice<Escape, not_char<'"'> > >,
    char_<'"'> >,
    lexeme< char_<'\''>,
        many_range< choice<Escape, not_char<'\''> > >,
    char_<'\''> >
> > {};

typedef lexeme<
    choice<char_<'_'>, char_range<a,z, A,Z> >,
    many< choice<
        char_range<a,z, A,Z, '0','9'>,
        char_<'_'>
    > > > Id;

typedef joined_plus<char_<'.'>, Id>      ScopedId;
typedef joined_plus<char_<':', ':'>, Id> ScopedRule;

struct Expression;

typedef choice<
    String, CharacterRange, Escape, AnyCharacter,
    sequence< ScopedRule, not_< char_<'<'> > >,
    sequence< char_<'('>, node<Expression>, char_<')'> >
> Primary;

typedef choice<
    char_from<'+', '?', '*'>,
    char_<'^', '+'>,
    char_<'^', '*'>,
    char_<'|', '+'>,
    char_<'|', '?'> > Suffixes;

struct Suffix
  : simple_node<Suffix, Primary, tree_optional<Suffixes>> {};

typedef choice<
    char_<'&', '!'>, char_<'#', '+'>, char_from<'&', '!', '#'> > Prefixes;

struct Prefix
  : simple_node<Prefix, tree_optional<Prefixes>, Suffix> {};

struct Join : simple_node<Join,
    Prefix,
    choice<
        char_<'^', '%'>,
        char_<'%', '+'>,
        char_<'%'>,
        char_<'|', '%'>,
        char_<'|', '^', '%'> >,
    Prefix> {};

struct Joined : simple_node<Joined,
    tree_joined<char_<'^'>, choice<Join, Prefix> > > {};

struct Sequence : simple_node<Sequence, tree_many<Joined> > {};

struct OrderedChoice : simple_node<OrderedChoice,
    tree_joined<char_<'/'>, Sequence> > {};

struct Expression : simple_node<Expression, OrderedChoice> {};

struct Rule : NyuRule, simple_node<Rule,
    key<Id>,
    char_<'<'>, joined<char_<','>, ScopedId>, char_from<'=', '-'>,
    Expression > {};

typedef many<Rule> Grammar;

} } }
#endif
