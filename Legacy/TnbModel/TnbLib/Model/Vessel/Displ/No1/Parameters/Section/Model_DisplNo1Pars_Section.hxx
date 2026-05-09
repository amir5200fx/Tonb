#pragma once
#ifndef _Model_DisplNo1Pars_Section_Header
#define _Model_DisplNo1Pars_Section_Header

#include <Model_VesselPars_StdSection.hxx>

namespace tnbLib
{

	class Model_DisplNo1Pars_Section
		: public Model_VesselPars_StdSection
	{

		/*Private Data*/

		std::shared_ptr<Model_Parameter> theTightness_;
		//std::shared_ptr<Model_Parameter> theFlare_;

	protected:

		// default constructor [12/21/2022 Payvand]

		Model_DisplNo1Pars_Section()
		{}


		// constructors [12/21/2022 Payvand]

	public:


		// Public functions and operators [12/22/2022 Payvand]

		GLOBAL_ACCESS_SINGLE(std::shared_ptr<Model_Parameter>, Tightness)
			//GLOBAL_ACCESS_SINGLE(std::shared_ptr<Model_Parameter>, Flare)
		
	};
}

#endif // !_Model_DisplNo1Pars_Section_Header
