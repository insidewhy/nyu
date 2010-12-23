#ifndef NYU_CPP_SEARCH_AST_HPP
#define NYU_CPP_SEARCH_AST_HPP

#include <nyu/cpp/scope_ref_cache.hpp>

#include <chilon/meta/return.hpp>

namespace nyu { namespace cpp {

struct search_ast {
    typedef builder::ast_t                       ast_t;
    typedef builder::module_type                 module_type;
    typedef output_file::ns_type                 scope_type;
    typedef module_type::value_type::value_type  module_scope_type;

  protected:
    ast_t& get_ast(scope_ref_cache& scope) {
        return scope.get_builder().ast_;
    }

    module_type& get_module(scope_ref_cache& scope) {
       return scope.module_;
    }

    scope_type& get_module_key(scope_ref_cache& scope) {
       return scope.module_.first;
    }

    module_scope_type& get_module_scope(scope_ref_cache& scope) {
       return scope.module_.second.value_;
    }
};

} }
#endif
