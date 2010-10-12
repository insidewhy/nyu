#ifndef NYU_CPP_MODULE_HPP
#define NYU_CPP_MODULE_HPP

#include <nyu/cpp/builder.hpp>

#include <chilon/getset.hpp>

#include <fstream>
#include <sstream>

namespace nyu { namespace cpp {

class module {
    typedef builder::module_type  module_type;

    builder&                      builder_;
    module_type const&            module_;
    mutable std::ofstream         stream_;
    mutable std::stringstream     body_;

    typedef chilon::range         range;

  public:
    CHILON_GET_REF(stream)

    module(module const& rhs) = delete;

    module(builder&           builder,
           module_type const& module);

    void operator()(chilon::key_value<range,
                                      grammar::nyah::Class,
                                      chilon::key_unique>& clas) const;

    void operator()(chilon::key_value<range,
                                      grammar::meta::NyuGrammar,
                                      chilon::key_unique>& gram) const;

    void operator()(chilon::key_value<range,
                                      grammar::nyah::Enum,
                                      chilon::key_unique>& gram) const;

    void close();
};

} }
#endif

