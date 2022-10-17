#pragma once
#ifndef _Marine_EnvtParam_Header
#define _Marine_EnvtParam_Header

#include <Marine_DimensionedParam.hxx>

namespace tnbLib
{

	class Marine_EnvtParam
		: public Marine_DimensionedParam<Standard_Real>
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Marine_DimensionedParam<Standard_Real>>(*this);
		}

	protected:

		//- default constructor

		Marine_EnvtParam()
		{}


		//- constructor

		Marine_EnvtParam
		(
			const word& theName,
			const dimensionSet& theDim,
			const Standard_Real theValue
		)
			: Marine_DimensionedParam<Standard_Real>(theName, theDim, theValue)
		{}

	public:

		//- public functions and operators
	};
}

#endif // !_Marine_EnvtParam_Header
