#pragma once
#ifndef _PtdModel_BladeFormNo1_Header
#define _PtdModel_BladeFormNo1_Header

#include <Global_Done.hxx>
#include <word.hxx>
#include <PtdModel_Module.hxx>

#include <memory>
#include <vector>
#include <map>

namespace tnbLib
{

	// Forward Declarations
	class PtdModel_Form;
	class PtdModel_Par;
	class PtdModel_BladeProfile;
	class PtdModel_BladeGlobalPars;

	class PtdModel_BladeFormNo1
		: public Global_Done
	{


		/*Private Data*/

		std::map<word, std::shared_ptr<PtdModel_Par>> theParameters_;

	protected:

		//- default constructor

		PtdModel_BladeFormNo1()
		{}


		//- constructors


	public:


		//- public functions and operators

		TnbPtdModel_EXPORT std::shared_ptr<PtdModel_Par> Parameter(const word&) const;
		TnbPtdModel_EXPORT std::vector<word> RetrieveParameters() const;

		TnbPtdModel_EXPORT void SetParameter(const word&, const std::shared_ptr<PtdModel_Par>&);
		TnbPtdModel_EXPORT void SetParameter(const word&, std::shared_ptr<PtdModel_Par>&&);

		virtual Standard_Integer NbParameters() const = 0;

		virtual word Parameter(const Standard_Integer theIndex) const = 0;

		virtual std::shared_ptr<PtdModel_Form> CreateForm() const = 0;
		virtual std::shared_ptr<PtdModel_BladeProfile> CreateProfile(const std::shared_ptr<PtdModel_BladeGlobalPars>&, const std::shared_ptr<PtdModel_Form>&) const = 0;
	};
}

#endif // !_PtdModel_BladeFormNo1_Header
