#pragma once
#ifndef _GeoIO_Loader_OBJ_Header
#define _GeoIO_Loader_OBJ_Header

#include <Entity3d_TriangulationFwd.hxx>
#include <Geo_Module.hxx>
#include <Global_Done.hxx>
#include <fileName.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	namespace ioLib
	{

		class Loader_OBJ
			: public Global_Done
		{

			/*Private Data*/

			fileName theFileName_;

			std::vector<std::shared_ptr<Entity3d_Triangulation>> theMeshes_;

		public:

			// default constructor [2/3/2023 Payvand]
			

			// constructors [2/3/2023 Payvand]

			explicit Loader_OBJ(const fileName& theName)
				: theFileName_(theName)
			{}

			// Public functions and operators [2/3/2023 Payvand]

			const auto& FileName() const
			{
				return theFileName_;
			}

			TnbGeo_EXPORT Standard_Integer NbMeshes() const;

			TnbGeo_EXPORT const std::shared_ptr<Entity3d_Triangulation>&
				Mesh(const Standard_Integer theIndex) const;

			TnbGeo_EXPORT const std::vector<std::shared_ptr<Entity3d_Triangulation>>&
				Meshes() const;

			TnbGeo_EXPORT void Perform();

		};
	}
}

#endif // !_GeoIO_Loader_OBJ_Header
