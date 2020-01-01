#include <DimensionedTensorField.hxx>

#include <DimensionedFieldReuseFunctions.hxx>
#include <tensorField.hxx>

#define TEMPLATE template<class GeoMesh>
#include <DimensionedFieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> tr(const DimensionedField<tensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("tr" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), transform(df1.dimensions())));
		tr(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> tr(const tmp<DimensionedField<tensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<tensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, tensor, GeoMesh>::New(tdf1, "tr" "(" + df1.name() + ')'
			                                                       , transform(df1.dimensions())));
		tr(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, tensor, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> sph(const DimensionedField<tensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<sphericalTensor, GeoMesh>> tRes(new DimensionedField<sphericalTensor, GeoMesh>(
			IOobject("sph" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), transform(df1.dimensions())));
		sph(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> sph(const tmp<DimensionedField<tensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<tensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor, tensor, GeoMesh>::New(tdf1, "sph" "(" + df1.name() + ')'
			                                                                , transform(df1.dimensions())));
		sph(tRes().field(), df1.field());
		reuseTmpDimensionedField<sphericalTensor, tensor, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> symm(const DimensionedField<tensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(new DimensionedField<symmTensor, GeoMesh>(
			IOobject("symm" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), transform(df1.dimensions())));
		symm(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> symm(const tmp<DimensionedField<tensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<tensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<symmTensor, tensor, GeoMesh>::New(tdf1, "symm" "(" + df1.name() + ')'
			                                                           , transform(df1.dimensions())));
		symm(tRes().field(), df1.field());
		reuseTmpDimensionedField<symmTensor, tensor, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> twoSymm(const DimensionedField<tensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(new DimensionedField<symmTensor, GeoMesh>(
			IOobject("twoSymm" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), transform(df1.dimensions())));
		twoSymm(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> twoSymm(const tmp<DimensionedField<tensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<tensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<symmTensor, tensor, GeoMesh>::New(tdf1, "twoSymm" "(" + df1.name() + ')'
			                                                           , transform(df1.dimensions())));
		twoSymm(tRes().field(), df1.field());
		reuseTmpDimensionedField<symmTensor, tensor, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<tensor, GeoMesh>> skew(const DimensionedField<tensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<tensor, GeoMesh>> tRes(new DimensionedField<tensor, GeoMesh>(
			IOobject("skew" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), transform(df1.dimensions())));
		skew(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<tensor, GeoMesh>> skew(const tmp<DimensionedField<tensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<tensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<tensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<tensor, tensor, GeoMesh>::New(tdf1, "skew" "(" + df1.name() + ')'
			                                                       , transform(df1.dimensions())));
		skew(tRes().field(), df1.field());
		reuseTmpDimensionedField<tensor, tensor, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<tensor, GeoMesh>> dev(const DimensionedField<tensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<tensor, GeoMesh>> tRes(new DimensionedField<tensor, GeoMesh>(
			IOobject("dev" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), transform(df1.dimensions())));
		dev(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<tensor, GeoMesh>> dev(const tmp<DimensionedField<tensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<tensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<tensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<tensor, tensor, GeoMesh>::New(tdf1, "dev" "(" + df1.name() + ')'
			                                                       , transform(df1.dimensions())));
		dev(tRes().field(), df1.field());
		reuseTmpDimensionedField<tensor, tensor, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<tensor, GeoMesh>> dev2(const DimensionedField<tensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<tensor, GeoMesh>> tRes(new DimensionedField<tensor, GeoMesh>(
			IOobject("dev2" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), transform(df1.dimensions())));
		dev2(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<tensor, GeoMesh>> dev2(const tmp<DimensionedField<tensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<tensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<tensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<tensor, tensor, GeoMesh>::New(tdf1, "dev2" "(" + df1.name() + ')'
			                                                       , transform(df1.dimensions())));
		dev2(tRes().field(), df1.field());
		reuseTmpDimensionedField<tensor, tensor, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> det(const DimensionedField<tensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("det" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), transform(df1.dimensions())));
		det(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> det(const tmp<DimensionedField<tensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<tensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, tensor, GeoMesh>::New(tdf1, "det" "(" + df1.name() + ')'
			                                                       , transform(df1.dimensions())));
		det(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, tensor, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<tensor, GeoMesh>> cof(const DimensionedField<tensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<tensor, GeoMesh>> tRes(new DimensionedField<tensor, GeoMesh>(
			IOobject("cof" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), cof(df1.dimensions())));
		cof(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<tensor, GeoMesh>> cof(const tmp<DimensionedField<tensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<tensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<tensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<tensor, tensor, GeoMesh>::New(tdf1, "cof" "(" + df1.name() + ')', cof(df1.dimensions())));
		cof(tRes().field(), df1.field());
		reuseTmpDimensionedField<tensor, tensor, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<tensor, GeoMesh>> inv(const DimensionedField<tensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<tensor, GeoMesh>> tRes(new DimensionedField<tensor, GeoMesh>(
			IOobject("inv" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), inv(df1.dimensions())));
		inv(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<tensor, GeoMesh>> inv(const tmp<DimensionedField<tensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<tensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<tensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<tensor, tensor, GeoMesh>::New(tdf1, "inv" "(" + df1.name() + ')', inv(df1.dimensions())));
		inv(tRes().field(), df1.field());
		reuseTmpDimensionedField<tensor, tensor, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<tensor, GeoMesh>> hinv(const DimensionedField<tensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<tensor, GeoMesh>> tRes(new DimensionedField<tensor, GeoMesh>(
			IOobject("hinv" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), hinv(df1.dimensions())));
		hinv(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<tensor, GeoMesh>> hinv(const tmp<DimensionedField<tensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<tensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<tensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<tensor, tensor, GeoMesh>::New(tdf1, "hinv" "(" + df1.name() + ')', hinv(df1.dimensions())));
		hinv(tRes().field(), df1.field());
		reuseTmpDimensionedField<tensor, tensor, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<vector, GeoMesh>> eigenValues(const DimensionedField<tensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<vector, GeoMesh>> tRes(new DimensionedField<vector, GeoMesh>(
			IOobject("eigenValues" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), sign(df1.dimensions())));
		eigenValues(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector, GeoMesh>> eigenValues(const tmp<DimensionedField<tensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<tensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector, tensor, GeoMesh>::New(tdf1, "eigenValues" "(" + df1.name() + ')'
			                                                       , sign(df1.dimensions())));
		eigenValues(tRes().field(), df1.field());
		reuseTmpDimensionedField<vector, tensor, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<tensor, GeoMesh>> eigenVectors(const DimensionedField<tensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<tensor, GeoMesh>> tRes(new DimensionedField<tensor, GeoMesh>(
			IOobject("eigenVectors" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), transform(df1.dimensions())));
		eigenVectors(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<tensor, GeoMesh>> eigenVectors(const tmp<DimensionedField<tensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<tensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<tensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<tensor, tensor, GeoMesh>::New(tdf1, "eigenVectors" "(" + df1.name() + ')'
			                                                       , transform(df1.dimensions())));
		eigenVectors(tRes().field(), df1.field());
		reuseTmpDimensionedField<tensor, tensor, GeoMesh>::clear(tdf1);
		return tRes;
	}

		
	template <class GeoMesh>
	tmp<DimensionedField<vector, GeoMesh>> eigenValues(const DimensionedField<symmTensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<vector, GeoMesh>> tRes(new DimensionedField<vector, GeoMesh>(
			IOobject("eigenValues" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), sign(df1.dimensions())));
		eigenValues(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector, GeoMesh>> eigenValues(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<symmTensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector, symmTensor, GeoMesh>::New(tdf1, "eigenValues" "(" + df1.name() + ')'
			                                                           , sign(df1.dimensions())));
		eigenValues(tRes().field(), df1.field());
		reuseTmpDimensionedField<vector, symmTensor, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> eigenVectors(const DimensionedField<symmTensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(new DimensionedField<symmTensor, GeoMesh>(
			IOobject("eigenVectors" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), transform(df1.dimensions())));
		eigenVectors(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> eigenVectors(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<symmTensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<symmTensor, symmTensor, GeoMesh>::New(tdf1, "eigenVectors" "(" + df1.name() + ')'
			                                                               , transform(df1.dimensions())));
		eigenVectors(tRes().field(), df1.field());
		reuseTmpDimensionedField<symmTensor, symmTensor, GeoMesh>::clear(tdf1);
		return tRes;
	}


		// * * * * * * * * * * * * * * * global operators  * * * * * * * * * * * * * //

		
	template <class GeoMesh>
	tmp<DimensionedField<vector, GeoMesh>> operator *(const DimensionedField<tensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<vector, GeoMesh>> tRes(new DimensionedField<vector, GeoMesh>(
			IOobject("*" + df1.name(), df1.instance(), df1.db()), df1.mesh(), transform(df1.dimensions())));
		tnbLib::hdual(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector, GeoMesh>> operator *(const tmp<DimensionedField<tensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<tensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector, tensor, GeoMesh>::New(tdf1, "*" + df1.name(), transform(df1.dimensions())));
		tnbLib::hdual(tRes().field(), df1.field());
		reuseTmpDimensionedField<vector, tensor, GeoMesh>::clear(tdf1);
		return tRes;
	}
		
	template <class GeoMesh>
	tmp<DimensionedField<tensor, GeoMesh>> operator *(const DimensionedField<vector, GeoMesh>& df1)
	{
		tmp<DimensionedField<tensor, GeoMesh>> tRes(new DimensionedField<tensor, GeoMesh>(
			IOobject("*" + df1.name(), df1.instance(), df1.db()), df1.mesh(), transform(df1.dimensions())));
		tnbLib::hdual(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<tensor, GeoMesh>> operator *(const tmp<DimensionedField<vector, GeoMesh>>& tdf1)
	{
		const DimensionedField<vector, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<tensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<tensor, vector, GeoMesh>::New(tdf1, "*" + df1.name(), transform(df1.dimensions())));
		tnbLib::hdual(tRes().field(), df1.field());
		reuseTmpDimensionedField<tensor, vector, GeoMesh>::clear(tdf1);
		return tRes;
	}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <undefFieldFunctionsM.hxx>