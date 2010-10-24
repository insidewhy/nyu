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

    attrs_.push_back(
        std::make_tuple(attr.first, resolver.type(), resolver.value()));
}

namespace {
    template <class S, class A>
    void end_class(S&                   stream,
                   chilon::range const& class_name,
                   std::string const&   body,
                   A const&             attrs)
    {
        stream << body;
        if (! attrs.empty()) {
            stream << '\n' << NYU_CPP_INDENT << class_name << "()\n";
            stream << NYU_CPP_INDENT << "  : "
                   << std::get<0>(attrs.front()) << '('
                   << std::get<2>(attrs.front()) << ')';

            // TODO: attributes after first

            stream << '\n' << NYU_CPP_INDENT << "{}";
        }

        stream << "\n};\n";
    }
}

void build_class::close() {
    if (! module_id_.empty()) {
        open_namespace(module_id_);
        end_class(stream_, class_.first, body_.str(), attrs_);
        close_namespace(module_id_.size());
    }
    else end_class(stream_, class_.first, body_.str(), attrs_);

    chilon::print(stream_, "\n#endif");
    stream_ << std::flush;
    stream_.close();
}

void build_class::open() {
    output_file::open(module_id_, class_.first);
    body_ << "\nstruct " << class_.first << " {";
}

} }
