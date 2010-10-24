#ifndef nyu_grammar_WithStatus_HPP
#define nyu_grammar_WithStatus_HPP

namespace nyu { namespace grammar {

struct WithStatus {
    WithStatus()
      : status_()
    {}
    status_ Status;
};

} }
#endif
