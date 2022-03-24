#pragma once
#ifndef _Cad2d_IntsctEntity_Pair_Header
#define _Cad2d_IntsctEntity_Pair_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Global_Serialization.hxx>
#include <Cad2d_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Cad2d_IntsctEntity;

	class Cad2d_IntsctEntity_Pair
		: public Global_Indexed
		, public Global_Named
	{

		/*Private Data*/

		std::shared_ptr<Cad2d_IntsctEntity> theEntity0_;
		std::shared_ptr<Cad2d_IntsctEntity> theEntity1_;


		// private functions and operators [3/22/2022 Amir]

		TNB_SERIALIZATION(TnbCad2d_EXPORT);


		// default constructor [3/22/2022 Amir]

		Cad2d_IntsctEntity_Pair()
		{}

	public:

		//- default constructor


		//- constructors

		Cad2d_IntsctEntity_Pair
		(
			const std::shared_ptr<Cad2d_IntsctEntity>& theEnt0,
			const std::shared_ptr<Cad2d_IntsctEntity>& theEnt1
		)
			: theEntity0_(theEnt0)
			, theEntity1_(theEnt1)
		{}


		Cad2d_IntsctEntity_Pair
		(
			std::shared_ptr<Cad2d_IntsctEntity>&& theEnt0,
			std::shared_ptr<Cad2d_IntsctEntity>&& theEnt1
		)
			: theEntity0_(std::move(theEnt0))
			, theEntity1_(std::move(theEnt1))
		{}

		Cad2d_IntsctEntity_Pair
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<Cad2d_IntsctEntity>& theEnt0,
			const std::shared_ptr<Cad2d_IntsctEntity>& theEnt1
		)
			: Global_Indexed(theIndex)
			, theEntity0_(theEnt0)
			, theEntity1_(theEnt1)
		{}

		Cad2d_IntsctEntity_Pair
		(
			const Standard_Integer theIndex,
			std::shared_ptr<Cad2d_IntsctEntity>&& theEnt0,
			std::shared_ptr<Cad2d_IntsctEntity>&& theEnt1
		)
			: Global_Indexed(theIndex)
			, theEntity0_(std::move(theEnt0))
			, theEntity1_(std::move(theEnt1))
		{}


		//- public functions and operators

		const auto& Entity0() const
		{
			return theEntity0_;
		}

		const auto& Entity1() const
		{
			return theEntity1_;
		}
	};
}

#endif // !_Cad2d_IntsctEntity_Pair_Header
