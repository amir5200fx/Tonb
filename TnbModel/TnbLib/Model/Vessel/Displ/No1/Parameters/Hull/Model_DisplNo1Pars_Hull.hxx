#pragma once
#ifndef _Model_DisplNo1Pars_Hull_Header
#define _Model_DisplNo1Pars_Hull_Header

#include <Model_DisplNo1Pars_AftSection.hxx>
#include <Model_DisplNo1Pars_MidSection.hxx>
#include <Model_DisplNo1Pars_FwdSection.hxx>

namespace tnbLib
{

	class Model_DisplNo1Pars_Hull
	{

		/*Private Data*/

		Model_DisplNo1Pars_AftSection theAftSection_;
		Model_DisplNo1Pars_MidSection theMidSection_;
		Model_DisplNo1Pars_FwdSection theFwdSection_;

		std::shared_ptr<Model_Parameter> theMaxAreaLocation_;
		std::shared_ptr<Model_Parameter> theFwdFullness_;
		std::shared_ptr<Model_Parameter> theAftFullness_;

	public:

		// default constructor [12/22/2022 Payvand]

		Model_DisplNo1Pars_Hull()
		{}


		// constructors [12/22/2022 Payvand]


		// Public functions and operators [12/22/2022 Payvand]


		// Macros [12/22/2022 Payvand]

		GLOBAL_ACCESS_SINGLE(Model_DisplNo1Pars_AftSection, AftSection)
			GLOBAL_ACCESS_SINGLE(Model_DisplNo1Pars_MidSection, MidSection)
			GLOBAL_ACCESS_SINGLE(Model_DisplNo1Pars_FwdSection, FwdSection)

			GLOBAL_ACCESS_SINGLE(std::shared_ptr<Model_Parameter>, MaxAreaLocation)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<Model_Parameter>, FwdFullness)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<Model_Parameter>, AftFullness)

	};
}

#endif // !_Model_DisplNo1Pars_Hull_Header
