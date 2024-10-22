#pragma once
#ifndef _Merge3d_CmpMesh_Header
#define _Merge3d_CmpMesh_Header

#include <Entity3d_CmpMesh.hxx>
#include <Entity3d_CmpConnect.hxx>
#include <Merge_StaticData.hxx>
#include <Global_Done.hxx>


namespace tnbLib
{
	typedef Merge_StaticData<Entity3d_CmpMesh> Merge3d_CmpMesgh;

	template<>
	class Merge_StaticData<Entity3d_CmpMesh, Merge_PntAlg_Mean>
		: public Global_Done
	{
	public:
		typedef Merge_Pnt<Pnt3d, Stl_Vector, Merge_PntAlg_Mean> mergePnt;
	private:
		/*Private Data*/
		mergePnt theMergePnt_;

		// results
		std::shared_ptr<Entity3d_CmpMesh> theMerged_;
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
		TnbGeo_EXPORT void Import(const Entity3d_CmpMesh&);
		TnbGeo_EXPORT void Perform();
	};
}

#endif