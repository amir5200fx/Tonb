#pragma once
#ifndef _Cad2d_CrvsIntsct_Header
#define _Cad2d_CrvsIntsct_Header

#include <Cad2d_Module.hxx>
#include <Global_Done.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations [1/27/2022 Amir]
	class Cad2d_SearchCrv;
	class Cad2d_IntsctEntity_Pair;

	class Cad2d_CrvsIntsct
		: public Global_Done
	{

		/*Private Data*/

		// input data [1/27/2022 Amir]

		std::shared_ptr<Cad2d_SearchCrv> theEngine_;

		Standard_Real theTolerance_;

		// outputs [1/27/2022 Amir]

		std::vector<std::shared_ptr<Cad2d_IntsctEntity_Pair>> theEntities_;


		// private functions and operators [1/27/2022 Amir]

		auto& EntitiesRef()
		{
			return theEntities_;
		}

	public:

		static TnbCad2d_EXPORT const Standard_Real DEFAULT_TOLERANCE;

		// default constructor [1/27/2022 Amir]

		

		// constructors [1/27/2022 Amir]

		Cad2d_CrvsIntsct
		(
			const std::shared_ptr<Cad2d_SearchCrv>& theEngine
		)
			: theEngine_(theEngine)
			, theTolerance_(DEFAULT_TOLERANCE)
		{}

		Cad2d_CrvsIntsct
		(
			const std::shared_ptr<Cad2d_SearchCrv>& theEngine,
			const Standard_Real theTolerance
		)
			: theEngine_(theEngine)
			, theTolerance_(theTolerance)
		{}

		// public functions and operators [1/27/2022 Amir]

		auto Tolerance() const
		{
			return theTolerance_;
		}

		const auto& Engine() const
		{
			return theEngine_;
		}

		const auto& Entities() const
		{
			return theEntities_;
		}

		TnbCad2d_EXPORT void Perform();

		void SetTolerance(const Standard_Real theTol)
		{
			theTolerance_ = theTol;
		}
	};
}

#endif // !_Cad2d_CrvsIntsct_Header
