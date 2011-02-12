#ifndef NYU_CPP_GET_TYPE_AND_VALUE_HPP
#define NYU_CPP_GET_TYPE_AND_VALUE_HPP

#include <chilon/iterator_range.hpp>

#include <nyu/cpp/output_file.hpp>
#include <nyu/cpp/search_ast.hpp>

#include <sstream>
#include <vector>

namespace nyu { namespace cpp {

class scope_ref_cache;

// splits something like namespace_.class_.colors_enum_.RED
// into namespace_.class_.colors_enum_ and RED
class get_type_and_value : public search_ast {
    struct module_dep;

    typedef chilon::iterator_range<scope_type::const_iterator>  scope_range;
    typedef output_file::enum_type                              enum_type;
    typedef output_file::class_type                             class_type;

    std::stringstream  type_;
    std::stringstream  value_;
    scope_range        search_;

  public:
    get_type_and_value(scope_type const& search)
      : search_(search.begin(), search.end()) {}

    std::string type() { return type_.str(); }
    std::string value() { return value_.str(); }

    void operator()(class_type& clss, scope_ref_cache& scope);

    template <class T>
    void operator()(T& t) {
        // todo: throw error
    }

    void operator()(enum_type& enm);
};

} }
#endif
