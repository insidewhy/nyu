#include <nyu/cpp/output_file.hpp>
#include <nyu/cpp/config.hpp>

#include <chilon/print.hpp>
#include <chilon/print_join.hpp>

#include <sstream>

namespace nyu { namespace cpp {

void output_file::open(ns_type const& ns) {
    if (ns.empty()) {
        builder_.opts().output_path(stream_, "global.hpp");
        chilon::print(stream_, "#ifndef global_HPP\n");
        chilon::print(stream_, "#define global_HPP\n\n");
    }
    else {
        builder_.opts().output_path(stream_, ns, ".hpp");

        std::stringstream guard;
        chilon::print_join(guard, '_', ns);
        chilon::print(stream_, "#ifndef ", guard.str(), "_HPP\n");
        chilon::print(stream_, "#define ", guard.str(), "_HPP\n\n");
    }
}

void output_file::open(ns_type const& ns, range const& id) {
    if (ns.empty()) {
        std::string path = id;
        path.append(".hpp");
        builder_.opts().output_path(stream_, path.c_str());
        stream_ << "#ifndef " << id << "_HPP\n";
        stream_ << "#define " << id << "_HPP\n\n";
    }
    else {
        builder_.opts().output_path(stream_, ns, id, ".hpp");

        std::stringstream guard;
        chilon::print_join(guard, '_', ns);
        guard << "_" << id;
        chilon::print(stream_, "#ifndef ", guard.str(), "_HPP\n");
        chilon::print(stream_, "#define ", guard.str(), "_HPP\n\n");
    }
}

void output_file::operator()(enum_type& enm) {
    body_ << "\nenum class " << enm.first << " {\n" NYU_CPP_INDENT;
    if (! enm.second.value_.empty()) {
        auto it = enm.second.value_.begin();
        body_ << std::get<0>(*it);

        // todo: handle =
        for (++it; it != enm.second.value_.end(); ++it)
            body_ << ",\n" NYU_CPP_INDENT << std::get<0>(*it);
    }
    body_ << "\n};\n";
}


} }
