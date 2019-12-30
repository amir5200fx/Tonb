//#include <FieldField.hxx>

#include <Field.hxx>
#include <PstreamReduceOps.hxx>
#include <FieldFieldReuseFunctions.hxx>

#define TEMPLATE template<template<class> class Field, class Type>
#include <FieldFieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/* * * * * * * * * * * * * * * * Global functions  * * * * * * * * * * * * * */

	template<template<class> class Field, class Type>
	void component
	(
		FieldField<Field, typename FieldField<Field, Type>::cmptType>& sf,
		const FieldField<Field, Type>& f,
		const direction d
	)
	{
		forAll(sf, i)
		{
			component(sf[i], f[i], d);
		}
	}


	template<template<class> class Field, class Type>
	void T(FieldField<Field, Type>& f1, const FieldField<Field, Type>& f2)
	{
		forAll(f1, i)
		{
			T(f1[i], f2[i]);
		}
	}


	template<template<class> class Field, class Type, int r>
	void pow
	(
		FieldField<Field, typename powProduct<Type, r>::type>& f,
		const FieldField<Field, Type>& vf
	)
	{
		forAll(f, i)
		{
			pow(f[i], vf[i]);
		}
	}

	template<template<class> class Field, class Type, int r>
	tmp<FieldField<Field, typename powProduct<Type, r>::type> >
		pow
		(
			const FieldField<Field, Type>& f, typename powProduct<Type, r>::type
		)
	{
		typedef typename powProduct<Type, r>::type powProductType;
		tmp<FieldField<Field, powProductType> > tRes
		(
			FieldField<Field, powProductType>::NewCalculatedType(f)
		);
		pow<Type, r>(tRes(), f);
		return tRes;
	}

	template<template<class> class Field, class Type, int r>
	tmp<FieldField<Field, typename powProduct<Type, r>::type> >
		pow
		(
			const tmp<FieldField<Field, Type> >& tf, typename powProduct<Type, r>::type
		)
	{
		typedef typename powProduct<Type, r>::type powProductType;
		tmp<FieldField<Field, powProductType> > tRes
		(
			reuseTmpFieldField<Field, powProductType, Type>::New(tf)
		);
		pow<Type, r>(tRes(), tf());
		reuseTmpFieldField<Field, powProductType, Type>::clear(tf);
		return tRes;
	}


	template<template<class> class Field, class Type>
	void sqr
	(
		FieldField<Field, typename outerProduct<Type, Type>::type>& f,
		const FieldField<Field, Type>& vf
	)
	{
		forAll(f, i)
		{
			sqr(f[i], vf[i]);
		}
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, typename outerProduct<Type, Type>::type> >
		sqr(const FieldField<Field, Type>& f)
	{
		typedef typename outerProduct<Type, Type>::type outerProductType;
		tmp<FieldField<Field, outerProductType> > tRes
		(
			FieldField<Field, outerProductType>::NewCalculatedType(f)
		);
		sqr(tRes(), f);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, typename outerProduct<Type, Type>::type> >
		sqr(const tmp<FieldField<Field, Type> >& tf)
	{
		typedef typename outerProduct<Type, Type>::type outerProductType;
		tmp<FieldField<Field, outerProductType> > tRes
		(
			reuseTmpFieldField<Field, outerProductType, Type>::New(tf)
		);
		sqr(tRes(), tf());
		reuseTmpFieldField<Field, outerProductType, Type>::clear(tf);
		return tRes;
	}


	template<template<class> class Field, class Type>
	void magSqr(FieldField<Field, scalar>& sf, const FieldField<Field, Type>& f)
	{
		forAll(sf, i)
		{
			magSqr(sf[i], f[i]);
		}
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, scalar> > magSqr(const FieldField<Field, Type>& f)
	{
		tmp<FieldField<Field, scalar> > tRes
		(
			FieldField<Field, scalar>::NewCalculatedType(f)
		);

		magSqr(tRes(), f);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, scalar> > magSqr(const tmp<FieldField<Field, Type> >& tf)
	{
		tmp<FieldField<Field, scalar> > tRes
		(
			reuseTmpFieldField<Field, scalar, Type>::New(tf)
		);

		magSqr(tRes(), tf());
		reuseTmpFieldField<Field, scalar, Type>::clear(tf);
		return tRes;
	}


	template<template<class> class Field, class Type>
	void mag(FieldField<Field, scalar>& sf, const FieldField<Field, Type>& f)
	{
		forAll(sf, i)
		{
			mag(sf[i], f[i]);
		}
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, scalar> > mag(const FieldField<Field, Type>& f)
	{
		tmp<FieldField<Field, scalar> > tRes
		(
			FieldField<Field, scalar>::NewCalculatedType(f)
		);

		mag(tRes(), f);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, scalar> > mag(const tmp<FieldField<Field, Type> >& tf)
	{
		tmp<FieldField<Field, scalar> > tRes
		(
			reuseTmpFieldField<Field, scalar, Type>::New(tf)
		);

		mag(tRes(), tf());
		reuseTmpFieldField<Field, scalar, Type>::clear(tf);
		return tRes;
	}


	template<template<class> class Field, class Type>
	void cmptMax
	(
		FieldField<Field, typename FieldField<Field, Type>::cmptType>& cf,
		const FieldField<Field, Type>& f
	)
	{
		forAll(cf, i)
		{
			cmptMax(cf[i], f[i]);
		}
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, typename FieldField<Field, Type>::cmptType> > cmptMax
	(
		const FieldField<Field, Type>& f
	)
	{
		typedef typename FieldField<Field, Type>::cmptType cmptType;
		tmp<FieldField<Field, cmptType> > tRes
		(
			FieldField<Field, cmptType>::NewCalculatedType(f)
		);
		cmptMax(tRes(), f);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, typename FieldField<Field, Type>::cmptType> > cmptMax
	(
		const tmp<FieldField<Field, Type> >& tf
	)
	{
		typedef typename FieldField<Field, Type>::cmptType cmptType;
		tmp<FieldField<Field, cmptType> > tRes
		(
			reuseTmpFieldField<Field, cmptType, Type>::New(tf)
		);
		cmptMax(tRes(), tf());
		reuseTmpFieldField<Field, cmptType, Type>::clear(tf);
		return tRes;
	}


	template<template<class> class Field, class Type>
	void cmptMin
	(
		FieldField<Field, typename FieldField<Field, Type>::cmptType>& cf,
		const FieldField<Field, Type>& f
	)
	{
		forAll(cf, i)
		{
			cmptMin(cf[i], f[i]);
		}
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, typename FieldField<Field, Type>::cmptType> > cmptMin
	(
		const FieldField<Field, Type>& f
	)
	{
		typedef typename FieldField<Field, Type>::cmptType cmptType;
		tmp<FieldField<Field, cmptType> > tRes
		(
			FieldField<Field, cmptType>::NewCalculatedType(f)
		);
		cmptMin(tRes(), f);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, typename FieldField<Field, Type>::cmptType> > cmptMin
	(
		const tmp<FieldField<Field, Type> >& tf
	)
	{
		typedef typename FieldField<Field, Type>::cmptType cmptType;
		tmp<FieldField<Field, cmptType> > tRes
		(
			reuseTmpFieldField<Field, cmptType, Type>::New(tf)
		);
		cmptMin(tRes(), tf());
		reuseTmpFieldField<Field, cmptType, Type>::clear(tf);
		return tRes;
	}


	template<template<class> class Field, class Type>
	void cmptAv
	(
		FieldField<Field, typename FieldField<Field, Type>::cmptType>& cf,
		const FieldField<Field, Type>& f
	)
	{
		forAll(cf, i)
		{
			cmptAv(cf[i], f[i]);
		}
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, typename FieldField<Field, Type>::cmptType> > cmptAv
	(
		const FieldField<Field, Type>& f
	)
	{
		typedef typename FieldField<Field, Type>::cmptType cmptType;
		tmp<FieldField<Field, cmptType> > tRes
		(
			FieldField<Field, cmptType>::NewCalculatedType(f)
		);
		cmptAv(tRes(), f);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, typename FieldField<Field, Type>::cmptType> > cmptAv
	(
		const tmp<FieldField<Field, Type> >& tf
	)
	{
		typedef typename FieldField<Field, Type>::cmptType cmptType;
		tmp<FieldField<Field, cmptType> > tRes
		(
			reuseTmpFieldField<Field, cmptType, Type>::New(tf)
		);
		cmptAv(tRes(), tf());
		reuseTmpFieldField<Field, cmptType, Type>::clear(tf);
		return tRes;
	}


	template<template<class> class Field, class Type>
	void cmptMag
	(
		FieldField<Field, Type>& cf,
		const FieldField<Field, Type>& f
	)
	{
		forAll(cf, i)
		{
			cmptMag(cf[i], f[i]);
		}
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type> > cmptMag
	(
		const FieldField<Field, Type>& f
	)
	{
		tmp<FieldField<Field, Type> > tRes
		(
			FieldField<Field, Type>::NewCalculatedType(f)
		);
		cmptMag(tRes(), f);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type> > cmptMag
	(
		const tmp<FieldField<Field, Type> >& tf
	)
	{
		tmp<FieldField<Field, Type> > tRes
		(
			reuseTmpFieldField<Field, Type, Type>::New(tf)
		);
		cmptMag(tRes(), tf());
		reuseTmpFieldField<Field, Type, Type>::clear(tf);
		return tRes;
	}


#define TMP_UNARY_FUNCTION(returnType, func)                                  \
                                                                              \
template<template<class> class Field, class Type>                             \
returnType func(const tmp<FieldField<Field, Type> >& tf1)                     \
{                                                                             \
    returnType res = func(tf1());                                             \
    tf1.clear();                                                              \
    return res;                                                               \
}

	template<template<class> class Field, class Type>
	Type max(const FieldField<Field, Type>& f)
	{
		label i = 0;
		while (i < f.size() && !f[i].size()) i++;

		if (i < f.size())
		{
			Type Max(max(f[i]));

			for (label j = i + 1; j < f.size(); j++)
			{
				if (f[j].size())
				{
					Max = max(max(f[j]), Max);
				}
			}

			return Max;
		}
		else
		{
			WarningIn("max(const FieldField<Field, Type>&) const")
				<< "empty fieldField, returning zero" << endl;

			return pTraits<Type>::zero;
		}
	}

	template <template<class> class Field, class Type>
	Type max(const tmp<FieldField<Field, Type>>& tf1)
	{
		Type res = max(tf1());
		tf1.clear();
		return res;
	}

		template<template<class> class Field, class Type>
	Type min(const FieldField<Field, Type>& f)
	{
		label i = 0;
		while (i < f.size() && !f[i].size()) i++;

		if (i < f.size())
		{
			label i = 0;
			while (!f[i].size()) i++;

			Type Min(min(f[i]));

			for (label j = i + 1; j < f.size(); j++)
			{
				if (f[j].size())
				{
					Min = min(min(f[j]), Min);
				}
			}

			return Min;
		}
		else
		{
			WarningIn("min(const FieldField<Field, Type>&) const")
				<< "empty fieldField, returning zero" << endl;

			return pTraits<Type>::zero;
		}
	}

	template <template<class> class Field, class Type>
	Type min(const tmp<FieldField<Field, Type>>& tf1)
	{
		Type res = min(tf1());
		tf1.clear();
		return res;
	}

		template<template<class> class Field, class Type>
	Type sum(const FieldField<Field, Type>& f)
	{
		if (f.size())
		{
			Type Sum = pTraits<Type>::zero;

			forAll(f, i)
			{
				Sum += sum(f[i]);
			}

			return Sum;
		}
		else
		{
			return pTraits<Type>::zero;
		}
	}

	template <template<class> class Field, class Type>
	Type sum(const tmp<FieldField<Field, Type>>& tf1)
	{
		Type res = sum(tf1());
		tf1.clear();
		return res;
	}

		template<template<class> class Field, class Type>
	scalar sumMag(const FieldField<Field, Type>& f)
	{
		if (f.size())
		{
			scalar SumMag = 0.0;

			forAll(f, i)
			{
				SumMag += sumMag(f[i]);
			}

			return SumMag;
		}
		else
		{
			return 0.0;
		}
	}

	template <template<class> class Field, class Type>
	scalar sumMag(const tmp<FieldField<Field, Type>>& tf1)
	{
		scalar res = sumMag(tf1());
		tf1.clear();
		return res;
	}

		template<template<class> class Field, class Type>
	Type average(const FieldField<Field, Type>& f)
	{
		if (f.size())
		{
			label n = 0;

			forAll(f, i)
			{
				n += f[i].size();
			}

			if (n == 0)
			{
				WarningIn("average(const FieldField<Field, Type>&) const")
					<< "empty fieldField, returning zero" << endl;

				return pTraits<Type>::zero;
			}

			Type avrg = sum(f) / n;

			return avrg;
		}
		else
		{
			WarningIn("average(const FieldField<Field, Type>&) const")
				<< "empty fieldField, returning zero" << endl;

			return pTraits<Type>::zero;
		}
	}

	template <template<class> class Field, class Type>
	Type average(const tmp<FieldField<Field, Type>>& tf1)
	{
		Type res = average(tf1());
		tf1.clear();
		return res;
	}


#define G_UNARY_FUNCTION(returnType, gFunc, func, rFunc)                      \
                                                                              \
template<template<class> class Field, class Type>                             \
returnType gFunc(const FieldField<Field, Type>& f)                            \
{                                                                             \
    returnType res = func(f);                                                 \
    reduce(res, rFunc##Op<Type>());                                           \
    return res;                                                               \
}                                                                             \
TMP_UNARY_FUNCTION(returnType, gFunc)

		
	template <template<class> class Field, class Type>
	Type gMax(const FieldField<Field, Type>& f)
	{
		Type res = max(f);
		reduce(res, maxOp<Type>());
		return res;
	}

	template <template<class> class Field, class Type>
	Type gMax(const tmp<FieldField<Field, Type>>& tf1)
	{
		Type res = gMax(tf1());
		tf1.clear();
		return res;
	}
		
	template <template<class> class Field, class Type>
	Type gMin(const FieldField<Field, Type>& f)
	{
		Type res = min(f);
		reduce(res, minOp<Type>());
		return res;
	}

	template <template<class> class Field, class Type>
	Type gMin(const tmp<FieldField<Field, Type>>& tf1)
	{
		Type res = gMin(tf1());
		tf1.clear();
		return res;
	}
		
	template <template<class> class Field, class Type>
	Type gSum(const FieldField<Field, Type>& f)
	{
		Type res = sum(f);
		reduce(res, sumOp<Type>());
		return res;
	}

	template <template<class> class Field, class Type>
	Type gSum(const tmp<FieldField<Field, Type>>& tf1)
	{
		Type res = gSum(tf1());
		tf1.clear();
		return res;
	}
		
	template <template<class> class Field, class Type>
	scalar gSumMag(const FieldField<Field, Type>& f)
	{
		scalar res = sumMag(f);
		reduce(res, sumOp<Type>());
		return res;
	}

	template <template<class> class Field, class Type>
	scalar gSumMag(const tmp<FieldField<Field, Type>>& tf1)
	{
		scalar res = gSumMag(tf1());
		tf1.clear();
		return res;
	}

#undef G_UNARY_FUNCTION


		template<class Type>
	scalar gSumProd
	(
		const FieldField<Field, Type>& f1,
		const FieldField<Field, Type>& f2
	)
	{
		scalar SumProd = 0;

		if (f1.size() && (f1.size() == f2.size()))
		{
			forAll(f1, i)
			{
				SumProd += sumProd(f1[i], f2[i]);
			}
			reduce(SumProd, sumOp<scalar>());
		}

		return SumProd;
	}


	template<template<class> class Field, class Type>
	Type gAverage(const FieldField<Field, Type>& f)
	{
		label n = 0;

		forAll(f, i)
		{
			n += f[i].size();
		}

		reduce(n, sumOp<label>());

		if (n > 0)
		{
			Type avrg = gSum(f) / n;

			return avrg;
		}
		else
		{
			WarningIn("gAverage(const FieldField<Field, Type>&) const")
				<< "empty fieldField, returning zero" << endl;

			return pTraits<Type>::zero;
		}
	}

	template <template<class> class Field, class Type>
	Type gAverage(const tmp<FieldField<Field, Type>>& tf1)
	{
		Type res = gAverage(tf1());
		tf1.clear();
		return res;
	}

#undef TMP_UNARY_FUNCTION


		
	template<template<class> class Field, class Type>
	void max(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const FieldField<Field, Type>& f2)
	{
		for (tnbLib::label i=0; i<(f).size(); i++) { max(f[i], f1[i], f2[i]); }
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> max(const FieldField<Field, Type>& f1, const FieldField<Field, Type>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f1));
		max(tRes(), f1, f2);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> max(const FieldField<Field, Type>& f1, const tmp<FieldField<Field, Type>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf2));
		max(tRes(), f1, tf2());
		reuseTmpFieldField<Field, Type, Type>::clear(tf2);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> max(const tmp<FieldField<Field, Type>>& tf1, const FieldField<Field, Type>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf1));
		max(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, Type, Type>::clear(tf1);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> max(const tmp<FieldField<Field, Type>>& tf1, const tmp<FieldField<Field, Type>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpTmpFieldField<Field, Type, Type, Type, Type>::New(tf1, tf2));
		max(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, Type, Type, Type, Type>::clear(tf1, tf2);
		return tRes;
	}
		
	template<template<class> class Field, class Type>
	void min(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const FieldField<Field, Type>& f2)
	{
		forAll(f, i) { min(f[i], f1[i], f2[i]); }
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> min(const FieldField<Field, Type>& f1, const FieldField<Field, Type>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f1));
		min(tRes(), f1, f2);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> min(const FieldField<Field, Type>& f1, const tmp<FieldField<Field, Type>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf2));
		min(tRes(), f1, tf2());
		reuseTmpFieldField<Field, Type, Type>::clear(tf2);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> min(const tmp<FieldField<Field, Type>>& tf1, const FieldField<Field, Type>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf1));
		min(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, Type, Type>::clear(tf1);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> min(const tmp<FieldField<Field, Type>>& tf1, const tmp<FieldField<Field, Type>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpTmpFieldField<Field, Type, Type, Type, Type>::New(tf1, tf2));
		min(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, Type, Type, Type, Type>::clear(tf1, tf2);
		return tRes;
	}
		
	template<template<class> class Field, class Type>
	void cmptMultiply(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const FieldField<Field, Type>& f2)
	{
		forAll(f, i) { cmptMultiply(f[i], f1[i], f2[i]); }
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptMultiply(const FieldField<Field, Type>& f1, const FieldField<Field, Type>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f1));
		cmptMultiply(tRes(), f1, f2);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptMultiply(const FieldField<Field, Type>& f1, const tmp<FieldField<Field, Type>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf2));
		cmptMultiply(tRes(), f1, tf2());
		reuseTmpFieldField<Field, Type, Type>::clear(tf2);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptMultiply(const tmp<FieldField<Field, Type>>& tf1, const FieldField<Field, Type>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf1));
		cmptMultiply(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, Type, Type>::clear(tf1);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptMultiply(const tmp<FieldField<Field, Type>>& tf1
	                                          , const tmp<FieldField<Field, Type>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpTmpFieldField<Field, Type, Type, Type, Type>::New(tf1, tf2));
		cmptMultiply(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, Type, Type, Type, Type>::clear(tf1, tf2);
		return tRes;
	}
		
	template<template<class> class Field, class Type>
	void cmptDivide(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const FieldField<Field, Type>& f2)
	{
		forAll(f, i) { cmptDivide(f[i], f1[i], f2[i]); }
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptDivide(const FieldField<Field, Type>& f1, const FieldField<Field, Type>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f1));
		cmptDivide(tRes(), f1, f2);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptDivide(const FieldField<Field, Type>& f1, const tmp<FieldField<Field, Type>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf2));
		cmptDivide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, Type, Type>::clear(tf2);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptDivide(const tmp<FieldField<Field, Type>>& tf1, const FieldField<Field, Type>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf1));
		cmptDivide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, Type, Type>::clear(tf1);
		return tRes;
	}

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptDivide(const tmp<FieldField<Field, Type>>& tf1
	                                        , const tmp<FieldField<Field, Type>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpTmpFieldField<Field, Type, Type, Type, Type>::New(tf1, tf2));
		cmptDivide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, Type, Type, Type, Type>::clear(tf1, tf2);
		return tRes;
	}

		
	TEMPLATE
	void max(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const Type& s)
	{
		forAll(f, i) { max(f[i], f1[i], s); }
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> max(const FieldField<Field, Type>& f1, const Type& s)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f1));
		max(tRes(), f1, s);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> max(const tmp<FieldField<Field, Type>>& tf1, const Type& s)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf1));
		max(tRes(), tf1(), s);
		reuseTmpFieldField<Field, Type, Type>::clear(tf1);
		return tRes;
	} 
	
	TEMPLATE
	void max(FieldField<Field, Type>& f, const Type& s, const FieldField<Field, Type>& f2)
	{
		forAll(f, i) { max(f[i], s, f2[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> max(const Type& s, const FieldField<Field, Type>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f2));
		max(tRes(), s, f2);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> max(const Type& s, const tmp<FieldField<Field, Type>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf2));
		max(tRes(), s, tf2());
		reuseTmpFieldField<Field, Type, Type>::clear(tf2);
		return tRes;
	}
		
	TEMPLATE
	void min(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const Type& s)
	{
		forAll(f, i) { min(f[i], f1[i], s); }
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> min(const FieldField<Field, Type>& f1, const Type& s)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f1));
		min(tRes(), f1, s);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> min(const tmp<FieldField<Field, Type>>& tf1, const Type& s)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf1));
		min(tRes(), tf1(), s);
		reuseTmpFieldField<Field, Type, Type>::clear(tf1);
		return tRes;
	} 
	
	TEMPLATE
	void min(FieldField<Field, Type>& f, const Type& s, const FieldField<Field, Type>& f2)
	{
		forAll(f, i) { min(f[i], s, f2[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> min(const Type& s, const FieldField<Field, Type>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f2));
		min(tRes(), s, f2);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> min(const Type& s, const tmp<FieldField<Field, Type>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf2));
		min(tRes(), s, tf2());
		reuseTmpFieldField<Field, Type, Type>::clear(tf2);
		return tRes;
	}
		
	TEMPLATE
	void cmptMultiply(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const Type& s)
	{
		forAll(f, i) { cmptMultiply(f[i], f1[i], s); }
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> cmptMultiply(const FieldField<Field, Type>& f1, const Type& s)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f1));
		cmptMultiply(tRes(), f1, s);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> cmptMultiply(const tmp<FieldField<Field, Type>>& tf1, const Type& s)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf1));
		cmptMultiply(tRes(), tf1(), s);
		reuseTmpFieldField<Field, Type, Type>::clear(tf1);
		return tRes;
	}
	
	TEMPLATE
	void cmptMultiply(FieldField<Field, Type>& f, const Type& s, const FieldField<Field, Type>& f2)
	{
		forAll(f, i) { cmptMultiply(f[i], s, f2[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> cmptMultiply(const Type& s, const FieldField<Field, Type>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f2));
		cmptMultiply(tRes(), s, f2);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> cmptMultiply(const Type& s, const tmp<FieldField<Field, Type>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf2));
		cmptMultiply(tRes(), s, tf2());
		reuseTmpFieldField<Field, Type, Type>::clear(tf2);
		return tRes;
	}
		
	TEMPLATE
	void cmptDivide(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const Type& s)
	{
		forAll(f, i) { cmptDivide(f[i], f1[i], s); }
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> cmptDivide(const FieldField<Field, Type>& f1, const Type& s)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f1));
		cmptDivide(tRes(), f1, s);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> cmptDivide(const tmp<FieldField<Field, Type>>& tf1, const Type& s)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf1));
		cmptDivide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, Type, Type>::clear(tf1);
		return tRes;
	} 
	
	TEMPLATE
	void cmptDivide(FieldField<Field, Type>& f, const Type& s, const FieldField<Field, Type>& f2)
	{
		forAll(f, i) { cmptDivide(f[i], s, f2[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> cmptDivide(const Type& s, const FieldField<Field, Type>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f2));
		cmptDivide(tRes(), s, f2);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> cmptDivide(const Type& s, const tmp<FieldField<Field, Type>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf2));
		cmptDivide(tRes(), s, tf2());
		reuseTmpFieldField<Field, Type, Type>::clear(tf2);
		return tRes;
	}


		/* * * * * * * * * * * * * * * * Global operators  * * * * * * * * * * * * * */

		
	TEMPLATE
	void negate(FieldField<Field, Type>& res, const FieldField<Field, Type>& f)
	{
		forAll(res, i) { negate(res[i], f[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> operator -(const FieldField<Field, Type>& f)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f));
		negate(tRes(), f);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> operator -(const tmp<FieldField<Field, Type>>& tf)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf));
		negate(tRes(), tf());
		reuseTmpFieldField<Field, Type, Type>::clear(tf);
		return tRes;
	}

