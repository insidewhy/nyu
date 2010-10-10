#ifndef NYU_GRAMMAR_META_HPP
#define NYU_GRAMMAR_META_HPP

#include <nyu/grammar/nyah.hpp>

namespace nyu { namespace grammar {

struct NyuGrammar {
    enum class Status {
        PROCESSING,
        PROCESSED, // can be a node
    };

    NyuGrammar() : status_(Status::PROCESSING) {}
    Status status_;
};

namespace meta {

using namespace chilon::parser;
using namespace chilon::parser::ascii;

using nyu::Spacing;
using nyu::Identifier;
using nyu::ScopedIdentifier;

typedef joined_plus<char_<'.'>, Identifier> ScopedIdentifier;

typedef sequence<char_<'@',m,o,d,u,l,e>, ScopedIdentifier> ModuleDefinition;

struct NyuGrammar : grammar::NyuGrammar, simple_node<NyuGrammar,
    char_<'@',g,r,a,m,m,a,r>, key<Identifier>,
    optional<char_<':'>, ScopedIdentifier>,
    nyu::Grammar> {};

struct Module : simple_node<Module,
    key_plus< optional<ModuleDefinition> >,
    many_plus< choice<nyah::Class, NyuGrammar> > > {};

typedef sequence<
    char_<'@',i,n,c,l,u,d,e>,
    joined_plus<char_<'/'>, Identifier> > Include;

typedef sequence<
    many<Include>, many<Module> > Grammar;

} } }
#endif
