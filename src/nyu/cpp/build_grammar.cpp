#include <nyu/cpp/build_grammar.hpp>
#include <nyu/cpp/build_rule.hpp>
#include <nyu/cpp/get_grammar.hpp>

#include <chilon/print_join.hpp>

namespace nyu { namespace cpp {

void build_grammar::close() {
    compilation_unit::close();

    if (! module_.first.empty())
        open_namespace(module_.first, grammar_.first);
    else
        stream_ << "namespace " << grammar_.first << " {\n";

    stream_ << "\nnamespace " << namespace_alias() << " = chilon::parser;\n";

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

        build_grammar_scope(*parent_grammar_, grammar_get.module());
    }
    else {
        stream_ << "\n#include <chilon/parser.hpp>\n";
    }
}

void build_grammar::operator()(rule_type& rule) {
    typedef grammar::NyuRule::Status RuleStatus;
    switch (rule.second.status_) {
        case RuleStatus::UNKNOWN: {
            build_rule rule_builder(*this);
            rule_builder(rule);
            break;
        }
        case RuleStatus::DECLARED_NODE: {
            build_rule rule_builder(*this);
            rule_builder.begin_node_rule(rule);
            chilon::variant_apply(
                std::get<2>(rule.second.value_).value_, rule_builder);
            rule_builder.end_node_rule();
            rule.second.status_ = RuleStatus::PROCESSED;
            break;
        }
        default: break; // already processed
    }
}

} }
