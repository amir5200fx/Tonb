#pragma once
#ifndef _NModel_Edge_Header
#define _NModel_Edge_Header

#include <Cad_EntityPrecision.hxx>
#include <NModel_Entity.hxx>
#include <NModel_EdgeAdaptor.hxx>
#include <NModel_EdgeGeometry.hxx>

namespace tnbLib
{

	// Forward Declarations
	class NModel_Vertex;
	class NModel_Curve;
	class NModel_ParaCurve;
	class NModel_Segment;
	class NModel_Surface;
	class NModel_Wire;

	class NModel_Edge
		: public NModel_Entity
		, public NModel_EdgeAdaptor
		, public NModel_EdgeGeometry
		, public Cad_EntityPrecision
	{

		/*Private Data*/

		std::shared_ptr<NModel_Vertex> theVtx0_;
		std::shared_ptr<NModel_Vertex> theVtx1_;

	public:

		NModel_Edge
		(
			const std::shared_ptr<NModel_Vertex>& theVtx0,
			const std::shared_ptr<NModel_Vertex>& theVtx1,
			const std::shared_ptr<NModel_Curve>& theCurve,
			const std::shared_ptr<NModel_ParaCurve>& theParaCurve,
			const Standard_Boolean theSense = Standard_True
		);

		NModel_Edge
		(
			const std::shared_ptr<NModel_Curve>& theCurve,
			const std::shared_ptr<NModel_ParaCurve>& theParaCurve,
			const Standard_Boolean theSense = Standard_True
		);

		NModel_Edge
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<NModel_Vertex>& theVtx0,
			const std::shared_ptr<NModel_Vertex>& theVtx1,
			const std::shared_ptr<NModel_Curve>& theCurve,
			const std::shared_ptr<NModel_ParaCurve>& theParaCurve,
			const Standard_Boolean theSense = Standard_True
		);

		NModel_Edge
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<NModel_Curve>& theCurve,
			const std::shared_ptr<NModel_ParaCurve>& theParaCurve,
			const Standard_Boolean theSense = Standard_True
		);

		NModel_Edge
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<NModel_Vertex>& theVtx0,
			const std::shared_ptr<NModel_Vertex>& theVtx1,
			const std::shared_ptr<NModel_Curve>& theCurve,
			const std::shared_ptr<NModel_ParaCurve>& theParaCurve,
			const Standard_Boolean theSense = Standard_True
		);

		NModel_Edge
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<NModel_Curve>& theCurve,
			const std::shared_ptr<NModel_ParaCurve>& theParaCurve,
			const Standard_Boolean theSense = Standard_True
		);


		//- virtual functions and operators

		virtual Standard_Boolean IsDegenerated() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsRing() const
		{
			return Standard_False;
		}


		//- Static functions and operators

		static Standard_Boolean
			IsLess
			(
				const std::shared_ptr<NModel_Edge>& theEdge0,
				const std::shared_ptr<NModel_Edge>& theEdge1
			)
		{
			Debug_Null_Pointer(theEdge0);
			Debug_Null_Pointer(theEdge1);

			return theEdge0->Index() < theEdge1->Index();
		}

		//- Macros
		GLOBAL_ACCESS_SINGLE(std::shared_ptr<NModel_Vertex>, Vtx0)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<NModel_Vertex>, Vtx1)
	};
}

#endif // !_NModel_Edge_Header
