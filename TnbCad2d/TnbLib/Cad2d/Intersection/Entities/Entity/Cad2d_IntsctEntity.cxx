#include <Cad2d_IntsctEntity.hxx>

tnbLib::Cad2d_IntsctEntity::Cad2d_IntsctEntity
(
	const Standard_Integer theIndex
)
	: Global_Indexed(theIndex)
{
}

tnbLib::Cad2d_IntsctEntity::Cad2d_IntsctEntity
(
	const Standard_Integer theIndex,
	const word & theName
)
	: Global_Indexed(theIndex)
	, Global_Named(theName)
{
}