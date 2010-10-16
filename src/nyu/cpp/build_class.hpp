#ifndef NYU_CPP_BUILD_CLASS_HPP
#define NYU_CPP_BUILD_CLASS_HPP

#include <nyu/cpp/builder.hpp>
#include <nyu/cpp/output_file.hpp>

#include <sstream>

namespace nyu { namespace cpp {

class build_class : public output_file {
    typedef builder::module_id  module_id;

    module_id const&            module_id_;
    mutable std::stringstream   body_;
    class_type&                 class_;

  public:
    build_class(builder&         builder,
                module_id const& module_id,
                class_type&      clss)
      : output_file(builder), module_id_(module_id), class_(clss) {}

    // TODO: fix this
    template <class T>
    void operator()(T& t) {}

    void close();

  private:
    void open();
};

} }
#endif

