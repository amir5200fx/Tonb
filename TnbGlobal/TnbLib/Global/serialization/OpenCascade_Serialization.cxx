#include <OpenCascade_Serialization.hxx>

#include <BinTools_Curve2dSet.hxx>
#include <GeomTools.hxx>
#include <istream>

#include <Geom2d_Curve.hxx>
#include <Geom_Curve.hxx>
#include <Geom_Surface.hxx>

template<>
void boost::serialization::save
(
	TNB_oARCH_TYPE & ar, 
	const Handle(Geom2d_Curve)& c, 
	const unsigned int version
)
{
	std::stringstream st;
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