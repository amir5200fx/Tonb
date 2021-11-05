#pragma once
#ifndef _StbGMaker_Creator_Header
#define _StbGMaker_Creator_Header

#include <Global_Serialization.hxx>
#include <Geo_ItemCounter.hxx>
#include <Marine_ShapesFwd.hxx>
#include <StbGMaker_Module.hxx>
#include <Pnt3d.hxx>

#include <memory>
#include <map>

namespace tnbLib
{

	// Forward Declarations
	class StbGMaker_HullCreator;
	class StbGMaker_SailCreator;
	class StbGMaker_TankCreator;
	class Cad2d_Plane;
	class StbGMaker_Model;

	class StbGMaker_Creator
	{

		/*Private Data*/

		std::shared_ptr<StbGMaker_HullCreator> 
			theHullCreator_;

		std::map<Standard_Integer, std::shared_ptr<StbGMaker_TankCreator>> 
			theTankCreators_;
		std::map<Standard_Integer, std::shared_ptr<StbGMaker_SailCreator>>
			theSailCreators_;

		mutable Geo_ItemCounter theTankCounter_;
		mutable Geo_ItemCounter theSailCounter_;


		TNB_SERIALIZATION(TnbStbGMaker_EXPORT);

		auto& TankCounter() const
		{
			return theTankCounter_;
		}

		auto& SailCounter() const
		{
			return theSailCounter_;
		}

		TnbStbGMaker_EXPORT void ImportToTanks
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<StbGMaker_TankCreator>&& theTank
		);

		TnbStbGMaker_EXPORT void ImportToSails
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<StbGMaker_SailCreator>&& theSail
		);
		

	public:

		TnbStbGMaker_EXPORT StbGMaker_Creator();

		auto NbTanks() const
		{
			return (Standard_Integer)theTankCreators_.size();
		}

		auto NbSails() const
		{
			return (Standard_Integer)theSailCreators_.size();
		}

		TnbStbGMaker_EXPORT Standard_Integer
			CreateTankMaker();

		TnbStbGMaker_EXPORT Standard_Integer
			CreateTankMaker
			(
				const std::shared_ptr<marineLib::Shape_Tank>& theTank
			);

		TnbStbGMaker_EXPORT Standard_Integer
			CreateShapeGeomSailMaker();

		TnbStbGMaker_EXPORT Standard_Integer
			CreateShapeGeomSailMaker
			(
				const std::shared_ptr<marineLib::Shape_Sail>& theSail
			);

		TnbStbGMaker_EXPORT Standard_Integer
			CreateConstAreaSailMaker
			(
				const Standard_Real theArea,
				const Standard_Real theZbar
			);

		TnbStbGMaker_EXPORT Standard_Integer
			CreatePlaneGeomSailMaker
			(
				const std::shared_ptr<Cad2d_Plane>& thePlane
			);

		TnbStbGMaker_EXPORT Standard_Integer
			CreatePlaneGeomSailMaker
			(
				std::shared_ptr<Cad2d_Plane>&& thePlane
			);

		TnbStbGMaker_EXPORT std::shared_ptr<StbGMaker_TankCreator>
			SelectTankMaker
			(
				const Standard_Integer theIndex
			) const;

		TnbStbGMaker_EXPORT std::shared_ptr<StbGMaker_SailCreator>
			SelectSailMaker
			(
				const Standard_Integer theIndex
			) const;

		TnbStbGMaker_EXPORT std::shared_ptr<StbGMaker_TankCreator>
			RemoveTankMaker
			(
				const Standard_Integer theIndex
			);

		TnbStbGMaker_EXPORT std::shared_ptr<StbGMaker_SailCreator>
			RemoveSailMaker
			(
				const Standard_Integer theIndex
			);

		TnbStbGMaker_EXPORT std::shared_ptr<StbGMaker_HullCreator>
			RemoveHullMaker();

		const auto& HullMaker() const
		{
			return theHullCreator_;
		}

		const auto& TankMakers() const
		{
			return theTankCreators_;
		}

		const auto& SailMakers() const
		{
			return theSailCreators_;
		}

		TnbStbGMaker_EXPORT std::shared_ptr<StbGMaker_Model> ExportModel() const;

		TnbStbGMaker_EXPORT void CreateHullMaker();

		TnbStbGMaker_EXPORT void CreateHullMaker
		(
			const std::shared_ptr<marineLib::Shape_Hull>& theHull
		);

		TnbStbGMaker_EXPORT void ExportAs(std::shared_ptr<StbGMaker_Model>& theModel) const;

	};
}

#endif // !_StbGMaker_Creator_Header
