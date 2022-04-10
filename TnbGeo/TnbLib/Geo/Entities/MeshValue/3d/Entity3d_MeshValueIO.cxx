#include <Entity3d_MeshValue.hxx>

#include <Entity3d_Box.hxx>
#include <Entity3d_Triangulation.hxx>

namespace tnbLib
{

	template<>
	template<>
	void Entity3d_MeshValue::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int /*file_version*/
			)
	{
		ar & theMesh_;
		ar & theValues_;
	}

	template<>
	template<>
	void Entity3d_MeshValue::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int /*file_version*/
			)
	{
		ar & theMesh_;
		ar & theValues_;
	}
}