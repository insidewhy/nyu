#include <nyu/cpp/module.hpp>
#include <nyu/error/grammar_dep_cycle.hpp>

#include <chilon/print_join.hpp>

namespace nyu { namespace cpp {

module::module(builder&           builder,
               module_type const& module)
  : builder_(builder), module_(module)
{
    std::stringstream guard;

    if (module.first.empty()) {
        builder_.opts().output_path(stream_, "global.hpp");
        guard << "GLOBAL";
    }
    else {
        auto const& module_id = module.first.at<0>();
        builder_.opts().output_path(stream_, module_id, ".hpp");
        chilon::print_join(guard, '_', module_id);
    }

    chilon::print(stream_, "#ifndef ", guard.str(), "_HPP\n");
    chilon::print(stream_, "#define ", guard.str(), "_HPP\n\n");
}

void module::operator()(chilon::key_value<
    chilon::range, grammar::nyah::Class, chilon::key_unique>& clas) const
{
}

void module::operator()(chilon::key_value<
    chilon::range, grammar::meta::NyuGrammar, chilon::key_unique>& gram) const
{
    if (gram.second.status_ == grammar::Status::PROCESSED) return;
    else if (gram.second.status_ == grammar::Status::PROCESSING)
        throw error::grammar_dep_cycle(gram.first);

    try {
        auto extends = std::get<0>(gram.second.value_);
        if (! extends.empty()) {
            gram.second.status_ = grammar::Status::PROCESSING;
            builder_.grammar_dep(module_, extends.at<grammar_id>());
        }
    }
    catch (error::grammar_dep_cycle& err) {
        err.grammars_.push_back(gram.first);
        throw err;
    }

    // TODO: process grammar

    gram.second.status_ = grammar::Status::PROCESSED;
}

void module::operator()(chilon::key_value<
    chilon::range, grammar::nyah::Enum, chilon::key_unique>& gram) const
{
    // TODO: process enum
}

void module::close() {
    if (! module_.first.empty()) {
        auto const& module_id = module_.first.at<0>();

        stream_ << "namespace " << module_id.front() << " {";
        for (auto it = module_id.begin() + 1; it != module_id.end(); ++it) {
            stream_ << " namespace " << *it << " {";
        }
        stream_ << '\n';

        stream_ << body_.str() << '\n';

        stream_ << '}';
        for (auto i = 1u; i < module_id.size(); ++i) {
            stream_ << " }";
        }
        stream_ << '\n';
    }
    else stream_ << body_.str() << '\n';

    chilon::print(stream_, "#endif");
    stream_ << std::flush;
}

} }
