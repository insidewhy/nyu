#ifndef NYU_CPP_GET_CLASS_HPP
#define NYU_CPP_GET_CLASS_HPP

#include <nyu/cpp/search_ast.hpp>

#include <sstream>
#include <vector>

namespace nyu { namespace cpp {

// looks up a class by name
class get_class : public search_ast {
    class class_dep;

    typedef chilon::iterator_range<scope_type::const_iterator>  scope_range;

    scope_range           search_;
    grammar::nyah::Class *class_;

  public:
    // looks up class with respect to compilation unit
    void operator()(compilation_unit& unit);
    void operator()(class_type& clss) { class_ = &(clss.second); }

    grammar::nyah::Class *clss() { return class_; }

    get_class(scope_type const& search)
      : search_(search.begin(), search.end()), class_(0) {}
};

} }
#endif

