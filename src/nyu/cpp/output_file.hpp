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
    typedef std::vector<chilon::range>  path_type;
    typedef path_type                   ns_type;

    builder&       builder_;
    std::ofstream  stream_;

    bool is_open() const { return stream_.is_open(); }
    bool verbose_comments() const {
        return builder_.opts().verbose_comments_;
    }

    void open_namespace(ns_type const& ns) {
        stream_ << "namespace " << ns.front() << " {";
        for (auto it = ns.begin() + 1; it != ns.end(); ++it)
            stream_ << " namespace " << *it << " {";
        stream_ << '\n';
    }

    void close_namespace(unsigned int const depth) {
        stream_ << "\n}";
        for (auto i = 1u; i < depth; ++i) stream_ << " }";
    }

    void open(char const *filename, char const *guard);
    void open(path_type const& path);

  public:
    CHILON_GET_REF(stream)

    output_file(output_file const& rhs) = delete;
    output_file(decltype(builder_)& builder) : builder_(builder) {}
};

} }
#endif
