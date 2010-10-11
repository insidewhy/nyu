#ifndef NYU_ERROR_INCLUDE_NOT_FOUND_HPP
#define NYU_ERROR_INCLUDE_NOT_FOUND_HPP

#include <chilon/iterator_range.hpp>

#include <stdexcept>
#include <vector>

namespace nyu { namespace error {

struct include_not_found : std::runtime_error {
    std::vector<chilon::range> id_;

    include_not_found(decltype(id_) const& id)
      : std::runtime_error("include not found"), id_(id) {}

    ~include_not_found() throw() {}
};

} }
#endif
