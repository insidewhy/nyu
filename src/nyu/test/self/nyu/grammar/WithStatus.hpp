#ifndef nyu_grammar_WithStatus_HPP
#define nyu_grammar_WithStatus_HPP

#include <nyu/grammar.hpp>

namespace nyu { namespace grammar {

struct WithStatus {
    WithStatus()
      : status_(Status::UNKNOWN)
    {}
    Status status_;
};

} }
#endif
