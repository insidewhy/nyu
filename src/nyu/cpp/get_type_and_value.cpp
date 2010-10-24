#include <nyu/cpp/get_type_and_value.hpp>
#include <nyu/cpp/build_class.hpp>

namespace nyu { namespace cpp {

void get_type_and_value::operator()(build_class& builder) {
    auto& class_scope = builder.get_class().second.value_;
    auto it = class_scope.find(scope_.front());
    if (it == class_scope.end()) {
        // search in preceding namespaces
    }
    else {
        // chilon::variant_apply(*it, build_assigned_attr());
    }
}

void get_type_and_value::operator()(enum_type& enm) {
    type_ << enm.first;
}

} }
