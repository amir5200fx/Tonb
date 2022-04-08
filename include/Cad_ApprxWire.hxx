#pragma once
#ifndef _Cad_ApprxWire_Header
#define _Cad_ApprxWire_Header

#include <Cad_ApprxCurve.hxx>
#include <Cad_ApprxWireTraits.hxx>
#include <Entity2d_PolygonFwd.hxx>

#include <vector>

namespace tnbLib
{

	template<class WireType, bool RandSamples>
	class Cad_ApprxWire
		: public Global_Done
	{

	public:

		typedef typename cad_apprx_wire_traits<WireType>::curveType curveType;
		typedef typename Cad_ApprxCurve<curveType, RandSamples>::Point Point;

	private:

		/*Private Data*/


		// inputs [4/4/2022 Amir]
		std::shared_ptr<WireType> theWire_;
		std::shared_ptr<Geo_ApprxCurve_Info> theInfo_;

		// outputs [4/4/2022 Amir]	
		std::vector<std::shared_ptr<Entity_Polygon<Point>>> thePolygons_;


		// private functions and operators [4/4/2022 Amir]


		auto& PolygonsRef()
		{
			return thePolygons_;
		}

		static std::vector<std::shared_ptr<curveType>> RetrieveCurves(const WireType&);

	public:

		// default constructor [4/4/2022 Amir]

		Cad_ApprxWire()
		{}


		// constructors [4/4/2022 Amir]

		Cad_ApprxWire
		(
			const std::shared_ptr<WireType>& theWire,
			const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo
		)
			: theWire_(theWire)
			, theInfo_(theInfo)
		{}


		// public functions and operators [4/4/2022 Amir]

		Standard_Integer NbPolygons() const;

		const auto& Wire() const
		{
			return theWire_;
		}

		const auto& AlgInfo() const
		{
			return theInfo_;
		}

		const auto& Polygons() const
		{
			return thePolygons_;
		}

		void Perform();

		void SetWire(const std::shared_ptr<WireType>& theWire)
		{
			theWire_ = theWire;
		}

		void SetInfo(const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo)
		{
			theInfo_ = theInfo;
		}


	};
}

#include <Cad_ApprxWireI.hxx>

#endif // !_Cad_ApprxWire_Header
