#pragma once
#ifndef _Entity3d_Pentahedralization_Header
#define _Entity3d_Pentahedralization_Header

#include <Entity3d_PentahedralizationFwd.hxx>
#include <Entity_StaticData.hxx>
#include <Pnt3d.hxx>

namespace tnbLib
{

	template<>
	void Entity3d_Pentahedrolization::ExportToPlt(OFstream& File) const;
}

#endif // !_Entity3d_Pentahedralization_Header
