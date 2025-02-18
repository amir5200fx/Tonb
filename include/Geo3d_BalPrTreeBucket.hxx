#pragma once
#ifndef _Geo3d_BalPrTreeBucket_Header
#define _Geo3d_BalPrTreeBucket_Header

#include <Global_TypeDef.hxx>

#include <set>

namespace tnbLib
{

	template<class T>
	class Geo3d_BalPrTreeBucket
	{

		/*Private Data*/

		std::set<T> theBucket_;

	protected:

		// default constructor [7/5/2022 Amir]

		Geo3d_BalPrTreeBucket()
		{}


	public:

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

#include <Geo3d_BalPrTreeBucketI.hxx>

#endif // !_Geo3d_BalPrTreeBucket_Header
