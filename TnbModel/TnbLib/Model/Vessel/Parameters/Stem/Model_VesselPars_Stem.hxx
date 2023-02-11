#pragma once
#ifndef _Model_VesselPars_Stem_Header
#define _Model_VesselPars_Stem_Header

#include <Model_Parameter.hxx>
#include <Global_AccessMethod.hxx>

#include <memory>

namespace tnbLib
{

	class Model_VesselPars_Stem
	{

		/*Private Data*/

		std::shared_ptr<Model_Parameter> theBowRounding_;
		std::shared_ptr<Model_Parameter> theStemRake_;
		std::shared_ptr<Model_Parameter> theForeFootShape_;

	protected:

		// default constructor [12/22/2022 Payvand]

		Model_VesselPars_Stem()
		{}


		// constructors [12/22/2022 Payvand]

	public:

		// Public functions and operators [12/22/2022 Payvand]

		// Macros [12/22/2022 Payvand]

		GLOBAL_ACCESS_SINGLE(std::shared_ptr<Model_Parameter>, BowRounding)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<Model_Parameter>, StemRake)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<Model_Parameter>, ForeFootShape)

	};
}

#endif // !_Model_VesselPars_Stem_Header
