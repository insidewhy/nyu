#include <nyu/cpp/get_type_and_value.hpp>
#include <nyu/cpp/build_class.hpp>

namespace nyu { namespace cpp {

void get_type_and_value::operator()(build_class& builder) {
    auto& class_scope = builder.get_class().second.value_;
    auto it = class_scope.find(scope_.front());
    if (it == class_scope.end()) {
        // todo: search in preceding namespaces
    }
    else {
        chilon::variant_apply(*it, *this);
    }
}

void get_type_and_value::operator()(enum_type& enm) {
    scope_.advance();
    if (1 == scope_.size()) {
        type_ << enm.first;
        value_ << enm.first << "::" << scope_.front();
    }
    else if (0 == scope_.size()) {
        // throw can't get value from enm
    }
    else {
        // crap after enum
    }
}

} }
