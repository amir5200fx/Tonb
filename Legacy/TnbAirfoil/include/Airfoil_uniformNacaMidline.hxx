#pragma once
#ifndef _Airfoil_uniformNacaMidline_Header
#define _Airfoil_uniformNacaMidline_Header

#include <Airfoil_NacaMidline.hxx>

namespace tnbLib
{

	class Airfoil_uniformNacaMidline
		: public Airfoil_NacaMidline
	{

		/*Private Data*/

		Standard_Real theCli_;


		// Private functions and operators [10/30/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Airfoil_NacaMidline>(*this);
			ar & theCli_;
		}

	public:

		// default constructor [10/30/2022 Amir]

		Airfoil_uniformNacaMidline()
			: theCli_(0)
		{}


		// constructors [10/30/2022 Amir]

		Airfoil_uniformNacaMidline(const Standard_Integer theIndex, const word& theName)
			: Airfoil_NacaMidline(theIndex, theName)
			, theCli_(0)
		{}


		// public functions and operators [10/30/2022 Amir]

		auto Cli() const
		{
			return theCli_;
		}

		TnbAirfoil_EXPORT Standard_Real 
			CalcY(const Standard_Real xPerc) const override;

		void SetCli(const Standard_Real theValue)
		{
			theCli_ = theValue;
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Airfoil_uniformNacaMidline);

#endif // !_Airfoil_uniformNacaMidline_Header
