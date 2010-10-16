#ifndef NYU_CPP_BUILDER_HPP
#define NYU_CPP_BUILDER_HPP

#include <nyu/options.hpp>
#include <nyu/file.hpp>

#include <chilon/getset.hpp>
#include <chilon/iterator_range.hpp>

#include <unordered_map>
#include <fstream>
#include <stdexcept>

namespace nyu { namespace cpp {

namespace parser = chilon::parser;

// TODO: add nodes involved in cycle to exception.
class file_dependency_cycle {};

class builder {
    typedef grammar::meta::Grammar                    grammar_t;
    typename parser::stored<grammar_t>::type  ast_;

    options&                                          options_;
    std::unordered_map<std::string, file>             files_;

    typedef decltype(files_) files_t;

  public:
    typedef chilon::variant<
        typename parser::stored<grammar::meta::ModuleDefinition>::type,
        void
    > module_id;

    typedef std::vector<chilon::range>  ns_type;

    options const& opts() const { return options_; }

    typedef typename parser::stored<
        grammar::meta::Module>::type  module_type;

  private:
    // if file doesn't exist in project, add it and return reference to it
    // otherwise return a reference to the existing file.
    file& add_file(std::string const& file_path) {
        return files_.insert(
            files_t::value_type(file_path, file())).first->second;
    }


  public:
    // parse file, return true if parsed, false if already parsed,
    // throw error on parse failure
    bool parse_file(std::string const& file_path);

    void operator()(module_type& module);

    void grammar_dep(module_id const& from_id, ns_type const& id);

    void print_ast() const;
    void generate_code();

    builder(decltype(options_)& options) : options_(options) {}
};

} }
#endif
