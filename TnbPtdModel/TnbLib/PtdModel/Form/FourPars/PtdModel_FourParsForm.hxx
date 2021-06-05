#pragma once
#ifndef _PtdModel_FourParsForm_Header
#define _PtdModel_FourParsForm_Header

#include <PtdModel_Form.hxx>

namespace tnbLib
{

	class PtdModel_FourParsForm
		: public PtdModel_Form
	{

		/*Private Data*/

		std::shared_ptr<PtdModel_Par> theX0_;
		std::shared_ptr<PtdModel_Par> theX1_;
		std::shared_ptr<PtdModel_Par> theX2_;
		std::shared_ptr<PtdModel_Par> theX3_;


		//- private functions and operators


		TNB_SERIALIZATION(TnbPtdModel_EXPORT);

	public:

		//- default constructor

		PtdModel_FourParsForm()
		{}


		//- constructors

		TnbPtdModel_EXPORT PtdModel_FourParsForm
		(
			const std::shared_ptr<PtdModel_Par>& theX0,
			const std::shared_ptr<PtdModel_Par>& theX1,
			const std::shared_ptr<PtdModel_Par>& theX2, 
			const std::shared_ptr<PtdModel_Par>& theX3
		);

		TnbPtdModel_EXPORT PtdModel_FourParsForm
		(
			const Standard_Integer theIndex, 
			const word& theName, 
			const std::shared_ptr<PtdModel_Par>& theX0,
			const std::shared_ptr<PtdModel_Par>& theX1, 
			const std::shared_ptr<PtdModel_Par>& theX2, 
			const std::shared_ptr<PtdModel_Par>& theX3
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

		const auto& X3() const
		{
			return theX3_;
		}

		inline void SetX0(std::shared_ptr<PtdModel_Par>&&);
		inline void SetX1(std::shared_ptr<PtdModel_Par>&&);
		inline void SetX2(std::shared_ptr<PtdModel_Par>&&);
		inline void SetX3(std::shared_ptr<PtdModel_Par>&&);

		inline void SetX0(const std::shared_ptr<PtdModel_Par>&);
		inline void SetX1(const std::shared_ptr<PtdModel_Par>&);
		inline void SetX2(const std::shared_ptr<PtdModel_Par>&);
		inline void SetX3(const std::shared_ptr<PtdModel_Par>&);

		inline void SetX(const Standard_Integer, std::shared_ptr<PtdModel_Par>&&);
		inline void SetX(const Standard_Integer, const std::shared_ptr<PtdModel_Par>&);

		TnbPtdModel_EXPORT Standard_Integer NbParameters() const override;

		TnbPtdModel_EXPORT std::map<word, std::shared_ptr<PtdModel_Par>> Parameters() const override;

	};
}

#include <PtdModel_FourParsFormI.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::PtdModel_FourParsForm);

#endif // !_PtdModel_FourParsForm_Header
