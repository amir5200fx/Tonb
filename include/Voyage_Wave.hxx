#pragma once
#ifndef _Voyage_Wave_Header
#define _Voyage_Wave_Header

#include <Global_Serialization.hxx>
#include <Global_TypeDef.hxx>

namespace tnbLib
{

	class Voyage_Wave
	{

		/*Private Data*/

		Standard_Real theHs_;
		Standard_Real theTp_;
		Standard_Real theSw_;

		// Private functions and operators [7/11/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& theHs_;
			ar& theTp_;
			ar& theSw_;
		}

	public:

		// default constructor [7/11/2023 Payvand]

		Voyage_Wave()
			: theHs_(0)
			, theTp_(0)
			, theSw_(0)
		{}

		// constructors [7/11/2023 Payvand]

		Voyage_Wave(const Standard_Real theHs, const Standard_Real theTp, const Standard_Real theSw)
			: theHs_(theHs)
			, theTp_(theTp)
			, theSw_(theSw)
		{}

		// Public functions and operators [7/11/2023 Payvand]

		auto Hs() const { return theHs_; }
		auto Tp() const { return theTp_; }
		auto Sw() const { return theSw_; }

		void SetHs(const Standard_Real x) { theHs_ = x; }
		void SetTp(const Standard_Real x) { theTp_ = x; }
		void SetSw(const Standard_Real x) { theSw_ = x; }

	};
}

#endif // !_Voyage_Wave_Header
