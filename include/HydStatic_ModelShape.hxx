#pragma once
#ifndef _HydStatic_ModelShape_Header
#define _HydStatic_ModelShape_Header

#include <HydStatic_Entity.hxx>
#include <Marine_LightWeight.hxx>
#include <HydStatic_Module.hxx>

#include <memory>
#include <map>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_HullShape;
	class HydStatic_TankShape;
	class HydStatic_SailShape;
	class Marine_Domain;
	class StbGMaker_Model;

	class HydStatic_ModelShape
		: public HydStatic_Entity
	{

	public:

		typedef std::map
			<
			Standard_Integer,
			std::shared_ptr<HydStatic_TankShape>
			>
			tankMap;

		typedef std::map
			<
			Standard_Integer,
			std::shared_ptr<HydStatic_SailShape>
			>
			sailMap;

	private:

		/*Private Data*/

		std::shared_ptr<HydStatic_HullShape> theHull_;

		std::map<Standard_Integer, std::shared_ptr<HydStatic_TankShape>> theTanks_;
		std::map<Standard_Integer, std::shared_ptr<HydStatic_SailShape>> theSails_;

		Marine_LightWeight theWeight_;

		std::shared_ptr<Marine_Domain> theDomain_;

		//- private functions and operators

		TNB_SERIALIZATION(TnbHydStatic_EXPORT);

	public:

		//- default constructor

		HydStatic_ModelShape()
		{}

		//- constructors


		//- public functions and operators

		const auto& Hull() const
		{
			return theHull_;
		}

		const auto& Tanks() const
		{
			return theTanks_;
		}

		const auto& Sails() const
		{
			return theSails_;
		}

		const auto& LightWeight() const
		{
			return theWeight_;
		}

		const auto& Domain() const
		{
			return theDomain_;
		}

		auto NbTanks() const
		{
			return (Standard_Integer)theTanks_.size();
		}

		auto NbSails() const
		{
			return (Standard_Integer)theSails_.size();
		}

		TnbHydStatic_EXPORT tankMap::const_iterator SelectTank(const Standard_Integer theIndex) const;
		TnbHydStatic_EXPORT sailMap::const_iterator SelectSail(const Standard_Integer theIndex) const;

		TnbHydStatic_EXPORT tankMap::iterator ImportTank(const std::shared_ptr<HydStatic_TankShape>& theTank);
		TnbHydStatic_EXPORT sailMap::iterator ImportSail(const std::shared_ptr<HydStatic_SailShape>& theTank);
		TnbHydStatic_EXPORT tankMap::iterator ImportTank(std::shared_ptr<HydStatic_TankShape>&& theTank);
		TnbHydStatic_EXPORT sailMap::iterator ImportSail(std::shared_ptr<HydStatic_SailShape>&& theTank);

		TnbHydStatic_EXPORT void RemoveTank(const Standard_Integer theIndex);
		TnbHydStatic_EXPORT void RemoveTank(const tankMap::const_iterator& iter);
		TnbHydStatic_EXPORT void RemoveSail(const Standard_Integer theIndex);
		TnbHydStatic_EXPORT void RemoveSail(const sailMap::const_iterator& iter);

		TnbHydStatic_EXPORT void Import(const std::shared_ptr<StbGMaker_Model>& theModel);

		void SetDomain
		(
			const std::shared_ptr<Marine_Domain>& theDomain
		)
		{
			theDomain_ = theDomain;
		}

		void SetDomain
		(
			std::shared_ptr<Marine_Domain>&& theDomain
		)
		{
			theDomain_ = std::move(theDomain);
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::HydStatic_ModelShape);

#endif // !_HydStatic_ModelShape_Header
