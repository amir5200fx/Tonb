#pragma once
#ifndef _HydStatic_FillTank_Header
#define _HydStatic_FillTank_Header

#include <Global_Done.hxx>
#include <Marine_BodiesFwd.hxx>
#include <HydStatic_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Geo_xDistb;
	class Marine_Domain;
	class HydStatic_FillCurveQ;

	class HydStatic_FillTank
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Marine_Domain> theDomain_;
		std::shared_ptr<marineLib::Body_Tank> theTank_;

		Standard_Integer theNbWaters_;


		std::shared_ptr<HydStatic_FillCurveQ> theCurve_;

	public:

		static TnbHydStatic_EXPORT Standard_Real DELTA_WATER_COEFF;
		static TnbHydStatic_EXPORT unsigned short verbose;

		HydStatic_FillTank()
		{}

		HydStatic_FillTank
		(
			const std::shared_ptr<Marine_Domain>& theDomain,
			const std::shared_ptr<marineLib::Body_Tank>& theTank,
			const Standard_Integer nbWaters
		)
			: theDomain_(theDomain)
			, theTank_(theTank)
			, theNbWaters_(nbWaters)
		{}


		//- public functions and operators

		const auto& Domain() const
		{
			return theDomain_;
		}

		const auto& Tank() const
		{
			return theTank_;
		}

		const auto& Curve() const
		{
			return theCurve_;
		}

		auto NbWaters() const
		{
			return theNbWaters_;
		}

		TnbHydStatic_EXPORT void Perform();

		void LoadDomain(const std::shared_ptr<Marine_Domain>& theDomain)
		{
			theDomain_ = theDomain;
		}

		void LoadTank(const std::shared_ptr<marineLib::Body_Tank>& theTank)
		{
			theTank_ = theTank;
		}

		void SetNbWaters(const Standard_Integer nbWaters)
		{
			theNbWaters_ = nbWaters;
		}

		static TnbHydStatic_EXPORT std::shared_ptr<Geo_xDistb> 
			Z
			(
				const Standard_Real z0,
				const Standard_Real z1,
				const Standard_Integer n
			);
	};
}

#endif // !_HydStatic_FillTank_Header
