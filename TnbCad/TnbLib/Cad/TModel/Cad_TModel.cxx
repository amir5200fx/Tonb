#include <Cad_TModel.hxx>

const std::string tnbLib::Cad_TModel::extension = ".tmodel";

Standard_Integer 
tnbLib::Cad_TModel::NbHoles() const
{
	if (Holes())
	{
		return (Standard_Integer)Holes()->size();
	}
	return 0;
}