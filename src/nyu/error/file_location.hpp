#ifndef NYU_ERROR_GRAMMAR_RANGE_HPP
#define NYU_ERROR_GRAMMAR_RANGE_HPP

#include <chilon/iterator_range.hpp>

#include <stdexcept>
#include <vector>

namespace nyu { namespace error {

struct file_location : std::runtime_error {
    file_location(std::string const& msg, chilon::range const& loc)
      : std::runtime_error(msg), location_(loc) {}

    file_location(std::string                const& msg,
                  std::vector<chilon::range> const& loc)
      : std::runtime_error(msg),
        location_(loc.front().begin(), (loc.end() - 1)->end()) {}

    ~file_location() throw() {}

    chilon::range location_;
};

struct many_file_locations : std::runtime_error {
    many_file_locations(std::string const& msg, chilon::range const& loc)
      : std::runtime_error(msg)
    { locations_.push_back(loc); }

    // convert range into file range.. if the vector has ranges that
    // cover different files or are not in order in the file this
    // would screw up bad
    many_file_locations(std::string                const& msg,
                        std::vector<chilon::range> const& loc)
      : std::runtime_error(msg)
    {
        locations_.push_back(
            chilon::range(loc.front().begin(), (loc.end() - 1)->end()));
    }

    void push_back(chilon::range const& loc) {
        locations_.push_back(loc);
    }

    ~many_file_locations() throw() {}

    std::vector<chilon::range> locations_;
};

} }
#endif
