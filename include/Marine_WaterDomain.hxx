#pragma once
#ifndef _Marine_WaterDomain_Header
#define _Marine_WaterDomain_Header

#include <Global_Done.hxx>
#include <Marine_Entity.hxx>
#include <Entity3d_Box.hxx>
#include <OFstream.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Marine_Section;
	class Marine_Domain;
	class Marine_Wave;

	class Marine_WaterDomain
		: public Marine_Entity
		, public Global_Done
	{

		/*Private Data*/

		std::vector<std::shared_ptr<Marine_Section>> theWaters_;

		std::shared_ptr<Marine_Domain> theDomain_;
		std::shared_ptr<Marine_Wave> theWave_;

	protected:

		Marine_WaterDomain
		(
			const std::shared_ptr<Marine_Domain>& theDomain
		);

		Marine_WaterDomain
		(
			const Standard_Integer theIndex, 
			const std::shared_ptr<Marine_Domain>& theDomain
		);

		Marine_WaterDomain
		(
			const Standard_Integer theIndex, 
			const word& theName, 
			const std::shared_ptr<Marine_Domain>& theDomain
		);

	public:

		virtual Standard_Real Z() const = 0;

		auto& ChangeWaters()
		{
			return theWaters_;
		}

		auto& ChangeWave()
		{
			return theWave_;
		}

		const auto& Domain() const
		{
			return theDomain_;
		}

		const auto& Waters() const
		{
			return theWaters_;
		}

		const auto& Wave() const
		{
			return theWave_;
		}

		void SetWave
		(
			const std::shared_ptr<Marine_Wave>& theWave
		)
		{
			theWave_ = theWave;
		}

		void ExportToPlt(OFstream& File) const;
	};
}

#endif // !_Marine_WaterDomain_Header
