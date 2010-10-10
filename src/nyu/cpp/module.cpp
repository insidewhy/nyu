#include <nyu/cpp/module.hpp>

namespace nyu { namespace cpp {


void module::operator()(chilon::key_value<
    chilon::range, grammar::nyah::Class, chilon::key_unique> const& clas) const
{
}

void module::operator()(chilon::key_value<
    chilon::range, grammar::meta::NyuGrammar, chilon::key_unique> const& gram) const
{
    auto extends = std::get<0>(gram.second.value_);
    if (! extends.empty())
        builder_.grammar_dep(module_, extends.at<grammar_identifier>());
}

} }
