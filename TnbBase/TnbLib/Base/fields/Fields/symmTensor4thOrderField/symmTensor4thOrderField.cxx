#include <symmTensor4thOrderField.hxx>

#include <transformField.hxx>
#include <boolList.hxx>

#define TEMPLATE
#include <FieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * global functions  * * * * * * * * * * * * * //

	template<>
	tmp<Field<symmTensor4thOrder> > transformFieldMask<symmTensor4thOrder>
		(
			const symmTensorField& stf
			)
	{
		tmp<symmTensor4thOrderField> tRes(new symmTensor4thOrderField(stf.size()));
		//symmTensor4thOrderField& res = tRes();
		//TFOR_ALL_F_OP_F(symmTensor4thOrder, res, =, symmTensor, stf)
		return tRes;
	}

	template<>
	tmp<Field<symmTensor4thOrder> > transformFieldMask<symmTensor4thOrder>
		(
			const tmp<symmTensorField>& tstf
			)
	{
		tmp<Field<symmTensor4thOrder> > ret = transformFieldMask<symmTensor4thOrder>(tstf());
		tstf.clear();
		return ret;
	}



	// * * * * * * * * * * * * * * * global operators  * * * * * * * * * * * * * //

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <undefFieldFunctionsM.hxx>