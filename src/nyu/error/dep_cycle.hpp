#ifndef NYU_ERROR_DEP_CYCLE_HPP
#define NYU_ERROR_DEP_CYCLE_HPP

#include <nyu/error/file_location.hpp>

#include <chilon/iterator_range.hpp>

#include <stdexcept>
#include <vector>

namespace nyu { namespace error {

struct dep_cycle : many_file_locations {
    template <class T>
    dep_cycle(T const& loc)
      : many_file_locations("dependency cycle", loc) {}

    ~dep_cycle() throw() {}
};

} }
#endif
