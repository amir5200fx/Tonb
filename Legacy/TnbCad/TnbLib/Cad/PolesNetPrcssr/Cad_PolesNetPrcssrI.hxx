#pragma once
#include <Vec3d.hxx>
inline Standard_Integer 
tnbLib::Cad_PolesNetPrcssr::NbVectorRows() const
{
	return NbColumns() - 1;
}

inline Standard_Integer 
tnbLib::Cad_PolesNetPrcssr::NbVectorColumns() const
{
	return NbRows() - 1;
}
