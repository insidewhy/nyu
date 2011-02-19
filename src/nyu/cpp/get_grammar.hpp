#ifndef NYU_CPP_GET_GRAMMAR_HPP
#define NYU_CPP_GET_GRAMMAR_HPP

#include <chilon/iterator_range.hpp>

#include <nyu/cpp/output_file.hpp>
#include <nyu/cpp/search_ast.hpp>

#include <sstream>
#include <vector>

namespace nyu { namespace cpp {

class compilation_unit;

class get_grammar : public search_ast {
    struct leaf_dep;

    typedef output_file::grammar_type                           grammar_type;
    typedef chilon::iterator_range<scope_type::const_iterator>  scope_range;

    // target grammar
    output_file::grammar_type    *grammar_;
    // module grammar was found in
    output_file::module_type     *module_;
    // contains portion of scope currently being searched..
    scope_range                   search_;

  public:
    get_grammar(scope_type const& search)
      : search_(search.begin(), search.end()) {}

    void operator()(compilation_unit& scope);

    grammar_type&  grammar()      { return *grammar_; }
    module_type&   module() const { return *module_; }
};

} }
#endif
