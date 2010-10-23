#ifndef NYU_ERROR_OUTPUT_FILE_HPP
#define NYU_ERROR_OUTPUT_FILE_HPP

#include <stdexcept>

namespace nyu { namespace error {

struct cannot_open_output_file : std::runtime_error {
    cannot_open_output_file(std::string const& file_path)
      : std::runtime_error("could not open file for writing"),
        file_path_(file_path)
    {}
    ~cannot_open_output_file() throw() {}
    std::string file_path_;
};

} }
#endif
