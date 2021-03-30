#pragma once
#ifndef _Cad_EntityPrecision_Header
#define _Cad_EntityPrecision_Header

#include <Precision.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Global_Serialization.hxx>

namespace tnbLib
{

	class Cad_EntityPrecision
	{

		/*Private Data*/

		Standard_Real thePrecision_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & thePrecision_;
		}

	public:

		Cad_EntityPrecision()
			: thePrecision_(Precision::Confusion())
		{}

		Cad_EntityPrecision(const Standard_Real thePrec)
		{
			SetPrecision(thePrec);
		}

		Standard_Real Presicion() const
		{
			return thePrecision_;
		}

		Standard_Real& Presicion()
		{
			return thePrecision_;
		}

		void SetPrecision(const Standard_Real thePrec)
		{
			if (thePrec <= RealSmall())
			{
				FatalErrorIn("void SetPrecision(const Standard_Real thePrec)")
					<< "Invalid Precision: " << thePrecision_ << endl
					<< abort(FatalError);
			}

			thePrecision_ = thePrec;
		}
	};
}

#endif // !_Cad_EntityPrecision_Header
