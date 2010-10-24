#include <nyu/cpp/build_class.hpp>
#include <nyu/cpp/get_type_and_value.hpp>

#include <chilon/noncopyable.hpp>

namespace nyu { namespace cpp {

void build_class::operator()(attr_type& attr) {
}

void build_class::operator()(assigned_attr_type& attr) {
    // current rhs can only be a scoped id.. vector of range
    get_type_and_value resolver(attr.second.value_);
    resolver(*this);

    // TODO: put type() and value() in constructor string
}

void build_class::close() {
    if (! module_id_.empty()) {
        open_namespace(module_id_);
        stream_ << body_.str() << "\n};\n";
        close_namespace(module_id_.size());
    }
    else stream_ << body_.str() << "\n};\n";

    chilon::print(stream_, "\n#endif");
    stream_ << std::flush;
    stream_.close();
}

void build_class::open() {
    output_file::open(module_id_, class_.first);
    body_ << "\nstruct " << class_.first << " {";
}

} }
