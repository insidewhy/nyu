#ifndef NYU_CPP_SEARCH_AST_HPP
#define NYU_CPP_SEARCH_AST_HPP

#include <nyu/cpp/compilation_unit.hpp>

#include <chilon/meta/return.hpp>

namespace nyu { namespace cpp {

struct search_ast {
    typedef builder::ast_t                       ast_t;
    typedef builder::module_type                 module_type;
    typedef output_file::ns_type                 scope_type;
    typedef module_type::value_type::value_type  module_scope_type;

  protected:
    ast_t& get_ast(compilation_unit& unit) {
        return unit.get_builder().ast_;
    }

    module_type& get_module(compilation_unit& unit) {
       return unit.module_;
    }

    scope_type& get_module_key(compilation_unit& unit) {
       return unit.module_.first;
    }

    module_scope_type& get_module_scope(compilation_unit& unit) {
       return unit.module_.second.value_;
    }
};

} }
#endif
