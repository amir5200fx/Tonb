#pragma once
#ifndef _ShipModeler_Basic_Tools_Header
#define _ShipModeler_Basic_Tools_Header

#include <Standard_TypeDef.hxx>

#include <memory>
#include <vector>

class TopoDS_Shape;
class gp_Ax2;

namespace tnbLib
{

	// Forward Declarations
	class Geo_xDistb;
	class Marine_CmpSection;

	namespace shipModelerLib
	{

		// Forward declarations
		class Basic_Tank;
		class Basic_Hull;
		class Basic_Sail;
		class Basic_WPlane;

		class Basic_Tools
		{

		public:

			static std::shared_ptr<Geo_xDistb> 
				UniformDistribution
				(
					const TopoDS_Shape& theShape, 
					const Standard_Integer nbSegments
				);

			static std::shared_ptr<Geo_xDistb> 
				UniformDistribution
				(
					const Standard_Real x0,
					const Standard_Real x1, 
					const Standard_Integer nbSegments
				);

			static std::shared_ptr<Basic_WPlane> 
				CreateWorkingPlane
				(
					const TopoDS_Shape& theShape, 
					const gp_Ax2& theAx, 
					const Standard_Real x
				);

			static std::vector<std::shared_ptr<Basic_WPlane>>
				CreateWorkingPlanes
				(
					const TopoDS_Shape& theShape, 
					const gp_Ax2& theAx,
					const Geo_xDistb& theDistb
				);

			static std::shared_ptr<Marine_CmpSection> CreateSection(const Basic_WPlane& thePlane);

			static std::shared_ptr<Basic_Tank> CreateTank(const std::vector<std::shared_ptr<Basic_WPlane>>& theShape);

			static std::shared_ptr<Basic_Sail> CreateSail(const std::vector<std::shared_ptr<Basic_WPlane>>& theShape, const Geo_xDistb& theDistb);

			static std::shared_ptr<Basic_Hull> CreateHull(const std::vector<std::shared_ptr<Basic_WPlane>>& theShape, const Geo_xDistb& theDistb);
		};
	}
}

#endif // !_ShipModeler_Basic_Tools_Header
