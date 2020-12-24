#pragma once
#ifndef _NModel_EdgeAdaptor_Header
#define _NModel_EdgeAdaptor_Header

#include <Global_AccessMethod.hxx>

#include <TopoDS_Edge.hxx>

#include <memory>

namespace tnbLib
{

	//- Forward Declarations
	class NModel_Surface;
	class NModel_Segment;
	class NModel_Wire;
	class NModel_Edge;

	class NModel_EdgeAdaptor
	{

		/*Private Data*/

		std::weak_ptr<NModel_Surface> theSurface_;
		std::weak_ptr<NModel_Segment> theSegment_;
		std::weak_ptr<NModel_Wire> theWire_;

		TopoDS_Edge theTEdge_;

	protected:

		NModel_EdgeAdaptor()
		{}

	public:

		//- Macros
		GLOBAL_ACCESS_SINGLE(std::weak_ptr<NModel_Surface>, Surface)
			GLOBAL_ACCESS_SINGLE(std::weak_ptr<NModel_Segment>, Segment)
			GLOBAL_ACCESS_SINGLE(std::weak_ptr<NModel_Wire>, Wire)

			GLOBAL_ACCESS_PRIM_SINGLE(TopoDS_Edge, TEdge)
	};
}

#endif // !_NModel_EdgeAdaptor_Header