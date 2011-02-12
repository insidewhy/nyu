#ifndef nyu_grammar_meta_HPP
#define nyu_grammar_meta_HPP

#include <nyu/grammar/nyah.hpp>

namespace nyu { namespace grammar { namespace meta {

namespace chpar = chilon::parser;

typedef TODO_rule Id;

typedef TODO_rule ScopedId;

typedef chpar::join<
> ModuleId;

typedef chpar::sequence<
> ModuleDefinition;

struct NyuGrammar : simple_node<NyuGrammar, TODO> {}

struct Module : simple_node<Module, TODO> {}

typedef chpar::sequence<
> Include;

typedef chpar::sequence<
> Grammar;

} } }
#endif
