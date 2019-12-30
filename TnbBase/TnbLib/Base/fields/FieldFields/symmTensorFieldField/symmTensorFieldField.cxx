#include <symmTensorFieldField.hxx>

#define TEMPLATE template<template<class> class Field>
#include <FieldFieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * global operators  * * * * * * * * * * * * * //

	TEMPLATE
	void sqr(FieldField<Field, symmTensor>& res, const FieldField<Field, vector>& f)
	{
		forAll(res, i)
		{
			sqr(res[i], f[i]);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, symmTensor>> sqr(const FieldField<Field, vector>& f)
	{
		tmp<FieldField<Field, symmTensor>> tRes(FieldField<Field, symmTensor>::NewCalculatedType(f));
		sqr(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, symmTensor>> sqr(const tmp<FieldField<Field, vector>>& tf)
	{
		tmp<FieldField<Field, symmTensor>> tRes(reuseTmpFieldField<Field, vector, vector>::New(tf));
		sqr(tRes(), tf());
		reuseTmpFieldField<Field, vector, vector>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void innerSqr(FieldField<Field, symmTensor>& res, const FieldField<Field, symmTensor>& f)
	{
		forAll(res, i)
		{
			innerSqr(res[i], f[i]);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, symmTensor>> innerSqr(const FieldField<Field, symmTensor>& f)
	{
		tmp<FieldField<Field, symmTensor>> tRes(FieldField<Field, symmTensor>::NewCalculatedType(f));
		innerSqr(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, symmTensor>> innerSqr(const tmp<FieldField<Field, symmTensor>>& tf)
	{
		tmp<FieldField<Field, symmTensor>> tRes(reuseTmpFieldField<Field, symmTensor, symmTensor>::New(tf));
		innerSqr(tRes(), tf());
		reuseTmpFieldField<Field, symmTensor, symmTensor>::clear(tf);
		return tRes;
	}

		
	TEMPLATE
	void tr(FieldField<Field, scalar>& res, const FieldField<Field, symmTensor>& f)
	{
		forAll(res, i)
		{
			tr(res[i], f[i]);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> tr(const FieldField<Field, symmTensor>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		tr(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> tr(const tmp<FieldField<Field, symmTensor>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, symmTensor, symmTensor>::New(tf));
		tr(tRes(), tf());
		reuseTmpFieldField<Field, symmTensor, symmTensor>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void sph(FieldField<Field, sphericalTensor>& res, const FieldField<Field, symmTensor>& f)
	{
		forAll(res, i)
		{
			sph(res[i], f[i]);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, sphericalTensor>> sph(const FieldField<Field, symmTensor>& f)
	{
		tmp<FieldField<Field, sphericalTensor>> tRes(FieldField<Field, sphericalTensor>::NewCalculatedType(f));
		sph(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, sphericalTensor>> sph(const tmp<FieldField<Field, symmTensor>>& tf)
	{
		tmp<FieldField<Field, sphericalTensor>> tRes(reuseTmpFieldField<Field, symmTensor, symmTensor>::New(tf));
		sph(tRes(), tf());
		reuseTmpFieldField<Field, symmTensor, symmTensor>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void symm(FieldField<Field, symmTensor>& res, const FieldField<Field, symmTensor>& f)
	{
		forAll(res, i)
		{
			symm(res[i], f[i]);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, symmTensor>> symm(const FieldField<Field, symmTensor>& f)
	{
		tmp<FieldField<Field, symmTensor>> tRes(FieldField<Field, symmTensor>::NewCalculatedType(f));
		symm(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, symmTensor>> symm(const tmp<FieldField<Field, symmTensor>>& tf)
	{
		tmp<FieldField<Field, symmTensor>> tRes(reuseTmpFieldField<Field, symmTensor, symmTensor>::New(tf));
		symm(tRes(), tf());
		reuseTmpFieldField<Field, symmTensor, symmTensor>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void twoSymm(FieldField<Field, symmTensor>& res, const FieldField<Field, symmTensor>& f)
	{
		forAll(res, i)
		{
			twoSymm(res[i], f[i]);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, symmTensor>> twoSymm(const FieldField<Field, symmTensor>& f)
	{
		tmp<FieldField<Field, symmTensor>> tRes(FieldField<Field, symmTensor>::NewCalculatedType(f));
		twoSymm(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, symmTensor>> twoSymm(const tmp<FieldField<Field, symmTensor>>& tf)
	{
		tmp<FieldField<Field, symmTensor>> tRes(reuseTmpFieldField<Field, symmTensor, symmTensor>::New(tf));
		twoSymm(tRes(), tf());
		reuseTmpFieldField<Field, symmTensor, symmTensor>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void dev(FieldField<Field, symmTensor>& res, const FieldField<Field, symmTensor>& f)
	{
		forAll(res, i)
		{
			dev(res[i], f[i]);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, symmTensor>> dev(const FieldField<Field, symmTensor>& f)
	{
		tmp<FieldField<Field, symmTensor>> tRes(FieldField<Field, symmTensor>::NewCalculatedType(f));
		dev(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, symmTensor>> dev(const tmp<FieldField<Field, symmTensor>>& tf)
	{
		tmp<FieldField<Field, symmTensor>> tRes(reuseTmpFieldField<Field, symmTensor, symmTensor>::New(tf));
		dev(tRes(), tf());
		reuseTmpFieldField<Field, symmTensor, symmTensor>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void dev2(FieldField<Field, symmTensor>& res, const FieldField<Field, symmTensor>& f)
	{
		forAll(res, i)
		{
			dev2(res[i], f[i]);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, symmTensor>> dev2(const FieldField<Field, symmTensor>& f)
	{
		tmp<FieldField<Field, symmTensor>> tRes(FieldField<Field, symmTensor>::NewCalculatedType(f));
		dev2(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, symmTensor>> dev2(const tmp<FieldField<Field, symmTensor>>& tf)
	{
		tmp<FieldField<Field, symmTensor>> tRes(reuseTmpFieldField<Field, symmTensor, symmTensor>::New(tf));
		dev2(tRes(), tf());
		reuseTmpFieldField<Field, symmTensor, symmTensor>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void det(FieldField<Field, scalar>& res, const FieldField<Field, symmTensor>& f)
	{
		forAll(res, i)
		{
			det(res[i], f[i]);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> det(const FieldField<Field, symmTensor>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		det(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> det(const tmp<FieldField<Field, symmTensor>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, symmTensor, symmTensor>::New(tf));
		det(tRes(), tf());
		reuseTmpFieldField<Field, symmTensor, symmTensor>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void cof(FieldField<Field, symmTensor>& res, const FieldField<Field, symmTensor>& f)
	{
		forAll(res, i)
		{
			cof(res[i], f[i]);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, symmTensor>> cof(const FieldField<Field, symmTensor>& f)
	{
		tmp<FieldField<Field, symmTensor>> tRes(FieldField<Field, symmTensor>::NewCalculatedType(f));
		cof(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, symmTensor>> cof(const tmp<FieldField<Field, symmTensor>>& tf)
	{
		tmp<FieldField<Field, symmTensor>> tRes(reuseTmpFieldField<Field, symmTensor, symmTensor>::New(tf));
		cof(tRes(), tf());
		reuseTmpFieldField<Field, symmTensor, symmTensor>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void inv(FieldField<Field, symmTensor>& res, const FieldField<Field, symmTensor>& f)
	{
		forAll(res, i)
		{
			inv(res[i], f[i]);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, symmTensor>> inv(const FieldField<Field, symmTensor>& f)
	{
		tmp<FieldField<Field, symmTensor>> tRes(FieldField<Field, symmTensor>::NewCalculatedType(f));
		inv(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, symmTensor>> inv(const tmp<FieldField<Field, symmTensor>>& tf)
	{
		tmp<FieldField<Field, symmTensor>> tRes(reuseTmpFieldField<Field, symmTensor, symmTensor>::New(tf));
		inv(tRes(), tf());
		reuseTmpFieldField<Field, symmTensor, symmTensor>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void hinv(FieldField<Field, symmTensor>& res, const FieldField<Field, symmTensor>& f)
	{
		forAll(res, i)
		{
			hinv(res[i], f[i]);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, symmTensor>> hinv(const FieldField<Field, symmTensor>& f)
	{
		tmp<FieldField<Field, symmTensor>> tRes(FieldField<Field, symmTensor>::NewCalculatedType(f));
		hinv(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, symmTensor>> hinv(const tmp<FieldField<Field, symmTensor>>& tf)
	{
		tmp<FieldField<Field, symmTensor>> tRes(reuseTmpFieldField<Field, symmTensor, symmTensor>::New(tf));
		hinv(tRes(), tf());
		reuseTmpFieldField<Field, symmTensor, symmTensor>::clear(tf);
		return tRes;
	}


		// * * * * * * * * * * * * * * * global operators  * * * * * * * * * * * * * //

		
	TEMPLATE
	void hdual(FieldField<Field, vector>& res, const FieldField<Field, symmTensor>& f)
	{
		forAll(res, i)
		{
			hdual(res[i], f[i]);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, vector>> operator *(const FieldField<Field, symmTensor>& f)
	{
		tmp<FieldField<Field, vector>> tRes(FieldField<Field, symmTensor>::NewCalculatedType(f));
		hdual(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, vector>> operator *(const tmp<FieldField<Field, symmTensor>>& tf)
	{
		tmp<FieldField<Field, vector>> tRes(reuseTmpFieldField<Field, symmTensor, symmTensor>::New(tf));
		hdual(tRes(), tf());
		reuseTmpFieldField<Field, symmTensor, symmTensor>::clear(tf);
		return tRes;
	}

		
	TEMPLATE
	void dot(FieldField<Field, tensor>& f, const FieldField<Field, symmTensor>& f1
	         , const FieldField<Field, symmTensor>& f2)
	{
		forAll(f, i)
		{
			dot(f[i], f1[i], f2[i]);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, tensor>> operator &(const FieldField<Field, symmTensor>& f1
	                                          , const FieldField<Field, symmTensor>& f2)
	{
		tmp<FieldField<Field, tensor>> tRes(FieldField<Field, tensor>::NewCalculatedType(f1));
		dot(tRes(), f1, f2);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, tensor>> operator &(const FieldField<Field, symmTensor>& f1
	                                          , const tmp<FieldField<Field, symmTensor>>& tf2)
	{
		tmp<FieldField<Field, tensor>> tRes(reuseTmpFieldField<Field, tensor, symmTensor>::New(tf2));
		dot(tRes(), f1, tf2());
		reuseTmpFieldField<Field, tensor, symmTensor>::clear(tf2);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, tensor>> operator &(const tmp<FieldField<Field, symmTensor>>& tf1
	                                          , const FieldField<Field, symmTensor>& f2)
	{
		tmp<FieldField<Field, tensor>> tRes(reuseTmpFieldField<Field, tensor, symmTensor>::New(tf1));
		dot(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, tensor, symmTensor>::clear(tf1);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, tensor>> operator &(const tmp<FieldField<Field, symmTensor>>& tf1
	                                          , const tmp<FieldField<Field, symmTensor>>& tf2)
	{
		tmp<FieldField<Field, tensor>> tRes(
			reuseTmpTmpFieldField<Field, tensor, symmTensor, symmTensor, symmTensor>::New(tf1, tf2));
		dot(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, tensor, symmTensor, symmTensor, symmTensor>::clear(tf1, tf2);
		return tRes;
	}
		
	TEMPLATE
	void dot(FieldField<Field, tensor>& f, const symmTensor& s, const FieldField<Field, symmTensor>& f2)
	{
		forAll(f, i)
		{
			dot(f[i], s, f2[i]);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, tensor>> operator &(const symmTensor& s, const FieldField<Field, symmTensor>& f2)
	{
		tmp<FieldField<Field, tensor>> tRes(FieldField<Field, symmTensor>::NewCalculatedType(f2));
		dot(tRes(), s, f2);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, tensor>> operator &(const symmTensor& s, const tmp<FieldField<Field, symmTensor>>& tf2)
	{
		tmp<FieldField<Field, tensor>> tRes(reuseTmpFieldField<Field, tensor, symmTensor>::New(tf2));
		dot(tRes(), s, tf2());
		reuseTmpFieldField<Field, tensor, symmTensor>::clear(tf2);
		return tRes;
	}

	TEMPLATE
	void dot(FieldField<Field, tensor>& f, const FieldField<Field, symmTensor>& f1, const symmTensor& s)
	{
		forAll(f, i)
		{
			dot(f[i], f1[i], s);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, tensor>> operator &(const FieldField<Field, symmTensor>& f1, const symmTensor& s)
	{
		tmp<FieldField<Field, tensor>> tRes(FieldField<Field, symmTensor>::NewCalculatedType(f1));
		dot(tRes(), f1, s);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, tensor>> operator &(const tmp<FieldField<Field, symmTensor>>& tf1, const symmTensor& s)
	{
		tmp<FieldField<Field, tensor>> tRes(reuseTmpFieldField<Field, tensor, symmTensor>::New(tf1));
		dot(tRes(), tf1(), s);
		reuseTmpFieldField<Field, tensor, symmTensor>::clear(tf1);
		return tRes;
	}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <undefFieldFunctionsM.hxx>