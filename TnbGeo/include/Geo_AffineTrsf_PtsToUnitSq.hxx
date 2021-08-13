#pragma once
#ifndef _Geo_AffineTrsf_PtsToUnitSq_Header
#define _Geo_AffineTrsf_PtsToUnitSq_Header

#include <Global_Done.hxx>
#include <Pnt2d.hxx>

#include <vector>

namespace tnbLib
{

	namespace GeoLib
	{

		//- Forward Declarations
		class AffineTrsf_PtsToUnitSq;

		class AffineTrsf_PtsToUnitSqObj
		{

			friend class AffineTrsf_PtsToUnitSq;

			/*Private Data*/

			Standard_Real theXmin_;
			Standard_Real theYmin_;

			Standard_Real theXmax_;
			Standard_Real theYmax_;

			Standard_Real theDx_;
			Standard_Real theDy_;

		public:

			AffineTrsf_PtsToUnitSqObj()
			{}

			//- public functions and operators


			auto Xmin() const
			{
				return theXmin_;
			}

			auto Xmax() const
			{
				return theXmax_;
			}

			auto Ymin() const
			{
				return theYmin_;
			}

			auto Ymax() const
			{
				return theYmax_;
			}

			auto Dx() const
			{
				return theDx_;
			}

			auto Dy() const
			{
				return theDy_;
			}

			TnbGeo_EXPORT Pnt2d CalcTrsfPoint(const Pnt2d&) const;
			TnbGeo_EXPORT Pnt2d CalcInvTrsfPoint(const Pnt2d&) const;

			TnbGeo_EXPORT Standard_Real CalcTrsfX(const Standard_Real) const;
			TnbGeo_EXPORT Standard_Real CalcTrsfY(const Standard_Real) const;
			TnbGeo_EXPORT Standard_Real CalcInvX(const Standard_Real) const;
			TnbGeo_EXPORT Standard_Real CalcInvY(const Standard_Real) const;
		};

		class AffineTrsf_PtsToUnitSq
			: public Global_Done
		{

			/*Private Data*/

			const std::vector<Pnt2d> thePts_;

			AffineTrsf_PtsToUnitSqObj theObj_;

		public:

			//- default constructor


			//- constructors

			AffineTrsf_PtsToUnitSq(const std::vector<Pnt2d>& theQ)
				: thePts_(theQ)
			{}


			//- public functions and operators

			TnbGeo_EXPORT const AffineTrsf_PtsToUnitSqObj& TrsfObj() const;

			TnbGeo_EXPORT void Perform();

			TnbGeo_EXPORT std::vector<Pnt2d> CalcTrsfPoints(const std::vector<Pnt2d>&) const;
			
		};
	}
}

#endif // !_Geo_AffineTrsf_PtsToUnitSq_Header
