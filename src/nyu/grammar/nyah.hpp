#ifndef NYU_GRAMMAR_NYAH_HPP
#define NYU_GRAMMAR_NYAH_HPP

#include <nyu/grammar/nyu.hpp>

namespace nyu { namespace grammar { namespace nyah {

using namespace chilon::parser;
using namespace chilon::parser::ascii;

using nyu::Spacing;
using nyu::Identifier;
using nyu::ScopedIdentifier;

typedef Identifier EnumEntry;
struct Enum : simple_node<Enum,
    char_<e,n,u,m>, key<Identifier>, char_<'{'>,
        joined<char_<','>, EnumEntry>,
    char_<'}'> >
{};

typedef ScopedIdentifier Type;
typedef ScopedIdentifier AssignExpression;

struct Attribute : simple_node<Attribute,
    key<Identifier>, char_<':'>, Type> {};

struct AssignedAttribute : simple_node<AssignedAttribute,
    key<Identifier>, char_<':'>, char_<'='>, AssignExpression> {};

struct Class : simple_node<Class,
    char_<c,l,a,s,s>, key<Identifier>, char_<'{'>,
    many<choice<Attribute, AssignedAttribute, Enum>>,
    char_<'}'> > {};

} } }
#endif
