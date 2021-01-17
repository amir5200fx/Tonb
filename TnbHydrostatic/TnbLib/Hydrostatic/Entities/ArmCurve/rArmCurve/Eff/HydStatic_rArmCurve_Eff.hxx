#pragma once
#ifndef _HydStatic_rArmCurve_Eff_Header
#define _HydStatic_rArmCurve_Eff_Header

#include <HydStatic_rArmCurve.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_rAuCurve;
	class HydStatic_CmptLib;

	namespace hydStcLib
	{

		// Forward Declarations
		class rArmCurve_Body;
		class rArmCurve_GGt;
		class rArmCurve_GGv;
		class rArmCurve_TCG;
		class rArmCurve_Tanks;

		class rArmCurve_Eff
			: public HydStatic_rArmCurve
		{

			friend class HydStatic_CmptLib;

			/*Private Data*/

			std::shared_ptr<HydStatic_rAuCurve> theAuCurve_;

			std::shared_ptr<rArmCurve_Body> theBody_;
			std::shared_ptr<rArmCurve_TCG> theTCG_;
			std::shared_ptr<rArmCurve_GGt> theGGt_;
			std::shared_ptr<rArmCurve_GGv> theGGv_;
			std::shared_ptr<rArmCurve_Tanks> theTanks_;

			auto& ChangeAuCurve()
			{
				return theAuCurve_;
			}

		protected:

			rArmCurve_Eff
			(
				const Handle(Geom2d_Curve)& theCurve
			)
				: HydStatic_rArmCurve(theCurve)
			{}

			/*rArmCurve_Eff
			(
				const Standard_Integer theIndex,
				const Handle(Geom2d_Curve)& theCurve
			)
				: HydStatic_rArmCurve(theIndex, theCurve)
			{}*/

			rArmCurve_Eff
			(
				const Standard_Integer theIndex,
				const word& theName,
				const Handle(Geom2d_Curve)& theCurve
			)
				: HydStatic_rArmCurve(theIndex, theName, theCurve)
			{}

		public:

			const auto& AuCurve() const
			{
				return theAuCurve_;
			}

			Standard_Boolean IsEffective() const override
			{
				return Standard_True;
			}

			const auto& Body() const
			{
				return theBody_;
			}

			auto& ChangeBody()
			{
				return theBody_;
			}

			const auto& TCG() const
			{
				return theTCG_;
			}

			auto& ChangeTCG()
			{
				return theTCG_;
			}

			const auto& GGt() const
			{
				return theGGt_;
			}

			auto& ChangeGGt()
			{
				return theGGt_;
			}

			const auto& GGv() const
			{
				return theGGv_;
			}

			auto& ChangeGGv()
			{
				return theGGv_;
			}

			const auto& Tanks() const
			{
				return theTanks_;
			}

			auto& ChangeTanks()
			{
				return theTanks_;
			}

			void SetBody
			(
				const std::shared_ptr<rArmCurve_Body>&& theBody
			)
			{
				theBody_ = std::move(theBody);
			}

			void SetTCG
			(
				const std::shared_ptr<rArmCurve_TCG>&& theTCG
			)
			{
				theTCG_ = std::move(theTCG);
			}

			void SetGGt
			(
				const std::shared_ptr<rArmCurve_GGt>&& theGGt
			)
			{
				theGGt_ = std::move(theGGt);
			}

			void SetGGv
			(
				const std::shared_ptr<rArmCurve_GGv>&& theGGv
			)
			{
				theGGv_ = std::move(theGGv);
			}

			void SetTanks
			(
				const std::shared_ptr<rArmCurve_Tanks>&& theTanks
			)
			{
				theTanks_ = std::move(theTanks);
			}

			void SetAuCurve
			(
				const std::shared_ptr<HydStatic_rAuCurve>&& theCurve
			)
			{
				theAuCurve_ = std::move(theCurve);
			}

			std::shared_ptr<HydStatic_rArmCurve>
				ExpandToPort() const override;
		};
	}
}

#endif // !_HydStatic_rArmCurve_Eff_Header
