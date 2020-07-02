#include <StbGMaker_Creator.hxx>

#include <StbGMaker_SailCreator.hxx>
#include <StbGMaker_TankCreator.hxx>
#include <StbGMaker_HullCreator.hxx>
#include <error.hxx>
#include <OSstream.hxx>

tnbLib::StbGMaker_Creator::StbGMaker_Creator()
{
}

void tnbLib::StbGMaker_Creator::CreateHullMaker()
{
	theHullCreator_ = std::make_shared<StbGMaker_HullCreator>();
	Debug_Null_Pointer(theHullCreator_);

	theHullCreator_->Index() = 1;
	theHullCreator_->Name() = "hull maker nb. " + std::to_string(theHullCreator_->Index());
}

void tnbLib::StbGMaker_Creator::CreateHullMaker
(
	const std::shared_ptr<marineLib::Shape_Hull>& theHull
)
{
	theHullCreator_ = std::make_shared<StbGMaker_HullCreator>(theHull);
	Debug_Null_Pointer(theHullCreator_);

	theHullCreator_->Index() = 1;
	theHullCreator_->Name() = "hull maker nb. " + std::to_string(theHullCreator_->Index());
}

void tnbLib::StbGMaker_Creator::ImportToTanks
(
	const Standard_Integer theIndex,
	const std::shared_ptr<StbGMaker_TankCreator>&& theTank
)
{
	auto paired = std::make_pair(theIndex, std::move(theTank));
	auto insert = theTankCreators_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn
		(
			"void ImportToTanks(const Standard_Integer theIndex,"
			"const std::shared_ptr<StbGMaker_TankCreator>&& theTank)"
		)
			<< "duplicate data!" << endl
			<< "index = " << theIndex << endl
			<< abort(FatalError);
	}
}

void tnbLib::StbGMaker_Creator::ImportToSails
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<StbGMaker_SailCreator>&& theSail
)
{
	auto paired = std::make_pair(theIndex, std::move(theSail));
	auto insert = theSailCreators_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn
		(
			"void ImportToSails(const Standard_Integer theIndex,"
			"const std::shared_ptr<StbGMaker_SailCreator>&& theSail)"
		)
			<< "duplicate data!" << endl
			<< "index = " << theIndex << endl
			<< abort(FatalError);
	}
}

Standard_Integer 
tnbLib::StbGMaker_Creator::CreateTankMaker()
{
	auto tank = std::make_shared<StbGMaker_TankCreator>();
	Debug_Null_Pointer(tank);

	tank->Index() = TankCounter().RetrieveIndex();
	tank->Name() = "tank maker nb. " + std::to_string(tank->Index());

	ImportToTanks(tank->Index(), std::move(tank));

	return tank->Index();
}

Standard_Integer 
tnbLib::StbGMaker_Creator::CreateTankMaker
(
	const std::shared_ptr<marineLib::Shape_Tank>& theTank
)
{
	auto tank = std::make_shared<StbGMaker_TankCreator>(theTank);
	Debug_Null_Pointer(tank);

	tank->Index() = TankCounter().RetrieveIndex();
	tank->Name() = "tank maker nb. " + std::to_string(tank->Index());

	ImportToTanks(tank->Index(), std::move(tank));

	return tank->Index();
}

Standard_Integer
tnbLib::StbGMaker_Creator::CreateSailMaker()
{
	auto sail = std::make_shared<StbGMaker_SailCreator>();
	Debug_Null_Pointer(sail);

	sail->Index() = SailCounter().RetrieveIndex();
	sail->Name() = "sail maker nb. " + std::to_string(sail->Index());

	ImportToSails(sail->Index(), std::move(sail));

	return sail->Index();
}

Standard_Integer 
tnbLib::StbGMaker_Creator::CreateSailMaker
(
	const std::shared_ptr<marineLib::Shape_Sail>& theSail
)
{
	auto sail = std::make_shared<StbGMaker_SailCreator>(theSail);
	Debug_Null_Pointer(sail);

	sail->Index() = SailCounter().RetrieveIndex();
	sail->Name() = "sail maker nb. " + std::to_string(sail->Index());

	ImportToSails(sail->Index(), std::move(sail));

	return sail->Index();
}

std::shared_ptr<tnbLib::StbGMaker_TankCreator> 
tnbLib::StbGMaker_Creator::SelectTankMaker
(
	const Standard_Integer theIndex
) const
{
	auto iter = theTankCreators_.find(theIndex);
	if (iter IS_EQUAL theTankCreators_.end())
	{
		FatalErrorIn("std::shared_ptr<StbGMaker_TankCreator> SelectTankMaker(const Standard_Integer theIndex) const")
			<< "the tank maker is not in the creator's tree!" << endl
			<< abort(FatalError);
	}
	return iter->second;
}

std::shared_ptr<tnbLib::StbGMaker_SailCreator> 
tnbLib::StbGMaker_Creator::SelectSailMaker
(
	const Standard_Integer theIndex
) const
{
	auto iter = theSailCreators_.find(theIndex);
	if (iter IS_EQUAL theSailCreators_.end())
	{
		FatalErrorIn("std::shared_ptr<StbGMaker_SailCreator> SelectSailMaker(const Standard_Integer theIndex) const")
			<< "the sail maker is not in the creator's tree!" << endl
			<< abort(FatalError);
	}
	return iter->second;
}

std::shared_ptr<tnbLib::StbGMaker_TankCreator> 
tnbLib::StbGMaker_Creator::RemoveTankMaker(const Standard_Integer theIndex)
{
	auto iter = theTankCreators_.find(theIndex);
	if (iter IS_EQUAL theTankCreators_.end())
	{
		FatalErrorIn("std::shared_ptr<StbGMaker_TankCreator> RemoveTankMaker(const Standard_Integer theIndex)")
			<< "the tank maker is not in the creator's tree!" << endl
			<< "index = " << theIndex << endl
			<< abort(FatalError);
	}
	auto item = std::move(iter->second);
	theTankCreators_.erase(iter);

	TankCounter().ReturnToCounter(item->Index());

	return std::move(item);
}

std::shared_ptr<tnbLib::StbGMaker_SailCreator> 
tnbLib::StbGMaker_Creator::RemoveSailMaker(const Standard_Integer theIndex)
{
	auto iter = theSailCreators_.find(theIndex);
	if (iter IS_EQUAL theSailCreators_.end())
	{
		FatalErrorIn("std::shared_ptr<StbGMaker_SailCreator> RemoveSailMaker(const Standard_Integer theIndex)")
			<< "the sail maker is not int the creator's tree!" << endl
			<< "index = " << theIndex << endl
			<< abort(FatalError);
	}
	auto item = std::move(iter->second);
	theSailCreators_.erase(iter);

	SailCounter().ReturnToCounter(item->Index());

	return std::move(item);
}