#include <GModel_SurfaceGeometry.hxx>

#include <Cad_GeomSurface.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <opencascade/BRepTools.hxx>
#include <opencascade/BRep_Builder.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::GModel_SurfaceGeometry)
{
	ar & theGeometry_;

	std::stringstream st;
	st.precision(16);
	BRepTools::Write(theFace_, st);

	std::string s = st.str();
	ar << s;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::GModel_SurfaceGeometry)
{
	ar & theGeometry_;

	std::string st;
	ar >> st;

	std::stringstream is;
	is << st;

	BRep_Builder b;
	BRepTools::Read(theFace_, is, b);
}