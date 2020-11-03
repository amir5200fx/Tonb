#include <Marine_Shape.hxx>

#include <BRepTools.hxx>
#include <BRep_Builder.hxx>

DECLARE_SAVE_IMP(tnbLib::Marine_Shape)
{
	ar & boost::serialization::base_object<Marine_CoordinatedEntity>(*this);

	std::stringstream st;
	BRepTools::Write(Shape(), st);

	std::string s = st.str();
	ar & s;
}

DECLARE_LOAD_IMP(tnbLib::Marine_Shape)
{
	ar & boost::serialization::base_object<Marine_CoordinatedEntity>(*this);

	std::string s;
	ar & s;

	std::stringstream st;
	st << s;

	s.clear();

	BRep_Builder builder;

	BRepTools::Read(ChangeShape(), st, builder);
}