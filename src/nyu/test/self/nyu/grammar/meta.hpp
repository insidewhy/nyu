#ifndef nyu_grammar_meta_HPP
#define nyu_grammar_meta_HPP

#include <nyu/grammar/nyah.hpp>

namespace nyu { namespace grammar { namespace meta {

namespace chpar = chilon::parser;

typedef TODO_rule Id;

typedef TODO_rule ScopedId;

typedef chpar::join<
    TODO
> ModuleId;

typedef chpar::sequence<
    TODO
> ModuleDefinition;

struct NyuGrammar : simple_node<
    NyuGrammar,
    TODO
> {}

struct Module : simple_node<
    Module,
    TODO
> {}

typedef chpar::sequence<
    TODO
> Include;

typedef chpar::sequence<
    TODO
> Grammar;

} } }
#endif
