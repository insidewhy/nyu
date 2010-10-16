#ifndef NYU_CPP_MODULE_HPP
#define NYU_CPP_MODULE_HPP

#include <nyu/cpp/builder.hpp>
#include <nyu/cpp/output_file.hpp>

#include <sstream>

namespace nyu { namespace cpp {

class build_module : public output_file {
    typedef builder::module_type  module_type;
    typedef builder::ns_type      ns_type;

    module_type const&            module_;
    mutable std::stringstream     body_;

    typedef chilon::range         range;

    typedef chilon::key_value<
        range, grammar::meta::NyuGrammar, chilon::key_unique> grammar_type;

    typedef chilon::key_value<
        range, grammar::nyah::Class, chilon::key_unique>      class_type;

    typedef chilon::key_value<
        range, grammar::nyah::Enum, chilon::key_unique>       enum_type;

  public:
    build_module(builder&           builder,
                 module_type const& module)
      : output_file(builder), module_(module) {}

    template <class T>
    void subnamespace(T& t) {}

    template <class T>
    void operator()(T& t) {}

    // classes and grammars create a new namespace dependency
    void subnamespace(class_type& clas);
    void subnamespace(grammar_type& gram);

    // enumerations are stored within the grammar namespace
    void operator()(enum_type& enm);
    void grammar_dep(ns_type const& id);
    void close();

  private:
    void open();
};

class namespace_builder {
    build_module& mod_;
  public:
    namespace_builder(decltype(mod_)& mod) : mod_(mod) {};

    template <class T>
    void operator()(T&& t) const {
        mod_.subnamespace(t);
    }
};

} }
#endif

