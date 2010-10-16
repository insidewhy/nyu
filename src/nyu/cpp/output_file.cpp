#include <nyu/cpp/output_file.hpp>

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

} }
