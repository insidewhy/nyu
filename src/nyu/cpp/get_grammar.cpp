#include <nyu/cpp/get_grammar.hpp>
#include <nyu/cpp/scope_ref_cache.hpp>

#include <nyu/error/file_location.hpp>

namespace nyu { namespace cpp {

struct get_grammar::leaf_dep {
    get_grammar&                  resolver_;
    search_ast::scope_type const& module_;

    leaf_dep(decltype(resolver_)&  resolver,
             decltype(module_)&    module)
      : resolver_(resolver), module_(module) {}

    template <class T>
    void operator()(T& t) {
        throw error::file_location("target was not a grammar",
                                   resolver_.search_.front());
    }

    void operator()(get_grammar::grammar_type& grmmr) {
        resolver_.search_.assign(module_.begin(), module_.end());
        resolver_.grammar_ = &grmmr;
    }
};

void get_grammar::operator()(scope_ref_cache& scope) {
    if (1 == search_.size()) {
        // todo: search in cached includes

        auto& module_scope = get_module_scope(scope);
        auto search_it = module_scope.find(search_.front());
        if (search_it != module_scope.end()) {
            chilon::variant_apply(
                *search_it, leaf_dep(*this, get_module_key(scope)));
            return;
        }

        // todo: search in ancestors of module
    }
    else {
        // todo: search for submodule

    }
}

} }
