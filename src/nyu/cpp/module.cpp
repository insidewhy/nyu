#include <nyu/cpp/module.hpp>

namespace nyu { namespace cpp {

module::module(builder&           builder,
               module_type const& module)
  : builder_(builder), module_(module)
{
    std::stringstream guard;
    std::stringstream nmspace;

    if (module.first.empty()) {
        builder_.opts().output_path(stream_, "global.hpp");
        guard << "GLOBAL";
    }
    else {
        auto const& module_id = module.first.at<0>();
        builder_.opts().output_path(stream_, module_id, ".hpp");

        nmspace << "namespace " << module_id.front() << " {";
        guard << module_id.front();
        for (auto it = module_id.begin() + 1; it != module_id.end(); ++it) {
            nmspace << " namespace " << *it << " {";
            guard << "_" << *it;
        }
        nmspace << '\n';
    }

    chilon::print(stream_, "#ifndef ", guard.str(), "_HPP\n");
    chilon::print(stream_, "#define ", guard.str(), "_HPP\n");
    chilon::print(stream_, nmspace.str());
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
    stream_ << body_.str() << '\n';

    if (! module_.first.empty()) {
        auto const& module_id = module_.first.at<0>();
        stream_ << '}';
        for (auto i = 1u; i < module_id.size(); ++i) {
            stream_ << " }";
        }
        stream_ << '\n';
    }

    chilon::print(stream_, "#endif");
    stream_ << std::flush;
}

} }
