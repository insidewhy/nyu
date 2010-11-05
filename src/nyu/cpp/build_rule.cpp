#include <nyu/cpp/build_rule.hpp>

namespace nyu { namespace cpp {

class build_rule::first_node_expr {
    build_rule&  rule_builder_;
    rule_type&   rule_;

  public:
    template <class T>
    void operator()(T& t) {
        rule_.second.status_ = RuleStatus::NODE;
        // todo: pass through to rule_builder_

        rule_builder_.stream_ << "TODO";

        rule_.second.status_ = RuleStatus::PROCESSED;
    }

    // todo: specialise operator() on sequence/tree_joined to
    //       see if it is NODE or NORMAL

    first_node_expr(decltype(rule_builder_)& rule_builder,
                    decltype(rule_)&         rule)
      : rule_builder_(rule_builder), rule_(rule) {}
};

void build_rule::operator()(rule_type& rule) {
    // todo: handle parent rule

    if ('=' == std::get<1>(rule.second.value_)) {
        stream_ << "struct " << rule.first << " : simple_node<"
                << rule.first << ", ";

        // todo: delay until after parent rule has finished if node rule
        chilon::variant_apply(
            std::get<2>(rule.second.value_).value_, first_node_expr(*this, rule));

        grammar_builder_.body_ << '\n' << stream_.str();
        grammar_builder_.body_ << "> {}\n";
        return;
    }

    rule.second.status_ = RuleStatus::NORMAL;
    stream_ << "typedef ";

    // todo: output rule
    stream_ << "TODO";

    grammar_builder_.body_ << '\n' << stream_.str();
    grammar_builder_.body_ << ' ' << rule.first << ";\n";
    rule.second.status_ = RuleStatus::PROCESSED;
}

} }