#ifndef __INTEL_COMPILER
		
	TEMPLATE
	void multiply(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const FieldField<Field, scalar>& f2)
	{
		forAll(f, i) { multiply(f[i], f1[i], f2[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> operator *(const FieldField<Field, Type>& f1, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f1));
		multiply(tRes(), f1, f2);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> operator *(const FieldField<Field, Type>& f1, const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, scalar>::New(tf2));
		multiply(tRes(), f1, tf2());
		reuseTmpFieldField<Field, Type, scalar>::clear(tf2);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> operator *(const tmp<FieldField<Field, Type>>& tf1, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf1));
		multiply(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, Type, Type>::clear(tf1);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> operator *(const tmp<FieldField<Field, Type>>& tf1
	                                        , const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpTmpFieldField<Field, Type, Type, Type, scalar>::New(tf1, tf2));
		multiply(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, Type, Type, Type, scalar>::clear(tf1, tf2);
		return tRes;
	}
		
	TEMPLATE
	void multiply(FieldField<Field, Type>& f, const FieldField<Field, scalar>& f1, const FieldField<Field, Type>& f2)
	{
		forAll(f, i) { multiply(f[i], f1[i], f2[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> operator *(const FieldField<Field, scalar>& f1, const FieldField<Field, Type>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f1));
		multiply(tRes(), f1, f2);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> operator *(const FieldField<Field, scalar>& f1, const tmp<FieldField<Field, Type>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf2));
		multiply(tRes(), f1, tf2());
		reuseTmpFieldField<Field, Type, Type>::clear(tf2);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> operator *(const tmp<FieldField<Field, scalar>>& tf1, const FieldField<Field, Type>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, scalar>::New(tf1));
		multiply(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, Type, scalar>::clear(tf1);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> operator *(const tmp<FieldField<Field, scalar>>& tf1
	                                        , const tmp<FieldField<Field, Type>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpTmpFieldField<Field, Type, scalar, scalar, Type>::New(tf1, tf2));
		multiply(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, Type, scalar, scalar, Type>::clear(tf1, tf2);
		return tRes;
	}
#endif
		
	TEMPLATE
	void divide(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const FieldField<Field, scalar>& f2)
	{
		forAll(f, i) { divide(f[i], f1[i], f2[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> operator /(const FieldField<Field, Type>& f1, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f1));
		divide(tRes(), f1, f2);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> operator /(const FieldField<Field, Type>& f1, const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, scalar>::New(tf2));
		divide(tRes(), f1, tf2());
		reuseTmpFieldField<Field, Type, scalar>::clear(tf2);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> operator /(const tmp<FieldField<Field, Type>>& tf1, const FieldField<Field, scalar>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf1));
		divide(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, Type, Type>::clear(tf1);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> operator /(const tmp<FieldField<Field, Type>>& tf1
	                                        , const tmp<FieldField<Field, scalar>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpTmpFieldField<Field, Type, Type, Type, scalar>::New(tf1, tf2));
		divide(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, Type, Type, Type, scalar>::clear(tf1, tf2);
		return tRes;
	}

		
	TEMPLATE
	void multiply(FieldField<Field, Type>& f, const scalar& s, const FieldField<Field, Type>& f2)
	{
		forAll(f, i) { multiply(f[i], s, f2[i]); }
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> operator *(const scalar& s, const FieldField<Field, Type>& f2)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f2));
		multiply(tRes(), s, f2);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> operator *(const scalar& s, const tmp<FieldField<Field, Type>>& tf2)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf2));
		multiply(tRes(), s, tf2());
		reuseTmpFieldField<Field, Type, Type>::clear(tf2);
		return tRes;
	}
		
	TEMPLATE
	void multiply(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const scalar& s)
	{
		forAll(f, i) { multiply(f[i], f1[i], s); }
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> operator *(const FieldField<Field, Type>& f1, const scalar& s)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f1));
		multiply(tRes(), f1, s);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> operator *(const tmp<FieldField<Field, Type>>& tf1, const scalar& s)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf1));
		multiply(tRes(), tf1(), s);
		reuseTmpFieldField<Field, Type, Type>::clear(tf1);
		return tRes;
	}

		
	TEMPLATE
	void divide(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const scalar& s)
	{
		forAll(f, i) { divide(f[i], f1[i], s); }
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> operator /(const FieldField<Field, Type>& f1, const scalar& s)
	{
		tmp<FieldField<Field, Type>> tRes(FieldField<Field, Type>::NewCalculatedType(f1));
		divide(tRes(), f1, s);
		return tRes;
	}

	TEMPLATE
	tmp<FieldField<Field, Type>> operator /(const tmp<FieldField<Field, Type>>& tf1, const scalar& s)
	{
		tmp<FieldField<Field, Type>> tRes(reuseTmpFieldField<Field, Type, Type>::New(tf1));
		divide(tRes(), tf1(), s);
		reuseTmpFieldField<Field, Type, Type>::clear(tf1);
		return tRes;
	}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define PRODUCT_OPERATOR(product, op, opFunc)                                 \
                                                                              \
template<template<class> class Field, class Type1, class Type2>               \
void opFunc                                                                   \
(                                                                             \
    FieldField<Field, typename product<Type1, Type2>::type>& f,               \
    const FieldField<Field, Type1>& f1,                                       \
    const FieldField<Field, Type2>& f2                                        \
)                                                                             \
{                                                                             \
    forAll(f, i)                                                              \
    {                                                                         \
        opFunc(f[i], f1[i], f2[i]);                                           \
    }                                                                         \
}                                                                             \
                                                                              \
template<template<class> class Field, class Type1, class Type2>               \
tmp<FieldField<Field, typename product<Type1, Type2>::type> >                 \
operator op                                                                   \
(                                                                             \
    const FieldField<Field, Type1>& f1,                                       \
    const FieldField<Field, Type2>& f2                                        \
)                                                                             \
{                                                                             \
    typedef typename product<Type1, Type2>::type productType;                 \
    tmp<FieldField<Field, productType> > tRes                                 \
    (                                                                         \
        FieldField<Field, productType>::NewCalculatedType(f1)                 \
    );                                                                        \
    opFunc(tRes(), f1, f2);                                                   \
    return tRes;                                                              \
}                                                                             \
                                                                              \
template<template<class> class Field, class Type1, class Type2>               \
tmp<FieldField<Field, typename product<Type1, Type2>::type> >                 \
operator op                                                                   \
(                                                                             \
    const FieldField<Field, Type1>& f1,                                       \
    const tmp<FieldField<Field, Type2> >& tf2                                 \
)                                                                             \
{                                                                             \
    typedef typename product<Type1, Type2>::type productType;                 \
    tmp<FieldField<Field, productType> > tRes                                 \
    (                                                                         \
        reuseTmpFieldField<Field, productType, Type2>::New(tf2)               \
    );                                                                        \
    opFunc(tRes(), f1, tf2());                                                \
    reuseTmpFieldField<Field, productType, Type2>::clear(tf2);                \
    return tRes;                                                              \
}                                                                             \
                                                                              \
template<template<class> class Field, class Type1, class Type2>               \
tmp<FieldField<Field, typename product<Type1, Type2>::type> >                 \
operator op                                                                   \
(                                                                             \
    const tmp<FieldField<Field, Type1> >& tf1,                                \
    const FieldField<Field, Type2>& f2                                        \
)                                                                             \
{                                                                             \
    typedef typename product<Type1, Type2>::type productType;                 \
    tmp<FieldField<Field, productType> > tRes                                 \
    (                                                                         \
        reuseTmpFieldField<Field, productType, Type1>::New(tf1)               \
    );                                                                        \
    opFunc(tRes(), tf1(), f2);                                                \
    reuseTmpFieldField<Field, productType, Type1>::clear(tf1);                \
    return tRes;                                                              \
}                                                                             \
                                                                              \
template<template<class> class Field, class Type1, class Type2>               \
tmp<FieldField<Field, typename product<Type1, Type2>::type> >                 \
operator op                                                                   \
(                                                                             \
    const tmp<FieldField<Field, Type1> >& tf1,                                \
    const tmp<FieldField<Field, Type2> >& tf2                                 \
)                                                                             \
{                                                                             \
    typedef typename product<Type1, Type2>::type productType;                 \
    tmp<FieldField<Field, productType> > tRes                                 \
    (                                                                         \
        reuseTmpTmpFieldField<Field, productType, Type1, Type1, Type2>::New   \
            (tf1, tf2)                                                        \
    );                                                                        \
    opFunc(tRes(), tf1(), tf2());                                             \
    reuseTmpTmpFieldField<Field, productType, Type1, Type1, Type2>::clear     \
        (tf1, tf2);                                                           \
    return tRes;                                                              \
}                                                                             \
                                                                              \
template                                                                      \
<template<class> class Field, class Type, class Form, class Cmpt, int nCmpt>  \
void opFunc                                                                   \
(                                                                             \
    FieldField<Field, typename product<Type, Form>::type>& f,                 \
    const FieldField<Field, Type>& f1,                                        \
    const VectorSpace<Form,Cmpt,nCmpt>& vs                                    \
)                                                                             \
{                                                                             \
    forAll(f, i)                                                              \
    {                                                                         \
        opFunc(f[i], f1[i], vs);                                              \
    }                                                                         \
}                                                                             \
                                                                              \
template                                                                      \
<template<class> class Field, class Type, class Form, class Cmpt, int nCmpt>  \
tmp<FieldField<Field, typename product<Type, Form>::type> >                   \
operator op                                                                   \
(                                                                             \
    const FieldField<Field, Type>& f1,                                        \
    const VectorSpace<Form,Cmpt,nCmpt>& vs                                    \
)                                                                             \
{                                                                             \
    typedef typename product<Type, Form>::type productType;                   \
    tmp<FieldField<Field, productType> > tRes                                 \
    (                                                                         \
        FieldField<Field, productType>::NewCalculatedType(f1)                 \
    );                                                                        \
    opFunc(tRes(), f1, static_cast<const Form&>(vs));                         \
    return tRes;                                                              \
}                                                                             \
                                                                              \
template                                                                      \
<template<class> class Field, class Type, class Form, class Cmpt, int nCmpt>  \
tmp<FieldField<Field, typename product<Type, Form>::type> >                   \
operator op                                                                   \
(                                                                             \
    const tmp<FieldField<Field, Type> >& tf1,                                 \
    const VectorSpace<Form,Cmpt,nCmpt>& vs                                    \
)                                                                             \
{                                                                             \
    typedef typename product<Type, Form>::type productType;                   \
    tmp<FieldField<Field, productType> > tRes                                 \
    (                                                                         \
        reuseTmpFieldField<Field, productType, Type>::New(tf1)                \
    );                                                                        \
    opFunc(tRes(), tf1(), static_cast<const Form&>(vs));                      \
    reuseTmpFieldField<Field, productType, Type>::clear(tf1);                 \
    return tRes;                                                              \
}                                                                             \
                                                                              \
template                                                                      \
<template<class> class Field, class Form, class Cmpt, int nCmpt, class Type>  \
void opFunc                                                                   \
(                                                                             \
    FieldField<Field, typename product<Form, Type>::type>& f,                 \
    const VectorSpace<Form,Cmpt,nCmpt>& vs,                                   \
    const FieldField<Field, Type>& f1                                         \
)                                                                             \
{                                                                             \
    forAll(f, i)                                                              \
    {                                                                         \
        opFunc(f[i], vs, f1[i]);                                              \
    }                                                                         \
}                                                                             \
                                                                              \
template                                                                      \
<template<class> class Field, class Form, class Cmpt, int nCmpt, class Type>  \
tmp<FieldField<Field, typename product<Form, Type>::type> >                   \
operator op                                                                   \
(                                                                             \
    const VectorSpace<Form,Cmpt,nCmpt>& vs,                                   \
    const FieldField<Field, Type>& f1                                         \
)                                                                             \
{                                                                             \
    typedef typename product<Form, Type>::type productType;                   \
    tmp<FieldField<Field, productType> > tRes                                 \
    (                                                                         \
        FieldField<Field, productType>::NewCalculatedType(f1)                 \
    );                                                                        \
    opFunc(tRes(), static_cast<const Form&>(vs), f1);                         \
    return tRes;                                                              \
}                                                                             \
                                                                              \
template                                                                      \
<template<class> class Field, class Form, class Cmpt, int nCmpt, class Type>  \
tmp<FieldField<Field, typename product<Form, Type>::type> >                   \
operator op                                                                   \
(                                                                             \
    const VectorSpace<Form,Cmpt,nCmpt>& vs,                                   \
    const tmp<FieldField<Field, Type> >& tf1                                  \
)                                                                             \
{                                                                             \
    typedef typename product<Form, Type>::type productType;                   \
    tmp<FieldField<Field, productType> > tRes                                 \
    (                                                                         \
        reuseTmpFieldField<Field, productType, Type>::New(tf1)                \
    );                                                                        \
    opFunc(tRes(), static_cast<const Form&>(vs), tf1());                      \
    reuseTmpFieldField<Field, productType, Type>::clear(tf1);                 \
    return tRes;                                                              \
}

		
	template <template<class> class Field, class Type1, class Type2>
	void add(FieldField<Field, typename typeOfSum<Type1, Type2>::type>& f, const FieldField<Field, Type1>& f1
	         , const FieldField<Field, Type2>& f2)
	{
		forAll(f, i) { add(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename typeOfSum<Type1, Type2>::type>> operator +(
		const FieldField<Field, Type1>& f1, const FieldField<Field, Type2>& f2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		tmp<FieldField<Field, productType>> tRes(FieldField<Field, productType>::NewCalculatedType(f1));
		add(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename typeOfSum<Type1, Type2>::type>> operator +(
		const FieldField<Field, Type1>& f1, const tmp<FieldField<Field, Type2>>& tf2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type2>::New(tf2));
		add(tRes(), f1, tf2());
		reuseTmpFieldField<Field, productType, Type2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename typeOfSum<Type1, Type2>::type>> operator +(
		const tmp<FieldField<Field, Type1>>& tf1, const FieldField<Field, Type2>& f2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type1>::New(tf1));
		add(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, productType, Type1>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename typeOfSum<Type1, Type2>::type>> operator +(
		const tmp<FieldField<Field, Type1>>& tf1, const tmp<FieldField<Field, Type2>>& tf2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		tmp<FieldField<Field, productType>> tRes(
			reuseTmpTmpFieldField<Field, productType, Type1, Type1, Type2>::New(tf1, tf2));
		add(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, productType, Type1, Type1, Type2>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, int nCmpt>
	void add(FieldField<Field, typename typeOfSum<Type, Form>::type>& f, const FieldField<Field, Type>& f1
	         , const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		forAll(f, i) { add(f[i], f1[i], vs); }
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, int nCmpt>
	tmp<FieldField<Field, typename typeOfSum<Type, Form>::type>> operator +(
		const FieldField<Field, Type>& f1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename typeOfSum<Type, Form>::type productType;
		tmp<FieldField<Field, productType>> tRes(FieldField<Field, productType>::NewCalculatedType(f1));
		add(tRes(), f1, static_cast<const Form&>(vs));
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, int nCmpt>
	tmp<FieldField<Field, typename typeOfSum<Type, Form>::type>> operator +(
		const tmp<FieldField<Field, Type>>& tf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename typeOfSum<Type, Form>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type>::New(tf1));
		add(tRes(), tf1(), static_cast<const Form&>(vs));
		reuseTmpFieldField<Field, productType, Type>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field, class Form, class Cmpt, int nCmpt, class Type>
	void add(FieldField<Field, typename typeOfSum<Form, Type>::type>& f, const VectorSpace<Form, Cmpt, nCmpt>& vs
	         , const FieldField<Field, Type>& f1)
	{
		forAll(f, i) { add(f[i], vs, f1[i]); }
	}

	template <template<class> class Field, class Form, class Cmpt, int nCmpt, class Type>
	tmp<FieldField<Field, typename typeOfSum<Form, Type>::type>> operator +(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const FieldField<Field, Type>& f1)
	{
		typedef typename typeOfSum<Form, Type>::type productType;
		tmp<FieldField<Field, productType>> tRes(FieldField<Field, productType>::NewCalculatedType(f1));
		add(tRes(), static_cast<const Form&>(vs), f1);
		return tRes;
	}

	template <template<class> class Field, class Form, class Cmpt, int nCmpt, class Type>
	tmp<FieldField<Field, typename typeOfSum<Form, Type>::type>> operator +(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<FieldField<Field, Type>>& tf1)
	{
		typedef typename typeOfSum<Form, Type>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type>::New(tf1));
		add(tRes(), static_cast<const Form&>(vs), tf1());
		reuseTmpFieldField<Field, productType, Type>::clear(tf1);
		return tRes;
	}
		
	template <template<class> class Field, class Type1, class Type2>
	void subtract(FieldField<Field, typename typeOfSum<Type1, Type2>::type>& f, const FieldField<Field, Type1>& f1
	              , const FieldField<Field, Type2>& f2)
	{
		forAll(f, i) { subtract(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename typeOfSum<Type1, Type2>::type>> operator -(
		const FieldField<Field, Type1>& f1, const FieldField<Field, Type2>& f2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		tmp<FieldField<Field, productType>> tRes(FieldField<Field, productType>::NewCalculatedType(f1));
		subtract(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename typeOfSum<Type1, Type2>::type>> operator -(
		const FieldField<Field, Type1>& f1, const tmp<FieldField<Field, Type2>>& tf2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type2>::New(tf2));
		subtract(tRes(), f1, tf2());
		reuseTmpFieldField<Field, productType, Type2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename typeOfSum<Type1, Type2>::type>> operator -(
		const tmp<FieldField<Field, Type1>>& tf1, const FieldField<Field, Type2>& f2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type1>::New(tf1));
		subtract(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, productType, Type1>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename typeOfSum<Type1, Type2>::type>> operator -(
		const tmp<FieldField<Field, Type1>>& tf1, const tmp<FieldField<Field, Type2>>& tf2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		tmp<FieldField<Field, productType>> tRes(
			reuseTmpTmpFieldField<Field, productType, Type1, Type1, Type2>::New(tf1, tf2));
		subtract(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, productType, Type1, Type1, Type2>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, int nCmpt>
	void subtract(FieldField<Field, typename typeOfSum<Type, Form>::type>& f, const FieldField<Field, Type>& f1
	              , const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		forAll(f, i) { subtract(f[i], f1[i], vs); }
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, int nCmpt>
	tmp<FieldField<Field, typename typeOfSum<Type, Form>::type>> operator -(
		const FieldField<Field, Type>& f1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename typeOfSum<Type, Form>::type productType;
		tmp<FieldField<Field, productType>> tRes(FieldField<Field, productType>::NewCalculatedType(f1));
		subtract(tRes(), f1, static_cast<const Form&>(vs));
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, int nCmpt>
	tmp<FieldField<Field, typename typeOfSum<Type, Form>::type>> operator -(
		const tmp<FieldField<Field, Type>>& tf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename typeOfSum<Type, Form>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type>::New(tf1));
		subtract(tRes(), tf1(), static_cast<const Form&>(vs));
		reuseTmpFieldField<Field, productType, Type>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field, class Form, class Cmpt, int nCmpt, class Type>
	void subtract(FieldField<Field, typename typeOfSum<Form, Type>::type>& f, const VectorSpace<Form, Cmpt, nCmpt>& vs
	              , const FieldField<Field, Type>& f1)
	{
		forAll(f, i) { subtract(f[i], vs, f1[i]); }
	}

	template <template<class> class Field, class Form, class Cmpt, int nCmpt, class Type>
	tmp<FieldField<Field, typename typeOfSum<Form, Type>::type>> operator -(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const FieldField<Field, Type>& f1)
	{
		typedef typename typeOfSum<Form, Type>::type productType;
		tmp<FieldField<Field, productType>> tRes(FieldField<Field, productType>::NewCalculatedType(f1));
		subtract(tRes(), static_cast<const Form&>(vs), f1);
		return tRes;
	}

	template <template<class> class Field, class Form, class Cmpt, int nCmpt, class Type>
	tmp<FieldField<Field, typename typeOfSum<Form, Type>::type>> operator -(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<FieldField<Field, Type>>& tf1)
	{
		typedef typename typeOfSum<Form, Type>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type>::New(tf1));
		subtract(tRes(), static_cast<const Form&>(vs), tf1());
		reuseTmpFieldField<Field, productType, Type>::clear(tf1);
		return tRes;
	}

		
	template <template<class> class Field, class Type1, class Type2>
	void outer(FieldField<Field, typename outerProduct<Type1, Type2>::type>& f, const FieldField<Field, Type1>& f1
	           , const FieldField<Field, Type2>& f2)
	{
		forAll(f, i) { outer(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename outerProduct<Type1, Type2>::type>> operator *(
		const FieldField<Field, Type1>& f1, const FieldField<Field, Type2>& f2)
	{
		typedef typename outerProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field, productType>> tRes(FieldField<Field, productType>::NewCalculatedType(f1));
		outer(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename outerProduct<Type1, Type2>::type>> operator *(
		const FieldField<Field, Type1>& f1, const tmp<FieldField<Field, Type2>>& tf2)
	{
		typedef typename outerProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type2>::New(tf2));
		outer(tRes(), f1, tf2());
		reuseTmpFieldField<Field, productType, Type2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename outerProduct<Type1, Type2>::type>> operator *(
		const tmp<FieldField<Field, Type1>>& tf1, const FieldField<Field, Type2>& f2)
	{
		typedef typename outerProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type1>::New(tf1));
		outer(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, productType, Type1>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename outerProduct<Type1, Type2>::type>> operator *(
		const tmp<FieldField<Field, Type1>>& tf1, const tmp<FieldField<Field, Type2>>& tf2)
	{
		typedef typename outerProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field, productType>> tRes(
			reuseTmpTmpFieldField<Field, productType, Type1, Type1, Type2>::New(tf1, tf2));
		outer(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, productType, Type1, Type1, Type2>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, int nCmpt>
	void outer(FieldField<Field, typename outerProduct<Type, Form>::type>& f, const FieldField<Field, Type>& f1
	           , const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		forAll(f, i) { outer(f[i], f1[i], vs); }
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, int nCmpt>
	tmp<FieldField<Field, typename outerProduct<Type, Form>::type>> operator *(
		const FieldField<Field, Type>& f1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename outerProduct<Type, Form>::type productType;
		tmp<FieldField<Field, productType>> tRes(FieldField<Field, productType>::NewCalculatedType(f1));
		outer(tRes(), f1, static_cast<const Form&>(vs));
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, int nCmpt>
	tmp<FieldField<Field, typename outerProduct<Type, Form>::type>> operator *(
		const tmp<FieldField<Field, Type>>& tf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename outerProduct<Type, Form>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type>::New(tf1));
		outer(tRes(), tf1(), static_cast<const Form&>(vs));
		reuseTmpFieldField<Field, productType, Type>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field, class Form, class Cmpt, int nCmpt, class Type>
	void outer(FieldField<Field, typename outerProduct<Form, Type>::type>& f, const VectorSpace<Form, Cmpt, nCmpt>& vs
	           , const FieldField<Field, Type>& f1)
	{
		forAll(f, i) { outer(f[i], vs, f1[i]); }
	}

	template <template<class> class Field, class Form, class Cmpt, int nCmpt, class Type>
	tmp<FieldField<Field, typename outerProduct<Form, Type>::type>> operator *(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const FieldField<Field, Type>& f1)
	{
		typedef typename outerProduct<Form, Type>::type productType;
		tmp<FieldField<Field, productType>> tRes(FieldField<Field, productType>::NewCalculatedType(f1));
		outer(tRes(), static_cast<const Form&>(vs), f1);
		return tRes;
	}

	template <template<class> class Field, class Form, class Cmpt, int nCmpt, class Type>
	tmp<FieldField<Field, typename outerProduct<Form, Type>::type>> operator *(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<FieldField<Field, Type>>& tf1)
	{
		typedef typename outerProduct<Form, Type>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type>::New(tf1));
		outer(tRes(), static_cast<const Form&>(vs), tf1());
		reuseTmpFieldField<Field, productType, Type>::clear(tf1);
		return tRes;
	}
		
	template <template<class> class Field, class Type1, class Type2>
	void cross(FieldField<Field, typename crossProduct<Type1, Type2>::type>& f, const FieldField<Field, Type1>& f1
	           , const FieldField<Field, Type2>& f2)
	{
		forAll(f, i) { cross(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename crossProduct<Type1, Type2>::type>> operator ^(
		const FieldField<Field, Type1>& f1, const FieldField<Field, Type2>& f2)
	{
		typedef typename crossProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field, productType>> tRes(FieldField<Field, productType>::NewCalculatedType(f1));
		cross(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename crossProduct<Type1, Type2>::type>> operator ^(
		const FieldField<Field, Type1>& f1, const tmp<FieldField<Field, Type2>>& tf2)
	{
		typedef typename crossProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type2>::New(tf2));
		cross(tRes(), f1, tf2());
		reuseTmpFieldField<Field, productType, Type2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename crossProduct<Type1, Type2>::type>> operator ^(
		const tmp<FieldField<Field, Type1>>& tf1, const FieldField<Field, Type2>& f2)
	{
		typedef typename crossProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type1>::New(tf1));
		cross(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, productType, Type1>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename crossProduct<Type1, Type2>::type>> operator ^(
		const tmp<FieldField<Field, Type1>>& tf1, const tmp<FieldField<Field, Type2>>& tf2)
	{
		typedef typename crossProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field, productType>> tRes(
			reuseTmpTmpFieldField<Field, productType, Type1, Type1, Type2>::New(tf1, tf2));
		cross(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, productType, Type1, Type1, Type2>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, int nCmpt>
	void cross(FieldField<Field, typename crossProduct<Type, Form>::type>& f, const FieldField<Field, Type>& f1
	           , const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		forAll(f, i) { cross(f[i], f1[i], vs); }
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, int nCmpt>
	tmp<FieldField<Field, typename crossProduct<Type, Form>::type>> operator ^(
		const FieldField<Field, Type>& f1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename crossProduct<Type, Form>::type productType;
		tmp<FieldField<Field, productType>> tRes(FieldField<Field, productType>::NewCalculatedType(f1));
		cross(tRes(), f1, static_cast<const Form&>(vs));
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, int nCmpt>
	tmp<FieldField<Field, typename crossProduct<Type, Form>::type>> operator ^(
		const tmp<FieldField<Field, Type>>& tf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename crossProduct<Type, Form>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type>::New(tf1));
		cross(tRes(), tf1(), static_cast<const Form&>(vs));
		reuseTmpFieldField<Field, productType, Type>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field, class Form, class Cmpt, int nCmpt, class Type>
	void cross(FieldField<Field, typename crossProduct<Form, Type>::type>& f, const VectorSpace<Form, Cmpt, nCmpt>& vs
	           , const FieldField<Field, Type>& f1)
	{
		forAll(f, i) { cross(f[i], vs, f1[i]); }
	}

	template <template<class> class Field, class Form, class Cmpt, int nCmpt, class Type>
	tmp<FieldField<Field, typename crossProduct<Form, Type>::type>> operator ^(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const FieldField<Field, Type>& f1)
	{
		typedef typename crossProduct<Form, Type>::type productType;
		tmp<FieldField<Field, productType>> tRes(FieldField<Field, productType>::NewCalculatedType(f1));
		cross(tRes(), static_cast<const Form&>(vs), f1);
		return tRes;
	}

	template <template<class> class Field, class Form, class Cmpt, int nCmpt, class Type>
	tmp<FieldField<Field, typename crossProduct<Form, Type>::type>> operator ^(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<FieldField<Field, Type>>& tf1)
	{
		typedef typename crossProduct<Form, Type>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type>::New(tf1));
		cross(tRes(), static_cast<const Form&>(vs), tf1());
		reuseTmpFieldField<Field, productType, Type>::clear(tf1);
		return tRes;
	}
		
	template <template<class> class Field, class Type1, class Type2>
	void dot(FieldField<Field, typename innerProduct<Type1, Type2>::type>& f, const FieldField<Field, Type1>& f1
	         , const FieldField<Field, Type2>& f2)
	{
		forAll(f, i) { dot(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename innerProduct<Type1, Type2>::type>> operator &(
		const FieldField<Field, Type1>& f1, const FieldField<Field, Type2>& f2)
	{
		typedef typename innerProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field, productType>> tRes(FieldField<Field, productType>::NewCalculatedType(f1));
		dot(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename innerProduct<Type1, Type2>::type>> operator &(
		const FieldField<Field, Type1>& f1, const tmp<FieldField<Field, Type2>>& tf2)
	{
		typedef typename innerProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type2>::New(tf2));
		dot(tRes(), f1, tf2());
		reuseTmpFieldField<Field, productType, Type2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename innerProduct<Type1, Type2>::type>> operator &(
		const tmp<FieldField<Field, Type1>>& tf1, const FieldField<Field, Type2>& f2)
	{
		typedef typename innerProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type1>::New(tf1));
		dot(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, productType, Type1>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename innerProduct<Type1, Type2>::type>> operator &(
		const tmp<FieldField<Field, Type1>>& tf1, const tmp<FieldField<Field, Type2>>& tf2)
	{
		typedef typename innerProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field, productType>> tRes(
			reuseTmpTmpFieldField<Field, productType, Type1, Type1, Type2>::New(tf1, tf2));
		dot(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, productType, Type1, Type1, Type2>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, int nCmpt>
	void dot(FieldField<Field, typename innerProduct<Type, Form>::type>& f, const FieldField<Field, Type>& f1
	         , const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		forAll(f, i) { dot(f[i], f1[i], vs); }
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, int nCmpt>
	tmp<FieldField<Field, typename innerProduct<Type, Form>::type>> operator &(
		const FieldField<Field, Type>& f1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename innerProduct<Type, Form>::type productType;
		tmp<FieldField<Field, productType>> tRes(FieldField<Field, productType>::NewCalculatedType(f1));
		dot(tRes(), f1, static_cast<const Form&>(vs));
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, int nCmpt>
	tmp<FieldField<Field, typename innerProduct<Type, Form>::type>> operator &(
		const tmp<FieldField<Field, Type>>& tf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename innerProduct<Type, Form>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type>::New(tf1));
		dot(tRes(), tf1(), static_cast<const Form&>(vs));
		reuseTmpFieldField<Field, productType, Type>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field, class Form, class Cmpt, int nCmpt, class Type>
	void dot(FieldField<Field, typename innerProduct<Form, Type>::type>& f, const VectorSpace<Form, Cmpt, nCmpt>& vs
	         , const FieldField<Field, Type>& f1)
	{
		forAll(f, i) { dot(f[i], vs, f1[i]); }
	}

	template <template<class> class Field, class Form, class Cmpt, int nCmpt, class Type>
	tmp<FieldField<Field, typename innerProduct<Form, Type>::type>> operator &(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const FieldField<Field, Type>& f1)
	{
		typedef typename innerProduct<Form, Type>::type productType;
		tmp<FieldField<Field, productType>> tRes(FieldField<Field, productType>::NewCalculatedType(f1));
		dot(tRes(), static_cast<const Form&>(vs), f1);
		return tRes;
	}

	template <template<class> class Field, class Form, class Cmpt, int nCmpt, class Type>
	tmp<FieldField<Field, typename innerProduct<Form, Type>::type>> operator &(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<FieldField<Field, Type>>& tf1)
	{
		typedef typename innerProduct<Form, Type>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type>::New(tf1));
		dot(tRes(), static_cast<const Form&>(vs), tf1());
		reuseTmpFieldField<Field, productType, Type>::clear(tf1);
		return tRes;
	}
		
	template <template<class> class Field, class Type1, class Type2>
	void dotdot(FieldField<Field, typename scalarProduct<Type1, Type2>::type>& f, const FieldField<Field, Type1>& f1
	            , const FieldField<Field, Type2>& f2)
	{
		forAll(f, i) { dotdot(f[i], f1[i], f2[i]); }
	}

	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename scalarProduct<Type1, Type2>::type>> operator &&(
		const FieldField<Field, Type1>& f1, const FieldField<Field, Type2>& f2)
	{
		typedef typename scalarProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field, productType>> tRes(FieldField<Field, productType>::NewCalculatedType(f1));
		dotdot(tRes(), f1, f2);
		return tRes;
	}

	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename scalarProduct<Type1, Type2>::type>> operator &&(
		const FieldField<Field, Type1>& f1, const tmp<FieldField<Field, Type2>>& tf2)
	{
		typedef typename scalarProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type2>::New(tf2));
		dotdot(tRes(), f1, tf2());
		reuseTmpFieldField<Field, productType, Type2>::clear(tf2);
		return tRes;
	}

	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename scalarProduct<Type1, Type2>::type>> operator &&(
		const tmp<FieldField<Field, Type1>>& tf1, const FieldField<Field, Type2>& f2)
	{
		typedef typename scalarProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type1>::New(tf1));
		dotdot(tRes(), tf1(), f2);
		reuseTmpFieldField<Field, productType, Type1>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename scalarProduct<Type1, Type2>::type>> operator &&(
		const tmp<FieldField<Field, Type1>>& tf1, const tmp<FieldField<Field, Type2>>& tf2)
	{
		typedef typename scalarProduct<Type1, Type2>::type productType;
		tmp<FieldField<Field, productType>> tRes(
			reuseTmpTmpFieldField<Field, productType, Type1, Type1, Type2>::New(tf1, tf2));
		dotdot(tRes(), tf1(), tf2());
		reuseTmpTmpFieldField<Field, productType, Type1, Type1, Type2>::clear(tf1, tf2);
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, int nCmpt>
	void dotdot(FieldField<Field, typename scalarProduct<Type, Form>::type>& f, const FieldField<Field, Type>& f1
	            , const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		forAll(f, i) { dotdot(f[i], f1[i], vs); }
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, int nCmpt>
	tmp<FieldField<Field, typename scalarProduct<Type, Form>::type>> operator &&(
		const FieldField<Field, Type>& f1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename scalarProduct<Type, Form>::type productType;
		tmp<FieldField<Field, productType>> tRes(FieldField<Field, productType>::NewCalculatedType(f1));
		dotdot(tRes(), f1, static_cast<const Form&>(vs));
		return tRes;
	}

	template <template<class> class Field, class Type, class Form, class Cmpt, int nCmpt>
	tmp<FieldField<Field, typename scalarProduct<Type, Form>::type>> operator &&(
		const tmp<FieldField<Field, Type>>& tf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		typedef typename scalarProduct<Type, Form>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type>::New(tf1));
		dotdot(tRes(), tf1(), static_cast<const Form&>(vs));
		reuseTmpFieldField<Field, productType, Type>::clear(tf1);
		return tRes;
	}

	template <template<class> class Field, class Form, class Cmpt, int nCmpt, class Type>
	void dotdot(FieldField<Field, typename scalarProduct<Form, Type>::type>& f, const VectorSpace<Form, Cmpt, nCmpt>& vs
	            , const FieldField<Field, Type>& f1)
	{
		forAll(f, i) { dotdot(f[i], vs, f1[i]); }
	}

	template <template<class> class Field, class Form, class Cmpt, int nCmpt, class Type>
	tmp<FieldField<Field, typename scalarProduct<Form, Type>::type>> operator &&(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const FieldField<Field, Type>& f1)
	{
		typedef typename scalarProduct<Form, Type>::type productType;
		tmp<FieldField<Field, productType>> tRes(FieldField<Field, productType>::NewCalculatedType(f1));
		dotdot(tRes(), static_cast<const Form&>(vs), f1);
		return tRes;
	}

	template <template<class> class Field, class Form, class Cmpt, int nCmpt, class Type>
	tmp<FieldField<Field, typename scalarProduct<Form, Type>::type>> operator &&(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<FieldField<Field, Type>>& tf1)
	{
		typedef typename scalarProduct<Form, Type>::type productType;
		tmp<FieldField<Field, productType>> tRes(reuseTmpFieldField<Field, productType, Type>::New(tf1));
		dotdot(tRes(), static_cast<const Form&>(vs), tf1());
		reuseTmpFieldField<Field, productType, Type>::clear(tf1);
		return tRes;
	}

#undef PRODUCT_OPERATOR


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <undefFieldFunctionsM.hxx>