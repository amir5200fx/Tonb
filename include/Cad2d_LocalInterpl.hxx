#pragma once
#ifndef _Cad2d_LocalInterpl_Header
#define _Cad2d_LocalInterpl_Header

#include <Cad2d_Module.hxx>
#include <Pnt2d.hxx>
#include <Global_Done.hxx>
#include <Global_TypeDef.hxx>

#include <vector>

class Geom2d_Curve;

namespace tnbLib
{

	// Forward Declarations
	class Cad2d_InterpUbarMap;

	class Cad2d_LocalInterpl
		: public Global_Done
	{

	public:

		enum class neighborType
		{
			threePoint = 0,
			fivePoint
		};

		enum class continuity
		{
			G1 = 0,
			C1
		};

	private:

		/*Private Data*/

		const std::vector<Pnt2d>& theQ_;

		std::shared_ptr<Cad2d_InterpUbarMap> theMap_;

		neighborType theType_;
		continuity theContinuity_;

		Standard_Real theTol_;
		Standard_Real theAlfa_;

		Handle(Geom2d_Curve) theCurve_;

	public:

		//- default constructor


		//- constructors

		TnbCad2d_EXPORT Cad2d_LocalInterpl
		(
			const std::vector<Pnt2d>& theQ
		);

		TnbCad2d_EXPORT Cad2d_LocalInterpl
		(
			const std::vector<Pnt2d>& theQ,
			const std::shared_ptr<Cad2d_InterpUbarMap>& theMap
		);


		//- public functions and operators

		const auto& Qs() const
		{
			return theQ_;
		}

		const auto& UbarMap() const
		{
			return theMap_;
		}

		TnbCad2d_EXPORT const Handle(Geom2d_Curve)& Curve() const;

		auto NeighborType() const
		{
			return theType_;
		}

		auto Continuity() const
		{
			return theContinuity_;
		}

		auto Tolerance() const
		{
			return theTol_;
		}

		auto Alpha() const
		{
			return theAlfa_;
		}

		TnbCad2d_EXPORT void Perform();

		TnbCad2d_EXPORT void SetUbarMap(const std::shared_ptr<Cad2d_InterpUbarMap>&);

		TnbCad2d_EXPORT void SetType(const neighborType);
		TnbCad2d_EXPORT void SetContinuity(const continuity);
		TnbCad2d_EXPORT void SetAlpha(const Standard_Real);
		TnbCad2d_EXPORT void SetTolerance(const Standard_Real);

	};
}

#endif // !_Cad2d_LocalInterpl_Header
