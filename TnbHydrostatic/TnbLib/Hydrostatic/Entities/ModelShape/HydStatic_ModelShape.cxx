#include <HydStatic_ModelShape.hxx>

#include <HydStatic_Shapes.hxx>
#include <StbGMaker_Model.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

typename tnbLib::HydStatic_ModelShape::tankMap::const_iterator 
tnbLib::HydStatic_ModelShape::SelectTank
(
	const Standard_Integer theIndex
) const
{
	auto iter = theTanks_.find(theIndex);
	if (iter IS_EQUAL theTanks_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< " the tank is not inside the solution data!" << endl
			<< " - id: " << theIndex << endl
			<< abort(FatalError);
	}
	return std::move(iter);
}

typename tnbLib::HydStatic_ModelShape::sailMap::const_iterator 
tnbLib::HydStatic_ModelShape::SelectSail
(
	const Standard_Integer theIndex
) const
{
	auto iter = theSails_.find(theIndex);
	if (iter IS_EQUAL theSails_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< " the sail is not inside the solution data!" << endl
			<< " - id: " << theIndex << endl
			<< abort(FatalError);
	}
	return std::move(iter);
}

typename tnbLib::HydStatic_ModelShape::tankMap::iterator
tnbLib::HydStatic_ModelShape::ImportTank
(
	const std::shared_ptr<HydStatic_TankShape>& theTank
)
{
	auto paired = std::make_pair(theTank->Index(), theTank);
	auto insert = theTanks_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "unable to insert the tank into the list: duplicate data has been detected!" << endl
			<< abort(FatalError);
	}
	return std::move(insert.first);
}

typename tnbLib::HydStatic_ModelShape::sailMap::iterator
tnbLib::HydStatic_ModelShape::ImportSail
(
	const std::shared_ptr<HydStatic_SailShape>& theSail
)
{
	auto paired = std::make_pair(theSail->Index(), theSail);
	auto insert = theSails_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "unable to insert the sail into the list: duplicate data has been detected!" << endl
			<< abort(FatalError);
	}
	return std::move(insert.first);
}

typename tnbLib::HydStatic_ModelShape::tankMap::iterator
tnbLib::HydStatic_ModelShape::ImportTank
(
	std::shared_ptr<HydStatic_TankShape>&& theTank
)
{
	auto paired = std::make_pair(theTank->Index(), std::move(theTank));
	auto insert = theTanks_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "unable to insert the tank into the list: duplicate data has been detected!" << endl
			<< abort(FatalError);
	}
	return std::move(insert.first);
}

typename tnbLib::HydStatic_ModelShape::sailMap::iterator
tnbLib::HydStatic_ModelShape::ImportSail
(
	std::shared_ptr<HydStatic_SailShape>&& theSail
)
{
	auto paired = std::make_pair(theSail->Index(), std::move(theSail));
	auto insert = theSails_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "unable to insert the sail into the list: duplicate data has been detected!" << endl
			<< abort(FatalError);
	}
	return std::move(insert.first);
}

void tnbLib::HydStatic_ModelShape::RemoveTank
(
	const Standard_Integer theIndex
)
{
	auto tank = SelectTank(theIndex);
	RemoveTank(tank);
}

void tnbLib::HydStatic_ModelShape::RemoveTank
(
	const tankMap::const_iterator & iter
)
{
	theTanks_.erase(iter);
}

void tnbLib::HydStatic_ModelShape::RemoveSail
(
	const Standard_Integer theIndex
)
{
	auto tank = SelectSail(theIndex);
	RemoveSail(tank);
}

void tnbLib::HydStatic_ModelShape::RemoveSail
(
	const sailMap::const_iterator & iter
)
{
	theSails_.erase(iter);
}

void tnbLib::HydStatic_ModelShape::Import
(
	const std::shared_ptr<StbGMaker_Model>& theModel
)
{
	if (NOT theModel)
	{
		FatalErrorIn(FunctionSIG)
			<< " the imported model is null" << endl
			<< abort(FatalError);
	}

	theWeight_ = theModel->LightWeight();
	theDomain_ = theModel->Domain();
	if (NOT theDomain_)
	{
		FatalErrorIn(FunctionSIG)
			<< "no domain has been created!" << endl
			<< abort(FatalError);
	}

	theHull_ = std::make_shared<HydStatic_HullShape>();
	theHull_->SetHull(theModel->Hull());

	for (const auto& x : theModel->Tanks())
	{
		Debug_Null_Pointer(x);

		auto tank = std::make_shared<HydStatic_TankShape>();
		Debug_Null_Pointer(tank);

		tank->SetModel(x);
		ImportTank(std::move(tank));
	}

	for (const auto& x : theModel->Sails())
	{
		Debug_Null_Pointer(x);

		auto sail = std::make_shared<HydStatic_SailShape>();
		Debug_Null_Pointer(sail);

		sail->SetSail(x);
		ImportSail(std::move(sail));
	}
}