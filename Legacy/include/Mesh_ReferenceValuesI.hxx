#pragma once
template<class Box>
inline void tnbLib::Mesh_ReferenceValues<Box>::AllocateMemory()
{
	theSurfaceSize_ = std::make_shared<Mesh_SurfaceSizeValues>();
	theSurfaceCurvature_ = std::make_shared<Mesh_SurfaceCurvatureValues>();
}