#pragma once
#ifndef _Model_DisplNo1Pars_Transom_Header
#define _Model_DisplNo1Pars_Transom_Header

#include <Model_VesselPars_Transom.hxx>

namespace tnbLib
{

	class Model_DisplNo1Pars_Transom
		: public Model_VesselPars_Transom
	{

		/*Private Data*/

		std::shared_ptr<Model_Parameter> theRake_;
		std::shared_ptr<Model_Parameter> theWidth_;

	public:

		// default constructor [12/22/2022 Payvand]

		Model_DisplNo1Pars_Transom()
		{}

		// constructors [12/22/2022 Payvand]


		// Public functions and operators [12/22/2022 Payvand]


		// Macros [12/22/2022 Payvand]

		GLOBAL_ACCESS_SINGLE(std::shared_ptr<Model_Parameter>, Rake)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<Model_Parameter>, Width)

	};
}

#endif // !_Model_DisplNo1Pars_Transom_Header
