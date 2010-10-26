#ifndef NYU_CPP_BUILD_CLASS_HPP
#define NYU_CPP_BUILD_CLASS_HPP

#include <nyu/cpp/builder.hpp>
#include <nyu/cpp/output_file.hpp>

namespace nyu { namespace cpp {

class build_class : public output_file {
    ns_type const&   module_id_;
    class_type&      class_;

    std::vector<
        std::tuple<std::string, std::string, std::string> > attrs_;

    typedef typename parser::stored<
        grammar::nyah::Attribute>::type          attr_type;
    typedef typename parser::stored<
        grammar::nyah::AssignedAttribute>::type  assigned_attr_type;

  public:
    class_type&       get_class()       { return class_; }
    class_type const& get_class() const { return class_; }

    builder::ast_t&       ast()       { return builder_.ast_; }
    builder::ast_t const& ast() const { return builder_.ast_; }

    ns_type const& module_id() const { return module_id_; }

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

