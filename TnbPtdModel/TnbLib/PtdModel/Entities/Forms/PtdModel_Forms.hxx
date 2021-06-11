#pragma once
#ifndef _PtdModel_Forms_Header
#define _PtdModel_Forms_Header

#include <Standard_TypeDef.hxx>
#include <Global_Serialization.hxx>
#include <PtdModel_Module.hxx>

#include <word.hxx>

#include <map>
#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class PtdModel_Form;

	class PtdModel_Forms
	{

		/*Private Data*/

		std::map<word, std::shared_ptr<PtdModel_Form>> theForms_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbPtdModel_EXPORT);

	public:

		//- default constructor

		PtdModel_Forms()
		{}

		//- constructors


		//- public functions and operators

		inline Standard_Integer NbForms() const;

		const auto& Forms() const
		{
			return theForms_;
		}

		void Import(const std::shared_ptr<PtdModel_Form>&);
		void Import(std::shared_ptr<PtdModel_Form>&&);
	};
}

#include <PtdModel_FormsI.hxx>

#endif // !_PtdModel_Forms_Header
