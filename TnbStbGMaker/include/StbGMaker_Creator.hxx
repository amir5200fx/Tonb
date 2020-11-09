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


		DECLARE_SAVE_LOAD_HEADER(TnbStbGMaker_EXPORT);

		auto& TankCounter() const
		{
			return theTankCounter_;
		}

		auto& SailCounter() const
		{
			return theSailCounter_;
		}

		void ImportToTanks
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<StbGMaker_TankCreator>&& theTank
		);

		void ImportToSails
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<StbGMaker_SailCreator>&& theSail
		);
		

	public:

		StbGMaker_Creator();

		auto NbTanks() const
		{
			return (Standard_Integer)theTankCreators_.size();
		}

		auto NbSails() const
		{
			return (Standard_Integer)theSailCreators_.size();
		}

		Standard_Integer 
			CreateTankMaker();

		Standard_Integer 
			CreateTankMaker
			(
				const std::shared_ptr<marineLib::Shape_Tank>& theTank
			);

		Standard_Integer 
			CreateShapeGeomSailMaker();

		Standard_Integer 
			CreateShapeGeomSailMaker
			(
				const std::shared_ptr<marineLib::Shape_Sail>& theSail
			);

		Standard_Integer 
			CreateConstAreaSailMaker
			(
				const Standard_Real theArea,
				const Standard_Real theZbar
			);

		Standard_Integer 
			CreatePlaneGeomSailMaker
			(
				const std::shared_ptr<Cad2d_Plane>& thePlane,
				const Standard_Real theZbar
			);

		Standard_Integer 
			CreatePlaneGeomSailMaker
			(
				std::shared_ptr<Cad2d_Plane>&& thePlane,
				const Standard_Real theZbar
			);

		std::shared_ptr<StbGMaker_TankCreator> 
			SelectTankMaker
			(
				const Standard_Integer theIndex
			) const;

		std::shared_ptr<StbGMaker_SailCreator> 
			SelectSailMaker
			(
				const Standard_Integer theIndex
			) const;

		std::shared_ptr<StbGMaker_TankCreator> 
			RemoveTankMaker
			(
				const Standard_Integer theIndex
			);

		std::shared_ptr<StbGMaker_SailCreator> 
			RemoveSailMaker
			(
				const Standard_Integer theIndex
			);

		std::shared_ptr<StbGMaker_HullCreator>
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

		std::shared_ptr<StbGMaker_Model> ExportModel() const;

		void CreateHullMaker();

		void CreateHullMaker
		(
			const std::shared_ptr<marineLib::Shape_Hull>& theHull
		);

		void ExportAs(std::shared_ptr<StbGMaker_Model>& theModel) const;

	};
}

#endif // !_StbGMaker_Creator_Header
