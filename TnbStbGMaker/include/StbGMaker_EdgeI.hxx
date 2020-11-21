#pragma once
#include <Entity3d_Polygon.hxx>

template<class PlnEdge>
template<class Archive>
inline void tnbLib::StbGMaker_Edge<PlnEdge>::serialize(Archive & ar, const unsigned int version)
{
	ar & boost::serialization::base_object<PlnEdge>(*this);
	ar & theMesh3d_;
}

namespace tnbLib
{

	// Forward Declarations
	class Pln_Edge;
	class Pln_Ring;
}

BOOST_CLASS_EXPORT_KEY(tnbLib::StbGMaker_Edge<tnbLib::Pln_Edge>);
BOOST_CLASS_EXPORT_KEY(tnbLib::StbGMaker_Edge<tnbLib::Pln_Ring>);