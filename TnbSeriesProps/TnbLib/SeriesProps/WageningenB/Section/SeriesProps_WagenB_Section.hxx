#pragma once
#ifndef _SeriesProps_WagenB_Section_Header
#define _SeriesProps_WagenB_Section_Header

#include <SeriesProps_Module.hxx>
#include <Geo2d_AirfoilFaceFwd.hxx>
#include <Geo2d_AirfoilBackFwd.hxx>
#include <Global_Done.hxx>

#include <Standard_TypeDef.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations [4/28/2022 Amir]
	class Geo_xDistb;

	class SeriesProps_WagenB_Section
		: public Global_Done
	{

		/*Private Data*/


		// inputs [4/28/2022 Amir]

		std::shared_ptr<Geo_xDistb> theDistb_;

		Standard_Real theLeadThick_;
		Standard_Real theTrailThick_;
		Standard_Real theMaxThick_;

		Standard_Real theRadius_;

		// outputs [4/28/2022 Amir]

		std::shared_ptr<Geo2d_AirfoilFace> theFace_;
		std::shared_ptr<Geo2d_AirfoilBack> theBack_;


		// private functions and operators [4/28/2022 Amir]

		auto& FaceSurfaceRef()
		{
			return theFace_;
		}

		auto& BackSurfaceRef()
		{
			return theBack_;
		}

	public:

		// default constructor [4/28/2022 Amir]

		SeriesProps_WagenB_Section()
			: theLeadThick_(0)
			, theTrailThick_(0)
			, theMaxThick_(0)
			, theRadius_(0)
		{}


		// constructors [4/28/2022 Amir]

		explicit SeriesProps_WagenB_Section
		(
			const std::shared_ptr<Geo_xDistb>& theFun
		)
			: theDistb_(theFun)
			, theLeadThick_(0)
			, theTrailThick_(0)
			, theMaxThick_(0)
			, theRadius_(0)
		{}

		SeriesProps_WagenB_Section
		(
			const std::shared_ptr<Geo_xDistb>& theFun,
			const Standard_Real theLET,
			const Standard_Real theTET, 
			const Standard_Real theMaxT,
			const Standard_Real rPerR
		)
			: theDistb_(theFun)
			, theLeadThick_(theLET)
			, theTrailThick_(theTET)
			, theMaxThick_(theMaxT)
			, theRadius_(rPerR)
		{}

		// public functions and operators [4/28/2022 Amir]

		const auto& DistbFun() const
		{
			return theDistb_;
		}

		auto LeadingThick() const
		{
			return theLeadThick_;
		}

		auto TrailingThick() const
		{
			return theTrailThick_;
		}

		auto MaxThick() const
		{
			return theMaxThick_;
		}

		auto Radius() const
		{
			return theRadius_;
		}

		const auto& FaceSurface() const
		{
			return theFace_;
		}

		const auto& BackSurface() const
		{
			return theBack_;
		}

		TnbSeriesProps_EXPORT void Perform();

		void SetDistbFun(const std::shared_ptr<Geo_xDistb>& theFun)
		{
			theDistb_ = theFun;
		}

		void SetLeadingThick(const Standard_Real theValue)
		{
			theLeadThick_ = theValue;
		}

		void SetTrailingThick(const Standard_Real theValue)
		{
			theTrailThick_ = theValue;
		}

		void SetMaxThick(const Standard_Real theValue)
		{
			theMaxThick_ = theValue;
		}

		void SetRadius(const Standard_Real rPerR)
		{
			theRadius_ = rPerR;
		}
	};
}

#endif // !_SeriesProps_WagenB_Section_Header
