#include <DimensionedSphericalTensorNFields.hxx>

#include <DimensionedFieldReuseFunctions.hxx>

#define TEMPLATE template<class GeoMesh>
#include <DimensionedFieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define SphericalTensorN_FieldFunctions(tensorType, diagTensorType,                 \
    sphericalTensorType, vectorType, CmptType, args)                             \
                                                                                    \
UNARY_FUNCTION(sphericalTensorType, sphericalTensorType,inv,inv)                    \
UNARY_FUNCTION(sphericalTensorType, sphericalTensorType,diag,diag)                  \
UNARY_FUNCTION(CmptType, sphericalTensorType, contractLinear,contractLinear)        \
UNARY_FUNCTION(CmptType, sphericalTensorType, contractScalar,contractLinear)        \
                                                                                    \
BINARY_OPERATOR(sphericalTensorType, CmptType, sphericalTensorType, /,'|',divide)   \
BINARY_TYPE_OPERATOR(sphericalTensorType, CmptType, sphericalTensorType, /,'|',divide) \
                                                                                    \
BINARY_OPERATOR(vectorType, vectorType, sphericalTensorType, /,'|',divide)          \
BINARY_TYPE_OPERATOR(vectorType, vectorType, sphericalTensorType, /,'|',divide)     \
                                                                                    \
BINARY_OPERATOR(sphericalTensorType, sphericalTensorType, sphericalTensorType, /,'|',divide)           \
BINARY_TYPE_OPERATOR(sphericalTensorType, sphericalTensorType, sphericalTensorType, /,'|',divide)      \
                                                                                    \
BINARY_OPERATOR(sphericalTensorType, sphericalTensorType, sphericalTensorType, +,'+',add)             \
BINARY_OPERATOR(sphericalTensorType, sphericalTensorType, sphericalTensorType, -,'-',subtract)        \
                                                                                    \
