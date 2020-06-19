#pragma once
#ifndef _Marine_DisctLib_Header
#define _Marine_DisctLib_Header

#include <Marine_ModelsFwd.hxx>
#include <Marine_BodiesFwd.hxx>
#include <Marine_BodyType.hxx>

#include <memory>
#include <tuple>

#include <TopoDS_Shape.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Marine_Distrb;
	class Marine_WireFrameModel;
	class Marine_WaterDomain;

	class Marine_DisctLib
	{

	public:

		static TopoDS_Shape Section(const TopoDS_Shape& theShape, const gp_Ax2& theSys);

		static std::shared_ptr<Marine_WireFrameModel> 
			xWireFrameModel
			(
				const Marine_Model& theModel,
				const Marine_Distrb& theX,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);


		static std::shared_ptr<marineLib::Body_Wetted>
			WettedBody
			(
				const Marine_WireFrameModel& theModel,
				const Marine_WaterDomain& theWaterDomain,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);

		static std::tuple<std::shared_ptr<marineLib::Body_Wetted>, std::shared_ptr<marineLib::Body_Dry>>
			WettedAndDryBody
			(
				const Marine_WireFrameModel& theModel,
				const Marine_WaterDomain& theWaterDomain,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);

	};
}

#endif // !_Marine_DisctLib_Header
