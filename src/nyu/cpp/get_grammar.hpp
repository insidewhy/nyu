#ifndef NYU_CPP_GET_GRAMMAR_HPP
#define NYU_CPP_GET_GRAMMAR_HPP

#include <chilon/iterator_range.hpp>

#include <nyu/cpp/output_file.hpp>
#include <nyu/cpp/search_ast.hpp>

#include <sstream>
#include <vector>

namespace nyu { namespace cpp {

class scope_ref_cache;

class get_grammar : public search_ast {
    struct module_dep;

    typedef output_file::grammar_type                           grammar_type;
    typedef output_file::ns_type                                scope_type;
    typedef output_file::module_type                            module_type;
    typedef chilon::iterator_range<scope_type::const_iterator>  scope_range;

    output_file::grammar_type    *grammar_;
    // contains portion of scope currently being searched..
    scope_range                   search_;

  public:
    get_grammar(scope_type const& search)
      : search_(search.begin(), search.end()) {}

    void operator()(scope_ref_cache& scope);

    grammar_type&      grammar()      { return *grammar_; }
    scope_range const& search() const { return search_; }
};

} }
#endif
