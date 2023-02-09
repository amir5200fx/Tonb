#include <Aft2d_tPlnCurveSurface.hxx>

#include <TModel_ParaCurve.hxx>
#include <Entity2d_Polygon.hxx>

namespace tnbLib
{

	template<>
	template<>
	void Aft2d_tPlnCurveSurface::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar, 
			const unsigned int /*file_version*/
			)
	{
		ar & boost::serialization::base_object<Mesh_PlnCurve_Base>(*this);
		ar & boost::serialization::base_object<Global_Indexed>(*this);

		ar & theCurve_;
		ar & theMesh_;
		ar& theSense_;
	}

	template<>
	template<>
	void Aft2d_tPlnCurveSurface::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar, 
			const unsigned int /*file_version*/
			)
	{
		ar & boost::serialization::base_object<Mesh_PlnCurve_Base>(*this);
		ar & boost::serialization::base_object<Global_Indexed>(*this);

		ar & theCurve_;
		ar & theMesh_;
		ar& theSense_;
	}
}