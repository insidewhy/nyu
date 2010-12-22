#include <nyu/cpp/build_module.hpp>
#include <nyu/cpp/build_class.hpp>
#include <nyu/cpp/build_grammar.hpp>
#include <nyu/error/dep_cycle.hpp>

#include <chilon/print_join.hpp>

namespace nyu { namespace cpp {

void build_module::subnamespace(class_type& clss) {
    if (clss.second.status_ == grammar::Status::PROCESSED) return;
    else if (clss.second.status_ == grammar::Status::PROCESSING)
        throw error::dep_cycle(clss.first);

    cpp::build_class class_builder(builder_, module_, clss);
    for (auto it = clss.second.value_.begin();
         it != clss.second.value_.end(); ++it)
    {
        chilon::variant_apply(*it, class_builder);
    }

    class_builder.close();
}

void build_module::subnamespace(grammar_type& gram) {
    if (gram.second.status_ == grammar::Status::PROCESSED) return;
    else if (gram.second.status_ == grammar::Status::PROCESSING)
        throw error::dep_cycle(gram.first);

    cpp::build_grammar grammar_builder(builder_, module_, gram);
    auto& children = std::get<1>(gram.second.value_);
    for (auto it = children.begin(); it != children.end(); ++it) {
        grammar_builder(*it);
    }
    grammar_builder.close();

    gram.second.status_ = grammar::Status::PROCESSED;
}

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
