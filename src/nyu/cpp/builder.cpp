#include <nyu/cpp/builder.hpp>
#include <nyu/cpp/module.hpp>
#include <nyu/error/not_found.hpp>

#include <cstring>
#include <stdexcept>

namespace nyu { namespace cpp {

void builder::generate_code() {
    for (auto it = chilon::make_safe_iterator(std::get<0>(ast_));
         ! it.at_end(); ++it)
    {
        std::string depFile = options_.include(*it);
        parse_file(depFile);
    }

    for (auto it = std::get<1>(ast_).safe_ordered_begin(); ! it.at_end(); ++it) {
        (*this)(*it);
    }
}

bool builder::parse_file(std::string const& file_path) {
    auto& file = add_file(file_path);

    if (file.parse_succeeded()) return false;

    options_.verbose(file_path, ": parsing");

    if (file.parse(file_path.c_str(), ast_)) {
        if (! file.parse_succeeded())
            throw error::parsing(file_path);
        else
            options_.verbose(file_path, ": parsed");
    }
    else throw error::parsing("nothing parsed", file_path);

    return true;
}

void builder::operator()(module_type const& module) {
    // auto& moduleId = module.first;
    auto& grammar = module.second.value_;

    cpp::module module_builder(*this, module);
    for (auto it = grammar.safe_ordered_begin(); ! it.at_end(); ++it)
        chilon::variant_apply(*it, module_builder);

    module_builder.close();
}

void builder::grammar_dep(module_type const& module, grammar_identifier const& id) {
    // auto& grammar = module.second.value_;
    // TODO: search for grammar in current module, then all parent modules
}

void builder::print_ast() const {
    chilon::println("include ", std::get<0>(ast_));
    for (auto it = std::get<1>(ast_).begin();
         it != std::get<1>(ast_).end(); ++it)
    {
        chilon::println("module id ", it->first);
        chilon::println("module ", it->second.value_);
    }
}

} }
