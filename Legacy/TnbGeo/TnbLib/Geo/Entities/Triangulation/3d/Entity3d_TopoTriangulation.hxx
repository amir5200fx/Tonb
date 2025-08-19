#pragma once
#ifndef _Entity3d_TopoTriangulation_Header
#define _Entity3d_TopoTriangulation_Header
#include <Entity3d_Triangulation.hxx>

namespace tnbLib
{
	class Entity3d_TopoTriangulation
		: public Entity3d_Triangulation
	{
		/*Private Data*/
		std::vector<connectivity::dual> theSegments_;
		std::vector<connectivity::dual> theTAS_; // triangles around the segments

		// Private functions and opearators
		void Construct(const Entity3d_Triangulation&);
	public:
		// default constructor
		Entity3d_TopoTriangulation() = default;

		// constructors
		TnbGeo_EXPORT Entity3d_TopoTriangulation(const Entity3d_Triangulation&);
		TnbGeo_EXPORT Entity3d_TopoTriangulation(const std::vector<Pnt3d>& thePnts,
		                                         const std::vector<connectivity::triple>& theTris);

		// Public functions and operators
		auto NbSegments() const { return static_cast<Standard_Integer>(theSegments_.size()); }

		const auto& Segments() const { return theSegments_; }
		const auto& TAS() const { return theTAS_; }

		TnbGeo_EXPORT void Import(const Entity3d_Triangulation&);
	};
}

#endif