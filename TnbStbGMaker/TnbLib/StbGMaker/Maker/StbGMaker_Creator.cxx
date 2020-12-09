#include <StbGMaker_Creator.hxx>

#include <StbGMaker_SailCreator.hxx>
#include <StbGMaker_TankCreators.hxx>
#include <StbGMaker_HullCreators.hxx>
#include <StbGMaker_SailCreators.hxx>
#include <StbGMaker_Model.hxx>
#include <Marine_Models.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_SectTools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::StbGMaker_Creator::StbGMaker_Creator()
{
	// empty body
}

namespace tnbLib
{
	std::vector<std::shared_ptr<StbGMaker_WP>> 
		RetrieveWps
		(
			const std::map<Standard_Integer, std::shared_ptr<StbGMaker_WP>>& theMap
		)
	{
		std::vector<std::shared_ptr<StbGMaker_WP>> Wps;
		Wps.reserve(theMap.size());
		for (const auto& x : theMap)
		{
			Debug_Null_Pointer(x.second);
			Wps.push_back(x.second);
		}
		return std::move(Wps);
	}
}

std::shared_ptr<tnbLib::StbGMaker_Model> 
tnbLib::StbGMaker_Creator::ExportModel() const
{
	auto model = std::make_shared<StbGMaker_Model>(0, "model");
	Debug_Null_Pointer(model);

	ExportAs(model);
	return std::move(model);
}

void tnbLib::StbGMaker_Creator::CreateHullMaker()
{
	if (HullMaker())
	{
		FatalErrorIn(FunctionSIG)
			<< "the creator already has a hull maker!" << endl
			<< abort(FatalError);
	}

	theHullCreator_ = std::make_shared<stbGmakerLib::HullCreator_noShape>();
	Debug_Null_Pointer(theHullCreator_);

	theHullCreator_->Index() = 1;
	theHullCreator_->Name() = "hull maker nb. " + std::to_string(theHullCreator_->Index());
}

void tnbLib::StbGMaker_Creator::CreateHullMaker
(
	const std::shared_ptr<marineLib::Shape_Hull>& theHull
)
{
	if (HullMaker())
	{
		FatalErrorIn(FunctionSIG)
			<< "the creator already has a hull maker!" << endl
			<< abort(FatalError);
	}

	theHullCreator_ = std::make_shared<stbGmakerLib::HullCreator_Shape>(theHull);
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
	auto tank = std::make_shared<stbGmakerLib::TankCreator_noShape>();
	Debug_Null_Pointer(tank);

	tank->Index() = TankCounter().RetrieveIndex();
	tank->Name() = "tank maker nb. " + std::to_string(tank->Index());

	const auto id = tank->Index();

	ImportToTanks(id, std::move(tank));

	return id;
}

Standard_Integer 
tnbLib::StbGMaker_Creator::CreateTankMaker
(
	const std::shared_ptr<marineLib::Shape_Tank>& theTank
)
{
	auto tank = std::make_shared<stbGmakerLib::TankCreator_Shape>(theTank);
	Debug_Null_Pointer(tank);

	tank->Index() = TankCounter().RetrieveIndex();
	tank->Name() = "tank maker nb. " + std::to_string(tank->Index());

	const auto id = tank->Index();

	ImportToTanks(id, std::move(tank));

	return id;
}

Standard_Integer
tnbLib::StbGMaker_Creator::CreateShapeGeomSailMaker()
{
	auto sail = std::make_shared<stbGmakerLib::VolumeSailCreator_noShape>();
	Debug_Null_Pointer(sail);

	sail->Index() = SailCounter().RetrieveIndex();
	sail->Name() = "sail maker nb. " + std::to_string(sail->Index());

	const auto id = sail->Index();

	ImportToSails(id, std::move(sail));

	return id;
}

Standard_Integer 
tnbLib::StbGMaker_Creator::CreateShapeGeomSailMaker
(
	const std::shared_ptr<marineLib::Shape_Sail>& theSail
)
{
	auto sail = std::make_shared<stbGmakerLib::VolumeSailCreator_Shape>(theSail);
	Debug_Null_Pointer(sail);

	sail->Index() = SailCounter().RetrieveIndex();
	sail->Name() = "sail maker nb. " + std::to_string(sail->Index());

	const auto id = sail->Index();

	ImportToSails(id, std::move(sail));

	return id;
}

