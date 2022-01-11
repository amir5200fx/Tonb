#pragma once
#ifndef _TModel_RingEdge_Header
#define _TModel_RingEdge_Header

#include <TModel_GeneratedEdge.hxx>

namespace tnbLib
{

	class TModel_RingEdge
		: public TModel_GeneratedEdge
	{

		/*Private Data*/

		std::shared_ptr<TModel_Vertex> theVtx_;


		// private functions and operators [1/6/2022 Amir]

		TNB_SERIALIZATION(TnbCad_EXPORT);

	protected:

		// default constructor [1/6/2022 Amir]

		TModel_RingEdge()
		{}

	public:

		// constructors [1/6/2022 Amir]

		TModel_RingEdge
		(
			const std::shared_ptr<TModel_Vertex>& theVtx,
			const std::shared_ptr<TModel_Curve>& theCurve,
			const std::shared_ptr<TModel_ParaCurve>& theParaCurve,
			const Standard_Boolean theSense = Standard_True
		)
			: TModel_GeneratedEdge(theParaCurve, theCurve, theSense)
			, theVtx_(theVtx)
		{}

		TModel_RingEdge
		(
			const std::shared_ptr<TModel_Curve>& theCurve,
			const std::shared_ptr<TModel_ParaCurve>& theParaCurve,
			const Standard_Boolean theSense = Standard_True
		)
			: TModel_GeneratedEdge(theParaCurve, theCurve, theSense)
		{}

		TModel_RingEdge
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<TModel_Vertex>& theVtx,
			const std::shared_ptr<TModel_Curve>& theCurve,
			const std::shared_ptr<TModel_ParaCurve>& theParaCurve,
			const Standard_Boolean theSense = Standard_True
		)
			: TModel_GeneratedEdge(theIndex, theName, theParaCurve, theCurve, theSense)
			, theVtx_(theVtx)
		{}

		TModel_RingEdge
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

		Standard_Boolean IsRing() const override
		{
			return Standard_True;
		}

		TnbCad_EXPORT void RetrieveVerticesTo
		(
			std::vector<std::shared_ptr<TModel_Vertex>>&
		) const override;

		//- Macros
		GLOBAL_ACCESS_SINGLE(std::shared_ptr<TModel_Vertex>, Vtx)
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::TModel_RingEdge);

#endif // !_TModel_RingEdge_Header
