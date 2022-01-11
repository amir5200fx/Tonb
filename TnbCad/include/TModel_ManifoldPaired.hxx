#pragma once
#ifndef _TModel_ManifoldPaired_Header
#define _TModel_ManifoldPaired_Header

#include <TModel_Paired.hxx>

namespace tnbLib
{

	class TModel_ManifoldPaired
		: public TModel_Paired
	{

		/*Private Data*/

		std::shared_ptr<TModel_Edge> theEdge0_;
		std::shared_ptr<TModel_Edge> theEdge1_;


		// private functions and operators [1/9/2022 Amir]

		TnbCad_EXPORT void CheckManifold();

		TNB_SERIALIZATION(TnbCad_EXPORT);

	protected:

		// default constructor [1/9/2022 Amir]

		TModel_ManifoldPaired()
		{}

	public:

		// default constructor [1/9/2022 Amir]


		// constructors [1/9/2022 Amir]

		TModel_ManifoldPaired
		(
			const std::shared_ptr<TModel_Edge>& theEdge0,
			const std::shared_ptr<TModel_Edge>& theEdge1
		)
			: theEdge0_(theEdge0)
			, theEdge1_(theEdge1)
		{
			CheckManifold();
		}

		TModel_ManifoldPaired
		(
			std::shared_ptr<TModel_Edge>&& theEdge0,
			std::shared_ptr<TModel_Edge>&& theEdge1
		)
			: theEdge0_(std::move(theEdge0))
			, theEdge1_(std::move(theEdge1))
		{
			CheckManifold();
		}

		TModel_ManifoldPaired
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<TModel_Edge>& theEdge0,
			const std::shared_ptr<TModel_Edge>& theEdge1
		)
			: TModel_Paired(theIndex, theName)
			, theEdge0_(theEdge0)
			, theEdge1_(theEdge1)
		{
			CheckManifold();
		}

		TModel_ManifoldPaired
		(
			const Standard_Integer theIndex,
			const word& theName, 
			std::shared_ptr<TModel_Edge>&& theEdge0, 
			std::shared_ptr<TModel_Edge>&& theEdge1
		)
			: TModel_Paired(theIndex, theName)
			, theEdge0_(std::move(theEdge0))
			, theEdge1_(std::move(theEdge1))
		{
			CheckManifold();
		}

		// public functions and operators [1/9/2022 Amir]

		const auto& Edge0() const
		{
			return theEdge0_;
		}

		const auto& Edge1() const
		{
			return theEdge1_;
		}

		Standard_Boolean IsManifold() const override
		{
			return Standard_True;
		}

		const std::shared_ptr<TModel_Edge>& Other
		(
			const std::shared_ptr<TModel_Edge>& theEdge
		);

		// override functions and operators [1/9/2022 Amir]

		TnbCad_EXPORT void SetPairs() const override;
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::TModel_ManifoldPaired);

#endif // !_TModel_ManifoldPaired_Header
