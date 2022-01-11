#pragma once
#ifndef _Cad_tModelMakerInfo_Absolute_Header
#define _Cad_tModelMakerInfo_Absolute_Header

#include <Cad_tModelMakerInfo.hxx>

namespace tnbLib
{

	class Cad_tModelMakerInfo_Absolute
		: public Cad_tModelMakerInfo
	{

		/*Private Data*/

		Standard_Real theRadius_;
		Standard_Real theTolerance_;

	public:

		static TnbCad_EXPORT const Standard_Real DEFAULT_RADIUS;
		static TnbCad_EXPORT const Standard_Real DEFAULT_TOLERANCE;

		// default constructor [1/7/2022 Amir]

		Cad_tModelMakerInfo_Absolute()
			: theRadius_(DEFAULT_RADIUS)
			, theTolerance_(DEFAULT_TOLERANCE)
		{}

		// constructors [1/7/2022 Amir]

		Cad_tModelMakerInfo_Absolute
		(
			const Standard_Real theRadius,
			const Standard_Real theTol
		)
			: theRadius_(theRadius)
			, theTolerance_(theTol)
		{}

		// public functions and operators [1/7/2022 Amir]

		Standard_Real Radius() const override
		{
			return theRadius_;
		}

		Standard_Real Tolerance() const override
		{
			return theTolerance_;
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Cad_tModelMakerInfo_Absolute);

#endif // !_Cad_tModelMakerInfo_Absolute_Header
