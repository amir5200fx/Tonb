#pragma once
#ifndef _Cad_LineSingularCurve_Header
#define _Cad_LineSingularCurve_Header

#include <Cad_SingularCurve.hxx>
#include <Cad_SingularCurveTraits.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations [4/5/2022 Amir]
	class Pnt3d;

	template<class CurveType>
	class Cad_LineSingularCurve
		: public Cad_SingularCurve<CurveType>
	{

	public:

		typedef typename cad_singular_curve_traits<CurveType>::surfType surfType;
		typedef typename cad_singular_curve_traits<CurveType>::baseCurveType baseCurveType;

		using typename Cad_SingularCurve<CurveType>::metricMap;

	private:

		/*Private Data*/

		mutable std::vector<Standard_Real> theProjPars_;
		mutable std::vector<std::shared_ptr<CurveType>> theSubCurves_;

		mutable std::weak_ptr<CurveType> theParPaired_;

		// private functions and operators [12/31/2021 Amir]

		//friend class boost::serialization::access;

		//template<class Archive>
		//void serialize(Archive& ar, const unsigned int /*file_version*/)
		//{
		//	ar & boost::serialization::base_object<Cad_SingularCurve<CurveType>>(*this);
		//}

	public:

		//typedef typename Cad_SingularCurve<CurveType>::geomType geomType;

		// default constructor [12/31/2021 Amir]


		// constructors [12/31/2021 Amir]

		explicit Cad_LineSingularCurve(const std::shared_ptr<baseCurveType>& theCurve)
			: Cad_SingularCurve<CurveType>(theCurve)
		{}

		Cad_LineSingularCurve(std::shared_ptr<baseCurveType>&& theCurve)
			: Cad_SingularCurve<CurveType>(std::move(theCurve))
		{}


		// override functions and operators [4/5/2022 Amir]

		std::pair<std::shared_ptr<CurveType>, std::shared_ptr<CurveType>>
			Split(const Standard_Real x) const override;

		Standard_Boolean IsLine() const override
		{
			return Standard_True;
		}

		Standard_Boolean HasSubcurves() const override;

		void CalcSubcurves() const override
		{
			NotImplemented;
		}

		/*std::shared_ptr<Entity2d_Polygon>
			Mesh
			(
				const std::shared_ptr<metricMap>& theMetricMap,
				const std::shared_ptr<Mesh_Curve_Info>& theInfo
			) const override;*/

		// public functions and operators [12/31/2021 Amir]

		Standard_Real ProjectAt(const Pnt3d&, const surfType&) const;

		const auto& ProjPars() const
		{
			return theProjPars_;
		}

		auto& ProjParsRef()
		{
			return theProjPars_;
		}

		const auto& SubCurves() const
		{
			return theSubCurves_;
		}

		auto& SubCurvesRef()
		{
			return theSubCurves_;
		}

		void SetParPaired(const std::weak_ptr<CurveType>& theCurve)
		{
			theParPaired_ = theCurve;
		}

		// static functions and operators [5/31/2022 Amir]

		static void CheckProjPars(const std::vector<Standard_Real>&);

		template<class EdgeType, class PlnCurve>
		static std::vector<std::shared_ptr<EdgeType>> TopoMesh
		(
			const std::shared_ptr<PlnCurve>& theCurve,
			const std::shared_ptr<metricMap>& theMetricMap,
			const std::shared_ptr<Mesh_Curve_Info>& theInfo
		);
	};
}

#include <Cad_LineSingularCurveI.hxx>

#endif // !_Cad_LineSingularCurve_Header
