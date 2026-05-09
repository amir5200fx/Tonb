#pragma once
#ifndef _Airfoil_NacaThickness_Header
#define _Airfoil_NacaThickness_Header

#include <Airfoil_Entity.hxx>

namespace tnbLib
{

	class Airfoil_NacaThickness
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

		Airfoil_NacaThickness()
		{}


		// constructors [10/30/2022 Amir]

		Airfoil_NacaThickness(const Standard_Integer theIndex, const word& theName)
			: Airfoil_Entity(theIndex, theName)
		{}

	public:

		// public functions and operators [10/30/2022 Amir]

		virtual Standard_Real CalcYt(const Standard_Real xPerc) const = 0;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Airfoil_NacaThickness);

#endif // !_Airfoil_NacaThickness_Header
