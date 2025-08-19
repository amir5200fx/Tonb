#pragma once
#ifndef _Marine_Model_SailTools_Header
#define _Marine_Model_SailTools_Header

#include <Entity2d_TriangulationFwd.hxx>
#include <Entity2d_ChainFwd.hxx>
#include <Marine_Module.hxx>
#include <Marine_SailModelsFwd.hxx>

#include <memory>

namespace tnbLib
{

	class Marine_Model_SailTools
	{

	public:

		static TnbMarine_EXPORT std::shared_ptr<Entity2d_Triangulation> 
			LateralProjArea
			(
				const std::shared_ptr<marineLib::Model_SurfaceSail>&
			);

		static TnbMarine_EXPORT std::shared_ptr<Entity2d_Chain> 
			GetMergedPlane
			(
				const std::shared_ptr<marineLib::Model_LateralPlnSail>&, 
				const Standard_Real theResolution = 1.0E-4, 
				const Standard_Real theRadius = 1.0E-6
			);

		static TnbMarine_EXPORT void
			Triangulate
			(
				const std::shared_ptr<marineLib::Model_LateralPlnSail>&
			);
	};
}

#endif // !_Marine_Model_SailTools_Header
