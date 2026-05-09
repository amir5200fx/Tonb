#include <StbGMaker_EntityCreator.hxx>

std::shared_ptr<tnbLib::Marine_Model> 
tnbLib::StbGMaker_EntityCreator::ExportModel() const
{
	std::shared_ptr<Marine_Model> model;
	ExportAs(model);
	return std::move(model);
}