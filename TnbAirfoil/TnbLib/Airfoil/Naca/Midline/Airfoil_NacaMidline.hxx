#pragma once
#ifndef _Airfoil_NacaMidline_Header
#define _Airfoil_NacaMidline_Header

#include <Airfoil_Entity.hxx>

namespace tnbLib
{

	class Airfoil_NacaMidline
		: public Airfoil_Entity
	{

		/*Private Data*/


		// Private functions and operators [10/30/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Airfoil_Entity>(*this);
		}

	protected:

		// default constructor [10/30/2022 Amir]

		Airfoil_NacaMidline()
		{}


		// constructors [10/30/2022 Amir]

		Airfoil_NacaMidline(const Standard_Integer theIndex, const word& theName)
			: Airfoil_Entity(theIndex, theName)
		{}

	public:

		// public funct6ions and operators [10/30/2022 Amir]

		// the xPerc value is between 0 and 1 [10/30/2022 Amir]
		virtual Standard_Real CalcY(const Standard_Real xPerc) const = 0;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Airfoil_NacaMidline);

#endif // !_Airfoil_NacaMidline_Header
