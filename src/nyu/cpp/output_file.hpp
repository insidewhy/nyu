#ifndef NYU_CPP_OUTPUT_FILE_HPP
#define NYU_CPP_OUTPUT_FILE_HPP

#include <nyu/cpp/builder.hpp>

#include <chilon/getset.hpp>
#include <chilon/iterator_range.hpp>

#include <fstream>
#include <string>

namespace nyu { namespace cpp {

class output_file {
  protected:
    builder&       builder_;
    std::ofstream  stream_;

    bool is_open() const { return stream_.is_open(); }
    bool verbose_comments() const {
        return builder_.opts().verbose_comments_;
    }

    void open(char const *filename, char const *guard);
    void open(std::vector<chilon::range> const& path);

  public:
    CHILON_GET_REF(stream)

    output_file(decltype(builder_)& builder) : builder_(builder) {}
};

} }
#endif
