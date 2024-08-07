#pragma once
#ifndef _PlnOpert_IntsctEdge_Header
#define _PlnOpert_IntsctEdge_Header

#include <Pln_Segment.hxx>

namespace tnbLib
{

	// Forward Declarations
	class PlnOpert_IntsctSegment;

	class PlnOpert_IntsctEdge
		: public Pln_Segment
	{

		/*Private Data*/

		std::shared_ptr<PlnOpert_IntsctSegment> theIntsctEntity_;

	public:

		PlnOpert_IntsctEdge
		(
			const std::shared_ptr<Pln_Vertex>& theVtx0,
			const std::shared_ptr<Pln_Vertex>& theVtx1
		)
			: Pln_Segment(theVtx0, theVtx1)
		{}

		PlnOpert_IntsctEdge
		(
			const std::shared_ptr<Pln_Vertex>& theVtx0,
			const std::shared_ptr<Pln_Vertex>& theVtx1,
			const std::shared_ptr<Pln_Curve>& theCurve,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_Segment(theVtx0, theVtx1, theCurve, Sense)
		{}

		PlnOpert_IntsctEdge
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<Pln_Vertex>& theVtx0,
			const std::shared_ptr<Pln_Vertex>& theVtx1
		)
			: Pln_Segment(theIndex, theName, theVtx0, theVtx1)
		{}

		PlnOpert_IntsctEdge
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<Pln_Vertex>& theVtx0,
			const std::shared_ptr<Pln_Vertex>& theVtx1,
			const std::shared_ptr<Pln_Curve>& theCurve,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_Segment(theIndex, theName, theVtx0, theVtx1, theCurve, Sense)
		{}

		PlnOpert_IntsctEdge(const Pln_Segment& theEdge)
			: Pln_Segment(theEdge)
		{}


		Standard_Boolean IsIntersect() const override
		{
			return Standard_True;
		}

		//- Macros
		GLOBAL_ACCESS_SINGLE(std::shared_ptr<PlnOpert_IntsctSegment>, IntsctEntity)
	};
}

#endif // !_PlnOpert_IntsctEdge_Header
