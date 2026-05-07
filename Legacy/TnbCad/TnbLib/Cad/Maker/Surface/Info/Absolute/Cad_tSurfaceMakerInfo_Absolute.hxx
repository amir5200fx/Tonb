#pragma once
#ifndef _Cad_tSurfaceMakerInfo_Absolute_Header
#define _Cad_tSurfaceMakerInfo_Absolute_Header

#include <Cad_tSurfaceMakerInfo.hxx>

namespace tnbLib
{

	class Cad_tSurfaceMakerInfo_Absolute
		: public Cad_tSurfaceMakerInfo
	{

		/*Private Data*/

		Standard_Real thePrecision_;

		Standard_Real theMinTol_;
		Standard_Real theMaxTol_;
		Standard_Real theTol_;

		// private functions and operators [1/7/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Cad_tSurfaceMakerInfo>(*this);
			ar & thePrecision_;
			ar & theMinTol_;
			ar & theMaxTol_;
			ar & theTol_;
		}

	public:

		static TnbCad_EXPORT const Standard_Real DEFAULT_PRECISION;
		static TnbCad_EXPORT const Standard_Real DEFAULT_MIN_TOLERANCE;
		static TnbCad_EXPORT const Standard_Real DEFAULT_MAX_TOLERANCE;
		static TnbCad_EXPORT const Standard_Real DEFAULT_TOLERANCE;

		// default constructor [1/7/2022 Amir]

		Cad_tSurfaceMakerInfo_Absolute()
			: thePrecision_(DEFAULT_PRECISION)
			, theMinTol_(DEFAULT_MIN_TOLERANCE)
			, theMaxTol_(DEFAULT_MAX_TOLERANCE)
			, theTol_(DEFAULT_TOLERANCE)
		{}

		// constructors [1/7/2022 Amir]

		Cad_tSurfaceMakerInfo_Absolute
		(
			const Standard_Real thePrec, 
			const Standard_Real theMinTol,
			const Standard_Real theMaxTol,
			const Standard_Real theTol
		)
			: thePrecision_(thePrec)
			, theMinTol_(theMinTol)
			, theMaxTol_(theMaxTol)
			, theTol_(theTol)
		{}


		// public functions and operators [1/7/2022 Amir]


		// override functions and operators [1/7/2022 Amir]

		Standard_Real Precision() const override
		{
			return thePrecision_;
		}

		Standard_Real MinTolerance() const override
		{
			return theMinTol_;
		}

		Standard_Real MaxTolerance() const override
		{
			return theMaxTol_;
		}

		Standard_Real Tolerance() const override
		{
			return theTol_;
		}

		void SetPrecision(const Standard_Real tehPrec)
		{
			thePrecision_ = tehPrec;
		}

		void SetMinTolerance(const Standard_Real theMinTol)
		{
			theMinTol_ = theMinTol;
		}

		void SetMaxTolerance(const Standard_Real theMaxTol)
		{
			theMaxTol_ = theMaxTol;
		}

		void SetTolerance(const Standard_Real theTol)
		{
			theTol_ = theTol;
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Cad_tSurfaceMakerInfo_Absolute);

#endif // !_Cad_tSurfaceMakerInfo_Absolute_Header
