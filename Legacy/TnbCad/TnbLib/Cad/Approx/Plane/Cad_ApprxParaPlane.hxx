#pragma once
#ifndef _Cad_ApprxParaPlane_Header
#define _Cad_ApprxParaPlane_Header

#include <Cad_ApprxWire.hxx>
#include <Cad_ApprxParaPlaneTraits.hxx>
#include <Cad_Module.hxx>

namespace tnbLib
{

	template<class PlnType, bool RandSamples>
	class Cad_ApprxParaPlane
		: public Global_Done
	{

	public:

		typedef typename cad_apprx_plane_traits<PlnType>::wireType wireType;
		typedef typename cad_apprx_wire_traits<wireType>::curveType curveType;
		typedef typename Cad_ApprxCurve<curveType, RandSamples>::Point Point;

	private:

		/*Private Data*/

		// inputs [4/18/2022 Amir]
		std::shared_ptr<PlnType> thePlane_;
		std::shared_ptr<Geo_ApprxCurve_Info> theInfo_;

		// outputs [4/18/2022 Amir]
		std::vector<std::shared_ptr<Entity_Polygon<Point>>> thePolygons_;


		// private functions and operators [4/18/2022 Amir]

		auto& PolygonsRef()
		{
			return thePolygons_;
		}

		static std::vector<std::shared_ptr<wireType>> RetrieveWires(const std::shared_ptr<PlnType>&);

	public:

		// default constructor [4/18/2022 Amir]

		Cad_ApprxParaPlane()
		{}

		// constructors [4/18/2022 Amir]

		Cad_ApprxParaPlane
		(
			const std::shared_ptr<PlnType>& thePlane, 
			const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo
		)
			: thePlane_(thePlane)
			, theInfo_(theInfo)
		{}

		// public functions and operators [4/18/2022 Amir]

		Standard_Integer NbPolygons() const;

		const auto& Plane() const
		{
			return thePlane_;
		}

		const auto& ApproxInfo() const
		{
			return theInfo_;
		}

		const auto& Polygons() const
		{
			return thePolygons_;
		}

		void Perform();

		void SetPlane(const std::shared_ptr<PlnType>& thePlane)
		{
			thePlane_ = thePlane;
		}

		void SetInfo(const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo)
		{
			theInfo_ = theInfo;
		}

	};
}

#include <Cad_ApprxParaPlaneI.hxx>

#endif // !_Cad_ApprxParaPlane_Header
