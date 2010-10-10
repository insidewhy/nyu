#include <nyu/cpp/module.hpp>

namespace nyu { namespace cpp {

module::module(builder&           builder,
               module_type const& module)
  : builder_(builder), module_(module)
{
    if (module.first.empty())
        builder_.opts().output_path(stream_, "global.hpp");
    else {
        builder_.opts().output_path(
            stream_, module.first.at< std::vector<chilon::range> >(), ".hpp");
    }
}

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

void module::close() {
    // TODO:
}

} }
