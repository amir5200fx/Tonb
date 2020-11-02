#include <Pln_Curve.hxx>

#include <BinTools_Curve2dSet.hxx>
#include <GeomTools.hxx>
#include <istream>

#include <Geom2d_Curve.hxx>

DECLARE_SAVE_IMP(tnbLib::Pln_Curve)
{
	std::stringstream st;
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

DECLARE_LOAD_IMP(tnbLib::Pln_Curve)
{
	std::string s;
	ar >> s;

	std::stringstream is;
	is << s;
	LoadGeometry(is, ChangeGeometry());
}