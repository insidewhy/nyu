#include <nyu/cpp/output_file.hpp>

#include <chilon/print.hpp>
#include <chilon/print_join.hpp>

#include <sstream>

namespace nyu { namespace cpp {

void output_file::open(char const *filename, char const *guard) {
    builder_.opts().output_path(stream_, filename);
    chilon::print(stream_, "#ifndef global_HPP\n");
    chilon::print(stream_, "#define global_HPP\n\n");
}

void output_file::open(ns_type const& ns) {
    builder_.opts().output_path(stream_, ns, ".hpp");

    std::stringstream guard;
    chilon::print_join(guard, '_', ns);
    chilon::print(stream_, "#ifndef ", guard.str(), "_HPP\n");
    chilon::print(stream_, "#define ", guard.str(), "_HPP\n\n");
}

} }
