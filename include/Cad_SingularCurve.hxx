#pragma once
#ifndef _Cad_SingularCurve_Header
#define _Cad_SingularCurve_Header

#include <Standard_TypeDef.hxx>
#include <Global_Serialization.hxx>
#include <Mesh_Module.hxx>
#include <Cad_SingularCurveTraits.hxx>

class Geom2d_Curve;
class Geom_Curve;

#include "Aft2d_gPlnCurveSurface.hxx"

namespace tnbLib
{

	template<class CurveType>
	class Cad_SingularCurve
		: public CurveType
	{

	public:

		//typedef typename CurveType::geomType geomType;
		typedef typename cad_singular_curve_traits<CurveType>::baseCurveType baseCurveType;

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

		// public functions and operators [12/31/2021 Amir]

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

#endif // !_Cad_SingularCurve_Header

