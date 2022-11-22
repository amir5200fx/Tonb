#pragma once
#ifndef _Airfoil_NacaThickOffsets_Header
#define _Airfoil_NacaThickOffsets_Header

#include <Airfoil_Module.hxx>
#include <Global_Serialization.hxx>

#include <vector>

#include <Standard_Real.hxx>

namespace tnbLib
{

	class Airfoil_NacaThickOffsets
	{

		/*Private Data*/

	protected:

		// default constructor [11/5/2022 Amir]

		Airfoil_NacaThickOffsets()
		{}


		// constructors [11/5/2022 Amir]


	public:


		// public functions and operators [11/5/2022 Amir]

		virtual std::vector<std::pair<Standard_Real, Standard_Real>> 
			Values(const Standard_Real theMaxThick) const = 0;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Airfoil_NacaThickOffsets);

#endif // !_Airfoil_NacaThickOffsets_Header
