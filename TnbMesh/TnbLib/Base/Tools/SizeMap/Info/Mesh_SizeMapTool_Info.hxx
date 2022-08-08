#pragma once
#ifndef _Mesh_SizeMapTool_Info_Header
#define _Mesh_SizeMapTool_Info_Header

#include <Mesh_Module.hxx>
#include <Global_Serialization.hxx>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	class Mesh_SizeMapTool_Info
	{

		/*Private Data*/

		Standard_Integer theUnbalancing_;
		Standard_Integer theMinSubdivide_;
		Standard_Integer theMaxSubdivide_;

	public:

		static TnbMesh_EXPORT const Standard_Integer DEFAULT_UNBALANCING;
		static TnbMesh_EXPORT const Standard_Integer DEFAULT_MIN_SUBDIVIDE;
		static TnbMesh_EXPORT const Standard_Integer DEFAULT_MAX_SUBDIVIDE;

		// default constructor [6/23/2022 Amir]

		Mesh_SizeMapTool_Info()
			: theUnbalancing_(DEFAULT_UNBALANCING)
			, theMinSubdivide_(DEFAULT_MIN_SUBDIVIDE)
			, theMaxSubdivide_(DEFAULT_MAX_SUBDIVIDE)
		{}


		// constructors [6/23/2022 Amir]



		// public functions and operators [6/23/2022 Amir]

		auto Unbalancing() const
		{
			return theUnbalancing_;
		}

		auto MinSubdivide() const
		{
			return theMinSubdivide_;
		}

		auto MaxSubdivide() const
		{
			return theMaxSubdivide_;
		}

		void SetMinSubdivide(const Standard_Integer n)
		{
			theMinSubdivide_ = n;
		}

		void SetMaxSubdivide(const Standard_Integer n)
		{
			theMaxSubdivide_ = n;
		}

		void SetUnbalancing(const Standard_Integer n)
		{
			theUnbalancing_ = n;
		}
	};
}

#endif // !_Mesh_SizeMapTool_Info_Header
