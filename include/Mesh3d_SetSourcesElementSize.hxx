#pragma once
#ifndef _Mesh3d_SetSourcesElementSize_Header
#define _Mesh3d_SetSourcesElementSize_Header

#include <Mesh_Module.hxx>

#include <memory>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{


	// Forward Declarations [8/18/2022 Amir]
	class Mesh3d_SizeMapTool;
	class Pnt3d;

	class Mesh3d_SetSourcesElementSize
	{

		/*Private Data*/

	protected:

		// default constructor [8/18/2022 Amir]

		Mesh3d_SetSourcesElementSize()
		{}


		// constructors [8/18/2022 Amir]


	public:


		// public functions and operators [8/18/2022 Amir]

		virtual Standard_Real 
			CalcElementSize
			(
				const std::shared_ptr<Mesh3d_SizeMapTool>& theSizeMap, 
				const Standard_Real theRadius, 
				const Pnt3d& theCoord, 
				const Pnt3d& theSource
			) const = 0;
	};
}

#endif // !_Mesh3d_SetSourcesElementSize_Header
