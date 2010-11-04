#include <nyu/cpp/build_grammar.hpp>
#include <nyu/cpp/build_rule.hpp>

namespace nyu { namespace cpp {

void build_grammar::close() {
    scope_ref_cache::close();

    if (! module_.first.empty())
        open_namespace(module_.first, grammar_.first);
    else
        stream_ << "namespace " << grammar_.first << '\n';

    stream_ << body_.str();
    close_namespace(module_.first.size() + 1);
    chilon::print(stream_, "\n#endif\n");
    stream_.close();
}

void build_grammar::open() {
    output_file::open(module_.first, grammar_.first);
}

void build_grammar::operator()(rule_type& rule) {
    typedef grammar::NyuRule::Status RuleStatus;
    if (RuleStatus::UNKNOWN == rule.second.status_) {
        build_rule rule_builder(*this);
        rule_builder(rule);
    }
}

} }
