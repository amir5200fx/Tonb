#pragma once
#ifndef _Model_VesselPars_Dimens_Header
#define _Model_VesselPars_Dimens_Header

#include <Model_Parameter.hxx>
#include <Global_AccessMethod.hxx>

#include <memory>

namespace tnbLib
{

	class Model_VesselPars_Dimens
	{

		/*Private Data*/

		std::shared_ptr<Model_Parameter> theDepthAtBow_;
		std::shared_ptr<Model_Parameter> theDepthAtTransom_;

		std::shared_ptr<Model_Parameter> theBeamOnDeck_;
		std::shared_ptr<Model_Parameter> theLengthOnDeck_;

		Standard_Integer theNbNetRows_;
		Standard_Integer theNbNetColumns_;

	protected:

		// default constructor [12/21/2022 Payvand]

		Model_VesselPars_Dimens()
			: theNbNetRows_(0)
			, theNbNetColumns_(0)
		{}

		// constructors [12/21/2022 Payvand]

	public:

		// Public functions and operators [12/21/2022 Payvand]

		// Macros [12/21/2022 Payvand]

		GLOBAL_ACCESS_SINGLE(std::shared_ptr<Model_Parameter>, DepthAtBow)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<Model_Parameter>, DepthAtTransom)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<Model_Parameter>, BeamOnDeck)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<Model_Parameter>, LengthOnDeck)

			GLOBAL_ACCESS_SINGLE(Standard_Integer, NbNetRows)
			GLOBAL_ACCESS_SINGLE(Standard_Integer, NbNetColumns)
	};
}

#endif // !_Model_VesselPars_Dimens_Header
