#ifndef NYU_CPP_MODULE_HPP
#define NYU_CPP_MODULE_HPP

#include <nyu/cpp/builder.hpp>

namespace nyu { namespace cpp {

class module {
    typedef builder::module_type         module_type;
    typedef builder::grammar_identifier  grammar_identifier;

    builder&            builder_;
    module_type const&  module_;

  public:
    module(builder&           builder,
           module_type const& module) : builder_(builder), module_(module) {}

    void operator()(chilon::key_value<chilon::range,
                                      grammar::nyah::Class,
                                      chilon::key_unique> const& clas) const;

    void operator()(chilon::key_value<chilon::range,
                                      grammar::meta::NyuGrammar,
                                      chilon::key_unique> const& gram) const;
};

} }
#endif

