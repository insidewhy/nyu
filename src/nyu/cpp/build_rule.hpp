#ifndef NYU_CPP_BUILD_RULE_HPP
#define NYU_CPP_BUILD_RULE_HPP

#include <nyu/cpp/build_grammar.hpp>

namespace nyu { namespace cpp {

class build_rule {
    class first_node_expr;

    typedef build_grammar::rule_type rule_type;
    typedef grammar::NyuRule::Status RuleStatus;

    typedef nyu::grammar::nyu::Sequence        Sequence;
    typedef nyu::grammar::nyu::Join            Join;
    typedef nyu::grammar::nyu::Prefix          Prefix;
    typedef nyu::grammar::nyu::Suffix          Suffix;
    typedef nyu::grammar::nyu::OrderedChoice   OrderedChoice;
    typedef nyu::grammar::nyu::String          String;
    typedef nyu::grammar::nyu::CharacterRange  CharacterRange;
    typedef nyu::grammar::nyu::Expression      Expression;
    typedef nyu::grammar::nyu::Joined          Joined;

    build_grammar&     grammar_builder_;
    int                indent_;
    std::stringstream  stream_;

  public:
    build_rule(decltype(grammar_builder_)& grammar_builder)
      : grammar_builder_(grammar_builder), indent_(0) {}

    void operator()(rule_type& rule);

    void operator()(Sequence& sub);
    void operator()(Join& sub);
    void operator()(Prefix& sub);
    void operator()(Suffix& sub);
    void operator()(OrderedChoice& sub);
    void operator()(String& sub);
    void operator()(CharacterRange& sub);
    void operator()(chilon::range& sub);
    void operator()(std::vector<chilon::range>& sub);
    void operator()(char const sub);
    void operator()(Expression& sub);
    void operator()(Joined& sub);
};

} }
#endif
