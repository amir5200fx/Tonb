#include <DimensionedFieldReuseFunctions.hxx>
#include <DimensionedField.hxx>

#define TEMPLATE template<class Type, class GeoMesh>
#include <DimensionedFieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Global functions  * * * * * * * * * * * * * //

	template<class Type, class GeoMesh, int r>
	tmp<DimensionedField<typename powProduct<Type, r>::type, GeoMesh> >
		pow
		(
			const DimensionedField<Type, GeoMesh>& df,
			typename powProduct<Type, r>::type
		)
	{
		typedef typename powProduct<Type, r>::type powProductType;

		tmp<DimensionedField<powProductType, GeoMesh> > tPow
		(
			new DimensionedField<powProductType, GeoMesh>
			(
				IOobject
				(
					"pow(" + df.name() + ',' + name(r) + ')',
					df.instance(),
					df.db()
				),
				df.mesh(),
				pow(df.dimensions(), r)
				)
		);

		pow<Type, r, GeoMesh>(tPow().field(), df.field());

		return tPow;
	}


	template<class Type, class GeoMesh, int r>
	tmp<DimensionedField<typename powProduct<Type, r>::type, GeoMesh> >
		pow
		(
			const tmp<DimensionedField<Type, GeoMesh> >& tdf,
			typename powProduct<Type, r>::type
		)
	{
		typedef typename powProduct<Type, r>::type powProductType;

		const DimensionedField<Type, GeoMesh>& df = tdf();

		tmp<DimensionedField<powProductType, GeoMesh> > tPow =
			reuseTmpDimensionedField<powProductType, Type, GeoMesh>::New
			(
				tdf,
				"pow(" + df.name() + ',' + name(r) + ')',
				pow(df.dimensions(), r)
			);

		pow<Type, r, GeoMesh>(tPow().field(), df.field());

		reuseTmpDimensionedField<powProductType, Type, GeoMesh>::clear(tdf);

		return tPow;
	}

	template<class Type, class GeoMesh>
	tmp<DimensionedField<typename outerProduct<Type, Type>::type, GeoMesh> >
		sqr(const DimensionedField<Type, GeoMesh>& df)
	{
		typedef typename outerProduct<Type, Type>::type outerProductType;

		tmp<DimensionedField<outerProductType, GeoMesh> > tSqr
		(
			new DimensionedField<outerProductType, GeoMesh>
			(
				IOobject
				(
					"sqr(" + df.name() + ')',
					df.instance(),
					df.db()
				),
				df.mesh(),
				sqr(df.dimensions())
				)
		);

		sqr(tSqr().field(), df.field());

		return tSqr;
	}

	template<class Type, class GeoMesh>
	tmp<DimensionedField<typename outerProduct<Type, Type>::type, GeoMesh> >
		sqr(const tmp<DimensionedField<Type, GeoMesh> >& tdf)
	{
		typedef typename outerProduct<Type, Type>::type outerProductType;

		const DimensionedField<Type, GeoMesh>& df = tdf();

		tmp<DimensionedField<outerProductType, GeoMesh> > tSqr =
			reuseTmpDimensionedField<outerProductType, Type, GeoMesh>::New
			(
				tdf,
				"sqr(" + df.name() + ')',
				sqr(df.dimensions())
			);

		sqr(tSqr().field(), df.field());

		reuseTmpDimensionedField<outerProductType, Type, GeoMesh>::clear(tdf);

		return tSqr;
	}


	template<class Type, class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh> > magSqr
	(
		const DimensionedField<Type, GeoMesh>& df
	)
	{
		tmp<DimensionedField<scalar, GeoMesh> > tMagSqr
		(
			new DimensionedField<scalar, GeoMesh>
			(
				IOobject
				(
					"magSqr(" + df.name() + ')',
					df.instance(),
					df.db()
				),
				df.mesh(),
				sqr(df.dimensions())
				)
		);

		magSqr(tMagSqr().field(), df.field());

		return tMagSqr;
	}

	template<class Type, class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh> > magSqr
	(
		const tmp<DimensionedField<Type, GeoMesh> >& tdf
	)
	{
		const DimensionedField<Type, GeoMesh>& df = tdf();

		tmp<DimensionedField<scalar, GeoMesh> > tMagSqr =
			reuseTmpDimensionedField<scalar, Type, GeoMesh>::New
			(
				tdf,
				"magSqr(" + df.name() + ')',
				sqr(df.dimensions())
			);

		magSqr(tMagSqr().field(), df.field());

		reuseTmpDimensionedField<scalar, Type, GeoMesh>::clear(tdf);

		return tMagSqr;
	}


	template<class Type, class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh> > mag
	(
		const DimensionedField<Type, GeoMesh>& df
	)
	{
		tmp<DimensionedField<scalar, GeoMesh> > tMag
		(
			new DimensionedField<scalar, GeoMesh>
			(
				IOobject
				(
					"mag(" + df.name() + ')',
					df.instance(),
					df.db()
				),
				df.mesh(),
				df.dimensions()
				)
		);

		mag(tMag().field(), df.field());

		return tMag;
	}

	template<class Type, class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh> > mag
	(
		const tmp<DimensionedField<Type, GeoMesh> >& tdf
	)
	{
		const DimensionedField<Type, GeoMesh>& df = tdf();

		tmp<DimensionedField<scalar, GeoMesh> > tMag =
			reuseTmpDimensionedField<scalar, Type, GeoMesh>::New
			(
				tdf,
				"mag(" + df.name() + ')',
				df.dimensions()
			);

		mag(tMag().field(), df.field());

		reuseTmpDimensionedField<scalar, Type, GeoMesh>::clear(tdf);

		return tMag;
	}


	template<class Type, class GeoMesh>
	tmp
		<
		DimensionedField
		<typename DimensionedField<Type, GeoMesh>::cmptType, GeoMesh>
		>
		cmptAv(const DimensionedField<Type, GeoMesh>& df)
	{
		typedef typename DimensionedField<Type, GeoMesh>::cmptType cmptType;

		tmp<DimensionedField<cmptType, GeoMesh> > CmptAv
		(
			new DimensionedField<scalar, GeoMesh>
			(
				IOobject
				(
					"cmptAv(" + df.name() + ')',
					df.instance(),
					df.db()
				),
				df.mesh(),
				df.dimensions()
				)
		);

		cmptAv(CmptAv().field(), df.field());

		return CmptAv;
	}

	template<class Type, class GeoMesh>
	tmp
		<
		DimensionedField
		<typename DimensionedField<Type, GeoMesh>::cmptType, GeoMesh>
		>
		cmptAv(const tmp<DimensionedField<Type, GeoMesh> >& tdf)
	{
		typedef typename DimensionedField<Type, GeoMesh>::cmptType
			cmptType;

		const DimensionedField<Type, GeoMesh>& df = tdf();

		tmp<DimensionedField<cmptType, GeoMesh> > CmptAv =
			reuseTmpDimensionedField<cmptType, Type, GeoMesh>::New
			(
				tdf,
				"cmptAv(" + df.name() + ')',
				df.dimensions()
			);

		cmptAv(CmptAv().field(), df.field());

		reuseTmpDimensionedField<cmptType, Type, GeoMesh>::clear(tdf);

		return CmptAv;
	}

#define UNARY_REDUCTION_FUNCTION(returnType, func, dfunc)                     \
                                                                              \
template<class Type, class GeoMesh>                                           \
dimensioned<returnType> func                                                  \
(                                                                             \
    const DimensionedField<Type, GeoMesh>& df                                 \
)                                                                             \
{                                                                             \
    return dimensioned<Type>                                                  \
    (                                                                         \
        #func "(" + df.name() + ')',                                          \
        df.dimensions(),                                                      \
        dfunc(df.field())                                                     \
    );                                                                        \
}                                                                             \
                                                                              \
template<class Type, class GeoMesh>                                           \
dimensioned<returnType> func                                                  \
(                                                                             \
    const tmp<DimensionedField<Type, GeoMesh> >& tdf1                         \
)                                                                             \
{                                                                             \
    dimensioned<returnType> res = func(tdf1());                               \
    tdf1.clear();                                                             \
    return res;                                                               \
}

	template <class Type, class GeoMesh>
	dimensioned<Type> max(const DimensionedField<Type, GeoMesh>& df)
	{
		return dimensioned<Type>("max" "(" + df.name() + ')', df.dimensions(), gMax(df.field()));
	}

	template <class Type, class GeoMesh>
	dimensioned<Type> max(const tmp<DimensionedField<Type, GeoMesh>>& tdf1)
	{
		dimensioned<Type> res = max(tdf1());
		tdf1.clear();
		return res;
	}
		
	template <class Type, class GeoMesh>
	dimensioned<Type> min(const DimensionedField<Type, GeoMesh>& df)
	{
		return dimensioned<Type>("min" "(" + df.name() + ')', df.dimensions(), gMin(df.field()));
	}

	template <class Type, class GeoMesh>
	dimensioned<Type> min(const tmp<DimensionedField<Type, GeoMesh>>& tdf1)
	{
		dimensioned<Type> res = min(tdf1());
		tdf1.clear();
		return res;
	}
		
	template <class Type, class GeoMesh>
	dimensioned<Type> sum(const DimensionedField<Type, GeoMesh>& df)
	{
		return dimensioned<Type>("sum" "(" + df.name() + ')', df.dimensions(), gSum(df.field()));
	}

	template <class Type, class GeoMesh>
	dimensioned<Type> sum(const tmp<DimensionedField<Type, GeoMesh>>& tdf1)
	{
		dimensioned<Type> res = sum(tdf1());
		tdf1.clear();
		return res;
	}
		
	template <class Type, class GeoMesh>
	dimensioned<scalar> sumMag(const DimensionedField<Type, GeoMesh>& df)
	{
		return dimensioned<Type>("sumMag" "(" + df.name() + ')', df.dimensions(), gSumMag(df.field()));
	}

	template <class Type, class GeoMesh>
	dimensioned<scalar> sumMag(const tmp<DimensionedField<Type, GeoMesh>>& tdf1)
	{
		dimensioned<scalar> res = sumMag(tdf1());
		tdf1.clear();
		return res;
	}
		
	template <class Type, class GeoMesh>
	dimensioned<Type> average(const DimensionedField<Type, GeoMesh>& df)
	{
		return dimensioned<Type>("average" "(" + df.name() + ')', df.dimensions(), gAverage(df.field()));
	}

	template <class Type, class GeoMesh>
	dimensioned<Type> average(const tmp<DimensionedField<Type, GeoMesh>>& tdf1)
	{
		dimensioned<Type> res = average(tdf1());
		tdf1.clear();
		return res;
	}

