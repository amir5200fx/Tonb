#include <Mesh2d_SizeMapControl.hxx>

#include <Cad2d_Plane.hxx>
#include <Mesh_ReferenceValues.hxx>
#include <Mesh2d_SizeMapTool.hxx>

namespace tnbLib
{
	template<>
	template<>
	void Mesh2d_SizeMapControl::serialize<TNB_iARCH_TYPE>(TNB_iARCH_TYPE& ar, const unsigned int /*file_version*/)
	{
		ar & theReference_;
		ar & theBoundaries_;

		//ar & theCloud_;
		FatalErrorIn(FunctionSIG)
			<< "active cloud2!" << endl
			<< abort(FatalError);
	}

	template<>
	template<>
	void Mesh2d_SizeMapControl::serialize<TNB_oARCH_TYPE>(TNB_oARCH_TYPE& ar, const unsigned int /*file_version*/)
	{
		ar & theReference_;
		ar & theBoundaries_;

		//ar & theCloud_;
		FatalErrorIn(FunctionSIG)
			<< "active cloud2!" << endl
			<< abort(FatalError);
	}
}