BINARY_TYPE_OPERATOR(sphericalTensorType, sphericalTensorType, sphericalTensorType, +,'+',add)        \
BINARY_TYPE_OPERATOR(sphericalTensorType, sphericalTensorType, sphericalTensorType, -,'-',subtract)


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> inv(const DimensionedField<sphericalTensor2, GeoMesh>& df1)
	{
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(new DimensionedField<sphericalTensor2, GeoMesh>(
			IOobject("inv" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), inv(df1.dimensions())));
		inv(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> inv(const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf1)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor2, sphericalTensor2, GeoMesh>::New(
				tdf1, "inv" "(" + df1.name() + ')', inv(df1.dimensions())));
		inv(tRes().field(), df1.field());
		reuseTmpDimensionedField<sphericalTensor2, sphericalTensor2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> diag(const DimensionedField<sphericalTensor2, GeoMesh>& df1)
	{
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(new DimensionedField<sphericalTensor2, GeoMesh>(
			IOobject("diag" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), diag(df1.dimensions())));
		diag(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> diag(const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf1)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor2, sphericalTensor2, GeoMesh>::New(
				tdf1, "diag" "(" + df1.name() + ')', diag(df1.dimensions())));
		diag(tRes().field(), df1.field());
		reuseTmpDimensionedField<sphericalTensor2, sphericalTensor2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> contractLinear(const DimensionedField<sphericalTensor2, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("contractLinear" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, contractLinear(df1.dimensions())));
		contractLinear(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> contractLinear(const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf1)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, sphericalTensor2, GeoMesh>::New(tdf1, "contractLinear" "(" + df1.name() + ')'
			                                                                 , contractLinear(df1.dimensions())));
		contractLinear(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, sphericalTensor2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> contractScalar(const DimensionedField<sphericalTensor2, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("contractScalar" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, contractLinear(df1.dimensions())));
		contractScalar(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> contractScalar(const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf1)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, sphericalTensor2, GeoMesh>::New(tdf1, "contractScalar" "(" + df1.name() + ')'
			                                                                 , contractLinear(df1.dimensions())));
		contractScalar(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, sphericalTensor2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                            , const DimensionedField<sphericalTensor2, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(new DimensionedField<sphericalTensor2, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                            , const tmp<DimensionedField<sphericalTensor2, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor2, sphericalTensor2, GeoMesh>::New(
				tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor2, sphericalTensor2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                            , const DimensionedField<sphericalTensor2, GeoMesh>& df2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor2, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                 , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor2, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                            , const tmp<DimensionedField<sphericalTensor2, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<sphericalTensor2, scalar, scalar, sphericalTensor2, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<sphericalTensor2, scalar, scalar, sphericalTensor2, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator /(const dimensioned<scalar>& dt1
	                                                            , const DimensionedField<sphericalTensor2, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(new DimensionedField<sphericalTensor2, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator /(const scalar& t1
	                                                            , const DimensionedField<sphericalTensor2, GeoMesh>& df2)
	{
		return dimensioned<scalar>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator /(const dimensioned<scalar>& dt1
	                                                            , const tmp<DimensionedField<sphericalTensor2, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor2, sphericalTensor2, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '|' + df2.name() + ')', dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<sphericalTensor2, sphericalTensor2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator /(const scalar& t1
	                                                            , const tmp<DimensionedField<sphericalTensor2, GeoMesh>>&
	                                                            tdf2) { return dimensioned<scalar>(t1) / tdf2; }

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                            , const dimensioned<sphericalTensor2>& dt2)
	{
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(new DimensionedField<sphericalTensor2, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                            , const sphericalTensor2& t2)
	{
		return df1 / dimensioned<sphericalTensor2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                            , const dimensioned<sphericalTensor2>& dt2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor2, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + dt2.name() + ')'
			                                                                 , df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<sphericalTensor2, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                            , const sphericalTensor2& t2)
	{
		return tdf1 / dimensioned<sphericalTensor2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator /(const DimensionedField<vector2, GeoMesh>& df1
	                                                   , const DimensionedField<sphericalTensor2, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector2, GeoMesh>> tRes(new DimensionedField<vector2, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator /(const DimensionedField<vector2, GeoMesh>& df1
	                                                   , const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector2, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector2, sphericalTensor2, GeoMesh>::New(tdf2, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                  , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector2, sphericalTensor2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator /(const tmp<DimensionedField<vector2, GeoMesh>>& tdf1
	                                                   , const DimensionedField<sphericalTensor2, GeoMesh>& df2)
	{
		const DimensionedField<vector2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector2, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector2, vector2, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + df2.name() + ')'
			                                                         , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector2, vector2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator /(const tmp<DimensionedField<vector2, GeoMesh>>& tdf1
	                                                   , const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector2, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector2, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<vector2, vector2, vector2, sphericalTensor2, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<vector2, vector2, vector2, sphericalTensor2, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator /(const dimensioned<vector2>& dt1
	                                                   , const DimensionedField<sphericalTensor2, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector2, GeoMesh>> tRes(new DimensionedField<vector2, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator /(const vector2& t1
	                                                   , const DimensionedField<sphericalTensor2, GeoMesh>& df2)
	{
		return dimensioned<vector2>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator /(const dimensioned<vector2>& dt1
	                                                   , const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector2, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector2, sphericalTensor2, GeoMesh>::New(tdf2, '(' + dt1.name() + '|' + df2.name() + ')'
			                                                                  , dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<vector2, sphericalTensor2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator /(const vector2& t1
	                                                   , const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf2)
	{
		return dimensioned<vector2>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator /(const DimensionedField<vector2, GeoMesh>& df1
	                                                   , const dimensioned<sphericalTensor2>& dt2)
	{
		tmp<DimensionedField<vector2, GeoMesh>> tRes(new DimensionedField<vector2, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator /(const DimensionedField<vector2, GeoMesh>& df1
	                                                   , const sphericalTensor2& t2)
	{
		return df1 / dimensioned<sphericalTensor2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator /(const tmp<DimensionedField<vector2, GeoMesh>>& tdf1
	                                                   , const dimensioned<sphericalTensor2>& dt2)
	{
		const DimensionedField<vector2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector2, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector2, vector2, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + dt2.name() + ')'
			                                                         , df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<vector2, vector2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator /(const tmp<DimensionedField<vector2, GeoMesh>>& tdf1
	                                                   , const sphericalTensor2& t2)
	{
		return tdf1 / dimensioned<sphericalTensor2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator /(const DimensionedField<sphericalTensor2, GeoMesh>& df1
	                                                            , const DimensionedField<sphericalTensor2, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(new DimensionedField<sphericalTensor2, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator /(const DimensionedField<sphericalTensor2, GeoMesh>& df1
	                                                            , const tmp<DimensionedField<sphericalTensor2, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor2, sphericalTensor2, GeoMesh>::New(
				tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor2, sphericalTensor2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator /(
		const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf1, const DimensionedField<sphericalTensor2, GeoMesh>& df2)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor2, sphericalTensor2, GeoMesh>::New(
				tdf1, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor2, sphericalTensor2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator /(
		const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf1
		, const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<sphericalTensor2, sphericalTensor2, sphericalTensor2, sphericalTensor2, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<sphericalTensor2, sphericalTensor2, sphericalTensor2, sphericalTensor2, GeoMesh>::
			clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator /(const dimensioned<sphericalTensor2>& dt1
	                                                            , const DimensionedField<sphericalTensor2, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(new DimensionedField<sphericalTensor2, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator /(const sphericalTensor2& t1
	                                                            , const DimensionedField<sphericalTensor2, GeoMesh>& df2)
	{
		return dimensioned<sphericalTensor2>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator /(const dimensioned<sphericalTensor2>& dt1
	                                                            , const tmp<DimensionedField<sphericalTensor2, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor2, sphericalTensor2, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '|' + df2.name() + ')', dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<sphericalTensor2, sphericalTensor2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator /(const sphericalTensor2& t1
	                                                            , const tmp<DimensionedField<sphericalTensor2, GeoMesh>>&
	                                                            tdf2) { return dimensioned<sphericalTensor2>(t1) / tdf2; }

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator /(const DimensionedField<sphericalTensor2, GeoMesh>& df1
	                                                            , const dimensioned<sphericalTensor2>& dt2)
	{
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(new DimensionedField<sphericalTensor2, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator /(const DimensionedField<sphericalTensor2, GeoMesh>& df1
	                                                            , const sphericalTensor2& t2)
	{
		return df1 / dimensioned<sphericalTensor2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator /(
		const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf1, const dimensioned<sphericalTensor2>& dt2)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor2, sphericalTensor2, GeoMesh>::New(
				tdf1, '(' + df1.name() + '|' + dt2.name() + ')', df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<sphericalTensor2, sphericalTensor2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator /(
		const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf1, const sphericalTensor2& t2)
	{
		return tdf1 / dimensioned<sphericalTensor2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator +(const DimensionedField<sphericalTensor2, GeoMesh>& df1
	                                                            , const DimensionedField<sphericalTensor2, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(new DimensionedField<sphericalTensor2, GeoMesh>(
			IOobject('(' + df1.name() + '+' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator +(const DimensionedField<sphericalTensor2, GeoMesh>& df1
	                                                            , const tmp<DimensionedField<sphericalTensor2, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor2, sphericalTensor2, GeoMesh>::New(
				tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor2, sphericalTensor2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator +(
		const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf1, const DimensionedField<sphericalTensor2, GeoMesh>& df2)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor2, sphericalTensor2, GeoMesh>::New(
				tdf1, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor2, sphericalTensor2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator +(
		const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf1
		, const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<sphericalTensor2, sphericalTensor2, sphericalTensor2, sphericalTensor2, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<sphericalTensor2, sphericalTensor2, sphericalTensor2, sphericalTensor2, GeoMesh>::
			clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator -(const DimensionedField<sphericalTensor2, GeoMesh>& df1
	                                                            , const DimensionedField<sphericalTensor2, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(new DimensionedField<sphericalTensor2, GeoMesh>(
			IOobject('(' + df1.name() + '-' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator -(const DimensionedField<sphericalTensor2, GeoMesh>& df1
	                                                            , const tmp<DimensionedField<sphericalTensor2, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor2, sphericalTensor2, GeoMesh>::New(
				tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor2, sphericalTensor2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator -(
		const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf1, const DimensionedField<sphericalTensor2, GeoMesh>& df2)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor2, sphericalTensor2, GeoMesh>::New(
				tdf1, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor2, sphericalTensor2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator -(
		const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf1
		, const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<sphericalTensor2, sphericalTensor2, sphericalTensor2, sphericalTensor2, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<sphericalTensor2, sphericalTensor2, sphericalTensor2, sphericalTensor2, GeoMesh>::
			clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator +(const dimensioned<sphericalTensor2>& dt1
	                                                            , const DimensionedField<sphericalTensor2, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(new DimensionedField<sphericalTensor2, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator +(const sphericalTensor2& t1
	                                                            , const DimensionedField<sphericalTensor2, GeoMesh>& df2)
	{
		return dimensioned<sphericalTensor2>(t1) + df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator +(const dimensioned<sphericalTensor2>& dt1
	                                                            , const tmp<DimensionedField<sphericalTensor2, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor2, sphericalTensor2, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '+' + df2.name() + ')', dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<sphericalTensor2, sphericalTensor2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator +(const sphericalTensor2& t1
	                                                            , const tmp<DimensionedField<sphericalTensor2, GeoMesh>>&
	                                                            tdf2) { return dimensioned<sphericalTensor2>(t1) + tdf2; }

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator +(const DimensionedField<sphericalTensor2, GeoMesh>& df1
	                                                            , const dimensioned<sphericalTensor2>& dt2)
	{
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(new DimensionedField<sphericalTensor2, GeoMesh>(
			IOobject('(' + df1.name() + '+' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator +(const DimensionedField<sphericalTensor2, GeoMesh>& df1
	                                                            , const sphericalTensor2& t2)
	{
		return df1 + dimensioned<sphericalTensor2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator +(
		const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf1, const dimensioned<sphericalTensor2>& dt2)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor2, sphericalTensor2, GeoMesh>::New(
				tdf1, '(' + df1.name() + '+' + dt2.name() + ')', df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<sphericalTensor2, sphericalTensor2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator +(
		const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf1, const sphericalTensor2& t2)
	{
		return tdf1 + dimensioned<sphericalTensor2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator -(const dimensioned<sphericalTensor2>& dt1
	                                                            , const DimensionedField<sphericalTensor2, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(new DimensionedField<sphericalTensor2, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator -(const sphericalTensor2& t1
	                                                            , const DimensionedField<sphericalTensor2, GeoMesh>& df2)
	{
		return dimensioned<sphericalTensor2>(t1) - df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator -(const dimensioned<sphericalTensor2>& dt1
	                                                            , const tmp<DimensionedField<sphericalTensor2, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor2, sphericalTensor2, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '-' + df2.name() + ')', dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<sphericalTensor2, sphericalTensor2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator -(const sphericalTensor2& t1
	                                                            , const tmp<DimensionedField<sphericalTensor2, GeoMesh>>&
	                                                            tdf2) { return dimensioned<sphericalTensor2>(t1) - tdf2; }

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator -(const DimensionedField<sphericalTensor2, GeoMesh>& df1
	                                                            , const dimensioned<sphericalTensor2>& dt2)
	{
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(new DimensionedField<sphericalTensor2, GeoMesh>(
			IOobject('(' + df1.name() + '-' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator -(const DimensionedField<sphericalTensor2, GeoMesh>& df1
	                                                            , const sphericalTensor2& t2)
	{
		return df1 - dimensioned<sphericalTensor2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator -(
		const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf1, const dimensioned<sphericalTensor2>& dt2)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor2, sphericalTensor2, GeoMesh>::New(
				tdf1, '(' + df1.name() + '-' + dt2.name() + ')', df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<sphericalTensor2, sphericalTensor2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor2, GeoMesh>> operator -(
		const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf1, const sphericalTensor2& t2)
	{
		return tdf1 - dimensioned<sphericalTensor2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> inv(const DimensionedField<sphericalTensor3, GeoMesh>& df1)
	{
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(new DimensionedField<sphericalTensor3, GeoMesh>(
			IOobject("inv" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), inv(df1.dimensions())));
		inv(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> inv(const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf1)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor3, sphericalTensor3, GeoMesh>::New(
				tdf1, "inv" "(" + df1.name() + ')', inv(df1.dimensions())));
		inv(tRes().field(), df1.field());
		reuseTmpDimensionedField<sphericalTensor3, sphericalTensor3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> diag(const DimensionedField<sphericalTensor3, GeoMesh>& df1)
	{
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(new DimensionedField<sphericalTensor3, GeoMesh>(
			IOobject("diag" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), diag(df1.dimensions())));
		diag(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> diag(const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf1)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor3, sphericalTensor3, GeoMesh>::New(
				tdf1, "diag" "(" + df1.name() + ')', diag(df1.dimensions())));
		diag(tRes().field(), df1.field());
		reuseTmpDimensionedField<sphericalTensor3, sphericalTensor3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> contractLinear(const DimensionedField<sphericalTensor3, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("contractLinear" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, contractLinear(df1.dimensions())));
		contractLinear(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> contractLinear(const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf1)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, sphericalTensor3, GeoMesh>::New(tdf1, "contractLinear" "(" + df1.name() + ')'
			                                                                 , contractLinear(df1.dimensions())));
		contractLinear(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, sphericalTensor3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> contractScalar(const DimensionedField<sphericalTensor3, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("contractScalar" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, contractLinear(df1.dimensions())));
		contractScalar(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> contractScalar(const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf1)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, sphericalTensor3, GeoMesh>::New(tdf1, "contractScalar" "(" + df1.name() + ')'
			                                                                 , contractLinear(df1.dimensions())));
		contractScalar(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, sphericalTensor3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                            , const DimensionedField<sphericalTensor3, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(new DimensionedField<sphericalTensor3, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                            , const tmp<DimensionedField<sphericalTensor3, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor3, sphericalTensor3, GeoMesh>::New(
				tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor3, sphericalTensor3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                            , const DimensionedField<sphericalTensor3, GeoMesh>& df2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor3, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                 , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor3, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                            , const tmp<DimensionedField<sphericalTensor3, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<sphericalTensor3, scalar, scalar, sphericalTensor3, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<sphericalTensor3, scalar, scalar, sphericalTensor3, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator /(const dimensioned<scalar>& dt1
	                                                            , const DimensionedField<sphericalTensor3, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(new DimensionedField<sphericalTensor3, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator /(const scalar& t1
	                                                            , const DimensionedField<sphericalTensor3, GeoMesh>& df2)
	{
		return dimensioned<scalar>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator /(const dimensioned<scalar>& dt1
	                                                            , const tmp<DimensionedField<sphericalTensor3, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor3, sphericalTensor3, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '|' + df2.name() + ')', dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<sphericalTensor3, sphericalTensor3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator /(const scalar& t1
	                                                            , const tmp<DimensionedField<sphericalTensor3, GeoMesh>>&
	                                                            tdf2) { return dimensioned<scalar>(t1) / tdf2; }

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                            , const dimensioned<sphericalTensor3>& dt2)
	{
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(new DimensionedField<sphericalTensor3, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                            , const sphericalTensor3& t2)
	{
		return df1 / dimensioned<sphericalTensor3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                            , const dimensioned<sphericalTensor3>& dt2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor3, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + dt2.name() + ')'
			                                                                 , df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<sphericalTensor3, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                            , const sphericalTensor3& t2)
	{
		return tdf1 / dimensioned<sphericalTensor3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator /(const DimensionedField<vector3, GeoMesh>& df1
	                                                   , const DimensionedField<sphericalTensor3, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector3, GeoMesh>> tRes(new DimensionedField<vector3, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator /(const DimensionedField<vector3, GeoMesh>& df1
	                                                   , const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector3, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector3, sphericalTensor3, GeoMesh>::New(tdf2, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                  , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector3, sphericalTensor3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator /(const tmp<DimensionedField<vector3, GeoMesh>>& tdf1
	                                                   , const DimensionedField<sphericalTensor3, GeoMesh>& df2)
	{
		const DimensionedField<vector3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector3, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector3, vector3, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + df2.name() + ')'
			                                                         , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector3, vector3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator /(const tmp<DimensionedField<vector3, GeoMesh>>& tdf1
	                                                   , const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector3, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector3, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<vector3, vector3, vector3, sphericalTensor3, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<vector3, vector3, vector3, sphericalTensor3, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator /(const dimensioned<vector3>& dt1
	                                                   , const DimensionedField<sphericalTensor3, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector3, GeoMesh>> tRes(new DimensionedField<vector3, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator /(const vector3& t1
	                                                   , const DimensionedField<sphericalTensor3, GeoMesh>& df2)
	{
		return dimensioned<vector3>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator /(const dimensioned<vector3>& dt1
	                                                   , const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector3, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector3, sphericalTensor3, GeoMesh>::New(tdf2, '(' + dt1.name() + '|' + df2.name() + ')'
			                                                                  , dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<vector3, sphericalTensor3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator /(const vector3& t1
	                                                   , const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf2)
	{
		return dimensioned<vector3>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator /(const DimensionedField<vector3, GeoMesh>& df1
	                                                   , const dimensioned<sphericalTensor3>& dt2)
	{
		tmp<DimensionedField<vector3, GeoMesh>> tRes(new DimensionedField<vector3, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator /(const DimensionedField<vector3, GeoMesh>& df1
	                                                   , const sphericalTensor3& t2)
	{
		return df1 / dimensioned<sphericalTensor3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator /(const tmp<DimensionedField<vector3, GeoMesh>>& tdf1
	                                                   , const dimensioned<sphericalTensor3>& dt2)
	{
		const DimensionedField<vector3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector3, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector3, vector3, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + dt2.name() + ')'
			                                                         , df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<vector3, vector3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator /(const tmp<DimensionedField<vector3, GeoMesh>>& tdf1
	                                                   , const sphericalTensor3& t2)
	{
		return tdf1 / dimensioned<sphericalTensor3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator /(const DimensionedField<sphericalTensor3, GeoMesh>& df1
	                                                            , const DimensionedField<sphericalTensor3, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(new DimensionedField<sphericalTensor3, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator /(const DimensionedField<sphericalTensor3, GeoMesh>& df1
	                                                            , const tmp<DimensionedField<sphericalTensor3, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor3, sphericalTensor3, GeoMesh>::New(
				tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor3, sphericalTensor3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator /(
		const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf1, const DimensionedField<sphericalTensor3, GeoMesh>& df2)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor3, sphericalTensor3, GeoMesh>::New(
				tdf1, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor3, sphericalTensor3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator /(
		const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf1
		, const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<sphericalTensor3, sphericalTensor3, sphericalTensor3, sphericalTensor3, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<sphericalTensor3, sphericalTensor3, sphericalTensor3, sphericalTensor3, GeoMesh>::
			clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator /(const dimensioned<sphericalTensor3>& dt1
	                                                            , const DimensionedField<sphericalTensor3, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(new DimensionedField<sphericalTensor3, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator /(const sphericalTensor3& t1
	                                                            , const DimensionedField<sphericalTensor3, GeoMesh>& df2)
	{
		return dimensioned<sphericalTensor3>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator /(const dimensioned<sphericalTensor3>& dt1
	                                                            , const tmp<DimensionedField<sphericalTensor3, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor3, sphericalTensor3, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '|' + df2.name() + ')', dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<sphericalTensor3, sphericalTensor3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator /(const sphericalTensor3& t1
	                                                            , const tmp<DimensionedField<sphericalTensor3, GeoMesh>>&
	                                                            tdf2) { return dimensioned<sphericalTensor3>(t1) / tdf2; }

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator /(const DimensionedField<sphericalTensor3, GeoMesh>& df1
	                                                            , const dimensioned<sphericalTensor3>& dt2)
	{
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(new DimensionedField<sphericalTensor3, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator /(const DimensionedField<sphericalTensor3, GeoMesh>& df1
	                                                            , const sphericalTensor3& t2)
	{
		return df1 / dimensioned<sphericalTensor3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator /(
		const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf1, const dimensioned<sphericalTensor3>& dt2)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor3, sphericalTensor3, GeoMesh>::New(
				tdf1, '(' + df1.name() + '|' + dt2.name() + ')', df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<sphericalTensor3, sphericalTensor3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator /(
		const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf1, const sphericalTensor3& t2)
	{
		return tdf1 / dimensioned<sphericalTensor3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator +(const DimensionedField<sphericalTensor3, GeoMesh>& df1
	                                                            , const DimensionedField<sphericalTensor3, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(new DimensionedField<sphericalTensor3, GeoMesh>(
			IOobject('(' + df1.name() + '+' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator +(const DimensionedField<sphericalTensor3, GeoMesh>& df1
	                                                            , const tmp<DimensionedField<sphericalTensor3, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor3, sphericalTensor3, GeoMesh>::New(
				tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor3, sphericalTensor3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator +(
		const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf1, const DimensionedField<sphericalTensor3, GeoMesh>& df2)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor3, sphericalTensor3, GeoMesh>::New(
				tdf1, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor3, sphericalTensor3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator +(
		const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf1
		, const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<sphericalTensor3, sphericalTensor3, sphericalTensor3, sphericalTensor3, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<sphericalTensor3, sphericalTensor3, sphericalTensor3, sphericalTensor3, GeoMesh>::
			clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator -(const DimensionedField<sphericalTensor3, GeoMesh>& df1
	                                                            , const DimensionedField<sphericalTensor3, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(new DimensionedField<sphericalTensor3, GeoMesh>(
			IOobject('(' + df1.name() + '-' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator -(const DimensionedField<sphericalTensor3, GeoMesh>& df1
	                                                            , const tmp<DimensionedField<sphericalTensor3, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor3, sphericalTensor3, GeoMesh>::New(
				tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor3, sphericalTensor3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator -(
		const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf1, const DimensionedField<sphericalTensor3, GeoMesh>& df2)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor3, sphericalTensor3, GeoMesh>::New(
				tdf1, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor3, sphericalTensor3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator -(
		const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf1
		, const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<sphericalTensor3, sphericalTensor3, sphericalTensor3, sphericalTensor3, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<sphericalTensor3, sphericalTensor3, sphericalTensor3, sphericalTensor3, GeoMesh>::
			clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator +(const dimensioned<sphericalTensor3>& dt1
	                                                            , const DimensionedField<sphericalTensor3, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(new DimensionedField<sphericalTensor3, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator +(const sphericalTensor3& t1
	                                                            , const DimensionedField<sphericalTensor3, GeoMesh>& df2)
	{
		return dimensioned<sphericalTensor3>(t1) + df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator +(const dimensioned<sphericalTensor3>& dt1
	                                                            , const tmp<DimensionedField<sphericalTensor3, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor3, sphericalTensor3, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '+' + df2.name() + ')', dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<sphericalTensor3, sphericalTensor3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator +(const sphericalTensor3& t1
	                                                            , const tmp<DimensionedField<sphericalTensor3, GeoMesh>>&
	                                                            tdf2) { return dimensioned<sphericalTensor3>(t1) + tdf2; }

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator +(const DimensionedField<sphericalTensor3, GeoMesh>& df1
	                                                            , const dimensioned<sphericalTensor3>& dt2)
	{
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(new DimensionedField<sphericalTensor3, GeoMesh>(
			IOobject('(' + df1.name() + '+' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator +(const DimensionedField<sphericalTensor3, GeoMesh>& df1
	                                                            , const sphericalTensor3& t2)
	{
		return df1 + dimensioned<sphericalTensor3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator +(
		const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf1, const dimensioned<sphericalTensor3>& dt2)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor3, sphericalTensor3, GeoMesh>::New(
				tdf1, '(' + df1.name() + '+' + dt2.name() + ')', df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<sphericalTensor3, sphericalTensor3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator +(
		const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf1, const sphericalTensor3& t2)
	{
		return tdf1 + dimensioned<sphericalTensor3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator -(const dimensioned<sphericalTensor3>& dt1
	                                                            , const DimensionedField<sphericalTensor3, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(new DimensionedField<sphericalTensor3, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator -(const sphericalTensor3& t1
	                                                            , const DimensionedField<sphericalTensor3, GeoMesh>& df2)
	{
		return dimensioned<sphericalTensor3>(t1) - df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator -(const dimensioned<sphericalTensor3>& dt1
	                                                            , const tmp<DimensionedField<sphericalTensor3, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor3, sphericalTensor3, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '-' + df2.name() + ')', dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<sphericalTensor3, sphericalTensor3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator -(const sphericalTensor3& t1
	                                                            , const tmp<DimensionedField<sphericalTensor3, GeoMesh>>&
	                                                            tdf2) { return dimensioned<sphericalTensor3>(t1) - tdf2; }

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator -(const DimensionedField<sphericalTensor3, GeoMesh>& df1
	                                                            , const dimensioned<sphericalTensor3>& dt2)
	{
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(new DimensionedField<sphericalTensor3, GeoMesh>(
			IOobject('(' + df1.name() + '-' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator -(const DimensionedField<sphericalTensor3, GeoMesh>& df1
	                                                            , const sphericalTensor3& t2)
	{
		return df1 - dimensioned<sphericalTensor3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator -(
		const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf1, const dimensioned<sphericalTensor3>& dt2)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor3, sphericalTensor3, GeoMesh>::New(
				tdf1, '(' + df1.name() + '-' + dt2.name() + ')', df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<sphericalTensor3, sphericalTensor3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor3, GeoMesh>> operator -(
		const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf1, const sphericalTensor3& t2)
	{
		return tdf1 - dimensioned<sphericalTensor3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> inv(const DimensionedField<sphericalTensor4, GeoMesh>& df1)
	{
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(new DimensionedField<sphericalTensor4, GeoMesh>(
			IOobject("inv" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), inv(df1.dimensions())));
		inv(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> inv(const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf1)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor4, sphericalTensor4, GeoMesh>::New(
				tdf1, "inv" "(" + df1.name() + ')', inv(df1.dimensions())));
		inv(tRes().field(), df1.field());
		reuseTmpDimensionedField<sphericalTensor4, sphericalTensor4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> diag(const DimensionedField<sphericalTensor4, GeoMesh>& df1)
	{
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(new DimensionedField<sphericalTensor4, GeoMesh>(
			IOobject("diag" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), diag(df1.dimensions())));
		diag(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> diag(const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf1)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor4, sphericalTensor4, GeoMesh>::New(
				tdf1, "diag" "(" + df1.name() + ')', diag(df1.dimensions())));
		diag(tRes().field(), df1.field());
		reuseTmpDimensionedField<sphericalTensor4, sphericalTensor4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> contractLinear(const DimensionedField<sphericalTensor4, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("contractLinear" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, contractLinear(df1.dimensions())));
		contractLinear(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> contractLinear(const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf1)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, sphericalTensor4, GeoMesh>::New(tdf1, "contractLinear" "(" + df1.name() + ')'
			                                                                 , contractLinear(df1.dimensions())));
		contractLinear(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, sphericalTensor4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> contractScalar(const DimensionedField<sphericalTensor4, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("contractScalar" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, contractLinear(df1.dimensions())));
		contractScalar(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> contractScalar(const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf1)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, sphericalTensor4, GeoMesh>::New(tdf1, "contractScalar" "(" + df1.name() + ')'
			                                                                 , contractLinear(df1.dimensions())));
		contractScalar(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, sphericalTensor4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                            , const DimensionedField<sphericalTensor4, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(new DimensionedField<sphericalTensor4, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                            , const tmp<DimensionedField<sphericalTensor4, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor4, sphericalTensor4, GeoMesh>::New(
				tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor4, sphericalTensor4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                            , const DimensionedField<sphericalTensor4, GeoMesh>& df2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor4, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                 , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor4, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                            , const tmp<DimensionedField<sphericalTensor4, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<sphericalTensor4, scalar, scalar, sphericalTensor4, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<sphericalTensor4, scalar, scalar, sphericalTensor4, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator /(const dimensioned<scalar>& dt1
	                                                            , const DimensionedField<sphericalTensor4, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(new DimensionedField<sphericalTensor4, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator /(const scalar& t1
	                                                            , const DimensionedField<sphericalTensor4, GeoMesh>& df2)
	{
		return dimensioned<scalar>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator /(const dimensioned<scalar>& dt1
	                                                            , const tmp<DimensionedField<sphericalTensor4, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor4, sphericalTensor4, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '|' + df2.name() + ')', dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<sphericalTensor4, sphericalTensor4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator /(const scalar& t1
	                                                            , const tmp<DimensionedField<sphericalTensor4, GeoMesh>>&
	                                                            tdf2) { return dimensioned<scalar>(t1) / tdf2; }

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                            , const dimensioned<sphericalTensor4>& dt2)
	{
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(new DimensionedField<sphericalTensor4, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                            , const sphericalTensor4& t2)
	{
		return df1 / dimensioned<sphericalTensor4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                            , const dimensioned<sphericalTensor4>& dt2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor4, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + dt2.name() + ')'
			                                                                 , df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<sphericalTensor4, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                            , const sphericalTensor4& t2)
	{
		return tdf1 / dimensioned<sphericalTensor4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator /(const DimensionedField<vector4, GeoMesh>& df1
	                                                   , const DimensionedField<sphericalTensor4, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector4, GeoMesh>> tRes(new DimensionedField<vector4, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator /(const DimensionedField<vector4, GeoMesh>& df1
	                                                   , const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector4, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector4, sphericalTensor4, GeoMesh>::New(tdf2, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                  , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector4, sphericalTensor4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator /(const tmp<DimensionedField<vector4, GeoMesh>>& tdf1
	                                                   , const DimensionedField<sphericalTensor4, GeoMesh>& df2)
	{
		const DimensionedField<vector4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector4, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector4, vector4, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + df2.name() + ')'
			                                                         , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector4, vector4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator /(const tmp<DimensionedField<vector4, GeoMesh>>& tdf1
	                                                   , const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector4, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector4, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<vector4, vector4, vector4, sphericalTensor4, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<vector4, vector4, vector4, sphericalTensor4, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator /(const dimensioned<vector4>& dt1
	                                                   , const DimensionedField<sphericalTensor4, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector4, GeoMesh>> tRes(new DimensionedField<vector4, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator /(const vector4& t1
	                                                   , const DimensionedField<sphericalTensor4, GeoMesh>& df2)
	{
		return dimensioned<vector4>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator /(const dimensioned<vector4>& dt1
	                                                   , const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector4, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector4, sphericalTensor4, GeoMesh>::New(tdf2, '(' + dt1.name() + '|' + df2.name() + ')'
			                                                                  , dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<vector4, sphericalTensor4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator /(const vector4& t1
	                                                   , const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf2)
	{
		return dimensioned<vector4>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator /(const DimensionedField<vector4, GeoMesh>& df1
	                                                   , const dimensioned<sphericalTensor4>& dt2)
	{
		tmp<DimensionedField<vector4, GeoMesh>> tRes(new DimensionedField<vector4, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator /(const DimensionedField<vector4, GeoMesh>& df1
	                                                   , const sphericalTensor4& t2)
	{
		return df1 / dimensioned<sphericalTensor4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator /(const tmp<DimensionedField<vector4, GeoMesh>>& tdf1
	                                                   , const dimensioned<sphericalTensor4>& dt2)
	{
		const DimensionedField<vector4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector4, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector4, vector4, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + dt2.name() + ')'
			                                                         , df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<vector4, vector4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator /(const tmp<DimensionedField<vector4, GeoMesh>>& tdf1
	                                                   , const sphericalTensor4& t2)
	{
		return tdf1 / dimensioned<sphericalTensor4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator /(const DimensionedField<sphericalTensor4, GeoMesh>& df1
	                                                            , const DimensionedField<sphericalTensor4, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(new DimensionedField<sphericalTensor4, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator /(const DimensionedField<sphericalTensor4, GeoMesh>& df1
	                                                            , const tmp<DimensionedField<sphericalTensor4, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor4, sphericalTensor4, GeoMesh>::New(
				tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor4, sphericalTensor4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator /(
		const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf1, const DimensionedField<sphericalTensor4, GeoMesh>& df2)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor4, sphericalTensor4, GeoMesh>::New(
				tdf1, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor4, sphericalTensor4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator /(
		const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf1
		, const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<sphericalTensor4, sphericalTensor4, sphericalTensor4, sphericalTensor4, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<sphericalTensor4, sphericalTensor4, sphericalTensor4, sphericalTensor4, GeoMesh>::
			clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator /(const dimensioned<sphericalTensor4>& dt1
	                                                            , const DimensionedField<sphericalTensor4, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(new DimensionedField<sphericalTensor4, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator /(const sphericalTensor4& t1
	                                                            , const DimensionedField<sphericalTensor4, GeoMesh>& df2)
	{
		return dimensioned<sphericalTensor4>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator /(const dimensioned<sphericalTensor4>& dt1
	                                                            , const tmp<DimensionedField<sphericalTensor4, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor4, sphericalTensor4, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '|' + df2.name() + ')', dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<sphericalTensor4, sphericalTensor4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator /(const sphericalTensor4& t1
	                                                            , const tmp<DimensionedField<sphericalTensor4, GeoMesh>>&
	                                                            tdf2) { return dimensioned<sphericalTensor4>(t1) / tdf2; }

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator /(const DimensionedField<sphericalTensor4, GeoMesh>& df1
	                                                            , const dimensioned<sphericalTensor4>& dt2)
	{
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(new DimensionedField<sphericalTensor4, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator /(const DimensionedField<sphericalTensor4, GeoMesh>& df1
	                                                            , const sphericalTensor4& t2)
	{
		return df1 / dimensioned<sphericalTensor4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator /(
		const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf1, const dimensioned<sphericalTensor4>& dt2)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor4, sphericalTensor4, GeoMesh>::New(
				tdf1, '(' + df1.name() + '|' + dt2.name() + ')', df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<sphericalTensor4, sphericalTensor4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator /(
		const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf1, const sphericalTensor4& t2)
	{
		return tdf1 / dimensioned<sphericalTensor4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator +(const DimensionedField<sphericalTensor4, GeoMesh>& df1
	                                                            , const DimensionedField<sphericalTensor4, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(new DimensionedField<sphericalTensor4, GeoMesh>(
			IOobject('(' + df1.name() + '+' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator +(const DimensionedField<sphericalTensor4, GeoMesh>& df1
	                                                            , const tmp<DimensionedField<sphericalTensor4, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor4, sphericalTensor4, GeoMesh>::New(
				tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor4, sphericalTensor4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator +(
		const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf1, const DimensionedField<sphericalTensor4, GeoMesh>& df2)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor4, sphericalTensor4, GeoMesh>::New(
				tdf1, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor4, sphericalTensor4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator +(
		const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf1
		, const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<sphericalTensor4, sphericalTensor4, sphericalTensor4, sphericalTensor4, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<sphericalTensor4, sphericalTensor4, sphericalTensor4, sphericalTensor4, GeoMesh>::
			clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator -(const DimensionedField<sphericalTensor4, GeoMesh>& df1
	                                                            , const DimensionedField<sphericalTensor4, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(new DimensionedField<sphericalTensor4, GeoMesh>(
			IOobject('(' + df1.name() + '-' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator -(const DimensionedField<sphericalTensor4, GeoMesh>& df1
	                                                            , const tmp<DimensionedField<sphericalTensor4, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor4, sphericalTensor4, GeoMesh>::New(
				tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor4, sphericalTensor4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator -(
		const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf1, const DimensionedField<sphericalTensor4, GeoMesh>& df2)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor4, sphericalTensor4, GeoMesh>::New(
				tdf1, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor4, sphericalTensor4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator -(
		const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf1
		, const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<sphericalTensor4, sphericalTensor4, sphericalTensor4, sphericalTensor4, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<sphericalTensor4, sphericalTensor4, sphericalTensor4, sphericalTensor4, GeoMesh>::
			clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator +(const dimensioned<sphericalTensor4>& dt1
	                                                            , const DimensionedField<sphericalTensor4, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(new DimensionedField<sphericalTensor4, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator +(const sphericalTensor4& t1
	                                                            , const DimensionedField<sphericalTensor4, GeoMesh>& df2)
	{
		return dimensioned<sphericalTensor4>(t1) + df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator +(const dimensioned<sphericalTensor4>& dt1
	                                                            , const tmp<DimensionedField<sphericalTensor4, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor4, sphericalTensor4, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '+' + df2.name() + ')', dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<sphericalTensor4, sphericalTensor4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator +(const sphericalTensor4& t1
	                                                            , const tmp<DimensionedField<sphericalTensor4, GeoMesh>>&
	                                                            tdf2) { return dimensioned<sphericalTensor4>(t1) + tdf2; }

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator +(const DimensionedField<sphericalTensor4, GeoMesh>& df1
	                                                            , const dimensioned<sphericalTensor4>& dt2)
	{
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(new DimensionedField<sphericalTensor4, GeoMesh>(
			IOobject('(' + df1.name() + '+' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator +(const DimensionedField<sphericalTensor4, GeoMesh>& df1
	                                                            , const sphericalTensor4& t2)
	{
		return df1 + dimensioned<sphericalTensor4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator +(
		const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf1, const dimensioned<sphericalTensor4>& dt2)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor4, sphericalTensor4, GeoMesh>::New(
				tdf1, '(' + df1.name() + '+' + dt2.name() + ')', df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<sphericalTensor4, sphericalTensor4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator +(
		const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf1, const sphericalTensor4& t2)
	{
		return tdf1 + dimensioned<sphericalTensor4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator -(const dimensioned<sphericalTensor4>& dt1
	                                                            , const DimensionedField<sphericalTensor4, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(new DimensionedField<sphericalTensor4, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator -(const sphericalTensor4& t1
	                                                            , const DimensionedField<sphericalTensor4, GeoMesh>& df2)
	{
		return dimensioned<sphericalTensor4>(t1) - df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator -(const dimensioned<sphericalTensor4>& dt1
	                                                            , const tmp<DimensionedField<sphericalTensor4, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor4, sphericalTensor4, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '-' + df2.name() + ')', dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<sphericalTensor4, sphericalTensor4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator -(const sphericalTensor4& t1
	                                                            , const tmp<DimensionedField<sphericalTensor4, GeoMesh>>&
	                                                            tdf2) { return dimensioned<sphericalTensor4>(t1) - tdf2; }

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator -(const DimensionedField<sphericalTensor4, GeoMesh>& df1
	                                                            , const dimensioned<sphericalTensor4>& dt2)
	{
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(new DimensionedField<sphericalTensor4, GeoMesh>(
			IOobject('(' + df1.name() + '-' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator -(const DimensionedField<sphericalTensor4, GeoMesh>& df1
	                                                            , const sphericalTensor4& t2)
	{
		return df1 - dimensioned<sphericalTensor4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator -(
		const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf1, const dimensioned<sphericalTensor4>& dt2)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor4, sphericalTensor4, GeoMesh>::New(
				tdf1, '(' + df1.name() + '-' + dt2.name() + ')', df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<sphericalTensor4, sphericalTensor4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor4, GeoMesh>> operator -(
		const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf1, const sphericalTensor4& t2)
	{
		return tdf1 - dimensioned<sphericalTensor4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> inv(const DimensionedField<sphericalTensor6, GeoMesh>& df1)
	{
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(new DimensionedField<sphericalTensor6, GeoMesh>(
			IOobject("inv" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), inv(df1.dimensions())));
		inv(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> inv(const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf1)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor6, sphericalTensor6, GeoMesh>::New(
				tdf1, "inv" "(" + df1.name() + ')', inv(df1.dimensions())));
		inv(tRes().field(), df1.field());
		reuseTmpDimensionedField<sphericalTensor6, sphericalTensor6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> diag(const DimensionedField<sphericalTensor6, GeoMesh>& df1)
	{
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(new DimensionedField<sphericalTensor6, GeoMesh>(
			IOobject("diag" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), diag(df1.dimensions())));
		diag(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> diag(const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf1)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor6, sphericalTensor6, GeoMesh>::New(
				tdf1, "diag" "(" + df1.name() + ')', diag(df1.dimensions())));
		diag(tRes().field(), df1.field());
		reuseTmpDimensionedField<sphericalTensor6, sphericalTensor6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> contractLinear(const DimensionedField<sphericalTensor6, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("contractLinear" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, contractLinear(df1.dimensions())));
		contractLinear(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> contractLinear(const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf1)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, sphericalTensor6, GeoMesh>::New(tdf1, "contractLinear" "(" + df1.name() + ')'
			                                                                 , contractLinear(df1.dimensions())));
		contractLinear(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, sphericalTensor6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> contractScalar(const DimensionedField<sphericalTensor6, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("contractScalar" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, contractLinear(df1.dimensions())));
		contractScalar(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> contractScalar(const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf1)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, sphericalTensor6, GeoMesh>::New(tdf1, "contractScalar" "(" + df1.name() + ')'
			                                                                 , contractLinear(df1.dimensions())));
		contractScalar(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, sphericalTensor6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                            , const DimensionedField<sphericalTensor6, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(new DimensionedField<sphericalTensor6, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                            , const tmp<DimensionedField<sphericalTensor6, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor6, sphericalTensor6, GeoMesh>::New(
				tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor6, sphericalTensor6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                            , const DimensionedField<sphericalTensor6, GeoMesh>& df2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor6, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                 , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor6, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                            , const tmp<DimensionedField<sphericalTensor6, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<sphericalTensor6, scalar, scalar, sphericalTensor6, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<sphericalTensor6, scalar, scalar, sphericalTensor6, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator /(const dimensioned<scalar>& dt1
	                                                            , const DimensionedField<sphericalTensor6, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(new DimensionedField<sphericalTensor6, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator /(const scalar& t1
	                                                            , const DimensionedField<sphericalTensor6, GeoMesh>& df2)
	{
		return dimensioned<scalar>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator /(const dimensioned<scalar>& dt1
	                                                            , const tmp<DimensionedField<sphericalTensor6, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor6, sphericalTensor6, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '|' + df2.name() + ')', dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<sphericalTensor6, sphericalTensor6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator /(const scalar& t1
	                                                            , const tmp<DimensionedField<sphericalTensor6, GeoMesh>>&
	                                                            tdf2) { return dimensioned<scalar>(t1) / tdf2; }

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                            , const dimensioned<sphericalTensor6>& dt2)
	{
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(new DimensionedField<sphericalTensor6, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                            , const sphericalTensor6& t2)
	{
		return df1 / dimensioned<sphericalTensor6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                            , const dimensioned<sphericalTensor6>& dt2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor6, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + dt2.name() + ')'
			                                                                 , df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<sphericalTensor6, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                            , const sphericalTensor6& t2)
	{
		return tdf1 / dimensioned<sphericalTensor6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator /(const DimensionedField<vector6, GeoMesh>& df1
	                                                   , const DimensionedField<sphericalTensor6, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector6, GeoMesh>> tRes(new DimensionedField<vector6, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator /(const DimensionedField<vector6, GeoMesh>& df1
	                                                   , const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector6, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector6, sphericalTensor6, GeoMesh>::New(tdf2, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                  , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector6, sphericalTensor6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator /(const tmp<DimensionedField<vector6, GeoMesh>>& tdf1
	                                                   , const DimensionedField<sphericalTensor6, GeoMesh>& df2)
	{
		const DimensionedField<vector6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector6, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector6, vector6, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + df2.name() + ')'
			                                                         , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector6, vector6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator /(const tmp<DimensionedField<vector6, GeoMesh>>& tdf1
	                                                   , const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector6, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector6, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<vector6, vector6, vector6, sphericalTensor6, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<vector6, vector6, vector6, sphericalTensor6, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator /(const dimensioned<vector6>& dt1
	                                                   , const DimensionedField<sphericalTensor6, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector6, GeoMesh>> tRes(new DimensionedField<vector6, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator /(const vector6& t1
	                                                   , const DimensionedField<sphericalTensor6, GeoMesh>& df2)
	{
		return dimensioned<vector6>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator /(const dimensioned<vector6>& dt1
	                                                   , const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector6, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector6, sphericalTensor6, GeoMesh>::New(tdf2, '(' + dt1.name() + '|' + df2.name() + ')'
			                                                                  , dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<vector6, sphericalTensor6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator /(const vector6& t1
	                                                   , const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf2)
	{
		return dimensioned<vector6>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator /(const DimensionedField<vector6, GeoMesh>& df1
	                                                   , const dimensioned<sphericalTensor6>& dt2)
	{
		tmp<DimensionedField<vector6, GeoMesh>> tRes(new DimensionedField<vector6, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator /(const DimensionedField<vector6, GeoMesh>& df1
	                                                   , const sphericalTensor6& t2)
	{
		return df1 / dimensioned<sphericalTensor6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator /(const tmp<DimensionedField<vector6, GeoMesh>>& tdf1
	                                                   , const dimensioned<sphericalTensor6>& dt2)
	{
		const DimensionedField<vector6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector6, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector6, vector6, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + dt2.name() + ')'
			                                                         , df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<vector6, vector6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator /(const tmp<DimensionedField<vector6, GeoMesh>>& tdf1
	                                                   , const sphericalTensor6& t2)
	{
		return tdf1 / dimensioned<sphericalTensor6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator /(const DimensionedField<sphericalTensor6, GeoMesh>& df1
	                                                            , const DimensionedField<sphericalTensor6, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(new DimensionedField<sphericalTensor6, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator /(const DimensionedField<sphericalTensor6, GeoMesh>& df1
	                                                            , const tmp<DimensionedField<sphericalTensor6, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor6, sphericalTensor6, GeoMesh>::New(
				tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor6, sphericalTensor6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator /(
		const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf1, const DimensionedField<sphericalTensor6, GeoMesh>& df2)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor6, sphericalTensor6, GeoMesh>::New(
				tdf1, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor6, sphericalTensor6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator /(
		const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf1
		, const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<sphericalTensor6, sphericalTensor6, sphericalTensor6, sphericalTensor6, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<sphericalTensor6, sphericalTensor6, sphericalTensor6, sphericalTensor6, GeoMesh>::
			clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator /(const dimensioned<sphericalTensor6>& dt1
	                                                            , const DimensionedField<sphericalTensor6, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(new DimensionedField<sphericalTensor6, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator /(const sphericalTensor6& t1
	                                                            , const DimensionedField<sphericalTensor6, GeoMesh>& df2)
	{
		return dimensioned<sphericalTensor6>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator /(const dimensioned<sphericalTensor6>& dt1
	                                                            , const tmp<DimensionedField<sphericalTensor6, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor6, sphericalTensor6, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '|' + df2.name() + ')', dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<sphericalTensor6, sphericalTensor6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator /(const sphericalTensor6& t1
	                                                            , const tmp<DimensionedField<sphericalTensor6, GeoMesh>>&
	                                                            tdf2) { return dimensioned<sphericalTensor6>(t1) / tdf2; }

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator /(const DimensionedField<sphericalTensor6, GeoMesh>& df1
	                                                            , const dimensioned<sphericalTensor6>& dt2)
	{
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(new DimensionedField<sphericalTensor6, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator /(const DimensionedField<sphericalTensor6, GeoMesh>& df1
	                                                            , const sphericalTensor6& t2)
	{
		return df1 / dimensioned<sphericalTensor6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator /(
		const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf1, const dimensioned<sphericalTensor6>& dt2)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor6, sphericalTensor6, GeoMesh>::New(
				tdf1, '(' + df1.name() + '|' + dt2.name() + ')', df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<sphericalTensor6, sphericalTensor6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator /(
		const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf1, const sphericalTensor6& t2)
	{
		return tdf1 / dimensioned<sphericalTensor6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator +(const DimensionedField<sphericalTensor6, GeoMesh>& df1
	                                                            , const DimensionedField<sphericalTensor6, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(new DimensionedField<sphericalTensor6, GeoMesh>(
			IOobject('(' + df1.name() + '+' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator +(const DimensionedField<sphericalTensor6, GeoMesh>& df1
	                                                            , const tmp<DimensionedField<sphericalTensor6, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor6, sphericalTensor6, GeoMesh>::New(
				tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor6, sphericalTensor6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator +(
		const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf1, const DimensionedField<sphericalTensor6, GeoMesh>& df2)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor6, sphericalTensor6, GeoMesh>::New(
				tdf1, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor6, sphericalTensor6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator +(
		const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf1
		, const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<sphericalTensor6, sphericalTensor6, sphericalTensor6, sphericalTensor6, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<sphericalTensor6, sphericalTensor6, sphericalTensor6, sphericalTensor6, GeoMesh>::
			clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator -(const DimensionedField<sphericalTensor6, GeoMesh>& df1
	                                                            , const DimensionedField<sphericalTensor6, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(new DimensionedField<sphericalTensor6, GeoMesh>(
			IOobject('(' + df1.name() + '-' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator -(const DimensionedField<sphericalTensor6, GeoMesh>& df1
	                                                            , const tmp<DimensionedField<sphericalTensor6, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor6, sphericalTensor6, GeoMesh>::New(
				tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor6, sphericalTensor6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator -(
		const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf1, const DimensionedField<sphericalTensor6, GeoMesh>& df2)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor6, sphericalTensor6, GeoMesh>::New(
				tdf1, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor6, sphericalTensor6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator -(
		const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf1
		, const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<sphericalTensor6, sphericalTensor6, sphericalTensor6, sphericalTensor6, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<sphericalTensor6, sphericalTensor6, sphericalTensor6, sphericalTensor6, GeoMesh>::
			clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator +(const dimensioned<sphericalTensor6>& dt1
	                                                            , const DimensionedField<sphericalTensor6, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(new DimensionedField<sphericalTensor6, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator +(const sphericalTensor6& t1
	                                                            , const DimensionedField<sphericalTensor6, GeoMesh>& df2)
	{
		return dimensioned<sphericalTensor6>(t1) + df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator +(const dimensioned<sphericalTensor6>& dt1
	                                                            , const tmp<DimensionedField<sphericalTensor6, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor6, sphericalTensor6, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '+' + df2.name() + ')', dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<sphericalTensor6, sphericalTensor6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator +(const sphericalTensor6& t1
	                                                            , const tmp<DimensionedField<sphericalTensor6, GeoMesh>>&
	                                                            tdf2) { return dimensioned<sphericalTensor6>(t1) + tdf2; }

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator +(const DimensionedField<sphericalTensor6, GeoMesh>& df1
	                                                            , const dimensioned<sphericalTensor6>& dt2)
	{
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(new DimensionedField<sphericalTensor6, GeoMesh>(
			IOobject('(' + df1.name() + '+' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator +(const DimensionedField<sphericalTensor6, GeoMesh>& df1
	                                                            , const sphericalTensor6& t2)
	{
		return df1 + dimensioned<sphericalTensor6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator +(
		const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf1, const dimensioned<sphericalTensor6>& dt2)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor6, sphericalTensor6, GeoMesh>::New(
				tdf1, '(' + df1.name() + '+' + dt2.name() + ')', df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<sphericalTensor6, sphericalTensor6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator +(
		const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf1, const sphericalTensor6& t2)
	{
		return tdf1 + dimensioned<sphericalTensor6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator -(const dimensioned<sphericalTensor6>& dt1
	                                                            , const DimensionedField<sphericalTensor6, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(new DimensionedField<sphericalTensor6, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator -(const sphericalTensor6& t1
	                                                            , const DimensionedField<sphericalTensor6, GeoMesh>& df2)
	{
		return dimensioned<sphericalTensor6>(t1) - df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator -(const dimensioned<sphericalTensor6>& dt1
	                                                            , const tmp<DimensionedField<sphericalTensor6, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor6, sphericalTensor6, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '-' + df2.name() + ')', dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<sphericalTensor6, sphericalTensor6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator -(const sphericalTensor6& t1
	                                                            , const tmp<DimensionedField<sphericalTensor6, GeoMesh>>&
	                                                            tdf2) { return dimensioned<sphericalTensor6>(t1) - tdf2; }

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator -(const DimensionedField<sphericalTensor6, GeoMesh>& df1
	                                                            , const dimensioned<sphericalTensor6>& dt2)
	{
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(new DimensionedField<sphericalTensor6, GeoMesh>(
			IOobject('(' + df1.name() + '-' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator -(const DimensionedField<sphericalTensor6, GeoMesh>& df1
	                                                            , const sphericalTensor6& t2)
	{
		return df1 - dimensioned<sphericalTensor6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator -(
		const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf1, const dimensioned<sphericalTensor6>& dt2)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor6, sphericalTensor6, GeoMesh>::New(
				tdf1, '(' + df1.name() + '-' + dt2.name() + ')', df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<sphericalTensor6, sphericalTensor6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor6, GeoMesh>> operator -(
		const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf1, const sphericalTensor6& t2)
	{
		return tdf1 - dimensioned<sphericalTensor6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> inv(const DimensionedField<sphericalTensor8, GeoMesh>& df1)
	{
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(new DimensionedField<sphericalTensor8, GeoMesh>(
			IOobject("inv" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), inv(df1.dimensions())));
		inv(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> inv(const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf1)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor8, sphericalTensor8, GeoMesh>::New(
				tdf1, "inv" "(" + df1.name() + ')', inv(df1.dimensions())));
		inv(tRes().field(), df1.field());
		reuseTmpDimensionedField<sphericalTensor8, sphericalTensor8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> diag(const DimensionedField<sphericalTensor8, GeoMesh>& df1)
	{
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(new DimensionedField<sphericalTensor8, GeoMesh>(
			IOobject("diag" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), diag(df1.dimensions())));
		diag(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> diag(const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf1)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor8, sphericalTensor8, GeoMesh>::New(
				tdf1, "diag" "(" + df1.name() + ')', diag(df1.dimensions())));
		diag(tRes().field(), df1.field());
		reuseTmpDimensionedField<sphericalTensor8, sphericalTensor8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> contractLinear(const DimensionedField<sphericalTensor8, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("contractLinear" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, contractLinear(df1.dimensions())));
		contractLinear(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> contractLinear(const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf1)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, sphericalTensor8, GeoMesh>::New(tdf1, "contractLinear" "(" + df1.name() + ')'
			                                                                 , contractLinear(df1.dimensions())));
		contractLinear(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, sphericalTensor8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> contractScalar(const DimensionedField<sphericalTensor8, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("contractScalar" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, contractLinear(df1.dimensions())));
		contractScalar(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> contractScalar(const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf1)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, sphericalTensor8, GeoMesh>::New(tdf1, "contractScalar" "(" + df1.name() + ')'
			                                                                 , contractLinear(df1.dimensions())));
		contractScalar(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, sphericalTensor8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                            , const DimensionedField<sphericalTensor8, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(new DimensionedField<sphericalTensor8, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                            , const tmp<DimensionedField<sphericalTensor8, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor8, sphericalTensor8, GeoMesh>::New(
				tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor8, sphericalTensor8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                            , const DimensionedField<sphericalTensor8, GeoMesh>& df2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor8, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                 , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor8, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                            , const tmp<DimensionedField<sphericalTensor8, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<sphericalTensor8, scalar, scalar, sphericalTensor8, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<sphericalTensor8, scalar, scalar, sphericalTensor8, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator /(const dimensioned<scalar>& dt1
	                                                            , const DimensionedField<sphericalTensor8, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(new DimensionedField<sphericalTensor8, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator /(const scalar& t1
	                                                            , const DimensionedField<sphericalTensor8, GeoMesh>& df2)
	{
		return dimensioned<scalar>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator /(const dimensioned<scalar>& dt1
	                                                            , const tmp<DimensionedField<sphericalTensor8, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor8, sphericalTensor8, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '|' + df2.name() + ')', dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<sphericalTensor8, sphericalTensor8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator /(const scalar& t1
	                                                            , const tmp<DimensionedField<sphericalTensor8, GeoMesh>>&
	                                                            tdf2) { return dimensioned<scalar>(t1) / tdf2; }

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                            , const dimensioned<sphericalTensor8>& dt2)
	{
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(new DimensionedField<sphericalTensor8, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                            , const sphericalTensor8& t2)
	{
		return df1 / dimensioned<sphericalTensor8>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                            , const dimensioned<sphericalTensor8>& dt2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor8, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + dt2.name() + ')'
			                                                                 , df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<sphericalTensor8, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                            , const sphericalTensor8& t2)
	{
		return tdf1 / dimensioned<sphericalTensor8>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator /(const DimensionedField<vector8, GeoMesh>& df1
	                                                   , const DimensionedField<sphericalTensor8, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector8, GeoMesh>> tRes(new DimensionedField<vector8, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator /(const DimensionedField<vector8, GeoMesh>& df1
	                                                   , const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector8, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector8, sphericalTensor8, GeoMesh>::New(tdf2, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                  , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector8, sphericalTensor8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator /(const tmp<DimensionedField<vector8, GeoMesh>>& tdf1
	                                                   , const DimensionedField<sphericalTensor8, GeoMesh>& df2)
	{
		const DimensionedField<vector8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector8, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector8, vector8, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + df2.name() + ')'
			                                                         , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector8, vector8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator /(const tmp<DimensionedField<vector8, GeoMesh>>& tdf1
	                                                   , const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector8, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector8, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<vector8, vector8, vector8, sphericalTensor8, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<vector8, vector8, vector8, sphericalTensor8, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator /(const dimensioned<vector8>& dt1
	                                                   , const DimensionedField<sphericalTensor8, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector8, GeoMesh>> tRes(new DimensionedField<vector8, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator /(const vector8& t1
	                                                   , const DimensionedField<sphericalTensor8, GeoMesh>& df2)
	{
		return dimensioned<vector8>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator /(const dimensioned<vector8>& dt1
	                                                   , const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector8, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector8, sphericalTensor8, GeoMesh>::New(tdf2, '(' + dt1.name() + '|' + df2.name() + ')'
			                                                                  , dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<vector8, sphericalTensor8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator /(const vector8& t1
	                                                   , const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf2)
	{
		return dimensioned<vector8>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator /(const DimensionedField<vector8, GeoMesh>& df1
	                                                   , const dimensioned<sphericalTensor8>& dt2)
	{
		tmp<DimensionedField<vector8, GeoMesh>> tRes(new DimensionedField<vector8, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator /(const DimensionedField<vector8, GeoMesh>& df1
	                                                   , const sphericalTensor8& t2)
	{
		return df1 / dimensioned<sphericalTensor8>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator /(const tmp<DimensionedField<vector8, GeoMesh>>& tdf1
	                                                   , const dimensioned<sphericalTensor8>& dt2)
	{
		const DimensionedField<vector8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector8, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector8, vector8, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + dt2.name() + ')'
			                                                         , df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<vector8, vector8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator /(const tmp<DimensionedField<vector8, GeoMesh>>& tdf1
	                                                   , const sphericalTensor8& t2)
	{
		return tdf1 / dimensioned<sphericalTensor8>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator /(const DimensionedField<sphericalTensor8, GeoMesh>& df1
	                                                            , const DimensionedField<sphericalTensor8, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(new DimensionedField<sphericalTensor8, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator /(const DimensionedField<sphericalTensor8, GeoMesh>& df1
	                                                            , const tmp<DimensionedField<sphericalTensor8, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor8, sphericalTensor8, GeoMesh>::New(
				tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor8, sphericalTensor8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator /(
		const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf1, const DimensionedField<sphericalTensor8, GeoMesh>& df2)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor8, sphericalTensor8, GeoMesh>::New(
				tdf1, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor8, sphericalTensor8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator /(
		const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf1
		, const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<sphericalTensor8, sphericalTensor8, sphericalTensor8, sphericalTensor8, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<sphericalTensor8, sphericalTensor8, sphericalTensor8, sphericalTensor8, GeoMesh>::
			clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator /(const dimensioned<sphericalTensor8>& dt1
	                                                            , const DimensionedField<sphericalTensor8, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(new DimensionedField<sphericalTensor8, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator /(const sphericalTensor8& t1
	                                                            , const DimensionedField<sphericalTensor8, GeoMesh>& df2)
	{
		return dimensioned<sphericalTensor8>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator /(const dimensioned<sphericalTensor8>& dt1
	                                                            , const tmp<DimensionedField<sphericalTensor8, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor8, sphericalTensor8, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '|' + df2.name() + ')', dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<sphericalTensor8, sphericalTensor8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator /(const sphericalTensor8& t1
	                                                            , const tmp<DimensionedField<sphericalTensor8, GeoMesh>>&
	                                                            tdf2) { return dimensioned<sphericalTensor8>(t1) / tdf2; }

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator /(const DimensionedField<sphericalTensor8, GeoMesh>& df1
	                                                            , const dimensioned<sphericalTensor8>& dt2)
	{
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(new DimensionedField<sphericalTensor8, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator /(const DimensionedField<sphericalTensor8, GeoMesh>& df1
	                                                            , const sphericalTensor8& t2)
	{
		return df1 / dimensioned<sphericalTensor8>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator /(
		const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf1, const dimensioned<sphericalTensor8>& dt2)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor8, sphericalTensor8, GeoMesh>::New(
				tdf1, '(' + df1.name() + '|' + dt2.name() + ')', df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<sphericalTensor8, sphericalTensor8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator /(
		const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf1, const sphericalTensor8& t2)
	{
		return tdf1 / dimensioned<sphericalTensor8>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator +(const DimensionedField<sphericalTensor8, GeoMesh>& df1
	                                                            , const DimensionedField<sphericalTensor8, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(new DimensionedField<sphericalTensor8, GeoMesh>(
			IOobject('(' + df1.name() + '+' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator +(const DimensionedField<sphericalTensor8, GeoMesh>& df1
	                                                            , const tmp<DimensionedField<sphericalTensor8, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor8, sphericalTensor8, GeoMesh>::New(
				tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor8, sphericalTensor8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator +(
		const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf1, const DimensionedField<sphericalTensor8, GeoMesh>& df2)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor8, sphericalTensor8, GeoMesh>::New(
				tdf1, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor8, sphericalTensor8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator +(
		const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf1
		, const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<sphericalTensor8, sphericalTensor8, sphericalTensor8, sphericalTensor8, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<sphericalTensor8, sphericalTensor8, sphericalTensor8, sphericalTensor8, GeoMesh>::
			clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator -(const DimensionedField<sphericalTensor8, GeoMesh>& df1
	                                                            , const DimensionedField<sphericalTensor8, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(new DimensionedField<sphericalTensor8, GeoMesh>(
			IOobject('(' + df1.name() + '-' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator -(const DimensionedField<sphericalTensor8, GeoMesh>& df1
	                                                            , const tmp<DimensionedField<sphericalTensor8, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor8, sphericalTensor8, GeoMesh>::New(
				tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor8, sphericalTensor8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator -(
		const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf1, const DimensionedField<sphericalTensor8, GeoMesh>& df2)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor8, sphericalTensor8, GeoMesh>::New(
				tdf1, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<sphericalTensor8, sphericalTensor8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator -(
		const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf1
		, const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<sphericalTensor8, sphericalTensor8, sphericalTensor8, sphericalTensor8, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<sphericalTensor8, sphericalTensor8, sphericalTensor8, sphericalTensor8, GeoMesh>::
			clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator +(const dimensioned<sphericalTensor8>& dt1
	                                                            , const DimensionedField<sphericalTensor8, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(new DimensionedField<sphericalTensor8, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator +(const sphericalTensor8& t1
	                                                            , const DimensionedField<sphericalTensor8, GeoMesh>& df2)
	{
		return dimensioned<sphericalTensor8>(t1) + df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator +(const dimensioned<sphericalTensor8>& dt1
	                                                            , const tmp<DimensionedField<sphericalTensor8, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor8, sphericalTensor8, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '+' + df2.name() + ')', dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<sphericalTensor8, sphericalTensor8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator +(const sphericalTensor8& t1
	                                                            , const tmp<DimensionedField<sphericalTensor8, GeoMesh>>&
	                                                            tdf2) { return dimensioned<sphericalTensor8>(t1) + tdf2; }

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator +(const DimensionedField<sphericalTensor8, GeoMesh>& df1
	                                                            , const dimensioned<sphericalTensor8>& dt2)
	{
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(new DimensionedField<sphericalTensor8, GeoMesh>(
			IOobject('(' + df1.name() + '+' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator +(const DimensionedField<sphericalTensor8, GeoMesh>& df1
	                                                            , const sphericalTensor8& t2)
	{
		return df1 + dimensioned<sphericalTensor8>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator +(
		const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf1, const dimensioned<sphericalTensor8>& dt2)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor8, sphericalTensor8, GeoMesh>::New(
				tdf1, '(' + df1.name() + '+' + dt2.name() + ')', df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<sphericalTensor8, sphericalTensor8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator +(
		const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf1, const sphericalTensor8& t2)
	{
		return tdf1 + dimensioned<sphericalTensor8>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator -(const dimensioned<sphericalTensor8>& dt1
	                                                            , const DimensionedField<sphericalTensor8, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(new DimensionedField<sphericalTensor8, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator -(const sphericalTensor8& t1
	                                                            , const DimensionedField<sphericalTensor8, GeoMesh>& df2)
	{
		return dimensioned<sphericalTensor8>(t1) - df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator -(const dimensioned<sphericalTensor8>& dt1
	                                                            , const tmp<DimensionedField<sphericalTensor8, GeoMesh>>&
	                                                            tdf2)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor8, sphericalTensor8, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '-' + df2.name() + ')', dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<sphericalTensor8, sphericalTensor8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator -(const sphericalTensor8& t1
	                                                            , const tmp<DimensionedField<sphericalTensor8, GeoMesh>>&
	                                                            tdf2) { return dimensioned<sphericalTensor8>(t1) - tdf2; }

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator -(const DimensionedField<sphericalTensor8, GeoMesh>& df1
	                                                            , const dimensioned<sphericalTensor8>& dt2)
	{
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(new DimensionedField<sphericalTensor8, GeoMesh>(
			IOobject('(' + df1.name() + '-' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator -(const DimensionedField<sphericalTensor8, GeoMesh>& df1
	                                                            , const sphericalTensor8& t2)
	{
		return df1 - dimensioned<sphericalTensor8>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator -(
		const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf1, const dimensioned<sphericalTensor8>& dt2)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor8, sphericalTensor8, GeoMesh>::New(
				tdf1, '(' + df1.name() + '-' + dt2.name() + ')', df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<sphericalTensor8, sphericalTensor8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor8, GeoMesh>> operator -(
		const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf1, const sphericalTensor8& t2)
	{
		return tdf1 - dimensioned<sphericalTensor8>(t2);
	}

}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#undef SphericalTensorN_FieldFunctions

#include <undefFieldFunctionsM.hxx>
