#pragma once
#ifndef _Mesh_VariationRate_Header
#define _Mesh_VariationRate_Header

#include <Mesh_VariationRateInfo.hxx>
#include <Mesh_Module.hxx>
#include <Global_TypeDef.hxx>

namespace tnbLib
{

	class Mesh_VariationRate
	{

	public:

		static TnbMesh_EXPORT Standard_Real customValue;

		static TnbMesh_EXPORT Standard_Real VeryLowrate();

		static TnbMesh_EXPORT Standard_Real Lowrate();

		static TnbMesh_EXPORT Standard_Real Moderate();

		static TnbMesh_EXPORT Standard_Real Highrate();

		static TnbMesh_EXPORT Standard_Real Rate(const Mesh_VariationRateInfo Info);
	};
}

#endif // !_Mesh_VariationRate_Header
