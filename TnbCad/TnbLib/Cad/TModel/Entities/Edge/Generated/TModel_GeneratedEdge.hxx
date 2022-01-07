#pragma once
#ifndef _TModel_GeneratedEdge_Header
#define _TModel_GeneratedEdge_Header

#include <TModel_Edge.hxx>
#include <TModel_GeneratedEdgeGeometry.hxx>
#include <TModel_GeneratedEdgeAdaptor.hxx>

namespace tnbLib
{

	class TModel_GeneratedEdge
		: public TModel_GeneratedEdgeGeometry
		, public TModel_GeneratedEdgeAdaptor
		, public TModel_Edge
	{

		/*Private Data*/


		// private functions and operators [1/6/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<TModel_GeneratedEdgeGeometry>(*this);
			ar & boost::serialization::base_object<TModel_GeneratedEdgeAdaptor>(*this);
			ar & boost::serialization::base_object<TModel_Edge>(*this);
		}

	protected:

		// default constructor [1/6/2022 Amir]

		TModel_GeneratedEdge()
		{}

		// constructors [1/6/2022 Amir]

		TModel_GeneratedEdge
		(
			const std::shared_ptr<TModel_ParaCurve>& theParaCurve,
			const std::shared_ptr<TModel_Curve>& theCurve,
			const Standard_Boolean theSense = Standard_True
		)
			: TModel_GeneratedEdgeGeometry(theCurve, theSense)
			, TModel_Edge(theParaCurve)
		{}

		TModel_GeneratedEdge
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<TModel_ParaCurve>& theParaCurve,
			const std::shared_ptr<TModel_Curve>& theCurve,
			const Standard_Boolean theSense = Standard_True
		)
			: TModel_GeneratedEdgeGeometry(theCurve, theSense)
			, TModel_Edge(theIndex, theName, theParaCurve)
		{}

	public:


		// public functions and operators [1/6/2022 Amir]

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::TModel_GeneratedEdge);

#endif // !_TModel_GeneratedEdge_Header
