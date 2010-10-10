#ifndef NYU_GRAMMAR_NYAH_HPP
#define NYU_GRAMMAR_NYAH_HPP

#include <nyu/grammar/nyu.hpp>

namespace nyu { namespace grammar { namespace nyah {

using namespace chilon::parser;
using namespace chilon::parser::ascii;

using nyu::Spacing;

typedef nyu::Identifier Identifier;

typedef joined_plus<char_<'.'>, Identifier> ScopedIdentifier;

typedef sequence<char_<'@',m,o,d,u,l,e>, ScopedIdentifier> ModuleDefinition;

typedef Identifier EnumEntry;
struct Enum : simple_node<Enum,
    char_<e,n,u,m>, key<Identifier>, char_<'{'>,
        joined<char_<','>, EnumEntry>,
    char_<'}'> >
{};

struct Attribute : simple_node<Attribute,
    key<Identifier>, char_<':'>, ScopedIdentifier> {};

struct Class : simple_node<Class,
    char_<c,l,a,s,s>, key<Identifier>, char_<'{'>,
    many<choice<Attribute, Enum>>,
    char_<'}'> > {};

struct NyuGrammar : simple_node<NyuGrammar,
    char_<'@',g,r,a,m,m,a,r>, key<Identifier>,
    optional<char_<':'>, ScopedIdentifier>,
    nyu::Grammar> {};

struct Module : simple_node<Module,
    key_plus< optional<ModuleDefinition> >,
    many_plus< choice<Class, NyuGrammar> > > {};

typedef sequence<
    char_<'@',i,n,c,l,u,d,e>,
    joined_plus<char_<'/'>, Identifier> > Include;

typedef sequence<
    many<Include>, many_plus<Module> > Grammar;

} } }
#endif
