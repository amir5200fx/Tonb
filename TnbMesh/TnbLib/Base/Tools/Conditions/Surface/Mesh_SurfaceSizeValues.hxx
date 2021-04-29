#pragma once
#ifndef _Mesh_SurfaceSizeValues_Header
#define _Mesh_SurfaceSizeValues_Header

#include <Standard_TypeDef.hxx>
#include <Global_Serialization.hxx>
#include <Mesh_Module.hxx>
#include <Mesh_SizeMethodInfo.hxx>
#include <Mesh_RelativeAbsoluteInfo.hxx>

namespace tnbLib
{

	class Mesh_SurfaceSizeValues
	{

		/*Private Data*/

		Mesh_SizeMethodInfo theSizeMethod_;

		Mesh_RelativeAbsoluteInfo theRelativeAbsolute_;

		Standard_Real theMinSize_;
		Standard_Real theTargetSize_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & theSizeMethod_;
			ar & theRelativeAbsolute_;

			ar & theMinSize_;
			ar & theTargetSize_;
		}

	public:

		static TnbMesh_EXPORT const Standard_Real DEFAULT_MIN_SIZE;
		static TnbMesh_EXPORT const Standard_Real DEFAULT_TARGET_SIZE;

		TnbMesh_EXPORT Mesh_SurfaceSizeValues();

		auto SizeMethod() const
		{
			return theSizeMethod_;
		}

		auto& ChangeSizeMethod()
		{
			return theSizeMethod_;
		}

		auto RelativeAbsolute() const
		{
			return theRelativeAbsolute_;
		}

		auto& ChangeRelativeAbsolute()
		{
			return theRelativeAbsolute_;
		}

		auto MinSize() const
		{
			return theMinSize_;
		}

		auto& ChangeMinSize()
		{
			return theMinSize_;
		}

		auto TargetSize() const
		{
			return theTargetSize_;
		}

		auto& ChangeTargetSize()
		{
			return theTargetSize_;
		}

		void SetSizeMethod(const Mesh_SizeMethodInfo info)
		{
			theSizeMethod_ = info;
		}

		void SetRelativeAbsolute(const Mesh_RelativeAbsoluteInfo info)
		{
			theRelativeAbsolute_ = info;
		}

		void SetMinSize(const Standard_Real theSize)
		{
			theMinSize_ = theSize;
		}

		void SetTargetSize(const Standard_Real theSize)
		{
			theTargetSize_ = theSize;
		}
	};
}

#endif // !_Mesh_SurfaceSizeValues_Header
