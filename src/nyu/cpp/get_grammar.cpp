#include <nyu/cpp/get_grammar.hpp>
#include <nyu/cpp/scope_ref_cache.hpp>

#include <nyu/error/file_location.hpp>

namespace nyu { namespace cpp {

void get_grammar::operator()(scope_ref_cache& scope) {
    if (1 == search_.size()) {
        // auto& ast = get_ast(scope);
    }
}

} }
