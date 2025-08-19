#pragma once
#ifndef _TModel_Paired_Header
#define _TModel_Paired_Header

#include <Global_AccessMethod.hxx>
#include <TModel_Entity.hxx>
#include <TModel_PairedGeometry.hxx>

namespace tnbLib
{

	// Forward Declarations
	class TModel_Edge;
	class Cad_tModelMaker;

	class TModel_Paired
		: public TModel_Entity
		, public TModel_PairedGeometry
	{

		friend class Cad_tModelMaker;

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<TModel_Entity>(*this);
			ar & boost::serialization::base_object<TModel_PairedGeometry>(*this);
		}

	protected:

		// default constructor [1/5/2022 Amir]

		TModel_Paired()
		{}

		// constructors [1/9/2022 Amir]

		TModel_Paired
		(
			const Standard_Integer theIndex, 
			const word& theName
		)
			: TModel_Entity(theIndex, theName)
		{}

	public:


		// public functions and operators [1/5/2022 Amir]

		virtual std::vector<std::shared_ptr<TModel_Edge>> RetrieveEdges() const = 0;

		virtual void RetrieveEdgesTo(std::vector<std::shared_ptr<TModel_Edge>>&) const = 0;
		virtual void SetPairs() const = 0;

		virtual Standard_Boolean IsManifold() const
		{
			return Standard_False;
		}


		
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::TModel_Paired);

#include <TModel_ManifoldPaired.hxx>
#include <TModel_nonManifoldPaired.hxx>

#endif // !_TModel_Paired_Header
