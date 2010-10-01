#include <nyu/options.hpp>
#include <nyu/config.hpp>

#include <chilon/conf/cmd/command_line.hpp>
#include <chilon/parser/joined.hpp>
#include <chilon/parser/char_range.hpp>
#include <chilon/parser/char.hpp>
#include <chilon/parser/many.hpp>

#include <sstream>

namespace nyu {

namespace cmd_line = chilon::conf::cmd;

options::options() : verbose_(false), print_ast_(false), output_dir_(".") {}

int options::parse_command_line(char const *header, int argc, char *argv[]) {
    int nPositionals;

    using chilon::conf::value;
    using cmd_line::options_description;

    options_description opt_parser;
    opt_parser.add_options()
        .help(header)
        ("p,print",      print_ast_, "print AST of grammar")
        ("v,verbose",    verbose_, "increase verbosity")
        ("o,output-dir", output_dir_, "directory to output code")
        ("I,include",    include_paths_, "include paths")
        ;

    try {
        nPositionals = cmd_line::parser(argc, argv, opt_parser)(std::cerr).n_positionals();
    }
    catch (cmd_line::invalid_arguments& ) {
        return 0;
    }
    catch (cmd_line::bad_value& e) {
        std::cerr << "bad value reading command line options\n";
        std::cout << opt_parser << std::endl;
        return 0;
    }
    catch (cmd_line::expected_argument& e) {
        std::cerr << "expected command line argument\n";
        std::cout << opt_parser << std::endl;
        return 0;
    }

    include_paths_.push_back(std::string(MOUSEDEER_SYSTEM_INCLUDE_PATH));

    if (nPositionals < 1) {
        std::cerr << "please supply at least one grammar to parse\n";
        std::cout << opt_parser << std::endl;
        return 0;
    }

    return nPositionals;
}

std::string options::include(std::vector<chilon::range> const& path) {
    std::stringstream s;
    s << '/';
    chilon::print_join(s, '/', path);
    s << ".nyah";
    for (auto it = include_paths_.begin(); it != include_paths_.end();
         ++it)
    {
        std::string search = *it + s.str();
        if (! access(search.c_str(), R_OK)) return search;
    }

    return "";
}

}