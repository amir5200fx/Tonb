#pragma once
#ifndef _Airfoil_trapzNacaMidline_Header
#define _Airfoil_trapzNacaMidline_Header

#include <Airfoil_NacaMidline.hxx>

namespace tnbLib
{

	class Airfoil_trapzNacaMidline
		: public Airfoil_NacaMidline
	{

		/*Private Data*/

		Standard_Real theCli_;
		Standard_Real theA_;
		Standard_Real theChord_;


		// Private functions and operators [10/30/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Airfoil_NacaMidline>(*this);
			ar & theCli_;
			ar & theA_;
		}

	public:

		// default constructor [10/30/2022 Amir]

		Airfoil_trapzNacaMidline()
			: theCli_(0)
			, theA_(0)
			, theChord_(0)
		{}

		// constructors [10/30/2022 Amir]

		Airfoil_trapzNacaMidline(const Standard_Integer theIndex, const word& theName)
			: Airfoil_NacaMidline(theIndex, theName)
			, theCli_(0)
			, theA_(0)
			, theChord_(0)
		{}


		// public functions and operators [10/30/2022 Amir]

		auto Cli() const
		{
			return theCli_;
		}

		// A is somewhere placed between xPerc between 0 and 1 which
		// the load distribution decreases linearly to zero at trailing edge (x/c=1)[10/30/2022 Amir]
		auto A() const
		{
			return theA_;
		}

		auto Chord() const
		{
			return theChord_;
		}

		TnbAirfoil_EXPORT Standard_Real
			CalcY(const Standard_Real xPerc) const override;

		void SetCli(const Standard_Real theValue)
		{
			theCli_ = theValue;
		}

		void SetA(const Standard_Real theValue)
		{
			theA_ = theValue;
		}

		void SetChord(const Standard_Real theValue)
		{
			theChord_ = theValue;
		}
	};
}

#endif // !_Airfoil_trapzNacaMidline_Header
