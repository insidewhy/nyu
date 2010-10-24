#include <nyu/cpp/build_class.hpp>

namespace nyu { namespace cpp {

struct build_class::build_class_assigned_attr {
    std::stringstream  type_;
    std::stringstream  value_;

    template <class T>
    void operator()(T& t) {
        // todo: throw error
        // std::cerr << "bad assignment" << std::endl;
    }

    void operator()(enum_type& enm) {
    }
};

void build_class::operator()(attr_type& attr) {
}

void build_class::operator()(assigned_attr_type& attr) {
    // current rhs can only be a scoped id.. vector of range
    auto& rhs = attr.second.value_;
    auto& class_scope = class_.second.value_;

    auto it = class_scope.find(rhs.front());
    if (it == class_scope.end()) {
        // search in preceding namespaces
    }
    else chilon::variant_apply(*it, build_class_assigned_attr());
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
