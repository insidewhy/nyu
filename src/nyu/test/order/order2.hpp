#ifndef order2_HPP
#define order2_HPP

#include <chilon/parser.hpp>
namespace order2 {

namespace chpar = chilon::parser;

typedef chpar::many_plus<
    chpar::char_range<'a','z'>
> Id;

struct C;

struct B : chpar::simple_node<
    B,
    chpar::sequence<
        chpar::node<C>,
        chpar::tree_optional<
            Id
        >
    >
> {};

struct C : chpar::simple_node<
    C,
    chpar::sequence<
        B,
        Id
    >
> {};

}
#endif
