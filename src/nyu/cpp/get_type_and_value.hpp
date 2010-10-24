#ifndef NYU_CPP_GET_TYPE_AND_VALUE_HPP
#define NYU_CPP_GET_TYPE_AND_VALUE_HPP

#include <nyu/cpp/build_class.hpp>

#include <chilon/iterator_range.hpp>

#include <sstream>
#include <vector>

namespace nyu { namespace cpp {

class build_class;

class get_type_and_value {
    typedef std::vector<chilon::range>                          scope_type;
    typedef chilon::iterator_range<scope_type::const_iterator>  scope_range;
    typedef output_file::enum_type                              enum_type;

    std::stringstream  type_;
    std::stringstream  value_;
    scope_range        scope_;

  public:
    get_type_and_value(scope_type const& scope)
      : scope_(scope.begin(), scope.end()) {}

    std::string type() { return type_.str(); }
    std::string value() { return value_.str(); }

    void operator()(build_class& builder);

    template <class T>
    void operator()(T& t) {
        // todo: throw error
    }

    void operator()(enum_type& enm);
};

} }
#endif
