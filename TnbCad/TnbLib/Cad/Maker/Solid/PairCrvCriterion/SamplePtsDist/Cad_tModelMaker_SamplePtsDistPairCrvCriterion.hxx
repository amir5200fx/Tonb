#pragma once
#ifndef _Cad_tModelMaker_SamplePtsDistPairCrvCriterion_Header
#define _Cad_tModelMaker_SamplePtsDistPairCrvCriterion_Header

#include <Cad_tModelMaker_PairCrvCriterion.hxx>

namespace tnbLib
{

	class Cad_tModelMaker_SamplePtsDistPairCrvCriterion
		: public Cad_tModelMaker_PairCrvCriterion
	{

		/*Private Data*/

	protected:

		// default constructor [1/16/2022 Amir]

		Cad_tModelMaker_SamplePtsDistPairCrvCriterion()
		{}

		// constructors [1/16/2022 Amir]


	public:


	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Cad_tModelMaker_SamplePtsDistPairCrvCriterion);

#endif // !_Cad_tModelMaker_SamplePtsDistPairCrvCriterion_Header
