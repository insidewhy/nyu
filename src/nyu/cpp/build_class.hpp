#ifndef NYU_CPP_BUILD_CLASS_HPP
#define NYU_CPP_BUILD_CLASS_HPP

#include <nyu/cpp/builder.hpp>
#include <nyu/cpp/output_file.hpp>

namespace nyu { namespace cpp {

class build_class : public output_file {
    ns_type const&  module_id_;
    class_type&     class_;

    typedef typename parser::stored<
        grammar::nyah::Attribute>::type          attr_type;
    typedef typename parser::stored<
        grammar::nyah::AssignedAttribute>::type  assigned_attr_type;

  public:
    build_class(builder& builder, ns_type const& module_id, class_type& clss)
      : output_file(builder), module_id_(module_id), class_(clss)
    { open(); }

    void operator()(enum_type& enm) { output_file::operator()(enm, 1); }
    void operator()(attr_type& attr);
    void operator()(assigned_attr_type& attr);

    void close();

  private:
    void open();
};

} }
#endif

