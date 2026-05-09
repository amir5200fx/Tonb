#pragma once
#ifndef _Voyage_Mesh2_Header
#define _Voyage_Mesh2_Header

#include <Voyage_Module.hxx>
#include <Geo2d_MetricPrcsrAnIsoFwd.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Dir2d.hxx>
#include <Global_Done.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations [7/20/2023 Payvand]

	class Voyage_WptsGrid;
	class VoyageGeo_Path;
	class VoyageGeo_SizeFun;
	class VoyageGeo_MetricFun;
	class VoyageField_Earth;
	class Mesh_Curve_Info;
	class Pln_Curve;

	class Voyage_Mesh2
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Pln_Curve> theRefRoute_;

	public:

		// default constructor [8/5/2023 Payvand]

		Voyage_Mesh2()
		{}

		// constructors [8/5/2023 Payvand]


		// Public functions and operators [8/5/2023 Payvand]

		
	};
}

#endif // !_Voyage_Mesh2_Header
