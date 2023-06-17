#pragma once
#ifndef _AirfoilPx_ThickProfile_Header
#define _AirfoilPx_ThickProfile_Header

#include <Airfoil_Module.hxx>
#include <Standard_TypeDef.hxx>
#include <Global_Serialization.hxx>

namespace tnbLib
{

	// Forward Declarations [4/26/2023 Payvand]
	class AirfoilPx;
	class Pln_Curve;

	class AirfoilPx_ThickProfile
	{

		friend class AirfoilPx;

		/*Private Data*/

		Standard_Real theChordLen_;

		// Private functions and operators [4/26/2023 Payvand]

		void SetChordLen(const Standard_Real x) { theChordLen_ = x; }

		virtual void Perform() = 0;

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar& theChordLen_;
		}

	protected:

		// default constructor [4/25/2023 Payvand]

		AirfoilPx_ThickProfile()
			: theChordLen_(1.0)
		{}

		// constructors [4/25/2023 Payvand]

	public:

		// Public functions and operators [4/25/2023 Payvand]

		auto ChordLen() const { return theChordLen_; }

		virtual Standard_Real Value(const Standard_Real) const = 0;

		virtual std::vector<std::shared_ptr<Pln_Curve>> Curves() const = 0;
		virtual std::vector<Standard_Real> Spans() const = 0;

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::AirfoilPx_ThickProfile);

#endif // !_AirfoilPx_ThickProfile_Header
