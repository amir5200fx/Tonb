#include <sphericalTensorFieldField.hxx>

#define TEMPLATE template<template<class> class Field>
#include <FieldFieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * global functions  * * * * * * * * * * * * * //

	TEMPLATE
	void tr(FieldField<Field, scalar>& res, const FieldField<Field, sphericalTensor>& f)
	{
		forAll(res, i) { tr(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> tr(const FieldField<Field, sphericalTensor>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		tr(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> tr(const tmp<FieldField<Field, sphericalTensor>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, sphericalTensor, sphericalTensor>::New(tf));
		tr(tRes(), tf());
		reuseTmpFieldField<Field, sphericalTensor, sphericalTensor>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void sph(FieldField<Field, sphericalTensor>& res, const FieldField<Field, sphericalTensor>& f)
	{
		forAll(res, i) { sph(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, sphericalTensor>> sph(const FieldField<Field, sphericalTensor>& f)
	{
		tmp<FieldField<Field, sphericalTensor>> tRes(FieldField<Field, sphericalTensor>::NewCalculatedType(f));
		sph(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, sphericalTensor>> sph(const tmp<FieldField<Field, sphericalTensor>>& tf)
	{
		tmp<FieldField<Field, sphericalTensor>> tRes(reuseTmpFieldField<Field, sphericalTensor, sphericalTensor>::New(tf));
		sph(tRes(), tf());
		reuseTmpFieldField<Field, sphericalTensor, sphericalTensor>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void det(FieldField<Field, scalar>& res, const FieldField<Field, sphericalTensor>& f)
	{
		forAll(res, i) { det(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> det(const FieldField<Field, sphericalTensor>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		det(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> det(const tmp<FieldField<Field, sphericalTensor>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, sphericalTensor, sphericalTensor>::New(tf));
		det(tRes(), tf());
		reuseTmpFieldField<Field, sphericalTensor, sphericalTensor>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void inv(FieldField<Field, sphericalTensor>& res, const FieldField<Field, sphericalTensor>& f)
	{
		forAll(res, i) { inv(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, sphericalTensor>> inv(const FieldField<Field, sphericalTensor>& f)
	{
		tmp<FieldField<Field, sphericalTensor>> tRes(FieldField<Field, sphericalTensor>::NewCalculatedType(f));
		inv(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, sphericalTensor>> inv(const tmp<FieldField<Field, sphericalTensor>>& tf)
	{
		tmp<FieldField<Field, sphericalTensor>> tRes(reuseTmpFieldField<Field, sphericalTensor, sphericalTensor>::New(tf));
		inv(tRes(), tf());
		reuseTmpFieldField<Field, sphericalTensor, sphericalTensor>::clear(tf);
		return tRes;
	}


		// * * * * * * * * * * * * * * * global operators  * * * * * * * * * * * * * //

		
	TEMPLATE
	void divide(FieldField<Field, sphericalTensor>& f, const FieldField<Field, scalar>& f1
	            , const FieldField<Field, sphericalTensor>& f2)
	{
		forAll(f, i) { divide(f[i], f1[i], f2[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, sphericalTensor>> operator /(const FieldField<Field, scalar>& f1
	                                                   , const FieldField<Field, sphericalTensor>& f2)
	{
		tmp<FieldField<Field, sphericalTensor>> tRes(FieldField<Field, sphericalTensor>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, sphericalTensor>> operator /(const FieldField<Field, scalar>& f1
	                                                   , const tmp<FieldField<Field, sphericalTensor>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor>> tRes(reuseTmpFieldField<Field, sphericalTensor, sphericalTensor>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, sphericalTensor, sphericalTensor>::clear(tf2);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, sphericalTensor>> operator /(const tmp<FieldField<Field, scalar>>& tf1
	                                                   , const FieldField<Field, sphericalTensor>& f2)
	{
		tmp<FieldField<Field, sphericalTensor>> tRes(reuseTmpFieldField<Field, sphericalTensor, scalar>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, sphericalTensor, scalar>::clear(tf1);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, sphericalTensor>> operator /(const tmp<FieldField<Field, scalar>>& tf1
	                                                   , const tmp<FieldField<Field, sphericalTensor>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor>> tRes(
			reuseTmpTmpFieldField<Field, sphericalTensor, scalar, scalar, sphericalTensor>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, sphericalTensor, scalar, scalar, sphericalTensor>::clear(tf1, tf2);
		return tRes;
	}
		
	TEMPLATE
	void divide(FieldField<Field, sphericalTensor>& f, const scalar& s, const FieldField<Field, sphericalTensor>& f2)
	{
		forAll(f, i) { divide(f[i], s, f2[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, sphericalTensor>> operator /(const scalar& s, const FieldField<Field, sphericalTensor>& f2)
	{
		tmp<FieldField<Field, sphericalTensor>> tRes(FieldField<Field, sphericalTensor>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, sphericalTensor>> operator /(const scalar& s, const tmp<FieldField<Field, sphericalTensor>>& tf2)
	{
		tmp<FieldField<Field, sphericalTensor>> tRes(reuseTmpFieldField<Field, sphericalTensor, sphericalTensor>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, sphericalTensor, sphericalTensor>::clear(tf2);
		return tRes;
	}

	TEMPLATE
	void divide(FieldField<Field, sphericalTensor>& f, const FieldField<Field, scalar>& f1, const sphericalTensor& s)
	{
		forAll(f, i) { divide(f[i], f1[i], s); }
	}

	TEMPLATE
	tmp<FieldField<Field, sphericalTensor>> operator /(const FieldField<Field, scalar>& f1, const sphericalTensor& s)
	{
		tmp<FieldField<Field, sphericalTensor>> tRes(FieldField<Field, scalar>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, sphericalTensor>> operator /(const tmp<FieldField<Field, scalar>>& tf1, const sphericalTensor& s)
	{
		tmp<FieldField<Field, sphericalTensor>> tRes(reuseTmpFieldField<Field, sphericalTensor, scalar>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, sphericalTensor, scalar>::clear(tf1);
		return tRes;
	}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <undefFieldFunctionsM.hxx>