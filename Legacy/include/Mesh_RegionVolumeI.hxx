#pragma once
#include <Mesh_PatchTemplate.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
template<class SurfType>
inline Standard_Boolean 
tnbLib::Mesh_RegionVolume<SurfType>::HasHole() const
{
	return Standard_Boolean(theInners_);
}

template<class SurfType>
inline Standard_Integer 
tnbLib::Mesh_RegionVolume<SurfType>::NbHoles() const
{
	if (NOT HasHole()) return 0;
	return Standard_Integer(theInners_->size());
}

//namespace tnbLib
//{
//	template<class SurfType, class SizeFun, class MetricFun>
//	template<class ShellType>
//	inline std::shared_ptr<typename Mesh_RegionVolume<SurfType, SizeFun, MetricFun>::shellType>
//		Mesh_RegionVolume<SurfType, SizeFun, MetricFun>::MakeMeshShell(const ShellType& theShell)
//	{
//		auto surfaces_ptr = 
//			std::make_shared<std::vector<std::shared_ptr<surfMeshType>>>();
//		auto& surfaces = *surfaces_ptr;
//		surfaces.reserve(theShell.NbSurfaces());
//		
//		Standard_Integer k = 0;
//		for (const auto& x : theShell.Surfaces())
//		{
//			Debug_Null_Pointer(x);
//			auto surfaceMesh = std::make_shared<Mesh_PatchTemplate>(x);
//			surfaces.push_back(std::move(surfaceMesh));
//		}
//		auto shell = std::make_shared<shellType>(std::move(surfaces));
//		return std::move(shell);
//	}
//}
//
//template<class SurfType, class SizeFun, class MetricFun>
//inline std::shared_ptr<tnbLib::Mesh_RegionVolume<SurfType, SizeFun, MetricFun>>
//tnbLib::Mesh_RegionVolume<SurfType, SizeFun, MetricFun>::MakeVolume
//(
//	const std::shared_ptr<volType>& theVolume
//)
//{
//	Debug_Null_Pointer(theVolume);
//	if (NOT theVolume->Outer())
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "invalid solid: doesn't have an outer shell!" << endl
//			<< abort(FatalError);
//	}
//	const auto& outer = *theVolume->Outer();
//	auto outer_shell = MakeMeshShell(outer);
//
//	std::shared_ptr<std::vector<std::shared_ptr<shellType>>>
//		inner_shells;
//	if (theVolume->Holes())
//	{
//		const auto& inners = *theVolume->Holes();
//		inner_shells =
//			std::make_shared<std::vector<std::shared_ptr<shellType>>>();
//		inner_shells->reserve(inners.size());
//		for (const auto& x : inners)
//		{
//			Debug_Null_Pointer(x);
//			auto shell = MakeMeshShell(*x);
//			inner_shells->push_back(std::move(shell));
//		}
//	}
//	auto volume = 
//		std::make_shared<Mesh_RegionVolume>
//		(theVolume, outer_shell, inner_shells);
//	return std::move(volume);
//}