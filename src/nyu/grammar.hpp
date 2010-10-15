#ifndef NYU_GRAMMAR_HPP
#define NYU_GRAMMAR_HPP
namespace nyu { namespace grammar {

enum class Status {
    UNKNOWN,
    PROCESSING,
    PROCESSED
};

struct WithStatus {
    WithStatus() : status_(Status::UNKNOWN) {}
    Status status_;
};

} }
#endif
