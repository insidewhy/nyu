#ifndef NYU_CPP_TYPE_REF_CACHE_HPP
#define NYU_CPP_TYPE_REF_CACHE_HPP

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

struct type_ref_cache : output_file {
    typedef std::vector<chilon::range> scope_type;

    typedef chilon::variant_vector_hash_map<
        chilon::variant<
            chilon::key_value<scope_type, grammar::nyah::Class *>,
            chilon::key_value<scope_type, grammar::meta::Module *> >,
        chilon::hasher>                                   map_t;

    template <class T>
    void add_type_ref(T& dep) {
        builder_(dep);
        type_ref_map_.insert(
            chilon::key_value<scope_type, decltype(dep.second) *>(
                dep.first, &dep.second));
    }

    void close();

    type_ref_cache(builder& builder) : output_file(builder) {}
  private:
    map_t  type_ref_map_;
};

} }
#endif
