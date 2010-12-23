#include <nyu/cpp/build_grammar.hpp>
#include <nyu/cpp/build_rule.hpp>
#include <nyu/cpp/get_grammar.hpp>

#include <nyu/error/dep_cycle.hpp>

#include <chilon/print_join.hpp>

namespace nyu { namespace cpp {

void build_grammar::close() {
    scope_ref_cache::close();

    if (! module_.first.empty())
        open_namespace(module_.first, grammar_.first);
    else
        stream_ << "namespace " << grammar_.first << "{\n";

    stream_ << "\nusing namespace chilon::parser;\n";
    stream_ << body_.str();
    close_namespace(module_.first.size() + 1);
    chilon::print(stream_, "\n#endif\n");
    stream_.close();
}

void build_grammar::open() {
    output_file::open(module_.first, grammar_.first);

    auto& parent = std::get<0>(grammar_.second.value_);
    if (! parent.empty()) {
        cpp::get_grammar grammar_get(parent);
        grammar_get(*this);

        stream_ << "\n#include <";
        chilon::print_join(stream_, '/',
            grammar_get.module().first, grammar_get.grammar().first);
        stream_ << ".hpp>\n";
        parent_grammar_ = &grammar_get.grammar();

        if (grammar::Status::PROCESSING == parent_grammar_->second.status_)
            throw error::dep_cycle(parent_grammar_->first);
        else if (grammar::Status::PROCESSED != parent_grammar_->second.status_) {
            // todo: build grammar
        }
    }
    else {
        stream_ << "\n#include <chilon/parser.hpp>\n";
    }
}

void build_grammar::operator()(rule_type& rule) {
    typedef grammar::NyuRule::Status RuleStatus;
    if (RuleStatus::UNKNOWN == rule.second.status_) {
        build_rule rule_builder(*this);
        rule_builder(rule);
    }
}

} }
