#ifndef order_HPP
#define order_HPP

#include <chilon/parser.hpp>
namespace order {

namespace chpar = chilon::parser;

typedef chpar::char_from<'\n', '\t', ' '> Spacing;

typedef chpar::char_<'p'> A;

struct D;

typedef chpar::sequence<
    chpar::char_<'i'>,
    A,
    chpar::node<D>
> B;

typedef chpar::sequence<
    chpar::char_<'t'>,
    B,
    chpar::node<D>
> C;

struct D : chpar::simple_node<
    D,
    chpar::sequence<
        chpar::any_char,
        chpar::any_char
    >
> {};

}
#endif
