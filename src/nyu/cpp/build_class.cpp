#include <nyu/cpp/build_class.hpp>

namespace nyu { namespace cpp {

void build_class::close() {
    if (! module_id_.empty()) {
        open_namespace(module_id_);
        stream_ << body_.str();
        close_namespace(module_id_.size());
    }
    else stream_ << body_.str();

    chilon::print(stream_, "\n#endif");
    stream_ << std::flush;
    stream_.close();
}

} }
