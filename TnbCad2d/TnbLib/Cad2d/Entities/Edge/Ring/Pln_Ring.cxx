#include <Pln_Ring.hxx>

#include <Pln_Vertex.hxx>

Standard_Integer 
tnbLib::Pln_Ring::NbEntities
(
	const Pln_EntityType t
) const
{
	if (t IS_EQUAL Pln_EntityType::VERTEX)
		return 1;
	if (t IS_EQUAL Pln_EntityType::EDGE)
		return 1;
	return 0;
}

void tnbLib::Pln_Ring::RetrieveEntitiesTo
(
	std::vector<std::shared_ptr<Pln_Entity>>& theEntities,
	const Pln_EntityType t
) const
{
	if (t IS_EQUAL Pln_EntityType::VERTEX)
	{
		theEntities.push_back(Vtx());
	}
	if (t IS_EQUAL Pln_EntityType::EDGE)
	{
		theEntities.push_back(std::dynamic_pointer_cast<Pln_Entity>(This()));
	}
}