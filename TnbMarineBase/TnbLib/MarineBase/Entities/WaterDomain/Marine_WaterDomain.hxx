#pragma once
#ifndef _Marine_WaterDomain_Header
#define _Marine_WaterDomain_Header

#include <Global_Done.hxx>
#include <Marine_CoordinatedEntity.hxx>
#include <Marine_Module.hxx>
#include <Entity3d_Box.hxx>
#include <OFstream.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Marine_Section;
	class Marine_Domain;
	class Marine_Wave;
	class Marine_Water;

	class Marine_WaterDomain
		: public Marine_CoordinatedEntity
		, public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Marine_Domain> theDomain_;

		std::shared_ptr<Marine_Water> theWater_;
		std::shared_ptr<Marine_Wave> theWave_;

		DECLARE_SAVE_LOAD_HEADER(TnbMarine_EXPORT);
		
	protected:

		Marine_WaterDomain()
		{}

	public:

		TnbMarine_EXPORT Marine_WaterDomain
		(
			const std::shared_ptr<Marine_Domain>& theDomain,
			const std::shared_ptr<Marine_Water>& theWater,
			const std::shared_ptr<Marine_Wave>& theWave
		);

		TnbMarine_EXPORT Marine_WaterDomain
		(
			std::shared_ptr<Marine_Domain>&& theDomain,
			std::shared_ptr<Marine_Water>&& theWater,
			std::shared_ptr<Marine_Wave>&& theWave
		);

		TnbMarine_EXPORT Marine_WaterDomain
		(
			const Standard_Integer theIndex, 
			const word& theName, 
			const std::shared_ptr<Marine_Domain>& theDomain,
			const std::shared_ptr<Marine_Water>& theWater,
			const std::shared_ptr<Marine_Wave>& theWave
		);

		TnbMarine_EXPORT Marine_WaterDomain
		(
			const Standard_Integer theIndex,
			const word& theName,
			std::shared_ptr<Marine_Domain>&& theDomain,
			std::shared_ptr<Marine_Water>&& theWater,
			std::shared_ptr<Marine_Wave>&& theWave
		);

	public:

		//Standard_Real Z() const;

		const auto& Domain() const
		{
			return theDomain_;
		}

		const auto& Water() const
		{
			return theWater_;
		}

		const auto& Wave() const
		{
			return theWave_;
		}

		TnbMarine_EXPORT void ExportToPlt(OFstream& File) const;
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Marine_WaterDomain);

#endif // !_Marine_WaterDomain_Header
