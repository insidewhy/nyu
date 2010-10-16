#include <nyu/cpp/build_module.hpp>
#include <nyu/cpp/config.hpp>
#include <nyu/cpp/build_class.hpp>
#include <nyu/error/dep_cycle.hpp>

#include <chilon/print_join.hpp>

namespace nyu { namespace cpp {

void build_module::subnamespace(class_type& clss) {
    if (clss.second.status_ == grammar::Status::PROCESSED) return;
    else if (clss.second.status_ == grammar::Status::PROCESSING)
        throw error::dep_cycle(clss.first);

    cpp::build_class class_builder(builder_, module_.first, clss);
    for (auto it = clss.second.value_.begin();
         it != clss.second.value_.end(); ++it)
    {
        chilon::variant_apply(*it, class_builder);
    }
}

void build_module::subnamespace(grammar_type& gram) {
    if (gram.second.status_ == grammar::Status::PROCESSED) return;
    else if (gram.second.status_ == grammar::Status::PROCESSING)
        throw error::dep_cycle(gram.first);

    try {
        auto extends = std::get<0>(gram.second.value_);
        if (! extends.empty()) {
            gram.second.status_ = grammar::Status::PROCESSING;
            grammar_dep(extends);
        }
    }
    catch (error::dep_cycle& err) {
        // TODO: signify is grammar, add namespace also
        err.dependencies_.push_back(gram.first);
        throw err;
    }

    // mega todo: process grammar here

    gram.second.status_ = grammar::Status::PROCESSED;
}

void build_module::operator()(enum_type& enm) {
    if (! is_open()) open();

    body_ << "\nenum class " << enm.first << " {\n" NYU_CPP_INDENT;
    if (! enm.second.value_.empty()) {
        auto it = enm.second.value_.begin();
        body_ << std::get<0>(*it);

        // todo: handle =
        for (++it; it != enm.second.value_.end(); ++it)
            body_ << ",\n" NYU_CPP_INDENT << std::get<0>(*it);
    }
    body_ << "\n};\n";
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

void build_module::grammar_dep(ns_type const& id) {
    if (1 == id.size()) {
        // TODO: search in current module
        auto it = module_.second.value_.find(id.front());
        if (it != module_.second.value_.end()) {
            // TODO: build grammar
            return;
        }
    }
    else {
        // see if id is reference to current module
    }

    // mega todo: search in current module first
    builder_.grammar_dep(module_.first, id);
}

} }
