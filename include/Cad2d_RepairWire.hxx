#pragma once
#ifndef _Cad2d_RepairWire_Header
#define _Cad2d_RepairWire_Header

#include <Cad2d_Module.hxx>
#include <Global_Done.hxx>
#include <Global_Handle.hxx>

#include <vector>


class Geom2d_Curve;

namespace tnbLib
{

	// Forward Declarations [6/16/2022 Amir]
	class NumAlg_AdaptiveInteg_Info;

	class Cad2d_RepairWire
		: public Global_Done
	{

		/*Private Data*/

		// inputs [5/15/2022 Amir]

		std::vector<Handle(Geom2d_Curve)> theCurves_;

		Standard_Real theTol_;
		std::shared_ptr<NumAlg_AdaptiveInteg_Info> theIntegInfo_;

		// outputs [5/15/2022 Amir]

		std::vector<Handle(Geom2d_Curve)> theWire_;

		// private functions and operators [5/15/2022 Amir]

		
		auto& WireRef()
		{
			return theWire_;
		}

		
		TnbCad2d_EXPORT std::vector<Handle(Geom2d_Curve)> 
			RepairWire
			(
				const Handle(Geom2d_Curve)&, 
				const Handle(Geom2d_Curve)&
			);

		TnbCad2d_EXPORT std::vector<Handle(Geom2d_Curve)> 
			RepairWire
			(
				const std::vector<Handle(Geom2d_Curve)>& theCurves
			);

		TnbCad2d_EXPORT Handle(Geom2d_Curve) RetrieveGeometry(const Handle(Geom2d_Curve)&);

		TnbCad2d_EXPORT Handle(Geom2d_Curve) 
			RetrieveCurve
			(
				const Handle(Geom2d_Curve)&, 
				const Handle(Geom2d_Curve)&
			);

		TnbCad2d_EXPORT Handle(Geom2d_Curve) 
			RetrieveCurve
			(
				const Handle(Geom2d_Curve)&, 
				const Handle(Geom2d_Curve)&,
				const Handle(Geom2d_Curve)&
			);

		static TnbCad2d_EXPORT std::pair<Handle(Geom2d_Curve), Handle(Geom2d_Curve)> 
			Subdivide
			(
				const Handle(Geom2d_Curve)&,
				const Standard_Real x
			);

		static TnbCad2d_EXPORT std::pair<Handle(Geom2d_Curve), Handle(Geom2d_Curve)> 
			RepairIntersection
			(
				const Handle(Geom2d_Curve)& theC0, 
				const Handle(Geom2d_Curve)& theC1, 
				const Standard_Real theTol
			);

	public:

		static TnbCad2d_EXPORT const Standard_Real DEFAULT_TOLERANCE;
		static TnbCad2d_EXPORT const std::shared_ptr<NumAlg_AdaptiveInteg_Info> DEFAULT_INTEG_INFO;

		// default constructor [5/15/2022 Amir]

		Cad2d_RepairWire()
			: theTol_(DEFAULT_TOLERANCE)
			, theIntegInfo_(DEFAULT_INTEG_INFO)
		{}


		// constructors [5/15/2022 Amir]


		// public functions and operators [5/16/2022 Amir]

		const auto& Curves() const
		{
			return theCurves_;
		}

		const auto& IntegInfo() const
		{
			return theIntegInfo_;
		}

		auto Tolerance() const
		{
			return theTol_;
		}

		const auto& Wire() const
		{
			return theWire_;
		}

		TnbCad2d_EXPORT void Perform();

		void SetCurves(const std::vector<Handle(Geom2d_Curve)>& theCurves)
		{
			theCurves_ = theCurves;
		}

		void SetCurves(std::vector<Handle(Geom2d_Curve)>&& theCurves)
		{
			theCurves_ = std::move(theCurves);
		}

		void SetTolerance(const Standard_Real theTol)
		{
			theTol_ = theTol;
		}

		void OverrideIntegInfo(const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo)
		{
			theIntegInfo_ = theInfo;
		}
	};
}

#endif // !_Cad2d_RepairWire_Header
