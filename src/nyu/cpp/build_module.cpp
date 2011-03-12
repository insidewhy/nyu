#include <nyu/cpp/build_module.hpp>
#include <nyu/cpp/build_class.hpp>
#include <nyu/error/dep_cycle.hpp>

#include <chilon/print_join.hpp>

namespace nyu { namespace cpp {

void build_module::close() {
    if (! stream_.is_open()) return;

    if (! module_.first.empty()) {
        open_namespace(module_.first);
        stream_ << body_.str();
        close_namespace(module_.first.size());
    }
    else stream_ << body_.str();

    chilon::print(stream_, "\n#endif");
    stream_ << std::flush;
    stream_.close();
}

} }
