#pragma once
#ifndef _ISC08_Parameter_Header
#define _ISC08_Parameter_Header

#include <Marine_DimensionedParam.hxx>

namespace tnbLib
{

	class ISC08_Parameter
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

		ISC08_Parameter()
		{}


		//- constructors

		ISC08_Parameter
		(
			const word& theName,
			const dimensionSet& theDim
		)
			: Marine_DimensionedParam<Standard_Real>(theName, theDim)
		{}

		ISC08_Parameter
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

#include <ISC08_Parameters.hxx>

#endif // !_ISC08_Parameter_Header
