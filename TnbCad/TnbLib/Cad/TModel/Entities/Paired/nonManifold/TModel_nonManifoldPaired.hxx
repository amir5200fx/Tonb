#pragma once
#ifndef _TModel_nonManifoldPaired_Header
#define _TModel_nonManifoldPaired_Header

#include <TModel_Paired.hxx>

#include <map>

namespace tnbLib
{

	class TModel_nonManifoldPaired
		: public TModel_Paired
	{

		/*private Data*/

		std::map<Standard_Integer, std::shared_ptr<TModel_Edge>> theEdges_;


		// private functions and operators [1/9/2022 Amir]

		TNB_SERIALIZATION(TnbCad_EXPORT);

		

	public:

		// default constructor [1/9/2022 Amir]

		TModel_nonManifoldPaired()
		{}

		// constructors [1/9/2022 Amir]

		TModel_nonManifoldPaired
		(
			const Standard_Integer theIndex, 
			const word& theName
		)
			: TModel_Paired(theIndex, theName)
		{}


		// public functions and operators [1/9/2022 Amir]

		TnbCad_EXPORT Standard_Boolean IsFree() const;

		const auto& Edges() const
		{
			return theEdges_;
		}

		auto& EdgesRef()
		{
			return theEdges_;
		}

		auto NbEdges() const
		{
			return (Standard_Integer)theEdges_.size();
		}

		TnbCad_EXPORT std::shared_ptr<TModel_Edge> 
			RemoveEdge(const Standard_Integer theIndex);

		TnbCad_EXPORT void InsertToEdges
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<TModel_Edge>& theEdge
		);

		TnbCad_EXPORT void InsertToEdges
		(
			const Standard_Integer theIndex,
			std::shared_ptr<TModel_Edge>&& theEdge
		);

		// override functions and operators [1/9/2022 Amir]

		TnbCad_EXPORT void SetPairs() const override;
		
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::TModel_nonManifoldPaired);

#endif // !_TModel_nonManifoldPaired_Header
