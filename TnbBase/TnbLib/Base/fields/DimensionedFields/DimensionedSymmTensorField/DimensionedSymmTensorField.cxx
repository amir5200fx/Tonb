#include <DimensionedSymmTensorField.hxx>

#include <DimensionedFieldReuseFunctions.hxx>
#include <symmTensorField.hxx>

#define TEMPLATE template<class GeoMesh>
#include <DimensionedFieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> sqr(const DimensionedField<vector, GeoMesh>& df1)
	{
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(new DimensionedField<symmTensor, GeoMesh>(
			IOobject("sqr" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), transform(df1.dimensions())));
		sqr(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> sqr(const tmp<DimensionedField<vector, GeoMesh>>& tdf1)
	{
		const DimensionedField<vector, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<symmTensor, vector, GeoMesh>::New(tdf1, "sqr" "(" + df1.name() + ')'
			                                                           , transform(df1.dimensions())));
		sqr(tRes().field(), df1.field());
		reuseTmpDimensionedField<symmTensor, vector, GeoMesh>::clear(tdf1);
		return tRes;
	}

		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> tr(const DimensionedField<symmTensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("tr" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), transform(df1.dimensions())));
		tr(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> tr(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<symmTensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, symmTensor, GeoMesh>::New(tdf1, "tr" "(" + df1.name() + ')'
			                                                           , transform(df1.dimensions())));
		tr(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, symmTensor, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> sph(const DimensionedField<symmTensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<sphericalTensor, GeoMesh>> tRes(new DimensionedField<sphericalTensor, GeoMesh>(
			IOobject("sph" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), transform(df1.dimensions())));
		sph(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> sph(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<symmTensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor, symmTensor, GeoMesh>::New(tdf1, "sph" "(" + df1.name() + ')'
			                                                                    , transform(df1.dimensions())));
		sph(tRes().field(), df1.field());
		reuseTmpDimensionedField<sphericalTensor, symmTensor, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> symm(const DimensionedField<symmTensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(new DimensionedField<symmTensor, GeoMesh>(
			IOobject("symm" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), transform(df1.dimensions())));
		symm(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> symm(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<symmTensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<symmTensor, symmTensor, GeoMesh>::New(tdf1, "symm" "(" + df1.name() + ')'
			                                                               , transform(df1.dimensions())));
		symm(tRes().field(), df1.field());
		reuseTmpDimensionedField<symmTensor, symmTensor, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> twoSymm(const DimensionedField<symmTensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(new DimensionedField<symmTensor, GeoMesh>(
			IOobject("twoSymm" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), transform(df1.dimensions())));
		twoSymm(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> twoSymm(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<symmTensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<symmTensor, symmTensor, GeoMesh>::New(tdf1, "twoSymm" "(" + df1.name() + ')'
			                                                               , transform(df1.dimensions())));
		twoSymm(tRes().field(), df1.field());
		reuseTmpDimensionedField<symmTensor, symmTensor, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> dev(const DimensionedField<symmTensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(new DimensionedField<symmTensor, GeoMesh>(
			IOobject("dev" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), transform(df1.dimensions())));
		dev(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> dev(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<symmTensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<symmTensor, symmTensor, GeoMesh>::New(tdf1, "dev" "(" + df1.name() + ')'
			                                                               , transform(df1.dimensions())));
		dev(tRes().field(), df1.field());
		reuseTmpDimensionedField<symmTensor, symmTensor, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> dev2(const DimensionedField<symmTensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(new DimensionedField<symmTensor, GeoMesh>(
			IOobject("dev2" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), transform(df1.dimensions())));
		dev2(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> dev2(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<symmTensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<symmTensor, symmTensor, GeoMesh>::New(tdf1, "dev2" "(" + df1.name() + ')'
			                                                               , transform(df1.dimensions())));
		dev2(tRes().field(), df1.field());
		reuseTmpDimensionedField<symmTensor, symmTensor, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> det(const DimensionedField<symmTensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("det" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), transform(df1.dimensions())));
		det(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> det(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<symmTensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, symmTensor, GeoMesh>::New(tdf1, "det" "(" + df1.name() + ')'
			                                                           , transform(df1.dimensions())));
		det(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, symmTensor, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> cof(const DimensionedField<symmTensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(new DimensionedField<symmTensor, GeoMesh>(
			IOobject("cof" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), cof(df1.dimensions())));
		cof(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> cof(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<symmTensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<symmTensor, symmTensor, GeoMesh>::New(tdf1, "cof" "(" + df1.name() + ')'
			                                                               , cof(df1.dimensions())));
		cof(tRes().field(), df1.field());
		reuseTmpDimensionedField<symmTensor, symmTensor, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> inv(const DimensionedField<symmTensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(new DimensionedField<symmTensor, GeoMesh>(
			IOobject("inv" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), inv(df1.dimensions())));
		inv(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> inv(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<symmTensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<symmTensor, symmTensor, GeoMesh>::New(tdf1, "inv" "(" + df1.name() + ')'
			                                                               , inv(df1.dimensions())));
		inv(tRes().field(), df1.field());
		reuseTmpDimensionedField<symmTensor, symmTensor, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> hinv(const DimensionedField<symmTensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(new DimensionedField<symmTensor, GeoMesh>(
			IOobject("hinv" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), hinv(df1.dimensions())));
		hinv(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> hinv(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<symmTensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<symmTensor, symmTensor, GeoMesh>::New(tdf1, "hinv" "(" + df1.name() + ')'
			                                                               , hinv(df1.dimensions())));
		hinv(tRes().field(), df1.field());
		reuseTmpDimensionedField<symmTensor, symmTensor, GeoMesh>::clear(tdf1);
		return tRes;
	}


		// * * * * * * * * * * * * * * * global operators  * * * * * * * * * * * * * //

		
	template <class GeoMesh>
	tmp<DimensionedField<vector, GeoMesh>> operator *(const DimensionedField<symmTensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<vector, GeoMesh>> tRes(new DimensionedField<vector, GeoMesh>(
			IOobject("*" + df1.name(), df1.instance(), df1.db()), df1.mesh(), transform(df1.dimensions())));
		tnbLib::hdual(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector, GeoMesh>> operator *(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<symmTensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector, symmTensor, GeoMesh>::New(tdf1, "*" + df1.name(), transform(df1.dimensions())));
		tnbLib::hdual(tRes().field(), df1.field());
		reuseTmpDimensionedField<vector, symmTensor, GeoMesh>::clear(tdf1);
		return tRes;
	}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <undefFieldFunctionsM.hxx>