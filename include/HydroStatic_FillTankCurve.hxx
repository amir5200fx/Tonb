#pragma once
#ifndef _HydroStatic_FillTankCurve_Header
#define _HydroStatic_FillTankCurve_Header

#include <Global_Done.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class CrossSection_xShapeStation;
	class Marine_Graph;
	class Marine_Domain;
	class Geo_xDistb;

	class HydroStatic_FillTankCurve
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Marine_Domain> theDomain_;
		std::shared_ptr<CrossSection_xShapeStation> theTank_;
		std::shared_ptr<Geo_xDistb> theFillLine_;

		std::shared_ptr<Marine_Graph> theGraph_;


		auto& ChangeGraph()
		{
			return theGraph_;
		}

	public:

		HydroStatic_FillTankCurve();

		const auto& Domain() const
		{
			return theDomain_;
		}

		const auto& Tank() const
		{
			return theTank_;
		}

		const auto& Lines() const
		{
			return theFillLine_;
		}

		const auto& Graph() const
		{
			return theGraph_;
		}

		void Perform();

		void LoadTank
		(
			const std::shared_ptr<CrossSection_xShapeStation>& theTank
		)
		{
			theTank_ = theTank;
		}

		void LoadLines
		(
			const std::shared_ptr<Geo_xDistb>& theLines
		)
		{
			theFillLine_ = theLines;
		}
	};
}

#endif // !_HydroStatic_FillTankCurve_Header
