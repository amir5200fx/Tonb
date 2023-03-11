#pragma once
template<class SurfType>
inline void tnbLib::Mesh_Surface<SurfType>::SetSurface(const std::shared_ptr<SurfType>& theSurface)
{
	theSurface_ = theSurface;
}

template<class SurfType>
inline void tnbLib::Mesh_Surface<SurfType>::SetSurface(std::shared_ptr<SurfType>&& theSurface)
{
	theSurface_ = std::move(theSurface);
}

template<class SurfType>
inline void tnbLib::Mesh_Surface<SurfType>::SetParaTriangulation
(
	const std::shared_ptr<Entity2d_Triangulation>& theTri
)
{
	theParaTriangulation_ = theTri;
}

template<class SurfType>
inline void tnbLib::Mesh_Surface<SurfType>::SetParaTriangulation
(
	std::shared_ptr<Entity2d_Triangulation>&& theTri
)
{
	theParaTriangulation_ = std::move(theTri);
}

template<class SurfType>
inline void tnbLib::Mesh_Surface<SurfType>::SetTriangulation
(const std::shared_ptr<Entity3d_Triangulation>& theTri)
{
	theTriangulation_ = theTri;
}

template<class SurfType>
inline void tnbLib::Mesh_Surface<SurfType>::SetTriangulation
(std::shared_ptr<Entity3d_Triangulation>&& theTri)
{
	theTriangulation_ = std::move(theTri);
}