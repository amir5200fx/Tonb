#pragma once
#ifndef _Cad_ModifySingularPlane_PolygonLib_Header
#define _Cad_ModifySingularPlane_PolygonLib_Header

#include <Mesh_Module.hxx>
#include <Cad_ModifySingularPlane_Polygon.hxx>
#include <Entity2d_PolygonFwd.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	namespace meshLib
	{

		namespace singularity
		{

			class PolygonLib
			{

				/*Private Data*/

				std::vector<std::shared_ptr<Polygon>> thePolygons_;

			public:

				// default constructor [4/3/2022 Amir]

				PolygonLib()
				{}

				// constructors [4/3/2022 Amir]

				PolygonLib(const std::vector<std::shared_ptr<Polygon>>& thePolys)
					: thePolygons_(thePolys)
				{}

				PolygonLib(std::vector<std::shared_ptr<Polygon>>&& thePolys)
					: thePolygons_(std::move(thePolys))
				{}

				// public functions and operators [4/3/2022 Amir]

				auto NbPolygons() const
				{
					return (Standard_Integer)thePolygons_.size();
				}

				const auto& Polygons() const
				{
					return thePolygons_;
				}

				auto& PolygonsRef()
				{
					return thePolygons_;
				}

				// static functions and operators [4/3/2022 Amir]

				static TnbMesh_EXPORT Point_2 GetPoint(const Pnt2d&);
				static TnbMesh_EXPORT std::shared_ptr<Polygon> GetWire(const Entity2d_Polygon&);

			};
		}
	}
}

#endif // !_Cad_ModifySingularPlane_PolygonLib_Header
