#include <OpenCascade_Serialization.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo


#include <opencascade/BinTools_Curve2dSet.hxx>
#include <opencascade/GeomTools.hxx>
#include <istream>

//#include <opencascade/gp_Pln.hxx>
//#include <opencascade/Poly_Triangle.hxx>
#include <opencascade/Geom2d_Curve.hxx>
#include <opencascade/Geom_Curve.hxx>
#include <opencascade/Geom_Surface.hxx>
//#include <opencascade/TopoDS_Shape.hxx>
#include <opencascade/BRepTools.hxx>

//template<>
//void boost::serialization::save
//(
//	TNB_oARCH_TYPE& ar, 
//	const std::shared_ptr<gp_Pln>& pl,
//	const unsigned int file_version
//)
//{
//	Standard_Real a, b, c, d;
//	pl->Coefficients(a, b, c, d);
//	ar << a;
//	ar << b;
//	ar << c;
//	ar << d;
//}
//
//template<>
//void boost::serialization::load
//(
//	TNB_iARCH_TYPE& ar,
//	std::shared_ptr<gp_Pln>& pl,
//	const unsigned int file_version
//)
//{
//	Standard_Real a, b, c, d;
//	ar >> a;
//	ar >> b;
//	ar >> c;
//	ar >> d;
//	pl = std::make_shared<gp_Pln>(a, b, c, d);
//}

template<>
void boost::serialization::save
(
	TNB_oARCH_TYPE & ar,
	const Handle(Geom2d_Curve)& c,
	const unsigned int version
)
{
	std::stringstream st;
	st.precision(16);
	GeomTools::Write(c, st);

	std::string s = st.str();
	ar << s;
}

template<>
void boost::serialization::load
(
	TNB_iARCH_TYPE & ar,
	Handle(Geom2d_Curve)& c,
	const unsigned int version
)
{
	std::string s;
	ar >> s;

	std::stringstream is;
	is << s;

	GeomTools::Read(c, is);
}

template<>
void boost::serialization::save
(
	TNB_oARCH_TYPE & ar,
	const Handle(Geom_Curve)& c,
	const unsigned int version
)
{
	std::stringstream st;
	st.precision(16);
	GeomTools::Write(c, st);

	std::string s = st.str();
	ar << s;
}

template<>
void boost::serialization::load
(
	TNB_iARCH_TYPE & ar,
	Handle(Geom_Curve)& c,
	const unsigned int version
)
{
	std::string s;
	ar >> s;

	std::stringstream is;
	is << s;

	GeomTools::Read(c, is);
}

template<>
void boost::serialization::save
(
	TNB_oARCH_TYPE & ar,
	const Handle(Geom_Surface)& sr,
	const unsigned int version
)
{
	std::stringstream st;
	st.precision(16);
	GeomTools::Write(sr, st);

	std::string s = st.str();
	ar << s;
}

template<>
void boost::serialization::load
(
	TNB_iARCH_TYPE & ar,
	Handle(Geom_Surface)& s,
	const unsigned int version
)
{
	std::string st;
	ar >> st;

	std::stringstream is;
	is << st;

	GeomTools::Read(s, is);
}

template<>
void boost::serialization::save
(
	TNB_oARCH_TYPE & ar,
	const TopoDS_Shape& sr,
	const unsigned int version
)
{
	std::stringstream st;
	st.precision(16);
	BRepTools::Write(sr, st);

	std::string s = st.str();
	ar << s;
}

#include <opencascade/BRep_Builder.hxx>

template<>
void boost::serialization::load
(
	TNB_iARCH_TYPE & ar,
	TopoDS_Shape& s,
	const unsigned int version
)
{
	std::string st;
	ar >> st;

	std::stringstream is;
	is << st;

	BRep_Builder b;
	BRepTools::Read(s, is, b);
}