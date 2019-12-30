#include <tensorFieldField.hxx>

#define TEMPLATE template<template<class> class Field>
#include <FieldFieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * global operators  * * * * * * * * * * * * * //

	TEMPLATE
	void tr(FieldField<Field, scalar>& res, const FieldField<Field, tensor>& f)
	{
		forAll(res, i) { tr(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> tr(const FieldField<Field, tensor>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		tr(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> tr(const tmp<FieldField<Field, tensor>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, tensor, tensor>::New(tf));
		tr(tRes(), tf());
		reuseTmpFieldField<Field, tensor, tensor>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void sph(FieldField<Field, sphericalTensor>& res, const FieldField<Field, tensor>& f)
	{
		forAll(res, i)
		{
			sph(res[i], f[i]);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, sphericalTensor>> sph(const FieldField<Field, tensor>& f)
	{
		tmp<FieldField<Field, sphericalTensor>> tRes(FieldField<Field, sphericalTensor>::NewCalculatedType(f));
		sph(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, sphericalTensor>> sph(const tmp<FieldField<Field, tensor>>& tf)
	{
		tmp<FieldField<Field, sphericalTensor>> tRes(reuseTmpFieldField<Field, tensor, tensor>::New(tf));
		sph(tRes(), tf());
		reuseTmpFieldField<Field, tensor, tensor>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void symm(FieldField<Field, symmTensor>& res, const FieldField<Field, tensor>& f)
	{
		forAll(res, i)
		{
			symm(res[i], f[i]);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, symmTensor>> symm(const FieldField<Field, tensor>& f)
	{
		tmp<FieldField<Field, symmTensor>> tRes(FieldField<Field, symmTensor>::NewCalculatedType(f));
		symm(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, symmTensor>> symm(const tmp<FieldField<Field, tensor>>& tf)
	{
		tmp<FieldField<Field, symmTensor>> tRes(reuseTmpFieldField<Field, tensor, tensor>::New(tf));
		symm(tRes(), tf());
		reuseTmpFieldField<Field, tensor, tensor>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void twoSymm(FieldField<Field, symmTensor>& res, const FieldField<Field, tensor>& f)
	{
		forAll(res, i)
		{
			twoSymm(res[i], f[i]);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, symmTensor>> twoSymm(const FieldField<Field, tensor>& f)
	{
		tmp<FieldField<Field, symmTensor>> tRes(FieldField<Field, symmTensor>::NewCalculatedType(f));
		twoSymm(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, symmTensor>> twoSymm(const tmp<FieldField<Field, tensor>>& tf)
	{
		tmp<FieldField<Field, symmTensor>> tRes(reuseTmpFieldField<Field, tensor, tensor>::New(tf));
		twoSymm(tRes(), tf());
		reuseTmpFieldField<Field, tensor, tensor>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void skew(FieldField<Field, tensor>& res, const FieldField<Field, tensor>& f)
	{
		forAll(res, i)
		{
			skew(res[i], f[i]);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, tensor>> skew(const FieldField<Field, tensor>& f)
	{
		tmp<FieldField<Field, tensor>> tRes(FieldField<Field, tensor>::NewCalculatedType(f));
		skew(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, tensor>> skew(const tmp<FieldField<Field, tensor>>& tf)
	{
		tmp<FieldField<Field, tensor>> tRes(reuseTmpFieldField<Field, tensor, tensor>::New(tf));
		skew(tRes(), tf());
		reuseTmpFieldField<Field, tensor, tensor>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void dev(FieldField<Field, tensor>& res, const FieldField<Field, tensor>& f)
	{
		forAll(res, i)
		{
			dev(res[i], f[i]);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, tensor>> dev(const FieldField<Field, tensor>& f)
	{
		tmp<FieldField<Field, tensor>> tRes(FieldField<Field, tensor>::NewCalculatedType(f));
		dev(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, tensor>> dev(const tmp<FieldField<Field, tensor>>& tf)
	{
		tmp<FieldField<Field, tensor>> tRes(reuseTmpFieldField<Field, tensor, tensor>::New(tf));
		dev(tRes(), tf());
		reuseTmpFieldField<Field, tensor, tensor>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void dev2(FieldField<Field, tensor>& res, const FieldField<Field, tensor>& f)
	{
		forAll(res, i)
		{
			dev2(res[i], f[i]);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, tensor>> dev2(const FieldField<Field, tensor>& f)
	{
		tmp<FieldField<Field, tensor>> tRes(FieldField<Field, tensor>::NewCalculatedType(f));
		dev2(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, tensor>> dev2(const tmp<FieldField<Field, tensor>>& tf)
	{
		tmp<FieldField<Field, tensor>> tRes(reuseTmpFieldField<Field, tensor, tensor>::New(tf));
		dev2(tRes(), tf());
		reuseTmpFieldField<Field, tensor, tensor>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void det(FieldField<Field, scalar>& res, const FieldField<Field, tensor>& f)
	{
		forAll(res, i)
		{
			det(res[i], f[i]);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> det(const FieldField<Field, tensor>& f)
	{
		tmp<FieldField<Field, scalar>> tRes(FieldField<Field, scalar>::NewCalculatedType(f));
		det(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, scalar>> det(const tmp<FieldField<Field, tensor>>& tf)
	{
		tmp<FieldField<Field, scalar>> tRes(reuseTmpFieldField<Field, tensor, tensor>::New(tf));
		det(tRes(), tf());
		reuseTmpFieldField<Field, tensor, tensor>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void cof(FieldField<Field, tensor>& res, const FieldField<Field, tensor>& f)
	{
		forAll(res, i)
		{
			cof(res[i], f[i]);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, tensor>> cof(const FieldField<Field, tensor>& f)
	{
		tmp<FieldField<Field, tensor>> tRes(FieldField<Field, tensor>::NewCalculatedType(f));
		cof(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, tensor>> cof(const tmp<FieldField<Field, tensor>>& tf)
	{
		tmp<FieldField<Field, tensor>> tRes(reuseTmpFieldField<Field, tensor, tensor>::New(tf));
		cof(tRes(), tf());
		reuseTmpFieldField<Field, tensor, tensor>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void inv(FieldField<Field, tensor>& res, const FieldField<Field, tensor>& f)
	{
		forAll(res, i)
		{
			inv(res[i], f[i]);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, tensor>> inv(const FieldField<Field, tensor>& f)
	{
		tmp<FieldField<Field, tensor>> tRes(FieldField<Field, tensor>::NewCalculatedType(f));
		inv(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, tensor>> inv(const tmp<FieldField<Field, tensor>>& tf)
	{
		tmp<FieldField<Field, tensor>> tRes(reuseTmpFieldField<Field, tensor, tensor>::New(tf));
		inv(tRes(), tf());
		reuseTmpFieldField<Field, tensor, tensor>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void hinv(FieldField<Field, tensor>& res, const FieldField<Field, tensor>& f)
	{
		forAll(res, i)
		{
			hinv(res[i], f[i]);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, tensor>> hinv(const FieldField<Field, tensor>& f)
	{
		tmp<FieldField<Field, tensor>> tRes(FieldField<Field, tensor>::NewCalculatedType(f));
		hinv(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, tensor>> hinv(const tmp<FieldField<Field, tensor>>& tf)
	{
		tmp<FieldField<Field, tensor>> tRes(reuseTmpFieldField<Field, tensor, tensor>::New(tf));
		hinv(tRes(), tf());
		reuseTmpFieldField<Field, tensor, tensor>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void eigenValues(FieldField<Field, vector>& res, const FieldField<Field, tensor>& f)
	{
		forAll(res, i)
		{
			eigenValues(res[i], f[i]);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, vector>> eigenValues(const FieldField<Field, tensor>& f)
	{
		tmp<FieldField<Field, vector>> tRes(FieldField<Field, vector>::NewCalculatedType(f));
		eigenValues(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, vector>> eigenValues(const tmp<FieldField<Field, tensor>>& tf)
	{
		tmp<FieldField<Field, vector>> tRes(reuseTmpFieldField<Field, tensor, tensor>::New(tf));
		eigenValues(tRes(), tf());
		reuseTmpFieldField<Field, tensor, tensor>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void eigenVectors(FieldField<Field, tensor>& res, const FieldField<Field, tensor>& f)
	{
		forAll(res, i)
		{
			eigenVectors(res[i], f[i]);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, tensor>> eigenVectors(const FieldField<Field, tensor>& f)
	{
		tmp<FieldField<Field, tensor>> tRes(FieldField<Field, tensor>::NewCalculatedType(f));
		eigenVectors(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, tensor>> eigenVectors(const tmp<FieldField<Field, tensor>>& tf)
	{
		tmp<FieldField<Field, tensor>> tRes(reuseTmpFieldField<Field, tensor, tensor>::New(tf));
		eigenVectors(tRes(), tf());
		reuseTmpFieldField<Field, tensor, tensor>::clear(tf);
		return tRes;
	}

		
	TEMPLATE
	void eigenValues(FieldField<Field, vector>& res, const FieldField<Field, symmTensor>& f)
	{
		forAll(res, i)
		{
			eigenValues(res[i], f[i]);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, vector>> eigenValues(const FieldField<Field, symmTensor>& f)
	{
		tmp<FieldField<Field, vector>> tRes(FieldField<Field, vector>::NewCalculatedType(f));
		eigenValues(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, vector>> eigenValues(const tmp<FieldField<Field, symmTensor>>& tf)
	{
		tmp<FieldField<Field, vector>> tRes(reuseTmpFieldField<Field, symmTensor, symmTensor>::New(tf));
		eigenValues(tRes(), tf());
		reuseTmpFieldField<Field, symmTensor, symmTensor>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void eigenVectors(FieldField<Field, symmTensor>& res, const FieldField<Field, symmTensor>& f)
	{
		forAll(res, i)
		{
			eigenVectors(res[i], f[i]);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, symmTensor>> eigenVectors(const FieldField<Field, symmTensor>& f)
	{
		tmp<FieldField<Field, symmTensor>> tRes(FieldField<Field, symmTensor>::NewCalculatedType(f));
		eigenVectors(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, symmTensor>> eigenVectors(const tmp<FieldField<Field, symmTensor>>& tf)
	{
		tmp<FieldField<Field, symmTensor>> tRes(reuseTmpFieldField<Field, symmTensor, symmTensor>::New(tf));
		eigenVectors(tRes(), tf());
		reuseTmpFieldField<Field, symmTensor, symmTensor>::clear(tf);
		return tRes;
	}


		// * * * * * * * * * * * * * * * global operators  * * * * * * * * * * * * * //

		
	TEMPLATE
	void hdual(FieldField<Field, vector>& res, const FieldField<Field, tensor>& f)
	{
		forAll(res, i)
		{
			hdual(res[i], f[i]);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, vector>> operator *(const FieldField<Field, tensor>& f)
	{
		tmp<FieldField<Field, vector>> tRes(FieldField<Field, tensor>::NewCalculatedType(f));
		hdual(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, vector>> operator *(const tmp<FieldField<Field, tensor>>& tf)
	{
		tmp<FieldField<Field, vector>> tRes(reuseTmpFieldField<Field, tensor, tensor>::New(tf));
		hdual(tRes(), tf());
		reuseTmpFieldField<Field, tensor, tensor>::clear(tf);
		return tRes;
	}
		
	TEMPLATE
	void hdual(FieldField<Field, tensor>& res, const FieldField<Field, vector>& f)
	{
		forAll(res, i)
		{
			hdual(res[i], f[i]);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, tensor>> operator *(const FieldField<Field, vector>& f)
	{
		tmp<FieldField<Field, tensor>> tRes(FieldField<Field, vector>::NewCalculatedType(f));
		hdual(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, tensor>> operator *(const tmp<FieldField<Field, vector>>& tf)
	{
		tmp<FieldField<Field, tensor>> tRes(reuseTmpFieldField<Field, vector, vector>::New(tf));
		hdual(tRes(), tf());
		reuseTmpFieldField<Field, vector, vector>::clear(tf);
		return tRes;
	}

		
	TEMPLATE
	void divide(FieldField<Field, vector>& f, const FieldField<Field, vector>& f1, const FieldField<Field, tensor>& f2)
	{
		forAll(f, i)
		{
			divide(f[i], f1[i], f2[i]);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, vector>> operator /(const FieldField<Field, vector>& f1, const FieldField<Field, tensor>& f2)
	{
		tmp<FieldField<Field, vector>> tRes(FieldField<Field, vector>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, vector>> operator /(const FieldField<Field, vector>& f1
	                                          , const tmp<FieldField<Field, tensor>>& tf2)
	{
		tmp<FieldField<Field, vector>> tRes(reuseTmpFieldField<Field, vector, tensor>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, vector, tensor>::clear(tf2);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, vector>> operator /(const tmp<FieldField<Field, vector>>& tf1
	                                          , const FieldField<Field, tensor>& f2)
	{
		tmp<FieldField<Field, vector>> tRes(reuseTmpFieldField<Field, vector, vector>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, vector, vector>::clear(tf1);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, vector>> operator /(const tmp<FieldField<Field, vector>>& tf1
	                                          , const tmp<FieldField<Field, tensor>>& tf2)
	{
		tmp<FieldField<Field, vector>> tRes(reuseTmpTmpFieldField<Field, vector, vector, vector, tensor>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, vector, vector, vector, tensor>::clear(tf1, tf2);
		return tRes;
	}
		
	TEMPLATE
	void divide(FieldField<Field, vector>& f, const vector& s, const FieldField<Field, tensor>& f2)
	{
		forAll(f, i)
		{
			divide(f[i], s, f2[i]);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, vector>> operator /(const vector& s, const FieldField<Field, tensor>& f2)
	{
		tmp<FieldField<Field, vector>> tRes(FieldField<Field, tensor>::NewCalculatedType(f2));
		divide(tRes(), s, f2);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, vector>> operator /(const vector& s, const tmp<FieldField<Field, tensor>>& tf2)
	{
		tmp<FieldField<Field, vector>> tRes(reuseTmpFieldField<Field, vector, tensor>::New(tf2));
		divide(tRes(), s, tf2());
		reuseTmpFieldField<Field, vector, tensor>::clear(tf2);
		return tRes;
	}
	
	TEMPLATE
	void divide(FieldField<Field, vector>& f, const FieldField<Field, vector>& f1, const tensor& s)
	{
		forAll(f, i)
		{
			divide(f[i], f1[i], s);
		}
	}

	TEMPLATE
	tmp<FieldField<Field, vector>> operator /(const FieldField<Field, vector>& f1, const tensor& s)
	{
		tmp<FieldField<Field, vector>> tRes(FieldField<Field, vector>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, vector>> operator /(const tmp<FieldField<Field, vector>>& tf1, const tensor& s)
	{
		tmp<FieldField<Field, vector>> tRes(reuseTmpFieldField<Field, vector, vector>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, vector, vector>::clear(tf1);
		return tRes;
	}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <undefFieldFunctionsM.hxx>