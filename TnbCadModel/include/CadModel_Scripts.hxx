#pragma once
#ifndef _CadModel_Scripts_Header
#define _CadModel_Scripts_Header

#include <memory>

namespace chaiscript
{
	class ChaiScript;
}

namespace tnbLib
{

	// Forward Declarations
	class LegModel_DispNo1;
	class LegModel_NozzleType1;

	namespace script
	{

		struct CadModel
		{

			std::shared_ptr<LegModel_DispNo1> newLegModelDispNo1() const;
			std::shared_ptr<LegModel_NozzleType1> newLegModelNozzelType1() const;

		};

		void load_cad_model(chaiscript::ChaiScript&);
	}
}

#endif // !_CadModel_Scripts_Header
