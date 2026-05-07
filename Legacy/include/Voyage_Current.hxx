#pragma once
#ifndef _Voyage_Current_Header
#define _Voyage_Current_Header

#include <Vec2d.hxx>

namespace tnbLib
{

	class Voyage_Current
	{

		/*Private Data*/

		Vec2d theVector_;


		// Private functions and operators [7/10/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& theVector_;
		}

	public:

		// default constructor [7/10/2023 Payvand]

		Voyage_Current()
		{}

		//  constructors [7/10/2023 Payvand]

		Voyage_Current(const Vec2d& theVector)
			: theVector_(theVector)
		{}

		Voyage_Current(Vec2d&& theVetor)
			: theVector_(std::move(theVetor))
		{}


		// Public functions and operators [7/10/2023 Payvand]

		const auto& Vector() const { return theVector_; }

		void SetVector(const Vec2d& theVector) { theVector_ = theVector; }
		void SetVector(Vec2d&& theVector) { theVector_ = std::move(theVector); }

	};
}

#endif // !_Voyage_Current_Header
