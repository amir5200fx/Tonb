#pragma once
#ifndef _VoyageFun_CostFunction_Resistane_Header
#define _VoyageFun_CostFunction_Resistane_Header

#include <VoyageFun_CostFunction.hxx>
#include <Voyage_Module.hxx>
#include <Vec2d.hxx>

namespace tnbLib
{
	// Forward Declarations
	class VoyageFun_Resistance;

	class VoyageFun_CostFunction_Resistane
		: public VoyageFun_CostFunction
	{

	public:

		typedef std::function<std::pair<Standard_Real, Standard_Real>
			(const Pnt2d&, const Standard_Real)>
			VelFun;

	private:

		/*Private Data*/

		Standard_Integer theNbSamples_;
		Standard_Real theDist_;
		Standard_Real theShipVel_;

		std::shared_ptr<VoyageFun_Resistance> theResist_;
		VelFun theVelocity_;

		// Private functions

		TnbVoyage_EXPORT std::pair<Standard_Real, Standard_Real>
			CalcAvgVelocity(const State& theState0, const State& theState1) const;
		static TnbVoyage_EXPORT Vec2d ShipDirect(const Pnt2d&, const Pnt2d&);
		

	public:

		// default construtor

		TnbVoyage_EXPORT VoyageFun_CostFunction_Resistane
		(
			const VelFun& theVelFun, 
			const std::shared_ptr<VoyageFun_Resistance>& theResistFun
		);

		// constructors

		// Public funtions and operators

		auto NbSamples() const { return theNbSamples_; }
		auto Distance() const { return theDist_; }
		auto ShipVel() const { return theShipVel_; }

		TnbVoyage_EXPORT Standard_Real
			Value(const State& theState0, const State& theState1) const override;

		void SetNbSamples(const Standard_Integer theNb) { theNbSamples_ = theNb; }
		void SetDistance(const Standard_Real theDist) { theDist_ = theDist; }
		void SetShipVel(const Standard_Real theVel) { theShipVel_ = theVel; }
		
	};
	
}

#endif
