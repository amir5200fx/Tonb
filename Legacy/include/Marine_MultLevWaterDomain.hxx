#pragma once
#ifndef _Marine_MultLevWaterDomain_Header
#define _Marine_MultLevWaterDomain_Header

#include <Marine_Entity.hxx>
#include <Marine_Module.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Marine_WaterDomain;
	class Marine_WaterLib;
	class Marine_Domain;
	class Marine_Body;

	class Marine_MultLevWaterDomain
		: public Marine_Entity
	{

		friend class Marine_WaterLib;

		/*Private Data*/

		std::shared_ptr<Marine_Domain> theDomain_;
		std::shared_ptr<Marine_Body> theBody_;

		std::vector<std::shared_ptr<Marine_WaterDomain>> theWaters_;


		TNB_SERIALIZATION(TnbMarine_EXPORT);
		

	public:

		//- default constructor

		Marine_MultLevWaterDomain()
		{}


		//- constructors

		TnbMarine_EXPORT Marine_MultLevWaterDomain
		(
			const Standard_Integer theIndex, 
			const word& theName
		);

		TnbMarine_EXPORT Marine_MultLevWaterDomain
		(
			const std::shared_ptr<Marine_Domain>& theDomain,
			const std::shared_ptr<Marine_Body>& theBody,
			const std::vector<std::shared_ptr<Marine_WaterDomain>>& theWaters
		);

		TnbMarine_EXPORT Marine_MultLevWaterDomain
		(
			const Standard_Integer theIndex, 
			const word& theName, 
			const std::shared_ptr<Marine_Domain>& theDomain,
			const std::shared_ptr<Marine_Body>& theBody, 
			const std::vector<std::shared_ptr<Marine_WaterDomain>>& theWaters
		);

		TnbMarine_EXPORT Marine_MultLevWaterDomain
		(
			std::shared_ptr<Marine_Domain>&& theDomain,
			std::shared_ptr<Marine_Body>&& theBody,
			std::vector<std::shared_ptr<Marine_WaterDomain>>&& theWaters
		);

		TnbMarine_EXPORT Marine_MultLevWaterDomain
		(
			const Standard_Integer theIndex, 
			const word& theName,
			std::shared_ptr<Marine_Domain>&& theDomain,
			std::shared_ptr<Marine_Body>&& theBody,
			std::vector<std::shared_ptr<Marine_WaterDomain>>&& theWaters
		);



		//- public functions and operators

		const auto& Domain() const
		{
			return theDomain_;
		}

		const auto& Body() const
		{
			return theBody_;
		}

		const auto& Waters() const
		{
			return theWaters_;
		}

		void SetBody
		(
			const std::shared_ptr<Marine_Body>& theBody
		)
		{
			theBody_ = theBody;
		}

		void SetBody
		(
			std::shared_ptr<Marine_Body>&& theBody
		)
		{
			theBody_ = std::move(theBody);
		}

		void SetWaters
		(
			const std::vector<std::shared_ptr<Marine_WaterDomain>>&& theWaters
		)
		{
			theWaters_ = std::move(theWaters);
		}

		void SetWaters
		(
			const std::vector<std::shared_ptr<Marine_WaterDomain>>& theWaters
		)
		{
			theWaters_ = theWaters;
		}

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

BOOST_CLASS_EXPORT_KEY(tnbLib::Marine_MultLevWaterDomain);

#endif // !_Marine_MultLevWaterDomain_Header
