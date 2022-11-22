#pragma once
#ifndef _Geo2d_BalPrTreeBucket_Header
#define _Geo2d_BalPrTreeBucket_Header

#include <Standard_TypeDef.hxx>

#include <set>

namespace tnbLib
{

	template<class T>
	class Geo2d_BalPrTreeBucket
	{

		/*Private Data*/

		std::set<T> theBucket_;

	public:

		// default constructor [7/5/2022 Amir]

		Geo2d_BalPrTreeBucket()
		{}


		// public functions and operators [7/5/2022 Amir]

		Standard_Boolean IsEmpty() const;

		Standard_Integer Size() const;

		const auto& Bucket() const
		{
			return theBucket_;
		}

		void Insert(const T& theObject);
		void Insert(T&& theObject);

		void Remove(const T& theObject);
	};
}

#include <Geo2d_BalPrTreeBucketI.hxx>

#endif // !_Geo2d_BalPrTreeBucket_Header
