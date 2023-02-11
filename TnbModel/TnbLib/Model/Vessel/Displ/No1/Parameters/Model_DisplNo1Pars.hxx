#pragma once
#ifndef _Model_DisplNo1Pars_Header
#define _Model_DisplNo1Pars_Header

#include <Model_DisplNo1Pars_Hull.hxx>
#include <Model_DisplNo1Pars_Keel.hxx>
#include <Model_DisplNo1Pars_Stem.hxx>
#include <Model_DisplNo1Pars_Transom.hxx>
#include <Model_DisplNo1Pars_Dimensions.hxx>

namespace tnbLib
{

	class Model_DisplNo1Pars
	{

		/*Private Data*/

		Model_DisplNo1Pars_Hull theHull_;
		Model_DisplNo1Pars_Keel theKeel_;
		Model_DisplNo1Pars_Stem theStem_;
		Model_DisplNo1Pars_Transom theTransom_;
		Model_DisplNo1Pars_Dimensions theDimensions_;

	public:

		// default constructor [12/22/2022 Payvand]

		Model_DisplNo1Pars()
		{}


		// constructors [12/22/2022 Payvand]


		// Public functions and operators [12/22/2022 Payvand]

		GLOBAL_ACCESS_SINGLE(Model_DisplNo1Pars_Hull, Hull)
			GLOBAL_ACCESS_SINGLE(Model_DisplNo1Pars_Keel, Keel)
			GLOBAL_ACCESS_SINGLE(Model_DisplNo1Pars_Stem, Stem)
			GLOBAL_ACCESS_SINGLE(Model_DisplNo1Pars_Transom, Transom)
			GLOBAL_ACCESS_SINGLE(Model_DisplNo1Pars_Dimensions, Dimensions)
	};
}

#endif // !_Model_DisplNo1Pars_Header
