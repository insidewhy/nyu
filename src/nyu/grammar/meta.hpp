#ifndef NYU_GRAMMAR_META_HPP
#define NYU_GRAMMAR_META_HPP

#include <nyu/grammar/nyah.hpp>

namespace nyu { namespace grammar { namespace meta {

using namespace chilon::parser;
using namespace chilon::parser::ascii;

using nyah::Spacing;
using nyah::Id;
using nyah::ScopedId;

typedef joined_plus<char_<'.'>, Id> ModuleId;

typedef sequence<char_<'@',m,o,d,u,l,e>, ModuleId> ModuleDefinition;

struct NyuGrammar : WithStatus, simple_node<NyuGrammar,
    char_<'@',g,r,a,m,m,a,r>, key<Id>,
    optional<char_<':'>, ScopedId>,
    nyu::Grammar> {};

struct Module : WithStatus, simple_node<Module,
    key_plus< optional<ModuleDefinition> >,
    many_plus< choice<nyah::Grammar, NyuGrammar> > > {};

typedef sequence<
    char_<'@',i,n,c,l,u,d,e>,
    joined_plus<char_<'/'>, Id> > Include;

typedef sequence<many<Include>, many<Module>> Grammar;

} } }
#endif
