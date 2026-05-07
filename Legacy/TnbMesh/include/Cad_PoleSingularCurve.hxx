#pragma once
#ifndef _Cad_PoleSingularCurve_Header
#define _Cad_PoleSingularCurve_Header

#include <Cad_SingularCurve.hxx>
#include <Entity2d_Polygon.hxx>

namespace tnbLib
{

	template<class CurveType>
	class Cad_PoleSingularCurve
		: public Cad_SingularCurve<CurveType>
	{

	public:

		typedef typename cad_singular_curve_traits<CurveType>::baseCurveType baseCurveType;
		using typename Cad_SingularCurve<CurveType>::metricMap;

	private:

		/*Private Data*/

		Pnt2d theMid_;

		// private functions and operators [12/31/2021 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Cad_SingularCurve<CurveType>>(*this);
			ar & theMid_;
		}

	public:

		//typedef typename CurveType::geomType geomType;

		// default constructor [12/31/2021 Amir]


		// constructors [12/31/2021 Amir]

		explicit Cad_PoleSingularCurve(const std::shared_ptr<baseCurveType>& theCurve)
			: Cad_SingularCurve<CurveType>(theCurve)
			, theMid_(Pnt2d::null)
		{}

		Cad_PoleSingularCurve(const std::shared_ptr<baseCurveType>& theCurve, const Pnt2d& theMid)
			: Cad_SingularCurve<CurveType>(theCurve)
			, theMid_(theMid)
		{}

		Cad_PoleSingularCurve(std::shared_ptr<baseCurveType>&& theCurve)
			: Cad_SingularCurve<CurveType>(std::move(theCurve))
			, theMid_(Pnt2d::null)
		{}

		Cad_PoleSingularCurve(std::shared_ptr<baseCurveType>&& theCurve, Pnt2d&& theMid)
			: Cad_SingularCurve<CurveType>(std::move(theCurve))
			, theMid_(std::move(theMid))
		{}


		// override functions and operators [3/30/2022 Amir]

		std::pair<std::shared_ptr<CurveType>, std::shared_ptr<CurveType>>
			Split(const Standard_Real x) const override;

		Standard_Boolean IsPole() const override
		{
			return Standard_True;
		}

		Standard_Boolean HasSubcurves() const override
		{
			return Standard_False;
		}

		Standard_Real 
			CalcCharLength
			(
				const Pnt2d&, 
				const Pnt2d&, 
				const std::shared_ptr<metricMap>&
			) const override;

		Pnt2d 
			CalcCentre
			(
				const Pnt2d&, 
				const Pnt2d&, 
				const std::shared_ptr<metricMap>&
			) const override;

		std::shared_ptr<Entity2d_Polygon>
			Mesh
			(
				const std::shared_ptr<metricMap>& theMetricMap,
				const std::shared_ptr<Mesh_Curve_Info>& theInfo
			) const override;

		void CalcSubcurves() const override;

		// public functions and operators [12/31/2021 Amir]

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


		// static functions and operators [4/26/2022 Amir]
		template<class EdgeType, class PlnCurve>
		static std::vector<std::shared_ptr<EdgeType>> TopoMesh
		(
			const std::shared_ptr<PlnCurve>& theCurve,
			const std::shared_ptr<metricMap>& theMetricMap,
			const std::shared_ptr<Mesh_Curve_Info>& theInfo
		);

	};
}

#include <Cad_PoleSingularCurveI.hxx>

#endif // !_Cad_PoleSingularCurve_Header
