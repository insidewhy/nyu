#include <nyu/cpp/build_rule.hpp>
#include <nyu/error/file_location.hpp>

namespace nyu { namespace cpp {

class build_rule::first_node_expr {
    build_rule&  rule_builder_;
    rule_type&   rule_;

  public:
    template <class T>
    void operator()(T& sub) {
        rule_.second.status_ = RuleStatus::NODE;
        rule_builder_(sub);
        rule_.second.status_ = RuleStatus::PROCESSED;
    }

    void operator()(Join& sub) {
        auto& op = std::get<1>(sub.value_);
        if (op.is<chilon::range>()) {
            auto& op_str = op.at<chilon::range>();
            if (op_str.front() == '|') {
                rule_.second.status_ = RuleStatus::NORMAL;
                if (op_str == "|%") {
                    rule_builder_.subparser("tree_joined");
                }
                else {
                    rule_builder_.subparser("tree_joined_lexeme");
                }

                chilon::variant_apply(std::get<2>(sub.value_), rule_builder_);
                rule_builder_.stream_ << ",\n";
                chilon::variant_apply(std::get<0>(sub.value_), rule_builder_);
                rule_builder_.end_subparser();
            };
        }
        else {
            rule_.second.status_ = RuleStatus::NODE;
            rule_builder_(sub);
        }

        rule_.second.status_ = RuleStatus::PROCESSED;
    }

    // mega TODO: specialise operator() on sequence also to look for
    //            |?
    // mega TODO: specialise operator() on suffix also to look for
    //            |+

