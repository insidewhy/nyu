#ifndef NYU_CPP_COMPILATION_UNIT_HPP
#define NYU_CPP_COMPILATION_UNIT_HPP

#include <nyu/cpp/output_file.hpp>

#include <chilon/iterator_range.hpp>
#include <chilon/variant_vector_hash_map.hpp>
#include <chilon/hash.hpp>

#include <vector>

namespace nyu {

namespace grammar {
    namespace nyah {
        class Class;
        class Enum;
    }
    namespace meta { class Module; }
}

namespace cpp {

class search_ast;

class compilation_unit : public output_file {
    friend class search_ast;

    typedef std::vector<chilon::range> scope_type;

    typedef chilon::variant_vector_hash_map<
        chilon::variant<
            chilon::key_value<scope_type, grammar::nyah::Class *>,
            chilon::key_value<scope_type, grammar::meta::Module *> >,
        chilon::hasher>                                   map_t;

    map_t  type_ref_map_;

  protected:
    builder&       get_builder()       { return builder_; }
    builder const& get_builder() const { return builder_; }

    module_type& module_;

    void build_grammar_scope(grammar_type& grmmr, module_type& module);

  public:
    template <class T>
    void add_type_ref(T& dep) {
        builder_(dep);
        type_ref_map_.insert(
            chilon::key_value<scope_type, decltype(dep.second) *>(
                dep.first, &dep.second));
    }

    void close();

    compilation_unit(builder& builder, decltype(module_)& module)
      : output_file(builder), module_(module) {}
};

} }
#endif