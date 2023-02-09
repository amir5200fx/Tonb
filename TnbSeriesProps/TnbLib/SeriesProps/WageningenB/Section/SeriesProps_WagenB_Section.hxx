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

		Standard_Real theLeadThick_;
		Standard_Real theTrailThick_;
		Standard_Real theMaxThick_;

		Standard_Real theChord_;
		Standard_Real theA_;
		Standard_Real theB_;

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
			, theChord_(0)
			, theA_(0)
			, theB_(0)
		{}


		// constructors [4/28/2022 Amir]

		SeriesProps_WagenB_Section
		(
			const Standard_Real theLET,
			const Standard_Real theTET, 
			const Standard_Real theMaxT,
			const Standard_Real theChord,
			const Standard_Real theA,
			const Standard_Real theB,
			const Standard_Real rPerR
		)
			: theLeadThick_(theLET)
			, theTrailThick_(theTET)
			, theMaxThick_(theMaxT)
			, theChord_(theChord)
			, theA_(theA)
			, theB_(theB)
			, theRadius_(rPerR)
		{}


		// public functions and operators [4/28/2022 Amir]


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

		auto Chord() const
		{
			return theChord_;
		}

		auto A() const
		{
			return theA_;
		}

		auto B() const
		{
			return theB_;
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

		TnbSeriesProps_EXPORT void Perform(const std::shared_ptr<Geo_xDistb>& theDistb);

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

		void SetChord(const Standard_Real theChord)
		{
			theChord_ = theChord;
		}

		void SetA(const Standard_Real theA)
		{
			theA_ = theA;
		}

		void SetB(const Standard_Real theB)
		{
			theB_ = theB;
		}
	};
}

#endif // !_SeriesProps_WagenB_Section_Header
