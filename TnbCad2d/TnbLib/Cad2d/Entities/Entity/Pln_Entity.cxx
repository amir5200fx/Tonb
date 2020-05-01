#include <Pln_Entity.hxx>

std::vector<std::shared_ptr<tnbLib::Pln_Entity>>
tnbLib::Pln_Entity::RetrieveEntities
(
	const Pln_EntityType t
) const
{
	std::vector<std::shared_ptr<Pln_Entity>> entities;
	RetrieveEntitiesTo(entities, t);

	return std::move(entities);
}