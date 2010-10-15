#ifndef NYU_OPTIONS_HPP
#define NYU_OPTIONS_HPP

#include <chilon/print.hpp>

#include <fstream>
#include <string>
#include <vector>

#include <unistd.h>

namespace nyu {

struct options {
    bool                       verbose_;
    bool                       verbose_comments_;
    bool                       print_ast_;
    std::string                output_dir_;
    std::vector<std::string>   include_paths_;

    options();

    // returns number of positionals, 0 for failure, prints errors to
    // stderr
    int parse_command_line(char const *header, int argc, char *argv[]);

    template <class... T>
    void verbose(T const&... t) const {
        if (verbose_) chilon::println(std::cerr, t...);
    }

    std::string include(std::vector<chilon::range> const& path) const;

    void output_path(std::ofstream&     stream,
                     std::string const& filename) const;
    void output_path(std::ofstream&                    stream,
                     std::vector<chilon::range> const& path,
                     char const * const                suffix) const;
  private:
    void output_path_helper(std::ofstream&     stream,
                            std::string const& filename) const;
};

}

#endif
