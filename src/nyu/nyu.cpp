#include <nyu/cpp/builder.hpp>
#include <nyu/options.hpp>
#include <nyu/error/output_file.hpp>
#include <nyu/error/grammar_not_found.hpp>
#include <nyu/error/include_not_found.hpp>
#include <nyu/error/file_location.hpp>

#include <chilon/print.hpp>

#include <iostream>
#include <stdexcept>

// #define MOUSEBEAR_VERSION "1000 (just don't get in a car, and stay away from my family)"
// #define MOUSEBEAR_VERSION "999 (she's also known as darwinius)"
// #define MOUSEBEAR_VERSION "998 (grind machine)"
// #define MOUSEBEAR_VERSION "997 (420 mishap)"
// #define MOUSEBEAR_VERSION "996 (super mousebear 4)"
// #define MOUSEBEAR_VERSION "995 (ibuki mousebear)"
// #define MOUSEBEAR_VERSION "994 (maryam the butcher)"
// #define MOUSEBEAR_VERSION "993 (friendly beard)"
// #define MOUSEDEER_VERSION "992 (rose almost 3000 mousedear)"
// #define MOUSEDEER_VERSION "991 (raging mousedeer)"
// #define NYU_VERSION "0.1 (displacing nyu)"
// #define NYU_VERSION "0.2 (sweet island)"
// #define NYU_VERSION "0.3 (kuchenfest)"
// #define NYU_VERSION "0.4 (spesiel bee friend)"
// #define NYU_VERSION "0.8 (suggested mouse name: crunchy yore)"
#define NYU_VERSION "0.8.1 (suggested mouse name: crunchy)"

namespace nyu {

inline int main(int argc, char *argv[]) {
    options opts;

    char const header[] = "nyu " NYU_VERSION "\nusage: nyu [arguments] <grammar files to process>";
    int nPositionals = opts.parse_command_line(header, argc, argv);

    if (0 == nPositionals) return 1;

    cpp::builder build_source(opts);
    try {
        for (int i = 1; i <= nPositionals; ++i) build_source.parse_file(argv[i]);

        build_source.generate_code();
        if (opts.print_ast_) build_source.print_ast();
    }
    catch (error::cannot_open_file const& e) {
        chilon::println(std::cerr, e.what(), ": ", e.file_path_);
    }
    catch (error::cannot_open_output_file const& e) {
        chilon::println(std::cerr, e.what(), ": ", e.file_path_);
    }
    catch (error::grammar_not_found const& e) {
        chilon::println(std::cerr, e.what(), ": ", e.id_);
    }
    catch (error::include_not_found const& e) {
        chilon::println(std::cerr, e.what(), ": ", e.id_);
    }
    catch (error::parsing const& e) {
        chilon::println(std::cerr, e.what(), ": ", e.file_path_);
    }
    catch (error::file_location const& e) {
        build_source.file_error(e.location_, e.what());
        return 1;
    }
    catch (std::runtime_error const& e) {
        chilon::println(std::cerr, e.what());
        return 1;
    }

    return 0;
}

}

int main(int argc, char *argv[]) {
    return nyu::main(argc, argv);
}
