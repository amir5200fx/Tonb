#include <expandTensorField.hxx>

#include <tensorField.hxx>
#include <expandTensor.hxx>

#define TEMPLATE
#include <FieldFunctionsM.cxx>

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

	void contractScalar(Field<scalar>& res, const UList<tensor>& f)
	{
		forAll(res, i)
		{
			contractScalar(res[i], f[i]);
		}
	}


	void contractLinear(Field<vector>& res, const UList<tensor>& f)
	{
		forAll(res, i)
		{
			contractLinear(res[i], f[i]);
		}
	}


	void expandScalar(Field<vector>& res, const UList<scalar>& f)
	{
		forAll(res, i)
		{
			expandScalar(res[i], f[i]);
		}
	}


	void expandScalar(Field<tensor>& res, const UList<scalar>& f)
	{
		forAll(res, i)
		{
			expandScalar(res[i], f[i]);
		}
	}


	void expandLinear(Field<tensor>& res, const UList<vector>& f)
	{
		forAll(res, i)
		{
			expandLinear(res[i], f[i]);
		}
	}


	void sumToDiag(Field<vector>& res, const UList<tensor>& f)
	{
		forAll(res, i)
		{
			sumToDiag(res[i], f[i]);
		}
	}


	void sumMagToDiag(Field<vector>& res, const UList<tensor>& f)
	{
		forAll(res, i)
		{
			sumMagToDiag(res[i], f[i]);
		}
	}


} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <undefFieldFunctionsM.hxx>