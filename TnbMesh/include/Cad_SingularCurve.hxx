#pragma once
#ifndef _Cad_SingularCurve_Header
#define _Cad_SingularCurve_Header

#include <Mesh_Module.hxx>
#include <Cad_SingularCurveTraits.hxx>
#include <Entity2d_Polygon.hxx>
#include <Global_Serialization.hxx>
#include <Global_TypeDef.hxx>
#include <Global_Handle.hxx>

class Geom2d_Curve;
class Geom_Curve;
class Geom_Surface;

namespace tnbLib
{

	// Forward Declarations [4/18/2022 Amir]
	class Geo_ApprxCurve_Info;
	class Mesh_Curve_Info;

	template<class SizeFun, class MetricFun>
	class Geo_MetricPrcsr;

	class Cad_SingularCurveBase
	{

		/*Private Data*/

	protected:

		// default constructor [4/18/2022 Amir]

		Cad_SingularCurveBase()
		{}

		// constructors [4/18/2022 Amir]

	public:

		static TnbMesh_EXPORT std::shared_ptr<Geo_ApprxCurve_Info> ApproxInfo;

		// public functions and operators [4/18/2022 Amir]

		static TnbMesh_EXPORT Handle(Geom_Curve)
			CalcCurve3d
			(
				const Handle(Geom2d_Curve)& para,
				const Handle(Geom_Surface)&, 
				const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo
			);

	};

	template<class CurveType>
	class Cad_SingularCurve
		: public CurveType
		, public Cad_SingularCurveBase
	{

	public:

		//typedef typename CurveType::geomType geomType;
		typedef typename cad_singular_curve_traits<CurveType>::baseCurveType baseCurveType;

		using typename CurveType::metricMap;

	private:

		/*Private Data*/

		Handle(Geom_Curve) thePaired3d_;

		// private functions and operators [12/31/2021 Amir]

		TNB_SERIALIZATION(TnbMesh_EXPORT);

		/*friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<CurveType>(*this);
		}*/

	protected:

		// default constructor [12/31/2021 Amir]


		// constructors [12/31/2021 Amir]

		Cad_SingularCurve(const std::shared_ptr<baseCurveType>& theCurve)
			: CurveType(theCurve)
		{}

		Cad_SingularCurve(std::shared_ptr<baseCurveType>&& theCurve)
			: CurveType(std::move(theCurve))
		{}

	public:

		
		// override functions and operators [4/25/2022 Amir]

		Standard_Boolean IsSingular() const override;

		void OrientWith(const std::shared_ptr<CurveType>&) override;

		// public functions and operators [12/31/2021 Amir]

		const auto& Paired3d() const
		{
			return thePaired3d_;
		}

		virtual Standard_Boolean IsPole() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsLine() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean HasSubcurves() const = 0;
		virtual void CalcSubcurves() const = 0;

		void SetPaired3d(const Handle(Geom_Curve)& theGeom)
		{
			thePaired3d_ = theGeom;
		}

	};
}

#include <Cad_SingularCurveI.hxx>

#endif // !_Cad_SingularCurve_Header

