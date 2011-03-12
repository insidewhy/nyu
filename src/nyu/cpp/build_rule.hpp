#ifndef NYU_CPP_BUILD_RULE_HPP
#define NYU_CPP_BUILD_RULE_HPP

#include <nyu/cpp/build_grammar.hpp>

// todo: make this configurable
#define NYU_INDENT_STRING "    ";

namespace nyu { namespace cpp {

class build_rule {
    class build_tree_node;
    class first_node_expr;

    typedef build_grammar::rule_type      rule_type;

    typedef grammar::NyuRule::Status      RuleStatus;
    typedef grammar::nyu::Sequence        Sequence;
    typedef grammar::nyu::Join            Join;
    typedef grammar::nyu::Prefix          Prefix;
    typedef grammar::nyu::Suffix          Suffix;
    typedef grammar::nyu::OrderedChoice   OrderedChoice;
    typedef grammar::nyu::String          String;
    typedef grammar::nyu::CharacterRange  CharacterRange;
    typedef grammar::nyu::Expression      Expression;
    typedef grammar::nyu::Joined          Joined;

    build_grammar&     grammar_builder_;
    int                indent_;
    std::stringstream  stream_;

    void print_indent() {
        for (int i = 0; i < indent_; ++i) stream_ << NYU_INDENT_STRING;
    }

    void print_indent_on_nl() {
        stream_ << '\n';
        print_indent();
    }

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
    void operator()(std::tuple<char, char> const& char_range);

    void begin_node_rule(rule_type& rule);
    void end_node_rule();

  private:
    class char_range_element;

    // a small subparser that will be on a single line
    inline void line_subparser(char const * const name);
    inline void subparser(char const * const name);
    inline void end_subparser();

    template <class T>
    inline void nested_parser(T& sub);
};

} }
#endif
