#ifndef NYAH_MOUSEDEER_CPP_BUILDER_HPP
#define NYAH_MOUSEDEER_CPP_BUILDER_HPP

#include <nyah/mousedeer/project.hpp>

#include <chilon/getset.hpp>

#include <fstream>
#include <stdexcept>

namespace nyah { namespace mousedeer { namespace cpp {

class builder {
    project& proj_;

  public:
    // add file to project and process it and its includes
    void operator()(std::string const& file_path);

    builder(decltype(proj_)& proj) : proj_(proj) {}
};

} } }
#endif