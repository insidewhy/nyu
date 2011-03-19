#ifndef NYU_FILE_HPP
#define NYU_FILE_HPP

#include <nyu/grammar/meta.hpp>
#include <nyu/error/file.hpp>

#include <chilon/getset.hpp>
#include <chilon/color.hpp>

namespace nyu {

class file {
    typedef chilon::parser::stream<
        chilon::parser::file_stream, grammar::nyu::Spacing>   stream_t;

    typedef grammar::meta::Grammar                            grammar_t;
    typedef typename chilon::parser::stored<grammar_t>::type  ast_type;

    stream_t   stream_;

    bool processed_;
  public:
    file() : processed_(false) {};

    bool has_range(chilon::range const& data) const {
        return data.begin() >= stream_.file_begin_ &&
               data.end() <= stream_.end();
    }

    bool parse_succeeded() const {
        return stream_.file_loaded() && stream_.empty();
    }

    void set_begin(char const *begin) { stream_.begin() = begin; }

    template <class Stream>
    void print_parse_error(Stream& out,
                           std::string const& file_path,
                           std::string const& message)
    {
        unsigned int column = 0;
        auto it = stream_.begin();
        for (; it != stream_.file_begin_ && *it != '\n'; --it) {
            ++column;
        }

        unsigned int line_count = 1;
        for (; it != stream_.file_begin_; --it) {
            if (*it == '\n') ++line_count;
        }

        auto line_end = stream_.begin();
        for (; line_end != stream_.end() && *line_end != '\n'; ++line_end) {}

        out << file_path << ':' << line_count << ':' << column << ':'
            << message << '\n' <<
            chilon::range(stream_.begin() - column + 1, line_end) << std::endl;

        // TODO: modulus number of columns in display
        for (unsigned int i = 1; i < column; ++i)
            out << ' ';
        out << chilon::color::s_red << '^' << chilon::color::s_neutral << '\n';
    }

    bool parse(char const * const file_path, ast_type& ast) {
        if (! stream_.load(file_path)) {
            throw error::cannot_open_file(file_path);
        }

        stream_.optional_spacing();

        if (chilon::parser::parse<grammar_t>::skip(stream_, ast)) {
            stream_.optional_spacing();
            return true;
        }
        else return false;
    }
};

}

#endif

