#pragma once
#ifndef _Geo_AffineTrsf_PtsToUnitSq_Header
#define _Geo_AffineTrsf_PtsToUnitSq_Header

#include <Global_Done.hxx>
#include <Pnt2d.hxx>

#include <vector>

namespace tnbLib
{

	namespace geoLib
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

			//- Private functions and operators
			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive& ar, const unsigned int version)
			{
				ar& theXmin_;
				ar& theYmin_;

				ar& theXmax_;
				ar& theYmax_;

				ar& theDx_;
				ar& theDy_;
			}

		public:

			AffineTrsf_PtsToUnitSqObj()
				: theXmin_(0), theYmin_(0), theXmax_(0)
				, theYmax_(0), theDx_(0), theDy_(0)
			{
			}

			//- public functions and operators


			[[nodiscard]] auto Xmin() const
			{
				return theXmin_;
			}

			[[nodiscard]] auto Xmax() const
			{
				return theXmax_;
			}

			[[nodiscard]] auto Ymin() const
			{
				return theYmin_;
			}

			[[nodiscard]] auto Ymax() const
			{
				return theYmax_;
			}

			[[nodiscard]] auto Dx() const
			{
				return theDx_;
			}

			[[nodiscard]] auto Dy() const
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

			std::vector<Pnt2d> thePts_;

			AffineTrsf_PtsToUnitSqObj theObj_;

			//- Private functions and operators
			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive& ar, const unsigned int version)
			{
				ar& boost::serialization::base_object<Global_Done>(*this);
				ar& thePts_;
				ar& theObj_;
			}

		public:

			//- default constructor


			//- constructors

			explicit AffineTrsf_PtsToUnitSq(std::vector<Pnt2d> theQ)
				: thePts_(std::move(theQ))
			{}


			//- public functions and operators

			TnbGeo_EXPORT const AffineTrsf_PtsToUnitSqObj& TrsfObj() const;

			TnbGeo_EXPORT void Perform();

			TnbGeo_EXPORT std::vector<Pnt2d> CalcTrsfPoints(const std::vector<Pnt2d>&) const;
			
		};
	}
}

#endif // !_Geo_AffineTrsf_PtsToUnitSq_Header
