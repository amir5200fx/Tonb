#pragma once
#ifndef _Geo2d_DelTri_CGAL_Header
#define _Geo2d_DelTri_CGAL_Header

#include <Global_Done.hxx>
#include <Geo_Module.hxx>
#include <Pnt2d.hxx>
#include <Entity2d_TriangleFwd.hxx>
#include <Entity2d_TriangulationFwd.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	namespace cgalLib
	{

		class Geo2d_DelTri
			: public Global_Done
		{

			/*Private Data*/

			const std::vector<Pnt2d>& thePoints_;

			std::shared_ptr<Entity2d_Triangulation> theTriangulation_;

		public:

			//- constructors

			explicit Geo2d_DelTri(const std::vector<Pnt2d>& thePoints)
				: thePoints_(thePoints)
			{}

			//- public functions and operators

			const auto& Triangulation() const
			{
				return theTriangulation_;
			}

			TnbGeo_EXPORT void Perform();

		};
	}
}

#endif // !_Geo2d_DelTri_CGAL_Header
