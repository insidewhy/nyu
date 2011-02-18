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

                // TODO: child nodes
                rule_builder_.print_indent();
                rule_builder_.stream_ << "TODO";
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
    //            tree_optional

    first_node_expr(decltype(rule_builder_)& rule_builder,
                    decltype(rule_)&         rule)
      : rule_builder_(rule_builder), rule_(rule) {}
};

void build_rule::operator()(rule_type& rule) {
    // todo: handle parent rule

    if ('=' == std::get<1>(rule.second.value_)) {
        stream_ << "struct " << rule.first << " : simple_node<\n";
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
    print_indent(); stream_ << "TODO";
    end_subparser();
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
        else throw
            error::file_location("join type not allowed at this scope", op_str);
    }

    print_indent(); stream_ << "TODO";
    end_subparser();
}

void build_rule::operator()(Prefix& sub) {
    subparser("unknown_prefix");
    print_indent(); stream_ << "TODO";
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
        subparser("unknown_suffix");
    }

    chilon::variant_apply(std::get<0>(sub.value_), *this);
    end_subparser();
}

void build_rule::operator()(OrderedChoice& sub) {
    subparser("unknown_choice");
    nested_parser(sub.value_);
}

void build_rule::operator()(String& sub) {
    subparser("char_");
    print_indent(); stream_ << "TODO";
    end_subparser();
}

void build_rule::operator()(CharacterRange& sub) {
    subparser("char_range");
    print_indent(); stream_ << "TODO";
    end_subparser();
}

void build_rule::operator()(chilon::range& sub) {
    print_indent();
    stream_ << "TODO_escape_sequence";
}

void build_rule::operator()(std::vector<chilon::range>& sub) {
    print_indent();
    stream_ << "TODO_rule";
}

void build_rule::operator()(char const sub) {
    print_indent();
    stream_ << grammar_builder_.namespace_alias() << "::"
            << "char_<\'" << sub << '\'' << ">";
}

void build_rule::operator()(Expression& sub) {
    chilon::variant_apply(sub.value_, *this);
}

void build_rule::operator()(Joined& sub) {
    subparser("lexeme");
    nested_parser(sub.value_);
}

void build_rule::subparser(char const * const name) {
    print_indent();
    stream_ << grammar_builder_.namespace_alias() << "::" << name << "<\n";
    ++indent_;
}

void build_rule::end_subparser() {
    --indent_;
    print_indent_on_nl();
    stream_ << '>';
}

template <class T>
void build_rule::nested_parser(T& sub) {
    auto it = sub.begin();
    chilon::variant_apply(*it, *this);
    for (++it; it != sub.end(); ++it) {
        stream_ << ",\n";
        chilon::variant_apply(*it, *this);
    }
    end_subparser();
}

} }
