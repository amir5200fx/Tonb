#pragma once
#ifndef _Model_VesselPars_StdSection_Header
#define _Model_VesselPars_StdSection_Header

#include <Model_Parameter.hxx>
#include <Global_AccessMethod.hxx>

#include <memory>

namespace tnbLib
{

	class Model_VesselPars_StdSection
	{

		/*Private Data*/

		std::shared_ptr<Model_Parameter> theDeadrise_;
		std::shared_ptr<Model_Parameter> theSideslope_;

	protected:

		// default constructor [12/22/2022 Payvand]

		Model_VesselPars_StdSection()
		{}

		// Public functions and operators [12/22/2022 Payvand]

	public:

		// Public functions and operators [12/22/2022 Payvand]


		// Macros [12/22/2022 Payvand]

		GLOBAL_ACCESS_SINGLE(std::shared_ptr<Model_Parameter>, Deadrise)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<Model_Parameter>, Sideslope)
	};
}

#endif // !_Model_VesselPars_StdSection_Header
