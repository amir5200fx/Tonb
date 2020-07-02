#pragma once
#ifndef _Marine_DisctLib_Header
#define _Marine_DisctLib_Header

#include <Marine_ShapesFwd.hxx>
#include <Marine_BodiesFwd.hxx>
#include <Marine_BodyType.hxx>
#include <Marine_WireFrameShapesFwd.hxx>

#include <memory>
#include <tuple>

#include <TopoDS_Shape.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Marine_Distrb;
	class Marine_WireFrameShape;
	class Marine_WaterDomain;

	class Marine_DisctLib
	{

	public:


		static std::shared_ptr<Marine_WireFrameShape> 
			xWireFrameModel
			(
				const std::shared_ptr<Marine_Shape>& theModel,
				const Marine_Distrb& theX,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);

		static std::shared_ptr<marineLib::Body_Wetted>
			WettedBody
			(
				const marineLib::Body_Tank& theModel,
				const Marine_WaterDomain& theWaterDomain,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);

		static std::shared_ptr<marineLib::Body_Wetted>
			WettedBody
			(
				const marineLib::Body_Displacer& theModel,
				const Marine_WaterDomain& theWaterDomain,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);

		static std::shared_ptr<marineLib::Body_Wetted>
			WettedBody
			(
				const std::shared_ptr<Marine_WireFrameShape>& theModel,
				const Marine_WaterDomain& theWaterDomain,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);

		static std::shared_ptr<marineLib::Body_Wetted>
			WettedBody
			(
				const marineLib::WireFrameShape_Shape& theModel,
				const Marine_WaterDomain& theWaterDomain,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);

		static std::shared_ptr<marineLib::Body_Wetted>
			WettedBody
			(
				const marineLib::WireFrameShape_Offset& theModel,
				const Marine_WaterDomain& theWaterDomain,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);

		static std::tuple<std::shared_ptr<marineLib::Body_Wetted>, std::shared_ptr<marineLib::Body_Dry>>
			WettedAndDryBody
			(
				const Marine_WireFrameShape& theModel,
				const Marine_WaterDomain& theWaterDomain,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);

	};
}

#endif // !_Marine_DisctLib_Header
