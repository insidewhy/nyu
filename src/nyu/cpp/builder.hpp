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

class build_class;
class build_grammar;

class builder {
    friend class build_class;
    friend class build_grammar;

    typedef grammar::meta::Grammar                    grammar_t;
    typedef typename parser::stored<grammar_t>::type  ast_t;
    typedef chilon::range                             range;
    typedef std::unordered_map<std::string, file>     files_t;

    ast_t     ast_;
    options&  options_;
    files_t   files_;

  public:
    typedef typename parser::stored<
        grammar::meta::Module>::type  module_type;

    typedef std::vector<range>  ns_type;

    options const& opts() const { return options_; }

  private:
    // if file doesn't exist in project, add it and return reference to it
    // otherwise return a reference to the existing file.
    file& add_file(std::string const& file_path) {
        return files_.insert(
            files_t::value_type(file_path, file())).first->second;
    }


  public:
    // parse file, throw error on parse failure
    void parse_file(std::string const& file_path);

    void operator()(module_type& module);

    void print_ast() const;
    void generate_code();

    builder(decltype(options_)& options) : options_(options) {}
};

} }
#endif
