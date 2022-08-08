#pragma once
#ifndef _Geo3d_DelTri_Fade3d_Header
#define _Geo3d_DelTri_Fade3d_Header

#include <Geo_Module.hxx>
#include <Global_Done.hxx>
#include <Pnt3d.hxx>
#include <Entity3d_TetrahedralizationFwd.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	namespace fadeLib
	{

		class Geo3d_DelTri
			: public Global_Done
		{

			/*Private Data*/

			const std::vector<Pnt3d>& thePoints_;

			std::shared_ptr<Entity3d_Tetrahedralization> theTriangulation_;

		public:


			// default constructor [8/4/2022 Amir]


			// constructors [8/4/2022 Amir]

			explicit Geo3d_DelTri(const std::vector<Pnt3d>& thePoints)
				: thePoints_(thePoints)
			{}


			// public functions and operators [8/4/2022 Amir]

			const auto& Points() const
			{
				return thePoints_;
			}

			const auto& Triangulation() const
			{
				return theTriangulation_;
			}

			TnbGeo_EXPORT void Perform();
		};
	}
}

#endif // !_Geo3d_DelTri_Fade3d_Header
