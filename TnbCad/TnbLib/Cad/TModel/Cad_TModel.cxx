#include <Cad_TModel.hxx>

tnbLib::Cad_TModel::Cad_TModel()
{
}

tnbLib::Cad_TModel::Cad_TModel
(
	const Standard_Integer theIndex
)
	: TModel_Entity(theIndex)
{
}

tnbLib::Cad_TModel::Cad_TModel
(
	const Standard_Integer theIndex,
	const word & theName
)
	: TModel_Entity(theIndex, theName)
{
}

Standard_Integer 
tnbLib::Cad_TModel::NbHoles() const
{
	if (Holes())
	{
		return (Standard_Integer)Holes()->size();
	}
	return 0;
}