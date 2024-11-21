#pragma once
#ifndef _Cad_ModifySingularPlane_Polygon_Header
#define _Cad_ModifySingularPlane_Polygon_Header

#include <Cad_ModifySingularPlane_PolygonPoint.hxx>
#include <Global_TypeDef.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	namespace meshLib
	{

		namespace singularity
		{

			class Polygon
			{

				/*Private Data*/

				std::vector<Point_2> thePoints_;

			public:

				// default constructor [4/3/2022 Amir]

				Polygon()
				{}

				// constructors [4/3/2022 Amir]

				Polygon(std::vector<Point_2>&& thePoints)
					: thePoints_(std::move(thePoints))
				{}

				explicit Polygon(const std::vector<Point_2>& thePoints)
					: thePoints_(thePoints)
				{}


				// public functions and operators [4/3/2022 Amir]

				auto NbPoints() const
				{
					return (Standard_Integer)thePoints_.size();
				}

				const auto& Points() const
				{
					return thePoints_;
				}

				auto& PointsRef()
				{
					return thePoints_;
				}
			};
		}
	}
}

#endif // !_Cad_ModifySingularPlane_Polygon_Header
