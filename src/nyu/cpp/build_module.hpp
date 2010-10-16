#ifndef NYU_CPP_BUILD_MODULE_HPP
#define NYU_CPP_BUILD_MODULE_HPP

#include <nyu/cpp/builder.hpp>
#include <nyu/cpp/output_file.hpp>

namespace nyu { namespace cpp {

class build_module : public output_file {
    module_type const&   module_;

    typedef chilon::key_value<
        range, grammar::meta::NyuGrammar, chilon::key_unique> grammar_type;

  public:
    build_module(builder&           builder,
                 module_type const& module)
      : output_file(builder), module_(module) {}

    template <class T>
    void subnamespace(T& t) {}

    template <class T>
    void operator()(T& t) {}

    // classes and grammars create a new namespace dependency
    void subnamespace(class_type& clss);
    void subnamespace(grammar_type& gram);

    // enumerations are stored within the grammar namespace
    void operator()(enum_type& enm);
    void grammar_dep(ns_type const& id);
    void close();

  private:
    void open() {
        output_file::open(module_.first);
    }
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

