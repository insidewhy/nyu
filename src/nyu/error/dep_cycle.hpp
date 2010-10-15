#ifndef NYU_ERROR_GRAMMAR_DEP_CYCLE_HPP
#define NYU_ERROR_GRAMMAR_DEP_CYCLE_HPP

#include <chilon/iterator_range.hpp>

#include <stdexcept>
#include <vector>

namespace nyu { namespace error {

struct dep_cycle : std::runtime_error {
    dep_cycle(chilon::range const& grammar_name)
      : std::runtime_error("dependency cycle")
    { dependencies_.push_back(grammar_name); }

    ~dep_cycle() throw() {}

    std::vector<chilon::range> dependencies_;
};

} }
#endif
