#pragma once
#ifndef _HydStatic_Tools_Header
#define _HydStatic_Tools_Header

#include <Standard_TypeDef.hxx>
#include <Marine_xSectionParam.hxx>
#include <Marine_VesselParam_KG.hxx>
#include <HydStatic_rArmCurves.hxx>
#include <HydStatic_Module.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	namespace marineLib { struct xSectionParam; }

	// Forward Declarations
	class TModel_Surface;
	class HydStatic_GzQ;
	class HydStatic_GzQP;
	class HydStatic_rArmCurve;
	class HydStatic_hArmCurve;
	class HydStatic_AuCurve;
	class HydStatic_rAuCurve;
	class NumAlg_AdaptiveInteg_Info;
	class Pnt2d;

	namespace hydStcLib { class rArmCurve_Eff; }

	class HydStatic_Tools
	{

	public:

		typedef NumAlg_AdaptiveInteg_Info info;

		static TnbHydStatic_EXPORT std::shared_ptr<HydStatic_hArmCurve> 
			HeelingCurve
			(
				const std::vector<HydStatic_GzQP>& theQs
			);

		static TnbHydStatic_EXPORT std::shared_ptr<HydStatic_hArmCurve> 
			HeelingCurve
			(
				const std::vector<HydStatic_GzQP>&& theQs
			);

		static TnbHydStatic_EXPORT std::vector<HydStatic_GzQ> 
			MirroredByO
			(
				const std::vector<HydStatic_GzQ>& theQs
			);

		static TnbHydStatic_EXPORT std::vector<HydStatic_GzQP> 
			MirroredByO
			(
				const std::vector<HydStatic_GzQP>& theQs
			);

		static TnbHydStatic_EXPORT std::vector<HydStatic_GzQ> 
			MirroredByOy
			(
				const std::vector<HydStatic_GzQ>& theQs
			);

		static TnbHydStatic_EXPORT std::vector<HydStatic_GzQP> 
			MirroredByOy
			(
				const std::vector<HydStatic_GzQP>& theQs
			);

		static TnbHydStatic_EXPORT std::vector<HydStatic_GzQ> 
			Merged
			(
				const std::vector<HydStatic_GzQ>& theQs
			);

		/*WARNING: the parameter for GzQP is set to zero after merging!*/
		static TnbHydStatic_EXPORT std::vector<HydStatic_GzQP> 
			Merged
			(
				const std::vector<HydStatic_GzQP>& theQs
			);

		static TnbHydStatic_EXPORT std::shared_ptr<hydStcLib::rArmCurve_Body> 
			ExpandToPort
			(
				const std::shared_ptr<hydStcLib::rArmCurve_Body>& theGZ
			);

		static TnbHydStatic_EXPORT std::shared_ptr<hydStcLib::rArmCurve_FSLq> 
			ExpandToPort
			(
				const std::shared_ptr<hydStcLib::rArmCurve_FSLq>& theGz
			);

		static TnbHydStatic_EXPORT std::shared_ptr<hydStcLib::rArmCurve_Hlds> 
			ExpandToPort
			(
				const std::shared_ptr<hydStcLib::rArmCurve_Hlds>& theGZ
			);

		static TnbHydStatic_EXPORT std::shared_ptr<hydStcLib::rArmCurve_LDT> 
			ExpandToPort
			(
				const std::shared_ptr<hydStcLib::rArmCurve_LDT>& theGZ
			);

		static TnbHydStatic_EXPORT std::shared_ptr<hydStcLib::rArmCurve_LDV> 
			ExpandToPort
			(
				const std::shared_ptr<hydStcLib::rArmCurve_LDV>& theGZ
			);

		static std::shared_ptr<HydStatic_rArmCurve> ExpandRigthingArmToPort(const HydStatic_rArmCurve& theCurve, const marineLib::KG& theKG)
		{
			NotImplemented;
			return std::shared_ptr<HydStatic_rArmCurve>();
		}

		static std::vector<marineLib::xSectionParam> OffsetsFrom(const std::vector<HydStatic_GzQ>& theQs)
		{
			NotImplemented;
			return std::vector<marineLib::xSectionParam>();
		}

		static std::vector<marineLib::xSectionParam> OffsetsFrom(const std::vector<HydStatic_GzQP>& theQs)
		{
			NotImplemented;
			return std::vector<marineLib::xSectionParam>();
		}

		static TnbHydStatic_EXPORT void
			AuCurve
			(
				const std::shared_ptr<hydStcLib::rArmCurve_Eff>& theCurve, 
				const Standard_Real y0, 
				const std::shared_ptr<info>& theInfo
			);

		static TnbHydStatic_EXPORT void
			AuCurve
			(
				const std::shared_ptr<HydStatic_hArmCurve>& theCurve,
				const Standard_Real y0,
				const std::shared_ptr<info>& theInfo
			);
	};
}

#endif // !_HydStatic_Tools_Header
