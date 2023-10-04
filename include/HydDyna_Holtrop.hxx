#pragma once
#ifndef _HydDyna_Holtrop_Header
#define _HydDyna_Holtrop_Header

#include <HydDyna_Holtrop_Veriables.hxx>
#include <Global_Done.hxx>

#include <memory>

namespace tnbLib
{

	class HydDyna_Holtrop
		: public Global_Done
	{

		/*Private Data*/

		Standard_Real theVelocity_;
		Standard_Real theDensity_;
		Standard_Real theViscosity_;
		Standard_Real theGravity_;

		std::shared_ptr<holtropLib::ShipPrincipals> theShip_;

		holtropLib::HoltropCoeffs theCoeffs_;
		holtropLib::Froudes theFroudes_;
		holtropLib::HoltropResistance theResist_;

		Standard_Real theLR_;

		// Private functions and operators [7/2/2023 Payvand]

		TnbHydDyna_EXPORT void CalcLR();
		TnbHydDyna_EXPORT void CalcFircResist();
		TnbHydDyna_EXPORT void CalcTransomPressResist();
		TnbHydDyna_EXPORT void CalcCorrlResist();
		TnbHydDyna_EXPORT void CalcWaveResist();
		TnbHydDyna_EXPORT void CalcCoeffs();
		TnbHydDyna_EXPORT void CalcFrouds();

	public:

		// default constructor [7/2/2023 Payvand]

		HydDyna_Holtrop()
		{}


		// constructors [7/2/2023 Payvand]

		HydDyna_Holtrop
		(
			const std::shared_ptr<holtropLib::ShipPrincipals>& theShip, 
			const Standard_Real theVel, 
			const Standard_Real theDensity,
			const Standard_Real theViscosity, 
			const Standard_Real theGravity
		)
			: theShip_(theShip)
			, theVelocity_(theVel)
			, theDensity_(theDensity)
			, theViscosity_(theViscosity)
			, theGravity_(theGravity)
		{}

		HydDyna_Holtrop
		(
			std::shared_ptr<holtropLib::ShipPrincipals>&& theShip,
			const Standard_Real theVel,
			const Standard_Real theDensity,
			const Standard_Real theViscosity,
			const Standard_Real theGravity
		)
			: theShip_(std::move(theShip))
			, theVelocity_(theVel)
			, theDensity_(theDensity)
			, theViscosity_(theViscosity)
			, theGravity_(theGravity)
		{}

		// Public functions and operators [7/2/2023 Payvand]

		const auto& Ship() const
		{
			return theShip_;
		}

		void Perform();

		auto Velocity() const { return theVelocity_; }
		auto Density() const { return theDensity_; }
		auto Viscosity() const { return theViscosity_; }
		auto Gravity() const { return theGravity_; }

		void SetShip(const std::shared_ptr<holtropLib::ShipPrincipals>& theShip) { theShip_ = theShip; }
		void SetShip(std::shared_ptr<holtropLib::ShipPrincipals>&& theShip) { theShip_ = std::move(theShip); }

		void SetVelocity(const Standard_Real theVelocity) { theVelocity_ = theVelocity; }
		void SetDensity(const Standard_Real theDensity) { theDensity_ = theDensity; }
		void SetViscosity(const Standard_Real theViscosity) { theViscosity_ = theViscosity; }
		void SetGravity(const Standard_Real theGravity) { theGravity_ = theGravity; }

	};
}

#endif // !_HydDyna_Holtrop_Header
