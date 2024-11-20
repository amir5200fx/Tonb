#pragma once
#ifndef _Cad_SubdivideHorizonTools_Header
#define _Cad_SubdivideHorizonTools_Header

#include <Mesh_Module.hxx>
#include <Global_Handle.hxx>

#include <vector>

class Geom2d_Curve;

namespace tnbLib
{

	// Forward Declarations [4/1/2022 Amir]
	class Pnt2d;

	class Cad_SubdivideHorizonTools
	{

		/*Private Data*/

	public:

		struct Params
		{
			Standard_Real ParOnC0;
			Standard_Real ParOnC1;
		};

		static TnbMesh_EXPORT std::pair<Standard_Real, Standard_Real> 
			RetrieveParams
			(
				const Handle(Geom2d_Curve)&
			);

		static TnbMesh_EXPORT Params 
			MakePair
			(
				const Standard_Real, 
				const Standard_Real
			);

		static TnbMesh_EXPORT std::pair<std::vector<Standard_Real>, std::vector<Standard_Real>> 
			RetrieveParams
			(
				const std::vector<Params>&
			);

		static TnbMesh_EXPORT std::pair<std::vector<Params>, Standard_Boolean>
			CalcIntersections
			(
				const Handle(Geom2d_Curve)& theC0, 
				const Handle(Geom2d_Curve)& theC1
			);
	};
}

#endif // !_Cad_SubdivideHorizonTools_Header
