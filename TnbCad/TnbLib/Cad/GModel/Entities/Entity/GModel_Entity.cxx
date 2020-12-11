#include <GModel_Entity.hxx>

tnbLib::GModel_Entity::GModel_Entity
(
	const Standard_Integer theIndex
)
	: Global_Indexed(theIndex)
{
	// empty body
}

tnbLib::GModel_Entity::GModel_Entity
(
	const Standard_Integer theIndex, 
	const word & theName
)
	: Global_Indexed(theIndex)
	, Global_Named(theName)
{
	// empty body
}