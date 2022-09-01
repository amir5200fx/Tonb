#pragma once
#ifndef _Mesh3d_SetSourcesCalcRadius_Header
#define _Mesh3d_SetSourcesCalcRadius_Header

#include <Standard_TypeDef.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [8/18/2022 Amir]
	class Mesh3d_SizeMapTool;

	class Mesh3d_SetSourcesCalcRadius
	{

		/*Private Data*/

	protected:

		// default constructor [8/18/2022 Amir]

		Mesh3d_SetSourcesCalcRadius()
		{}


		// constructors [8/18/2022 Amir]


	public:

		// public functions and operators [8/18/2022 Amir]

		virtual Standard_Real CalcRadius(const std::shared_ptr<Mesh3d_SizeMapTool>& theSizeMap) const = 0;
	};
}

#endif // !_Mesh3d_SetSourcesCalcRadius_Header
