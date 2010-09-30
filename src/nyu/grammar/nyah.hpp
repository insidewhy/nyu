#ifndef NYU_GRAMMAR_NYAH_HPP
#define NYU_GRAMMAR_NYAH_HPP

#include <nyu/grammar/nyu.hpp>

namespace nyu { namespace grammar { namespace nyah {

using namespace chilon::parser;
using namespace chilon::parser::ascii;

using nyu::Spacing;

typedef nyu::Identifier MetaIdentifier;

typedef joined_plus<char_<'.'>, MetaIdentifier> ScopedIdentifier;

typedef sequence<char_<'@',m,o,d,u,l,e>, ScopedIdentifier> ModuleDefinition;

struct MetaGrammar : simple_node<MetaGrammar,
    char_<'@',g,r,a,m,m,a,r>, key<MetaIdentifier>,
    optional<char_<':'>, ScopedIdentifier>,
    nyu::Grammar> {};

struct Module : simple_node<Module,
    key_plus< optional<ModuleDefinition> >,
    many_plus<MetaGrammar> > {};

typedef sequence<
    char_<'@',i,n,c,l,u,d,e>,
    joined_plus<char_<'/'>, MetaIdentifier> > Include;

typedef sequence<
    many<Include>, many_plus<Module> > Grammar;

} } }
#endif
