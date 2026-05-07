#pragma once
#ifndef _Cad_MergeParaCurves_Header
#define _Cad_MergeParaCurves_Header

#include <Global_Done.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	namespace cadLib
	{
		namespace mergeParaCurves
		{

			// Forward Declarations [6/4/2022 Amir]
			class Node;
			class Link;
			class Segment;
			class Ring;
			class Curve;
			class Wire;
		}
	}

	class Cad_MergeParaCurves
		: public Global_Done
	{

		/*Private Data*/

		// inputs [6/4/2022 Amir]
		std::vector<std::shared_ptr<cadLib::mergeParaCurves::Wire>> theWires_;


	public:

		// default constructor [6/4/2022 Amir]

		Cad_MergeParaCurves()
		{}


		// constructors [6/4/2022 Amir]


		// public functions and operators [6/4/2022 Amir]

		const auto& Wires() const
		{
			return theWires_;
		}

		void Perform();

		void SetCurves(const std::vector<std::shared_ptr<cadLib::mergeParaCurves::Wire>>& theWires)
		{
			theWires_ = theWires;
		}

		void SetCurves(std::vector<std::shared_ptr<cadLib::mergeParaCurves::Wire>>&& theWires)
		{
			theWires_ = std::move(theWires);
		}
	};
}

#endif // !_Cad_MergeParaCurves_Header
