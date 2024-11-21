#pragma once
#ifndef _Mesh_PlnGapCurve_Header
#define _Mesh_PlnGapCurve_Header

#include <Entity2d_PolygonFwd.hxx>
#include <Pnt2d.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [5/12/2022 Amir]
	class Geo_ApprxCurve_Info;
	class Mesh_Curve_Info;

	template<class CurveType>
	class Cad_PlnGapCurve
		: public CurveType
	{

		/*Private Data*/

		Pnt2d theMid_;


		// private functions and operators [5/13/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<CurveType>(*this);
			ar & theMid_;
		}

	public:

		typedef typename CurveType::curveType curveType;
		typedef typename CurveType::metricMap metricMap;

		// default constructor [5/12/2022 Amir]

		Cad_PlnGapCurve()
		{}

		// constructors [5/12/2022 Amir]


		explicit Cad_PlnGapCurve
		(
			const std::shared_ptr<curveType>& theCurve
		)
			: CurveType(theCurve)
		{}

		Cad_PlnGapCurve(std::shared_ptr<curveType>&& theCurve)
			: CurveType(std::move(theCurve))
		{}

		Cad_PlnGapCurve
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<curveType>& theCurve
		)
			: CurveType(theIndex, theCurve)
		{}

		Cad_PlnGapCurve
		(
			const Standard_Integer theIndex,
			std::shared_ptr<curveType>&& theCurve
		)
			: CurveType(theIndex, std::move(theCurve))
		{}

	public:

		// override functions and operators [5/12/2022 Amir]

		std::pair<std::shared_ptr<CurveType>, std::shared_ptr<CurveType>>
			Split(const Standard_Real x) const override;

		Standard_Boolean IsGap() const override
		{
			return Standard_True;
		}

		inline Standard_Real
			CalcCharLength
			(
				const Pnt2d&,
				const Pnt2d&,
				const std::shared_ptr<metricMap>&
			) const override;

		inline Pnt2d
			CalcCentre
			(
				const Pnt2d&,
				const Pnt2d&,
				const std::shared_ptr<metricMap>&
			) const override;

		inline std::shared_ptr<Entity2d_Polygon>
			Mesh
			(
				const std::shared_ptr<metricMap>& theMetricMap,
				const std::shared_ptr<Mesh_Curve_Info>& theInfo
			) const override;

		// public functions and operators [5/12/2022 Amir]

		const auto& MidCoord() const
		{
			return theMid_;
		}

		void SetMidCoord(const Pnt2d& theCoord)
		{
			theMid_ = theCoord;
		}

		void SetMidCoord(Pnt2d&& theCoord)
		{
			theMid_ = std::move(theCoord);
		}


		// static functions and operators [5/13/2022 Amir]

		template<class EdgeType, class PlnCurve>
		static std::vector<std::shared_ptr<EdgeType>> TopoMesh
		(
			const std::shared_ptr<PlnCurve>& theCurve,
			const std::shared_ptr<metricMap>& theMetricMap,
			const std::shared_ptr<Mesh_Curve_Info>& theInfo
		);

	};
}

#include <Cad_PlnGapCurveI.hxx>

#endif // !_Mesh_PlnGapCurve_Header
