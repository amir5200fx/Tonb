#include <DimensionedVectorNFields.hxx>

#include <DimensionedFieldReuseFunctions.hxx>

#define TEMPLATE template<class GeoMesh>
#include <DimensionedFieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define VectorN_FieldFunctions(tensorType, diagTensorType, sphericalTensorType, \
    vectorType, CmptType, args)                                              \
                                                                                \
UNARY_FUNCTION(CmptType, vectorType, cmptSum, cmptSum)                          \
                                                                                \
BINARY_FUNCTION(vectorType, vectorType, vectorType, cmptMultiply)               \
BINARY_TYPE_FUNCTION(vectorType, vectorType, vectorType, cmptMultiply)          \
                                                                                \
BINARY_OPERATOR(vectorType, CmptType, vectorType, /,'|',divide)                 \
BINARY_TYPE_OPERATOR(vectorType, CmptType, vectorType, /,'|',divide)            \
                                                                                \
BINARY_OPERATOR(vectorType, vectorType, vectorType, +,'+',add)                  \
BINARY_OPERATOR(vectorType, vectorType, vectorType, -,'-',subtract)             \
                                                                                \
BINARY_TYPE_OPERATOR(vectorType, vectorType, vectorType, +,'+',add)             \
BINARY_TYPE_OPERATOR(vectorType, vectorType, vectorType, -,'-',subtract)


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> cmptSum(const DimensionedField<vector2, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("cmptSum" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), cmptSum(df1.dimensions())));
		cmptSum(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> cmptSum(const tmp<DimensionedField<vector2, GeoMesh>>& tdf1)
	{
		const DimensionedField<vector2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, vector2, GeoMesh>::New(tdf1, "cmptSum" "(" + df1.name() + ')'
			                                                        , cmptSum(df1.dimensions())));
		cmptSum(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, vector2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> cmptMultiply(const DimensionedField<vector2, GeoMesh>& df1
	                                                     , const DimensionedField<vector2, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector2, GeoMesh>> tRes(new DimensionedField<vector2, GeoMesh>(
			IOobject("cmptMultiply" "(" + df1.name() + ',' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, cmptMultiply(df1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> cmptMultiply(const DimensionedField<vector2, GeoMesh>& df1
	                                                     , const tmp<DimensionedField<vector2, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector2, GeoMesh>> tRes(reuseTmpDimensionedField<vector2, vector2, GeoMesh>::New(
			tdf2, "cmptMultiply" "(" + df1.name() + ',' + df2.name() + ')', cmptMultiply(df1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector2, vector2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> cmptMultiply(const tmp<DimensionedField<vector2, GeoMesh>>& tdf1
	                                                     , const DimensionedField<vector2, GeoMesh>& df2)
	{
		const DimensionedField<vector2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector2, GeoMesh>> tRes(reuseTmpDimensionedField<vector2, vector2, GeoMesh>::New(
			tdf1, "cmptMultiply" "(" + df1.name() + ',' + df2.name() + ')', cmptMultiply(df1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector2, vector2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> cmptMultiply(const tmp<DimensionedField<vector2, GeoMesh>>& tdf1
	                                                     , const tmp<DimensionedField<vector2, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector2, GeoMesh>& df1 = tdf1();
		const DimensionedField<vector2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector2, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<vector2, vector2, vector2, vector2, GeoMesh>::New(
				tdf1, tdf2, "cmptMultiply" "(" + df1.name() + ',' + df2.name() + ')'
				, cmptMultiply(df1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<vector2, vector2, vector2, vector2, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> cmptMultiply(const dimensioned<vector2>& dt1
	                                                     , const DimensionedField<vector2, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector2, GeoMesh>> tRes(new DimensionedField<vector2, GeoMesh>(
			IOobject("cmptMultiply" "(" + dt1.name() + ',' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, cmptMultiply(dt1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> cmptMultiply(const vector2& t1, const DimensionedField<vector2, GeoMesh>& df2)
	{
		return cmptMultiply(dimensioned<vector2>(t1), df2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> cmptMultiply(const dimensioned<vector2>& dt1
	                                                     , const tmp<DimensionedField<vector2, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector2, GeoMesh>> tRes(reuseTmpDimensionedField<vector2, vector2, GeoMesh>::New(
			tdf2, "cmptMultiply" "(" + dt1.name() + ',' + df2.name() + ')', cmptMultiply(dt1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), dt1.value(), df2.field());
		reuseTmpDimensionedField<vector2, vector2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> cmptMultiply(const vector2& t1
	                                                     , const tmp<DimensionedField<vector2, GeoMesh>>& tdf2)
	{
		return cmptMultiply(dimensioned<vector2>(t1), tdf2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> cmptMultiply(const DimensionedField<vector2, GeoMesh>& df1
	                                                     , const dimensioned<vector2>& dt2)
	{
		tmp<DimensionedField<vector2, GeoMesh>> tRes(new DimensionedField<vector2, GeoMesh>(
			IOobject("cmptMultiply" "(" + df1.name() + ',' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, cmptMultiply(df1.dimensions(), dt2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> cmptMultiply(const DimensionedField<vector2, GeoMesh>& df1, const vector2& t2)
	{
		return cmptMultiply(df1, dimensioned<vector2>(t2));
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> cmptMultiply(const tmp<DimensionedField<vector2, GeoMesh>>& tdf1
	                                                     , const dimensioned<vector2>& dt2)
	{
		const DimensionedField<vector2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector2, GeoMesh>> tRes(reuseTmpDimensionedField<vector2, vector2, GeoMesh>::New(
			tdf1, "cmptMultiply" "(" + df1.name() + ',' + dt2.name() + ')', cmptMultiply(df1.dimensions(), dt2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), dt2.value());
		reuseTmpDimensionedField<vector2, vector2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> cmptMultiply(const tmp<DimensionedField<vector2, GeoMesh>>& tdf1
	                                                     , const vector2& t2)
	{
		return cmptMultiply(tdf1, dimensioned<vector2>(t2));
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                   , const DimensionedField<vector2, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector2, GeoMesh>> tRes(new DimensionedField<vector2, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                   , const tmp<DimensionedField<vector2, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector2, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector2, vector2, GeoMesh>::New(tdf2, '(' + df1.name() + '|' + df2.name() + ')'
			                                                         , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector2, vector2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                   , const DimensionedField<vector2, GeoMesh>& df2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector2, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector2, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + df2.name() + ')'
			                                                        , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector2, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                   , const tmp<DimensionedField<vector2, GeoMesh>>& tdf2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		const DimensionedField<vector2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector2, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<vector2, scalar, scalar, vector2, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<vector2, scalar, scalar, vector2, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator /(const dimensioned<scalar>& dt1
	                                                   , const DimensionedField<vector2, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector2, GeoMesh>> tRes(new DimensionedField<vector2, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator /(const scalar& t1, const DimensionedField<vector2, GeoMesh>& df2)
	{
		return dimensioned<scalar>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator /(const dimensioned<scalar>& dt1
	                                                   , const tmp<DimensionedField<vector2, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector2, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector2, vector2, GeoMesh>::New(tdf2, '(' + dt1.name() + '|' + df2.name() + ')'
			                                                         , dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<vector2, vector2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator /(const scalar& t1
	                                                   , const tmp<DimensionedField<vector2, GeoMesh>>& tdf2)
	{
		return dimensioned<scalar>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                   , const dimensioned<vector2>& dt2)
	{
		tmp<DimensionedField<vector2, GeoMesh>> tRes(new DimensionedField<vector2, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1, const vector2& t2)
	{
		return df1 / dimensioned<vector2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                   , const dimensioned<vector2>& dt2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector2, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector2, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + dt2.name() + ')'
			                                                        , df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<vector2, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                   , const vector2& t2) { return tdf1 / dimensioned<vector2>(t2); }

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator +(const DimensionedField<vector2, GeoMesh>& df1
	                                                   , const DimensionedField<vector2, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector2, GeoMesh>> tRes(new DimensionedField<vector2, GeoMesh>(
			IOobject('(' + df1.name() + '+' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator +(const DimensionedField<vector2, GeoMesh>& df1
	                                                   , const tmp<DimensionedField<vector2, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector2, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector2, vector2, GeoMesh>::New(tdf2, '(' + df1.name() + '+' + df2.name() + ')'
			                                                         , df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector2, vector2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator +(const tmp<DimensionedField<vector2, GeoMesh>>& tdf1
	                                                   , const DimensionedField<vector2, GeoMesh>& df2)
	{
		const DimensionedField<vector2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector2, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector2, vector2, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + df2.name() + ')'
			                                                         , df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector2, vector2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator +(const tmp<DimensionedField<vector2, GeoMesh>>& tdf1
	                                                   , const tmp<DimensionedField<vector2, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector2, GeoMesh>& df1 = tdf1();
		const DimensionedField<vector2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector2, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<vector2, vector2, vector2, vector2, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<vector2, vector2, vector2, vector2, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator -(const DimensionedField<vector2, GeoMesh>& df1
	                                                   , const DimensionedField<vector2, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector2, GeoMesh>> tRes(new DimensionedField<vector2, GeoMesh>(
			IOobject('(' + df1.name() + '-' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator -(const DimensionedField<vector2, GeoMesh>& df1
	                                                   , const tmp<DimensionedField<vector2, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector2, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector2, vector2, GeoMesh>::New(tdf2, '(' + df1.name() + '-' + df2.name() + ')'
			                                                         , df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector2, vector2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator -(const tmp<DimensionedField<vector2, GeoMesh>>& tdf1
	                                                   , const DimensionedField<vector2, GeoMesh>& df2)
	{
		const DimensionedField<vector2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector2, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector2, vector2, GeoMesh>::New(tdf1, '(' + df1.name() + '-' + df2.name() + ')'
			                                                         , df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector2, vector2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator -(const tmp<DimensionedField<vector2, GeoMesh>>& tdf1
	                                                   , const tmp<DimensionedField<vector2, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector2, GeoMesh>& df1 = tdf1();
		const DimensionedField<vector2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector2, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<vector2, vector2, vector2, vector2, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<vector2, vector2, vector2, vector2, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator +(const dimensioned<vector2>& dt1
	                                                   , const DimensionedField<vector2, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector2, GeoMesh>> tRes(new DimensionedField<vector2, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator +(const vector2& t1, const DimensionedField<vector2, GeoMesh>& df2)
	{
		return dimensioned<vector2>(t1) + df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator +(const dimensioned<vector2>& dt1
	                                                   , const tmp<DimensionedField<vector2, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector2, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector2, vector2, GeoMesh>::New(tdf2, '(' + dt1.name() + '+' + df2.name() + ')'
			                                                         , dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<vector2, vector2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator +(const vector2& t1
	                                                   , const tmp<DimensionedField<vector2, GeoMesh>>& tdf2)
	{
		return dimensioned<vector2>(t1) + tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator +(const DimensionedField<vector2, GeoMesh>& df1
	                                                   , const dimensioned<vector2>& dt2)
	{
		tmp<DimensionedField<vector2, GeoMesh>> tRes(new DimensionedField<vector2, GeoMesh>(
			IOobject('(' + df1.name() + '+' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator +(const DimensionedField<vector2, GeoMesh>& df1, const vector2& t2)
	{
		return df1 + dimensioned<vector2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator +(const tmp<DimensionedField<vector2, GeoMesh>>& tdf1
	                                                   , const dimensioned<vector2>& dt2)
	{
		const DimensionedField<vector2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector2, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector2, vector2, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + dt2.name() + ')'
			                                                         , df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<vector2, vector2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator +(const tmp<DimensionedField<vector2, GeoMesh>>& tdf1
	                                                   , const vector2& t2) { return tdf1 + dimensioned<vector2>(t2); }

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator -(const dimensioned<vector2>& dt1
	                                                   , const DimensionedField<vector2, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector2, GeoMesh>> tRes(new DimensionedField<vector2, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator -(const vector2& t1, const DimensionedField<vector2, GeoMesh>& df2)
	{
		return dimensioned<vector2>(t1) - df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator -(const dimensioned<vector2>& dt1
	                                                   , const tmp<DimensionedField<vector2, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector2, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector2, vector2, GeoMesh>::New(tdf2, '(' + dt1.name() + '-' + df2.name() + ')'
			                                                         , dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<vector2, vector2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator -(const vector2& t1
	                                                   , const tmp<DimensionedField<vector2, GeoMesh>>& tdf2)
	{
		return dimensioned<vector2>(t1) - tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator -(const DimensionedField<vector2, GeoMesh>& df1
	                                                   , const dimensioned<vector2>& dt2)
	{
		tmp<DimensionedField<vector2, GeoMesh>> tRes(new DimensionedField<vector2, GeoMesh>(
			IOobject('(' + df1.name() + '-' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator -(const DimensionedField<vector2, GeoMesh>& df1, const vector2& t2)
	{
		return df1 - dimensioned<vector2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator -(const tmp<DimensionedField<vector2, GeoMesh>>& tdf1
	                                                   , const dimensioned<vector2>& dt2)
	{
		const DimensionedField<vector2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector2, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector2, vector2, GeoMesh>::New(tdf1, '(' + df1.name() + '-' + dt2.name() + ')'
			                                                         , df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<vector2, vector2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator -(const tmp<DimensionedField<vector2, GeoMesh>>& tdf1
	                                                   , const vector2& t2) { return tdf1 - dimensioned<vector2>(t2); }

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> cmptSum(const DimensionedField<vector3, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("cmptSum" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), cmptSum(df1.dimensions())));
		cmptSum(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> cmptSum(const tmp<DimensionedField<vector3, GeoMesh>>& tdf1)
	{
		const DimensionedField<vector3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, vector3, GeoMesh>::New(tdf1, "cmptSum" "(" + df1.name() + ')'
			                                                        , cmptSum(df1.dimensions())));
		cmptSum(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, vector3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> cmptMultiply(const DimensionedField<vector3, GeoMesh>& df1
	                                                     , const DimensionedField<vector3, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector3, GeoMesh>> tRes(new DimensionedField<vector3, GeoMesh>(
			IOobject("cmptMultiply" "(" + df1.name() + ',' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, cmptMultiply(df1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> cmptMultiply(const DimensionedField<vector3, GeoMesh>& df1
	                                                     , const tmp<DimensionedField<vector3, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector3, GeoMesh>> tRes(reuseTmpDimensionedField<vector3, vector3, GeoMesh>::New(
			tdf2, "cmptMultiply" "(" + df1.name() + ',' + df2.name() + ')', cmptMultiply(df1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector3, vector3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> cmptMultiply(const tmp<DimensionedField<vector3, GeoMesh>>& tdf1
	                                                     , const DimensionedField<vector3, GeoMesh>& df2)
	{
		const DimensionedField<vector3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector3, GeoMesh>> tRes(reuseTmpDimensionedField<vector3, vector3, GeoMesh>::New(
			tdf1, "cmptMultiply" "(" + df1.name() + ',' + df2.name() + ')', cmptMultiply(df1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector3, vector3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> cmptMultiply(const tmp<DimensionedField<vector3, GeoMesh>>& tdf1
	                                                     , const tmp<DimensionedField<vector3, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector3, GeoMesh>& df1 = tdf1();
		const DimensionedField<vector3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector3, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<vector3, vector3, vector3, vector3, GeoMesh>::New(
				tdf1, tdf2, "cmptMultiply" "(" + df1.name() + ',' + df2.name() + ')'
				, cmptMultiply(df1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<vector3, vector3, vector3, vector3, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> cmptMultiply(const dimensioned<vector3>& dt1
	                                                     , const DimensionedField<vector3, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector3, GeoMesh>> tRes(new DimensionedField<vector3, GeoMesh>(
			IOobject("cmptMultiply" "(" + dt1.name() + ',' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, cmptMultiply(dt1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> cmptMultiply(const vector3& t1, const DimensionedField<vector3, GeoMesh>& df2)
	{
		return cmptMultiply(dimensioned<vector3>(t1), df2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> cmptMultiply(const dimensioned<vector3>& dt1
	                                                     , const tmp<DimensionedField<vector3, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector3, GeoMesh>> tRes(reuseTmpDimensionedField<vector3, vector3, GeoMesh>::New(
			tdf2, "cmptMultiply" "(" + dt1.name() + ',' + df2.name() + ')', cmptMultiply(dt1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), dt1.value(), df2.field());
		reuseTmpDimensionedField<vector3, vector3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> cmptMultiply(const vector3& t1
	                                                     , const tmp<DimensionedField<vector3, GeoMesh>>& tdf2)
	{
		return cmptMultiply(dimensioned<vector3>(t1), tdf2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> cmptMultiply(const DimensionedField<vector3, GeoMesh>& df1
	                                                     , const dimensioned<vector3>& dt2)
	{
		tmp<DimensionedField<vector3, GeoMesh>> tRes(new DimensionedField<vector3, GeoMesh>(
			IOobject("cmptMultiply" "(" + df1.name() + ',' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, cmptMultiply(df1.dimensions(), dt2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> cmptMultiply(const DimensionedField<vector3, GeoMesh>& df1, const vector3& t2)
	{
		return cmptMultiply(df1, dimensioned<vector3>(t2));
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> cmptMultiply(const tmp<DimensionedField<vector3, GeoMesh>>& tdf1
	                                                     , const dimensioned<vector3>& dt2)
	{
		const DimensionedField<vector3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector3, GeoMesh>> tRes(reuseTmpDimensionedField<vector3, vector3, GeoMesh>::New(
			tdf1, "cmptMultiply" "(" + df1.name() + ',' + dt2.name() + ')', cmptMultiply(df1.dimensions(), dt2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), dt2.value());
		reuseTmpDimensionedField<vector3, vector3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> cmptMultiply(const tmp<DimensionedField<vector3, GeoMesh>>& tdf1
	                                                     , const vector3& t2)
	{
		return cmptMultiply(tdf1, dimensioned<vector3>(t2));
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                   , const DimensionedField<vector3, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector3, GeoMesh>> tRes(new DimensionedField<vector3, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                   , const tmp<DimensionedField<vector3, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector3, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector3, vector3, GeoMesh>::New(tdf2, '(' + df1.name() + '|' + df2.name() + ')'
			                                                         , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector3, vector3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                   , const DimensionedField<vector3, GeoMesh>& df2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector3, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector3, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + df2.name() + ')'
			                                                        , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector3, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                   , const tmp<DimensionedField<vector3, GeoMesh>>& tdf2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		const DimensionedField<vector3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector3, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<vector3, scalar, scalar, vector3, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<vector3, scalar, scalar, vector3, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator /(const dimensioned<scalar>& dt1
	                                                   , const DimensionedField<vector3, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector3, GeoMesh>> tRes(new DimensionedField<vector3, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator /(const scalar& t1, const DimensionedField<vector3, GeoMesh>& df2)
	{
		return dimensioned<scalar>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator /(const dimensioned<scalar>& dt1
	                                                   , const tmp<DimensionedField<vector3, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector3, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector3, vector3, GeoMesh>::New(tdf2, '(' + dt1.name() + '|' + df2.name() + ')'
			                                                         , dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<vector3, vector3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator /(const scalar& t1
	                                                   , const tmp<DimensionedField<vector3, GeoMesh>>& tdf2)
	{
		return dimensioned<scalar>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                   , const dimensioned<vector3>& dt2)
	{
		tmp<DimensionedField<vector3, GeoMesh>> tRes(new DimensionedField<vector3, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1, const vector3& t2)
	{
		return df1 / dimensioned<vector3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                   , const dimensioned<vector3>& dt2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector3, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector3, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + dt2.name() + ')'
			                                                        , df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<vector3, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                   , const vector3& t2) { return tdf1 / dimensioned<vector3>(t2); }

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator +(const DimensionedField<vector3, GeoMesh>& df1
	                                                   , const DimensionedField<vector3, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector3, GeoMesh>> tRes(new DimensionedField<vector3, GeoMesh>(
			IOobject('(' + df1.name() + '+' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator +(const DimensionedField<vector3, GeoMesh>& df1
	                                                   , const tmp<DimensionedField<vector3, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector3, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector3, vector3, GeoMesh>::New(tdf2, '(' + df1.name() + '+' + df2.name() + ')'
			                                                         , df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector3, vector3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator +(const tmp<DimensionedField<vector3, GeoMesh>>& tdf1
	                                                   , const DimensionedField<vector3, GeoMesh>& df2)
	{
		const DimensionedField<vector3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector3, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector3, vector3, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + df2.name() + ')'
			                                                         , df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector3, vector3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator +(const tmp<DimensionedField<vector3, GeoMesh>>& tdf1
	                                                   , const tmp<DimensionedField<vector3, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector3, GeoMesh>& df1 = tdf1();
		const DimensionedField<vector3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector3, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<vector3, vector3, vector3, vector3, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<vector3, vector3, vector3, vector3, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator -(const DimensionedField<vector3, GeoMesh>& df1
	                                                   , const DimensionedField<vector3, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector3, GeoMesh>> tRes(new DimensionedField<vector3, GeoMesh>(
			IOobject('(' + df1.name() + '-' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator -(const DimensionedField<vector3, GeoMesh>& df1
	                                                   , const tmp<DimensionedField<vector3, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector3, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector3, vector3, GeoMesh>::New(tdf2, '(' + df1.name() + '-' + df2.name() + ')'
			                                                         , df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector3, vector3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator -(const tmp<DimensionedField<vector3, GeoMesh>>& tdf1
	                                                   , const DimensionedField<vector3, GeoMesh>& df2)
	{
		const DimensionedField<vector3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector3, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector3, vector3, GeoMesh>::New(tdf1, '(' + df1.name() + '-' + df2.name() + ')'
			                                                         , df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector3, vector3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator -(const tmp<DimensionedField<vector3, GeoMesh>>& tdf1
	                                                   , const tmp<DimensionedField<vector3, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector3, GeoMesh>& df1 = tdf1();
		const DimensionedField<vector3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector3, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<vector3, vector3, vector3, vector3, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<vector3, vector3, vector3, vector3, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator +(const dimensioned<vector3>& dt1
	                                                   , const DimensionedField<vector3, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector3, GeoMesh>> tRes(new DimensionedField<vector3, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator +(const vector3& t1, const DimensionedField<vector3, GeoMesh>& df2)
	{
		return dimensioned<vector3>(t1) + df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator +(const dimensioned<vector3>& dt1
	                                                   , const tmp<DimensionedField<vector3, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector3, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector3, vector3, GeoMesh>::New(tdf2, '(' + dt1.name() + '+' + df2.name() + ')'
			                                                         , dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<vector3, vector3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator +(const vector3& t1
	                                                   , const tmp<DimensionedField<vector3, GeoMesh>>& tdf2)
	{
		return dimensioned<vector3>(t1) + tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator +(const DimensionedField<vector3, GeoMesh>& df1
	                                                   , const dimensioned<vector3>& dt2)
	{
		tmp<DimensionedField<vector3, GeoMesh>> tRes(new DimensionedField<vector3, GeoMesh>(
			IOobject('(' + df1.name() + '+' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator +(const DimensionedField<vector3, GeoMesh>& df1, const vector3& t2)
	{
		return df1 + dimensioned<vector3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator +(const tmp<DimensionedField<vector3, GeoMesh>>& tdf1
	                                                   , const dimensioned<vector3>& dt2)
	{
		const DimensionedField<vector3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector3, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector3, vector3, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + dt2.name() + ')'
			                                                         , df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<vector3, vector3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator +(const tmp<DimensionedField<vector3, GeoMesh>>& tdf1
	                                                   , const vector3& t2) { return tdf1 + dimensioned<vector3>(t2); }

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator -(const dimensioned<vector3>& dt1
	                                                   , const DimensionedField<vector3, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector3, GeoMesh>> tRes(new DimensionedField<vector3, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator -(const vector3& t1, const DimensionedField<vector3, GeoMesh>& df2)
	{
		return dimensioned<vector3>(t1) - df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator -(const dimensioned<vector3>& dt1
	                                                   , const tmp<DimensionedField<vector3, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector3, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector3, vector3, GeoMesh>::New(tdf2, '(' + dt1.name() + '-' + df2.name() + ')'
			                                                         , dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<vector3, vector3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator -(const vector3& t1
	                                                   , const tmp<DimensionedField<vector3, GeoMesh>>& tdf2)
	{
		return dimensioned<vector3>(t1) - tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator -(const DimensionedField<vector3, GeoMesh>& df1
	                                                   , const dimensioned<vector3>& dt2)
	{
		tmp<DimensionedField<vector3, GeoMesh>> tRes(new DimensionedField<vector3, GeoMesh>(
			IOobject('(' + df1.name() + '-' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator -(const DimensionedField<vector3, GeoMesh>& df1, const vector3& t2)
	{
		return df1 - dimensioned<vector3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator -(const tmp<DimensionedField<vector3, GeoMesh>>& tdf1
	                                                   , const dimensioned<vector3>& dt2)
	{
		const DimensionedField<vector3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector3, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector3, vector3, GeoMesh>::New(tdf1, '(' + df1.name() + '-' + dt2.name() + ')'
			                                                         , df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<vector3, vector3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator -(const tmp<DimensionedField<vector3, GeoMesh>>& tdf1
	                                                   , const vector3& t2) { return tdf1 - dimensioned<vector3>(t2); }

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> cmptSum(const DimensionedField<vector4, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("cmptSum" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), cmptSum(df1.dimensions())));
		cmptSum(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> cmptSum(const tmp<DimensionedField<vector4, GeoMesh>>& tdf1)
	{
		const DimensionedField<vector4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, vector4, GeoMesh>::New(tdf1, "cmptSum" "(" + df1.name() + ')'
			                                                        , cmptSum(df1.dimensions())));
		cmptSum(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, vector4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> cmptMultiply(const DimensionedField<vector4, GeoMesh>& df1
	                                                     , const DimensionedField<vector4, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector4, GeoMesh>> tRes(new DimensionedField<vector4, GeoMesh>(
			IOobject("cmptMultiply" "(" + df1.name() + ',' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, cmptMultiply(df1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> cmptMultiply(const DimensionedField<vector4, GeoMesh>& df1
	                                                     , const tmp<DimensionedField<vector4, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector4, GeoMesh>> tRes(reuseTmpDimensionedField<vector4, vector4, GeoMesh>::New(
			tdf2, "cmptMultiply" "(" + df1.name() + ',' + df2.name() + ')', cmptMultiply(df1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector4, vector4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> cmptMultiply(const tmp<DimensionedField<vector4, GeoMesh>>& tdf1
	                                                     , const DimensionedField<vector4, GeoMesh>& df2)
	{
		const DimensionedField<vector4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector4, GeoMesh>> tRes(reuseTmpDimensionedField<vector4, vector4, GeoMesh>::New(
			tdf1, "cmptMultiply" "(" + df1.name() + ',' + df2.name() + ')', cmptMultiply(df1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector4, vector4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> cmptMultiply(const tmp<DimensionedField<vector4, GeoMesh>>& tdf1
	                                                     , const tmp<DimensionedField<vector4, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector4, GeoMesh>& df1 = tdf1();
		const DimensionedField<vector4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector4, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<vector4, vector4, vector4, vector4, GeoMesh>::New(
				tdf1, tdf2, "cmptMultiply" "(" + df1.name() + ',' + df2.name() + ')'
				, cmptMultiply(df1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<vector4, vector4, vector4, vector4, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> cmptMultiply(const dimensioned<vector4>& dt1
	                                                     , const DimensionedField<vector4, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector4, GeoMesh>> tRes(new DimensionedField<vector4, GeoMesh>(
			IOobject("cmptMultiply" "(" + dt1.name() + ',' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, cmptMultiply(dt1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> cmptMultiply(const vector4& t1, const DimensionedField<vector4, GeoMesh>& df2)
	{
		return cmptMultiply(dimensioned<vector4>(t1), df2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> cmptMultiply(const dimensioned<vector4>& dt1
	                                                     , const tmp<DimensionedField<vector4, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector4, GeoMesh>> tRes(reuseTmpDimensionedField<vector4, vector4, GeoMesh>::New(
			tdf2, "cmptMultiply" "(" + dt1.name() + ',' + df2.name() + ')', cmptMultiply(dt1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), dt1.value(), df2.field());
		reuseTmpDimensionedField<vector4, vector4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> cmptMultiply(const vector4& t1
	                                                     , const tmp<DimensionedField<vector4, GeoMesh>>& tdf2)
	{
		return cmptMultiply(dimensioned<vector4>(t1), tdf2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> cmptMultiply(const DimensionedField<vector4, GeoMesh>& df1
	                                                     , const dimensioned<vector4>& dt2)
	{
		tmp<DimensionedField<vector4, GeoMesh>> tRes(new DimensionedField<vector4, GeoMesh>(
			IOobject("cmptMultiply" "(" + df1.name() + ',' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, cmptMultiply(df1.dimensions(), dt2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> cmptMultiply(const DimensionedField<vector4, GeoMesh>& df1, const vector4& t2)
	{
		return cmptMultiply(df1, dimensioned<vector4>(t2));
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> cmptMultiply(const tmp<DimensionedField<vector4, GeoMesh>>& tdf1
	                                                     , const dimensioned<vector4>& dt2)
	{
		const DimensionedField<vector4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector4, GeoMesh>> tRes(reuseTmpDimensionedField<vector4, vector4, GeoMesh>::New(
			tdf1, "cmptMultiply" "(" + df1.name() + ',' + dt2.name() + ')', cmptMultiply(df1.dimensions(), dt2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), dt2.value());
		reuseTmpDimensionedField<vector4, vector4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> cmptMultiply(const tmp<DimensionedField<vector4, GeoMesh>>& tdf1
	                                                     , const vector4& t2)
	{
		return cmptMultiply(tdf1, dimensioned<vector4>(t2));
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                   , const DimensionedField<vector4, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector4, GeoMesh>> tRes(new DimensionedField<vector4, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                   , const tmp<DimensionedField<vector4, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector4, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector4, vector4, GeoMesh>::New(tdf2, '(' + df1.name() + '|' + df2.name() + ')'
			                                                         , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector4, vector4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                   , const DimensionedField<vector4, GeoMesh>& df2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector4, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector4, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + df2.name() + ')'
			                                                        , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector4, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                   , const tmp<DimensionedField<vector4, GeoMesh>>& tdf2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		const DimensionedField<vector4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector4, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<vector4, scalar, scalar, vector4, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<vector4, scalar, scalar, vector4, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator /(const dimensioned<scalar>& dt1
	                                                   , const DimensionedField<vector4, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector4, GeoMesh>> tRes(new DimensionedField<vector4, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator /(const scalar& t1, const DimensionedField<vector4, GeoMesh>& df2)
	{
		return dimensioned<scalar>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator /(const dimensioned<scalar>& dt1
	                                                   , const tmp<DimensionedField<vector4, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector4, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector4, vector4, GeoMesh>::New(tdf2, '(' + dt1.name() + '|' + df2.name() + ')'
			                                                         , dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<vector4, vector4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator /(const scalar& t1
	                                                   , const tmp<DimensionedField<vector4, GeoMesh>>& tdf2)
	{
		return dimensioned<scalar>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                   , const dimensioned<vector4>& dt2)
	{
		tmp<DimensionedField<vector4, GeoMesh>> tRes(new DimensionedField<vector4, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1, const vector4& t2)
	{
		return df1 / dimensioned<vector4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                   , const dimensioned<vector4>& dt2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector4, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector4, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + dt2.name() + ')'
			                                                        , df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<vector4, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                   , const vector4& t2) { return tdf1 / dimensioned<vector4>(t2); }

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator +(const DimensionedField<vector4, GeoMesh>& df1
	                                                   , const DimensionedField<vector4, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector4, GeoMesh>> tRes(new DimensionedField<vector4, GeoMesh>(
			IOobject('(' + df1.name() + '+' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator +(const DimensionedField<vector4, GeoMesh>& df1
	                                                   , const tmp<DimensionedField<vector4, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector4, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector4, vector4, GeoMesh>::New(tdf2, '(' + df1.name() + '+' + df2.name() + ')'
			                                                         , df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector4, vector4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator +(const tmp<DimensionedField<vector4, GeoMesh>>& tdf1
	                                                   , const DimensionedField<vector4, GeoMesh>& df2)
	{
		const DimensionedField<vector4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector4, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector4, vector4, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + df2.name() + ')'
			                                                         , df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector4, vector4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator +(const tmp<DimensionedField<vector4, GeoMesh>>& tdf1
	                                                   , const tmp<DimensionedField<vector4, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector4, GeoMesh>& df1 = tdf1();
		const DimensionedField<vector4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector4, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<vector4, vector4, vector4, vector4, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<vector4, vector4, vector4, vector4, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator -(const DimensionedField<vector4, GeoMesh>& df1
	                                                   , const DimensionedField<vector4, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector4, GeoMesh>> tRes(new DimensionedField<vector4, GeoMesh>(
			IOobject('(' + df1.name() + '-' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator -(const DimensionedField<vector4, GeoMesh>& df1
	                                                   , const tmp<DimensionedField<vector4, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector4, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector4, vector4, GeoMesh>::New(tdf2, '(' + df1.name() + '-' + df2.name() + ')'
			                                                         , df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector4, vector4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator -(const tmp<DimensionedField<vector4, GeoMesh>>& tdf1
	                                                   , const DimensionedField<vector4, GeoMesh>& df2)
	{
		const DimensionedField<vector4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector4, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector4, vector4, GeoMesh>::New(tdf1, '(' + df1.name() + '-' + df2.name() + ')'
			                                                         , df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector4, vector4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator -(const tmp<DimensionedField<vector4, GeoMesh>>& tdf1
	                                                   , const tmp<DimensionedField<vector4, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector4, GeoMesh>& df1 = tdf1();
		const DimensionedField<vector4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector4, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<vector4, vector4, vector4, vector4, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<vector4, vector4, vector4, vector4, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator +(const dimensioned<vector4>& dt1
	                                                   , const DimensionedField<vector4, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector4, GeoMesh>> tRes(new DimensionedField<vector4, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator +(const vector4& t1, const DimensionedField<vector4, GeoMesh>& df2)
	{
		return dimensioned<vector4>(t1) + df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator +(const dimensioned<vector4>& dt1
	                                                   , const tmp<DimensionedField<vector4, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector4, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector4, vector4, GeoMesh>::New(tdf2, '(' + dt1.name() + '+' + df2.name() + ')'
			                                                         , dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<vector4, vector4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator +(const vector4& t1
	                                                   , const tmp<DimensionedField<vector4, GeoMesh>>& tdf2)
	{
		return dimensioned<vector4>(t1) + tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator +(const DimensionedField<vector4, GeoMesh>& df1
	                                                   , const dimensioned<vector4>& dt2)
	{
		tmp<DimensionedField<vector4, GeoMesh>> tRes(new DimensionedField<vector4, GeoMesh>(
			IOobject('(' + df1.name() + '+' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator +(const DimensionedField<vector4, GeoMesh>& df1, const vector4& t2)
	{
		return df1 + dimensioned<vector4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator +(const tmp<DimensionedField<vector4, GeoMesh>>& tdf1
	                                                   , const dimensioned<vector4>& dt2)
	{
		const DimensionedField<vector4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector4, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector4, vector4, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + dt2.name() + ')'
			                                                         , df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<vector4, vector4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator +(const tmp<DimensionedField<vector4, GeoMesh>>& tdf1
	                                                   , const vector4& t2) { return tdf1 + dimensioned<vector4>(t2); }

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator -(const dimensioned<vector4>& dt1
	                                                   , const DimensionedField<vector4, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector4, GeoMesh>> tRes(new DimensionedField<vector4, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator -(const vector4& t1, const DimensionedField<vector4, GeoMesh>& df2)
	{
		return dimensioned<vector4>(t1) - df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator -(const dimensioned<vector4>& dt1
	                                                   , const tmp<DimensionedField<vector4, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector4, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector4, vector4, GeoMesh>::New(tdf2, '(' + dt1.name() + '-' + df2.name() + ')'
			                                                         , dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<vector4, vector4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator -(const vector4& t1
	                                                   , const tmp<DimensionedField<vector4, GeoMesh>>& tdf2)
	{
		return dimensioned<vector4>(t1) - tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator -(const DimensionedField<vector4, GeoMesh>& df1
	                                                   , const dimensioned<vector4>& dt2)
	{
		tmp<DimensionedField<vector4, GeoMesh>> tRes(new DimensionedField<vector4, GeoMesh>(
			IOobject('(' + df1.name() + '-' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator -(const DimensionedField<vector4, GeoMesh>& df1, const vector4& t2)
	{
		return df1 - dimensioned<vector4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator -(const tmp<DimensionedField<vector4, GeoMesh>>& tdf1
	                                                   , const dimensioned<vector4>& dt2)
	{
		const DimensionedField<vector4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector4, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector4, vector4, GeoMesh>::New(tdf1, '(' + df1.name() + '-' + dt2.name() + ')'
			                                                         , df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<vector4, vector4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator -(const tmp<DimensionedField<vector4, GeoMesh>>& tdf1
	                                                   , const vector4& t2) { return tdf1 - dimensioned<vector4>(t2); }

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> cmptSum(const DimensionedField<vector6, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("cmptSum" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), cmptSum(df1.dimensions())));
		cmptSum(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> cmptSum(const tmp<DimensionedField<vector6, GeoMesh>>& tdf1)
	{
		const DimensionedField<vector6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, vector6, GeoMesh>::New(tdf1, "cmptSum" "(" + df1.name() + ')'
			                                                        , cmptSum(df1.dimensions())));
		cmptSum(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, vector6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> cmptMultiply(const DimensionedField<vector6, GeoMesh>& df1
	                                                     , const DimensionedField<vector6, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector6, GeoMesh>> tRes(new DimensionedField<vector6, GeoMesh>(
			IOobject("cmptMultiply" "(" + df1.name() + ',' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, cmptMultiply(df1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> cmptMultiply(const DimensionedField<vector6, GeoMesh>& df1
	                                                     , const tmp<DimensionedField<vector6, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector6, GeoMesh>> tRes(reuseTmpDimensionedField<vector6, vector6, GeoMesh>::New(
			tdf2, "cmptMultiply" "(" + df1.name() + ',' + df2.name() + ')', cmptMultiply(df1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector6, vector6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> cmptMultiply(const tmp<DimensionedField<vector6, GeoMesh>>& tdf1
	                                                     , const DimensionedField<vector6, GeoMesh>& df2)
	{
		const DimensionedField<vector6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector6, GeoMesh>> tRes(reuseTmpDimensionedField<vector6, vector6, GeoMesh>::New(
			tdf1, "cmptMultiply" "(" + df1.name() + ',' + df2.name() + ')', cmptMultiply(df1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector6, vector6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> cmptMultiply(const tmp<DimensionedField<vector6, GeoMesh>>& tdf1
	                                                     , const tmp<DimensionedField<vector6, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector6, GeoMesh>& df1 = tdf1();
		const DimensionedField<vector6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector6, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<vector6, vector6, vector6, vector6, GeoMesh>::New(
				tdf1, tdf2, "cmptMultiply" "(" + df1.name() + ',' + df2.name() + ')'
				, cmptMultiply(df1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<vector6, vector6, vector6, vector6, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> cmptMultiply(const dimensioned<vector6>& dt1
	                                                     , const DimensionedField<vector6, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector6, GeoMesh>> tRes(new DimensionedField<vector6, GeoMesh>(
			IOobject("cmptMultiply" "(" + dt1.name() + ',' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, cmptMultiply(dt1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> cmptMultiply(const vector6& t1, const DimensionedField<vector6, GeoMesh>& df2)
	{
		return cmptMultiply(dimensioned<vector6>(t1), df2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> cmptMultiply(const dimensioned<vector6>& dt1
	                                                     , const tmp<DimensionedField<vector6, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector6, GeoMesh>> tRes(reuseTmpDimensionedField<vector6, vector6, GeoMesh>::New(
			tdf2, "cmptMultiply" "(" + dt1.name() + ',' + df2.name() + ')', cmptMultiply(dt1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), dt1.value(), df2.field());
		reuseTmpDimensionedField<vector6, vector6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> cmptMultiply(const vector6& t1
	                                                     , const tmp<DimensionedField<vector6, GeoMesh>>& tdf2)
	{
		return cmptMultiply(dimensioned<vector6>(t1), tdf2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> cmptMultiply(const DimensionedField<vector6, GeoMesh>& df1
	                                                     , const dimensioned<vector6>& dt2)
	{
		tmp<DimensionedField<vector6, GeoMesh>> tRes(new DimensionedField<vector6, GeoMesh>(
			IOobject("cmptMultiply" "(" + df1.name() + ',' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, cmptMultiply(df1.dimensions(), dt2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> cmptMultiply(const DimensionedField<vector6, GeoMesh>& df1, const vector6& t2)
	{
		return cmptMultiply(df1, dimensioned<vector6>(t2));
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> cmptMultiply(const tmp<DimensionedField<vector6, GeoMesh>>& tdf1
	                                                     , const dimensioned<vector6>& dt2)
	{
		const DimensionedField<vector6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector6, GeoMesh>> tRes(reuseTmpDimensionedField<vector6, vector6, GeoMesh>::New(
			tdf1, "cmptMultiply" "(" + df1.name() + ',' + dt2.name() + ')', cmptMultiply(df1.dimensions(), dt2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), dt2.value());
		reuseTmpDimensionedField<vector6, vector6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> cmptMultiply(const tmp<DimensionedField<vector6, GeoMesh>>& tdf1
	                                                     , const vector6& t2)
	{
		return cmptMultiply(tdf1, dimensioned<vector6>(t2));
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                   , const DimensionedField<vector6, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector6, GeoMesh>> tRes(new DimensionedField<vector6, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                   , const tmp<DimensionedField<vector6, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector6, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector6, vector6, GeoMesh>::New(tdf2, '(' + df1.name() + '|' + df2.name() + ')'
			                                                         , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector6, vector6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                   , const DimensionedField<vector6, GeoMesh>& df2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector6, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector6, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + df2.name() + ')'
			                                                        , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector6, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                   , const tmp<DimensionedField<vector6, GeoMesh>>& tdf2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		const DimensionedField<vector6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector6, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<vector6, scalar, scalar, vector6, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<vector6, scalar, scalar, vector6, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator /(const dimensioned<scalar>& dt1
	                                                   , const DimensionedField<vector6, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector6, GeoMesh>> tRes(new DimensionedField<vector6, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator /(const scalar& t1, const DimensionedField<vector6, GeoMesh>& df2)
	{
		return dimensioned<scalar>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator /(const dimensioned<scalar>& dt1
	                                                   , const tmp<DimensionedField<vector6, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector6, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector6, vector6, GeoMesh>::New(tdf2, '(' + dt1.name() + '|' + df2.name() + ')'
			                                                         , dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<vector6, vector6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator /(const scalar& t1
	                                                   , const tmp<DimensionedField<vector6, GeoMesh>>& tdf2)
	{
		return dimensioned<scalar>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                   , const dimensioned<vector6>& dt2)
	{
		tmp<DimensionedField<vector6, GeoMesh>> tRes(new DimensionedField<vector6, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1, const vector6& t2)
	{
		return df1 / dimensioned<vector6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                   , const dimensioned<vector6>& dt2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector6, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector6, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + dt2.name() + ')'
			                                                        , df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<vector6, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                   , const vector6& t2) { return tdf1 / dimensioned<vector6>(t2); }

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator +(const DimensionedField<vector6, GeoMesh>& df1
	                                                   , const DimensionedField<vector6, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector6, GeoMesh>> tRes(new DimensionedField<vector6, GeoMesh>(
			IOobject('(' + df1.name() + '+' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator +(const DimensionedField<vector6, GeoMesh>& df1
	                                                   , const tmp<DimensionedField<vector6, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector6, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector6, vector6, GeoMesh>::New(tdf2, '(' + df1.name() + '+' + df2.name() + ')'
			                                                         , df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector6, vector6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator +(const tmp<DimensionedField<vector6, GeoMesh>>& tdf1
	                                                   , const DimensionedField<vector6, GeoMesh>& df2)
	{
		const DimensionedField<vector6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector6, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector6, vector6, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + df2.name() + ')'
			                                                         , df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector6, vector6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator +(const tmp<DimensionedField<vector6, GeoMesh>>& tdf1
	                                                   , const tmp<DimensionedField<vector6, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector6, GeoMesh>& df1 = tdf1();
		const DimensionedField<vector6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector6, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<vector6, vector6, vector6, vector6, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<vector6, vector6, vector6, vector6, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator -(const DimensionedField<vector6, GeoMesh>& df1
	                                                   , const DimensionedField<vector6, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector6, GeoMesh>> tRes(new DimensionedField<vector6, GeoMesh>(
			IOobject('(' + df1.name() + '-' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator -(const DimensionedField<vector6, GeoMesh>& df1
	                                                   , const tmp<DimensionedField<vector6, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector6, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector6, vector6, GeoMesh>::New(tdf2, '(' + df1.name() + '-' + df2.name() + ')'
			                                                         , df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector6, vector6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator -(const tmp<DimensionedField<vector6, GeoMesh>>& tdf1
	                                                   , const DimensionedField<vector6, GeoMesh>& df2)
	{
		const DimensionedField<vector6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector6, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector6, vector6, GeoMesh>::New(tdf1, '(' + df1.name() + '-' + df2.name() + ')'
			                                                         , df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector6, vector6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator -(const tmp<DimensionedField<vector6, GeoMesh>>& tdf1
	                                                   , const tmp<DimensionedField<vector6, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector6, GeoMesh>& df1 = tdf1();
		const DimensionedField<vector6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector6, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<vector6, vector6, vector6, vector6, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<vector6, vector6, vector6, vector6, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator +(const dimensioned<vector6>& dt1
	                                                   , const DimensionedField<vector6, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector6, GeoMesh>> tRes(new DimensionedField<vector6, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator +(const vector6& t1, const DimensionedField<vector6, GeoMesh>& df2)
	{
		return dimensioned<vector6>(t1) + df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator +(const dimensioned<vector6>& dt1
	                                                   , const tmp<DimensionedField<vector6, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector6, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector6, vector6, GeoMesh>::New(tdf2, '(' + dt1.name() + '+' + df2.name() + ')'
			                                                         , dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<vector6, vector6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator +(const vector6& t1
	                                                   , const tmp<DimensionedField<vector6, GeoMesh>>& tdf2)
	{
		return dimensioned<vector6>(t1) + tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator +(const DimensionedField<vector6, GeoMesh>& df1
	                                                   , const dimensioned<vector6>& dt2)
	{
		tmp<DimensionedField<vector6, GeoMesh>> tRes(new DimensionedField<vector6, GeoMesh>(
			IOobject('(' + df1.name() + '+' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator +(const DimensionedField<vector6, GeoMesh>& df1, const vector6& t2)
	{
		return df1 + dimensioned<vector6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator +(const tmp<DimensionedField<vector6, GeoMesh>>& tdf1
	                                                   , const dimensioned<vector6>& dt2)
	{
		const DimensionedField<vector6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector6, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector6, vector6, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + dt2.name() + ')'
			                                                         , df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<vector6, vector6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator +(const tmp<DimensionedField<vector6, GeoMesh>>& tdf1
	                                                   , const vector6& t2) { return tdf1 + dimensioned<vector6>(t2); }

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator -(const dimensioned<vector6>& dt1
	                                                   , const DimensionedField<vector6, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector6, GeoMesh>> tRes(new DimensionedField<vector6, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator -(const vector6& t1, const DimensionedField<vector6, GeoMesh>& df2)
	{
		return dimensioned<vector6>(t1) - df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator -(const dimensioned<vector6>& dt1
	                                                   , const tmp<DimensionedField<vector6, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector6, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector6, vector6, GeoMesh>::New(tdf2, '(' + dt1.name() + '-' + df2.name() + ')'
			                                                         , dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<vector6, vector6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator -(const vector6& t1
	                                                   , const tmp<DimensionedField<vector6, GeoMesh>>& tdf2)
	{
		return dimensioned<vector6>(t1) - tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator -(const DimensionedField<vector6, GeoMesh>& df1
	                                                   , const dimensioned<vector6>& dt2)
	{
		tmp<DimensionedField<vector6, GeoMesh>> tRes(new DimensionedField<vector6, GeoMesh>(
			IOobject('(' + df1.name() + '-' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator -(const DimensionedField<vector6, GeoMesh>& df1, const vector6& t2)
	{
		return df1 - dimensioned<vector6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator -(const tmp<DimensionedField<vector6, GeoMesh>>& tdf1
	                                                   , const dimensioned<vector6>& dt2)
	{
		const DimensionedField<vector6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector6, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector6, vector6, GeoMesh>::New(tdf1, '(' + df1.name() + '-' + dt2.name() + ')'
			                                                         , df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<vector6, vector6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator -(const tmp<DimensionedField<vector6, GeoMesh>>& tdf1
	                                                   , const vector6& t2) { return tdf1 - dimensioned<vector6>(t2); }

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> cmptSum(const DimensionedField<vector8, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("cmptSum" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), cmptSum(df1.dimensions())));
		cmptSum(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> cmptSum(const tmp<DimensionedField<vector8, GeoMesh>>& tdf1)
	{
		const DimensionedField<vector8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, vector8, GeoMesh>::New(tdf1, "cmptSum" "(" + df1.name() + ')'
			                                                        , cmptSum(df1.dimensions())));
		cmptSum(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, vector8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> cmptMultiply(const DimensionedField<vector8, GeoMesh>& df1
	                                                     , const DimensionedField<vector8, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector8, GeoMesh>> tRes(new DimensionedField<vector8, GeoMesh>(
			IOobject("cmptMultiply" "(" + df1.name() + ',' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, cmptMultiply(df1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> cmptMultiply(const DimensionedField<vector8, GeoMesh>& df1
	                                                     , const tmp<DimensionedField<vector8, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector8, GeoMesh>> tRes(reuseTmpDimensionedField<vector8, vector8, GeoMesh>::New(
			tdf2, "cmptMultiply" "(" + df1.name() + ',' + df2.name() + ')', cmptMultiply(df1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector8, vector8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> cmptMultiply(const tmp<DimensionedField<vector8, GeoMesh>>& tdf1
	                                                     , const DimensionedField<vector8, GeoMesh>& df2)
	{
		const DimensionedField<vector8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector8, GeoMesh>> tRes(reuseTmpDimensionedField<vector8, vector8, GeoMesh>::New(
			tdf1, "cmptMultiply" "(" + df1.name() + ',' + df2.name() + ')', cmptMultiply(df1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector8, vector8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> cmptMultiply(const tmp<DimensionedField<vector8, GeoMesh>>& tdf1
	                                                     , const tmp<DimensionedField<vector8, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector8, GeoMesh>& df1 = tdf1();
		const DimensionedField<vector8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector8, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<vector8, vector8, vector8, vector8, GeoMesh>::New(
				tdf1, tdf2, "cmptMultiply" "(" + df1.name() + ',' + df2.name() + ')'
				, cmptMultiply(df1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<vector8, vector8, vector8, vector8, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> cmptMultiply(const dimensioned<vector8>& dt1
	                                                     , const DimensionedField<vector8, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector8, GeoMesh>> tRes(new DimensionedField<vector8, GeoMesh>(
			IOobject("cmptMultiply" "(" + dt1.name() + ',' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, cmptMultiply(dt1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> cmptMultiply(const vector8& t1, const DimensionedField<vector8, GeoMesh>& df2)
	{
		return cmptMultiply(dimensioned<vector8>(t1), df2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> cmptMultiply(const dimensioned<vector8>& dt1
	                                                     , const tmp<DimensionedField<vector8, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector8, GeoMesh>> tRes(reuseTmpDimensionedField<vector8, vector8, GeoMesh>::New(
			tdf2, "cmptMultiply" "(" + dt1.name() + ',' + df2.name() + ')', cmptMultiply(dt1.dimensions(), df2.dimensions())));
		cmptMultiply(tRes().field(), dt1.value(), df2.field());
		reuseTmpDimensionedField<vector8, vector8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> cmptMultiply(const vector8& t1
	                                                     , const tmp<DimensionedField<vector8, GeoMesh>>& tdf2)
	{
		return cmptMultiply(dimensioned<vector8>(t1), tdf2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> cmptMultiply(const DimensionedField<vector8, GeoMesh>& df1
	                                                     , const dimensioned<vector8>& dt2)
	{
		tmp<DimensionedField<vector8, GeoMesh>> tRes(new DimensionedField<vector8, GeoMesh>(
			IOobject("cmptMultiply" "(" + df1.name() + ',' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, cmptMultiply(df1.dimensions(), dt2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> cmptMultiply(const DimensionedField<vector8, GeoMesh>& df1, const vector8& t2)
	{
		return cmptMultiply(df1, dimensioned<vector8>(t2));
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> cmptMultiply(const tmp<DimensionedField<vector8, GeoMesh>>& tdf1
	                                                     , const dimensioned<vector8>& dt2)
	{
		const DimensionedField<vector8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector8, GeoMesh>> tRes(reuseTmpDimensionedField<vector8, vector8, GeoMesh>::New(
			tdf1, "cmptMultiply" "(" + df1.name() + ',' + dt2.name() + ')', cmptMultiply(df1.dimensions(), dt2.dimensions())));
		cmptMultiply(tRes().field(), df1.field(), dt2.value());
		reuseTmpDimensionedField<vector8, vector8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> cmptMultiply(const tmp<DimensionedField<vector8, GeoMesh>>& tdf1
	                                                     , const vector8& t2)
	{
		return cmptMultiply(tdf1, dimensioned<vector8>(t2));
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                   , const DimensionedField<vector8, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector8, GeoMesh>> tRes(new DimensionedField<vector8, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                   , const tmp<DimensionedField<vector8, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector8, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector8, vector8, GeoMesh>::New(tdf2, '(' + df1.name() + '|' + df2.name() + ')'
			                                                         , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector8, vector8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                   , const DimensionedField<vector8, GeoMesh>& df2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector8, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector8, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + df2.name() + ')'
			                                                        , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector8, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                   , const tmp<DimensionedField<vector8, GeoMesh>>& tdf2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		const DimensionedField<vector8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector8, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<vector8, scalar, scalar, vector8, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<vector8, scalar, scalar, vector8, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator /(const dimensioned<scalar>& dt1
	                                                   , const DimensionedField<vector8, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector8, GeoMesh>> tRes(new DimensionedField<vector8, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator /(const scalar& t1, const DimensionedField<vector8, GeoMesh>& df2)
	{
		return dimensioned<scalar>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator /(const dimensioned<scalar>& dt1
	                                                   , const tmp<DimensionedField<vector8, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector8, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector8, vector8, GeoMesh>::New(tdf2, '(' + dt1.name() + '|' + df2.name() + ')'
			                                                         , dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<vector8, vector8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator /(const scalar& t1
	                                                   , const tmp<DimensionedField<vector8, GeoMesh>>& tdf2)
	{
		return dimensioned<scalar>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                   , const dimensioned<vector8>& dt2)
	{
		tmp<DimensionedField<vector8, GeoMesh>> tRes(new DimensionedField<vector8, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1, const vector8& t2)
	{
		return df1 / dimensioned<vector8>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                   , const dimensioned<vector8>& dt2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector8, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector8, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + dt2.name() + ')'
			                                                        , df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<vector8, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                   , const vector8& t2) { return tdf1 / dimensioned<vector8>(t2); }

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator +(const DimensionedField<vector8, GeoMesh>& df1
	                                                   , const DimensionedField<vector8, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector8, GeoMesh>> tRes(new DimensionedField<vector8, GeoMesh>(
			IOobject('(' + df1.name() + '+' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator +(const DimensionedField<vector8, GeoMesh>& df1
	                                                   , const tmp<DimensionedField<vector8, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector8, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector8, vector8, GeoMesh>::New(tdf2, '(' + df1.name() + '+' + df2.name() + ')'
			                                                         , df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector8, vector8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator +(const tmp<DimensionedField<vector8, GeoMesh>>& tdf1
	                                                   , const DimensionedField<vector8, GeoMesh>& df2)
	{
		const DimensionedField<vector8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector8, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector8, vector8, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + df2.name() + ')'
			                                                         , df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector8, vector8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator +(const tmp<DimensionedField<vector8, GeoMesh>>& tdf1
	                                                   , const tmp<DimensionedField<vector8, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector8, GeoMesh>& df1 = tdf1();
		const DimensionedField<vector8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector8, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<vector8, vector8, vector8, vector8, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<vector8, vector8, vector8, vector8, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator -(const DimensionedField<vector8, GeoMesh>& df1
	                                                   , const DimensionedField<vector8, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector8, GeoMesh>> tRes(new DimensionedField<vector8, GeoMesh>(
			IOobject('(' + df1.name() + '-' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator -(const DimensionedField<vector8, GeoMesh>& df1
	                                                   , const tmp<DimensionedField<vector8, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector8, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector8, vector8, GeoMesh>::New(tdf2, '(' + df1.name() + '-' + df2.name() + ')'
			                                                         , df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector8, vector8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator -(const tmp<DimensionedField<vector8, GeoMesh>>& tdf1
	                                                   , const DimensionedField<vector8, GeoMesh>& df2)
	{
		const DimensionedField<vector8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector8, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector8, vector8, GeoMesh>::New(tdf1, '(' + df1.name() + '-' + df2.name() + ')'
			                                                         , df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector8, vector8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator -(const tmp<DimensionedField<vector8, GeoMesh>>& tdf1
	                                                   , const tmp<DimensionedField<vector8, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector8, GeoMesh>& df1 = tdf1();
		const DimensionedField<vector8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector8, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<vector8, vector8, vector8, vector8, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<vector8, vector8, vector8, vector8, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator +(const dimensioned<vector8>& dt1
	                                                   , const DimensionedField<vector8, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector8, GeoMesh>> tRes(new DimensionedField<vector8, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator +(const vector8& t1, const DimensionedField<vector8, GeoMesh>& df2)
	{
		return dimensioned<vector8>(t1) + df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator +(const dimensioned<vector8>& dt1
	                                                   , const tmp<DimensionedField<vector8, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector8, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector8, vector8, GeoMesh>::New(tdf2, '(' + dt1.name() + '+' + df2.name() + ')'
			                                                         , dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<vector8, vector8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator +(const vector8& t1
	                                                   , const tmp<DimensionedField<vector8, GeoMesh>>& tdf2)
	{
		return dimensioned<vector8>(t1) + tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator +(const DimensionedField<vector8, GeoMesh>& df1
	                                                   , const dimensioned<vector8>& dt2)
	{
		tmp<DimensionedField<vector8, GeoMesh>> tRes(new DimensionedField<vector8, GeoMesh>(
			IOobject('(' + df1.name() + '+' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator +(const DimensionedField<vector8, GeoMesh>& df1, const vector8& t2)
	{
		return df1 + dimensioned<vector8>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator +(const tmp<DimensionedField<vector8, GeoMesh>>& tdf1
	                                                   , const dimensioned<vector8>& dt2)
	{
		const DimensionedField<vector8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector8, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector8, vector8, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + dt2.name() + ')'
			                                                         , df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<vector8, vector8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator +(const tmp<DimensionedField<vector8, GeoMesh>>& tdf1
	                                                   , const vector8& t2) { return tdf1 + dimensioned<vector8>(t2); }

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator -(const dimensioned<vector8>& dt1
	                                                   , const DimensionedField<vector8, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector8, GeoMesh>> tRes(new DimensionedField<vector8, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator -(const vector8& t1, const DimensionedField<vector8, GeoMesh>& df2)
	{
		return dimensioned<vector8>(t1) - df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator -(const dimensioned<vector8>& dt1
	                                                   , const tmp<DimensionedField<vector8, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector8, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector8, vector8, GeoMesh>::New(tdf2, '(' + dt1.name() + '-' + df2.name() + ')'
			                                                         , dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<vector8, vector8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator -(const vector8& t1
	                                                   , const tmp<DimensionedField<vector8, GeoMesh>>& tdf2)
	{
		return dimensioned<vector8>(t1) - tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator -(const DimensionedField<vector8, GeoMesh>& df1
	                                                   , const dimensioned<vector8>& dt2)
	{
		tmp<DimensionedField<vector8, GeoMesh>> tRes(new DimensionedField<vector8, GeoMesh>(
			IOobject('(' + df1.name() + '-' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator -(const DimensionedField<vector8, GeoMesh>& df1, const vector8& t2)
	{
		return df1 - dimensioned<vector8>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator -(const tmp<DimensionedField<vector8, GeoMesh>>& tdf1
	                                                   , const dimensioned<vector8>& dt2)
	{
		const DimensionedField<vector8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector8, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector8, vector8, GeoMesh>::New(tdf1, '(' + df1.name() + '-' + dt2.name() + ')'
			                                                         , df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<vector8, vector8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator -(const tmp<DimensionedField<vector8, GeoMesh>>& tdf1
	                                                   , const vector8& t2) { return tdf1 - dimensioned<vector8>(t2); }

}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#undef VectorN_FieldFunctions

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <undefFieldFunctionsM.hxx>