#include <nyu/cpp/build_class.hpp>

namespace nyu { namespace cpp {

void build_class::operator()(attr_type& attr) {
    // mega todo:
}

void build_class::operator()(assigned_attr_type& attr) {
    // mega todo:
    // lookup type of ns_type attr.second
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
    body_ << "\nclass " << class_.first << " {";
}

} }
