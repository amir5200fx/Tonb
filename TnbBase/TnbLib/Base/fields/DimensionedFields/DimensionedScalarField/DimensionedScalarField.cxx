#include <DimensionedScalarField.hxx>

#include <DimensionedFieldReuseFunctions.hxx>

#define TEMPLATE template<class GeoMesh>
#include <DimensionedFieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh> > stabilise
	(
		const DimensionedField<scalar, GeoMesh>& dsf,
		const dimensioned<scalar>& ds
	)
	{
		tmp<DimensionedField<scalar, GeoMesh> > tRes
		(
			new DimensionedField<scalar, GeoMesh>
			(
				IOobject
				(
					"stabilise(" + dsf.name() + ',' + ds.name() + ')',
					dsf.instance(),
					dsf.db()
				),
				dsf.mesh(),
				dsf.dimensions() + ds.dimensions()
				)
		);

		stabilise(tRes().field(), dsf.field(), ds.value());

		return tRes;
	}


	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh> > stabilise
	(
		const tmp<DimensionedField<scalar, GeoMesh> >& tdsf,
		const dimensioned<scalar>& ds
	)
	{
		const DimensionedField<scalar, GeoMesh>& dsf = tdsf();

		tmp<DimensionedField<scalar, GeoMesh> > tRes =
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New
			(
				tdsf,
				"stabilise(" + dsf.name() + ',' + ds.name() + ')',
				dsf.dimensions() + ds.dimensions()
			);

		stabilise(tRes().field(), dsf.field(), ds.value());

		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdsf);

		return tRes;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator +(const dimensioned<scalar>& dt1
	                                                  , const DimensionedField<scalar, GeoMesh>& df2)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator +(const scalar& t1, const DimensionedField<scalar, GeoMesh>& df2)
	{
		return dimensioned<scalar>(t1) + df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator +(const dimensioned<scalar>& dt1
	                                                  , const tmp<DimensionedField<scalar, GeoMesh>>& tdf2)
	{
		const DimensionedField<scalar, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf2, '(' + dt1.name() + '+' + df2.name() + ')'
			                                                       , dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator +(const scalar& t1, const tmp<DimensionedField<scalar, GeoMesh>>& tdf2)
	{
		return dimensioned<scalar>(t1) + tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator +(const DimensionedField<scalar, GeoMesh>& df1
	                                                  , const dimensioned<scalar>& dt2)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject('(' + df1.name() + '+' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator +(const DimensionedField<scalar, GeoMesh>& df1, const scalar& t2)
	{
		return df1 + dimensioned<scalar>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator +(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                  , const dimensioned<scalar>& dt2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + dt2.name() + ')'
			                                                       , df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator +(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1, const scalar& t2)
	{
		return tdf1 + dimensioned<scalar>(t2);
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator -(const dimensioned<scalar>& dt1
	                                                  , const DimensionedField<scalar, GeoMesh>& df2)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator -(const scalar& t1, const DimensionedField<scalar, GeoMesh>& df2)
	{
		return dimensioned<scalar>(t1) - df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator -(const dimensioned<scalar>& dt1
	                                                  , const tmp<DimensionedField<scalar, GeoMesh>>& tdf2)
	{
		const DimensionedField<scalar, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf2, '(' + dt1.name() + '-' + df2.name() + ')'
			                                                       , dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator -(const scalar& t1, const tmp<DimensionedField<scalar, GeoMesh>>& tdf2)
	{
		return dimensioned<scalar>(t1) - tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator -(const DimensionedField<scalar, GeoMesh>& df1
	                                                  , const dimensioned<scalar>& dt2)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject('(' + df1.name() + '-' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator -(const DimensionedField<scalar, GeoMesh>& df1, const scalar& t2)
	{
		return df1 - dimensioned<scalar>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator -(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                  , const dimensioned<scalar>& dt2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '-' + dt2.name() + ')'
			                                                       , df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator -(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1, const scalar& t2)
	{
		return tdf1 - dimensioned<scalar>(t2);
	}

		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator *(const DimensionedField<scalar, GeoMesh>& df1
	                                                  , const DimensionedField<scalar, GeoMesh>& df2)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject('(' + df1.name() + '*' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() * df2.dimensions()));
		tnbLib::multiply(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator *(const DimensionedField<scalar, GeoMesh>& df1
	                                                  , const tmp<DimensionedField<scalar, GeoMesh>>& tdf2)
	{
		const DimensionedField<scalar, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf2, '(' + df1.name() + '*' + df2.name() + ')'
			                                                       , df1.dimensions() * df2.dimensions()));
		tnbLib::multiply(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator *(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                  , const DimensionedField<scalar, GeoMesh>& df2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '*' + df2.name() + ')'
			                                                       , df1.dimensions() * df2.dimensions()));
		tnbLib::multiply(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator *(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                  , const tmp<DimensionedField<scalar, GeoMesh>>& tdf2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		const DimensionedField<scalar, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<scalar, scalar, scalar, scalar, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '*' + df2.name() + ')', df1.dimensions() * df2.dimensions()));
		tnbLib::multiply(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<scalar, scalar, scalar, scalar, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                  , const DimensionedField<scalar, GeoMesh>& df2)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                  , const tmp<DimensionedField<scalar, GeoMesh>>& tdf2)
	{
		const DimensionedField<scalar, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf2, '(' + df1.name() + '|' + df2.name() + ')'
			                                                       , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                  , const DimensionedField<scalar, GeoMesh>& df2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + df2.name() + ')'
			                                                       , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                  , const tmp<DimensionedField<scalar, GeoMesh>>& tdf2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		const DimensionedField<scalar, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<scalar, scalar, scalar, scalar, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<scalar, scalar, scalar, scalar, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator /(const dimensioned<scalar>& dt1
	                                                  , const DimensionedField<scalar, GeoMesh>& df2)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator /(const scalar& t1, const DimensionedField<scalar, GeoMesh>& df2)
	{
		return dimensioned<scalar>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator /(const dimensioned<scalar>& dt1
	                                                  , const tmp<DimensionedField<scalar, GeoMesh>>& tdf2)
	{
		const DimensionedField<scalar, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf2, '(' + dt1.name() + '|' + df2.name() + ')'
			                                                       , dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator /(const scalar& t1, const tmp<DimensionedField<scalar, GeoMesh>>& tdf2)
	{
		return dimensioned<scalar>(t1) / tdf2;
	}

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh> > pow
	(
		const DimensionedField<scalar, GeoMesh>& dsf1,
		const DimensionedField<scalar, GeoMesh>& dsf2
	)
	{
		tmp<DimensionedField<scalar, GeoMesh> > tPow
		(
			new DimensionedField<scalar, GeoMesh>
			(
				IOobject
				(
					"pow(" + dsf1.name() + ',' + dsf2.name() + ')',
					dsf1.instance(),
					dsf1.db()
				),
				dsf1.mesh(),
				pow
				(
					dsf1.dimensions(),
					dimensionedScalar("1", 1.0, dsf2.dimensions())
				)
				)
		);

		pow(tPow().field(), dsf1.field(), dsf2.field());

		return tPow;
	}


	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh> > pow
	(
		const tmp<DimensionedField<scalar, GeoMesh> >& tdsf1,
		const DimensionedField<scalar, GeoMesh>& dsf2
	)
	{
		const DimensionedField<scalar, GeoMesh>& dsf1 = tdsf1();

		tmp<DimensionedField<scalar, GeoMesh> > tPow =
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New
			(
				tdsf1,
				"pow(" + dsf1.name() + ',' + dsf2.name() + ')',
				pow
				(
					dsf1.dimensions(),
					dimensionedScalar("1", 1.0, dsf2.dimensions())
				)
			);

		pow(tPow().field(), dsf1.field(), dsf2.field());

		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdsf1);

		return tPow;
	}


	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh> > pow
	(
		const DimensionedField<scalar, GeoMesh>& dsf1,
		const tmp<DimensionedField<scalar, GeoMesh> >& tdsf2
	)
	{
		const DimensionedField<scalar, GeoMesh>& dsf2 = tdsf2();

		tmp<DimensionedField<scalar, GeoMesh> > tPow =
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New
			(
				tdsf2,
				"pow(" + dsf1.name() + ',' + dsf2.name() + ')',
				pow
				(
					dsf1.dimensions(),
					dimensionedScalar("1", 1.0, dsf2.dimensions())
				)
			);

		pow(tPow().field(), dsf1.field(), dsf2.field());

		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdsf2);

		return tPow;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh> > pow
	(
		const tmp<DimensionedField<scalar, GeoMesh> >& tdsf1,
		const tmp<DimensionedField<scalar, GeoMesh> >& tdsf2
	)
	{
		const DimensionedField<scalar, GeoMesh>& dsf1 = tdsf1();
		const DimensionedField<scalar, GeoMesh>& dsf2 = tdsf2();

		tmp<DimensionedField<scalar, GeoMesh> > tPow =
			reuseTmpTmpDimensionedField<scalar, scalar, scalar, scalar, GeoMesh>::
			New
			(
				tdsf1,
				tdsf2,
				"pow(" + dsf1.name() + ',' + dsf2.name() + ')',
				pow
				(
					dsf1.dimensions(),
					dimensionedScalar("1", 1.0, dsf2.dimensions())
				)
			);

		pow(tPow().field(), dsf1.field(), dsf2.field());

		reuseTmpTmpDimensionedField<scalar, scalar, scalar, scalar, GeoMesh>::clear
		(
			tdsf1,
			tdsf2
		);

		return tPow;
	}


	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh> > pow
	(
		const DimensionedField<scalar, GeoMesh>& dsf,
		const dimensionedScalar& ds
	)
	{
		tmp<DimensionedField<scalar, GeoMesh> > tPow
		(
			new DimensionedField<scalar, GeoMesh>
			(
				IOobject
				(
					"pow(" + dsf.name() + ',' + ds.name() + ')',
					dsf.instance(),
					dsf.db()
				),
				dsf.mesh(),
				pow(dsf.dimensions(), ds)
				)
		);

		pow(tPow().field(), dsf.field(), ds.value());

		return tPow;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh> > pow
	(
		const tmp<DimensionedField<scalar, GeoMesh> >& tdsf,
		const dimensionedScalar& ds
	)
	{
		const DimensionedField<scalar, GeoMesh>& dsf = tdsf();

		tmp<DimensionedField<scalar, GeoMesh> > tPow =
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New
			(
				tdsf,
				"pow(" + dsf.name() + ',' + ds.name() + ')',
				pow(dsf.dimensions(), ds)
			);

		pow(tPow().field(), dsf.field(), ds.value());

		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdsf);

		return tPow;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh> > pow
	(
		const DimensionedField<scalar, GeoMesh>& dsf,
		const scalar& s
	)
	{
		return pow(dsf, dimensionedScalar(s));
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh> > pow
	(
		const tmp<DimensionedField<scalar, GeoMesh> >& tdsf,
		const scalar& s
	)
	{
		return pow(tdsf, dimensionedScalar(s));
	}


	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh> > pow
	(
		const dimensionedScalar& ds,
		const DimensionedField<scalar, GeoMesh>& dsf
	)
	{
		tmp<DimensionedField<scalar, GeoMesh> > tPow
		(
			new DimensionedField<scalar, GeoMesh>
			(
				IOobject
				(
					"pow(" + ds.name() + ',' + dsf.name() + ')',
					dsf.instance(),
					dsf.db()
				),
				dsf.mesh(),
				pow(ds, dsf.dimensions())
				)
		);

		pow(tPow().field(), ds.value(), dsf.field());

		return tPow;
	}


	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh> > pow
	(
		const dimensionedScalar& ds,
		const tmp<DimensionedField<scalar, GeoMesh> >& tdsf
	)
	{
		const DimensionedField<scalar, GeoMesh>& dsf = tdsf();

		tmp<DimensionedField<scalar, GeoMesh> > tPow =
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New
			(
				tdsf,
				"pow(" + ds.name() + ',' + dsf.name() + ')',
				pow(ds, dsf.dimensions())
			);

		pow(tPow().field(), ds.value(), dsf.field());

		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdsf);

		return tPow;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh> > pow
	(
		const scalar& s,
		const DimensionedField<scalar, GeoMesh>& dsf
	)
	{
		return pow(dimensionedScalar(s), dsf);
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh> > pow
	(
		const scalar& s,
		const tmp<DimensionedField<scalar, GeoMesh> >& tdsf
	)
	{
		return pow(dimensionedScalar(s), tdsf);
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow3(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("pow3" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), pow3(df1.dimensions())));
		pow3(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow3(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "pow3" "(" + df1.name() + ')', pow3(df1.dimensions())));
		pow3(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow4(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("pow4" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), pow4(df1.dimensions())));
		pow4(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow4(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "pow4" "(" + df1.name() + ')', pow4(df1.dimensions())));
		pow4(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow5(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("pow5" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), pow5(df1.dimensions())));
		pow5(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow5(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "pow5" "(" + df1.name() + ')', pow5(df1.dimensions())));
		pow5(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow6(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("pow6" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), pow6(df1.dimensions())));
		pow6(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow6(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "pow6" "(" + df1.name() + ')', pow6(df1.dimensions())));
		pow6(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> sqrt(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("sqrt" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), sqrt(df1.dimensions())));
		sqrt(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> sqrt(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "sqrt" "(" + df1.name() + ')', sqrt(df1.dimensions())));
		sqrt(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> sign(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("sign" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), sign(df1.dimensions())));
		sign(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> sign(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "sign" "(" + df1.name() + ')', sign(df1.dimensions())));
		sign(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pos(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("pos" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), pos(df1.dimensions())));
		pos(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pos(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "pos" "(" + df1.name() + ')', pos(df1.dimensions())));
		pos(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> neg(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("neg" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), neg(df1.dimensions())));
		neg(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> neg(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "neg" "(" + df1.name() + ')', neg(df1.dimensions())));
		neg(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> exp(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("exp" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), trans(df1.dimensions())));
		exp(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> exp(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "exp" "(" + df1.name() + ')', trans(df1.dimensions())));
		exp(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> log(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("log" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), trans(df1.dimensions())));
		log(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> log(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "log" "(" + df1.name() + ')', trans(df1.dimensions())));
		log(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> log10(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("log10" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), trans(df1.dimensions())));
		log10(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> log10(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::
			New(tdf1, "log10" "(" + df1.name() + ')', trans(df1.dimensions())));
		log10(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> sin(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("sin" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), trans(df1.dimensions())));
		sin(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> sin(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "sin" "(" + df1.name() + ')', trans(df1.dimensions())));
		sin(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> cos(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("cos" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), trans(df1.dimensions())));
		cos(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> cos(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "cos" "(" + df1.name() + ')', trans(df1.dimensions())));
		cos(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> tan(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("tan" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), trans(df1.dimensions())));
		tan(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> tan(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "tan" "(" + df1.name() + ')', trans(df1.dimensions())));
		tan(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> asin(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("asin" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), trans(df1.dimensions())));
		asin(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> asin(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "asin" "(" + df1.name() + ')'
			                                                       , trans(df1.dimensions())));
		asin(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> acos(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("acos" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), trans(df1.dimensions())));
		acos(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> acos(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "acos" "(" + df1.name() + ')'
			                                                       , trans(df1.dimensions())));
		acos(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atan(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("atan" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), trans(df1.dimensions())));
		atan(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atan(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "atan" "(" + df1.name() + ')'
			                                                       , trans(df1.dimensions())));
		atan(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> sinh(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("sinh" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), trans(df1.dimensions())));
		sinh(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> sinh(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "sinh" "(" + df1.name() + ')'
			                                                       , trans(df1.dimensions())));
		sinh(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> cosh(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("cosh" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), trans(df1.dimensions())));
		cosh(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> cosh(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "cosh" "(" + df1.name() + ')'
			                                                       , trans(df1.dimensions())));
		cosh(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> tanh(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("tanh" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), trans(df1.dimensions())));
		tanh(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> tanh(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "tanh" "(" + df1.name() + ')'
			                                                       , trans(df1.dimensions())));
		tanh(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> asinh(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("asinh" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), trans(df1.dimensions())));
		asinh(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> asinh(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::
			New(tdf1, "asinh" "(" + df1.name() + ')', trans(df1.dimensions())));
		asinh(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> acosh(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("acosh" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), trans(df1.dimensions())));
		acosh(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> acosh(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::
			New(tdf1, "acosh" "(" + df1.name() + ')', trans(df1.dimensions())));
		acosh(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atanh(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("atanh" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), trans(df1.dimensions())));
		atanh(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atanh(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::
			New(tdf1, "atanh" "(" + df1.name() + ')', trans(df1.dimensions())));
		atanh(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> erf(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("erf" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), trans(df1.dimensions())));
		erf(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> erf(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "erf" "(" + df1.name() + ')', trans(df1.dimensions())));
		erf(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> erfc(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("erfc" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), trans(df1.dimensions())));
		erfc(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> erfc(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "erfc" "(" + df1.name() + ')'
			                                                       , trans(df1.dimensions())));
		erfc(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> lgamma(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("lgamma" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), trans(df1.dimensions())));
		lgamma(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> lgamma(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "lgamma" "(" + df1.name() + ')'
			                                                       , trans(df1.dimensions())));
		lgamma(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> j0(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("j0" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), trans(df1.dimensions())));
		j0(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> j0(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "j0" "(" + df1.name() + ')', trans(df1.dimensions())));
		j0(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> j1(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("j1" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), trans(df1.dimensions())));
		j1(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> j1(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "j1" "(" + df1.name() + ')', trans(df1.dimensions())));
		j1(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> y0(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("y0" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), trans(df1.dimensions())));
		y0(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> y0(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "y0" "(" + df1.name() + ')', trans(df1.dimensions())));
		y0(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> y1(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("y1" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), trans(df1.dimensions())));
		y1(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> y1(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "y1" "(" + df1.name() + ')', trans(df1.dimensions())));
		y1(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define BesselFunc(func)                                                    \
                                                                            \
template<class GeoMesh>                                                     \
tmp<DimensionedField<scalar, GeoMesh> > func                                \
(                                                                           \
    const int n,                                                            \
    const DimensionedField<scalar, GeoMesh>& dsf                            \
)                                                                           \
{                                                                           \
    if (!dsf.dimensions().dimensionless())                                  \
    {                                                                       \
        FatalErrorIn                                                        \
        (                                                                   \
            #func"(const int n, "                                           \
            "const DimensionedField<scalar, GeoMesh>& dsf)"                 \
        )   << "dsf not dimensionless"                                      \
            << abort(FatalError);                                           \
    }                                                                       \
                                                                            \
    tmp<DimensionedField<scalar, GeoMesh> > tFunc                           \
    (                                                                       \
        new DimensionedField<scalar, GeoMesh>                               \
        (                                                                   \
            IOobject                                                        \
            (                                                               \
                #func "(" + name(n) + ',' + dsf.name() + ')',               \
                dsf.instance(),                                             \
                dsf.db()                                                    \
            ),                                                              \
            dsf.mesh(),                                                     \
            dimless                                                         \
        )                                                                   \
    );                                                                      \
                                                                            \
    func(tFunc().field(), n, dsf.field());                                  \
                                                                            \
    return tFunc;                                                           \
}                                                                           \
                                                                            \
template<class GeoMesh>                                                     \
tmp<DimensionedField<scalar, GeoMesh> > func                                \
(                                                                           \
    const int n,                                                            \
    const tmp<DimensionedField<scalar, GeoMesh> >& tdsf                     \
)                                                                           \
{                                                                           \
    const DimensionedField<scalar, GeoMesh>& dsf = tdsf();                  \
                                                                            \
    if (!dsf.dimensions().dimensionless())                                  \
    {                                                                       \
        FatalErrorIn                                                        \
        (                                                                   \
            #func"(const int n, "                                           \
            "const tmp<DimensionedField<scalar, GeoMesh> >& dsf)"           \
        )   << " : dsf not dimensionless"                                   \
            << abort(FatalError);                                           \
    }                                                                       \
                                                                            \
    tmp<DimensionedField<scalar, GeoMesh> > tFunc                           \
    (                                                                       \
        reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New              \
        (                                                                   \
            tdsf,                                                           \
            #func "(" + name(n) + ',' + dsf.name() + ')',                   \
            dimless                                                         \
        )                                                                   \
    );                                                                      \
                                                                            \
    func(tFunc().field(), n, dsf.field());                                  \
                                                                            \
    reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdsf);         \
                                                                            \
    return tFunc;                                                           \
}

		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> jn(const int n, const DimensionedField<scalar, GeoMesh>& dsf)
	{
		if (!dsf.dimensions().dimensionless())
		{
			FatalErrorIn ( "jn""(const int n, " "const DimensionedField<scalar, GeoMesh>& dsf)" ) << "dsf not dimensionless" <<
				abort(FatalError);
		}
		tmp<DimensionedField<scalar, GeoMesh>> tFunc(new DimensionedField<scalar, GeoMesh>(
			IOobject("jn" "(" + name(n) + ',' + dsf.name() + ')', dsf.instance(), dsf.db()), dsf.mesh(), dimless));
		jn(tFunc().field(), n, dsf.field());
		return tFunc;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> jn(const int n, const tmp<DimensionedField<scalar, GeoMesh>>& tdsf)
	{
		const DimensionedField<scalar, GeoMesh>& dsf = tdsf();
		if (!dsf.dimensions().dimensionless())
		{
			FatalErrorIn ( "jn""(const int n, " "const tmp<DimensionedField<scalar, GeoMesh> >& dsf)" ) <<
				" : dsf not dimensionless" << abort(FatalError);
		}
		tmp<DimensionedField<scalar, GeoMesh>> tFunc(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdsf, "jn" "(" + name(n) + ',' + dsf.name() + ')', dimless));
		jn(tFunc().field(), n, dsf.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdsf);
		return tFunc;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> yn(const int n, const DimensionedField<scalar, GeoMesh>& dsf)
	{
		if (!dsf.dimensions().dimensionless())
		{
			FatalErrorIn ( "yn""(const int n, " "const DimensionedField<scalar, GeoMesh>& dsf)" ) << "dsf not dimensionless" <<
				abort(FatalError);
		}
		tmp<DimensionedField<scalar, GeoMesh>> tFunc(new DimensionedField<scalar, GeoMesh>(
			IOobject("yn" "(" + name(n) + ',' + dsf.name() + ')', dsf.instance(), dsf.db()), dsf.mesh(), dimless));
		yn(tFunc().field(), n, dsf.field());
		return tFunc;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> yn(const int n, const tmp<DimensionedField<scalar, GeoMesh>>& tdsf)
	{
		const DimensionedField<scalar, GeoMesh>& dsf = tdsf();
		if (!dsf.dimensions().dimensionless())
		{
			FatalErrorIn ( "yn""(const int n, " "const tmp<DimensionedField<scalar, GeoMesh> >& dsf)" ) <<
				" : dsf not dimensionless" << abort(FatalError);
		}
		tmp<DimensionedField<scalar, GeoMesh>> tFunc(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdsf, "yn" "(" + name(n) + ',' + dsf.name() + ')', dimless));
		yn(tFunc().field(), n, dsf.field());
		reuseTmpDimensionedField<scalar, scalar, GeoMesh>::clear(tdsf);
		return tFunc;
	}

#undef BesselFunc


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <undefFieldFunctionsM.hxx>