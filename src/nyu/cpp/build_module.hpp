#ifndef NYU_CPP_BUILD_MODULE_HPP
#define NYU_CPP_BUILD_MODULE_HPP

#include <nyu/cpp/builder.hpp>
#include <nyu/cpp/compilation_unit.hpp>

namespace nyu { namespace cpp {

struct build_module : compilation_unit {

    build_module(builder& builder, module_type& module)
      : compilation_unit(builder, module) {}

    template <class T>
    void subnamespace(T& t) {}

    template <class T>
    void operator()(T& t) {}

    // classes and grammars create a new namespace dependency
    void subnamespace(class_type& clss);

    void subnamespace(grammar_type& gram) {
        build_grammar_scope(gram, module_);
    }

    // enumerations are stored within the grammar namespace
    void operator()(enum_type& enm) {
        if (! is_open()) open();
        output_file::operator()(enm);
    }

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

