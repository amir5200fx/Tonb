#pragma once
#ifndef _StbGMaker_Tools_Header
#define _StbGMaker_Tools_Header

#include <Standard_TypeDef.hxx>

#include <memory>

class gp_Pln;

namespace tnbLib
{

	// Forward Declarations
	class StbGMaker_Tank;
	class StbGMaker_Hull;
	class StbGMaker_IntplSect;
	class Marine_CmpSection;
	class Marine_Body;

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

		static std::shared_ptr<Marine_CmpSection> FitTankSectionToHull(const std::shared_ptr<Marine_CmpSection>& theSection, const std::shared_ptr<Marine_CmpSection>& theSHull0, const std::shared_ptr<Marine_CmpSection>& theSHull1, const std::shared_ptr<StbGMaker_IntplSect>& theIntrpl);

		static std::shared_ptr<StbGMaker_Tank> FitTankToHull(const StbGMaker_Tank& theTank, const StbGMaker_Hull& theHull, const std::shared_ptr<StbGMaker_IntplSect>& theIntrpl);

		static void CheckOutsideBoundaries(const Standard_Real x, const Marine_Body& theBody, const char* theFunName);

		static void CheckSameDirection(const std::shared_ptr<Marine_CmpSection>& theS0, const std::shared_ptr<Marine_CmpSection>& theS1, const char* theNameFun);
	};
}

#endif // !_StbGMaker_Tools_Header
