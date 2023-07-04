#include <Mesh2d_PlnCurveAnIso.hxx>

#include <Pln_Curve.hxx>
#include <Entity2d_Polygon.hxx>
#include <Mesh_Physic.hxx>

namespace tnbLib
{

	template<>
	template<>
	void Mesh2d_PlnCurveAnIso::serialize<TNB_oARCH_TYPE>
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
		ar& thePhysic_;
	}

	template<>
	template<>
	void Mesh2d_PlnCurveAnIso::serialize<TNB_iARCH_TYPE>
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
		ar& thePhysic_;
	}
}