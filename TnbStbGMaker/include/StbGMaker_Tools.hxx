#pragma once
#ifndef _StbGMaker_Tools_Header
#define _StbGMaker_Tools_Header

#include <Standard_TypeDef.hxx>

#include <memory>
#include <vector>

class gp_Pln;

namespace tnbLib
{

	// Forward Declarations
	class StbGMaker_Tank;
	class StbGMaker_Hull;
	class StbGMaker_IntplSect;
	class StbGMaker_WP;
	class Marine_CmpSection;
	class Marine_Body;
	class Pln_Wire;

	class StbGMaker_Tools
	{

	public:

		static Standard_Real MinX(const Marine_Body& theBody);

		static Standard_Real MaxX(const Marine_Body& theBody);

		static gp_Pln 
			IntplPln
			(
				const Standard_Real x,
				const std::shared_ptr<Marine_CmpSection>& theS0,
				const std::shared_ptr<Marine_CmpSection>& theS1
			);

		static std::shared_ptr<Marine_CmpSection> 
			IntplHullSection
			(
				const gp_Pln& thePlane, 
				const std::shared_ptr<Marine_CmpSection>& theS0, 
				const std::shared_ptr<Marine_CmpSection>& theS1,
				const std::shared_ptr<StbGMaker_IntplSect>& theIntrpl
			);

		static std::tuple
			<
			std::shared_ptr<Marine_CmpSection>,
			std::shared_ptr<Marine_CmpSection>
			>
			FindSpan
			(
				const Standard_Real x, 
				const Marine_Body& theBody
			);

		static std::tuple
			<
			std::shared_ptr<Marine_CmpSection>,
			std::shared_ptr<Marine_CmpSection>
			>
			FindSpan
			(
				const Standard_Real x, 
				const StbGMaker_Hull& theHull
			);

		static std::vector<std::shared_ptr<Pln_Wire>> OuterWires(const std::shared_ptr<StbGMaker_WP>& theWp);

		template<class SectionType>
		static std::shared_ptr<Marine_CmpSection> Section(const std::shared_ptr<StbGMaker_WP>& theWp);

		template<class SectionType>
		static std::vector<std::shared_ptr<Marine_CmpSection>> RetrieveSections(const std::vector<std::shared_ptr<StbGMaker_WP>>& theWps);

		static std::shared_ptr<Marine_CmpSection> FitTankSectionToHull(const std::shared_ptr<Marine_CmpSection>& theSection, const std::shared_ptr<Marine_CmpSection>& theSHull0, const std::shared_ptr<Marine_CmpSection>& theSHull1, const std::shared_ptr<StbGMaker_IntplSect>& theIntrpl);

		static std::shared_ptr<StbGMaker_Tank> FitTankToHull(const StbGMaker_Tank& theTank, const StbGMaker_Hull& theHull, const std::shared_ptr<StbGMaker_IntplSect>& theIntrpl);

		static void CheckOutsideBoundaries(const Standard_Real x, const Marine_Body& theBody, const char* theFunName);

		static void CheckSameDirection(const std::shared_ptr<Marine_CmpSection>& theS0, const std::shared_ptr<Marine_CmpSection>& theS1, const char* theNameFun);
	};
}

#include <StbGMaker_ToolsI.hxx>

#endif // !_StbGMaker_Tools_Header
