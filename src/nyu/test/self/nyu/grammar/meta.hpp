#ifndef nyu_grammar_meta_HPP
#define nyu_grammar_meta_HPP

#include <nyu/grammar/nyah.hpp>

namespace nyu { namespace grammar { namespace meta {

namespace chpar = chilon::parser;

typedef TODO_parent_rule Id;

typedef TODO_parent_rule ScopedId;

typedef chpar::joined_plus<
    chpar::char_<'.'>,
    Id
> ModuleId;

typedef chpar::sequence<
    chpar::char_<'@', 'm', 'o', 'd', 'u', 'l', 'e'>,
    ModuleId
> ModuleDefinition;

struct NyuGrammar : WithStatus, chpar::simple_node<
    NyuGrammar,
    chpar::sequence<
        chpar::char_<'@', 'g', 'r', 'a', 'm', 'm', 'a', 'r'>,
        chpar::key<
            Id
        >,
        chpar::optional<
            chpar::sequence<
                chpar::char_<':'>,
                ScopedId
            >
        >,
        TODO_parent_rule
    >
> {};

struct Module : WithStatus, chpar::simple_node<
    Module,
    chpar::sequence<
        chpar::key_plus<
            chpar::optional<
                ModuleDefinition
            >
        >,
        chpar::many_plus<
            chpar::choice<
                TODO_parent_rule,
                NyuGrammar
            >
        >
    >
> {};

typedef chpar::sequence<
    chpar::char_<'@', 'i', 'n', 'c', 'l', 'u', 'd', 'e'>,
    chpar::joined_plus<
        chpar::char_<'/'>,
        Id
    >
> Include;

typedef chpar::sequence<
    chpar::many<
        Include
    >,
    chpar::many<
        Module
    >
> Grammar;

} } }
#endif
