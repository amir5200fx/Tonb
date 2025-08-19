#pragma once
#ifndef _ShapePx_ContinProfile_GeneratedCustom_Header
#define _ShapePx_ContinProfile_GeneratedCustom_Header

#include <Standard_Handle.hxx>
#include <Global_Done.hxx>
#include <ShapePx_ContinProfile_Custom.hxx>

class Geom2d_Curve;

namespace tnbLib
{

	// Forward Declarations
	class SectPx_CurveQ;

	namespace shapePxLib
	{

		class ContinProfile_GeneratedCustom
			: public ContinProfile_Custom
			, public Global_Done
		{

			/*Private Data*/

			Standard_Integer theDegree_;
			std::shared_ptr<SectPx_CurveQ> theCurve_;


			Handle(Geom2d_Curve) theProfile_;

			//- private functions and operators

			TNB_SERIALIZATION(TnbShapePx_EXPORT);

		public:

			static TnbShapePx_EXPORT const Standard_Integer DEFAULT_MIN_DEGREE;
			static TnbShapePx_EXPORT const Standard_Integer DEFAULT_MAX_DEGREE;

			//- default constructor

			ContinProfile_GeneratedCustom()
			{}

			//- constructors

			TnbShapePx_EXPORT ContinProfile_GeneratedCustom
			(
				const Standard_Integer theIndex,
				const word& theName
			);

			TnbShapePx_EXPORT ContinProfile_GeneratedCustom
			(
				const std::shared_ptr<SectPx_CurveQ>& theCurve, 
				const Standard_Integer theDegree
			);

			TnbShapePx_EXPORT ContinProfile_GeneratedCustom
			(
				std::shared_ptr<SectPx_CurveQ>&& theCurve, 
				const Standard_Integer theDegree
			);

			TnbShapePx_EXPORT ContinProfile_GeneratedCustom
			(
				const Standard_Integer theIndex,
				const word& theName,
				const std::shared_ptr<SectPx_CurveQ>& theCurve,
				const Standard_Integer theDegree
			);

			TnbShapePx_EXPORT ContinProfile_GeneratedCustom
			(
				const Standard_Integer theIndex,
				const word& theName,
				std::shared_ptr<SectPx_CurveQ>&& theCurve, 
				const Standard_Integer theDegree
			);


			//- public functions and operators

			TnbShapePx_EXPORT Standard_Boolean 
				IsIntersect
				(
					const Standard_Real x
				) const;

			auto Degree() const
			{
				return theDegree_;
			}

			const auto& CurveQ() const
			{
				return theCurve_;
			}

			const auto& Profile() const
			{
				return theProfile_;
			}

			TnbShapePx_EXPORT void Perform();

			void SetDegree(const Standard_Integer theDeg)
			{
				theDegree_ = theDeg;
			}

			void SetCurve(const std::shared_ptr<SectPx_CurveQ>& theCurve)
			{
				theCurve_ = theCurve;
			}

			void SetCurve(std::shared_ptr<SectPx_CurveQ>&& theCurve)
			{
				theCurve_ = std::move(theCurve);
			}


			//- override functions and operators

			TnbShapePx_EXPORT Standard_Boolean IsGenerated() const override;

			TnbShapePx_EXPORT Standard_Real Lower() const override;
			TnbShapePx_EXPORT Standard_Real Upper() const override;
			TnbShapePx_EXPORT Standard_Real MinLower() const override;
			TnbShapePx_EXPORT Standard_Real MaxUpper() const override;

			TnbShapePx_EXPORT Standard_Real Value(const Standard_Real x) const override;

			TnbShapePx_EXPORT std::vector<offsetPoint> RetrieveOffsets() const override;

			TnbShapePx_EXPORT std::vector<Standard_Real> X() const override;

			TnbShapePx_EXPORT void Update() override;
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::shapePxLib::ContinProfile_GeneratedCustom);

#endif // !_ShapePx_ContinProfile_GeneratedCustom_Header