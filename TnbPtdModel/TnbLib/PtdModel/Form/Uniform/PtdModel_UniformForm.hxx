#pragma once
#ifndef _PtdModel_UniformForm_Header
#define _PtdModel_UniformForm_Header

#include <PtdModel_Form.hxx>

namespace tnbLib
{

	class PtdModel_UniformForm
		: public PtdModel_Form
	{

		/*Private Data*/

		std::shared_ptr<PtdModel_Par> theValue_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbPtdModel_EXPORT);


		

	public:

		//- default constructor

		PtdModel_UniformForm()
		{}


		//- constructors

		TnbPtdModel_EXPORT PtdModel_UniformForm
		(
			const std::shared_ptr<PtdModel_Par>& x
		);

		TnbPtdModel_EXPORT PtdModel_UniformForm
		(
			const Standard_Integer theIndex, 
			const word& theName,
			const std::shared_ptr<PtdModel_Par>& x
		);


		//- public functions and operators

		TnbPtdModel_EXPORT Standard_Integer NbParameters() const override;

		TnbPtdModel_EXPORT std::map<word, std::shared_ptr<PtdModel_Par>> Parameters() const override;

		TnbPtdModel_EXPORT void SetValue(std::shared_ptr<PtdModel_Par>&&);

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::PtdModel_UniformForm);

#endif // !_PtdModel_UniformForm_Header