Standard_Integer 
tnbLib::StbGMaker_Creator::CreateConstAreaSailMaker
(
	const Standard_Real theArea, 
	const Standard_Real theZbar
)
{
	auto sail =
		std::make_shared<stbGmakerLib::AreaSailCreator_Const>(theArea, theZbar);
	Debug_Null_Pointer(sail);

	sail->Index() = SailCounter().RetrieveIndex();
	sail->Name() = "sail maker nb. " + std::to_string(sail->Index());

	const auto id = sail->Index();

	ImportToSails(id, std::move(sail));

	return id;
}


Standard_Integer 
tnbLib::StbGMaker_Creator::CreatePlaneGeomSailMaker
(
	const std::shared_ptr<Cad2d_Plane>& thePlane,
	const Standard_Real theZbar
)
{
	auto sail =
		std::make_shared<stbGmakerLib::GeometricSailCreator_Plane>
		(
			thePlane,
			theZbar
			);
	Debug_Null_Pointer(sail);

	sail->Index() = SailCounter().RetrieveIndex();
	sail->Name() = "sail maker nb. " + std::to_string(sail->Index());

	const auto id = sail->Index();

	ImportToSails(id, std::move(sail));

	return id;
}

Standard_Integer
tnbLib::StbGMaker_Creator::CreatePlaneGeomSailMaker
(
	std::shared_ptr<Cad2d_Plane>&& thePlane,
	const Standard_Real theZbar
)
{
	auto sail =
		std::make_shared<stbGmakerLib::GeometricSailCreator_Plane>
		(
			std::move(thePlane), 
			theZbar
			);
	Debug_Null_Pointer(sail);

	sail->Index() = SailCounter().RetrieveIndex();
	sail->Name() = "sail maker nb. " + std::to_string(sail->Index());

	const auto id = sail->Index();

	ImportToSails(id, std::move(sail));

	return id;
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

std::shared_ptr<tnbLib::StbGMaker_HullCreator> 
tnbLib::StbGMaker_Creator::RemoveHullMaker()
{
	auto hull = std::move(theHullCreator_);
	theHullCreator_ = nullptr;
	return std::move(hull);
}

void tnbLib::StbGMaker_Creator::ExportAs
(
	std::shared_ptr<StbGMaker_Model>& theModel
) const
{
	if (NOT HullMaker())
	{
		FatalErrorIn(FunctionSIG)
			<< "there is no hull to extract a model!" << endl
			<< abort(FatalError);
	}

	auto& model = theModel;
	if (NOT model)
	{
		model = std::make_shared<StbGMaker_Model>();
	}

	auto hull = 
		std::dynamic_pointer_cast<marineLib::Model_Hull>
		(
			HullMaker()->ExportModel()
			);
	Debug_Null_Pointer(hull);

	model->ChangeHull() = std::move(hull);

	if (NbTanks())
	{
		model->ChangeTanks().reserve(NbTanks());
		auto& tanks = model->ChangeTanks();

		for (const auto& x : TankMakers())
		{
			Debug_Null_Pointer(x.second);
			const auto& maker = x.second;

			auto tank = 
				std::dynamic_pointer_cast<marineLib::Model_Tank>
				(
					maker->ExportModel()
					);
			Debug_Null_Pointer(tank);

			tanks.push_back(std::move(tank));
		}
	}

	if (NbSails())
	{
		model->ChangeSails().reserve(NbSails());
		auto& sails = model->ChangeSails();

		for (const auto& x : SailMakers())
		{
			Debug_Null_Pointer(x.second);
			const auto& maker = x.second;

			auto sail = 
				std::dynamic_pointer_cast<marineLib::Model_Sail>
				(
					maker->ExportModel()
					);
			Debug_Null_Pointer(sail);

			sails.push_back(std::move(sail));
		}
	}
}