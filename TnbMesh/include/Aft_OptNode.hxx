#pragma once
#ifndef _Aft_OptNode_Header
#define _Aft_OptNode_Header

#include <Aft_OptNode_Calculator.hxx>

namespace tnbLib
{

	template<class FrontType, class SizeFun, class MetricFun, class CorrAlg = void, class AltrAlg = void>
	class Aft_OptNode
		: public Aft_OptNode_Calculator<FrontType, SizeFun, MetricFun>
	{

		/*Private Data*/

	public:

		// default constructor [3/1/2022 Amir]

		Aft_OptNode()
		{}

		// constructors [3/1/2022 Amir]


		// override functions and operators [3/1/2022 Amir]

		void Perform() override;

	};


	
}

#include <Aft_OptNodeI.hxx>

#include <Aft_OptNode_Uniform.hxx>
#include <Aft_OptNode_Adaptive.hxx>
#include <Aft_OptNodeAnIso_Standard.hxx>
#include <Aft_OptNodeAnIso_Adaptive.hxx>

#endif // !_Aft_OptNode_Header