#undef UNARY_REDUCTION_FUNCTION


		
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> max(const DimensionedField<Type, GeoMesh>& df1
	                                         , const DimensionedField<Type, GeoMesh>& df2)
	{
		tmp<DimensionedField<Type, GeoMesh>> tRes(new DimensionedField<Type, GeoMesh>(
			IOobject("max" "(" + df1.name() + ',' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, max(df1.dimensions(), df2.dimensions())));
		max(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> max(const DimensionedField<Type, GeoMesh>& df1
	                                         , const tmp<DimensionedField<Type, GeoMesh>>& tdf2)
	{
		const DimensionedField<Type, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<Type, GeoMesh>> tRes(reuseTmpDimensionedField<Type, Type, GeoMesh>::New(
			tdf2, "max" "(" + df1.name() + ',' + df2.name() + ')', max(df1.dimensions(), df2.dimensions())));
		max(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<Type, Type, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> max(const tmp<DimensionedField<Type, GeoMesh>>& tdf1
	                                         , const DimensionedField<Type, GeoMesh>& df2)
	{
		const DimensionedField<Type, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<Type, GeoMesh>> tRes(reuseTmpDimensionedField<Type, Type, GeoMesh>::New(
			tdf1, "max" "(" + df1.name() + ',' + df2.name() + ')', max(df1.dimensions(), df2.dimensions())));
		max(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<Type, Type, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> max(const tmp<DimensionedField<Type, GeoMesh>>& tdf1
	                                         , const tmp<DimensionedField<Type, GeoMesh>>& tdf2)
	{
		const DimensionedField<Type, GeoMesh>& df1 = tdf1();
		const DimensionedField<Type, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<Type, GeoMesh>> tRes(reuseTmpTmpDimensionedField<Type, Type, Type, Type, GeoMesh>::New(
			tdf1, tdf2, "max" "(" + df1.name() + ',' + df2.name() + ')', max(df1.dimensions(), df2.dimensions())));
		max(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<Type, Type, Type, Type, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}
		
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> min(const DimensionedField<Type, GeoMesh>& df1
	                                         , const DimensionedField<Type, GeoMesh>& df2)
	{
		tmp<DimensionedField<Type, GeoMesh>> tRes(new DimensionedField<Type, GeoMesh>(
			IOobject("min" "(" + df1.name() + ',' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, min(df1.dimensions(), df2.dimensions())));
		min(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> min(const DimensionedField<Type, GeoMesh>& df1
	                                         , const tmp<DimensionedField<Type, GeoMesh>>& tdf2)
	{
		const DimensionedField<Type, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<Type, GeoMesh>> tRes(reuseTmpDimensionedField<Type, Type, GeoMesh>::New(
			tdf2, "min" "(" + df1.name() + ',' + df2.name() + ')', min(df1.dimensions(), df2.dimensions())));
		min(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<Type, Type, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> min(const tmp<DimensionedField<Type, GeoMesh>>& tdf1
	                                         , const DimensionedField<Type, GeoMesh>& df2)
	{
		const DimensionedField<Type, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<Type, GeoMesh>> tRes(reuseTmpDimensionedField<Type, Type, GeoMesh>::New(
			tdf1, "min" "(" + df1.name() + ',' + df2.name() + ')', min(df1.dimensions(), df2.dimensions())));
		min(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<Type, Type, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> min(const tmp<DimensionedField<Type, GeoMesh>>& tdf1
	                                         , const tmp<DimensionedField<Type, GeoMesh>>& tdf2)
	{
		const DimensionedField<Type, GeoMesh>& df1 = tdf1();
		const DimensionedField<Type, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<Type, GeoMesh>> tRes(reuseTmpTmpDimensionedField<Type, Type, Type, Type, GeoMesh>::New(
			tdf1, tdf2, "min" "(" + df1.name() + ',' + df2.name() + ')', min(df1.dimensions(), df2.dimensions())));
		min(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<Type, Type, Type, Type, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}
		
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptMultiply(const DimensionedField<Type, GeoMesh>& df1
	                                                  , const DimensionedField<Type, GeoMesh>& df2)
	{
		tmp<DimensionedField<Type, GeoMesh>> tRes(new DimensionedField<Type, GeoMesh>(
			IOobject("cmptMultiply" "(" + df1.name() + ',' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, cmptMultiply(df1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptMultiply(const DimensionedField<Type, GeoMesh>& df1
	                                                  , const tmp<DimensionedField<Type, GeoMesh>>& tdf2)
	{
		const DimensionedField<Type, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<Type, GeoMesh>> tRes(reuseTmpDimensionedField<Type, Type, GeoMesh>::New(
			tdf2, "cmptMultiply" "(" + df1.name() + ',' + df2.name() + ')', cmptMultiply(df1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<Type, Type, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptMultiply(const tmp<DimensionedField<Type, GeoMesh>>& tdf1
	                                                  , const DimensionedField<Type, GeoMesh>& df2)
	{
		const DimensionedField<Type, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<Type, GeoMesh>> tRes(reuseTmpDimensionedField<Type, Type, GeoMesh>::New(
			tdf1, "cmptMultiply" "(" + df1.name() + ',' + df2.name() + ')', cmptMultiply(df1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<Type, Type, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptMultiply(const tmp<DimensionedField<Type, GeoMesh>>& tdf1
	                                                  , const tmp<DimensionedField<Type, GeoMesh>>& tdf2)
	{
		const DimensionedField<Type, GeoMesh>& df1 = tdf1();
		const DimensionedField<Type, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<Type, GeoMesh>> tRes(reuseTmpTmpDimensionedField<Type, Type, Type, Type, GeoMesh>::New(
			tdf1, tdf2, "cmptMultiply" "(" + df1.name() + ',' + df2.name() + ')'
			, cmptMultiply(df1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<Type, Type, Type, Type, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}
		
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptDivide(const DimensionedField<Type, GeoMesh>& df1
	                                                , const DimensionedField<Type, GeoMesh>& df2)
	{
		tmp<DimensionedField<Type, GeoMesh>> tRes(new DimensionedField<Type, GeoMesh>(
			IOobject("cmptDivide" "(" + df1.name() + ',' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, cmptDivide(df1.dimensions(), df2.dimensions())));
		cmptDivide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptDivide(const DimensionedField<Type, GeoMesh>& df1
	                                                , const tmp<DimensionedField<Type, GeoMesh>>& tdf2)
	{
		const DimensionedField<Type, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<Type, GeoMesh>> tRes(reuseTmpDimensionedField<Type, Type, GeoMesh>::New(
			tdf2, "cmptDivide" "(" + df1.name() + ',' + df2.name() + ')', cmptDivide(df1.dimensions(), df2.dimensions())));
		cmptDivide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<Type, Type, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptDivide(const tmp<DimensionedField<Type, GeoMesh>>& tdf1
	                                                , const DimensionedField<Type, GeoMesh>& df2)
	{
		const DimensionedField<Type, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<Type, GeoMesh>> tRes(reuseTmpDimensionedField<Type, Type, GeoMesh>::New(
			tdf1, "cmptDivide" "(" + df1.name() + ',' + df2.name() + ')', cmptDivide(df1.dimensions(), df2.dimensions())));
		cmptDivide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<Type, Type, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptDivide(const tmp<DimensionedField<Type, GeoMesh>>& tdf1
	                                                , const tmp<DimensionedField<Type, GeoMesh>>& tdf2)
	{
		const DimensionedField<Type, GeoMesh>& df1 = tdf1();
		const DimensionedField<Type, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<Type, GeoMesh>> tRes(reuseTmpTmpDimensionedField<Type, Type, Type, Type, GeoMesh>::New(
			tdf1, tdf2, "cmptDivide" "(" + df1.name() + ',' + df2.name() + ')', cmptDivide(df1.dimensions(), df2.dimensions())));
		cmptDivide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<Type, Type, Type, Type, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

		
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> max(const dimensioned<Type>& dt1, const DimensionedField<Type, GeoMesh>& df2)
	{
		tmp<DimensionedField<Type, GeoMesh>> tRes(new DimensionedField<Type, GeoMesh>(
			IOobject("max" "(" + dt1.name() + ',' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, max(dt1.dimensions(), df2.dimensions())));
		max(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> max(const Type& t1, const DimensionedField<Type, GeoMesh>& df2)
	{
		return max(dimensioned<Type>(t1), df2);
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> max(const dimensioned<Type>& dt1
	                                         , const tmp<DimensionedField<Type, GeoMesh>>& tdf2)
	{
		const DimensionedField<Type, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<Type, GeoMesh>> tRes(reuseTmpDimensionedField<Type, Type, GeoMesh>::New(
			tdf2, "max" "(" + dt1.name() + ',' + df2.name() + ')', max(dt1.dimensions(), df2.dimensions())));
		max(tRes().field(), dt1.value(), df2.field());
		reuseTmpDimensionedField<Type, Type, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> max(const Type& t1, const tmp<DimensionedField<Type, GeoMesh>>& tdf2)
	{
		return max(dimensioned<Type>(t1), tdf2);
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> max(const DimensionedField<Type, GeoMesh>& df1, const dimensioned<Type>& dt2)
	{
		tmp<DimensionedField<Type, GeoMesh>> tRes(new DimensionedField<Type, GeoMesh>(
			IOobject("max" "(" + df1.name() + ',' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, max(df1.dimensions(), dt2.dimensions())));
		max(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> max(const DimensionedField<Type, GeoMesh>& df1, const Type& t2)
	{
		return max(df1, dimensioned<Type>(t2));
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> max(const tmp<DimensionedField<Type, GeoMesh>>& tdf1
	                                         , const dimensioned<Type>& dt2)
	{
		const DimensionedField<Type, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<Type, GeoMesh>> tRes(reuseTmpDimensionedField<Type, Type, GeoMesh>::New(
			tdf1, "max" "(" + df1.name() + ',' + dt2.name() + ')', max(df1.dimensions(), dt2.dimensions())));
		max(tRes().field(), df1.field(), dt2.value());
		reuseTmpDimensionedField<Type, Type, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> max(const tmp<DimensionedField<Type, GeoMesh>>& tdf1, const Type& t2)
	{
		return max(tdf1, dimensioned<Type>(t2));
	}
		
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> min(const dimensioned<Type>& dt1, const DimensionedField<Type, GeoMesh>& df2)
	{
		tmp<DimensionedField<Type, GeoMesh>> tRes(new DimensionedField<Type, GeoMesh>(
			IOobject("min" "(" + dt1.name() + ',' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, min(dt1.dimensions(), df2.dimensions())));
		min(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> min(const Type& t1, const DimensionedField<Type, GeoMesh>& df2)
	{
		return min(dimensioned<Type>(t1), df2);
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> min(const dimensioned<Type>& dt1
	                                         , const tmp<DimensionedField<Type, GeoMesh>>& tdf2)
	{
		const DimensionedField<Type, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<Type, GeoMesh>> tRes(reuseTmpDimensionedField<Type, Type, GeoMesh>::New(
			tdf2, "min" "(" + dt1.name() + ',' + df2.name() + ')', min(dt1.dimensions(), df2.dimensions())));
		min(tRes().field(), dt1.value(), df2.field());
		reuseTmpDimensionedField<Type, Type, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> min(const Type& t1, const tmp<DimensionedField<Type, GeoMesh>>& tdf2)
	{
		return min(dimensioned<Type>(t1), tdf2);
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> min(const DimensionedField<Type, GeoMesh>& df1, const dimensioned<Type>& dt2)
	{
		tmp<DimensionedField<Type, GeoMesh>> tRes(new DimensionedField<Type, GeoMesh>(
			IOobject("min" "(" + df1.name() + ',' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, min(df1.dimensions(), dt2.dimensions())));
		min(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> min(const DimensionedField<Type, GeoMesh>& df1, const Type& t2)
	{
		return min(df1, dimensioned<Type>(t2));
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> min(const tmp<DimensionedField<Type, GeoMesh>>& tdf1
	                                         , const dimensioned<Type>& dt2)
	{
		const DimensionedField<Type, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<Type, GeoMesh>> tRes(reuseTmpDimensionedField<Type, Type, GeoMesh>::New(
			tdf1, "min" "(" + df1.name() + ',' + dt2.name() + ')', min(df1.dimensions(), dt2.dimensions())));
		min(tRes().field(), df1.field(), dt2.value());
		reuseTmpDimensionedField<Type, Type, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> min(const tmp<DimensionedField<Type, GeoMesh>>& tdf1, const Type& t2)
	{
		return min(tdf1, dimensioned<Type>(t2));
	}
		
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptMultiply(const dimensioned<Type>& dt1
	                                                  , const DimensionedField<Type, GeoMesh>& df2)
	{
		tmp<DimensionedField<Type, GeoMesh>> tRes(new DimensionedField<Type, GeoMesh>(
			IOobject("cmptMultiply" "(" + dt1.name() + ',' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, cmptMultiply(dt1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptMultiply(const Type& t1, const DimensionedField<Type, GeoMesh>& df2)
	{
		return cmptMultiply(dimensioned<Type>(t1), df2);
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptMultiply(const dimensioned<Type>& dt1
	                                                  , const tmp<DimensionedField<Type, GeoMesh>>& tdf2)
	{
		const DimensionedField<Type, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<Type, GeoMesh>> tRes(reuseTmpDimensionedField<Type, Type, GeoMesh>::New(
			tdf2, "cmptMultiply" "(" + dt1.name() + ',' + df2.name() + ')', cmptMultiply(dt1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), dt1.value(), df2.field());
		reuseTmpDimensionedField<Type, Type, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptMultiply(const Type& t1, const tmp<DimensionedField<Type, GeoMesh>>& tdf2)
	{
		return cmptMultiply(dimensioned<Type>(t1), tdf2);
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptMultiply(const DimensionedField<Type, GeoMesh>& df1
	                                                  , const dimensioned<Type>& dt2)
	{
		tmp<DimensionedField<Type, GeoMesh>> tRes(new DimensionedField<Type, GeoMesh>(
			IOobject("cmptMultiply" "(" + df1.name() + ',' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, cmptMultiply(df1.dimensions(), dt2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptMultiply(const DimensionedField<Type, GeoMesh>& df1, const Type& t2)
	{
		return cmptMultiply(df1, dimensioned<Type>(t2));
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptMultiply(const tmp<DimensionedField<Type, GeoMesh>>& tdf1
	                                                  , const dimensioned<Type>& dt2)
	{
		const DimensionedField<Type, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<Type, GeoMesh>> tRes(reuseTmpDimensionedField<Type, Type, GeoMesh>::New(
			tdf1, "cmptMultiply" "(" + df1.name() + ',' + dt2.name() + ')', cmptMultiply(df1.dimensions(), dt2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), dt2.value());
		reuseTmpDimensionedField<Type, Type, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptMultiply(const tmp<DimensionedField<Type, GeoMesh>>& tdf1, const Type& t2)
	{
		return cmptMultiply(tdf1, dimensioned<Type>(t2));
	}
		
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptDivide(const dimensioned<Type>& dt1
	                                                , const DimensionedField<Type, GeoMesh>& df2)
	{
		tmp<DimensionedField<Type, GeoMesh>> tRes(new DimensionedField<Type, GeoMesh>(
			IOobject("cmptDivide" "(" + dt1.name() + ',' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, cmptDivide(dt1.dimensions(), df2.dimensions())));
		cmptDivide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptDivide(const Type& t1, const DimensionedField<Type, GeoMesh>& df2)
	{
		return cmptDivide(dimensioned<Type>(t1), df2);
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptDivide(const dimensioned<Type>& dt1
	                                                , const tmp<DimensionedField<Type, GeoMesh>>& tdf2)
	{
		const DimensionedField<Type, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<Type, GeoMesh>> tRes(reuseTmpDimensionedField<Type, Type, GeoMesh>::New(
			tdf2, "cmptDivide" "(" + dt1.name() + ',' + df2.name() + ')', cmptDivide(dt1.dimensions(), df2.dimensions())));
		cmptDivide(tRes().field(), dt1.value(), df2.field());
		reuseTmpDimensionedField<Type, Type, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptDivide(const Type& t1, const tmp<DimensionedField<Type, GeoMesh>>& tdf2)
	{
		return cmptDivide(dimensioned<Type>(t1), tdf2);
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptDivide(const DimensionedField<Type, GeoMesh>& df1
	                                                , const dimensioned<Type>& dt2)
	{
		tmp<DimensionedField<Type, GeoMesh>> tRes(new DimensionedField<Type, GeoMesh>(
			IOobject("cmptDivide" "(" + df1.name() + ',' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, cmptDivide(df1.dimensions(), dt2.dimensions())));
		cmptDivide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptDivide(const DimensionedField<Type, GeoMesh>& df1, const Type& t2)
	{
		return cmptDivide(df1, dimensioned<Type>(t2));
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptDivide(const tmp<DimensionedField<Type, GeoMesh>>& tdf1
	                                                , const dimensioned<Type>& dt2)
	{
		const DimensionedField<Type, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<Type, GeoMesh>> tRes(reuseTmpDimensionedField<Type, Type, GeoMesh>::New(
			tdf1, "cmptDivide" "(" + df1.name() + ',' + dt2.name() + ')', cmptDivide(df1.dimensions(), dt2.dimensions())));
		cmptDivide(tRes().field(), df1.field(), dt2.value());
		reuseTmpDimensionedField<Type, Type, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptDivide(const tmp<DimensionedField<Type, GeoMesh>>& tdf1, const Type& t2)
	{
		return cmptDivide(tdf1, dimensioned<Type>(t2));
	}


		// * * * * * * * * * * * * * * * Global operators  * * * * * * * * * * * * * //

		
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator -(const DimensionedField<Type, GeoMesh>& df1)
	{
		tmp<DimensionedField<Type, GeoMesh>> tRes(new DimensionedField<Type, GeoMesh>(
			IOobject("-" + df1.name(), df1.instance(), df1.db()), df1.mesh(), transform(df1.dimensions())));
		tnbLib::negate(tRes().field(), df1.field());
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator -(const tmp<DimensionedField<Type, GeoMesh>>& tdf1)
	{
		const DimensionedField<Type, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<Type, GeoMesh>> tRes(
			reuseTmpDimensionedField<Type, Type, GeoMesh>::New(tdf1, "-" + df1.name(), transform(df1.dimensions())));
		tnbLib::negate(tRes().field(), df1.field());
		reuseTmpDimensionedField<Type, Type, GeoMesh>::clear(tdf1);
		return tRes;
	}

		
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator *(const DimensionedField<Type, GeoMesh>& df1
	                                                , const DimensionedField<scalar, GeoMesh>& df2)
	{
		tmp<DimensionedField<Type, GeoMesh>> tRes(new DimensionedField<Type, GeoMesh>(
			IOobject('(' + df1.name() + '*' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() * df2.dimensions()));
		tnbLib::multiply(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator *(const DimensionedField<Type, GeoMesh>& df1
	                                                , const tmp<DimensionedField<scalar, GeoMesh>>& tdf2)
	{
		const DimensionedField<scalar, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<Type, GeoMesh>> tRes(
			reuseTmpDimensionedField<Type, scalar, GeoMesh>::New(tdf2, '(' + df1.name() + '*' + df2.name() + ')'
			                                                     , df1.dimensions() * df2.dimensions()));
		tnbLib::multiply(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<Type, scalar, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator *(const tmp<DimensionedField<Type, GeoMesh>>& tdf1
	                                                , const DimensionedField<scalar, GeoMesh>& df2)
	{
		const DimensionedField<Type, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<Type, GeoMesh>> tRes(
			reuseTmpDimensionedField<Type, Type, GeoMesh>::New(tdf1, '(' + df1.name() + '*' + df2.name() + ')'
			                                                   , df1.dimensions() * df2.dimensions()));
		tnbLib::multiply(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<Type, Type, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator *(const tmp<DimensionedField<Type, GeoMesh>>& tdf1
	                                                , const tmp<DimensionedField<scalar, GeoMesh>>& tdf2)
	{
		const DimensionedField<Type, GeoMesh>& df1 = tdf1();
		const DimensionedField<scalar, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<Type, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<Type, Type, Type, scalar, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '*' + df2.name() + ')', df1.dimensions() * df2.dimensions()));
		tnbLib::multiply(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<Type, Type, Type, scalar, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}
		
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator *(const DimensionedField<scalar, GeoMesh>& df1
	                                                , const DimensionedField<Type, GeoMesh>& df2)
	{
		tmp<DimensionedField<Type, GeoMesh>> tRes(new DimensionedField<Type, GeoMesh>(
			IOobject('(' + df1.name() + '*' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() * df2.dimensions()));
		tnbLib::multiply(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator *(const DimensionedField<scalar, GeoMesh>& df1
	                                                , const tmp<DimensionedField<Type, GeoMesh>>& tdf2)
	{
		const DimensionedField<Type, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<Type, GeoMesh>> tRes(
			reuseTmpDimensionedField<Type, Type, GeoMesh>::New(tdf2, '(' + df1.name() + '*' + df2.name() + ')'
			                                                   , df1.dimensions() * df2.dimensions()));
		tnbLib::multiply(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<Type, Type, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator *(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                , const DimensionedField<Type, GeoMesh>& df2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<Type, GeoMesh>> tRes(
			reuseTmpDimensionedField<Type, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '*' + df2.name() + ')'
			                                                     , df1.dimensions() * df2.dimensions()));
		tnbLib::multiply(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<Type, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator *(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                , const tmp<DimensionedField<Type, GeoMesh>>& tdf2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		const DimensionedField<Type, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<Type, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<Type, scalar, scalar, Type, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '*' + df2.name() + ')', df1.dimensions() * df2.dimensions()));
		tnbLib::multiply(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<Type, scalar, scalar, Type, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}
		
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator /(const DimensionedField<Type, GeoMesh>& df1
	                                                , const DimensionedField<scalar, GeoMesh>& df2)
	{
		tmp<DimensionedField<Type, GeoMesh>> tRes(new DimensionedField<Type, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator /(const DimensionedField<Type, GeoMesh>& df1
	                                                , const tmp<DimensionedField<scalar, GeoMesh>>& tdf2)
	{
		const DimensionedField<scalar, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<Type, GeoMesh>> tRes(
			reuseTmpDimensionedField<Type, scalar, GeoMesh>::New(tdf2, '(' + df1.name() + '|' + df2.name() + ')'
			                                                     , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<Type, scalar, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator /(const tmp<DimensionedField<Type, GeoMesh>>& tdf1
	                                                , const DimensionedField<scalar, GeoMesh>& df2)
	{
		const DimensionedField<Type, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<Type, GeoMesh>> tRes(
			reuseTmpDimensionedField<Type, Type, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + df2.name() + ')'
			                                                   , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<Type, Type, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator /(const tmp<DimensionedField<Type, GeoMesh>>& tdf1
	                                                , const tmp<DimensionedField<scalar, GeoMesh>>& tdf2)
	{
		const DimensionedField<Type, GeoMesh>& df1 = tdf1();
		const DimensionedField<scalar, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<Type, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<Type, Type, Type, scalar, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<Type, Type, Type, scalar, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

		
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator *(const dimensioned<scalar>& dt1
	                                                , const DimensionedField<Type, GeoMesh>& df2)
	{
		tmp<DimensionedField<Type, GeoMesh>> tRes(new DimensionedField<Type, GeoMesh>(
			IOobject('(' + dt1.name() + '*' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() * df2.dimensions()));
		tnbLib::multiply(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator *(const scalar& t1, const DimensionedField<Type, GeoMesh>& df2)
	{
		return dimensioned<scalar>(t1) * df2;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator *(const dimensioned<scalar>& dt1
	                                                , const tmp<DimensionedField<Type, GeoMesh>>& tdf2)
	{
		const DimensionedField<Type, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<Type, GeoMesh>> tRes(
			reuseTmpDimensionedField<Type, Type, GeoMesh>::New(tdf2, '(' + dt1.name() + '*' + df2.name() + ')'
			                                                   , dt1.dimensions() * df2.dimensions()));
		tnbLib::multiply(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<Type, Type, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator *(const scalar& t1, const tmp<DimensionedField<Type, GeoMesh>>& tdf2)
	{
		return dimensioned<scalar>(t1) * tdf2;
	}
		
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator *(const DimensionedField<Type, GeoMesh>& df1
	                                                , const dimensioned<scalar>& dt2)
	{
		tmp<DimensionedField<Type, GeoMesh>> tRes(new DimensionedField<Type, GeoMesh>(
			IOobject('(' + df1.name() + '*' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() * dt2.dimensions()));
		tnbLib::multiply(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator *(const DimensionedField<Type, GeoMesh>& df1, const scalar& t2)
	{
		return df1 * dimensioned<scalar>(t2);
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator *(const tmp<DimensionedField<Type, GeoMesh>>& tdf1
	                                                , const dimensioned<scalar>& dt2)
	{
		const DimensionedField<Type, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<Type, GeoMesh>> tRes(
			reuseTmpDimensionedField<Type, Type, GeoMesh>::New(tdf1, '(' + df1.name() + '*' + dt2.name() + ')'
			                                                   , df1.dimensions() * dt2.dimensions()));
		tnbLib::multiply(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<Type, Type, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator *(const tmp<DimensionedField<Type, GeoMesh>>& tdf1, const scalar& t2)
	{
		return tdf1 * dimensioned<scalar>(t2);
	}

		
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator /(const DimensionedField<Type, GeoMesh>& df1
	                                                , const dimensioned<scalar>& dt2)
	{
		tmp<DimensionedField<Type, GeoMesh>> tRes(new DimensionedField<Type, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator /(const DimensionedField<Type, GeoMesh>& df1, const scalar& t2)
	{
		return df1 / dimensioned<scalar>(t2);
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator /(const tmp<DimensionedField<Type, GeoMesh>>& tdf1
	                                                , const dimensioned<scalar>& dt2)
	{
		const DimensionedField<Type, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<Type, GeoMesh>> tRes(
			reuseTmpDimensionedField<Type, Type, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + dt2.name() + ')'
			                                                   , df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<Type, Type, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator /(const tmp<DimensionedField<Type, GeoMesh>>& tdf1, const scalar& t2)
	{
		return tdf1 / dimensioned<scalar>(t2);
	}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define PRODUCT_OPERATOR(product, op, opFunc)                                 \
                                                                              \
template<class Type1, class Type2, class GeoMesh>                             \
tmp<DimensionedField<typename product<Type1, Type2>::type, GeoMesh> >         \
operator op                                                                   \
(                                                                             \
    const DimensionedField<Type1, GeoMesh>& df1,                              \
    const DimensionedField<Type2, GeoMesh>& df2                               \
)                                                                             \
{                                                                             \
    typedef typename product<Type1, Type2>::type productType;                 \
    tmp<DimensionedField<productType, GeoMesh> > tRes                         \
    (                                                                         \
        new DimensionedField<productType, GeoMesh>                            \
        (                                                                     \
            IOobject                                                          \
            (                                                                 \
                '(' + df1.name() + #op + df2.name() + ')',                    \
                df1.instance(),                                               \
                df1.db()                                                      \
            ),                                                                \
            df1.mesh(),                                                       \
            df1.dimensions() op df2.dimensions()                              \
        )                                                                     \
    );                                                                        \
                                                                              \
    tnbLib::opFunc(tRes().field(), df1.field(), df2.field());                   \
                                                                              \
    return tRes;                                                              \
}                                                                             \
                                                                              \
template<class Type1, class Type2, class GeoMesh>                             \
tmp<DimensionedField<typename product<Type1, Type2>::type, GeoMesh> >         \
operator op                                                                   \
(                                                                             \
    const DimensionedField<Type1, GeoMesh>& df1,                              \
    const tmp<DimensionedField<Type2, GeoMesh> >& tdf2                        \
)                                                                             \
{                                                                             \
    typedef typename product<Type1, Type2>::type productType;                 \
                                                                              \
    const DimensionedField<Type2, GeoMesh>& df2 = tdf2();                     \
                                                                              \
    tmp<DimensionedField<productType, GeoMesh> > tRes =                       \
        reuseTmpDimensionedField<productType, Type2, GeoMesh>::New            \
        (                                                                     \
            tdf2,                                                             \
            '(' + df1.name() + #op + df2.name() + ')',                        \
            df1.dimensions() op df2.dimensions()                              \
        );                                                                    \
                                                                              \
    tnbLib::opFunc(tRes().field(), df1.field(), df2.field());                   \
                                                                              \
    reuseTmpDimensionedField<productType, Type2, GeoMesh>::clear(tdf2);       \
                                                                              \
    return tRes;                                                              \
}                                                                             \
                                                                              \
template<class Type1, class Type2, class GeoMesh>                             \
tmp<DimensionedField<typename product<Type1, Type2>::type, GeoMesh> >         \
operator op                                                                   \
(                                                                             \
    const tmp<DimensionedField<Type1, GeoMesh> >& tdf1,                       \
    const DimensionedField<Type2, GeoMesh>& df2                               \
)                                                                             \
{                                                                             \
    typedef typename product<Type1, Type2>::type productType;                 \
                                                                              \
    const DimensionedField<Type1, GeoMesh>& df1 = tdf1();                     \
                                                                              \
    tmp<DimensionedField<productType, GeoMesh> > tRes =                       \
        reuseTmpDimensionedField<productType, Type1, GeoMesh>::New            \
        (                                                                     \
            tdf1,                                                             \
            '(' + df1.name() + #op + df2.name() + ')',                        \
            df1.dimensions() op df2.dimensions()                              \
        );                                                                    \
                                                                              \
    tnbLib::opFunc(tRes().field(), df1.field(), df2.field());                   \
                                                                              \
    reuseTmpDimensionedField<productType, Type1, GeoMesh>::clear(tdf1);       \
                                                                              \
    return tRes;                                                              \
}                                                                             \
                                                                              \
template<class Type1, class Type2, class GeoMesh>                             \
tmp<DimensionedField<typename product<Type1, Type2>::type, GeoMesh> >         \
operator op                                                                   \
(                                                                             \
    const tmp<DimensionedField<Type1, GeoMesh> >& tdf1,                       \
    const tmp<DimensionedField<Type2, GeoMesh> >& tdf2                        \
)                                                                             \
{                                                                             \
    typedef typename product<Type1, Type2>::type productType;                 \
                                                                              \
    const DimensionedField<Type1, GeoMesh>& df1 = tdf1();                     \
    const DimensionedField<Type2, GeoMesh>& df2 = tdf2();                     \
                                                                              \
    tmp<DimensionedField<productType, GeoMesh> > tRes =                       \
        reuseTmpTmpDimensionedField                                           \
        <productType, Type1, Type1, Type2, GeoMesh>::New                      \
        (                                                                     \
            tdf1,                                                             \
            tdf2,                                                             \
            '(' + df1.name() + #op + df2.name() + ')',                        \
            df1.dimensions() op df2.dimensions()                              \
        );                                                                    \
                                                                              \
    tnbLib::opFunc(tRes().field(), df1.field(), df2.field());                   \
                                                                              \
    reuseTmpTmpDimensionedField                                               \
        <productType, Type1, Type1, Type2, GeoMesh>::clear(tdf1, tdf2);       \
                                                                              \
    return tRes;                                                              \
}                                                                             \
                                                                              \
template<class Form, class Type, class GeoMesh>                               \
tmp<DimensionedField<typename product<Type, Form>::type, GeoMesh> >           \
operator op                                                                   \
(                                                                             \
    const DimensionedField<Type, GeoMesh>& df1,                               \
    const dimensioned<Form>& dvs                                              \
)                                                                             \
{                                                                             \
    typedef typename product<Type, Form>::type productType;                   \
                                                                              \
    tmp<DimensionedField<productType, GeoMesh> > tRes                         \
    (                                                                         \
        new DimensionedField<productType, GeoMesh>                            \
        (                                                                     \
            IOobject                                                          \
            (                                                                 \
                '(' + df1.name() + #op + dvs.name() + ')',                    \
                df1.instance(),                                               \
                df1.db()                                                      \
            ),                                                                \
            df1.mesh(),                                                       \
            df1.dimensions() op dvs.dimensions()                              \
        )                                                                     \
    );                                                                        \
                                                                              \
    tnbLib::opFunc(tRes().field(), df1.field(), dvs.value());                   \
                                                                              \
    return tRes;                                                              \
}                                                                             \
                                                                              \
template<class Form, class Cmpt, int nCmpt, class Type, class GeoMesh>        \
tmp<DimensionedField<typename product<Form, Type>::type, GeoMesh> >           \
operator op                                                                   \
(                                                                             \
    const DimensionedField<Type, GeoMesh>& df1,                               \
    const VectorSpace<Form,Cmpt,nCmpt>& vs                                    \
)                                                                             \
{                                                                             \
    return df1 op dimensioned<Form>(static_cast<const Form&>(vs));            \
}                                                                             \
                                                                              \
                                                                              \
template<class Form, class Type, class GeoMesh>                               \
tmp<DimensionedField<typename product<Type, Form>::type, GeoMesh> >           \
operator op                                                                   \
(                                                                             \
    const tmp<DimensionedField<Type, GeoMesh> >& tdf1,                        \
    const dimensioned<Form>& dvs                                              \
)                                                                             \
{                                                                             \
    typedef typename product<Type, Form>::type productType;                   \
                                                                              \
    const DimensionedField<Type, GeoMesh>& df1 = tdf1();                      \
                                                                              \
    tmp<DimensionedField<productType, GeoMesh> > tRes =                       \
        reuseTmpDimensionedField<productType, Type, GeoMesh>::New             \
        (                                                                     \
            tdf1,                                                             \
            '(' + df1.name() + #op + dvs.name() + ')',                        \
            df1.dimensions() op dvs.dimensions()                              \
        );                                                                    \
                                                                              \
    tnbLib::opFunc(tRes().field(), df1.field(), dvs.value());                   \
                                                                              \
    reuseTmpDimensionedField<productType, Type, GeoMesh>::clear(tdf1);        \
                                                                              \
    return tRes;                                                              \
}                                                                             \
                                                                              \
template<class Form, class Cmpt, int nCmpt, class Type, class GeoMesh>        \
tmp<DimensionedField<typename product<Form, Type>::type, GeoMesh> >           \
operator op                                                                   \
(                                                                             \
    const tmp<DimensionedField<Type, GeoMesh> >& tdf1,                        \
    const VectorSpace<Form,Cmpt,nCmpt>& vs                                    \
)                                                                             \
{                                                                             \
    return tdf1 op dimensioned<Form>(static_cast<const Form&>(vs));           \
}                                                                             \
                                                                              \
                                                                              \
template<class Form, class Type, class GeoMesh>                               \
tmp<DimensionedField<typename product<Form, Type>::type, GeoMesh> >           \
operator op                                                                   \
(                                                                             \
    const dimensioned<Form>& dvs,                                             \
    const DimensionedField<Type, GeoMesh>& df1                                \
)                                                                             \
{                                                                             \
    typedef typename product<Form, Type>::type productType;                   \
    tmp<DimensionedField<productType, GeoMesh> > tRes                         \
    (                                                                         \
        new DimensionedField<productType, GeoMesh>                            \
        (                                                                     \
            IOobject                                                          \
            (                                                                 \
                '(' + dvs.name() + #op + df1.name() + ')',                    \
                df1.instance(),                                               \
                df1.db()                                                      \
            ),                                                                \
            df1.mesh(),                                                       \
            dvs.dimensions() op df1.dimensions()                              \
        )                                                                     \
    );                                                                        \
                                                                              \
    tnbLib::opFunc(tRes().field(), dvs.value(), df1.field());                   \
                                                                              \
    return tRes;                                                              \
}                                                                             \
                                                                              \
template<class Form, class Cmpt, int nCmpt, class Type, class GeoMesh>        \
tmp<DimensionedField<typename product<Form, Type>::type, GeoMesh> >           \
operator op                                                                   \
(                                                                             \
    const VectorSpace<Form,Cmpt,nCmpt>& vs,                                   \
    const DimensionedField<Type, GeoMesh>& df1                                \
)                                                                             \
{                                                                             \
    return dimensioned<Form>(static_cast<const Form&>(vs)) op df1;            \
}                                                                             \
                                                                              \
template<class Form, class Type, class GeoMesh>                               \
tmp<DimensionedField<typename product<Form, Type>::type, GeoMesh> >           \
operator op                                                                   \
(                                                                             \
    const dimensioned<Form>& dvs,                                             \
    const tmp<DimensionedField<Type, GeoMesh> >& tdf1                         \
)                                                                             \
{                                                                             \
    typedef typename product<Form, Type>::type productType;                   \
                                                                              \
    const DimensionedField<Type, GeoMesh>& df1 = tdf1();                      \
                                                                              \
    tmp<DimensionedField<productType, GeoMesh> > tRes =                       \
        reuseTmpDimensionedField<productType, Type, GeoMesh>::New             \
        (                                                                     \
            tdf1,                                                             \
            '(' + dvs.name() + #op + df1.name() + ')',                        \
            dvs.dimensions() op df1.dimensions()                              \
        );                                                                    \
                                                                              \
    tnbLib::opFunc(tRes().field(), dvs.value(), df1.field());                   \
                                                                              \
    reuseTmpDimensionedField<productType, Type, GeoMesh>::clear(tdf1);        \
                                                                              \
    return tRes;                                                              \
}                                                                             \
                                                                              \
template<class Form, class Cmpt, int nCmpt, class Type, class GeoMesh>        \
tmp<DimensionedField<typename product<Form, Type>::type, GeoMesh> >           \
operator op                                                                   \
(                                                                             \
    const VectorSpace<Form,Cmpt,nCmpt>& vs,                                   \
    const tmp<DimensionedField<Type, GeoMesh> >& tdf1                         \
)                                                                             \
{                                                                             \
    return dimensioned<Form>(static_cast<const Form&>(vs)) op tdf1;           \
}

		
	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Type1, Type2>::type, GeoMesh>> operator +(
		const DimensionedField<Type1, GeoMesh>& df1, const DimensionedField<Type2, GeoMesh>& df2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		tmp<DimensionedField<productType, GeoMesh>> tRes(new DimensionedField<productType, GeoMesh>(
			IOobject('(' + df1.name() + "+" + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Type1, Type2>::type, GeoMesh>> operator +(
		const DimensionedField<Type1, GeoMesh>& df1, const tmp<DimensionedField<Type2, GeoMesh>>& tdf2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		const DimensionedField<Type2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<productType, GeoMesh>> tRes = reuseTmpDimensionedField<productType, Type2, GeoMesh>::New(
			tdf2, '(' + df1.name() + "+" + df2.name() + ')', df1.dimensions() + df2.dimensions());
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<productType, Type2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Type1, Type2>::type, GeoMesh>> operator +(
		const tmp<DimensionedField<Type1, GeoMesh>>& tdf1, const DimensionedField<Type2, GeoMesh>& df2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		const DimensionedField<Type1, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<productType, GeoMesh>> tRes = reuseTmpDimensionedField<productType, Type1, GeoMesh>::New(
			tdf1, '(' + df1.name() + "+" + df2.name() + ')', df1.dimensions() + df2.dimensions());
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<productType, Type1, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Type1, Type2>::type, GeoMesh>> operator +(
		const tmp<DimensionedField<Type1, GeoMesh>>& tdf1, const tmp<DimensionedField<Type2, GeoMesh>>& tdf2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		const DimensionedField<Type1, GeoMesh>& df1 = tdf1();
		const DimensionedField<Type2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<productType, GeoMesh>> tRes = reuseTmpTmpDimensionedField<
			productType, Type1, Type1, Type2, GeoMesh>::New(tdf1, tdf2, '(' + df1.name() + "+" + df2.name() + ')'
			                                                , df1.dimensions() + df2.dimensions());
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<productType, Type1, Type1, Type2, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Type, Form>::type, GeoMesh>> operator +(
		const DimensionedField<Type, GeoMesh>& df1, const dimensioned<Form>& dvs)
	{
		typedef typename typeOfSum<Type, Form>::type productType;
		tmp<DimensionedField<productType, GeoMesh>> tRes(new DimensionedField<productType, GeoMesh>(
			IOobject('(' + df1.name() + "+" + dvs.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + dvs.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), dvs.value());
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Form, Type>::type, GeoMesh>> operator +(
		const DimensionedField<Type, GeoMesh>& df1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return df1 + dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Type, Form>::type, GeoMesh>> operator +(
		const tmp<DimensionedField<Type, GeoMesh>>& tdf1, const dimensioned<Form>& dvs)
	{
		typedef typename typeOfSum<Type, Form>::type productType;
		const DimensionedField<Type, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<productType, GeoMesh>> tRes = reuseTmpDimensionedField<productType, Type, GeoMesh>::New(
			tdf1, '(' + df1.name() + "+" + dvs.name() + ')', df1.dimensions() + dvs.dimensions());
		tnbLib::add(tRes().field(), df1.field(), dvs.value());
		reuseTmpDimensionedField<productType, Type, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Form, Type>::type, GeoMesh>> operator +(
		const tmp<DimensionedField<Type, GeoMesh>>& tdf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return tdf1 + dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Form, Type>::type, GeoMesh>> operator +(
		const dimensioned<Form>& dvs, const DimensionedField<Type, GeoMesh>& df1)
	{
		typedef typename typeOfSum<Form, Type>::type productType;
		tmp<DimensionedField<productType, GeoMesh>> tRes(new DimensionedField<productType, GeoMesh>(
			IOobject('(' + dvs.name() + "+" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, dvs.dimensions() + df1.dimensions()));
		tnbLib::add(tRes().field(), dvs.value(), df1.field());
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Form, Type>::type, GeoMesh>> operator +(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const DimensionedField<Type, GeoMesh>& df1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) + df1;
	}

	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Form, Type>::type, GeoMesh>> operator +(
		const dimensioned<Form>& dvs, const tmp<DimensionedField<Type, GeoMesh>>& tdf1)
	{
		typedef typename typeOfSum<Form, Type>::type productType;
		const DimensionedField<Type, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<productType, GeoMesh>> tRes = reuseTmpDimensionedField<productType, Type, GeoMesh>::New(
			tdf1, '(' + dvs.name() + "+" + df1.name() + ')', dvs.dimensions() + df1.dimensions());
		tnbLib::add(tRes().field(), dvs.value(), df1.field());
		reuseTmpDimensionedField<productType, Type, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Form, Type>::type, GeoMesh>> operator +(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<DimensionedField<Type, GeoMesh>>& tdf1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) + tdf1;
	}
		
	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Type1, Type2>::type, GeoMesh>> operator -(
		const DimensionedField<Type1, GeoMesh>& df1, const DimensionedField<Type2, GeoMesh>& df2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		tmp<DimensionedField<productType, GeoMesh>> tRes(new DimensionedField<productType, GeoMesh>(
			IOobject('(' + df1.name() + "-" + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Type1, Type2>::type, GeoMesh>> operator -(
		const DimensionedField<Type1, GeoMesh>& df1, const tmp<DimensionedField<Type2, GeoMesh>>& tdf2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		const DimensionedField<Type2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<productType, GeoMesh>> tRes = reuseTmpDimensionedField<productType, Type2, GeoMesh>::New(
			tdf2, '(' + df1.name() + "-" + df2.name() + ')', df1.dimensions() - df2.dimensions());
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<productType, Type2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Type1, Type2>::type, GeoMesh>> operator -(
		const tmp<DimensionedField<Type1, GeoMesh>>& tdf1, const DimensionedField<Type2, GeoMesh>& df2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		const DimensionedField<Type1, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<productType, GeoMesh>> tRes = reuseTmpDimensionedField<productType, Type1, GeoMesh>::New(
			tdf1, '(' + df1.name() + "-" + df2.name() + ')', df1.dimensions() - df2.dimensions());
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<productType, Type1, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Type1, Type2>::type, GeoMesh>> operator -(
		const tmp<DimensionedField<Type1, GeoMesh>>& tdf1, const tmp<DimensionedField<Type2, GeoMesh>>& tdf2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		const DimensionedField<Type1, GeoMesh>& df1 = tdf1();
		const DimensionedField<Type2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<productType, GeoMesh>> tRes = reuseTmpTmpDimensionedField<
			productType, Type1, Type1, Type2, GeoMesh>::New(tdf1, tdf2, '(' + df1.name() + "-" + df2.name() + ')'
			                                                , df1.dimensions() - df2.dimensions());
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<productType, Type1, Type1, Type2, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Type, Form>::type, GeoMesh>> operator -(
		const DimensionedField<Type, GeoMesh>& df1, const dimensioned<Form>& dvs)
	{
		typedef typename typeOfSum<Type, Form>::type productType;
		tmp<DimensionedField<productType, GeoMesh>> tRes(new DimensionedField<productType, GeoMesh>(
			IOobject('(' + df1.name() + "-" + dvs.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - dvs.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), dvs.value());
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Form, Type>::type, GeoMesh>> operator -(
		const DimensionedField<Type, GeoMesh>& df1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return df1 - dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Type, Form>::type, GeoMesh>> operator -(
		const tmp<DimensionedField<Type, GeoMesh>>& tdf1, const dimensioned<Form>& dvs)
	{
		typedef typename typeOfSum<Type, Form>::type productType;
		const DimensionedField<Type, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<productType, GeoMesh>> tRes = reuseTmpDimensionedField<productType, Type, GeoMesh>::New(
			tdf1, '(' + df1.name() + "-" + dvs.name() + ')', df1.dimensions() - dvs.dimensions());
		tnbLib::subtract(tRes().field(), df1.field(), dvs.value());
		reuseTmpDimensionedField<productType, Type, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Form, Type>::type, GeoMesh>> operator -(
		const tmp<DimensionedField<Type, GeoMesh>>& tdf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return tdf1 - dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Form, Type>::type, GeoMesh>> operator -(
		const dimensioned<Form>& dvs, const DimensionedField<Type, GeoMesh>& df1)
	{
		typedef typename typeOfSum<Form, Type>::type productType;
		tmp<DimensionedField<productType, GeoMesh>> tRes(new DimensionedField<productType, GeoMesh>(
			IOobject('(' + dvs.name() + "-" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, dvs.dimensions() - df1.dimensions()));
		tnbLib::subtract(tRes().field(), dvs.value(), df1.field());
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Form, Type>::type, GeoMesh>> operator -(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const DimensionedField<Type, GeoMesh>& df1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) - df1;
	}

	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Form, Type>::type, GeoMesh>> operator -(
		const dimensioned<Form>& dvs, const tmp<DimensionedField<Type, GeoMesh>>& tdf1)
	{
		typedef typename typeOfSum<Form, Type>::type productType;
		const DimensionedField<Type, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<productType, GeoMesh>> tRes = reuseTmpDimensionedField<productType, Type, GeoMesh>::New(
			tdf1, '(' + dvs.name() + "-" + df1.name() + ')', dvs.dimensions() - df1.dimensions());
		tnbLib::subtract(tRes().field(), dvs.value(), df1.field());
		reuseTmpDimensionedField<productType, Type, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Form, Type>::type, GeoMesh>> operator -(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<DimensionedField<Type, GeoMesh>>& tdf1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) - tdf1;
	}

		
	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename outerProduct<Type1, Type2>::type, GeoMesh>> operator *(
		const DimensionedField<Type1, GeoMesh>& df1, const DimensionedField<Type2, GeoMesh>& df2)
	{
		typedef typename outerProduct<Type1, Type2>::type productType;
		tmp<DimensionedField<productType, GeoMesh>> tRes(new DimensionedField<productType, GeoMesh>(
			IOobject('(' + df1.name() + "*" + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() * df2.dimensions()));
		tnbLib::outer(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename outerProduct<Type1, Type2>::type, GeoMesh>> operator *(
		const DimensionedField<Type1, GeoMesh>& df1, const tmp<DimensionedField<Type2, GeoMesh>>& tdf2)
	{
		typedef typename outerProduct<Type1, Type2>::type productType;
		const DimensionedField<Type2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<productType, GeoMesh>> tRes = reuseTmpDimensionedField<productType, Type2, GeoMesh>::New(
			tdf2, '(' + df1.name() + "*" + df2.name() + ')', df1.dimensions() * df2.dimensions());
		tnbLib::outer(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<productType, Type2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename outerProduct<Type1, Type2>::type, GeoMesh>> operator *(
		const tmp<DimensionedField<Type1, GeoMesh>>& tdf1, const DimensionedField<Type2, GeoMesh>& df2)
	{
		typedef typename outerProduct<Type1, Type2>::type productType;
		const DimensionedField<Type1, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<productType, GeoMesh>> tRes = reuseTmpDimensionedField<productType, Type1, GeoMesh>::New(
			tdf1, '(' + df1.name() + "*" + df2.name() + ')', df1.dimensions() * df2.dimensions());
		tnbLib::outer(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<productType, Type1, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename outerProduct<Type1, Type2>::type, GeoMesh>> operator *(
		const tmp<DimensionedField<Type1, GeoMesh>>& tdf1, const tmp<DimensionedField<Type2, GeoMesh>>& tdf2)
	{
		typedef typename outerProduct<Type1, Type2>::type productType;
		const DimensionedField<Type1, GeoMesh>& df1 = tdf1();
		const DimensionedField<Type2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<productType, GeoMesh>> tRes = reuseTmpTmpDimensionedField<
			productType, Type1, Type1, Type2, GeoMesh>::New(tdf1, tdf2, '(' + df1.name() + "*" + df2.name() + ')'
			                                                , df1.dimensions() * df2.dimensions());
		tnbLib::outer(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<productType, Type1, Type1, Type2, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename outerProduct<Type, Form>::type, GeoMesh>> operator *(
		const DimensionedField<Type, GeoMesh>& df1, const dimensioned<Form>& dvs)
	{
		typedef typename outerProduct<Type, Form>::type productType;
		tmp<DimensionedField<productType, GeoMesh>> tRes(new DimensionedField<productType, GeoMesh>(
			IOobject('(' + df1.name() + "*" + dvs.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() * dvs.dimensions()));
		tnbLib::outer(tRes().field(), df1.field(), dvs.value());
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename outerProduct<Form, Type>::type, GeoMesh>> operator *(
		const DimensionedField<Type, GeoMesh>& df1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return df1 * dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename outerProduct<Type, Form>::type, GeoMesh>> operator *(
		const tmp<DimensionedField<Type, GeoMesh>>& tdf1, const dimensioned<Form>& dvs)
	{
		typedef typename outerProduct<Type, Form>::type productType;
		const DimensionedField<Type, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<productType, GeoMesh>> tRes = reuseTmpDimensionedField<productType, Type, GeoMesh>::New(
			tdf1, '(' + df1.name() + "*" + dvs.name() + ')', df1.dimensions() * dvs.dimensions());
		tnbLib::outer(tRes().field(), df1.field(), dvs.value());
		reuseTmpDimensionedField<productType, Type, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename outerProduct<Form, Type>::type, GeoMesh>> operator *(
		const tmp<DimensionedField<Type, GeoMesh>>& tdf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return tdf1 * dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename outerProduct<Form, Type>::type, GeoMesh>> operator *(
		const dimensioned<Form>& dvs, const DimensionedField<Type, GeoMesh>& df1)
	{
		typedef typename outerProduct<Form, Type>::type productType;
		tmp<DimensionedField<productType, GeoMesh>> tRes(new DimensionedField<productType, GeoMesh>(
			IOobject('(' + dvs.name() + "*" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, dvs.dimensions() * df1.dimensions()));
		tnbLib::outer(tRes().field(), dvs.value(), df1.field());
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename outerProduct<Form, Type>::type, GeoMesh>> operator *(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const DimensionedField<Type, GeoMesh>& df1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) * df1;
	}

	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename outerProduct<Form, Type>::type, GeoMesh>> operator *(
		const dimensioned<Form>& dvs, const tmp<DimensionedField<Type, GeoMesh>>& tdf1)
	{
		typedef typename outerProduct<Form, Type>::type productType;
		const DimensionedField<Type, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<productType, GeoMesh>> tRes = reuseTmpDimensionedField<productType, Type, GeoMesh>::New(
			tdf1, '(' + dvs.name() + "*" + df1.name() + ')', dvs.dimensions() * df1.dimensions());
		tnbLib::outer(tRes().field(), dvs.value(), df1.field());
		reuseTmpDimensionedField<productType, Type, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename outerProduct<Form, Type>::type, GeoMesh>> operator *(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<DimensionedField<Type, GeoMesh>>& tdf1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) * tdf1;
	}
		
	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename crossProduct<Type1, Type2>::type, GeoMesh>> operator ^(
		const DimensionedField<Type1, GeoMesh>& df1, const DimensionedField<Type2, GeoMesh>& df2)
	{
		typedef typename crossProduct<Type1, Type2>::type productType;
		tmp<DimensionedField<productType, GeoMesh>> tRes(new DimensionedField<productType, GeoMesh>(
			IOobject('(' + df1.name() + "^" + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() ^ df2.dimensions()));
		tnbLib::cross(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename crossProduct<Type1, Type2>::type, GeoMesh>> operator ^(
		const DimensionedField<Type1, GeoMesh>& df1, const tmp<DimensionedField<Type2, GeoMesh>>& tdf2)
	{
		typedef typename crossProduct<Type1, Type2>::type productType;
		const DimensionedField<Type2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<productType, GeoMesh>> tRes = reuseTmpDimensionedField<productType, Type2, GeoMesh>::New(
			tdf2, '(' + df1.name() + "^" + df2.name() + ')', df1.dimensions() ^ df2.dimensions());
		tnbLib::cross(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<productType, Type2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename crossProduct<Type1, Type2>::type, GeoMesh>> operator ^(
		const tmp<DimensionedField<Type1, GeoMesh>>& tdf1, const DimensionedField<Type2, GeoMesh>& df2)
	{
		typedef typename crossProduct<Type1, Type2>::type productType;
		const DimensionedField<Type1, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<productType, GeoMesh>> tRes = reuseTmpDimensionedField<productType, Type1, GeoMesh>::New(
			tdf1, '(' + df1.name() + "^" + df2.name() + ')', df1.dimensions() ^ df2.dimensions());
		tnbLib::cross(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<productType, Type1, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename crossProduct<Type1, Type2>::type, GeoMesh>> operator ^(
		const tmp<DimensionedField<Type1, GeoMesh>>& tdf1, const tmp<DimensionedField<Type2, GeoMesh>>& tdf2)
	{
		typedef typename crossProduct<Type1, Type2>::type productType;
		const DimensionedField<Type1, GeoMesh>& df1 = tdf1();
		const DimensionedField<Type2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<productType, GeoMesh>> tRes = reuseTmpTmpDimensionedField<
			productType, Type1, Type1, Type2, GeoMesh>::New(tdf1, tdf2, '(' + df1.name() + "^" + df2.name() + ')'
			                                                , df1.dimensions() ^ df2.dimensions());
		tnbLib::cross(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<productType, Type1, Type1, Type2, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename crossProduct<Type, Form>::type, GeoMesh>> operator ^(
		const DimensionedField<Type, GeoMesh>& df1, const dimensioned<Form>& dvs)
	{
		typedef typename crossProduct<Type, Form>::type productType;
		tmp<DimensionedField<productType, GeoMesh>> tRes(new DimensionedField<productType, GeoMesh>(
			IOobject('(' + df1.name() + "^" + dvs.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() ^ dvs.dimensions()));
		tnbLib::cross(tRes().field(), df1.field(), dvs.value());
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename crossProduct<Form, Type>::type, GeoMesh>> operator ^(
		const DimensionedField<Type, GeoMesh>& df1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return df1 ^ dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename crossProduct<Type, Form>::type, GeoMesh>> operator ^(
		const tmp<DimensionedField<Type, GeoMesh>>& tdf1, const dimensioned<Form>& dvs)
	{
		typedef typename crossProduct<Type, Form>::type productType;
		const DimensionedField<Type, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<productType, GeoMesh>> tRes = reuseTmpDimensionedField<productType, Type, GeoMesh>::New(
			tdf1, '(' + df1.name() + "^" + dvs.name() + ')', df1.dimensions() ^ dvs.dimensions());
		tnbLib::cross(tRes().field(), df1.field(), dvs.value());
		reuseTmpDimensionedField<productType, Type, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename crossProduct<Form, Type>::type, GeoMesh>> operator ^(
		const tmp<DimensionedField<Type, GeoMesh>>& tdf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return tdf1 ^ dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename crossProduct<Form, Type>::type, GeoMesh>> operator ^(
		const dimensioned<Form>& dvs, const DimensionedField<Type, GeoMesh>& df1)
	{
		typedef typename crossProduct<Form, Type>::type productType;
		tmp<DimensionedField<productType, GeoMesh>> tRes(new DimensionedField<productType, GeoMesh>(
			IOobject('(' + dvs.name() + "^" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, dvs.dimensions() ^ df1.dimensions()));
		tnbLib::cross(tRes().field(), dvs.value(), df1.field());
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename crossProduct<Form, Type>::type, GeoMesh>> operator ^(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const DimensionedField<Type, GeoMesh>& df1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) ^ df1;
	}

	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename crossProduct<Form, Type>::type, GeoMesh>> operator ^(
		const dimensioned<Form>& dvs, const tmp<DimensionedField<Type, GeoMesh>>& tdf1)
	{
		typedef typename crossProduct<Form, Type>::type productType;
		const DimensionedField<Type, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<productType, GeoMesh>> tRes = reuseTmpDimensionedField<productType, Type, GeoMesh>::New(
			tdf1, '(' + dvs.name() + "^" + df1.name() + ')', dvs.dimensions() ^ df1.dimensions());
		tnbLib::cross(tRes().field(), dvs.value(), df1.field());
		reuseTmpDimensionedField<productType, Type, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename crossProduct<Form, Type>::type, GeoMesh>> operator ^(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<DimensionedField<Type, GeoMesh>>& tdf1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) ^ tdf1;
	}
		
	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename innerProduct<Type1, Type2>::type, GeoMesh>> operator &(
		const DimensionedField<Type1, GeoMesh>& df1, const DimensionedField<Type2, GeoMesh>& df2)
	{
		typedef typename innerProduct<Type1, Type2>::type productType;
		tmp<DimensionedField<productType, GeoMesh>> tRes(new DimensionedField<productType, GeoMesh>(
			IOobject('(' + df1.name() + "&" + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() & df2.dimensions()));
		tnbLib::dot(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename innerProduct<Type1, Type2>::type, GeoMesh>> operator &(
		const DimensionedField<Type1, GeoMesh>& df1, const tmp<DimensionedField<Type2, GeoMesh>>& tdf2)
	{
		typedef typename innerProduct<Type1, Type2>::type productType;
		const DimensionedField<Type2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<productType, GeoMesh>> tRes = reuseTmpDimensionedField<productType, Type2, GeoMesh>::New(
			tdf2, '(' + df1.name() + "&" + df2.name() + ')', df1.dimensions() & df2.dimensions());
		tnbLib::dot(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<productType, Type2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename innerProduct<Type1, Type2>::type, GeoMesh>> operator &(
		const tmp<DimensionedField<Type1, GeoMesh>>& tdf1, const DimensionedField<Type2, GeoMesh>& df2)
	{
		typedef typename innerProduct<Type1, Type2>::type productType;
		const DimensionedField<Type1, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<productType, GeoMesh>> tRes = reuseTmpDimensionedField<productType, Type1, GeoMesh>::New(
			tdf1, '(' + df1.name() + "&" + df2.name() + ')', df1.dimensions() & df2.dimensions());
		tnbLib::dot(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<productType, Type1, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename innerProduct<Type1, Type2>::type, GeoMesh>> operator &(
		const tmp<DimensionedField<Type1, GeoMesh>>& tdf1, const tmp<DimensionedField<Type2, GeoMesh>>& tdf2)
	{
		typedef typename innerProduct<Type1, Type2>::type productType;
		const DimensionedField<Type1, GeoMesh>& df1 = tdf1();
		const DimensionedField<Type2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<productType, GeoMesh>> tRes = reuseTmpTmpDimensionedField<
			productType, Type1, Type1, Type2, GeoMesh>::New(tdf1, tdf2, '(' + df1.name() + "&" + df2.name() + ')'
			                                                , df1.dimensions() & df2.dimensions());
		tnbLib::dot(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<productType, Type1, Type1, Type2, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename innerProduct<Type, Form>::type, GeoMesh>> operator &(
		const DimensionedField<Type, GeoMesh>& df1, const dimensioned<Form>& dvs)
	{
		typedef typename innerProduct<Type, Form>::type productType;
		tmp<DimensionedField<productType, GeoMesh>> tRes(new DimensionedField<productType, GeoMesh>(
			IOobject('(' + df1.name() + "&" + dvs.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() & dvs.dimensions()));
		tnbLib::dot(tRes().field(), df1.field(), dvs.value());
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename innerProduct<Form, Type>::type, GeoMesh>> operator &(
		const DimensionedField<Type, GeoMesh>& df1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return df1 & dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename innerProduct<Type, Form>::type, GeoMesh>> operator &(
		const tmp<DimensionedField<Type, GeoMesh>>& tdf1, const dimensioned<Form>& dvs)
	{
		typedef typename innerProduct<Type, Form>::type productType;
		const DimensionedField<Type, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<productType, GeoMesh>> tRes = reuseTmpDimensionedField<productType, Type, GeoMesh>::New(
			tdf1, '(' + df1.name() + "&" + dvs.name() + ')', df1.dimensions() & dvs.dimensions());
		tnbLib::dot(tRes().field(), df1.field(), dvs.value());
		reuseTmpDimensionedField<productType, Type, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename innerProduct<Form, Type>::type, GeoMesh>> operator &(
		const tmp<DimensionedField<Type, GeoMesh>>& tdf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return tdf1 & dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename innerProduct<Form, Type>::type, GeoMesh>> operator &(
		const dimensioned<Form>& dvs, const DimensionedField<Type, GeoMesh>& df1)
	{
		typedef typename innerProduct<Form, Type>::type productType;
		tmp<DimensionedField<productType, GeoMesh>> tRes(new DimensionedField<productType, GeoMesh>(
			IOobject('(' + dvs.name() + "&" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, dvs.dimensions() & df1.dimensions()));
		tnbLib::dot(tRes().field(), dvs.value(), df1.field());
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename innerProduct<Form, Type>::type, GeoMesh>> operator &(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const DimensionedField<Type, GeoMesh>& df1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) & df1;
	}

	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename innerProduct<Form, Type>::type, GeoMesh>> operator &(
		const dimensioned<Form>& dvs, const tmp<DimensionedField<Type, GeoMesh>>& tdf1)
	{
		typedef typename innerProduct<Form, Type>::type productType;
		const DimensionedField<Type, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<productType, GeoMesh>> tRes = reuseTmpDimensionedField<productType, Type, GeoMesh>::New(
			tdf1, '(' + dvs.name() + "&" + df1.name() + ')', dvs.dimensions() & df1.dimensions());
		tnbLib::dot(tRes().field(), dvs.value(), df1.field());
		reuseTmpDimensionedField<productType, Type, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename innerProduct<Form, Type>::type, GeoMesh>> operator &(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<DimensionedField<Type, GeoMesh>>& tdf1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) & tdf1;
	}
		
	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename scalarProduct<Type1, Type2>::type, GeoMesh>> operator &&(
		const DimensionedField<Type1, GeoMesh>& df1, const DimensionedField<Type2, GeoMesh>& df2)
	{
		typedef typename scalarProduct<Type1, Type2>::type productType;
		tmp<DimensionedField<productType, GeoMesh>> tRes(new DimensionedField<productType, GeoMesh>(
			IOobject('(' + df1.name() + "&&" + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() && df2.dimensions()));
		tnbLib::dotdot(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename scalarProduct<Type1, Type2>::type, GeoMesh>> operator &&(
		const DimensionedField<Type1, GeoMesh>& df1, const tmp<DimensionedField<Type2, GeoMesh>>& tdf2)
	{
		typedef typename scalarProduct<Type1, Type2>::type productType;
		const DimensionedField<Type2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<productType, GeoMesh>> tRes = reuseTmpDimensionedField<productType, Type2, GeoMesh>::New(
			tdf2, '(' + df1.name() + "&&" + df2.name() + ')', df1.dimensions() && df2.dimensions());
		tnbLib::dotdot(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<productType, Type2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename scalarProduct<Type1, Type2>::type, GeoMesh>> operator &&(
		const tmp<DimensionedField<Type1, GeoMesh>>& tdf1, const DimensionedField<Type2, GeoMesh>& df2)
	{
		typedef typename scalarProduct<Type1, Type2>::type productType;
		const DimensionedField<Type1, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<productType, GeoMesh>> tRes = reuseTmpDimensionedField<productType, Type1, GeoMesh>::New(
			tdf1, '(' + df1.name() + "&&" + df2.name() + ')', df1.dimensions() && df2.dimensions());
		tnbLib::dotdot(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<productType, Type1, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename scalarProduct<Type1, Type2>::type, GeoMesh>> operator &&(
		const tmp<DimensionedField<Type1, GeoMesh>>& tdf1, const tmp<DimensionedField<Type2, GeoMesh>>& tdf2)
	{
		typedef typename scalarProduct<Type1, Type2>::type productType;
		const DimensionedField<Type1, GeoMesh>& df1 = tdf1();
		const DimensionedField<Type2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<productType, GeoMesh>> tRes = reuseTmpTmpDimensionedField<
			productType, Type1, Type1, Type2, GeoMesh>::New(tdf1, tdf2, '(' + df1.name() + "&&" + df2.name() + ')'
			                                                , df1.dimensions() && df2.dimensions());
		tnbLib::dotdot(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<productType, Type1, Type1, Type2, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename scalarProduct<Type, Form>::type, GeoMesh>> operator &&(
		const DimensionedField<Type, GeoMesh>& df1, const dimensioned<Form>& dvs)
	{
		typedef typename scalarProduct<Type, Form>::type productType;
		tmp<DimensionedField<productType, GeoMesh>> tRes(new DimensionedField<productType, GeoMesh>(
			IOobject('(' + df1.name() + "&&" + dvs.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() && dvs.dimensions()));
		tnbLib::dotdot(tRes().field(), df1.field(), dvs.value());
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename scalarProduct<Form, Type>::type, GeoMesh>> operator &&(
		const DimensionedField<Type, GeoMesh>& df1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return df1 && dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename scalarProduct<Type, Form>::type, GeoMesh>> operator &&(
		const tmp<DimensionedField<Type, GeoMesh>>& tdf1, const dimensioned<Form>& dvs)
	{
		typedef typename scalarProduct<Type, Form>::type productType;
		const DimensionedField<Type, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<productType, GeoMesh>> tRes = reuseTmpDimensionedField<productType, Type, GeoMesh>::New(
			tdf1, '(' + df1.name() + "&&" + dvs.name() + ')', df1.dimensions() && dvs.dimensions());
		tnbLib::dotdot(tRes().field(), df1.field(), dvs.value());
		reuseTmpDimensionedField<productType, Type, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename scalarProduct<Form, Type>::type, GeoMesh>> operator &&(
		const tmp<DimensionedField<Type, GeoMesh>>& tdf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return tdf1 && dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename scalarProduct<Form, Type>::type, GeoMesh>> operator &&(
		const dimensioned<Form>& dvs, const DimensionedField<Type, GeoMesh>& df1)
	{
		typedef typename scalarProduct<Form, Type>::type productType;
		tmp<DimensionedField<productType, GeoMesh>> tRes(new DimensionedField<productType, GeoMesh>(
			IOobject('(' + dvs.name() + "&&" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, dvs.dimensions() && df1.dimensions()));
		tnbLib::dotdot(tRes().field(), dvs.value(), df1.field());
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename scalarProduct<Form, Type>::type, GeoMesh>> operator &&(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const DimensionedField<Type, GeoMesh>& df1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) && df1;
	}

	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename scalarProduct<Form, Type>::type, GeoMesh>> operator &&(
		const dimensioned<Form>& dvs, const tmp<DimensionedField<Type, GeoMesh>>& tdf1)
	{
		typedef typename scalarProduct<Form, Type>::type productType;
		const DimensionedField<Type, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<productType, GeoMesh>> tRes = reuseTmpDimensionedField<productType, Type, GeoMesh>::New(
			tdf1, '(' + dvs.name() + "&&" + df1.name() + ')', dvs.dimensions() && df1.dimensions());
		tnbLib::dotdot(tRes().field(), dvs.value(), df1.field());
		reuseTmpDimensionedField<productType, Type, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename scalarProduct<Form, Type>::type, GeoMesh>> operator &&(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<DimensionedField<Type, GeoMesh>>& tdf1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) && tdf1;
	}

#undef PRODUCT_OPERATOR


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <undefFieldFunctionsM.hxx>