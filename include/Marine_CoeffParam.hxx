#pragma once
#ifndef _Marine_CoeffParam_Header
#define _Marine_CoeffParam_Header

#include <Marine_DimensionedParam.hxx>

namespace tnbLib
{

	class Marine_CoeffParam
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

		Marine_CoeffParam()
		{}


		//- constructor

		Marine_CoeffParam
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

#endif // !_Marine_CoeffParam_Header
