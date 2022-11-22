#pragma once
#ifndef _Airfoil_NacaThickOffsets_Series6_Header
#define _Airfoil_NacaThickOffsets_Series6_Header

#include <Airfoil_NacaThickOffsets.hxx>

namespace tnbLib
{

	class Airfoil_NacaThickOffsets_Series6
		: public Airfoil_NacaThickOffsets
	{

		/*Private Data*/

	protected:

		// default constructor [11/5/2022 Amir]

		Airfoil_NacaThickOffsets_Series6()
		{}

		// constructors [11/5/2022 Amir]

	public:

		// public functions and operators [11/5/2022 Amir]

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Airfoil_NacaThickOffsets_Series6);

#endif // !_Airfoil_NacaThickOffsets_Series6_Header
