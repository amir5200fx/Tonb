#include <Geo_ProfileFun_Geom.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo


#include <opencascade/BinTools_Curve2dSet.hxx>
#include <opencascade/GeomTools.hxx>
#include <istream>

#include <opencascade/Geom2d_Curve.hxx>

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