#ifndef NYU_CPP_BUILD_RULE_HPP
#define NYU_CPP_BUILD_RULE_HPP

#include <nyu/cpp/build_grammar.hpp>

namespace nyu { namespace cpp {

class build_rule {
    typedef build_grammar::rule_type rule_type;

    build_grammar& grammar_builder_;

  public:
    build_rule(decltype(grammar_builder_)& grammar_builder)
      : grammar_builder_(grammar_builder) {}

    void operator()(rule_type& rule);
};

} }
#endif
