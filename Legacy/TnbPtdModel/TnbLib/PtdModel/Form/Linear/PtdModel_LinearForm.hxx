#pragma once
#ifndef _PtdModel_LinearForm_Header
#define _PtdModel_LinearForm_Header

#include <PtdModel_Form.hxx>

namespace tnbLib
{

	class PtdModel_LinearForm
		: public PtdModel_Form
	{

		/*Private Data*/

		std::shared_ptr<PtdModel_Par> theX0_;
		std::shared_ptr<PtdModel_Par> theX1_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbPtdModel_EXPORT);

	public:

		//- default constructor

		PtdModel_LinearForm()
		{}

		//- constructors

		TnbPtdModel_EXPORT PtdModel_LinearForm
		(
			const std::shared_ptr<PtdModel_Par>& theX0,
			const std::shared_ptr<PtdModel_Par>& theX1
		);

		TnbPtdModel_EXPORT PtdModel_LinearForm
		(
			const Standard_Integer theIndex, 
			const word& theName, 
			const std::shared_ptr<PtdModel_Par>& theX0, 
			const std::shared_ptr<PtdModel_Par>& theX1
		);


		//- public functions and operators

		inline void SetX(const Standard_Integer, std::shared_ptr<PtdModel_Par>&&);
		inline void SetX(const Standard_Integer, const std::shared_ptr<PtdModel_Par>&);

		TnbPtdModel_EXPORT Standard_Integer NbParameters() const override;

		TnbPtdModel_EXPORT std::map<word, std::shared_ptr<PtdModel_Par>> Parameters() const override;
	};
}

#include <PtdModel_LinearFormI.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::PtdModel_LinearForm);

#endif // !_PtdModel_LinearForm_Header
