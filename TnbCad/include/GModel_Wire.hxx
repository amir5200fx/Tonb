#pragma once
#ifndef _GModel_Wire_Header
#define _GModel_Wire_Header

#include <GModel_Entity.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <OFstream.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class GModel_Edge;
	class GModel_ParaWire;
	class GModel_ParaCurve;

	class GModel_Wire
		: public GModel_Entity
	{

		typedef std::vector<std::shared_ptr<GModel_Edge>> edgeList;

		/*Private Data*/

		std::shared_ptr<edgeList> theEdges_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbCad_EXPORT);


		//- default constructor

		GModel_Wire()
		{}

	public:


		//- constructors

		TnbCad_EXPORT GModel_Wire
		(
			const std::shared_ptr<edgeList>& theEdges
		);

		TnbCad_EXPORT GModel_Wire
		(
			std::shared_ptr<edgeList>&& theEdges
		);

		TnbCad_EXPORT GModel_Wire
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const std::shared_ptr<edgeList>& theEdges
		);

		TnbCad_EXPORT GModel_Wire
		(
			const Standard_Integer theIndex,
			const word& theName,
			std::shared_ptr<edgeList>&& theEdges
		);


		//- public functions and operators

		TnbCad_EXPORT Standard_Integer NbEdges() const;

		const auto& Edges() const
		{
			return theEdges_;
		}

		//- Io functions and operators

		void ExportPlaneCurvesToPlt
		(
			OFstream& File
		) const;


		//- Static functions and operators

		static TnbCad_EXPORT std::shared_ptr<std::vector<std::shared_ptr<GModel_ParaCurve>>>
			RetrieveParaCurves
			(
				const GModel_Wire& theWire
			);

		static TnbCad_EXPORT std::shared_ptr<GModel_ParaWire>
			RetrieveParaWire
			(
				const GModel_Wire& theWire
			);
	};
}

#endif // !_GModel_Wire_Header
