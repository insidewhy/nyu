#ifndef NYU_ERROR_GRAMMAR_NOT_FOUND_HPP
#define NYU_ERROR_GRAMMAR_NOT_FOUND_HPP

#include <nyu/grammar/meta.hpp>

#include <chilon/iterator_range.hpp>

#include <stdexcept>
#include <vector>

namespace nyu { namespace error {

typedef typename chilon::parser::stored<
    grammar::meta::ScopedId>::type  grammar_id;

struct grammar_not_found : std::runtime_error {
    grammar_id id_;

    grammar_not_found(decltype(id_) const& id)
      : std::runtime_error("grammar not found"), id_(id) {}

    ~grammar_not_found() throw() {}
};

} }
#endif
