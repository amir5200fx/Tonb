#pragma once
#ifndef _Marine_DisctLib_Header
#define _Marine_DisctLib_Header


#include <memory>
#include <tuple>

#include <TopoDS_Shape.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Marine_Distrb;
	class Marine_WettedBody;
	class Marine_DryBody;
	class Marine_WireFrameModel;
	class Marine_VesselHull;
	class Marine_WaterDomain;

	class Marine_DisctLib
	{

	public:

		static std::shared_ptr<Marine_WireFrameModel> 
			WireFrameModel
			(
				const Marine_VesselHull& theHull,
				const Marine_Distrb& theX,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);


		static std::shared_ptr<Marine_WettedBody>
			WettedBody
			(
				const Marine_WireFrameModel& theModel,
				const Marine_WaterDomain& theWaterDomain,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);

		static std::tuple<std::shared_ptr<Marine_WettedBody>, std::shared_ptr<Marine_DryBody>>
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
