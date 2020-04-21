#include <Marine_Criterion.hxx>

tnbLib::Marine_Criterion::Marine_Criterion()
	: Global_Named("marine criterion")
{
}

tnbLib::Marine_Criterion::Marine_Criterion
(
	const Standard_Integer theIndex, 
	const word & theName
)
	: Global_Indexed(theIndex)
	, Global_Named(theName)
{
}