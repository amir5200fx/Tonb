#pragma once
#ifndef _Cad_gModifySingularPlane_Header
#define _Cad_gModifySingularPlane_Header

#include <Cad_ModifySingularPlane.hxx>
#include <Cad_gModifySingularPlaneFwd.hxx>

#ifdef _DEBUG
namespace tnbLib
{
	template<>
	TnbMesh_EXPORT void Cad_gModifySingularPlane::Perform();
}
#endif // _DEBUG


#endif // !_Cad_gModifySingularPlane_Header
