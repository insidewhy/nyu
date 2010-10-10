#ifndef NYU_CPP_MODULE_HPP
#define NYU_CPP_MODULE_HPP

#include <nyu/cpp/builder.hpp>

#include <chilon/getset.hpp>

#include <fstream>

namespace nyu { namespace cpp {

class module {
    typedef builder::module_type         module_type;
    typedef builder::grammar_identifier  grammar_identifier;

    builder&                builder_;
    module_type const&      module_;
    mutable std::ofstream   stream_;

  public:
    CHILON_GET_REF(stream)

    module(module const& rhs) = delete;

    module(builder&           builder,
           module_type const& module);

    void operator()(chilon::key_value<chilon::range,
                                      grammar::nyah::Class,
                                      chilon::key_unique> const& clas) const;

    void operator()(chilon::key_value<chilon::range,
                                      grammar::meta::NyuGrammar,
                                      chilon::key_unique> const& gram) const;

    void close();
};

} }
#endif

