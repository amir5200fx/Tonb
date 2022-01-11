#pragma once
#ifndef _TModel_Edge_Header
#define _TModel_Edge_Header

#include <Cad_EntityPrecision.hxx>
#include <TModel_Entity.hxx>
#include <TModel_EdgeAdaptor.hxx>
#include <TModel_EdgeGeometry.hxx>

namespace tnbLib
{

	// Forward Declarations
	class TModel_Vertex;
	class TModel_Curve;
	class TModel_ParaCurve;
	class TModel_Paired;
	class TModel_Surface;
	class TModel_Wire;

	class TModel_Edge
		: public TModel_Entity
		, public TModel_EdgeAdaptor
		, public TModel_EdgeGeometry
		, public Cad_EntityPrecision
	{

		/*Private Data*/


		//- private functions and operators


		TNB_SERIALIZATION(TnbCad_EXPORT);


	protected:

		// default constructor [1/6/2022 Amir]

		TModel_Edge()
		{}

		// constructors [1/5/2022 Amir]


		explicit TModel_Edge
		(
			const std::shared_ptr<TModel_ParaCurve>& theParaCurve
		)
			: TModel_EdgeGeometry(theParaCurve)
		{}

		TModel_Edge
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<TModel_ParaCurve>& theParaCurve
		)
			: TModel_Entity(theIndex, theName)
			, TModel_EdgeGeometry(theParaCurve)
		{}

	public:

		//- virtual functions and operators

		virtual Standard_Boolean IsDegenerated() const
		{
			return Standard_False;
		}

		virtual std::vector<std::shared_ptr<TModel_Vertex>> RetrieveVertices() const = 0;

		virtual void RetrieveVerticesTo(std::vector<std::shared_ptr<TModel_Vertex>>&) const = 0;

		//- Static functions and operators

		static Standard_Boolean
			IsLess
			(
				const std::shared_ptr<TModel_Edge>& theEdge0,
				const std::shared_ptr<TModel_Edge>& theEdge1
			)
		{
			Debug_Null_Pointer(theEdge0);
			Debug_Null_Pointer(theEdge1);

			return theEdge0->Index() < theEdge1->Index();
		}

		//- Macros
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::TModel_Edge);

#endif // !_TModel_Edge_Header
