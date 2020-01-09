#include <GeometricField.hxx>
#include <GeometricFieldReuseFunctions.hxx>

#define TEMPLATE \
    template<class Type, template<class> class PatchField, class GeoMesh>
#include <GeometricFieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Global functions  * * * * * * * * * * * * * //

	template<class Type, template<class> class PatchField, class GeoMesh>
	void component
	(
		GeometricField
		<
		typename GeometricField<Type, PatchField, GeoMesh>::cmptType,
		PatchField,
		GeoMesh
		>& gcf,
		const GeometricField<Type, PatchField, GeoMesh>& gf,
		const direction d
	)
	{
		component(gcf.internalField(), gf.internalField(), d);
		component(gcf.boundaryField(), gf.boundaryField(), d);
	}


	template<class Type, template<class> class PatchField, class GeoMesh>
	void T
	(
		GeometricField<Type, PatchField, GeoMesh>& gf,
		const GeometricField<Type, PatchField, GeoMesh>& gf1
	)
	{
		T(gf.internalField(), gf1.internalField());
		T(gf.boundaryField(), gf1.boundaryField());
	}


	template<class Type, template<class> class PatchField, class GeoMesh, int r>
	void pow
	(
		GeometricField<typename powProduct<Type, r>::type, PatchField, GeoMesh>& gf,
		const GeometricField<Type, PatchField, GeoMesh>& gf1
	)
	{
		pow(gf.internalField(), gf1.internalField(), r);
		pow(gf.boundaryField(), gf1.boundaryField(), r);
	}

	template<class Type, template<class> class PatchField, class GeoMesh, int r>
	tmp<GeometricField<typename powProduct<Type, r>::type, PatchField, GeoMesh> >
		pow
		(
			const GeometricField<Type, PatchField, GeoMesh>& gf,
			typename powProduct<Type, r>::type
		)
	{
		typedef typename powProduct<Type, r>::type powProductType;

		tmp<GeometricField<powProductType, PatchField, GeoMesh> > tPow
		(
			new GeometricField<powProductType, PatchField, GeoMesh>
			(
				IOobject
				(
					"pow(" + gf.name() + ',' + name(r) + ')',
					gf.instance(),
					gf.db(),
					IOobject::NO_READ,
					IOobject::NO_WRITE
				),
				gf.mesh(),
				pow(gf.dimensions(), r)
				)
		);

		pow<Type, r, PatchField, GeoMesh>(tPow(), gf);

		return tPow;
	}


	template<class Type, template<class> class PatchField, class GeoMesh, int r>
	tmp<GeometricField<typename powProduct<Type, r>::type, PatchField, GeoMesh> >
		pow
		(
			const tmp<GeometricField<Type, PatchField, GeoMesh> >& tgf,
			typename powProduct<Type, r>::type
		)
	{
		typedef typename powProduct<Type, r>::type powProductType;

		const GeometricField<Type, PatchField, GeoMesh>& gf = tgf();

		tmp<GeometricField<powProductType, PatchField, GeoMesh> > tPow
		(
			new GeometricField<powProductType, PatchField, GeoMesh>
			(
				IOobject
				(
					"pow(" + gf.name() + ',' + name(r) + ')',
					gf.instance(),
					gf.db(),
					IOobject::NO_READ,
					IOobject::NO_WRITE
				),
				gf.mesh(),
				pow(gf.dimensions(), r)
				)
		);

		pow<Type, r, PatchField, GeoMesh>(tPow(), gf);

		tgf.clear();

		return tPow;
	}


	template<class Type, template<class> class PatchField, class GeoMesh>
	void sqr
	(
		GeometricField
		<typename outerProduct<Type, Type>::type, PatchField, GeoMesh>& gf,
		const GeometricField<Type, PatchField, GeoMesh>& gf1
	)
	{
		sqr(gf.internalField(), gf1.internalField());
		sqr(gf.boundaryField(), gf1.boundaryField());
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp
		<
		GeometricField
		<
		typename outerProduct<Type, Type>::type,
		PatchField,
		GeoMesh
		>
		>
		sqr(const GeometricField<Type, PatchField, GeoMesh>& gf)
	{
		typedef typename outerProduct<Type, Type>::type outerProductType;

		tmp<GeometricField<outerProductType, PatchField, GeoMesh> > tSqr
		(
			new GeometricField<outerProductType, PatchField, GeoMesh>
			(
				IOobject
				(
					"sqr(" + gf.name() + ')',
					gf.instance(),
					gf.db(),
					IOobject::NO_READ,
					IOobject::NO_WRITE
				),
				gf.mesh(),
				sqr(gf.dimensions())
				)
		);

		sqr(tSqr(), gf);

		return tSqr;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp
		<
		GeometricField
		<
		typename outerProduct<Type, Type>::type,
		PatchField,
		GeoMesh
		>
		>
		sqr(const tmp<GeometricField<Type, PatchField, GeoMesh> >& tgf)
	{
		typedef typename outerProduct<Type, Type>::type outerProductType;

		const GeometricField<Type, PatchField, GeoMesh>& gf = tgf();

		tmp<GeometricField<outerProductType, PatchField, GeoMesh> > tSqr
		(
			new GeometricField<outerProductType, PatchField, GeoMesh>
			(
				IOobject
				(
					"sqr(" + gf.name() + ')',
					gf.instance(),
					gf.db(),
					IOobject::NO_READ,
					IOobject::NO_WRITE
				),
				gf.mesh(),
				sqr(gf.dimensions())
				)
		);

		sqr(tSqr(), gf);

		tgf.clear();

		return tSqr;
	}


	template<class Type, template<class> class PatchField, class GeoMesh>
	void magSqr
	(
		GeometricField<scalar, PatchField, GeoMesh>& gsf,
		const GeometricField<Type, PatchField, GeoMesh>& gf
	)
	{
		magSqr(gsf.internalField(), gf.internalField());
		magSqr(gsf.boundaryField(), gf.boundaryField());
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh> > magSqr
	(
		const GeometricField<Type, PatchField, GeoMesh>& gf
	)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh> > tMagSqr
		(
			new GeometricField<scalar, PatchField, GeoMesh>
			(
				IOobject
				(
					"magSqr(" + gf.name() + ')',
					gf.instance(),
					gf.db(),
					IOobject::NO_READ,
					IOobject::NO_WRITE
				),
				gf.mesh(),
				sqr(gf.dimensions())
				)
		);

		magSqr(tMagSqr(), gf);

		return tMagSqr;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh> > magSqr
	(
		const tmp<GeometricField<Type, PatchField, GeoMesh> >& tgf
	)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf = tgf();

		tmp<GeometricField<scalar, PatchField, GeoMesh> > tMagSqr
		(
			new GeometricField<scalar, PatchField, GeoMesh>
			(
				IOobject
				(
					"magSqr(" + gf.name() + ')',
					gf.instance(),
					gf.db(),
					IOobject::NO_READ,
					IOobject::NO_WRITE
				),
				gf.mesh(),
				sqr(gf.dimensions())
				)
		);

		magSqr(tMagSqr(), gf);

		tgf.clear();

		return tMagSqr;
	}


	template<class Type, template<class> class PatchField, class GeoMesh>
	void mag
	(
		GeometricField<scalar, PatchField, GeoMesh>& gsf,
		const GeometricField<Type, PatchField, GeoMesh>& gf
	)
	{
		mag(gsf.internalField(), gf.internalField());
		mag(gsf.boundaryField(), gf.boundaryField());
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh> > mag
	(
		const GeometricField<Type, PatchField, GeoMesh>& gf
	)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh> > tMag
		(
			new GeometricField<scalar, PatchField, GeoMesh>
			(
				IOobject
				(
					"mag(" + gf.name() + ')',
					gf.instance(),
					gf.db(),
					IOobject::NO_READ,
					IOobject::NO_WRITE
				),
				gf.mesh(),
				gf.dimensions()
				)
		);

		mag(tMag(), gf);

		return tMag;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh> > mag
	(
		const tmp<GeometricField<Type, PatchField, GeoMesh> >& tgf
	)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf = tgf();

		tmp<GeometricField<scalar, PatchField, GeoMesh> > tMag
		(
			new GeometricField<scalar, PatchField, GeoMesh>
			(
				IOobject
				(
					"mag(" + gf.name() + ')',
					gf.instance(),
					gf.db(),
					IOobject::NO_READ,
					IOobject::NO_WRITE
				),
				gf.mesh(),
				gf.dimensions()
				)
		);

		mag(tMag(), gf);

		tgf.clear();

		return tMag;
	}


	template<class Type, template<class> class PatchField, class GeoMesh>
	void cmptAv
	(
		GeometricField
		<
		typename GeometricField<Type, PatchField, GeoMesh>::cmptType,
		PatchField,
		GeoMesh
		>& gcf,
		const GeometricField<Type, PatchField, GeoMesh>& gf
	)
	{
		cmptAv(gcf.internalField(), gf.internalField());
		cmptAv(gcf.boundaryField(), gf.boundaryField());
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp
		<
		GeometricField
		<
		typename GeometricField<Type, PatchField, GeoMesh>::cmptType,
		PatchField,
		GeoMesh
		>
		>
		cmptAv(const GeometricField<Type, PatchField, GeoMesh>& gf)
	{
		typedef typename GeometricField<Type, PatchField, GeoMesh>::cmptType
			cmptType;

		tmp<GeometricField<cmptType, PatchField, GeoMesh> > CmptAv
		(
			new GeometricField<scalar, PatchField, GeoMesh>
			(
				IOobject
				(
					"cmptAv(" + gf.name() + ')',
					gf.instance(),
					gf.db(),
					IOobject::NO_READ,
					IOobject::NO_WRITE
				),
				gf.mesh(),
				gf.dimensions()
				)
		);

		cmptAv(CmptAv(), gf);

		return CmptAv;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp
		<
		GeometricField
		<
		typename GeometricField<Type, PatchField, GeoMesh>::cmptType,
		PatchField,
		GeoMesh
		>
		>
		cmptAv(const tmp<GeometricField<Type, PatchField, GeoMesh> >& tgf)
	{
		typedef typename GeometricField<Type, PatchField, GeoMesh>::cmptType
			cmptType;

		const GeometricField<Type, PatchField, GeoMesh>& gf = tgf();

		tmp<GeometricField<cmptType, PatchField, GeoMesh> > CmptAv
		(
			new GeometricField<scalar, PatchField, GeoMesh>
			(
				IOobject
				(
					"cmptAv(" + gf.name() + ')',
					gf.instance(),
					gf.db(),
					IOobject::NO_READ,
					IOobject::NO_WRITE
				),
				gf.mesh(),
				gf.dimensions()
				)
		);

		cmptAv(CmptAv(), gf);

		tgf.clear();

		return CmptAv;
	}


#define UNARY_REDUCTION_FUNCTION_WITH_BOUNDARY(returnType, func, gFunc)       \
                                                                              \
template<class Type, template<class> class PatchField, class GeoMesh>         \
dimensioned<returnType> func                                                  \
(                                                                             \
    const GeometricField<Type, PatchField, GeoMesh>& gf                       \
)                                                                             \
{                                                                             \
    return dimensioned<Type>                                                  \
    (                                                                         \
        #func "(" + gf.name() + ')',                                          \
        gf.dimensions(),                                                      \
        tnbLib::func(gFunc(gf.internalField()), gFunc(gf.boundaryField()))      \
    );                                                                        \
}                                                                             \
                                                                              \
template<class Type, template<class> class PatchField, class GeoMesh>         \
dimensioned<returnType> func                                                  \
(                                                                             \
    const tmp<GeometricField<Type, PatchField, GeoMesh> >& tgf1               \
)                                                                             \
{                                                                             \
    dimensioned<returnType> res = func(tgf1());                               \
    tgf1.clear();                                                             \
    return res;                                                               \
}

	template <class Type, template<class> class PatchField, class GeoMesh>
	dimensioned<Type> max(const GeometricField<Type, PatchField, GeoMesh>& gf)
	{
		return dimensioned<Type>("max" "(" + gf.name() + ')', gf.dimensions(),
		                         tnbLib::max(gMax(gf.internalField()), gMax(gf.boundaryField())));
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	dimensioned<Type> max(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		dimensioned<Type> res = max(tgf1());
		tgf1.clear();
		return res;
	}
		
	template <class Type, template<class> class PatchField, class GeoMesh>
	dimensioned<Type> min(const GeometricField<Type, PatchField, GeoMesh>& gf)
	{
		return dimensioned<Type>("min" "(" + gf.name() + ')', gf.dimensions(),
		                         tnbLib::min(gMin(gf.internalField()), gMin(gf.boundaryField())));
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	dimensioned<Type> min(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		dimensioned<Type> res = min(tgf1());
		tgf1.clear();
		return res;
	}

#undef UNARY_REDUCTION_FUNCTION_WITH_BOUNDARY


#define UNARY_REDUCTION_FUNCTION(returnType, func, gFunc)                     \
                                                                              \
template<class Type, template<class> class PatchField, class GeoMesh>         \
dimensioned<returnType> func                                                  \
(                                                                             \
    const GeometricField<Type, PatchField, GeoMesh>& gf                       \
)                                                                             \
{                                                                             \
    return dimensioned<Type>                                                  \
    (                                                                         \
        #func "(" + gf.name() + ')',                                          \
        gf.dimensions(),                                                      \
        gFunc(gf.internalField())                                             \
    );                                                                        \
}                                                                             \
                                                                              \
template<class Type, template<class> class PatchField, class GeoMesh>         \
dimensioned<returnType> func                                                  \
(                                                                             \
    const tmp<GeometricField<Type, PatchField, GeoMesh> >& tgf1               \
)                                                                             \
{                                                                             \
    dimensioned<returnType> res = func(tgf1());                               \
    tgf1.clear();                                                             \
    return res;                                                               \
}

		
	template <class Type, template<class> class PatchField, class GeoMesh>
	dimensioned<Type> sum(const GeometricField<Type, PatchField, GeoMesh>& gf)
	{
		return dimensioned<Type>("sum" "(" + gf.name() + ')', gf.dimensions(), gSum(gf.internalField()));
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	dimensioned<Type> sum(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		dimensioned<Type> res = sum(tgf1());
		tgf1.clear();
		return res;
	}
		
	template <class Type, template<class> class PatchField, class GeoMesh>
	dimensioned<scalar> sumMag(const GeometricField<Type, PatchField, GeoMesh>& gf)
	{
		return dimensioned<Type>("sumMag" "(" + gf.name() + ')', gf.dimensions(), gSumMag(gf.internalField()));
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	dimensioned<scalar> sumMag(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		dimensioned<scalar> res = sumMag(tgf1());
		tgf1.clear();
		return res;
	}
		
	template <class Type, template<class> class PatchField, class GeoMesh>
	dimensioned<Type> average(const GeometricField<Type, PatchField, GeoMesh>& gf)
	{
		return dimensioned<Type>("average" "(" + gf.name() + ')', gf.dimensions(), gAverage(gf.internalField()));
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	dimensioned<Type> average(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		dimensioned<Type> res = average(tgf1());
		tgf1.clear();
		return res;
	}

#undef UNARY_REDUCTION_FUNCTION


		
	template <class Type, template<class> class PatchField, class GeoMesh>
	void max(GeometricField<Type, PatchField, GeoMesh>& res, const GeometricField<Type, PatchField, GeoMesh>& gf1,
	         const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tnbLib::max(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::max(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const GeometricField<Type, PatchField, GeoMesh>& gf1,
	                                                   const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(new GeometricField<Type, PatchField, GeoMesh>(
			IOobject("max" "(" + gf1.name() + ',' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ,
			         IOobject::NO_WRITE), gf1.mesh(), max(gf1.dimensions(), gf2.dimensions())));
		tnbLib::max(tRes(), gf1, gf2);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const GeometricField<Type, PatchField, GeoMesh>& gf1,
	                                                   const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(tgf2, "max" "(" + gf1.name() + ',' + gf2.name() + ')',
			                                                             max(gf1.dimensions(), gf2.dimensions())));
		tnbLib::max(tRes(), gf1, gf2);
		reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
	                                                   const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(tgf1, "max" "(" + gf1.name() + ',' + gf2.name() + ')',
			                                                             max(gf1.dimensions(), gf2.dimensions())));
		tnbLib::max(tRes(), gf1, gf2);
		reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
	                                                   const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<Type, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<Type, Type, Type, Type, PatchField, GeoMesh>::New(
				tgf1, tgf2, "max" "(" + gf1.name() + ',' + gf2.name() + ')', max(gf1.dimensions(), gf2.dimensions())));
		tnbLib::max(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<Type, Type, Type, Type, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}
		
	template <class Type, template<class> class PatchField, class GeoMesh>
	void min(GeometricField<Type, PatchField, GeoMesh>& res, const GeometricField<Type, PatchField, GeoMesh>& gf1,
	         const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tnbLib::min(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::min(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const GeometricField<Type, PatchField, GeoMesh>& gf1,
	                                                   const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(new GeometricField<Type, PatchField, GeoMesh>(
			IOobject("min" "(" + gf1.name() + ',' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ,
			         IOobject::NO_WRITE), gf1.mesh(), min(gf1.dimensions(), gf2.dimensions())));
		tnbLib::min(tRes(), gf1, gf2);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const GeometricField<Type, PatchField, GeoMesh>& gf1,
	                                                   const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(tgf2, "min" "(" + gf1.name() + ',' + gf2.name() + ')',
			                                                             min(gf1.dimensions(), gf2.dimensions())));
		tnbLib::min(tRes(), gf1, gf2);
		reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
	                                                   const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(tgf1, "min" "(" + gf1.name() + ',' + gf2.name() + ')',
			                                                             min(gf1.dimensions(), gf2.dimensions())));
		tnbLib::min(tRes(), gf1, gf2);
		reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
	                                                   const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<Type, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<Type, Type, Type, Type, PatchField, GeoMesh>::New(
				tgf1, tgf2, "min" "(" + gf1.name() + ',' + gf2.name() + ')', min(gf1.dimensions(), gf2.dimensions())));
		tnbLib::min(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<Type, Type, Type, Type, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}
		
	template <class Type, template<class> class PatchField, class GeoMesh>
	void cmptMultiply(GeometricField<Type, PatchField, GeoMesh>& res, const GeometricField<Type, PatchField, GeoMesh>& gf1,
	                  const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tnbLib::cmptMultiply(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::cmptMultiply(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const GeometricField<Type, PatchField, GeoMesh>& gf1,
	                                                            const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(new GeometricField<Type, PatchField, GeoMesh>(
			IOobject("cmptMultiply" "(" + gf1.name() + ',' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ,
			         IOobject::NO_WRITE), gf1.mesh(), cmptMultiply(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, gf2);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const GeometricField<Type, PatchField, GeoMesh>& gf1,
	                                                            const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(
			tgf2, "cmptMultiply" "(" + gf1.name() + ',' + gf2.name() + ')', cmptMultiply(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
	                                                            const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(
			tgf1, "cmptMultiply" "(" + gf1.name() + ',' + gf2.name() + ')', cmptMultiply(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
	                                                            const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<Type, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<Type, Type, Type, Type, PatchField, GeoMesh>::New(
				tgf1, tgf2, "cmptMultiply" "(" + gf1.name() + ',' + gf2.name() + ')',
				cmptMultiply(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<Type, Type, Type, Type, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}
		
	template <class Type, template<class> class PatchField, class GeoMesh>
	void cmptDivide(GeometricField<Type, PatchField, GeoMesh>& res, const GeometricField<Type, PatchField, GeoMesh>& gf1,
	                const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tnbLib::cmptDivide(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::cmptDivide(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const GeometricField<Type, PatchField, GeoMesh>& gf1,
	                                                          const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(new GeometricField<Type, PatchField, GeoMesh>(
			IOobject("cmptDivide" "(" + gf1.name() + ',' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ,
			         IOobject::NO_WRITE), gf1.mesh(), cmptDivide(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptDivide(tRes(), gf1, gf2);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const GeometricField<Type, PatchField, GeoMesh>& gf1,
	                                                          const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(
			tgf2, "cmptDivide" "(" + gf1.name() + ',' + gf2.name() + ')', cmptDivide(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptDivide(tRes(), gf1, gf2);
		reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
	                                                          const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(
			tgf1, "cmptDivide" "(" + gf1.name() + ',' + gf2.name() + ')', cmptDivide(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptDivide(tRes(), gf1, gf2);
		reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
	                                                          const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<Type, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<Type, Type, Type, Type, PatchField, GeoMesh>::New(
				tgf1, tgf2, "cmptDivide" "(" + gf1.name() + ',' + gf2.name() + ')',
				cmptDivide(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptDivide(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<Type, Type, Type, Type, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

		
	template <class Type, template<class> class PatchField, class GeoMesh>
	void max(GeometricField<Type, PatchField, GeoMesh>& res, const dimensioned<Type>& dt1,
	         const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tnbLib::max(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::max(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const dimensioned<Type>& dt1,
	                                                   const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(new GeometricField<Type, PatchField, GeoMesh>(
			IOobject("max" "(" + dt1.name() + ',' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ,
			         IOobject::NO_WRITE), gf2.mesh(), max(dt1.dimensions(), gf2.dimensions())));
		tnbLib::max(tRes(), dt1, gf2);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const Type& t1,
	                                                   const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		return max(dimensioned<Type>(t1), gf2);
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const dimensioned<Type>& dt1,
	                                                   const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(tgf2, "max" "(" + dt1.name() + gf2.name() + ',' + ')',
			                                                             max(dt1.dimensions(), gf2.dimensions())));
		tnbLib::max(tRes(), dt1, gf2);
		reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const Type& t1,
	                                                   const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		return max(dimensioned<Type>(t1), tgf2);
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	void max(GeometricField<Type, PatchField, GeoMesh>& res, const GeometricField<Type, PatchField, GeoMesh>& gf1,
	         const dimensioned<Type>& dt2)
	{
		tnbLib::max(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::max(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const GeometricField<Type, PatchField, GeoMesh>& gf1,
	                                                   const dimensioned<Type>& dt2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(new GeometricField<Type, PatchField, GeoMesh>(
			IOobject("max" "(" + gf1.name() + ',' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ,
			         IOobject::NO_WRITE), gf1.mesh(), max(gf1.dimensions(), dt2.dimensions())));
		tnbLib::max(tRes(), gf1, dt2);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const GeometricField<Type, PatchField, GeoMesh>& gf1,
	                                                   const Type& t2) { return max(gf1, dimensioned<Type>(t2)); }

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
	                                                   const dimensioned<Type>& dt2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(tgf1, "max" "(" + gf1.name() + ',' + dt2.name() + ')',
			                                                             max(gf1.dimensions(), dt2.dimensions())));
		tnbLib::max(tRes(), gf1, dt2);
		reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
	                                                   const Type& t2) { return max(tgf1, dimensioned<Type>(t2)); }
		
	template <class Type, template<class> class PatchField, class GeoMesh>
	void min(GeometricField<Type, PatchField, GeoMesh>& res, const dimensioned<Type>& dt1,
	         const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tnbLib::min(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::min(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const dimensioned<Type>& dt1,
	                                                   const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(new GeometricField<Type, PatchField, GeoMesh>(
			IOobject("min" "(" + dt1.name() + ',' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ,
			         IOobject::NO_WRITE), gf2.mesh(), min(dt1.dimensions(), gf2.dimensions())));
		tnbLib::min(tRes(), dt1, gf2);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const Type& t1,
	                                                   const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		return min(dimensioned<Type>(t1), gf2);
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const dimensioned<Type>& dt1,
	                                                   const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(tgf2, "min" "(" + dt1.name() + gf2.name() + ',' + ')',
			                                                             min(dt1.dimensions(), gf2.dimensions())));
		tnbLib::min(tRes(), dt1, gf2);
		reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const Type& t1,
	                                                   const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		return min(dimensioned<Type>(t1), tgf2);
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	void min(GeometricField<Type, PatchField, GeoMesh>& res, const GeometricField<Type, PatchField, GeoMesh>& gf1,
	         const dimensioned<Type>& dt2)
	{
		tnbLib::min(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::min(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const GeometricField<Type, PatchField, GeoMesh>& gf1,
	                                                   const dimensioned<Type>& dt2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(new GeometricField<Type, PatchField, GeoMesh>(
			IOobject("min" "(" + gf1.name() + ',' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ,
			         IOobject::NO_WRITE), gf1.mesh(), min(gf1.dimensions(), dt2.dimensions())));
		tnbLib::min(tRes(), gf1, dt2);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const GeometricField<Type, PatchField, GeoMesh>& gf1,
	                                                   const Type& t2) { return min(gf1, dimensioned<Type>(t2)); }

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
	                                                   const dimensioned<Type>& dt2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(tgf1, "min" "(" + gf1.name() + ',' + dt2.name() + ')',
			                                                             min(gf1.dimensions(), dt2.dimensions())));
		tnbLib::min(tRes(), gf1, dt2);
		reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
	                                                   const Type& t2) { return min(tgf1, dimensioned<Type>(t2)); }
		
	template <class Type, template<class> class PatchField, class GeoMesh>
	void cmptMultiply(GeometricField<Type, PatchField, GeoMesh>& res, const dimensioned<Type>& dt1,
	                  const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tnbLib::cmptMultiply(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::cmptMultiply(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const dimensioned<Type>& dt1,
	                                                            const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(new GeometricField<Type, PatchField, GeoMesh>(
			IOobject("cmptMultiply" "(" + dt1.name() + ',' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ,
			         IOobject::NO_WRITE), gf2.mesh(), cmptMultiply(dt1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), dt1, gf2);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const Type& t1,
	                                                            const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		return cmptMultiply(dimensioned<Type>(t1), gf2);
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const dimensioned<Type>& dt1,
	                                                            const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(
			tgf2, "cmptMultiply" "(" + dt1.name() + gf2.name() + ',' + ')', cmptMultiply(dt1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), dt1, gf2);
		reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const Type& t1,
	                                                            const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		return cmptMultiply(dimensioned<Type>(t1), tgf2);
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	void cmptMultiply(GeometricField<Type, PatchField, GeoMesh>& res, const GeometricField<Type, PatchField, GeoMesh>& gf1,
	                  const dimensioned<Type>& dt2)
	{
		tnbLib::cmptMultiply(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::cmptMultiply(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const GeometricField<Type, PatchField, GeoMesh>& gf1,
	                                                            const dimensioned<Type>& dt2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(new GeometricField<Type, PatchField, GeoMesh>(
			IOobject("cmptMultiply" "(" + gf1.name() + ',' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ,
			         IOobject::NO_WRITE), gf1.mesh(), cmptMultiply(gf1.dimensions(), dt2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, dt2);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const GeometricField<Type, PatchField, GeoMesh>& gf1,
	                                                            const Type& t2)
	{
		return cmptMultiply(gf1, dimensioned<Type>(t2));
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
	                                                            const dimensioned<Type>& dt2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(
			tgf1, "cmptMultiply" "(" + gf1.name() + ',' + dt2.name() + ')', cmptMultiply(gf1.dimensions(), dt2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, dt2);
		reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
	                                                            const Type& t2)
	{
		return cmptMultiply(tgf1, dimensioned<Type>(t2));
	}
		
	template <class Type, template<class> class PatchField, class GeoMesh>
	void cmptDivide(GeometricField<Type, PatchField, GeoMesh>& res, const dimensioned<Type>& dt1,
	                const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tnbLib::cmptDivide(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::cmptDivide(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const dimensioned<Type>& dt1,
	                                                          const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(new GeometricField<Type, PatchField, GeoMesh>(
			IOobject("cmptDivide" "(" + dt1.name() + ',' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ,
			         IOobject::NO_WRITE), gf2.mesh(), cmptDivide(dt1.dimensions(), gf2.dimensions())));
		tnbLib::cmptDivide(tRes(), dt1, gf2);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const Type& t1,
	                                                          const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		return cmptDivide(dimensioned<Type>(t1), gf2);
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const dimensioned<Type>& dt1,
	                                                          const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(
			tgf2, "cmptDivide" "(" + dt1.name() + gf2.name() + ',' + ')', cmptDivide(dt1.dimensions(), gf2.dimensions())));
		tnbLib::cmptDivide(tRes(), dt1, gf2);
		reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const Type& t1,
	                                                          const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		return cmptDivide(dimensioned<Type>(t1), tgf2);
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	void cmptDivide(GeometricField<Type, PatchField, GeoMesh>& res, const GeometricField<Type, PatchField, GeoMesh>& gf1,
	                const dimensioned<Type>& dt2)
	{
		tnbLib::cmptDivide(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::cmptDivide(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const GeometricField<Type, PatchField, GeoMesh>& gf1,
	                                                          const dimensioned<Type>& dt2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(new GeometricField<Type, PatchField, GeoMesh>(
			IOobject("cmptDivide" "(" + gf1.name() + ',' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ,
			         IOobject::NO_WRITE), gf1.mesh(), cmptDivide(gf1.dimensions(), dt2.dimensions())));
		tnbLib::cmptDivide(tRes(), gf1, dt2);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const GeometricField<Type, PatchField, GeoMesh>& gf1,
	                                                          const Type& t2)
	{
		return cmptDivide(gf1, dimensioned<Type>(t2));
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
	                                                          const dimensioned<Type>& dt2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(
			tgf1, "cmptDivide" "(" + gf1.name() + ',' + dt2.name() + ')', cmptDivide(gf1.dimensions(), dt2.dimensions())));
		tnbLib::cmptDivide(tRes(), gf1, dt2);
		reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
	                                                          const Type& t2)
	{
		return cmptDivide(tgf1, dimensioned<Type>(t2));
	}


		// * * * * * * * * * * * * * * * Global operators  * * * * * * * * * * * * * //

		
	template <class Type, template<class> class PatchField, class GeoMesh>
	void negate(GeometricField<Type, PatchField, GeoMesh>& res, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		tnbLib::negate(res.internalField(), gf1.internalField());
		tnbLib::negate(res.boundaryField(), gf1.boundaryField());
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator -(const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(new GeometricField<Type, PatchField, GeoMesh>(
			IOobject("-" + gf1.name(), gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			transform(gf1.dimensions())));
		tnbLib::negate(tRes(), gf1);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator -(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(tgf1, "-" + gf1.name(), transform(gf1.dimensions())));
		tnbLib::negate(tRes(), gf1);
		reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

#ifndef __INTEL_COMPILER
		
	template <class Type, template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<Type, PatchField, GeoMesh>& res, const GeometricField<Type, PatchField, GeoMesh>& gf1,
	              const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		tnbLib::multiply(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::multiply(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const GeometricField<Type, PatchField, GeoMesh>& gf1,
	                                                          const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(new GeometricField<Type, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '*' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const GeometricField<Type, PatchField, GeoMesh>& gf1,
	                                                          const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, scalar, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + '*' + gf2.name() + ')',
			                                                               gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<Type, scalar, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
	                                                          const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '*' + gf2.name() + ')',
			                                                             gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
	                                                          const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<scalar, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<Type, Type, Type, scalar, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '*' + gf2.name() + ')', gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<Type, Type, Type, scalar, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}
		
	template <class Type, template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<Type, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	              const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tnbLib::multiply(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::multiply(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                          const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(new GeometricField<Type, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '*' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                          const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + '*' + gf2.name() + ')',
			                                                             gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
	                                                          const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, scalar, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '*' + gf2.name() + ')',
			                                                               gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<Type, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
	                                                          const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<Type, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<Type, scalar, scalar, Type, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '*' + gf2.name() + ')', gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<Type, scalar, scalar, Type, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}
#endif
		
	template <class Type, template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<Type, PatchField, GeoMesh>& res, const GeometricField<Type, PatchField, GeoMesh>& gf1,
	            const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator /(const GeometricField<Type, PatchField, GeoMesh>& gf1,
	                                                          const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(new GeometricField<Type, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator /(const GeometricField<Type, PatchField, GeoMesh>& gf1,
	                                                          const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, scalar, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + '|' + gf2.name() + ')',
			                                                               gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<Type, scalar, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator /(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
	                                                          const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '|' + gf2.name() + ')',
			                                                             gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator /(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
	                                                          const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<scalar, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<Type, Type, Type, scalar, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<Type, Type, Type, scalar, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

		
	template <class Type, template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<Type, PatchField, GeoMesh>& res, const dimensioned<scalar>& dt1,
	              const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tnbLib::multiply(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::multiply(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const dimensioned<scalar>& dt1,
	                                                          const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(new GeometricField<Type, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '*' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), dt1, gf2);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const scalar& t1,
	                                                          const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<scalar>(t1) * gf2;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const dimensioned<scalar>& dt1,
	                                                          const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(tgf2, '(' + dt1.name() + '*' + gf2.name() + ')',
			                                                             dt1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), dt1, gf2);
		reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const scalar& t1,
	                                                          const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<scalar>(t1) * tgf2;
	}
		
	template <class Type, template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<Type, PatchField, GeoMesh>& res, const GeometricField<Type, PatchField, GeoMesh>& gf1,
	              const dimensioned<scalar>& dt2)
	{
		tnbLib::multiply(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::multiply(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const GeometricField<Type, PatchField, GeoMesh>& gf1,
	                                                          const dimensioned<scalar>& dt2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(new GeometricField<Type, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '*' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() * dt2.dimensions()));
		tnbLib::multiply(tRes(), gf1, dt2);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const GeometricField<Type, PatchField, GeoMesh>& gf1,
	                                                          const scalar& t2) { return gf1 * dimensioned<scalar>(t2); }

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
	                                                          const dimensioned<scalar>& dt2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '*' + dt2.name() + ')',
			                                                             gf1.dimensions() * dt2.dimensions()));
		tnbLib::multiply(tRes(), gf1, dt2);
		reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
	                                                          const scalar& t2) { return tgf1 * dimensioned<scalar>(t2); }

		
	template <class Type, template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<Type, PatchField, GeoMesh>& res, const GeometricField<Type, PatchField, GeoMesh>& gf1,
	            const dimensioned<scalar>& dt2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator /(const GeometricField<Type, PatchField, GeoMesh>& gf1,
	                                                          const dimensioned<scalar>& dt2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(new GeometricField<Type, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator /(const GeometricField<Type, PatchField, GeoMesh>& gf1,
	                                                          const scalar& t2) { return gf1 / dimensioned<scalar>(t2); }

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator /(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
	                                                          const dimensioned<scalar>& dt2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '|' + dt2.name() + ')',
			                                                             gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator /(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
	                                                          const scalar& t2) { return tgf1 / dimensioned<scalar>(t2); }


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define PRODUCT_OPERATOR(product, op, opFunc)                                 \
                                                                              \
template                                                                      \
<class Type1, class Type2, template<class> class PatchField, class GeoMesh>   \
void opFunc                                                                   \
(                                                                             \
    GeometricField                                                            \
    <typename product<Type1, Type2>::type, PatchField, GeoMesh>& gf,          \
    const GeometricField<Type1, PatchField, GeoMesh>& gf1,                    \
    const GeometricField<Type2, PatchField, GeoMesh>& gf2                     \
)                                                                             \
{                                                                             \
    tnbLib::opFunc(gf.internalField(), gf1.internalField(), gf2.internalField());\
    tnbLib::opFunc(gf.boundaryField(), gf1.boundaryField(), gf2.boundaryField());\
}                                                                             \
                                                                              \
template                                                                      \
<class Type1, class Type2, template<class> class PatchField, class GeoMesh>   \
tmp                                                                           \
<                                                                             \
    GeometricField<typename product<Type1, Type2>::type, PatchField, GeoMesh> \
>                                                                             \
operator op                                                                   \
(                                                                             \
    const GeometricField<Type1, PatchField, GeoMesh>& gf1,                    \
    const GeometricField<Type2, PatchField, GeoMesh>& gf2                     \
)                                                                             \
{                                                                             \
    typedef typename product<Type1, Type2>::type productType;                 \
    tmp<GeometricField<productType, PatchField, GeoMesh> > tRes               \
    (                                                                         \
        new GeometricField<productType, PatchField, GeoMesh>                  \
        (                                                                     \
            IOobject                                                          \
            (                                                                 \
                '(' + gf1.name() + #op + gf2.name() + ')',                    \
                gf1.instance(),                                               \
                gf1.db(),                                                     \
                IOobject::NO_READ,                                            \
                IOobject::NO_WRITE                                            \
            ),                                                                \
            gf1.mesh(),                                                       \
            gf1.dimensions() op gf2.dimensions()                              \
        )                                                                     \
    );                                                                        \
                                                                              \
    tnbLib::opFunc(tRes(), gf1, gf2);                                           \
                                                                              \
    return tRes;                                                              \
}                                                                             \
                                                                              \
template                                                                      \
<class Type1, class Type2, template<class> class PatchField, class GeoMesh>   \
tmp                                                                           \
<                                                                             \
    GeometricField<typename product<Type1, Type2>::type, PatchField, GeoMesh> \
>                                                                             \
operator op                                                                   \
(                                                                             \
    const GeometricField<Type1, PatchField, GeoMesh>& gf1,                    \
    const tmp<GeometricField<Type2, PatchField, GeoMesh> >& tgf2              \
)                                                                             \
{                                                                             \
    typedef typename product<Type1, Type2>::type productType;                 \
                                                                              \
    const GeometricField<Type2, PatchField, GeoMesh>& gf2 = tgf2();           \
                                                                              \
    tmp<GeometricField<productType, PatchField, GeoMesh> > tRes =             \
        reuseTmpGeometricField<productType, Type2, PatchField, GeoMesh>::New  \
        (                                                                     \
            tgf2,                                                             \
            '(' + gf1.name() + #op + gf2.name() + ')',                        \
            gf1.dimensions() op gf2.dimensions()                              \
        );                                                                    \
                                                                              \
    tnbLib::opFunc(tRes(), gf1, gf2);                                           \
                                                                              \
    reuseTmpGeometricField<productType, Type2, PatchField, GeoMesh>           \
    ::clear(tgf2);                                                            \
                                                                              \
    return tRes;                                                              \
}                                                                             \
                                                                              \
template                                                                      \
<class Type1, class Type2, template<class> class PatchField, class GeoMesh>   \
tmp                                                                           \
<                                                                             \
    GeometricField<typename product<Type1, Type2>::type, PatchField, GeoMesh> \
>                                                                             \
operator op                                                                   \
(                                                                             \
    const tmp<GeometricField<Type1, PatchField, GeoMesh> >& tgf1,             \
    const GeometricField<Type2, PatchField, GeoMesh>& gf2                     \
)                                                                             \
{                                                                             \
    typedef typename product<Type1, Type2>::type productType;                 \
                                                                              \
    const GeometricField<Type1, PatchField, GeoMesh>& gf1 = tgf1();           \
                                                                              \
    tmp<GeometricField<productType, PatchField, GeoMesh> > tRes =             \
        reuseTmpGeometricField<productType, Type1, PatchField, GeoMesh>::New  \
        (                                                                     \
            tgf1,                                                             \
            '(' + gf1.name() + #op + gf2.name() + ')',                        \
            gf1.dimensions() op gf2.dimensions()                              \
        );                                                                    \
                                                                              \
    tnbLib::opFunc(tRes(), gf1, gf2);                                           \
                                                                              \
    reuseTmpGeometricField<productType, Type1, PatchField, GeoMesh>           \
    ::clear(tgf1);                                                            \
                                                                              \
    return tRes;                                                              \
}                                                                             \
                                                                              \
template                                                                      \
<class Type1, class Type2, template<class> class PatchField, class GeoMesh>   \
tmp                                                                           \
<                                                                             \
    GeometricField<typename product<Type1, Type2>::type, PatchField, GeoMesh> \
>                                                                             \
operator op                                                                   \
(                                                                             \
    const tmp<GeometricField<Type1, PatchField, GeoMesh> >& tgf1,             \
    const tmp<GeometricField<Type2, PatchField, GeoMesh> >& tgf2              \
)                                                                             \
{                                                                             \
    typedef typename product<Type1, Type2>::type productType;                 \
                                                                              \
    const GeometricField<Type1, PatchField, GeoMesh>& gf1 = tgf1();           \
    const GeometricField<Type2, PatchField, GeoMesh>& gf2 = tgf2();           \
                                                                              \
    tmp<GeometricField<productType, PatchField, GeoMesh> > tRes =             \
        reuseTmpTmpGeometricField                                             \
        <productType, Type1, Type1, Type2, PatchField, GeoMesh>::New          \
        (                                                                     \
            tgf1,                                                             \
            tgf2,                                                             \
            '(' + gf1.name() + #op + gf2.name() + ')',                        \
            gf1.dimensions() op gf2.dimensions()                              \
        );                                                                    \
                                                                              \
    tnbLib::opFunc(tRes(), gf1, gf2);                                           \
                                                                              \
    reuseTmpTmpGeometricField                                                 \
        <productType, Type1, Type1, Type2, PatchField, GeoMesh>               \
    ::clear(tgf1, tgf2);                                                      \
                                                                              \
    return tRes;                                                              \
}                                                                             \
                                                                              \
template                                                                      \
<class Form, class Type, template<class> class PatchField, class GeoMesh>     \
void opFunc                                                                   \
(                                                                             \
    GeometricField                                                            \
    <typename product<Type, Form>::type, PatchField, GeoMesh>& gf,            \
    const GeometricField<Type, PatchField, GeoMesh>& gf1,                     \
    const dimensioned<Form>& dvs                                              \
)                                                                             \
{                                                                             \
    tnbLib::opFunc(gf.internalField(), gf1.internalField(), dvs.value());       \
    tnbLib::opFunc(gf.boundaryField(), gf1.boundaryField(), dvs.value());       \
}                                                                             \
                                                                              \
template                                                                      \
<class Form, class Type, template<class> class PatchField, class GeoMesh>     \
tmp<GeometricField<typename product<Type, Form>::type, PatchField, GeoMesh> > \
operator op                                                                   \
(                                                                             \
    const GeometricField<Type, PatchField, GeoMesh>& gf1,                     \
    const dimensioned<Form>& dvs                                              \
)                                                                             \
{                                                                             \
    typedef typename product<Type, Form>::type productType;                   \
                                                                              \
    tmp<GeometricField<productType, PatchField, GeoMesh> > tRes               \
    (                                                                         \
        new GeometricField<productType, PatchField, GeoMesh>                  \
        (                                                                     \
            IOobject                                                          \
            (                                                                 \
                '(' + gf1.name() + #op + dvs.name() + ')',                    \
                gf1.instance(),                                               \
                gf1.db(),                                                     \
                IOobject::NO_READ,                                            \
                IOobject::NO_WRITE                                            \
            ),                                                                \
            gf1.mesh(),                                                       \
            gf1.dimensions() op dvs.dimensions()                              \
        )                                                                     \
    );                                                                        \
                                                                              \
    tnbLib::opFunc(tRes(), gf1, dvs);                                           \
                                                                              \
    return tRes;                                                              \
}                                                                             \
                                                                              \
template                                                                      \
<                                                                             \
    class Form,                                                               \
    class Cmpt,                                                               \
    int nCmpt,                                                                \
    class Type, template<class> class PatchField,                             \
    class GeoMesh                                                             \
>                                                                             \
tmp<GeometricField<typename product<Form, Type>::type, PatchField, GeoMesh> > \
operator op                                                                   \
(                                                                             \
    const GeometricField<Type, PatchField, GeoMesh>& gf1,                     \
    const VectorSpace<Form,Cmpt,nCmpt>& vs                                    \
)                                                                             \
{                                                                             \
    return gf1 op dimensioned<Form>(static_cast<const Form&>(vs));            \
}                                                                             \
                                                                              \
                                                                              \
template                                                                      \
<class Form, class Type, template<class> class PatchField, class GeoMesh>     \
tmp<GeometricField<typename product<Type, Form>::type, PatchField, GeoMesh> > \
operator op                                                                   \
(                                                                             \
    const tmp<GeometricField<Type, PatchField, GeoMesh> >& tgf1,              \
    const dimensioned<Form>& dvs                                              \
)                                                                             \
{                                                                             \
    typedef typename product<Type, Form>::type productType;                   \
                                                                              \
    const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();            \
                                                                              \
    tmp<GeometricField<productType, PatchField, GeoMesh> > tRes =             \
        reuseTmpGeometricField<productType, Type, PatchField, GeoMesh>::New   \
        (                                                                     \
            tgf1,                                                             \
            '(' + gf1.name() + #op + dvs.name() + ')',                        \
            gf1.dimensions() op dvs.dimensions()                              \
        );                                                                    \
                                                                              \
    tnbLib::opFunc(tRes(), gf1, dvs);                                           \
                                                                              \
    reuseTmpGeometricField<productType, Type, PatchField, GeoMesh>            \
    ::clear(tgf1);                                                            \
                                                                              \
    return tRes;                                                              \
}                                                                             \
                                                                              \
template                                                                      \
<                                                                             \
    class Form,                                                               \
    class Cmpt,                                                               \
    int nCmpt,                                                                \
    class Type, template<class> class PatchField,                             \
    class GeoMesh                                                             \
>                                                                             \
tmp<GeometricField<typename product<Form, Type>::type, PatchField, GeoMesh> > \
operator op                                                                   \
(                                                                             \
    const tmp<GeometricField<Type, PatchField, GeoMesh> >& tgf1,              \
    const VectorSpace<Form,Cmpt,nCmpt>& vs                                    \
)                                                                             \
{                                                                             \
    return tgf1 op dimensioned<Form>(static_cast<const Form&>(vs));           \
}                                                                             \
                                                                              \
                                                                              \
template                                                                      \
<class Form, class Type, template<class> class PatchField, class GeoMesh>     \
void opFunc                                                                   \
(                                                                             \
    GeometricField                                                            \
    <typename product<Form, Type>::type, PatchField, GeoMesh>& gf,            \
    const dimensioned<Form>& dvs,                                             \
    const GeometricField<Type, PatchField, GeoMesh>& gf1                      \
)                                                                             \
{                                                                             \
    tnbLib::opFunc(gf.internalField(), dvs.value(), gf1.internalField());       \
    tnbLib::opFunc(gf.boundaryField(), dvs.value(), gf1.boundaryField());       \
}                                                                             \
                                                                              \
template                                                                      \
<class Form, class Type, template<class> class PatchField, class GeoMesh>     \
tmp<GeometricField<typename product<Form, Type>::type, PatchField, GeoMesh> > \
operator op                                                                   \
(                                                                             \
    const dimensioned<Form>& dvs,                                             \
    const GeometricField<Type, PatchField, GeoMesh>& gf1                      \
)                                                                             \
{                                                                             \
    typedef typename product<Form, Type>::type productType;                   \
    tmp<GeometricField<productType, PatchField, GeoMesh> > tRes               \
    (                                                                         \
        new GeometricField<productType, PatchField, GeoMesh>                  \
        (                                                                     \
            IOobject                                                          \
            (                                                                 \
                '(' + dvs.name() + #op + gf1.name() + ')',                    \
                gf1.instance(),                                               \
                gf1.db(),                                                     \
                IOobject::NO_READ,                                            \
                IOobject::NO_WRITE                                            \
            ),                                                                \
            gf1.mesh(),                                                       \
            dvs.dimensions() op gf1.dimensions()                              \
        )                                                                     \
    );                                                                        \
                                                                              \
    tnbLib::opFunc(tRes(), dvs, gf1);                                           \
                                                                              \
    return tRes;                                                              \
}                                                                             \
                                                                              \
template                                                                      \
<                                                                             \
    class Form,                                                               \
    class Cmpt,                                                               \
    int nCmpt,                                                                \
    class Type, template<class> class PatchField,                             \
    class GeoMesh                                                             \
>                                                                             \
tmp<GeometricField<typename product<Form, Type>::type, PatchField, GeoMesh> > \
operator op                                                                   \
(                                                                             \
    const VectorSpace<Form,Cmpt,nCmpt>& vs,                                   \
    const GeometricField<Type, PatchField, GeoMesh>& gf1                      \
)                                                                             \
{                                                                             \
    return dimensioned<Form>(static_cast<const Form&>(vs)) op gf1;            \
}                                                                             \
                                                                              \
template                                                                      \
<class Form, class Type, template<class> class PatchField, class GeoMesh>     \
tmp<GeometricField<typename product<Form, Type>::type, PatchField, GeoMesh> > \
operator op                                                                   \
(                                                                             \
    const dimensioned<Form>& dvs,                                             \
    const tmp<GeometricField<Type, PatchField, GeoMesh> >& tgf1               \
)                                                                             \
{                                                                             \
    typedef typename product<Form, Type>::type productType;                   \
                                                                              \
    const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();            \
                                                                              \
    tmp<GeometricField<productType, PatchField, GeoMesh> > tRes =             \
        reuseTmpGeometricField<productType, Type, PatchField, GeoMesh>::New   \
        (                                                                     \
            tgf1,                                                             \
            '(' + dvs.name() + #op + gf1.name() + ')',                        \
            dvs.dimensions() op gf1.dimensions()                              \
        );                                                                    \
                                                                              \
    tnbLib::opFunc(tRes(), dvs, gf1);                                           \
                                                                              \
    reuseTmpGeometricField<productType, Type, PatchField, GeoMesh>            \
    ::clear(tgf1);                                                            \
                                                                              \
    return tRes;                                                              \
}                                                                             \
                                                                              \
template                                                                      \
<                                                                             \
    class Form,                                                               \
    class Cmpt,                                                               \
    int nCmpt,                                                                \
    class Type, template<class> class PatchField,                             \
    class GeoMesh                                                             \
>                                                                             \
tmp<GeometricField<typename product<Form, Type>::type, PatchField, GeoMesh> > \
operator op                                                                   \
(                                                                             \
    const VectorSpace<Form,Cmpt,nCmpt>& vs,                                   \
    const tmp<GeometricField<Type, PatchField, GeoMesh> >& tgf1               \
)                                                                             \
{                                                                             \
    return dimensioned<Form>(static_cast<const Form&>(vs)) op tgf1;           \
}

		
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	void add(GeometricField<typename typeOfSum<Type1, Type2>::type, PatchField, GeoMesh>& gf,
	         const GeometricField<Type1, PatchField, GeoMesh>& gf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(gf.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::add(gf.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type1, Type2>::type, PatchField, GeoMesh>> operator +(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(new GeometricField<productType, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + "+" + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type1, Type2>::type, PatchField, GeoMesh>> operator +(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		const GeometricField<Type2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type2, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + "+" + gf2.name() + ')',
			                                              gf1.dimensions() + gf2.dimensions());
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<productType, Type2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type1, Type2>::type, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		const GeometricField<Type1, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type1, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + "+" + gf2.name() + ')',
			                                              gf1.dimensions() + gf2.dimensions());
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<productType, Type1, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type1, Type2>::type, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		const GeometricField<Type1, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<Type2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpTmpGeometricField<
			productType, Type1, Type1, Type2, PatchField, GeoMesh>::New(tgf1, tgf2, '(' + gf1.name() + "+" + gf2.name() + ')',
			                                                            gf1.dimensions() + gf2.dimensions());
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<productType, Type1, Type1, Type2, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void add(GeometricField<typename typeOfSum<Type, Form>::type, PatchField, GeoMesh>& gf,
	         const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs)
	{
		tnbLib::add(gf.internalField(), gf1.internalField(), dvs.value());
		tnbLib::add(gf.boundaryField(), gf1.boundaryField(), dvs.value());
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type, Form>::type, PatchField, GeoMesh>> operator +(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs)
	{
		typedef typename typeOfSum<Type, Form>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(new GeometricField<productType, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + "+" + dvs.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + dvs.dimensions()));
		tnbLib::add(tRes(), gf1, dvs);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator +(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return gf1 + dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type, Form>::type, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const dimensioned<Form>& dvs)
	{
		typedef typename typeOfSum<Type, Form>::type productType;
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + "+" + dvs.name() + ')',
			                                             gf1.dimensions() + dvs.dimensions());
		tnbLib::add(tRes(), gf1, dvs);
		reuseTmpGeometricField<productType, Type, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return tgf1 + dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void add(GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>& gf, const dimensioned<Form>& dvs,
	         const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		tnbLib::add(gf.internalField(), dvs.value(), gf1.internalField());
		tnbLib::add(gf.boundaryField(), dvs.value(), gf1.boundaryField());
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator +(
		const dimensioned<Form>& dvs, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		typedef typename typeOfSum<Form, Type>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(new GeometricField<productType, PatchField, GeoMesh>(
			IOobject('(' + dvs.name() + "+" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), dvs.dimensions() + gf1.dimensions()));
		tnbLib::add(tRes(), dvs, gf1);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator +(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) + gf1;
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator +(
		const dimensioned<Form>& dvs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		typedef typename typeOfSum<Form, Type>::type productType;
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type, PatchField, GeoMesh>::New(tgf1, '(' + dvs.name() + "+" + gf1.name() + ')',
			                                             dvs.dimensions() + gf1.dimensions());
		tnbLib::add(tRes(), dvs, gf1);
		reuseTmpGeometricField<productType, Type, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator +(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) + tgf1;
	}
		
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<typename typeOfSum<Type1, Type2>::type, PatchField, GeoMesh>& gf,
	              const GeometricField<Type1, PatchField, GeoMesh>& gf1,
	              const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(gf.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::subtract(gf.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type1, Type2>::type, PatchField, GeoMesh>> operator -(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(new GeometricField<productType, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + "-" + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type1, Type2>::type, PatchField, GeoMesh>> operator -(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		const GeometricField<Type2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type2, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + "-" + gf2.name() + ')',
			                                              gf1.dimensions() - gf2.dimensions());
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<productType, Type2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type1, Type2>::type, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		const GeometricField<Type1, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type1, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + "-" + gf2.name() + ')',
			                                              gf1.dimensions() - gf2.dimensions());
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<productType, Type1, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type1, Type2>::type, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		const GeometricField<Type1, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<Type2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpTmpGeometricField<
			productType, Type1, Type1, Type2, PatchField, GeoMesh>::New(tgf1, tgf2, '(' + gf1.name() + "-" + gf2.name() + ')',
			                                                            gf1.dimensions() - gf2.dimensions());
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<productType, Type1, Type1, Type2, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<typename typeOfSum<Type, Form>::type, PatchField, GeoMesh>& gf,
	              const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs)
	{
		tnbLib::subtract(gf.internalField(), gf1.internalField(), dvs.value());
		tnbLib::subtract(gf.boundaryField(), gf1.boundaryField(), dvs.value());
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type, Form>::type, PatchField, GeoMesh>> operator -(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs)
	{
		typedef typename typeOfSum<Type, Form>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(new GeometricField<productType, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + "-" + dvs.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - dvs.dimensions()));
		tnbLib::subtract(tRes(), gf1, dvs);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator -(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return gf1 - dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type, Form>::type, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const dimensioned<Form>& dvs)
	{
		typedef typename typeOfSum<Type, Form>::type productType;
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + "-" + dvs.name() + ')',
			                                             gf1.dimensions() - dvs.dimensions());
		tnbLib::subtract(tRes(), gf1, dvs);
		reuseTmpGeometricField<productType, Type, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return tgf1 - dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>& gf,
	              const dimensioned<Form>& dvs, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		tnbLib::subtract(gf.internalField(), dvs.value(), gf1.internalField());
		tnbLib::subtract(gf.boundaryField(), dvs.value(), gf1.boundaryField());
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator -(
		const dimensioned<Form>& dvs, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		typedef typename typeOfSum<Form, Type>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(new GeometricField<productType, PatchField, GeoMesh>(
			IOobject('(' + dvs.name() + "-" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), dvs.dimensions() - gf1.dimensions()));
		tnbLib::subtract(tRes(), dvs, gf1);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator -(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) - gf1;
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator -(
		const dimensioned<Form>& dvs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		typedef typename typeOfSum<Form, Type>::type productType;
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type, PatchField, GeoMesh>::New(tgf1, '(' + dvs.name() + "-" + gf1.name() + ')',
			                                             dvs.dimensions() - gf1.dimensions());
		tnbLib::subtract(tRes(), dvs, gf1);
		reuseTmpGeometricField<productType, Type, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator -(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) - tgf1;
	}

		
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	void outer(GeometricField<typename outerProduct<Type1, Type2>::type, PatchField, GeoMesh>& gf,
	           const GeometricField<Type1, PatchField, GeoMesh>& gf1,
	           const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::outer(gf.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::outer(gf.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator *(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		typedef typename outerProduct<Type1, Type2>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(new GeometricField<productType, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + "*" + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() * gf2.dimensions()));
		tnbLib::outer(tRes(), gf1, gf2);
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator *(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2)
	{
		typedef typename outerProduct<Type1, Type2>::type productType;
		const GeometricField<Type2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type2, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + "*" + gf2.name() + ')',
			                                              gf1.dimensions() * gf2.dimensions());
		tnbLib::outer(tRes(), gf1, gf2);
		reuseTmpGeometricField<productType, Type2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		typedef typename outerProduct<Type1, Type2>::type productType;
		const GeometricField<Type1, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type1, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + "*" + gf2.name() + ')',
			                                              gf1.dimensions() * gf2.dimensions());
		tnbLib::outer(tRes(), gf1, gf2);
		reuseTmpGeometricField<productType, Type1, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2)
	{
		typedef typename outerProduct<Type1, Type2>::type productType;
		const GeometricField<Type1, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<Type2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpTmpGeometricField<
			productType, Type1, Type1, Type2, PatchField, GeoMesh>::New(tgf1, tgf2, '(' + gf1.name() + "*" + gf2.name() + ')',
			                                                            gf1.dimensions() * gf2.dimensions());
		tnbLib::outer(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<productType, Type1, Type1, Type2, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void outer(GeometricField<typename outerProduct<Type, Form>::type, PatchField, GeoMesh>& gf,
	           const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs)
	{
		tnbLib::outer(gf.internalField(), gf1.internalField(), dvs.value());
		tnbLib::outer(gf.boundaryField(), gf1.boundaryField(), dvs.value());
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Type, Form>::type, PatchField, GeoMesh>> operator *(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs)
	{
		typedef typename outerProduct<Type, Form>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(new GeometricField<productType, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + "*" + dvs.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() * dvs.dimensions()));
		tnbLib::outer(tRes(), gf1, dvs);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Form, Type>::type, PatchField, GeoMesh>> operator *(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return gf1 * dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Type, Form>::type, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const dimensioned<Form>& dvs)
	{
		typedef typename outerProduct<Type, Form>::type productType;
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + "*" + dvs.name() + ')',
			                                             gf1.dimensions() * dvs.dimensions());
		tnbLib::outer(tRes(), gf1, dvs);
		reuseTmpGeometricField<productType, Type, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Form, Type>::type, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return tgf1 * dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void outer(GeometricField<typename outerProduct<Form, Type>::type, PatchField, GeoMesh>& gf,
	           const dimensioned<Form>& dvs, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		tnbLib::outer(gf.internalField(), dvs.value(), gf1.internalField());
		tnbLib::outer(gf.boundaryField(), dvs.value(), gf1.boundaryField());
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Form, Type>::type, PatchField, GeoMesh>> operator *(
		const dimensioned<Form>& dvs, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		typedef typename outerProduct<Form, Type>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(new GeometricField<productType, PatchField, GeoMesh>(
			IOobject('(' + dvs.name() + "*" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), dvs.dimensions() * gf1.dimensions()));
		tnbLib::outer(tRes(), dvs, gf1);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Form, Type>::type, PatchField, GeoMesh>> operator *(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) * gf1;
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Form, Type>::type, PatchField, GeoMesh>> operator *(
		const dimensioned<Form>& dvs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		typedef typename outerProduct<Form, Type>::type productType;
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type, PatchField, GeoMesh>::New(tgf1, '(' + dvs.name() + "*" + gf1.name() + ')',
			                                             dvs.dimensions() * gf1.dimensions());
		tnbLib::outer(tRes(), dvs, gf1);
		reuseTmpGeometricField<productType, Type, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Form, Type>::type, PatchField, GeoMesh>> operator *(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) * tgf1;
	}
		
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	void cross(GeometricField<typename crossProduct<Type1, Type2>::type, PatchField, GeoMesh>& gf,
	           const GeometricField<Type1, PatchField, GeoMesh>& gf1,
	           const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::cross(gf.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::cross(gf.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator ^(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		typedef typename crossProduct<Type1, Type2>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(new GeometricField<productType, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + "^" + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() ^ gf2.dimensions()));
		tnbLib::cross(tRes(), gf1, gf2);
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator ^(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2)
	{
		typedef typename crossProduct<Type1, Type2>::type productType;
		const GeometricField<Type2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type2, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + "^" + gf2.name() + ')',
			                                              gf1.dimensions() ^ gf2.dimensions());
		tnbLib::cross(tRes(), gf1, gf2);
		reuseTmpGeometricField<productType, Type2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator ^(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		typedef typename crossProduct<Type1, Type2>::type productType;
		const GeometricField<Type1, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type1, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + "^" + gf2.name() + ')',
			                                              gf1.dimensions() ^ gf2.dimensions());
		tnbLib::cross(tRes(), gf1, gf2);
		reuseTmpGeometricField<productType, Type1, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator ^(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2)
	{
		typedef typename crossProduct<Type1, Type2>::type productType;
		const GeometricField<Type1, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<Type2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpTmpGeometricField<
			productType, Type1, Type1, Type2, PatchField, GeoMesh>::New(tgf1, tgf2, '(' + gf1.name() + "^" + gf2.name() + ')',
			                                                            gf1.dimensions() ^ gf2.dimensions());
		tnbLib::cross(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<productType, Type1, Type1, Type2, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void cross(GeometricField<typename crossProduct<Type, Form>::type, PatchField, GeoMesh>& gf,
	           const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs)
	{
		tnbLib::cross(gf.internalField(), gf1.internalField(), dvs.value());
		tnbLib::cross(gf.boundaryField(), gf1.boundaryField(), dvs.value());
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Type, Form>::type, PatchField, GeoMesh>> operator ^(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs)
	{
		typedef typename crossProduct<Type, Form>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(new GeometricField<productType, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + "^" + dvs.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() ^ dvs.dimensions()));
		tnbLib::cross(tRes(), gf1, dvs);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Form, Type>::type, PatchField, GeoMesh>> operator ^(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return gf1 ^ dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Type, Form>::type, PatchField, GeoMesh>> operator ^(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const dimensioned<Form>& dvs)
	{
		typedef typename crossProduct<Type, Form>::type productType;
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + "^" + dvs.name() + ')',
			                                             gf1.dimensions() ^ dvs.dimensions());
		tnbLib::cross(tRes(), gf1, dvs);
		reuseTmpGeometricField<productType, Type, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Form, Type>::type, PatchField, GeoMesh>> operator ^(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return tgf1 ^ dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void cross(GeometricField<typename crossProduct<Form, Type>::type, PatchField, GeoMesh>& gf,
	           const dimensioned<Form>& dvs, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		tnbLib::cross(gf.internalField(), dvs.value(), gf1.internalField());
		tnbLib::cross(gf.boundaryField(), dvs.value(), gf1.boundaryField());
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Form, Type>::type, PatchField, GeoMesh>> operator ^(
		const dimensioned<Form>& dvs, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		typedef typename crossProduct<Form, Type>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(new GeometricField<productType, PatchField, GeoMesh>(
			IOobject('(' + dvs.name() + "^" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), dvs.dimensions() ^ gf1.dimensions()));
		tnbLib::cross(tRes(), dvs, gf1);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Form, Type>::type, PatchField, GeoMesh>> operator ^(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) ^ gf1;
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Form, Type>::type, PatchField, GeoMesh>> operator ^(
		const dimensioned<Form>& dvs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		typedef typename crossProduct<Form, Type>::type productType;
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type, PatchField, GeoMesh>::New(tgf1, '(' + dvs.name() + "^" + gf1.name() + ')',
			                                             dvs.dimensions() ^ gf1.dimensions());
		tnbLib::cross(tRes(), dvs, gf1);
		reuseTmpGeometricField<productType, Type, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Form, Type>::type, PatchField, GeoMesh>> operator ^(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) ^ tgf1;
	}
		
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	void dot(GeometricField<typename innerProduct<Type1, Type2>::type, PatchField, GeoMesh>& gf,
	         const GeometricField<Type1, PatchField, GeoMesh>& gf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::dot(gf.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::dot(gf.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator &(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		typedef typename innerProduct<Type1, Type2>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(new GeometricField<productType, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + "&" + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() & gf2.dimensions()));
		tnbLib::dot(tRes(), gf1, gf2);
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator &(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2)
	{
		typedef typename innerProduct<Type1, Type2>::type productType;
		const GeometricField<Type2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type2, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + "&" + gf2.name() + ')',
			                                              gf1.dimensions() & gf2.dimensions());
		tnbLib::dot(tRes(), gf1, gf2);
		reuseTmpGeometricField<productType, Type2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator &(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		typedef typename innerProduct<Type1, Type2>::type productType;
		const GeometricField<Type1, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type1, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + "&" + gf2.name() + ')',
			                                              gf1.dimensions() & gf2.dimensions());
		tnbLib::dot(tRes(), gf1, gf2);
		reuseTmpGeometricField<productType, Type1, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator &(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2)
	{
		typedef typename innerProduct<Type1, Type2>::type productType;
		const GeometricField<Type1, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<Type2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpTmpGeometricField<
			productType, Type1, Type1, Type2, PatchField, GeoMesh>::New(tgf1, tgf2, '(' + gf1.name() + "&" + gf2.name() + ')',
			                                                            gf1.dimensions() & gf2.dimensions());
		tnbLib::dot(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<productType, Type1, Type1, Type2, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void dot(GeometricField<typename innerProduct<Type, Form>::type, PatchField, GeoMesh>& gf,
	         const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs)
	{
		tnbLib::dot(gf.internalField(), gf1.internalField(), dvs.value());
		tnbLib::dot(gf.boundaryField(), gf1.boundaryField(), dvs.value());
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Type, Form>::type, PatchField, GeoMesh>> operator &(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs)
	{
		typedef typename innerProduct<Type, Form>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(new GeometricField<productType, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + "&" + dvs.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() & dvs.dimensions()));
		tnbLib::dot(tRes(), gf1, dvs);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Form, Type>::type, PatchField, GeoMesh>> operator &(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return gf1 & dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Type, Form>::type, PatchField, GeoMesh>> operator &(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const dimensioned<Form>& dvs)
	{
		typedef typename innerProduct<Type, Form>::type productType;
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + "&" + dvs.name() + ')',
			                                             gf1.dimensions() & dvs.dimensions());
		tnbLib::dot(tRes(), gf1, dvs);
		reuseTmpGeometricField<productType, Type, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Form, Type>::type, PatchField, GeoMesh>> operator &(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return tgf1 & dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void dot(GeometricField<typename innerProduct<Form, Type>::type, PatchField, GeoMesh>& gf,
	         const dimensioned<Form>& dvs, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		tnbLib::dot(gf.internalField(), dvs.value(), gf1.internalField());
		tnbLib::dot(gf.boundaryField(), dvs.value(), gf1.boundaryField());
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Form, Type>::type, PatchField, GeoMesh>> operator &(
		const dimensioned<Form>& dvs, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		typedef typename innerProduct<Form, Type>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(new GeometricField<productType, PatchField, GeoMesh>(
			IOobject('(' + dvs.name() + "&" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), dvs.dimensions() & gf1.dimensions()));
		tnbLib::dot(tRes(), dvs, gf1);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Form, Type>::type, PatchField, GeoMesh>> operator &(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) & gf1;
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Form, Type>::type, PatchField, GeoMesh>> operator &(
		const dimensioned<Form>& dvs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		typedef typename innerProduct<Form, Type>::type productType;
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type, PatchField, GeoMesh>::New(tgf1, '(' + dvs.name() + "&" + gf1.name() + ')',
			                                             dvs.dimensions() & gf1.dimensions());
		tnbLib::dot(tRes(), dvs, gf1);
		reuseTmpGeometricField<productType, Type, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Form, Type>::type, PatchField, GeoMesh>> operator &(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) & tgf1;
	}
		
	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	void dotdot(GeometricField<typename scalarProduct<Type1, Type2>::type, PatchField, GeoMesh>& gf,
	            const GeometricField<Type1, PatchField, GeoMesh>& gf1,
	            const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::dotdot(gf.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::dotdot(gf.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator &&(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		typedef typename scalarProduct<Type1, Type2>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(new GeometricField<productType, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + "&&" + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ,
			         IOobject::NO_WRITE), gf1.mesh(), gf1.dimensions() && gf2.dimensions()));
		tnbLib::dotdot(tRes(), gf1, gf2);
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator &&(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2)
	{
		typedef typename scalarProduct<Type1, Type2>::type productType;
		const GeometricField<Type2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type2, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + "&&" + gf2.name() + ')',
			                                              gf1.dimensions() && gf2.dimensions());
		tnbLib::dotdot(tRes(), gf1, gf2);
		reuseTmpGeometricField<productType, Type2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator &&(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		typedef typename scalarProduct<Type1, Type2>::type productType;
		const GeometricField<Type1, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type1, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + "&&" + gf2.name() + ')',
			                                              gf1.dimensions() && gf2.dimensions());
		tnbLib::dotdot(tRes(), gf1, gf2);
		reuseTmpGeometricField<productType, Type1, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator &&(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2)
	{
		typedef typename scalarProduct<Type1, Type2>::type productType;
		const GeometricField<Type1, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<Type2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpTmpGeometricField<
			productType, Type1, Type1, Type2, PatchField, GeoMesh>::New(tgf1, tgf2, '(' + gf1.name() + "&&" + gf2.name() + ')',
			                                                            gf1.dimensions() && gf2.dimensions());
		tnbLib::dotdot(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<productType, Type1, Type1, Type2, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void dotdot(GeometricField<typename scalarProduct<Type, Form>::type, PatchField, GeoMesh>& gf,
	            const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs)
	{
		tnbLib::dotdot(gf.internalField(), gf1.internalField(), dvs.value());
		tnbLib::dotdot(gf.boundaryField(), gf1.boundaryField(), dvs.value());
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Type, Form>::type, PatchField, GeoMesh>> operator &&(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs)
	{
		typedef typename scalarProduct<Type, Form>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(new GeometricField<productType, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + "&&" + dvs.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ,
			         IOobject::NO_WRITE), gf1.mesh(), gf1.dimensions() && dvs.dimensions()));
		tnbLib::dotdot(tRes(), gf1, dvs);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Form, Type>::type, PatchField, GeoMesh>> operator &&(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return gf1 && dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Type, Form>::type, PatchField, GeoMesh>> operator &&(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const dimensioned<Form>& dvs)
	{
		typedef typename scalarProduct<Type, Form>::type productType;
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + "&&" + dvs.name() + ')',
			                                             gf1.dimensions() && dvs.dimensions());
		tnbLib::dotdot(tRes(), gf1, dvs);
		reuseTmpGeometricField<productType, Type, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Form, Type>::type, PatchField, GeoMesh>> operator &&(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return tgf1 && dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void dotdot(GeometricField<typename scalarProduct<Form, Type>::type, PatchField, GeoMesh>& gf,
	            const dimensioned<Form>& dvs, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		tnbLib::dotdot(gf.internalField(), dvs.value(), gf1.internalField());
		tnbLib::dotdot(gf.boundaryField(), dvs.value(), gf1.boundaryField());
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Form, Type>::type, PatchField, GeoMesh>> operator &&(
		const dimensioned<Form>& dvs, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		typedef typename scalarProduct<Form, Type>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(new GeometricField<productType, PatchField, GeoMesh>(
			IOobject('(' + dvs.name() + "&&" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ,
			         IOobject::NO_WRITE), gf1.mesh(), dvs.dimensions() && gf1.dimensions()));
		tnbLib::dotdot(tRes(), dvs, gf1);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Form, Type>::type, PatchField, GeoMesh>> operator &&(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) && gf1;
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Form, Type>::type, PatchField, GeoMesh>> operator &&(
		const dimensioned<Form>& dvs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		typedef typename scalarProduct<Form, Type>::type productType;
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type, PatchField, GeoMesh>::New(tgf1, '(' + dvs.name() + "&&" + gf1.name() + ')',
			                                             dvs.dimensions() && gf1.dimensions());
		tnbLib::dotdot(tRes(), dvs, gf1);
		reuseTmpGeometricField<productType, Type, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <class Form, class Cmpt, int nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Form, Type>::type, PatchField, GeoMesh>> operator &&(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) && tgf1;
	}

#undef PRODUCT_OPERATOR


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <undefFieldFunctionsM.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
