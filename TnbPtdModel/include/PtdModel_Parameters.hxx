#pragma once
#ifndef _PtdModel_Parameters_Header
#define _PtdModel_Parameters_Header

#include <Standard_TypeDef.hxx>
#include <word.hxx>
#include <Global_Serialization.hxx>
#include <PtdModel_Module.hxx>

#include <memory>
#include <map>

namespace tnbLib
{

	// Forward Declarations
	class PtdModel_Par;


	class PtdModel_Parameters
	{

		/*Private Data*/

		std::map<word, std::shared_ptr<PtdModel_Par>> theParameters_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbPtdModel_EXPORT);

	protected:

		//- default constructor

		PtdModel_Parameters()
		{}


		//- constructors


	public:

		//- public functions and operators

		inline std::shared_ptr<PtdModel_Par> SelectParameter(const word&) const;

		const auto& Parameters() const
		{
			return theParameters_;
		}
	};
}

#include <PtdModel_ParametersI.hxx>

#endif // !_PtdModel_Parameters_Header
