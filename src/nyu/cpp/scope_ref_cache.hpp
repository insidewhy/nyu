#ifndef NYU_CPP_SCOPE_REF_CACHE_HPP
#define NYU_CPP_SCOPE_REF_CACHE_HPP

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

class scope_ref_cache : public output_file {
    typedef std::vector<chilon::range> scope_type;

    typedef chilon::variant_vector_hash_map<
        chilon::variant<
            chilon::key_value<scope_type, grammar::nyah::Class *>,
            chilon::key_value<scope_type, grammar::meta::Module *> >,
        chilon::hasher>                                   map_t;

    map_t  type_ref_map_;

  protected:
    module_type& module_;

  public:
    template <class T>
    void add_type_ref(T& dep) {
        builder_(dep);
        type_ref_map_.insert(
            chilon::key_value<scope_type, decltype(dep.second) *>(
                dep.first, &dep.second));
    }

    void close();

    scope_ref_cache(builder& builder, decltype(module_)& module)
      : output_file(builder), module_(module) {}
};

} }
#endif
