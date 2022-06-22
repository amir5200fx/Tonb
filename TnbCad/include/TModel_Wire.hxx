#pragma once
#ifndef _TModel_Wire_Header
#define _TModel_Wire_Header

#include <TModel_Entity.hxx>
#include <Entity2d_BoxFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	class TModel_ParaCurve;
	class TModel_ParaWire;
	class TModel_Edge;

	class TModel_Wire
		: public TModel_Entity
	{

		typedef std::vector<std::shared_ptr<TModel_Edge>> edgeList;

		/*Private Data*/

		std::shared_ptr<edgeList> theEdges_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbCad_EXPORT);

	protected:

		//- default constructors

		TModel_Wire()
		{}

	public:


		//- constructors

		TModel_Wire
		(
			const std::shared_ptr<edgeList>& theEdges
		)
			: theEdges_(theEdges)
		{}

		TModel_Wire
		(
			std::shared_ptr<edgeList>&& theEdges
		)
			: theEdges_(std::move(theEdges))
		{}

		TModel_Wire
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<edgeList>& theEdges
		)
			: TModel_Entity(theIndex, theName)
			, theEdges_(theEdges)
		{}

		TModel_Wire
		(
			const Standard_Integer theIndex,
			const word& theName,
			std::shared_ptr<edgeList>&& theEdges
		)
			: TModel_Entity(theIndex, theName)
			, theEdges_(std::move(theEdges))
		{}



		//- public functions and operators


		TnbCad_EXPORT Standard_Integer NbEdges() const;

		const auto& Edges() const
		{
			return theEdges_;
		}

		TnbCad_EXPORT Entity2d_Box CalcParametricBoundingBox() const;

		// static functions and operators [6/21/2022 Amir]

		static TnbCad_EXPORT std::shared_ptr<std::vector<std::shared_ptr<TModel_ParaCurve>>>
			RetrieveParaCurves
			(
				const TModel_Wire& theWire
			);

		static TnbCad_EXPORT std::shared_ptr<TModel_ParaWire>
			RetrieveParaWire
			(
				const TModel_Wire& theWire
			);
	};
}


BOOST_CLASS_EXPORT_KEY(tnbLib::TModel_Wire);

#endif // !_TModel_Wire_Header
