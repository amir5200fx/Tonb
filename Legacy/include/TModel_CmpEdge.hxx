#pragma once
#ifndef _TModel_CmpEdge_Header
#define _TModel_CmpEdge_Header

#include <TModel_Entity.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class TModel_Edge;
	class TModel_Wire;
	class Cad_Tools;
	class Cad_tSurfaceMaker;

	class TModel_CmpEdge
		: public TModel_Entity
	{

		friend class TModel_Edge;
		friend class TModel_Wire;
		friend class Cad_Tools;
		friend class Cad_tSurfaceMaker;

		/*Private Data*/

		std::vector<std::shared_ptr<TModel_Edge>> theEdges_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbCad_EXPORT);

	protected:

		void Insert(const std::shared_ptr<TModel_Edge>& theEdge)
		{
			theEdges_.push_back(theEdge);
		}

		auto& EdgesRef()
		{
			return theEdges_;
		}

	public:

		// default constructor [1/6/2022 Amir]

		TModel_CmpEdge()
		{}

		// constructors [1/6/2022 Amir]

		TModel_CmpEdge
		(
			const Standard_Integer theIndex
		)
			: TModel_Entity(theIndex)
		{}

		TModel_CmpEdge
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: TModel_Entity(theIndex, theName)
		{}


		// public functions and operators [1/6/2022 Amir]

		auto NbEdges() const
		{
			return (Standard_Integer)theEdges_.size();
		}

		const auto& Edges() const
		{
			return theEdges_;
		}

		//void Reverse();

		
	};
}


BOOST_CLASS_EXPORT_KEY(tnbLib::TModel_CmpEdge);

#endif // !_TModel_CmpEdge_Header
