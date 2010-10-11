#ifndef NYU_ERROR_GRAMMAR_DEP_CYCLE_HPP
#define NYU_ERROR_GRAMMAR_DEP_CYCLE_HPP

#include <chilon/iterator_range.hpp>

#include <stdexcept>
#include <vector>

namespace nyu { namespace error {

struct grammar_dep_cycle : std::runtime_error {
    grammar_dep_cycle(chilon::range const& grammar_name)
      : std::runtime_error("recursive grammar cycle")
    { grammars_.push_back(grammar_name); }

    ~grammar_dep_cycle() throw() {}

    std::vector<chilon::range> grammars_;
};

} }
#endif
