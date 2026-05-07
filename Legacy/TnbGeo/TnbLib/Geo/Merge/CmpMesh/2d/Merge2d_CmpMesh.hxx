#pragma once
#ifndef _Merge2d_CmpMesh_Header
#define _Merge2d_CmpMesh_Header

#include <Entity2d_CmpMesh.hxx>
#include <Merge_StaticData.hxx>
#include <Global_Done.hxx>

namespace tnbLib
{

	typedef Merge_StaticData<Entity2d_CmpMesh, Merge_PntAlg_Mean>
		Merge2d_CmpMesh;

	template<>
	class Merge_StaticData<Entity2d_CmpMesh, Merge_PntAlg_Mean>
		: public Global_Done
	{
	public:
		typedef Merge_Pnt<Pnt2d, Stl_Vector, Merge_PntAlg_Mean> mergePnt;
	private:
		/*Private Data*/
		mergePnt theMergePnt_;

		// results
		std::shared_ptr<Entity2d_CmpMesh> theMerged_;
	public:
		// default constructor
		Merge_StaticData() = default;
		// constructors

		// Public functions and operators
		auto& MergePnt()
		{
			return theMergePnt_;
		}
		const auto& Merged() const { return theMerged_; }
		TnbGeo_EXPORT void Import(const Entity2d_CmpMesh&);
		TnbGeo_EXPORT void Perform();
	};
}

#endif