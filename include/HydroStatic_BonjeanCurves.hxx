#pragma once
#ifndef _HydroStatic_BonjeanCurves_Header
#define _HydroStatic_BonjeanCurves_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Global_Done.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class CrossSection_xShapeStation;
	class Marine_Graph;
	class Marine_Domain;
	class Geo_xDistb;

	class HydroStatic_BonjeanCurves
		: public Global_Indexed
		, public Global_Named
		, public Global_Done
	{

		typedef std::vector<std::vector<Standard_Real>>
			tableOffset;

		/*Private Data*/

		std::shared_ptr<Marine_Domain> theDomain_;
		std::shared_ptr<CrossSection_xShapeStation> theModel_;
		std::shared_ptr<Geo_xDistb> theWaters_;

		std::vector<std::shared_ptr<Marine_Graph>> theArea_;

		auto& ChangeArea()
		{
			return theArea_;
		}

	public:

		HydroStatic_BonjeanCurves();

		HydroStatic_BonjeanCurves(const Standard_Integer theIndex);

		HydroStatic_BonjeanCurves(const Standard_Integer theIndex, const word& theName);


		const auto& Domain() const
		{
			return theDomain_;
		}

		const auto& Model() const
		{
			return theModel_;
		}

		const auto& Waters() const
		{
			return theWaters_;
		}

		const auto& AreaGraph() const
		{
			return theArea_;
		}

		void Perform();

		void LoadDomain
		(
			const std::shared_ptr<Marine_Domain>& theDomain
		)
		{
			theDomain_ = theDomain;
		}

		void LoadModel
		(
			const std::shared_ptr<CrossSection_xShapeStation>& theModel
		)
		{
			theModel_ = theModel;
		}

		void LoadWaters
		(
			const std::shared_ptr<Geo_xDistb>& theWaters
		)
		{
			theWaters_ = theWaters;
		}
	};
}

#endif // !_HydroStatic_BonjeanCurves_Header
