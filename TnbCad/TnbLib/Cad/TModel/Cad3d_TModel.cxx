#include <Cad3d_TModel.hxx>

tnbLib::Cad3d_TModel::Cad3d_TModel()
{
}

tnbLib::Cad3d_TModel::Cad3d_TModel
(
	const Standard_Integer theIndex
)
	: TModel_Entity(theIndex)
{
}

tnbLib::Cad3d_TModel::Cad3d_TModel
(
	const Standard_Integer theIndex,
	const word & theName
)
	: TModel_Entity(theIndex, theName)
{
}

Standard_Integer 
tnbLib::Cad3d_TModel::NbHoles() const
{
	if (Holes())
	{
		return (Standard_Integer)Holes()->size();
	}
	return 0;
}