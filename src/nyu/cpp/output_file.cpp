#include <nyu/cpp/output_file.hpp>

#include <chilon/print.hpp>
#include <chilon/print_join.hpp>

#include <sstream>

namespace nyu { namespace cpp {

void output_file::open(ns_type const& ns) {
    if (ns.empty()) {
        builder_.opts().output_path(stream_, "global.hpp");
        chilon::print(stream_, "#ifndef global_HPP\n");
        chilon::print(stream_, "#define global_HPP\n");
    }
    else {
        builder_.opts().output_path(stream_, ns, ".hpp");

        std::stringstream guard;
        chilon::print_join(guard, '_', ns);
        chilon::print(stream_, "#ifndef ", guard.str(), "_HPP\n");
        chilon::print(stream_, "#define ", guard.str(), "_HPP\n");
    }
}

void output_file::open(ns_type const& ns, range const& id) {
    if (ns.empty()) {
        std::string path = id;
        path.append(".hpp");
        builder_.opts().output_path(stream_, path.c_str());
        stream_ << "#ifndef " << id << "_HPP\n";
        stream_ << "#define " << id << "_HPP\n";
    }
    else {
        builder_.opts().output_path(stream_, ns, id, ".hpp");

        std::stringstream guard;
        chilon::print_join(guard, '_', ns);
        guard << "_" << id;
        chilon::print(stream_, "#ifndef ", guard.str(), "_HPP\n");
        chilon::print(stream_, "#define ", guard.str(), "_HPP\n");
    }
}

void output_file::operator()(enum_type& enm, int const indent) {
    body_ << "\n";
    print_indent(body_, indent);
    body_ << "enum class " << enm.first << " {\n";
    print_indent(body_, indent + 1);
    if (! enm.second.value_.empty()) {
        auto it = enm.second.value_.begin();
        body_ << std::get<0>(*it);

        // todo: handle =
        for (++it; it != enm.second.value_.end(); ++it) {
            body_ << ",\n";
            print_indent(body_, indent + 1);
            body_ << std::get<0>(*it);
        }
    }
    body_ << '\n';
    print_indent(body_, indent);
    body_ << "};\n";
}


} }
