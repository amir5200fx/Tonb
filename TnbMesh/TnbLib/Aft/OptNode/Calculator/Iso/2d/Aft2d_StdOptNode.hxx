#pragma once
#ifndef _Aft2d_StdOptNode_Header
#define _Aft2d_StdOptNode_Header

#include <Aft2d_OptNode_Calculator.hxx>

namespace tnbLib
{

	class Aft2d_StdOptNode
		: public Aft2d_OptNode_Calculator
	{

		/*Private Data*/

	public:

		// default constructor [11/27/2021 Amir]

		Aft2d_StdOptNode()
		{}


		// constructors [11/27/2021 Amir     

		void Perform() override;

	};
}

#endif // !_Aft2d_StdOptNode_Header
