#include <nyu/cpp/get_type_and_value.hpp>
#include <nyu/cpp/build_class.hpp>

#include <nyu/error/file_location.hpp>

namespace nyu { namespace cpp {

void get_type_and_value::operator()(build_class& builder) {
    auto& class_scope = builder.get_class().second.value_;

    // search within current class
    auto it = class_scope.find(scope_.front());
    if (it != class_scope.end()) {
        chilon::variant_apply(*it, *this);
        return;
    }

    // todo: search in cached includes

    // search for in module of class
    auto search_it = builder.module_.second.value_.find(scope_.front());
    if (search_it != builder.module_.second.value_.end()) {
        builder.new_dep(builder.module_);
        chilon::variant_apply(*search_it, *this);
        return;
    }

    // todo: search for submodule

    // todo: search in ancestors of class module
}

void get_type_and_value::operator()(enum_type& enm) {
    scope_.advance();
    if (1 == scope_.size()) {
        if (! enm.second.value_.count(scope_.front()))
            throw error::file_location("value not found in enumeration",
                                       scope_.front());

        type_ << enm.first;
        value_ << enm.first << "::" << scope_.front();
    }
    else if (0 == scope_.size())
        throw error::file_location("cannot use enum type as value",
                            chilon::range(scope_.front().begin(),
                                          (scope_.end() - 1)->end()));
    else
        throw error::file_location("bad enum value",
                            chilon::range(scope_.front().begin(),
                                          (scope_.end() - 1)->end()));
}

} }
