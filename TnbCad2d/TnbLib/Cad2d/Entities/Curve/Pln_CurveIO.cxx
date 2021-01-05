#include <Pln_Curve.hxx>

#include <BinTools_Curve2dSet.hxx>
#include <GeomTools.hxx>
#include <istream>

#include <Geom2d_Curve.hxx>
#include <fstream>

TNB_SAVE_IMPLEMENTATION(tnbLib::Pln_Curve)
{
	ar & boost::serialization::base_object<Global_Indexed>(*this);
	ar & boost::serialization::base_object<Global_Named>(*this);

	std::ostringstream st;
	st.precision(16);
	GeomTools::Write(Geometry(), st);

	std::string s = st.str();
	ar << s;
}

namespace tnbLib
{

	void LoadGeometry(std::istream& f, Handle(Geom2d_Curve)& curve)
	{
		GeomTools::Read(curve, f);
	}
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Pln_Curve)
{
	ar & boost::serialization::base_object<Global_Indexed>(*this);
	ar & boost::serialization::base_object<Global_Named>(*this);

	std::string s;
	ar >> s;

	std::stringstream is;
	is << s;
	LoadGeometry(is, ChangeGeometry());
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Pln_Curve);