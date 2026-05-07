#pragma once
#ifndef _Cad_ApprxCurveOnSurface_Header
#define _Cad_ApprxCurveOnSurface_Header

#include <Cad_Module.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Global_Done.hxx>
#include <Global_TypeDef.hxx>
#include <Global_Handle.hxx>

#include <memory>

class Geom2d_Curve;
class Geom_Surface;


namespace tnbLib
{

	// Forward Declarations [4/18/2022 Amir]
	class Geo_ApprxCurve_Info;

	class Cad_ApprxCurveOnSurface
		: public Global_Done
	{

		/*Private Data*/

		// inputs [4/17/2022 Amir]
		Handle(Geom_Surface) theSurface_;
		Handle(Geom2d_Curve) thePara_;

		Standard_Real theFirstParameter_;
		Standard_Real theLastParameter_;

		std::shared_ptr<Geo_ApprxCurve_Info> theInfo_;

		// outputs [4/17/2022 Amir]
		std::shared_ptr<Entity2d_Polygon> theApprox_;


		// private functions and operators [4/17/2022 Amir]

		auto& ApproxRef()
		{
			return theApprox_;
		}

	public:

		// default constructor [4/17/2022 Amir]

		Cad_ApprxCurveOnSurface()
		{}


		// constructors [4/17/2022 Amir]

		Cad_ApprxCurveOnSurface
		(
			const Handle(Geom_Surface)& theSurf,
			const Handle(Geom2d_Curve)& thePara,
			const Standard_Real theFirst,
			const Standard_Real theLast,
			const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo
		)
			: theSurface_(theSurf)
			, thePara_(thePara)
			, theFirstParameter_(theFirst)
			, theLastParameter_(theLast)
			, theInfo_(theInfo)
		{}

		// public functions and operators [4/17/2022 Amir]

		const auto& Surface() const
		{
			return theSurface_;
		}

		const auto& ParaCurve() const
		{
			return thePara_;
		}

		auto FirstParameter() const
		{
			return theFirstParameter_;
		}

		auto LastParameter() const
		{
			return theLastParameter_;
		}

		const auto& ApproxInfo() const
		{
			return theInfo_;
		}

		const auto& Approx() const
		{
			return theApprox_;
		}

		TnbCad_EXPORT void Perform();

		void SetSurface(const Handle(Geom_Surface)& theSurf)
		{
			theSurface_ = theSurf;
		}

		void SetApproxInfo(const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo)
		{
			theInfo_ = theInfo;
		}

		TnbCad_EXPORT void SetParaCurve
		(
			const Handle(Geom2d_Curve)& thePara, 
			const Standard_Real theFirst, 
			const Standard_Real theLast
		);

	};
}

#endif // !_Cad_ApprxCurveOnSurface_Header
