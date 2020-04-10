#pragma once
#ifndef _ShipSMdr_Model_Header
#define _ShipSMdr_Model_Header

#include <ShipSMdr_Entity.hxx>

#include <memory>
#include <map>

namespace tnbLib
{

	// Forward Declarations
	class NModel_Surface;
	class ShipSMdr_Volume;

	class ShipSMdr_Model
		: public ShipSMdr_Entity
	{

		/*Private Data*/

		std::shared_ptr<ShipSMdr_Volume> theHull_;

		std::map<Standard_Integer, std::shared_ptr<ShipSMdr_Volume>>
			theTanks_;

		std::map<Standard_Integer, std::shared_ptr<ShipSMdr_Volume>>
			theCompartments_;

		std::map<Standard_Integer, std::shared_ptr<NModel_Surface>>
			theSurfaces_;


		Standard_Boolean GoodToDelete(const std::shared_ptr<NModel_Surface>& theSurface);

		std::shared_ptr<ShipSMdr_Volume> RemoveFromTanks(const Standard_Integer theIndex);

		std::shared_ptr<ShipSMdr_Volume> RemoveFromCompartments(const Standard_Integer theIndex);

		std::shared_ptr<NModel_Surface> RemoveFromSurfaces(const Standard_Integer theIndex);

		void InsertToTanks(const Standard_Integer theIndex, const std::shared_ptr<ShipSMdr_Volume>& theTank);

		void InsertToCompartments(const Standard_Integer theIndex, const std::shared_ptr<ShipSMdr_Volume>& thePart);

		void InsertToSurfaces(const Standard_Integer theIndex, const std::shared_ptr<NModel_Surface>& theSurface);



	public:

		ShipSMdr_Model();

		const auto& Hull() const
		{
			return theHull_;
		}

		auto NbTanks() const
		{
			return (Standard_Integer)theTanks_.size();
		}

		const auto& Tanks() const
		{
			return theTanks_;
		}

		auto NbCompartments() const
		{
			return (Standard_Integer)theCompartments_.size();
		}

		const auto& Compartments() const
		{
			return theCompartments_;
		}

		auto NbSurfaces() const
		{
			return (Standard_Integer)theSurfaces_.size();
		}

		const auto& Surfaces() const
		{
			return theSurfaces_;
		}

	};
}

#endif // !_ShipSMdr_Model_Header
