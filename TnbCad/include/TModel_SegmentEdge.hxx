#pragma once
#ifndef _TModel_SegmentEdge_Header
#define _TModel_SegmentEdge_Header

#include <TModel_GeneratedEdge.hxx>

namespace tnbLib
{

	class TModel_SegmentEdge
		: public TModel_GeneratedEdge
	{

		/*Private Data*/

		std::shared_ptr<TModel_Vertex> theVtx0_;
		std::shared_ptr<TModel_Vertex> theVtx1_;


		// private functions and operators [1/6/2022 Amir]

		TNB_SERIALIZATION(TnbCad_EXPORT);

	protected:

		// default constructor [1/6/2022 Amir]

		TModel_SegmentEdge()
		{}


	public:

		// constructors [1/6/2022 Amir]


		TModel_SegmentEdge
		(
			const std::shared_ptr<TModel_Vertex>& theVtx0, 
			const std::shared_ptr<TModel_Vertex>& theVtx1, 
			const std::shared_ptr<TModel_Curve>& theCurve,
			const std::shared_ptr<TModel_ParaCurve>& theParaCurve,
			const Standard_Boolean theSense = Standard_True
		)
			: TModel_GeneratedEdge(theParaCurve, theCurve, theSense)
			, theVtx0_(theVtx0)
			, theVtx1_(theVtx1)
		{}

		TModel_SegmentEdge
		(
			const std::shared_ptr<TModel_Curve>& theCurve,
			const std::shared_ptr<TModel_ParaCurve>& theParaCurve,
			const Standard_Boolean theSense = Standard_True
		)
			: TModel_GeneratedEdge(theParaCurve, theCurve, theSense)
		{}

		TModel_SegmentEdge
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<TModel_Vertex>& theVtx0, 
			const std::shared_ptr<TModel_Vertex>& theVtx1, 
			const std::shared_ptr<TModel_Curve>& theCurve,
			const std::shared_ptr<TModel_ParaCurve>& theParaCurve, 
			const Standard_Boolean theSense = Standard_True
		)
			: TModel_GeneratedEdge(theIndex, theName, theParaCurve, theCurve, theSense)
			, theVtx0_(theVtx0)
			, theVtx1_(theVtx1)
		{}

		TModel_SegmentEdge
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const std::shared_ptr<TModel_Curve>& theCurve, 
			const std::shared_ptr<TModel_ParaCurve>& theParaCurve, 
			const Standard_Boolean theSense = Standard_True
		)
			: TModel_GeneratedEdge(theIndex, theName, theParaCurve, theCurve, theSense)
		{}


		// public functions and operators [1/6/2022 Amir]


		// override functions and operators [1/6/2022 Amir]

		Standard_Boolean IsSegment() const override
		{
			return Standard_True;
		}

		//- Macros
		GLOBAL_ACCESS_SINGLE(std::shared_ptr<TModel_Vertex>, Vtx0)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<TModel_Vertex>, Vtx1)
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::TModel_SegmentEdge);

#endif // !_TModel_SegmentEdge_Header
