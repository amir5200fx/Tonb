#pragma once
#ifndef _Mesh3d_SetSourcesCalcRadius_GrowthRate_Header
#define _Mesh3d_SetSourcesCalcRadius_GrowthRate_Header

#include <Mesh3d_SetSourcesCalcRadius.hxx>
#include <Mesh_Module.hxx>

namespace tnbLib
{

	class Mesh3d_SetSourcesCalcRadius_GrowthRate
		: public Mesh3d_SetSourcesCalcRadius
	{

		/*Private Data*/

	public:

		// default constructor [8/18/2022 Amir]

		Mesh3d_SetSourcesCalcRadius_GrowthRate()
		{}


		// constructors [8/18/2022 Amir]


		// public functions and operators [8/18/2022 Amir]


		TnbMesh_EXPORT Standard_Real 
			CalcRadius
			(
				const std::shared_ptr<Mesh3d_SizeMapTool>& theSizeMap
			) const override;


		static TnbMesh_EXPORT Standard_Real 
			CalcRadius
			(
				const Standard_Real theGrowthRate, 
				const Standard_Real theTarget, 
				const Standard_Real theBase
			);

	};
}

#endif // !_Mesh3d_SetSourcesCalcRadius_GrowthRate_Header
