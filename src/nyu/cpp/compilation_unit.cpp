#include <nyu/cpp/compilation_unit.hpp>
#include <nyu/cpp/build_grammar.hpp>
#include <nyu/error/dep_cycle.hpp>

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

void compilation_unit::close() {
    if (type_ref_map_.empty()) return;

    stream_ << '\n';
    for (auto it = type_ref_map_.begin(); it != type_ref_map_.end(); ++it) {
        stream_ << "#include <";
        chilon::variant_apply(*it, print_include(stream_));
        stream_ << ".hpp>\n";
    }
}

void compilation_unit::build_grammar_scope(grammar_type& grammar,
                                          module_type&  module)
{
    if (grammar::Status::PROCESSING == grammar.second.status_)
        throw error::dep_cycle(grammar.first);
    else if (grammar::Status::PROCESSED == grammar.second.status_)
        return;

    cpp::build_grammar grammar_builder(builder_, module, grammar);
    auto& children = std::get<1>(grammar.second.value_);
    for (auto it = children.begin(); it != children.end(); ++it) {
        grammar_builder(*it);
    }
    grammar_builder.close();

    grammar.second.status_ = grammar::Status::PROCESSED;
}

} }
