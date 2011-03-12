#ifndef nyu_grammar_NyuRule_HPP
#define nyu_grammar_NyuRule_HPP

namespace nyu { namespace grammar {

struct NyuRule {
    enum class Status {
        UNKNOWN,
        NORMAL,
        NODE,
        PROCESSED
    };

    NyuRule()
      : status_(Status::UNKNOWN)
    {}
    Status status_;
};

} }
#endif
