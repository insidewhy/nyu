#ifndef NYU_CPP_OUTPUT_FILE_HPP
#define NYU_CPP_OUTPUT_FILE_HPP

#include <nyu/cpp/builder.hpp>
#include <nyu/cpp/config.hpp>

#include <chilon/getset.hpp>
#include <chilon/iterator_range.hpp>

#include <fstream>
#include <sstream>
#include <string>

namespace nyu { namespace cpp {

struct output_file {
    typedef builder::ns_type      ns_type;
    typedef builder::module_type  module_type;

    typedef chilon::range range;

    typedef chilon::key_value<
        range, grammar::nyah::Enum, chilon::key_unique>   enum_type;

    typedef chilon::key_value<
        range, grammar::nyah::Class, chilon::key_unique>  class_type;

  protected:
    std::stringstream   body_;
    builder&            builder_;
    std::ofstream       stream_;

    bool is_open() const { return stream_.is_open(); }
    bool verbose_comments() const {
        return builder_.opts().verbose_comments_;
    }

    template <class S>
    inline void print_indent(S& str, int const indent) {
        for (int i = 0; i < indent; ++i) str << NYU_CPP_INDENT;
    }

    void operator()(enum_type& enm, int const indent = 0);

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

    void open(ns_type const& ns);
    void open(ns_type const& ns, range const& id);

  public:
    CHILON_GET_REF(stream)

    output_file(output_file const& rhs) = delete;
    output_file(decltype(builder_)& builder) : builder_(builder) {}
};

} }
#endif