    first_node_expr(decltype(rule_builder_)& rule_builder,
                    decltype(rule_)&         rule)
      : rule_builder_(rule_builder), rule_(rule) {}
};

void build_rule::operator()(rule_type& rule) {
    // todo: handle parent rule

    if ('=' == std::get<1>(rule.second.value_)) {
        stream_ << "struct " << rule.first << " : "
                << grammar_builder_.namespace_alias() << "::simple_node<\n";
        ++indent_;
        print_indent();
        stream_ << rule.first << ",\n";

        // todo: delay until after parent rule has finished if node rule
        chilon::variant_apply(
            std::get<2>(rule.second.value_).value_, first_node_expr(*this, rule));

        grammar_builder_.body_ << '\n' << stream_.str();
        grammar_builder_.body_ << "\n> {};\n";
        return;
    }

    rule.second.status_ = RuleStatus::NORMAL;
    stream_ << "typedef ";

    chilon::variant_apply(std::get<2>(rule.second.value_).value_, *this);

    grammar_builder_.body_ << '\n' << stream_.str();
    grammar_builder_.body_ << ' ' << rule.first << ";\n";
    rule.second.status_ = RuleStatus::PROCESSED;
}

void build_rule::operator()(Sequence& sub) {
    subparser("sequence");
    nested_parser(sub.value_);
}

void build_rule::operator()(Join& sub) {
    auto& op = std::get<1>(sub.value_);
    if (op.is<char>()) {
        subparser("joined");
    }
    else {
        auto& op_str = op.at<chilon::range>();
        if (op_str == "%+") {
            subparser("joined_plus");
        }
        else if (op_str == "^%") {
            subparser("joined_lexeme");
        }
        else throw error::file_location(
            "join type not allowed at this scope", op_str);
    }

    chilon::variant_apply(std::get<2>(sub.value_), *this);
    stream_ << ",\n";
    chilon::variant_apply(std::get<0>(sub.value_), *this);
    end_subparser();
}

void build_rule::operator()(Prefix& sub) {
    auto& prefix = std::get<0>(sub.value_);
    if (prefix.is<char>()) {
        switch (prefix.at<char>()) {
            case '&':
                subparser("try_");
                break;
            case '!':
                subparser("tbpeg_not");
                break;
            case '#':
                subparser("key");
                break;
        }
    }
    else {
        auto& prefix_str = prefix.at<chilon::range>();
        subparser(prefix_str == "&!" ? "not_" : "key_plus");
    }

    chilon::variant_apply(std::get<1>(sub.value_), *this);
    end_subparser();
}

void build_rule::operator()(Suffix& sub) {
    auto& suffix = std::get<1>(sub.value_);
    if (suffix.is<char>()) {
        switch (suffix.at<char>()) {
            case '+':
                subparser("many_plus");
                break;
            case '*':
                subparser("many");
                break;
            case '?':
                subparser("optional");
                break;
        }
    }
    else {
        auto& suffix_str = suffix.at<chilon::range>();
        if (suffix_str == "^+")
            subparser("many_plus_range");
        else if (suffix_str == "^*")
            subparser("many_plus");
        // TODO: replace last else with this
        // else throw error::file_location(
        //     "many type not allowed at this scope", suffix_str);
        else {
            std::string tmp = "TODO_suffix_";
            tmp.append(suffix_str);
            subparser(tmp.c_str());
        }
    }

    chilon::variant_apply(std::get<0>(sub.value_), *this);
    end_subparser();
}

void build_rule::operator()(OrderedChoice& sub) {
    subparser("choice");
    nested_parser(sub.value_);
}

namespace {
    template <class S>
    inline void print_char(S& stream, char const c) {
        stream << '\'';
        if ('\'' == c || '\\' == c) stream << '\\';
        stream << c << '\'';
    }
}

void build_rule::operator()(String& sub) {
    line_subparser("char_");
    auto it = sub.value_.begin();
    print_char(stream_, *it);
    for (++it; it != sub.value_.end(); ++it) {
        stream_ << ", ";
        print_char(stream_, *it);
    }

    stream_ << '>';
}

void build_rule::operator()(CharacterRange& sub) {
    auto it = sub.value_.begin();

    if (it->is<std::tuple<char, char>>()) {
        for (++it; it != sub.value_.end(); ++it) {
            if (! it->is<std::tuple<char, char>>()) break;
        }

        if (it == sub.value_.end()) {
            line_subparser("char_range");

            it = sub.value_.begin();
            auto& tup = it->at<std::tuple<char, char>>();
            print_char(stream_, std::get<0>(tup));
            stream_ << ',';
            print_char(stream_, std::get<1>(tup));

            for (++it; it != sub.value_.end(); ++it) {
                stream_ << ", ";

                auto& tup = it->at<std::tuple<char, char>>();
                print_char(stream_, std::get<0>(tup));
                stream_ << ',';
                print_char(stream_, std::get<1>(tup));
            }

            stream_ << '>';
            return;
        }
    }
    else if (it->is<char>()) {
        for (++it; it != sub.value_.end(); ++it) {
            if (! it->is<char>()) break;
        }

        if (it == sub.value_.end()) {
            line_subparser("char_from");
            it = sub.value_.begin();
            print_char(stream_, it->at<char>());
            for (++it; it != sub.value_.end(); ++it) {
                stream_ << ", ";
                print_char(stream_, it->at<char>());
            }
            stream_ << '>';
            return;
        }
    }

    subparser("choice");
    nested_parser(sub.value_);
}

void build_rule::operator()(chilon::range& sub) {
    print_indent();
    stream_ << grammar_builder_.namespace_alias() << "::";
    switch (sub[1]) {
        case 'S':
            stream_ << "not_";
        case 's':
            stream_ << "char_from<'\\n', '\\t', ' '>";
            break;
        case 'N':
        case 'T':
            stream_ << "not_";
        case 'n':
        case 't':
            stream_ << "char_<'\\" << sub[1] << "'>";
            break;
        default:
            stream_ << "char_<'" << sub[1] << "'>";
            break;
    }
}

void build_rule::operator()(std::vector<chilon::range>& sub) {
    if (1 == sub.size()) {
        print_indent();
        auto& grammar_rules = std::get<1>(grammar_builder_.grammar_.second.value_);
        // look for rule in grammar
        auto it = grammar_rules.find(sub.front());

        // TODO: look in parent grammar if not found here
        if (it == grammar_rules.end())
            throw error::file_location("rule not found", sub.front());

        // TODO: build parent, but delay building node rules until necessary
        // grammar_builder_(*it);

        stream_ << sub.front();
    }
    else if (2 == sub.size()) {
        print_indent();
        stream_ << "TODO_parent_rule";
    }
    else {
        print_indent();
        stream_ << "TODO_qualified_rule";
    }
}

void build_rule::operator()(char const sub) {
    line_subparser("char_");
    print_char(stream_, sub);
    stream_ << '>';
}

void build_rule::operator()(Expression& sub) {
    chilon::variant_apply(sub.value_, *this);
}

void build_rule::operator()(Joined& sub) {
    subparser("lexeme");
    nested_parser(sub.value_);
}

void build_rule::operator()(std::tuple<char, char> const& char_range) {
    line_subparser("char_range");
    print_char(stream_, std::get<0>(char_range));
    stream_ << ',';
    print_char(stream_, std::get<1>(char_range));
    stream_ << '>';
}

inline void build_rule::line_subparser(char const * const name) {
    print_indent();
    stream_ << grammar_builder_.namespace_alias() << "::" << name << '<';
}

inline void build_rule::subparser(char const * const name) {
    print_indent();
    stream_ << grammar_builder_.namespace_alias() << "::" << name << "<\n";
    ++indent_;
}

inline void build_rule::end_subparser() {
    --indent_;
    print_indent_on_nl();
    stream_ << '>';
}

template <class T>
inline void build_rule::nested_parser(T& sub) {
    auto it = sub.begin();
    chilon::variant_apply(*it, *this);
    for (++it; it != sub.end(); ++it) {
        stream_ << ",\n";
        chilon::variant_apply(*it, *this);
    }
    end_subparser();
}

} }
