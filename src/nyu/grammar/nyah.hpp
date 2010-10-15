#ifndef NYU_GRAMMAR_NYAH_HPP
#define NYU_GRAMMAR_NYAH_HPP

#include <nyu/grammar/nyu.hpp>
#include <nyu/grammar.hpp>

namespace nyu { namespace grammar { namespace nyah {

using namespace chilon::parser;
using namespace chilon::parser::ascii;

using nyu::Spacing;
using nyu::Id;
using nyu::ScopedId;

typedef many_plus<char_range<'0','9'>> UnsignedInteger;

typedef sequence<
    key<Id>, optional<char_<'='>, UnsignedInteger>> EnumEntry;

struct Enum : simple_node<Enum,
    char_<e,n,u,m>, key<Id>, char_<'{'>,
        joined<char_<','>, EnumEntry>,
    char_<'}'> >
{};

typedef ScopedId Type;
typedef ScopedId AssignExpression;

struct Attribute : simple_node<Attribute,
    key<Id>, char_<':'>, Type> {};

struct AssignedAttribute : simple_node<AssignedAttribute,
    key<Id>, char_<':'>, char_<'='>, AssignExpression> {};

struct Class : WithStatus, simple_node<Class,
    char_<c,l,a,s,s>, key<Id>, char_<'{'>,
    many<choice<Attribute, AssignedAttribute, Enum>>,
    char_<'}'> > {};

typedef choice<Class, Enum>  Grammar;

} } }
#endif
