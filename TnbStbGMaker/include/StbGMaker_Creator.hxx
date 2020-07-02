#pragma once
#ifndef _StbGMaker_Creator_Header
#define _StbGMaker_Creator_Header

#include <Geo_ItemCounter.hxx>
#include <Marine_ShapesFwd.hxx>

#include <memory>
#include <map>

namespace tnbLib
{

	// Forward Declarations
	class StbGMaker_HullCreator;
	class StbGMaker_SailCreator;
	class StbGMaker_TankCreator;

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
			CreateSailMaker();

		Standard_Integer 
			CreateSailMaker
			(
				const std::shared_ptr<marineLib::Shape_Sail>& theSail
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

		const auto& HullMaker() const
		{
			return theHullCreator_;
		}

		void CreateHullMaker();

		void CreateHullMaker
		(
			const std::shared_ptr<marineLib::Shape_Hull>& theHull
		);
	};
}

#endif // !_StbGMaker_Creator_Header
