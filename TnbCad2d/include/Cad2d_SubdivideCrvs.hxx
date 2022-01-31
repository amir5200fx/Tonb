#pragma once
#ifndef _Cad2d_SubdivideCrvs_Header
#define _Cad2d_SubdivideCrvs_Header

#include <Global_Done.hxx>

#include <map>
#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations [1/29/2022 Amir]
	class Cad2d_CrvsIntsct;
	class Cad2d_EntityEntityIntersection;
	class Pln_Edge;

	class Cad2d_SubdivideCrvs
		: public Global_Done
	{

		/*Private Data*/

		// inputs [1/29/2022 Amir]

		const std::vector<std::shared_ptr<Cad2d_EntityEntityIntersection>>& theEntities_;

		Standard_Real theTolerance_;

		// outputs [1/30/2022 Amir]

		std::map<Standard_Integer, std::vector<std::shared_ptr<Pln_Edge>>>
			theSubEdges_;


		// Private functions and operators [1/30/2022 Amir]

		auto& SubEdgesRef()
		{
			return theSubEdges_;
		}

	public:

		// default constructor [1/29/2022 Amir]

		

		// constructors [1/29/2022 Amir]

		Cad2d_SubdivideCrvs
		(
			const std::vector<std::shared_ptr<Cad2d_EntityEntityIntersection>>& thePairs,
			const Standard_Real theTolerance
		)
			: theEntities_(thePairs)
			, theTolerance_(theTolerance)
		{}

		// public functions and operators [1/29/2022 Amir]

		const auto& Entities() const
		{
			return theEntities_;
		}

		const auto& SubEdges() const
		{
			return theSubEdges_;
		}

		auto Tolerance() const
		{
			return theTolerance_;
		}

		void Perform();
	};
}

#endif // !_Cad2d_SubdivideCrvs_Header
