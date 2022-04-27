#pragma once
#ifndef _Mesh_PlnCurve_Header
#define _Mesh_PlnCurve_Header

#include <Global_Indexed.hxx>
#include <Mesh_Module.hxx>
#include <Mesh_PlnCurve_Base.hxx>
#include <Mesh_PlnCurve_Traits.hxx>
#include <Geo_MetricPrcsr.hxx>
#include <Entity_Polygon.hxx>

#include <Standard_Handle.hxx>

namespace tnbLib
{

	// Forward Declarations [4/15/2022 Amir]
	class Pnt2d;

	template<class CurveType, class SizeFun, class MetricFun = void>
	class Mesh_PlnCurve
		: public Mesh_PlnCurve_Base
		, public Global_Indexed
	{

	public:

		typedef Geo_MetricPrcsr<SizeFun, MetricFun> metricMap;
		typedef typename Mesh_PlnCurve_Traits<CurveType>::ptType Point;

	private:

		/*Private Data*/


		std::shared_ptr<CurveType> theCurve_;
		std::shared_ptr<Entity_Polygon<Point>> theMesh_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			Info << "WARNING! This function is not supposed to be called." << endl;
			NotImplemented;
		}

	public:

		typedef typename Mesh_PlnCurve_Traits<CurveType>::geomType geomType;
		typedef Mesh_PlnCurve_Base base;
		typedef CurveType curveType;


		//- default constructor

		Mesh_PlnCurve()
		{}


		//- constructors

		explicit Mesh_PlnCurve
		(
			const std::shared_ptr<CurveType>& theCurve
		)
			: theCurve_(theCurve)
		{}

		explicit Mesh_PlnCurve
		(
			std::shared_ptr<CurveType>&& theCurve
		)
			: theCurve_(std::move(theCurve))
		{}

		Mesh_PlnCurve
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<CurveType>& theCurve
		)
			: Global_Indexed(theIndex)
			, theCurve_(theCurve)
		{}


		// virtual functions and operators [4/25/2022 Amir]

		virtual Standard_Boolean IsSingular() const;
		virtual void OrientWith(const std::shared_ptr<Mesh_PlnCurve>&);

		//- public functions and operators

		Handle(geomType) Geometry() const;

	 	Standard_Real FirstParameter() const;
		Standard_Real LastParameter() const;

		Pnt2d Value(const Standard_Real) const;
		Pnt2d FirstCoord() const;
		Pnt2d LastCoord() const;

		virtual Standard_Real 
			CalcCharLength
			(
				const Pnt2d&, 
				const Pnt2d&, 
				const std::shared_ptr<metricMap>&
			) const;

		virtual Pnt2d 
			CalcCentre
			(
				const Pnt2d&, 
				const Pnt2d&, 
				const std::shared_ptr<metricMap>&
			) const;

		std::pair<Pnt2d, Pnt2d> BoundCoords() const;
		std::pair<Standard_Real, Standard_Real> Bounds() const;

		const auto& Curve() const
		{
			return theCurve_;
		}

		std::shared_ptr<Entity2d_Polygon> Discrete
		(
			const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo
		) const;

		virtual std::shared_ptr<Entity2d_Polygon> Mesh
		(
			const std::shared_ptr<metricMap>& theMetricMap,
			const std::shared_ptr<Mesh_Curve_Info>& theInfo
		) const;


		void SetCurve(const std::shared_ptr<CurveType>& theCurve)
		{
			theCurve_ = theCurve;
		}

		void SetMesh(const std::shared_ptr<Entity_Polygon<Point>>& theMesh)
		{
			theMesh_ = theMesh;
		}

		void SetMesh(std::shared_ptr<Entity_Polygon<Point>>&& theMesh)
		{
			theMesh_ = std::move(theMesh);
		}

		void Reverse();

		//- static functions

		template<class EdgeType, class PlnCurve>
		static std::vector<std::shared_ptr<EdgeType>> TopoMesh
		(
			const std::shared_ptr<PlnCurve>& theCurve,
			const std::shared_ptr<metricMap>& theMetricMap,
			const std::shared_ptr<Mesh_Curve_Info>& theInfo
		);

	};
}

#include <Mesh_PlnCurveI.hxx>

#endif // !_Mesh_PlnCurve_Header
