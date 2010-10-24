#ifndef NYU_CPP_GET_TYPE_AND_VALUE_HPP
#define NYU_CPP_GET_TYPE_AND_VALUE_HPP

#include <nyu/cpp/build_class.hpp>

#include <chilon/iterator_range.hpp>

#include <sstream>
#include <vector>

namespace nyu { namespace cpp {

class build_class;

class get_type_and_value {
    typedef std::vector<chilon::range>  scope_type;
    typedef output_file::enum_type      enum_type;

    std::stringstream  type_;
    std::stringstream  value_;
    scope_type  const& scope_;

  public:
    get_type_and_value(scope_type const& scope) : scope_(scope) {}

    std::string type() { return type_.str(); }
    std::string value() { return value_.str(); }

    void operator()(build_class& builder);

    template <class T>
    void operator()(T& t) {
        // todo: throw error
        // std::cerr << "bad lookup" << std::endl;
    }

    void operator()(enum_type& enm);
};

} }
#endif
