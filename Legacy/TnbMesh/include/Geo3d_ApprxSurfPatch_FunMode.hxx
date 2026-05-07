#pragma once
#ifndef _Geo3d_ApprxSurfPatch_FunMode_Header
#define _Geo3d_ApprxSurfPatch_FunMode_Header

#include <Mesh_Module.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Global_TypeDef.hxx>
#include <Global_Handle.hxx>

// Forward Declarations [9/2/2022 Amir]
class Geom_Surface;

#include <memory>

namespace tnbLib
{

	// Forward Declarations [9/1/2022 Amir]

	class Geo3d_ApprxSurfPatch_FunMode
	{

		/*Private Data*/

		

	protected:

		// default constructor [9/1/2022 Amir]

		Geo3d_ApprxSurfPatch_FunMode()
		{}


		// constructors [9/1/2022 Amir]

	public:


		// public functions and operators [9/1/2022 Amir]

		virtual ~Geo3d_ApprxSurfPatch_FunMode()
		{}

		virtual Standard_Boolean 
			DoSubdivide
			(
				const Entity2d_Box&,
				const Geom_Surface& theSurface, 
				const Standard_Real theTol
			) const = 0;

		

		
	};
}

#endif // !_Geo3d_ApprxSurfPatch_FunMode_Header
