#pragma once
#ifndef _GeoSlicer3d_PlnTris_Header
#define _GeoSlicer3d_PlnTris_Header

#include <Entity3d_Triangulation.hxx>
#include <Global_Done.hxx>

#include <memory>
#include <vector>

class gp_Pln;

namespace tnbLib
{

	class GeoSlicer3d_PlnTris
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<gp_Pln> thePlane_;
		std::shared_ptr<Entity3d_Triangulation> theMesh_;


		// Results [2/16/2023 Payvand]

		std::shared_ptr<Entity3d_Triangulation> theClipped_;

	public:

		// default constructor [2/16/2023 Payvand]

		GeoSlicer3d_PlnTris()
		{}

		// constructors [2/16/2023 Payvand]


		// Public functions and operators [2/16/2023 Payvand]

		TnbGeo_EXPORT Standard_Boolean IsClipped() const;

		const auto& Clipped() const
		{
			return theClipped_;
		}

		const auto& Plane() const
		{
			return thePlane_;
		}

		const auto& Mesh() const
		{
			return theMesh_;
		}

		TnbGeo_EXPORT void Perform();

		void SetPlane(const std::shared_ptr<gp_Pln>& thePlane)
		{
			thePlane_ = thePlane;
		}

		void SetPlane(std::shared_ptr<gp_Pln>&& thePlane)
		{
			thePlane_ = std::move(thePlane);
		}

		void SetMesh(const std::shared_ptr<Entity3d_Triangulation>& theMesh)
		{
			theMesh_ = theMesh;
		}

		void SetMesh(std::shared_ptr<Entity3d_Triangulation>&& theMesh)
		{
			theMesh_ = std::move(theMesh);
		}

	};
}

#endif // !_GeoSlicer3d_PlnTris_Header
