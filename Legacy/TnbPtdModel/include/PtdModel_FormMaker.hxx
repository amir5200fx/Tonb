#pragma once
#ifndef _PtdModel_FormMaker_Header
#define _PtdModel_FormMaker_Header

#include <Global_Done.hxx>
#include <PtdModel_Entity.hxx>

#include <memory>
#include <vector>
#include <map>

namespace tnbLib
{

	// Forward Declarations
	class PtdModel_Form;
	class PtdModel_Par;
	class PtdModel_Profile;
	class PtdModel_GlobalPars;

	class PtdModel_FormMaker
		: public PtdModel_Entity
		, public Global_Done
	{

		/*Private Data*/

		std::map<word, std::shared_ptr<PtdModel_Par>> theParameters_;

	protected:

		//- default constructor

		PtdModel_FormMaker()
		{}


		//- constructors


	public:


		//- public functions and operators

		TnbPtdModel_EXPORT std::shared_ptr<PtdModel_Par> Parameter(const word&) const;
		TnbPtdModel_EXPORT std::vector<word> RetrieveParameters() const;

		TnbPtdModel_EXPORT void SetParameter(const word&, const std::shared_ptr<PtdModel_Par>&);
		TnbPtdModel_EXPORT void SetParameter(const word&, std::shared_ptr<PtdModel_Par>&&);

		virtual Standard_Integer NbParameters() const = 0;
		virtual word GetTypeName() const = 0;

		virtual word Parameter(const Standard_Integer theIndex) const = 0;

		virtual std::shared_ptr<PtdModel_Form> CreateForm() const = 0;
		virtual std::shared_ptr<PtdModel_Profile> CreateProfile(const std::shared_ptr<PtdModel_GlobalPars>&, const std::shared_ptr<PtdModel_Form>&) const = 0;

	};
}

#endif // !_PtdModel_FormMaker_Header
