#ifndef NYU_CPP_BUILD_RULE_HPP
#define NYU_CPP_BUILD_RULE_HPP

#include <nyu/cpp/build_grammar.hpp>

namespace nyu { namespace cpp {

class build_rule {
    class first_node_expr;

    typedef build_grammar::rule_type rule_type;
    typedef grammar::NyuRule::Status RuleStatus;

    build_grammar&     grammar_builder_;
    int                indent_;
    std::stringstream  stream_;

  public:
    build_rule(decltype(grammar_builder_)& grammar_builder)
      : grammar_builder_(grammar_builder), indent_(0) {}

    void operator()(rule_type& rule);
};

} }
#endif
