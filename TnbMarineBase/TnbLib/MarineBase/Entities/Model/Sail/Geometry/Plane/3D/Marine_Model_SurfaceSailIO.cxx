#include <Marine_Model_SurfaceSail.hxx>

#include <BRepTools.hxx>
#include <BRep_Builder.hxx>

DECLARE_SAVE_IMP(tnbLib::marineLib::Model_SurfaceSail)
{
	ar & boost::serialization::base_object<Marine_PlnSailModel>(*this);

	std::stringstream st;
	BRepTools::Write(theFace_, st);

	std::string s = st.str();
	ar & s;
}

DECLARE_LOAD_IMP(tnbLib::marineLib::Model_SurfaceSail)
{
	ar & boost::serialization::base_object<Marine_PlnSailModel>(*this);

	std::string s;
	ar & s;

	std::stringstream st;
	st << s;

	s.clear();

	BRep_Builder builder;

	BRepTools::Read(theFace_, st, builder);
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::marineLib::Model_SurfaceSail);