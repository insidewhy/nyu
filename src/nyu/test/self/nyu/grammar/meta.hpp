#ifndef nyu_grammar_meta_HPP
#define nyu_grammar_meta_HPP

#include <nyu/grammar/nyah.hpp>

namespace nyu { namespace grammar { namespace meta {

namespace chpar = chilon::parser;

typedef TODO_rule Id;

typedef TODO_rule ScopedId;

typedef chpar::joined_plus<
    TODO
> ModuleId;

typedef chpar::sequence<
    chpar::char_<'@', 'm', 'o', 'd', 'u', 'l', 'e'>,
    TODO_rule
> ModuleDefinition;

struct NyuGrammar : simple_node<
    NyuGrammar,
    chpar::sequence<
        chpar::char_<'@', 'g', 'r', 'a', 'm', 'm', 'a', 'r'>,
        chpar::TODO_prefix<
            TODO_rule
        >,
        chpar::optional<
            chpar::sequence<
                chpar::char_<':'>,
                TODO_rule
            >
        >,
        TODO_rule
    >
> {};

struct Module : simple_node<
    Module,
    chpar::sequence<
        chpar::TODO_prefix<
            chpar::optional<
                TODO_rule
            >
        >,
        chpar::many_plus<
            chpar::TODO_choice<
                TODO_rule,
                TODO_rule
            >
        >
    >
> {};

typedef chpar::sequence<
    chpar::char_<'@', 'i', 'n', 'c', 'l', 'u', 'd', 'e'>,
    chpar::joined_plus<
        TODO
    >
> Include;

typedef chpar::sequence<
    chpar::many<
        TODO_rule
    >,
    chpar::many<
        TODO_rule
    >
> Grammar;

} } }
#endif
