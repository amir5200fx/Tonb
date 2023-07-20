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

		void CalcLR();
		void CalcFircResist();
		void CalcTransomPressResist();
		void CalcCorrlResist();
		void CalcWaveResist();
		void CalcCoeffs();
		void CalcFrouds();

	public:

		// default constructor [7/2/2023 Payvand]

		HydDyna_Holtrop()
		{}


		// constructors [7/2/2023 Payvand]


		// Public functions and operators [7/2/2023 Payvand]

		const auto& Ship() const
		{
			return theShip_;
		}

		auto Velocity() const { return theVelocity_; }
		auto Density() const { return theDensity_; }
		auto Viscosity() const { return theViscosity_; }
		auto Gravity() const { return theGravity_; }

	};
}

#endif // !_HydDyna_Holtrop_Header
