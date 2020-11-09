#pragma once
#include <Entity3d_Polygon.hxx>

template<class PlnEdge>
template<class Archive>
inline void tnbLib::StbGMaker_Edge<PlnEdge>::serialize(Archive & ar, const unsigned int version)
{
	ar & boost::serialization::base_object<PlnEdge>(*this);
	ar & theMesh3d_;
}