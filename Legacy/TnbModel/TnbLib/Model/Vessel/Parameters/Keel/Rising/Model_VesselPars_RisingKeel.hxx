#pragma once
#ifndef _Model_VesselPars_RisingKeel_Header
#define _Model_VesselPars_RisingKeel_Header

#include <Model_VesselPars_Keel.hxx>
#include <Model_Parameter.hxx>
#include <Global_AccessMethod.hxx>

#include <memory>

namespace tnbLib
{

	class Model_VesselPars_RisingKeel
		: public Model_VesselPars_Keel
	{

		/*Private Data*/

		std::shared_ptr<Model_Parameter> thePosition_;
		//std::shared_ptr<Model_Parameter> theDepthAtTransom_;

	protected:

		// default constructor [12/22/2022 Payvand]

		Model_VesselPars_RisingKeel()
		{}


		// constructors [12/22/2022 Payvand]

	public:

		// Public functions and operators [12/22/2022 Payvand]


		// Macros [12/22/2022 Payvand]

		GLOBAL_ACCESS_SINGLE(std::shared_ptr<Model_Parameter>, Position)
			//GLOBAL_ACCESS_SINGLE(std::shared_ptr<Model_Parameter>, DepthAtTransom)
	};
}

#endif // !_Model_VesselPars_RisingKeel_Header
