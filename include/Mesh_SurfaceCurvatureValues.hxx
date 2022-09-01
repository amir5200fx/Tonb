#pragma once
#ifndef _Mesh_SurfaceCurvatureValues_Header
#define _Mesh_SurfaceCurvatureValues_Header

#include <Standard_TypeDef.hxx>
#include <Global_Serialization.hxx>
#include <Mesh_Module.hxx>
#include <Mesh_SurfaceCurvatureInfo.hxx>

namespace tnbLib
{

	class Mesh_SurfaceCurvatureValues
	{

		/*Private Data*/

		Mesh_SurfaceCurvatureInfo theInfo_;

		Standard_Real theSpanAngle_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & theInfo_;
			ar & theSpanAngle_;
		}

	public:

		static TnbMesh_EXPORT const Standard_Real DEFAULT_SPAN_ANGLE;

		Mesh_SurfaceCurvatureValues()
			: theSpanAngle_(DEFAULT_SPAN_ANGLE)
			, theInfo_(Mesh_SurfaceCurvatureInfo::continum)
		{}


		auto SpanAngle() const
		{
			return theSpanAngle_;
		}

		auto& ChangeSpanAngle()
		{
			return theSpanAngle_;
		}

		auto CurvatureInfo() const
		{
			return theInfo_;
		}

		auto& ChangeCurvatureInfo()
		{
			return theInfo_;
		}

		void SetSpanAngle(const Standard_Real theAngle)
		{
			theSpanAngle_ = theAngle;
		}

		void SetCurvatureInfo(const Mesh_SurfaceCurvatureInfo& info)
		{
			theInfo_ = info;
		}
	};
}

#endif // !_Mesh_SurfaceCurvatureValues_Header
