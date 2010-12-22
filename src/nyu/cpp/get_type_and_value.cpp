#include <nyu/cpp/get_type_and_value.hpp>
#include <nyu/cpp/scope_ref_cache.hpp>

#include <nyu/error/file_location.hpp>

namespace nyu { namespace cpp {

struct get_type_and_value::module_dep {
    get_type_and_value&               resolver_;
    scope_ref_cache&                  scope_cache_;
    get_type_and_value::module_type&  module_;

    module_dep(decltype(resolver_)&    resolver,
               decltype(scope_cache_)& scope_cache,
               decltype(module_)&      module)
      : resolver_(resolver), scope_cache_(scope_cache), module_(module) {}

    template <class T>
    void operator()(T& t) { resolver_(t); }

    void operator()(enum_type& enm) {
        scope_cache_.add_type_ref(module_);
        resolver_(enm);
    }
};

void get_type_and_value::operator()(class_type& clss, scope_ref_cache& scope) {
    auto& class_scope = clss.second.value_;

    // search within current class
    auto it = class_scope.find(search_.front());
    if (it != class_scope.end()) {
        chilon::variant_apply(*it, *this);
        return;
    }

    // todo: search in cached includes

    // search for in module of class
    auto search_it = scope.module_.second.value_.find(search_.front());
    if (search_it != scope.module_.second.value_.end()) {
        chilon::variant_apply(*search_it,
            module_dep(*this, scope, scope.module_));
        return;
    }

    // todo: search for submodule

    // todo: search in ancestors of class module
}

void get_type_and_value::operator()(enum_type& enm) {
    search_.advance();
    if (1 == search_.size()) {
        if (! enm.second.value_.count(search_.front()))
            throw error::file_location("value not found in enumeration",
                                       search_.front());

        type_ << enm.first;
        value_ << enm.first << "::" << search_.front();
    }
    else if (0 == search_.size())
        throw error::file_location("cannot use enum type as value",
                            chilon::range(search_.front().begin(),
                                          (search_.end() - 1)->end()));
    else
        throw error::file_location("bad enum value",
                            chilon::range(search_.front().begin(),
                                          (search_.end() - 1)->end()));
}

} }
