#include <nyu/cpp/scope_ref_cache.hpp>

#include <chilon/print_join.hpp>

#include <fstream>

namespace nyu { namespace cpp {

struct print_include {
    template <class T>
    void operator()(T& t) {
        chilon::print_join(stream_, '/', t.first);
    }

    std::ofstream& stream_;
    print_include(decltype(stream_)& stream) : stream_(stream) {}
};

void scope_ref_cache::close() {
    if (type_ref_map_.empty()) return;

    stream_ << '\n';
    for (auto it = type_ref_map_.begin(); it != type_ref_map_.end(); ++it) {
        stream_ << "#include <";
        chilon::variant_apply(*it, print_include(stream_));
        stream_ << ".hpp>\n";
    }
}

} }
