#pragma once
#ifndef _TModel_SingularEdge_Header
#define _TModel_SingularEdge_Header

#include <TModel_Edge.hxx>

namespace tnbLib
{

	class TModel_SingularEdge
		: public TModel_Edge
	{

		/*Private Data*/

		std::shared_ptr<TModel_Vertex> theVtx_;

		// private functions and operators [1/6/2022 Amir]

		TNB_SERIALIZATION(TnbCad_EXPORT);

	protected:

		// default constructor [1/6/2022 Amir]

		TModel_SingularEdge()
		{}

	public:

		// constructors [1/6/2022 Amir]

		TModel_SingularEdge
		(
			const std::shared_ptr<TModel_Vertex>& theVtx,
			const std::shared_ptr<TModel_ParaCurve>& theParaCurve
		)
			: TModel_Edge(theParaCurve)
			, theVtx_(theVtx)
		{}

		explicit TModel_SingularEdge
		(
			const std::shared_ptr<TModel_ParaCurve>& theParaCurve
		)
			: TModel_Edge(theParaCurve)
		{}

		TModel_SingularEdge
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<TModel_Vertex>& theVtx,
			const std::shared_ptr<TModel_ParaCurve>& theParaCurve
		)
			: TModel_Edge(theIndex, theName, theParaCurve)
			, theVtx_(theVtx)
		{}

		TModel_SingularEdge
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<TModel_ParaCurve>& theParaCurve
		)
			: TModel_Edge(theIndex, theName, theParaCurve)
		{}

		// public functions and operators [1/6/2022 Amir]


		// override functions and operators [1/6/2022 Amir]

		Standard_Boolean IsDegenerated() const override
		{
			return Standard_True;
		}

		TnbCad_EXPORT std::vector<std::shared_ptr<TModel_Vertex>> RetrieveVertices() const override;

		TnbCad_EXPORT void RetrieveVerticesTo
		(
			std::vector<std::shared_ptr<TModel_Vertex>>&
		) const override;

		//- Macros
		GLOBAL_ACCESS_SINGLE(std::shared_ptr<TModel_Vertex>, Vtx)
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::TModel_SingularEdge);

#endif // !_TModel_SingularEdge_Header
