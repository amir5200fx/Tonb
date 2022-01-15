#include <Geo_ProfileFun_Geom.hxx>

#include <BinTools_Curve2dSet.hxx>
#include <GeomTools.hxx>
#include <istream>

#include <Geom2d_Curve.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::geoLib::ProfileFun_Geom)
{
	std::stringstream st;
	GeomTools::Write(theCurve_, st);

	std::string s = st.str();
	ar << s;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::geoLib::ProfileFun_Geom)
{
	std::string s;
	ar >> s;

	std::stringstream is;
	is << s;

	GeomTools::Read(theCurve_, is);
}