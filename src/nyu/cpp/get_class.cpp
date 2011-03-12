#include <nyu/cpp/get_class.hpp>
#include <nyu/error/file_location.hpp>

namespace nyu { namespace cpp {

struct get_class::class_dep {
    get_class&               resolver_;
    compilation_unit&        unit_; // dependant
    get_class::module_type&  module_;

    class_dep(decltype(resolver_)& resolver,
              decltype(unit_)&     unit_,
              decltype(module_)&   module)
      : resolver_(resolver), unit_(unit_), module_(module) {}

    template <class T>
    void operator()(T& t) {
        throw error::file_location("expected type", resolver_.search_.front());
    }

    void operator()(class_type& clss) {
        unit_.register_and_build_dep(clss, module_);
        resolver_(clss);
    }
};


void get_class::operator()(compilation_unit& unit) {
    // todo: first look in namespace of current compilation unit
    auto& module_scope = get_module_scope(unit);
    auto search_it = module_scope.find(search_.front());
    if (search_it != module_scope.end()) {
        chilon::variant_apply(*search_it,
            class_dep(*this, unit, get_module(unit)));
        return;
    }

    // todo: then check parent modules

    // todo: throw error
    throw error::file_location("type not found", search_.front());
}

} }
