#include <nyu/cpp/build_grammar.hpp>

namespace nyu { namespace cpp {

void build_grammar::close() {
    scope_ref_cache::close();

    if (! module_.first.empty()) {
        open_namespace(module_.first);
        stream_ << body_.str();
        close_namespace(module_.first.size());
    }
    else stream_ << body_.str();

    chilon::print(stream_, "\n#endif\n");
    stream_ << std::flush;
    stream_.close();
}

void build_grammar::open() {
    output_file::open(module_.first, grammar_.first);
}

void build_grammar::operator()(rule_type& rule) {
}

} }
