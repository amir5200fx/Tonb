#pragma once
#ifndef _PtdModel_ThreeParsForm_Header
#define _PtdModel_ThreeParsForm_Header

#include <PtdModel_Form.hxx>

namespace tnbLib
{

	class PtdModel_ThreeParsForm
		: public PtdModel_Form
	{

		/*Private Data*/

		std::shared_ptr<PtdModel_Par> theX0_;
		std::shared_ptr<PtdModel_Par> theX1_;
		std::shared_ptr<PtdModel_Par> theX2_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbPtdModel_EXPORT);

	public:

		//- default constructor

		PtdModel_ThreeParsForm()
		{}


		//- constructors

		TnbPtdModel_EXPORT PtdModel_ThreeParsForm
		(
			const std::shared_ptr<PtdModel_Par>& theX0, 
			const std::shared_ptr<PtdModel_Par>& theX1,
			const std::shared_ptr<PtdModel_Par>& theX2
		);

		TnbPtdModel_EXPORT PtdModel_ThreeParsForm
		(
			const Standard_Integer theIndex, 
			const word& theName, 
			const std::shared_ptr<PtdModel_Par>& theX0, 
			const std::shared_ptr<PtdModel_Par>& theX1, 
			const std::shared_ptr<PtdModel_Par>& theX2
		);


		//- public functions and operators

		const auto& X0() const
		{
			return theX0_;
		}

		const auto& X1() const
		{
			return theX1_;
		}

		const auto& X2() const
		{
			return theX2_;
		}

		inline void SetX0(std::shared_ptr<PtdModel_Par>&&);
		inline void SetX1(std::shared_ptr<PtdModel_Par>&&);
		inline void SetX2(std::shared_ptr<PtdModel_Par>&&);

		inline void SetX0(const std::shared_ptr<PtdModel_Par>&);
		inline void SetX1(const std::shared_ptr<PtdModel_Par>&);
		inline void SetX2(const std::shared_ptr<PtdModel_Par>&);

		inline void SetX(const Standard_Integer, std::shared_ptr<PtdModel_Par>&&);
		inline void SetX(const Standard_Integer, const std::shared_ptr<PtdModel_Par>&);

		TnbPtdModel_EXPORT Standard_Integer NbParameters() const override;

		TnbPtdModel_EXPORT std::map<word, std::shared_ptr<PtdModel_Par>> Parameters() const override;
	};
}

#include <PtdModel_ThreeParsFormI.hxx> 

BOOST_CLASS_EXPORT_KEY(tnbLib::PtdModel_ThreeParsForm);

#endif // !_PtdModel_ThreeParsForm_Header
