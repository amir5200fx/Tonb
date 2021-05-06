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
	class HydStatic_Tools;

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
			friend class HydStatic_Tools;

			/*Private Data*/

			std::shared_ptr<HydStatic_rAuCurve> theAuCurve_;

			std::shared_ptr<rArmCurve_Body> theBody_;
			//std::shared_ptr<rArmCurve_TCG> theTCG_;
			//std::shared_ptr<rArmCurve_GGt> theGGt_;
			//std::shared_ptr<rArmCurve_GGv> theGGv_;
			std::shared_ptr<rArmCurve_Tanks> theTanks_;


			//- private functions and operators

			TNB_SERIALIZATION(TnbHydStatic_EXPORT);

			auto& ChangeAuCurve()
			{
				return theAuCurve_;
			}

			auto& ChangeBody()
			{
				return theBody_;
			}

			auto& ChangeTanks()
			{
				return theTanks_;
			}

			void SetBody
			(
				std::shared_ptr<rArmCurve_Body>&& theBody
			)
			{
				theBody_ = std::move(theBody);
			}

			void SetBody
			(
				const std::shared_ptr<rArmCurve_Body>& theBody
			)
			{
				theBody_ = theBody;
			}

			void SetTanks
			(
				std::shared_ptr<rArmCurve_Tanks>&& theTanks
			)
			{
				theTanks_ = std::move(theTanks);
			}

			void SetTanks
			(
				const std::shared_ptr<rArmCurve_Tanks>& theTanks
			)
			{
				theTanks_ = theTanks;
			}

			void SetAuCurve
			(
				std::shared_ptr<HydStatic_rAuCurve>&& theCurve
			)
			{
				theAuCurve_ = std::move(theCurve);
			}

			void SetAuCurve
			(
				const std::shared_ptr<HydStatic_rAuCurve>& theCurve
			)
			{
				theAuCurve_ = theCurve;
			}

		public:

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

			Standard_Boolean HasAuCurve() const
			{
				return (Standard_Boolean)theAuCurve_;
			}

			Standard_Boolean IsEffective() const override
			{
				return Standard_True;
			}

			const auto& AuCurve() const
			{
				return theAuCurve_;
			}		

			const auto& Body() const
			{
				return theBody_;
			}

			

			/*const auto& TCG() const
			{
				return theTCG_;
			}*/

			/*auto& ChangeTCG()
			{
				return theTCG_;
			}*/

			/*const auto& GGt() const
			{
				return theGGt_;
			}*/

			/*auto& ChangeGGt()
			{
				return theGGt_;
			}*/

			/*const auto& GGv() const
			{
				return theGGv_;
			}*/

			/*auto& ChangeGGv()
			{
				return theGGv_;
			}*/

			const auto& Tanks() const
			{
				return theTanks_;
			}

			

			

			/*void SetTCG
			(
				const std::shared_ptr<rArmCurve_TCG>&& theTCG
			)
			{
				theTCG_ = std::move(theTCG);
			}*/

			/*void SetGGt
			(
				const std::shared_ptr<rArmCurve_GGt>&& theGGt
			)
			{
				theGGt_ = std::move(theGGt);
			}*/

			/*void SetGGv
			(
				const std::shared_ptr<rArmCurve_GGv>&& theGGv
			)
			{
				theGGv_ = std::move(theGGv);
			}*/

			

			std::shared_ptr<HydStatic_rArmCurve>
				ExpandToPort() const override;
		};
	}
}

#endif // !_HydStatic_rArmCurve_Eff_Header
