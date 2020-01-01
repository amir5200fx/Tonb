#include <DimensionedDiagTensorNFields.hxx>

#include <DimensionedFieldReuseFunctions.hxx>

#define TEMPLATE template<class GeoMesh>
#include <DimensionedFieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define DiagTensorN_FieldFunctions(tensorType, diagTensorType, sphericalTensorType,     \
    vectorType, CmptType, args)                                                      \
                                                                                        \
UNARY_FUNCTION(diagTensorType, diagTensorType,inv,inv)                                  \
UNARY_FUNCTION(diagTensorType, diagTensorType,diag,diag)                                \
UNARY_FUNCTION(vectorType, diagTensorType, contractLinear,contractLinear)               \
UNARY_FUNCTION(CmptType, diagTensorType, contractScalar,contractLinear)                 \
                                                                                        \
BINARY_OPERATOR(diagTensorType, CmptType, diagTensorType, /,'|',divide)                 \
BINARY_TYPE_OPERATOR(diagTensorType, CmptType, diagTensorType, /,'|',divide)            \
                                                                                        \
BINARY_OPERATOR(vectorType, vectorType, diagTensorType, /,'|',divide)                   \
BINARY_TYPE_OPERATOR(vectorType, vectorType, diagTensorType, /,'|',divide)              \
                                                                                        \
BINARY_OPERATOR(diagTensorType, diagTensorType, diagTensorType, /,'|',divide)           \
BINARY_TYPE_OPERATOR(diagTensorType, diagTensorType, diagTensorType, /,'|',divide)      \
                                                                                        \
BINARY_OPERATOR(diagTensorType, sphericalTensorType, diagTensorType, /,'|',divide)      \
BINARY_TYPE_OPERATOR(diagTensorType, sphericalTensorType, diagTensorType, /,'|',divide) \
                                                                                        \
BINARY_OPERATOR(diagTensorType, diagTensorType, sphericalTensorType, /,'|',divide)      \
BINARY_TYPE_OPERATOR(diagTensorType, diagTensorType, sphericalTensorType, /,'|',divide) \
                                                                                        \
BINARY_OPERATOR(diagTensorType, diagTensorType, diagTensorType, +,'+',add)              \
BINARY_OPERATOR(diagTensorType, diagTensorType, diagTensorType, -,'-',subtract)         \
                                                                                        \
BINARY_TYPE_OPERATOR(diagTensorType, diagTensorType, diagTensorType, +,'+', add)        \
BINARY_TYPE_OPERATOR(diagTensorType, diagTensorType, diagTensorType, -,'-', subtract)   \
                                                                                        \
BINARY_OPERATOR(diagTensorType, sphericalTensorType, diagTensorType, +,'+', add)        \
BINARY_OPERATOR(diagTensorType, sphericalTensorType, diagTensorType, -,'-', subtract)   \
                                                                                        \
BINARY_TYPE_OPERATOR(diagTensorType, sphericalTensorType, diagTensorType, +,'+', add)   \
BINARY_TYPE_OPERATOR(diagTensorType, sphericalTensorType, diagTensorType, -,'-', subtract)  \
                                                                                        \
BINARY_OPERATOR(diagTensorType, diagTensorType, sphericalTensorType, +,'+', add)        \
BINARY_OPERATOR(diagTensorType, diagTensorType, sphericalTensorType, -,'-', subtract)   \
                                                                                        \
BINARY_TYPE_OPERATOR(diagTensorType, diagTensorType, sphericalTensorType, +,'+', add)   \
BINARY_TYPE_OPERATOR(diagTensorType, diagTensorType, sphericalTensorType, -,'+', subtract)


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> inv(const DimensionedField<diagTensor2, GeoMesh>& df1)
	{
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(new DimensionedField<diagTensor2, GeoMesh>(
			IOobject("inv" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), inv(df1.dimensions())));
		inv(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> inv(const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf1)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::New(tdf1, "inv" "(" + df1.name() + ')'
			                                                                 , inv(df1.dimensions())));
		inv(tRes().field(), df1.field());
		reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> diag(const DimensionedField<diagTensor2, GeoMesh>& df1)
	{
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(new DimensionedField<diagTensor2, GeoMesh>(
			IOobject("diag" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), diag(df1.dimensions())));
		diag(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> diag(const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf1)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::New(tdf1, "diag" "(" + df1.name() + ')'
			                                                                 , diag(df1.dimensions())));
		diag(tRes().field(), df1.field());
		reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> contractLinear(const DimensionedField<diagTensor2, GeoMesh>& df1)
	{
		tmp<DimensionedField<vector2, GeoMesh>> tRes(new DimensionedField<vector2, GeoMesh>(
			IOobject("contractLinear" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, contractLinear(df1.dimensions())));
		contractLinear(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> contractLinear(const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf1)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector2, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector2, diagTensor2, GeoMesh>::New(tdf1, "contractLinear" "(" + df1.name() + ')'
			                                                             , contractLinear(df1.dimensions())));
		contractLinear(tRes().field(), df1.field());
		reuseTmpDimensionedField<vector2, diagTensor2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> contractScalar(const DimensionedField<diagTensor2, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("contractScalar" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, contractLinear(df1.dimensions())));
		contractScalar(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> contractScalar(const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf1)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, diagTensor2, GeoMesh>::New(tdf1, "contractScalar" "(" + df1.name() + ')'
			                                                            , contractLinear(df1.dimensions())));
		contractScalar(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, diagTensor2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor2, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(new DimensionedField<diagTensor2, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::New(tdf2, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                 , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor2, GeoMesh>& df2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + df2.name() + ')'
			                                                            , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor2, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor2, scalar, scalar, diagTensor2, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor2, scalar, scalar, diagTensor2, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const dimensioned<scalar>& dt1
	                                                       , const DimensionedField<diagTensor2, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(new DimensionedField<diagTensor2, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const scalar& t1
	                                                       , const DimensionedField<diagTensor2, GeoMesh>& df2)
	{
		return dimensioned<scalar>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const dimensioned<scalar>& dt1
	                                                       , const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::New(tdf2, '(' + dt1.name() + '|' + df2.name() + ')'
			                                                                 , dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const scalar& t1
	                                                       , const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf2)
	{
		return dimensioned<scalar>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor2>& dt2)
	{
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(new DimensionedField<diagTensor2, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                       , const diagTensor2& t2)
	{
		return df1 / dimensioned<diagTensor2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor2>& dt2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + dt2.name() + ')'
			                                                            , df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor2, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                       , const diagTensor2& t2)
	{
		return tdf1 / dimensioned<diagTensor2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator /(const DimensionedField<vector2, GeoMesh>& df1
	                                                   , const DimensionedField<diagTensor2, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector2, GeoMesh>> tRes(new DimensionedField<vector2, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator /(const DimensionedField<vector2, GeoMesh>& df1
	                                                   , const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector2, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector2, diagTensor2, GeoMesh>::New(tdf2, '(' + df1.name() + '|' + df2.name() + ')'
			                                                             , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector2, diagTensor2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator /(const tmp<DimensionedField<vector2, GeoMesh>>& tdf1
	                                                   , const DimensionedField<diagTensor2, GeoMesh>& df2)
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
	                                                   , const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector2, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector2, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<vector2, vector2, vector2, diagTensor2, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<vector2, vector2, vector2, diagTensor2, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator /(const dimensioned<vector2>& dt1
	                                                   , const DimensionedField<diagTensor2, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector2, GeoMesh>> tRes(new DimensionedField<vector2, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator /(const vector2& t1
	                                                   , const DimensionedField<diagTensor2, GeoMesh>& df2)
	{
		return dimensioned<vector2>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator /(const dimensioned<vector2>& dt1
	                                                   , const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector2, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector2, diagTensor2, GeoMesh>::New(tdf2, '(' + dt1.name() + '|' + df2.name() + ')'
			                                                             , dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<vector2, diagTensor2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator /(const vector2& t1
	                                                   , const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf2)
	{
		return dimensioned<vector2>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator /(const DimensionedField<vector2, GeoMesh>& df1
	                                                   , const dimensioned<diagTensor2>& dt2)
	{
		tmp<DimensionedField<vector2, GeoMesh>> tRes(new DimensionedField<vector2, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator /(const DimensionedField<vector2, GeoMesh>& df1
	                                                   , const diagTensor2& t2)
	{
		return df1 / dimensioned<diagTensor2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector2, GeoMesh>> operator /(const tmp<DimensionedField<vector2, GeoMesh>>& tdf1
	                                                   , const dimensioned<diagTensor2>& dt2)
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
	                                                   , const diagTensor2& t2)
	{
		return tdf1 / dimensioned<diagTensor2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const DimensionedField<diagTensor2, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor2, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(new DimensionedField<diagTensor2, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const DimensionedField<diagTensor2, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::New(tdf2, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                 , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor2, GeoMesh>& df2)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                 , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor2, diagTensor2, diagTensor2, diagTensor2, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor2, diagTensor2, diagTensor2, diagTensor2, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const dimensioned<diagTensor2>& dt1
	                                                       , const DimensionedField<diagTensor2, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(new DimensionedField<diagTensor2, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const diagTensor2& t1
	                                                       , const DimensionedField<diagTensor2, GeoMesh>& df2)
	{
		return dimensioned<diagTensor2>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const dimensioned<diagTensor2>& dt1
	                                                       , const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::New(tdf2, '(' + dt1.name() + '|' + df2.name() + ')'
			                                                                 , dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const diagTensor2& t1
	                                                       , const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf2)
	{
		return dimensioned<diagTensor2>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const DimensionedField<diagTensor2, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor2>& dt2)
	{
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(new DimensionedField<diagTensor2, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const DimensionedField<diagTensor2, GeoMesh>& df1
	                                                       , const diagTensor2& t2)
	{
		return df1 / dimensioned<diagTensor2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor2>& dt2)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + dt2.name() + ')'
			                                                                 , df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf1
	                                                       , const diagTensor2& t2)
	{
		return tdf1 / dimensioned<diagTensor2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const DimensionedField<sphericalTensor2, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor2, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(new DimensionedField<diagTensor2, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const DimensionedField<sphericalTensor2, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::New(tdf2, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                 , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor2, GeoMesh>& df2)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, sphericalTensor2, GeoMesh>::New(
				tdf1, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor2, sphericalTensor2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor2, sphericalTensor2, sphericalTensor2, diagTensor2, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor2, sphericalTensor2, sphericalTensor2, diagTensor2, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const dimensioned<sphericalTensor2>& dt1
	                                                       , const DimensionedField<diagTensor2, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(new DimensionedField<diagTensor2, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const sphericalTensor2& t1
	                                                       , const DimensionedField<diagTensor2, GeoMesh>& df2)
	{
		return dimensioned<sphericalTensor2>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const dimensioned<sphericalTensor2>& dt1
	                                                       , const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::New(tdf2, '(' + dt1.name() + '|' + df2.name() + ')'
			                                                                 , dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const sphericalTensor2& t1
	                                                       , const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf2)
	{
		return dimensioned<sphericalTensor2>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const DimensionedField<sphericalTensor2, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor2>& dt2)
	{
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(new DimensionedField<diagTensor2, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const DimensionedField<sphericalTensor2, GeoMesh>& df1
	                                                       , const diagTensor2& t2)
	{
		return df1 / dimensioned<diagTensor2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor2>& dt2)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, sphericalTensor2, GeoMesh>::New(
				tdf1, '(' + df1.name() + '|' + dt2.name() + ')', df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor2, sphericalTensor2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf1
	                                                       , const diagTensor2& t2)
	{
		return tdf1 / dimensioned<diagTensor2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const DimensionedField<diagTensor2, GeoMesh>& df1
	                                                       , const DimensionedField<sphericalTensor2, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(new DimensionedField<diagTensor2, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const DimensionedField<diagTensor2, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, sphericalTensor2, GeoMesh>::New(
				tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor2, sphericalTensor2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf1
	                                                       , const DimensionedField<sphericalTensor2, GeoMesh>& df2)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                 , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor2, diagTensor2, diagTensor2, sphericalTensor2, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor2, diagTensor2, diagTensor2, sphericalTensor2, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const dimensioned<diagTensor2>& dt1
	                                                       , const DimensionedField<sphericalTensor2, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(new DimensionedField<diagTensor2, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const diagTensor2& t1
	                                                       , const DimensionedField<sphericalTensor2, GeoMesh>& df2)
	{
		return dimensioned<diagTensor2>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const dimensioned<diagTensor2>& dt1
	                                                       , const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, sphericalTensor2, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '|' + df2.name() + ')', dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor2, sphericalTensor2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const diagTensor2& t1
	                                                       , const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf2)
	{
		return dimensioned<diagTensor2>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const DimensionedField<diagTensor2, GeoMesh>& df1
	                                                       , const dimensioned<sphericalTensor2>& dt2)
	{
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(new DimensionedField<diagTensor2, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const DimensionedField<diagTensor2, GeoMesh>& df1
	                                                       , const sphericalTensor2& t2)
	{
		return df1 / dimensioned<sphericalTensor2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf1
	                                                       , const dimensioned<sphericalTensor2>& dt2)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + dt2.name() + ')'
			                                                                 , df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf1
	                                                       , const sphericalTensor2& t2)
	{
		return tdf1 / dimensioned<sphericalTensor2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const DimensionedField<diagTensor2, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor2, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(new DimensionedField<diagTensor2, GeoMesh>(
			IOobject('(' + df1.name() + '+' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const DimensionedField<diagTensor2, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::New(tdf2, '(' + df1.name() + '+' + df2.name() + ')'
			                                                                 , df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor2, GeoMesh>& df2)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + df2.name() + ')'
			                                                                 , df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor2, diagTensor2, diagTensor2, diagTensor2, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor2, diagTensor2, diagTensor2, diagTensor2, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const DimensionedField<diagTensor2, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor2, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(new DimensionedField<diagTensor2, GeoMesh>(
			IOobject('(' + df1.name() + '-' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const DimensionedField<diagTensor2, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::New(tdf2, '(' + df1.name() + '-' + df2.name() + ')'
			                                                                 , df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor2, GeoMesh>& df2)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::New(tdf1, '(' + df1.name() + '-' + df2.name() + ')'
			                                                                 , df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor2, diagTensor2, diagTensor2, diagTensor2, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor2, diagTensor2, diagTensor2, diagTensor2, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const dimensioned<diagTensor2>& dt1
	                                                       , const DimensionedField<diagTensor2, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(new DimensionedField<diagTensor2, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const diagTensor2& t1
	                                                       , const DimensionedField<diagTensor2, GeoMesh>& df2)
	{
		return dimensioned<diagTensor2>(t1) + df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const dimensioned<diagTensor2>& dt1
	                                                       , const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::New(tdf2, '(' + dt1.name() + '+' + df2.name() + ')'
			                                                                 , dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const diagTensor2& t1
	                                                       , const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf2)
	{
		return dimensioned<diagTensor2>(t1) + tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const DimensionedField<diagTensor2, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor2>& dt2)
	{
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(new DimensionedField<diagTensor2, GeoMesh>(
			IOobject('(' + df1.name() + '+' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const DimensionedField<diagTensor2, GeoMesh>& df1
	                                                       , const diagTensor2& t2)
	{
		return df1 + dimensioned<diagTensor2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor2>& dt2)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + dt2.name() + ')'
			                                                                 , df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf1
	                                                       , const diagTensor2& t2)
	{
		return tdf1 + dimensioned<diagTensor2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const dimensioned<diagTensor2>& dt1
	                                                       , const DimensionedField<diagTensor2, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(new DimensionedField<diagTensor2, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const diagTensor2& t1
	                                                       , const DimensionedField<diagTensor2, GeoMesh>& df2)
	{
		return dimensioned<diagTensor2>(t1) - df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const dimensioned<diagTensor2>& dt1
	                                                       , const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::New(tdf2, '(' + dt1.name() + '-' + df2.name() + ')'
			                                                                 , dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const diagTensor2& t1
	                                                       , const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf2)
	{
		return dimensioned<diagTensor2>(t1) - tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const DimensionedField<diagTensor2, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor2>& dt2)
	{
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(new DimensionedField<diagTensor2, GeoMesh>(
			IOobject('(' + df1.name() + '-' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const DimensionedField<diagTensor2, GeoMesh>& df1
	                                                       , const diagTensor2& t2)
	{
		return df1 - dimensioned<diagTensor2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor2>& dt2)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::New(tdf1, '(' + df1.name() + '-' + dt2.name() + ')'
			                                                                 , df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf1
	                                                       , const diagTensor2& t2)
	{
		return tdf1 - dimensioned<diagTensor2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const DimensionedField<sphericalTensor2, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor2, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(new DimensionedField<diagTensor2, GeoMesh>(
			IOobject('(' + df1.name() + '+' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const DimensionedField<sphericalTensor2, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::New(tdf2, '(' + df1.name() + '+' + df2.name() + ')'
			                                                                 , df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor2, GeoMesh>& df2)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, sphericalTensor2, GeoMesh>::New(
				tdf1, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor2, sphericalTensor2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor2, sphericalTensor2, sphericalTensor2, diagTensor2, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor2, sphericalTensor2, sphericalTensor2, diagTensor2, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const DimensionedField<sphericalTensor2, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor2, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(new DimensionedField<diagTensor2, GeoMesh>(
			IOobject('(' + df1.name() + '-' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const DimensionedField<sphericalTensor2, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::New(tdf2, '(' + df1.name() + '-' + df2.name() + ')'
			                                                                 , df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor2, GeoMesh>& df2)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, sphericalTensor2, GeoMesh>::New(
				tdf1, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor2, sphericalTensor2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor2, sphericalTensor2, sphericalTensor2, diagTensor2, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor2, sphericalTensor2, sphericalTensor2, diagTensor2, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const dimensioned<sphericalTensor2>& dt1
	                                                       , const DimensionedField<diagTensor2, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(new DimensionedField<diagTensor2, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const sphericalTensor2& t1
	                                                       , const DimensionedField<diagTensor2, GeoMesh>& df2)
	{
		return dimensioned<sphericalTensor2>(t1) + df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const dimensioned<sphericalTensor2>& dt1
	                                                       , const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::New(tdf2, '(' + dt1.name() + '+' + df2.name() + ')'
			                                                                 , dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const sphericalTensor2& t1
	                                                       , const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf2)
	{
		return dimensioned<sphericalTensor2>(t1) + tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const DimensionedField<sphericalTensor2, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor2>& dt2)
	{
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(new DimensionedField<diagTensor2, GeoMesh>(
			IOobject('(' + df1.name() + '+' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const DimensionedField<sphericalTensor2, GeoMesh>& df1
	                                                       , const diagTensor2& t2)
	{
		return df1 + dimensioned<diagTensor2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor2>& dt2)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, sphericalTensor2, GeoMesh>::New(
				tdf1, '(' + df1.name() + '+' + dt2.name() + ')', df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor2, sphericalTensor2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf1
	                                                       , const diagTensor2& t2)
	{
		return tdf1 + dimensioned<diagTensor2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const dimensioned<sphericalTensor2>& dt1
	                                                       , const DimensionedField<diagTensor2, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(new DimensionedField<diagTensor2, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const sphericalTensor2& t1
	                                                       , const DimensionedField<diagTensor2, GeoMesh>& df2)
	{
		return dimensioned<sphericalTensor2>(t1) - df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const dimensioned<sphericalTensor2>& dt1
	                                                       , const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::New(tdf2, '(' + dt1.name() + '-' + df2.name() + ')'
			                                                                 , dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const sphericalTensor2& t1
	                                                       , const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf2)
	{
		return dimensioned<sphericalTensor2>(t1) - tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const DimensionedField<sphericalTensor2, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor2>& dt2)
	{
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(new DimensionedField<diagTensor2, GeoMesh>(
			IOobject('(' + df1.name() + '-' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const DimensionedField<sphericalTensor2, GeoMesh>& df1
	                                                       , const diagTensor2& t2)
	{
		return df1 - dimensioned<diagTensor2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor2>& dt2)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, sphericalTensor2, GeoMesh>::New(
				tdf1, '(' + df1.name() + '-' + dt2.name() + ')', df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor2, sphericalTensor2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf1
	                                                       , const diagTensor2& t2)
	{
		return tdf1 - dimensioned<diagTensor2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const DimensionedField<diagTensor2, GeoMesh>& df1
	                                                       , const DimensionedField<sphericalTensor2, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(new DimensionedField<diagTensor2, GeoMesh>(
			IOobject('(' + df1.name() + '+' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const DimensionedField<diagTensor2, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, sphericalTensor2, GeoMesh>::New(
				tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor2, sphericalTensor2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf1
	                                                       , const DimensionedField<sphericalTensor2, GeoMesh>& df2)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + df2.name() + ')'
			                                                                 , df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor2, diagTensor2, diagTensor2, sphericalTensor2, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor2, diagTensor2, diagTensor2, sphericalTensor2, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const DimensionedField<diagTensor2, GeoMesh>& df1
	                                                       , const DimensionedField<sphericalTensor2, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(new DimensionedField<diagTensor2, GeoMesh>(
			IOobject('(' + df1.name() + '-' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const DimensionedField<diagTensor2, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, sphericalTensor2, GeoMesh>::New(
				tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor2, sphericalTensor2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf1
	                                                       , const DimensionedField<sphericalTensor2, GeoMesh>& df2)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::New(tdf1, '(' + df1.name() + '-' + df2.name() + ')'
			                                                                 , df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor2, diagTensor2, diagTensor2, sphericalTensor2, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor2, diagTensor2, diagTensor2, sphericalTensor2, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const dimensioned<diagTensor2>& dt1
	                                                       , const DimensionedField<sphericalTensor2, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(new DimensionedField<diagTensor2, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const diagTensor2& t1
	                                                       , const DimensionedField<sphericalTensor2, GeoMesh>& df2)
	{
		return dimensioned<diagTensor2>(t1) + df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const dimensioned<diagTensor2>& dt1
	                                                       , const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, sphericalTensor2, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '+' + df2.name() + ')', dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor2, sphericalTensor2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const diagTensor2& t1
	                                                       , const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf2)
	{
		return dimensioned<diagTensor2>(t1) + tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const DimensionedField<diagTensor2, GeoMesh>& df1
	                                                       , const dimensioned<sphericalTensor2>& dt2)
	{
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(new DimensionedField<diagTensor2, GeoMesh>(
			IOobject('(' + df1.name() + '+' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const DimensionedField<diagTensor2, GeoMesh>& df1
	                                                       , const sphericalTensor2& t2)
	{
		return df1 + dimensioned<sphericalTensor2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf1
	                                                       , const dimensioned<sphericalTensor2>& dt2)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + dt2.name() + ')'
			                                                                 , df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf1
	                                                       , const sphericalTensor2& t2)
	{
		return tdf1 + dimensioned<sphericalTensor2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const dimensioned<diagTensor2>& dt1
	                                                       , const DimensionedField<sphericalTensor2, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(new DimensionedField<diagTensor2, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const diagTensor2& t1
	                                                       , const DimensionedField<sphericalTensor2, GeoMesh>& df2)
	{
		return dimensioned<diagTensor2>(t1) - df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const dimensioned<diagTensor2>& dt1
	                                                       , const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor2, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, sphericalTensor2, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '+' + df2.name() + ')', dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor2, sphericalTensor2, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const diagTensor2& t1
	                                                       , const tmp<DimensionedField<sphericalTensor2, GeoMesh>>& tdf2)
	{
		return dimensioned<diagTensor2>(t1) - tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const DimensionedField<diagTensor2, GeoMesh>& df1
	                                                       , const dimensioned<sphericalTensor2>& dt2)
	{
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(new DimensionedField<diagTensor2, GeoMesh>(
			IOobject('(' + df1.name() + '+' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const DimensionedField<diagTensor2, GeoMesh>& df1
	                                                       , const sphericalTensor2& t2)
	{
		return df1 - dimensioned<sphericalTensor2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf1
	                                                       , const dimensioned<sphericalTensor2>& dt2)
	{
		const DimensionedField<diagTensor2, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor2, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + dt2.name() + ')'
			                                                                 , df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor2, diagTensor2, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor2, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor2, GeoMesh>>& tdf1
	                                                       , const sphericalTensor2& t2)
	{
		return tdf1 - dimensioned<sphericalTensor2>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> inv(const DimensionedField<diagTensor3, GeoMesh>& df1)
	{
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(new DimensionedField<diagTensor3, GeoMesh>(
			IOobject("inv" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), inv(df1.dimensions())));
		inv(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> inv(const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf1)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::New(tdf1, "inv" "(" + df1.name() + ')'
			                                                                 , inv(df1.dimensions())));
		inv(tRes().field(), df1.field());
		reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> diag(const DimensionedField<diagTensor3, GeoMesh>& df1)
	{
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(new DimensionedField<diagTensor3, GeoMesh>(
			IOobject("diag" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), diag(df1.dimensions())));
		diag(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> diag(const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf1)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::New(tdf1, "diag" "(" + df1.name() + ')'
			                                                                 , diag(df1.dimensions())));
		diag(tRes().field(), df1.field());
		reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> contractLinear(const DimensionedField<diagTensor3, GeoMesh>& df1)
	{
		tmp<DimensionedField<vector3, GeoMesh>> tRes(new DimensionedField<vector3, GeoMesh>(
			IOobject("contractLinear" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, contractLinear(df1.dimensions())));
		contractLinear(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> contractLinear(const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf1)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector3, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector3, diagTensor3, GeoMesh>::New(tdf1, "contractLinear" "(" + df1.name() + ')'
			                                                             , contractLinear(df1.dimensions())));
		contractLinear(tRes().field(), df1.field());
		reuseTmpDimensionedField<vector3, diagTensor3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> contractScalar(const DimensionedField<diagTensor3, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("contractScalar" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, contractLinear(df1.dimensions())));
		contractScalar(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> contractScalar(const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf1)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, diagTensor3, GeoMesh>::New(tdf1, "contractScalar" "(" + df1.name() + ')'
			                                                            , contractLinear(df1.dimensions())));
		contractScalar(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, diagTensor3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor3, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(new DimensionedField<diagTensor3, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::New(tdf2, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                 , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor3, GeoMesh>& df2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + df2.name() + ')'
			                                                            , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor3, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor3, scalar, scalar, diagTensor3, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor3, scalar, scalar, diagTensor3, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const dimensioned<scalar>& dt1
	                                                       , const DimensionedField<diagTensor3, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(new DimensionedField<diagTensor3, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const scalar& t1
	                                                       , const DimensionedField<diagTensor3, GeoMesh>& df2)
	{
		return dimensioned<scalar>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const dimensioned<scalar>& dt1
	                                                       , const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::New(tdf2, '(' + dt1.name() + '|' + df2.name() + ')'
			                                                                 , dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const scalar& t1
	                                                       , const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf2)
	{
		return dimensioned<scalar>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor3>& dt2)
	{
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(new DimensionedField<diagTensor3, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                       , const diagTensor3& t2)
	{
		return df1 / dimensioned<diagTensor3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor3>& dt2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + dt2.name() + ')'
			                                                            , df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor3, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                       , const diagTensor3& t2)
	{
		return tdf1 / dimensioned<diagTensor3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator /(const DimensionedField<vector3, GeoMesh>& df1
	                                                   , const DimensionedField<diagTensor3, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector3, GeoMesh>> tRes(new DimensionedField<vector3, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator /(const DimensionedField<vector3, GeoMesh>& df1
	                                                   , const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector3, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector3, diagTensor3, GeoMesh>::New(tdf2, '(' + df1.name() + '|' + df2.name() + ')'
			                                                             , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector3, diagTensor3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator /(const tmp<DimensionedField<vector3, GeoMesh>>& tdf1
	                                                   , const DimensionedField<diagTensor3, GeoMesh>& df2)
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
	                                                   , const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector3, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector3, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<vector3, vector3, vector3, diagTensor3, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<vector3, vector3, vector3, diagTensor3, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator /(const dimensioned<vector3>& dt1
	                                                   , const DimensionedField<diagTensor3, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector3, GeoMesh>> tRes(new DimensionedField<vector3, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator /(const vector3& t1
	                                                   , const DimensionedField<diagTensor3, GeoMesh>& df2)
	{
		return dimensioned<vector3>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator /(const dimensioned<vector3>& dt1
	                                                   , const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector3, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector3, diagTensor3, GeoMesh>::New(tdf2, '(' + dt1.name() + '|' + df2.name() + ')'
			                                                             , dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<vector3, diagTensor3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator /(const vector3& t1
	                                                   , const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf2)
	{
		return dimensioned<vector3>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator /(const DimensionedField<vector3, GeoMesh>& df1
	                                                   , const dimensioned<diagTensor3>& dt2)
	{
		tmp<DimensionedField<vector3, GeoMesh>> tRes(new DimensionedField<vector3, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator /(const DimensionedField<vector3, GeoMesh>& df1
	                                                   , const diagTensor3& t2)
	{
		return df1 / dimensioned<diagTensor3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector3, GeoMesh>> operator /(const tmp<DimensionedField<vector3, GeoMesh>>& tdf1
	                                                   , const dimensioned<diagTensor3>& dt2)
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
	                                                   , const diagTensor3& t2)
	{
		return tdf1 / dimensioned<diagTensor3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const DimensionedField<diagTensor3, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor3, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(new DimensionedField<diagTensor3, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const DimensionedField<diagTensor3, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::New(tdf2, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                 , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor3, GeoMesh>& df2)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                 , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor3, diagTensor3, diagTensor3, diagTensor3, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor3, diagTensor3, diagTensor3, diagTensor3, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const dimensioned<diagTensor3>& dt1
	                                                       , const DimensionedField<diagTensor3, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(new DimensionedField<diagTensor3, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const diagTensor3& t1
	                                                       , const DimensionedField<diagTensor3, GeoMesh>& df2)
	{
		return dimensioned<diagTensor3>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const dimensioned<diagTensor3>& dt1
	                                                       , const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::New(tdf2, '(' + dt1.name() + '|' + df2.name() + ')'
			                                                                 , dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const diagTensor3& t1
	                                                       , const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf2)
	{
		return dimensioned<diagTensor3>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const DimensionedField<diagTensor3, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor3>& dt2)
	{
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(new DimensionedField<diagTensor3, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const DimensionedField<diagTensor3, GeoMesh>& df1
	                                                       , const diagTensor3& t2)
	{
		return df1 / dimensioned<diagTensor3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor3>& dt2)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + dt2.name() + ')'
			                                                                 , df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf1
	                                                       , const diagTensor3& t2)
	{
		return tdf1 / dimensioned<diagTensor3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const DimensionedField<sphericalTensor3, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor3, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(new DimensionedField<diagTensor3, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const DimensionedField<sphericalTensor3, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::New(tdf2, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                 , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor3, GeoMesh>& df2)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, sphericalTensor3, GeoMesh>::New(
				tdf1, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor3, sphericalTensor3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor3, sphericalTensor3, sphericalTensor3, diagTensor3, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor3, sphericalTensor3, sphericalTensor3, diagTensor3, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const dimensioned<sphericalTensor3>& dt1
	                                                       , const DimensionedField<diagTensor3, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(new DimensionedField<diagTensor3, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const sphericalTensor3& t1
	                                                       , const DimensionedField<diagTensor3, GeoMesh>& df2)
	{
		return dimensioned<sphericalTensor3>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const dimensioned<sphericalTensor3>& dt1
	                                                       , const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::New(tdf2, '(' + dt1.name() + '|' + df2.name() + ')'
			                                                                 , dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const sphericalTensor3& t1
	                                                       , const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf2)
	{
		return dimensioned<sphericalTensor3>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const DimensionedField<sphericalTensor3, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor3>& dt2)
	{
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(new DimensionedField<diagTensor3, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const DimensionedField<sphericalTensor3, GeoMesh>& df1
	                                                       , const diagTensor3& t2)
	{
		return df1 / dimensioned<diagTensor3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor3>& dt2)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, sphericalTensor3, GeoMesh>::New(
				tdf1, '(' + df1.name() + '|' + dt2.name() + ')', df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor3, sphericalTensor3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf1
	                                                       , const diagTensor3& t2)
	{
		return tdf1 / dimensioned<diagTensor3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const DimensionedField<diagTensor3, GeoMesh>& df1
	                                                       , const DimensionedField<sphericalTensor3, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(new DimensionedField<diagTensor3, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const DimensionedField<diagTensor3, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, sphericalTensor3, GeoMesh>::New(
				tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor3, sphericalTensor3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf1
	                                                       , const DimensionedField<sphericalTensor3, GeoMesh>& df2)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                 , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor3, diagTensor3, diagTensor3, sphericalTensor3, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor3, diagTensor3, diagTensor3, sphericalTensor3, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const dimensioned<diagTensor3>& dt1
	                                                       , const DimensionedField<sphericalTensor3, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(new DimensionedField<diagTensor3, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const diagTensor3& t1
	                                                       , const DimensionedField<sphericalTensor3, GeoMesh>& df2)
	{
		return dimensioned<diagTensor3>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const dimensioned<diagTensor3>& dt1
	                                                       , const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, sphericalTensor3, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '|' + df2.name() + ')', dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor3, sphericalTensor3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const diagTensor3& t1
	                                                       , const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf2)
	{
		return dimensioned<diagTensor3>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const DimensionedField<diagTensor3, GeoMesh>& df1
	                                                       , const dimensioned<sphericalTensor3>& dt2)
	{
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(new DimensionedField<diagTensor3, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const DimensionedField<diagTensor3, GeoMesh>& df1
	                                                       , const sphericalTensor3& t2)
	{
		return df1 / dimensioned<sphericalTensor3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf1
	                                                       , const dimensioned<sphericalTensor3>& dt2)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + dt2.name() + ')'
			                                                                 , df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf1
	                                                       , const sphericalTensor3& t2)
	{
		return tdf1 / dimensioned<sphericalTensor3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const DimensionedField<diagTensor3, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor3, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(new DimensionedField<diagTensor3, GeoMesh>(
			IOobject('(' + df1.name() + '+' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const DimensionedField<diagTensor3, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::New(tdf2, '(' + df1.name() + '+' + df2.name() + ')'
			                                                                 , df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor3, GeoMesh>& df2)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + df2.name() + ')'
			                                                                 , df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor3, diagTensor3, diagTensor3, diagTensor3, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor3, diagTensor3, diagTensor3, diagTensor3, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const DimensionedField<diagTensor3, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor3, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(new DimensionedField<diagTensor3, GeoMesh>(
			IOobject('(' + df1.name() + '-' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const DimensionedField<diagTensor3, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::New(tdf2, '(' + df1.name() + '-' + df2.name() + ')'
			                                                                 , df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor3, GeoMesh>& df2)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::New(tdf1, '(' + df1.name() + '-' + df2.name() + ')'
			                                                                 , df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor3, diagTensor3, diagTensor3, diagTensor3, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor3, diagTensor3, diagTensor3, diagTensor3, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const dimensioned<diagTensor3>& dt1
	                                                       , const DimensionedField<diagTensor3, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(new DimensionedField<diagTensor3, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const diagTensor3& t1
	                                                       , const DimensionedField<diagTensor3, GeoMesh>& df2)
	{
		return dimensioned<diagTensor3>(t1) + df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const dimensioned<diagTensor3>& dt1
	                                                       , const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::New(tdf2, '(' + dt1.name() + '+' + df2.name() + ')'
			                                                                 , dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const diagTensor3& t1
	                                                       , const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf2)
	{
		return dimensioned<diagTensor3>(t1) + tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const DimensionedField<diagTensor3, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor3>& dt2)
	{
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(new DimensionedField<diagTensor3, GeoMesh>(
			IOobject('(' + df1.name() + '+' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const DimensionedField<diagTensor3, GeoMesh>& df1
	                                                       , const diagTensor3& t2)
	{
		return df1 + dimensioned<diagTensor3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor3>& dt2)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + dt2.name() + ')'
			                                                                 , df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf1
	                                                       , const diagTensor3& t2)
	{
		return tdf1 + dimensioned<diagTensor3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const dimensioned<diagTensor3>& dt1
	                                                       , const DimensionedField<diagTensor3, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(new DimensionedField<diagTensor3, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const diagTensor3& t1
	                                                       , const DimensionedField<diagTensor3, GeoMesh>& df2)
	{
		return dimensioned<diagTensor3>(t1) - df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const dimensioned<diagTensor3>& dt1
	                                                       , const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::New(tdf2, '(' + dt1.name() + '-' + df2.name() + ')'
			                                                                 , dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const diagTensor3& t1
	                                                       , const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf2)
	{
		return dimensioned<diagTensor3>(t1) - tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const DimensionedField<diagTensor3, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor3>& dt2)
	{
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(new DimensionedField<diagTensor3, GeoMesh>(
			IOobject('(' + df1.name() + '-' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const DimensionedField<diagTensor3, GeoMesh>& df1
	                                                       , const diagTensor3& t2)
	{
		return df1 - dimensioned<diagTensor3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor3>& dt2)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::New(tdf1, '(' + df1.name() + '-' + dt2.name() + ')'
			                                                                 , df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf1
	                                                       , const diagTensor3& t2)
	{
		return tdf1 - dimensioned<diagTensor3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const DimensionedField<sphericalTensor3, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor3, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(new DimensionedField<diagTensor3, GeoMesh>(
			IOobject('(' + df1.name() + '+' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const DimensionedField<sphericalTensor3, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::New(tdf2, '(' + df1.name() + '+' + df2.name() + ')'
			                                                                 , df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor3, GeoMesh>& df2)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, sphericalTensor3, GeoMesh>::New(
				tdf1, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor3, sphericalTensor3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor3, sphericalTensor3, sphericalTensor3, diagTensor3, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor3, sphericalTensor3, sphericalTensor3, diagTensor3, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const DimensionedField<sphericalTensor3, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor3, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(new DimensionedField<diagTensor3, GeoMesh>(
			IOobject('(' + df1.name() + '-' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const DimensionedField<sphericalTensor3, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::New(tdf2, '(' + df1.name() + '-' + df2.name() + ')'
			                                                                 , df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor3, GeoMesh>& df2)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, sphericalTensor3, GeoMesh>::New(
				tdf1, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor3, sphericalTensor3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor3, sphericalTensor3, sphericalTensor3, diagTensor3, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor3, sphericalTensor3, sphericalTensor3, diagTensor3, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const dimensioned<sphericalTensor3>& dt1
	                                                       , const DimensionedField<diagTensor3, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(new DimensionedField<diagTensor3, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const sphericalTensor3& t1
	                                                       , const DimensionedField<diagTensor3, GeoMesh>& df2)
	{
		return dimensioned<sphericalTensor3>(t1) + df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const dimensioned<sphericalTensor3>& dt1
	                                                       , const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::New(tdf2, '(' + dt1.name() + '+' + df2.name() + ')'
			                                                                 , dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const sphericalTensor3& t1
	                                                       , const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf2)
	{
		return dimensioned<sphericalTensor3>(t1) + tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const DimensionedField<sphericalTensor3, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor3>& dt2)
	{
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(new DimensionedField<diagTensor3, GeoMesh>(
			IOobject('(' + df1.name() + '+' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const DimensionedField<sphericalTensor3, GeoMesh>& df1
	                                                       , const diagTensor3& t2)
	{
		return df1 + dimensioned<diagTensor3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor3>& dt2)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, sphericalTensor3, GeoMesh>::New(
				tdf1, '(' + df1.name() + '+' + dt2.name() + ')', df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor3, sphericalTensor3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf1
	                                                       , const diagTensor3& t2)
	{
		return tdf1 + dimensioned<diagTensor3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const dimensioned<sphericalTensor3>& dt1
	                                                       , const DimensionedField<diagTensor3, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(new DimensionedField<diagTensor3, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const sphericalTensor3& t1
	                                                       , const DimensionedField<diagTensor3, GeoMesh>& df2)
	{
		return dimensioned<sphericalTensor3>(t1) - df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const dimensioned<sphericalTensor3>& dt1
	                                                       , const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::New(tdf2, '(' + dt1.name() + '-' + df2.name() + ')'
			                                                                 , dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const sphericalTensor3& t1
	                                                       , const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf2)
	{
		return dimensioned<sphericalTensor3>(t1) - tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const DimensionedField<sphericalTensor3, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor3>& dt2)
	{
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(new DimensionedField<diagTensor3, GeoMesh>(
			IOobject('(' + df1.name() + '-' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const DimensionedField<sphericalTensor3, GeoMesh>& df1
	                                                       , const diagTensor3& t2)
	{
		return df1 - dimensioned<diagTensor3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor3>& dt2)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, sphericalTensor3, GeoMesh>::New(
				tdf1, '(' + df1.name() + '-' + dt2.name() + ')', df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor3, sphericalTensor3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf1
	                                                       , const diagTensor3& t2)
	{
		return tdf1 - dimensioned<diagTensor3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const DimensionedField<diagTensor3, GeoMesh>& df1
	                                                       , const DimensionedField<sphericalTensor3, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(new DimensionedField<diagTensor3, GeoMesh>(
			IOobject('(' + df1.name() + '+' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const DimensionedField<diagTensor3, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, sphericalTensor3, GeoMesh>::New(
				tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor3, sphericalTensor3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf1
	                                                       , const DimensionedField<sphericalTensor3, GeoMesh>& df2)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + df2.name() + ')'
			                                                                 , df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor3, diagTensor3, diagTensor3, sphericalTensor3, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor3, diagTensor3, diagTensor3, sphericalTensor3, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const DimensionedField<diagTensor3, GeoMesh>& df1
	                                                       , const DimensionedField<sphericalTensor3, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(new DimensionedField<diagTensor3, GeoMesh>(
			IOobject('(' + df1.name() + '-' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const DimensionedField<diagTensor3, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, sphericalTensor3, GeoMesh>::New(
				tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor3, sphericalTensor3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf1
	                                                       , const DimensionedField<sphericalTensor3, GeoMesh>& df2)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::New(tdf1, '(' + df1.name() + '-' + df2.name() + ')'
			                                                                 , df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor3, diagTensor3, diagTensor3, sphericalTensor3, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor3, diagTensor3, diagTensor3, sphericalTensor3, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const dimensioned<diagTensor3>& dt1
	                                                       , const DimensionedField<sphericalTensor3, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(new DimensionedField<diagTensor3, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const diagTensor3& t1
	                                                       , const DimensionedField<sphericalTensor3, GeoMesh>& df2)
	{
		return dimensioned<diagTensor3>(t1) + df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const dimensioned<diagTensor3>& dt1
	                                                       , const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, sphericalTensor3, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '+' + df2.name() + ')', dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor3, sphericalTensor3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const diagTensor3& t1
	                                                       , const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf2)
	{
		return dimensioned<diagTensor3>(t1) + tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const DimensionedField<diagTensor3, GeoMesh>& df1
	                                                       , const dimensioned<sphericalTensor3>& dt2)
	{
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(new DimensionedField<diagTensor3, GeoMesh>(
			IOobject('(' + df1.name() + '+' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const DimensionedField<diagTensor3, GeoMesh>& df1
	                                                       , const sphericalTensor3& t2)
	{
		return df1 + dimensioned<sphericalTensor3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf1
	                                                       , const dimensioned<sphericalTensor3>& dt2)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + dt2.name() + ')'
			                                                                 , df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf1
	                                                       , const sphericalTensor3& t2)
	{
		return tdf1 + dimensioned<sphericalTensor3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const dimensioned<diagTensor3>& dt1
	                                                       , const DimensionedField<sphericalTensor3, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(new DimensionedField<diagTensor3, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const diagTensor3& t1
	                                                       , const DimensionedField<sphericalTensor3, GeoMesh>& df2)
	{
		return dimensioned<diagTensor3>(t1) - df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const dimensioned<diagTensor3>& dt1
	                                                       , const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor3, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, sphericalTensor3, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '+' + df2.name() + ')', dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor3, sphericalTensor3, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const diagTensor3& t1
	                                                       , const tmp<DimensionedField<sphericalTensor3, GeoMesh>>& tdf2)
	{
		return dimensioned<diagTensor3>(t1) - tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const DimensionedField<diagTensor3, GeoMesh>& df1
	                                                       , const dimensioned<sphericalTensor3>& dt2)
	{
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(new DimensionedField<diagTensor3, GeoMesh>(
			IOobject('(' + df1.name() + '+' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const DimensionedField<diagTensor3, GeoMesh>& df1
	                                                       , const sphericalTensor3& t2)
	{
		return df1 - dimensioned<sphericalTensor3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf1
	                                                       , const dimensioned<sphericalTensor3>& dt2)
	{
		const DimensionedField<diagTensor3, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor3, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + dt2.name() + ')'
			                                                                 , df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor3, diagTensor3, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor3, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor3, GeoMesh>>& tdf1
	                                                       , const sphericalTensor3& t2)
	{
		return tdf1 - dimensioned<sphericalTensor3>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> inv(const DimensionedField<diagTensor4, GeoMesh>& df1)
	{
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(new DimensionedField<diagTensor4, GeoMesh>(
			IOobject("inv" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), inv(df1.dimensions())));
		inv(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> inv(const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf1)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::New(tdf1, "inv" "(" + df1.name() + ')'
			                                                                 , inv(df1.dimensions())));
		inv(tRes().field(), df1.field());
		reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> diag(const DimensionedField<diagTensor4, GeoMesh>& df1)
	{
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(new DimensionedField<diagTensor4, GeoMesh>(
			IOobject("diag" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), diag(df1.dimensions())));
		diag(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> diag(const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf1)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::New(tdf1, "diag" "(" + df1.name() + ')'
			                                                                 , diag(df1.dimensions())));
		diag(tRes().field(), df1.field());
		reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> contractLinear(const DimensionedField<diagTensor4, GeoMesh>& df1)
	{
		tmp<DimensionedField<vector4, GeoMesh>> tRes(new DimensionedField<vector4, GeoMesh>(
			IOobject("contractLinear" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, contractLinear(df1.dimensions())));
		contractLinear(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> contractLinear(const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf1)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector4, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector4, diagTensor4, GeoMesh>::New(tdf1, "contractLinear" "(" + df1.name() + ')'
			                                                             , contractLinear(df1.dimensions())));
		contractLinear(tRes().field(), df1.field());
		reuseTmpDimensionedField<vector4, diagTensor4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> contractScalar(const DimensionedField<diagTensor4, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("contractScalar" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, contractLinear(df1.dimensions())));
		contractScalar(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> contractScalar(const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf1)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, diagTensor4, GeoMesh>::New(tdf1, "contractScalar" "(" + df1.name() + ')'
			                                                            , contractLinear(df1.dimensions())));
		contractScalar(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, diagTensor4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor4, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(new DimensionedField<diagTensor4, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::New(tdf2, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                 , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor4, GeoMesh>& df2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + df2.name() + ')'
			                                                            , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor4, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor4, scalar, scalar, diagTensor4, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor4, scalar, scalar, diagTensor4, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const dimensioned<scalar>& dt1
	                                                       , const DimensionedField<diagTensor4, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(new DimensionedField<diagTensor4, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const scalar& t1
	                                                       , const DimensionedField<diagTensor4, GeoMesh>& df2)
	{
		return dimensioned<scalar>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const dimensioned<scalar>& dt1
	                                                       , const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::New(tdf2, '(' + dt1.name() + '|' + df2.name() + ')'
			                                                                 , dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const scalar& t1
	                                                       , const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf2)
	{
		return dimensioned<scalar>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor4>& dt2)
	{
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(new DimensionedField<diagTensor4, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                       , const diagTensor4& t2)
	{
		return df1 / dimensioned<diagTensor4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor4>& dt2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + dt2.name() + ')'
			                                                            , df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor4, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                       , const diagTensor4& t2)
	{
		return tdf1 / dimensioned<diagTensor4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator /(const DimensionedField<vector4, GeoMesh>& df1
	                                                   , const DimensionedField<diagTensor4, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector4, GeoMesh>> tRes(new DimensionedField<vector4, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator /(const DimensionedField<vector4, GeoMesh>& df1
	                                                   , const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector4, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector4, diagTensor4, GeoMesh>::New(tdf2, '(' + df1.name() + '|' + df2.name() + ')'
			                                                             , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector4, diagTensor4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator /(const tmp<DimensionedField<vector4, GeoMesh>>& tdf1
	                                                   , const DimensionedField<diagTensor4, GeoMesh>& df2)
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
	                                                   , const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector4, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector4, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<vector4, vector4, vector4, diagTensor4, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<vector4, vector4, vector4, diagTensor4, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator /(const dimensioned<vector4>& dt1
	                                                   , const DimensionedField<diagTensor4, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector4, GeoMesh>> tRes(new DimensionedField<vector4, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator /(const vector4& t1
	                                                   , const DimensionedField<diagTensor4, GeoMesh>& df2)
	{
		return dimensioned<vector4>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator /(const dimensioned<vector4>& dt1
	                                                   , const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector4, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector4, diagTensor4, GeoMesh>::New(tdf2, '(' + dt1.name() + '|' + df2.name() + ')'
			                                                             , dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<vector4, diagTensor4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator /(const vector4& t1
	                                                   , const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf2)
	{
		return dimensioned<vector4>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator /(const DimensionedField<vector4, GeoMesh>& df1
	                                                   , const dimensioned<diagTensor4>& dt2)
	{
		tmp<DimensionedField<vector4, GeoMesh>> tRes(new DimensionedField<vector4, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator /(const DimensionedField<vector4, GeoMesh>& df1
	                                                   , const diagTensor4& t2)
	{
		return df1 / dimensioned<diagTensor4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector4, GeoMesh>> operator /(const tmp<DimensionedField<vector4, GeoMesh>>& tdf1
	                                                   , const dimensioned<diagTensor4>& dt2)
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
	                                                   , const diagTensor4& t2)
	{
		return tdf1 / dimensioned<diagTensor4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const DimensionedField<diagTensor4, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor4, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(new DimensionedField<diagTensor4, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const DimensionedField<diagTensor4, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::New(tdf2, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                 , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor4, GeoMesh>& df2)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                 , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor4, diagTensor4, diagTensor4, diagTensor4, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor4, diagTensor4, diagTensor4, diagTensor4, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const dimensioned<diagTensor4>& dt1
	                                                       , const DimensionedField<diagTensor4, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(new DimensionedField<diagTensor4, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const diagTensor4& t1
	                                                       , const DimensionedField<diagTensor4, GeoMesh>& df2)
	{
		return dimensioned<diagTensor4>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const dimensioned<diagTensor4>& dt1
	                                                       , const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::New(tdf2, '(' + dt1.name() + '|' + df2.name() + ')'
			                                                                 , dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const diagTensor4& t1
	                                                       , const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf2)
	{
		return dimensioned<diagTensor4>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const DimensionedField<diagTensor4, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor4>& dt2)
	{
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(new DimensionedField<diagTensor4, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const DimensionedField<diagTensor4, GeoMesh>& df1
	                                                       , const diagTensor4& t2)
	{
		return df1 / dimensioned<diagTensor4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor4>& dt2)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + dt2.name() + ')'
			                                                                 , df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf1
	                                                       , const diagTensor4& t2)
	{
		return tdf1 / dimensioned<diagTensor4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const DimensionedField<sphericalTensor4, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor4, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(new DimensionedField<diagTensor4, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const DimensionedField<sphericalTensor4, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::New(tdf2, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                 , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor4, GeoMesh>& df2)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, sphericalTensor4, GeoMesh>::New(
				tdf1, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor4, sphericalTensor4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor4, sphericalTensor4, sphericalTensor4, diagTensor4, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor4, sphericalTensor4, sphericalTensor4, diagTensor4, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const dimensioned<sphericalTensor4>& dt1
	                                                       , const DimensionedField<diagTensor4, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(new DimensionedField<diagTensor4, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const sphericalTensor4& t1
	                                                       , const DimensionedField<diagTensor4, GeoMesh>& df2)
	{
		return dimensioned<sphericalTensor4>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const dimensioned<sphericalTensor4>& dt1
	                                                       , const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::New(tdf2, '(' + dt1.name() + '|' + df2.name() + ')'
			                                                                 , dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const sphericalTensor4& t1
	                                                       , const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf2)
	{
		return dimensioned<sphericalTensor4>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const DimensionedField<sphericalTensor4, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor4>& dt2)
	{
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(new DimensionedField<diagTensor4, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const DimensionedField<sphericalTensor4, GeoMesh>& df1
	                                                       , const diagTensor4& t2)
	{
		return df1 / dimensioned<diagTensor4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor4>& dt2)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, sphericalTensor4, GeoMesh>::New(
				tdf1, '(' + df1.name() + '|' + dt2.name() + ')', df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor4, sphericalTensor4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf1
	                                                       , const diagTensor4& t2)
	{
		return tdf1 / dimensioned<diagTensor4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const DimensionedField<diagTensor4, GeoMesh>& df1
	                                                       , const DimensionedField<sphericalTensor4, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(new DimensionedField<diagTensor4, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const DimensionedField<diagTensor4, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, sphericalTensor4, GeoMesh>::New(
				tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor4, sphericalTensor4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf1
	                                                       , const DimensionedField<sphericalTensor4, GeoMesh>& df2)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                 , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor4, diagTensor4, diagTensor4, sphericalTensor4, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor4, diagTensor4, diagTensor4, sphericalTensor4, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const dimensioned<diagTensor4>& dt1
	                                                       , const DimensionedField<sphericalTensor4, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(new DimensionedField<diagTensor4, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const diagTensor4& t1
	                                                       , const DimensionedField<sphericalTensor4, GeoMesh>& df2)
	{
		return dimensioned<diagTensor4>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const dimensioned<diagTensor4>& dt1
	                                                       , const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, sphericalTensor4, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '|' + df2.name() + ')', dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor4, sphericalTensor4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const diagTensor4& t1
	                                                       , const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf2)
	{
		return dimensioned<diagTensor4>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const DimensionedField<diagTensor4, GeoMesh>& df1
	                                                       , const dimensioned<sphericalTensor4>& dt2)
	{
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(new DimensionedField<diagTensor4, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const DimensionedField<diagTensor4, GeoMesh>& df1
	                                                       , const sphericalTensor4& t2)
	{
		return df1 / dimensioned<sphericalTensor4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf1
	                                                       , const dimensioned<sphericalTensor4>& dt2)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + dt2.name() + ')'
			                                                                 , df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf1
	                                                       , const sphericalTensor4& t2)
	{
		return tdf1 / dimensioned<sphericalTensor4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const DimensionedField<diagTensor4, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor4, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(new DimensionedField<diagTensor4, GeoMesh>(
			IOobject('(' + df1.name() + '+' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const DimensionedField<diagTensor4, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::New(tdf2, '(' + df1.name() + '+' + df2.name() + ')'
			                                                                 , df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor4, GeoMesh>& df2)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + df2.name() + ')'
			                                                                 , df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor4, diagTensor4, diagTensor4, diagTensor4, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor4, diagTensor4, diagTensor4, diagTensor4, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const DimensionedField<diagTensor4, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor4, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(new DimensionedField<diagTensor4, GeoMesh>(
			IOobject('(' + df1.name() + '-' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const DimensionedField<diagTensor4, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::New(tdf2, '(' + df1.name() + '-' + df2.name() + ')'
			                                                                 , df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor4, GeoMesh>& df2)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::New(tdf1, '(' + df1.name() + '-' + df2.name() + ')'
			                                                                 , df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor4, diagTensor4, diagTensor4, diagTensor4, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor4, diagTensor4, diagTensor4, diagTensor4, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const dimensioned<diagTensor4>& dt1
	                                                       , const DimensionedField<diagTensor4, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(new DimensionedField<diagTensor4, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const diagTensor4& t1
	                                                       , const DimensionedField<diagTensor4, GeoMesh>& df2)
	{
		return dimensioned<diagTensor4>(t1) + df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const dimensioned<diagTensor4>& dt1
	                                                       , const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::New(tdf2, '(' + dt1.name() + '+' + df2.name() + ')'
			                                                                 , dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const diagTensor4& t1
	                                                       , const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf2)
	{
		return dimensioned<diagTensor4>(t1) + tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const DimensionedField<diagTensor4, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor4>& dt2)
	{
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(new DimensionedField<diagTensor4, GeoMesh>(
			IOobject('(' + df1.name() + '+' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const DimensionedField<diagTensor4, GeoMesh>& df1
	                                                       , const diagTensor4& t2)
	{
		return df1 + dimensioned<diagTensor4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor4>& dt2)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + dt2.name() + ')'
			                                                                 , df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf1
	                                                       , const diagTensor4& t2)
	{
		return tdf1 + dimensioned<diagTensor4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const dimensioned<diagTensor4>& dt1
	                                                       , const DimensionedField<diagTensor4, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(new DimensionedField<diagTensor4, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const diagTensor4& t1
	                                                       , const DimensionedField<diagTensor4, GeoMesh>& df2)
	{
		return dimensioned<diagTensor4>(t1) - df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const dimensioned<diagTensor4>& dt1
	                                                       , const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::New(tdf2, '(' + dt1.name() + '-' + df2.name() + ')'
			                                                                 , dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const diagTensor4& t1
	                                                       , const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf2)
	{
		return dimensioned<diagTensor4>(t1) - tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const DimensionedField<diagTensor4, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor4>& dt2)
	{
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(new DimensionedField<diagTensor4, GeoMesh>(
			IOobject('(' + df1.name() + '-' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const DimensionedField<diagTensor4, GeoMesh>& df1
	                                                       , const diagTensor4& t2)
	{
		return df1 - dimensioned<diagTensor4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor4>& dt2)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::New(tdf1, '(' + df1.name() + '-' + dt2.name() + ')'
			                                                                 , df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf1
	                                                       , const diagTensor4& t2)
	{
		return tdf1 - dimensioned<diagTensor4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const DimensionedField<sphericalTensor4, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor4, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(new DimensionedField<diagTensor4, GeoMesh>(
			IOobject('(' + df1.name() + '+' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const DimensionedField<sphericalTensor4, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::New(tdf2, '(' + df1.name() + '+' + df2.name() + ')'
			                                                                 , df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor4, GeoMesh>& df2)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, sphericalTensor4, GeoMesh>::New(
				tdf1, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor4, sphericalTensor4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor4, sphericalTensor4, sphericalTensor4, diagTensor4, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor4, sphericalTensor4, sphericalTensor4, diagTensor4, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const DimensionedField<sphericalTensor4, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor4, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(new DimensionedField<diagTensor4, GeoMesh>(
			IOobject('(' + df1.name() + '-' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const DimensionedField<sphericalTensor4, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::New(tdf2, '(' + df1.name() + '-' + df2.name() + ')'
			                                                                 , df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor4, GeoMesh>& df2)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, sphericalTensor4, GeoMesh>::New(
				tdf1, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor4, sphericalTensor4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor4, sphericalTensor4, sphericalTensor4, diagTensor4, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor4, sphericalTensor4, sphericalTensor4, diagTensor4, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const dimensioned<sphericalTensor4>& dt1
	                                                       , const DimensionedField<diagTensor4, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(new DimensionedField<diagTensor4, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const sphericalTensor4& t1
	                                                       , const DimensionedField<diagTensor4, GeoMesh>& df2)
	{
		return dimensioned<sphericalTensor4>(t1) + df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const dimensioned<sphericalTensor4>& dt1
	                                                       , const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::New(tdf2, '(' + dt1.name() + '+' + df2.name() + ')'
			                                                                 , dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const sphericalTensor4& t1
	                                                       , const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf2)
	{
		return dimensioned<sphericalTensor4>(t1) + tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const DimensionedField<sphericalTensor4, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor4>& dt2)
	{
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(new DimensionedField<diagTensor4, GeoMesh>(
			IOobject('(' + df1.name() + '+' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const DimensionedField<sphericalTensor4, GeoMesh>& df1
	                                                       , const diagTensor4& t2)
	{
		return df1 + dimensioned<diagTensor4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor4>& dt2)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, sphericalTensor4, GeoMesh>::New(
				tdf1, '(' + df1.name() + '+' + dt2.name() + ')', df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor4, sphericalTensor4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf1
	                                                       , const diagTensor4& t2)
	{
		return tdf1 + dimensioned<diagTensor4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const dimensioned<sphericalTensor4>& dt1
	                                                       , const DimensionedField<diagTensor4, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(new DimensionedField<diagTensor4, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const sphericalTensor4& t1
	                                                       , const DimensionedField<diagTensor4, GeoMesh>& df2)
	{
		return dimensioned<sphericalTensor4>(t1) - df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const dimensioned<sphericalTensor4>& dt1
	                                                       , const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::New(tdf2, '(' + dt1.name() + '-' + df2.name() + ')'
			                                                                 , dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const sphericalTensor4& t1
	                                                       , const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf2)
	{
		return dimensioned<sphericalTensor4>(t1) - tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const DimensionedField<sphericalTensor4, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor4>& dt2)
	{
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(new DimensionedField<diagTensor4, GeoMesh>(
			IOobject('(' + df1.name() + '-' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const DimensionedField<sphericalTensor4, GeoMesh>& df1
	                                                       , const diagTensor4& t2)
	{
		return df1 - dimensioned<diagTensor4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor4>& dt2)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, sphericalTensor4, GeoMesh>::New(
				tdf1, '(' + df1.name() + '-' + dt2.name() + ')', df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor4, sphericalTensor4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf1
	                                                       , const diagTensor4& t2)
	{
		return tdf1 - dimensioned<diagTensor4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const DimensionedField<diagTensor4, GeoMesh>& df1
	                                                       , const DimensionedField<sphericalTensor4, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(new DimensionedField<diagTensor4, GeoMesh>(
			IOobject('(' + df1.name() + '+' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const DimensionedField<diagTensor4, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, sphericalTensor4, GeoMesh>::New(
				tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor4, sphericalTensor4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf1
	                                                       , const DimensionedField<sphericalTensor4, GeoMesh>& df2)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + df2.name() + ')'
			                                                                 , df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor4, diagTensor4, diagTensor4, sphericalTensor4, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor4, diagTensor4, diagTensor4, sphericalTensor4, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const DimensionedField<diagTensor4, GeoMesh>& df1
	                                                       , const DimensionedField<sphericalTensor4, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(new DimensionedField<diagTensor4, GeoMesh>(
			IOobject('(' + df1.name() + '-' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const DimensionedField<diagTensor4, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, sphericalTensor4, GeoMesh>::New(
				tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor4, sphericalTensor4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf1
	                                                       , const DimensionedField<sphericalTensor4, GeoMesh>& df2)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::New(tdf1, '(' + df1.name() + '-' + df2.name() + ')'
			                                                                 , df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor4, diagTensor4, diagTensor4, sphericalTensor4, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor4, diagTensor4, diagTensor4, sphericalTensor4, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const dimensioned<diagTensor4>& dt1
	                                                       , const DimensionedField<sphericalTensor4, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(new DimensionedField<diagTensor4, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const diagTensor4& t1
	                                                       , const DimensionedField<sphericalTensor4, GeoMesh>& df2)
	{
		return dimensioned<diagTensor4>(t1) + df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const dimensioned<diagTensor4>& dt1
	                                                       , const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, sphericalTensor4, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '+' + df2.name() + ')', dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor4, sphericalTensor4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const diagTensor4& t1
	                                                       , const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf2)
	{
		return dimensioned<diagTensor4>(t1) + tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const DimensionedField<diagTensor4, GeoMesh>& df1
	                                                       , const dimensioned<sphericalTensor4>& dt2)
	{
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(new DimensionedField<diagTensor4, GeoMesh>(
			IOobject('(' + df1.name() + '+' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const DimensionedField<diagTensor4, GeoMesh>& df1
	                                                       , const sphericalTensor4& t2)
	{
		return df1 + dimensioned<sphericalTensor4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf1
	                                                       , const dimensioned<sphericalTensor4>& dt2)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + dt2.name() + ')'
			                                                                 , df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf1
	                                                       , const sphericalTensor4& t2)
	{
		return tdf1 + dimensioned<sphericalTensor4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const dimensioned<diagTensor4>& dt1
	                                                       , const DimensionedField<sphericalTensor4, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(new DimensionedField<diagTensor4, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const diagTensor4& t1
	                                                       , const DimensionedField<sphericalTensor4, GeoMesh>& df2)
	{
		return dimensioned<diagTensor4>(t1) - df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const dimensioned<diagTensor4>& dt1
	                                                       , const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor4, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, sphericalTensor4, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '+' + df2.name() + ')', dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor4, sphericalTensor4, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const diagTensor4& t1
	                                                       , const tmp<DimensionedField<sphericalTensor4, GeoMesh>>& tdf2)
	{
		return dimensioned<diagTensor4>(t1) - tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const DimensionedField<diagTensor4, GeoMesh>& df1
	                                                       , const dimensioned<sphericalTensor4>& dt2)
	{
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(new DimensionedField<diagTensor4, GeoMesh>(
			IOobject('(' + df1.name() + '+' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const DimensionedField<diagTensor4, GeoMesh>& df1
	                                                       , const sphericalTensor4& t2)
	{
		return df1 - dimensioned<sphericalTensor4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf1
	                                                       , const dimensioned<sphericalTensor4>& dt2)
	{
		const DimensionedField<diagTensor4, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor4, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + dt2.name() + ')'
			                                                                 , df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor4, diagTensor4, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor4, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor4, GeoMesh>>& tdf1
	                                                       , const sphericalTensor4& t2)
	{
		return tdf1 - dimensioned<sphericalTensor4>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> inv(const DimensionedField<diagTensor6, GeoMesh>& df1)
	{
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(new DimensionedField<diagTensor6, GeoMesh>(
			IOobject("inv" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), inv(df1.dimensions())));
		inv(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> inv(const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf1)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::New(tdf1, "inv" "(" + df1.name() + ')'
			                                                                 , inv(df1.dimensions())));
		inv(tRes().field(), df1.field());
		reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> diag(const DimensionedField<diagTensor6, GeoMesh>& df1)
	{
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(new DimensionedField<diagTensor6, GeoMesh>(
			IOobject("diag" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), diag(df1.dimensions())));
		diag(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> diag(const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf1)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::New(tdf1, "diag" "(" + df1.name() + ')'
			                                                                 , diag(df1.dimensions())));
		diag(tRes().field(), df1.field());
		reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> contractLinear(const DimensionedField<diagTensor6, GeoMesh>& df1)
	{
		tmp<DimensionedField<vector6, GeoMesh>> tRes(new DimensionedField<vector6, GeoMesh>(
			IOobject("contractLinear" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, contractLinear(df1.dimensions())));
		contractLinear(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> contractLinear(const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf1)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector6, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector6, diagTensor6, GeoMesh>::New(tdf1, "contractLinear" "(" + df1.name() + ')'
			                                                             , contractLinear(df1.dimensions())));
		contractLinear(tRes().field(), df1.field());
		reuseTmpDimensionedField<vector6, diagTensor6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> contractScalar(const DimensionedField<diagTensor6, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("contractScalar" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, contractLinear(df1.dimensions())));
		contractScalar(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> contractScalar(const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf1)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, diagTensor6, GeoMesh>::New(tdf1, "contractScalar" "(" + df1.name() + ')'
			                                                            , contractLinear(df1.dimensions())));
		contractScalar(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, diagTensor6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor6, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(new DimensionedField<diagTensor6, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::New(tdf2, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                 , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor6, GeoMesh>& df2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + df2.name() + ')'
			                                                            , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor6, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor6, scalar, scalar, diagTensor6, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor6, scalar, scalar, diagTensor6, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const dimensioned<scalar>& dt1
	                                                       , const DimensionedField<diagTensor6, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(new DimensionedField<diagTensor6, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const scalar& t1
	                                                       , const DimensionedField<diagTensor6, GeoMesh>& df2)
	{
		return dimensioned<scalar>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const dimensioned<scalar>& dt1
	                                                       , const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::New(tdf2, '(' + dt1.name() + '|' + df2.name() + ')'
			                                                                 , dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const scalar& t1
	                                                       , const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf2)
	{
		return dimensioned<scalar>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor6>& dt2)
	{
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(new DimensionedField<diagTensor6, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                       , const diagTensor6& t2)
	{
		return df1 / dimensioned<diagTensor6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor6>& dt2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + dt2.name() + ')'
			                                                            , df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor6, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                       , const diagTensor6& t2)
	{
		return tdf1 / dimensioned<diagTensor6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator /(const DimensionedField<vector6, GeoMesh>& df1
	                                                   , const DimensionedField<diagTensor6, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector6, GeoMesh>> tRes(new DimensionedField<vector6, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator /(const DimensionedField<vector6, GeoMesh>& df1
	                                                   , const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector6, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector6, diagTensor6, GeoMesh>::New(tdf2, '(' + df1.name() + '|' + df2.name() + ')'
			                                                             , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector6, diagTensor6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator /(const tmp<DimensionedField<vector6, GeoMesh>>& tdf1
	                                                   , const DimensionedField<diagTensor6, GeoMesh>& df2)
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
	                                                   , const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector6, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector6, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<vector6, vector6, vector6, diagTensor6, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<vector6, vector6, vector6, diagTensor6, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator /(const dimensioned<vector6>& dt1
	                                                   , const DimensionedField<diagTensor6, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector6, GeoMesh>> tRes(new DimensionedField<vector6, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator /(const vector6& t1
	                                                   , const DimensionedField<diagTensor6, GeoMesh>& df2)
	{
		return dimensioned<vector6>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator /(const dimensioned<vector6>& dt1
	                                                   , const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector6, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector6, diagTensor6, GeoMesh>::New(tdf2, '(' + dt1.name() + '|' + df2.name() + ')'
			                                                             , dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<vector6, diagTensor6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator /(const vector6& t1
	                                                   , const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf2)
	{
		return dimensioned<vector6>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator /(const DimensionedField<vector6, GeoMesh>& df1
	                                                   , const dimensioned<diagTensor6>& dt2)
	{
		tmp<DimensionedField<vector6, GeoMesh>> tRes(new DimensionedField<vector6, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator /(const DimensionedField<vector6, GeoMesh>& df1
	                                                   , const diagTensor6& t2)
	{
		return df1 / dimensioned<diagTensor6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector6, GeoMesh>> operator /(const tmp<DimensionedField<vector6, GeoMesh>>& tdf1
	                                                   , const dimensioned<diagTensor6>& dt2)
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
	                                                   , const diagTensor6& t2)
	{
		return tdf1 / dimensioned<diagTensor6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const DimensionedField<diagTensor6, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor6, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(new DimensionedField<diagTensor6, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const DimensionedField<diagTensor6, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::New(tdf2, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                 , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor6, GeoMesh>& df2)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                 , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor6, diagTensor6, diagTensor6, diagTensor6, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor6, diagTensor6, diagTensor6, diagTensor6, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const dimensioned<diagTensor6>& dt1
	                                                       , const DimensionedField<diagTensor6, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(new DimensionedField<diagTensor6, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const diagTensor6& t1
	                                                       , const DimensionedField<diagTensor6, GeoMesh>& df2)
	{
		return dimensioned<diagTensor6>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const dimensioned<diagTensor6>& dt1
	                                                       , const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::New(tdf2, '(' + dt1.name() + '|' + df2.name() + ')'
			                                                                 , dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const diagTensor6& t1
	                                                       , const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf2)
	{
		return dimensioned<diagTensor6>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const DimensionedField<diagTensor6, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor6>& dt2)
	{
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(new DimensionedField<diagTensor6, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const DimensionedField<diagTensor6, GeoMesh>& df1
	                                                       , const diagTensor6& t2)
	{
		return df1 / dimensioned<diagTensor6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor6>& dt2)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + dt2.name() + ')'
			                                                                 , df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf1
	                                                       , const diagTensor6& t2)
	{
		return tdf1 / dimensioned<diagTensor6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const DimensionedField<sphericalTensor6, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor6, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(new DimensionedField<diagTensor6, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const DimensionedField<sphericalTensor6, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::New(tdf2, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                 , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor6, GeoMesh>& df2)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, sphericalTensor6, GeoMesh>::New(
				tdf1, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor6, sphericalTensor6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor6, sphericalTensor6, sphericalTensor6, diagTensor6, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor6, sphericalTensor6, sphericalTensor6, diagTensor6, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const dimensioned<sphericalTensor6>& dt1
	                                                       , const DimensionedField<diagTensor6, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(new DimensionedField<diagTensor6, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const sphericalTensor6& t1
	                                                       , const DimensionedField<diagTensor6, GeoMesh>& df2)
	{
		return dimensioned<sphericalTensor6>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const dimensioned<sphericalTensor6>& dt1
	                                                       , const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::New(tdf2, '(' + dt1.name() + '|' + df2.name() + ')'
			                                                                 , dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const sphericalTensor6& t1
	                                                       , const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf2)
	{
		return dimensioned<sphericalTensor6>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const DimensionedField<sphericalTensor6, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor6>& dt2)
	{
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(new DimensionedField<diagTensor6, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const DimensionedField<sphericalTensor6, GeoMesh>& df1
	                                                       , const diagTensor6& t2)
	{
		return df1 / dimensioned<diagTensor6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor6>& dt2)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, sphericalTensor6, GeoMesh>::New(
				tdf1, '(' + df1.name() + '|' + dt2.name() + ')', df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor6, sphericalTensor6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf1
	                                                       , const diagTensor6& t2)
	{
		return tdf1 / dimensioned<diagTensor6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const DimensionedField<diagTensor6, GeoMesh>& df1
	                                                       , const DimensionedField<sphericalTensor6, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(new DimensionedField<diagTensor6, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const DimensionedField<diagTensor6, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, sphericalTensor6, GeoMesh>::New(
				tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor6, sphericalTensor6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf1
	                                                       , const DimensionedField<sphericalTensor6, GeoMesh>& df2)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                 , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor6, diagTensor6, diagTensor6, sphericalTensor6, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor6, diagTensor6, diagTensor6, sphericalTensor6, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const dimensioned<diagTensor6>& dt1
	                                                       , const DimensionedField<sphericalTensor6, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(new DimensionedField<diagTensor6, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const diagTensor6& t1
	                                                       , const DimensionedField<sphericalTensor6, GeoMesh>& df2)
	{
		return dimensioned<diagTensor6>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const dimensioned<diagTensor6>& dt1
	                                                       , const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, sphericalTensor6, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '|' + df2.name() + ')', dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor6, sphericalTensor6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const diagTensor6& t1
	                                                       , const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf2)
	{
		return dimensioned<diagTensor6>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const DimensionedField<diagTensor6, GeoMesh>& df1
	                                                       , const dimensioned<sphericalTensor6>& dt2)
	{
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(new DimensionedField<diagTensor6, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const DimensionedField<diagTensor6, GeoMesh>& df1
	                                                       , const sphericalTensor6& t2)
	{
		return df1 / dimensioned<sphericalTensor6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf1
	                                                       , const dimensioned<sphericalTensor6>& dt2)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + dt2.name() + ')'
			                                                                 , df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf1
	                                                       , const sphericalTensor6& t2)
	{
		return tdf1 / dimensioned<sphericalTensor6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const DimensionedField<diagTensor6, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor6, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(new DimensionedField<diagTensor6, GeoMesh>(
			IOobject('(' + df1.name() + '+' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const DimensionedField<diagTensor6, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::New(tdf2, '(' + df1.name() + '+' + df2.name() + ')'
			                                                                 , df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor6, GeoMesh>& df2)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + df2.name() + ')'
			                                                                 , df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor6, diagTensor6, diagTensor6, diagTensor6, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor6, diagTensor6, diagTensor6, diagTensor6, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const DimensionedField<diagTensor6, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor6, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(new DimensionedField<diagTensor6, GeoMesh>(
			IOobject('(' + df1.name() + '-' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const DimensionedField<diagTensor6, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::New(tdf2, '(' + df1.name() + '-' + df2.name() + ')'
			                                                                 , df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor6, GeoMesh>& df2)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::New(tdf1, '(' + df1.name() + '-' + df2.name() + ')'
			                                                                 , df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor6, diagTensor6, diagTensor6, diagTensor6, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor6, diagTensor6, diagTensor6, diagTensor6, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const dimensioned<diagTensor6>& dt1
	                                                       , const DimensionedField<diagTensor6, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(new DimensionedField<diagTensor6, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const diagTensor6& t1
	                                                       , const DimensionedField<diagTensor6, GeoMesh>& df2)
	{
		return dimensioned<diagTensor6>(t1) + df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const dimensioned<diagTensor6>& dt1
	                                                       , const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::New(tdf2, '(' + dt1.name() + '+' + df2.name() + ')'
			                                                                 , dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const diagTensor6& t1
	                                                       , const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf2)
	{
		return dimensioned<diagTensor6>(t1) + tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const DimensionedField<diagTensor6, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor6>& dt2)
	{
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(new DimensionedField<diagTensor6, GeoMesh>(
			IOobject('(' + df1.name() + '+' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const DimensionedField<diagTensor6, GeoMesh>& df1
	                                                       , const diagTensor6& t2)
	{
		return df1 + dimensioned<diagTensor6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor6>& dt2)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + dt2.name() + ')'
			                                                                 , df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf1
	                                                       , const diagTensor6& t2)
	{
		return tdf1 + dimensioned<diagTensor6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const dimensioned<diagTensor6>& dt1
	                                                       , const DimensionedField<diagTensor6, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(new DimensionedField<diagTensor6, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const diagTensor6& t1
	                                                       , const DimensionedField<diagTensor6, GeoMesh>& df2)
	{
		return dimensioned<diagTensor6>(t1) - df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const dimensioned<diagTensor6>& dt1
	                                                       , const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::New(tdf2, '(' + dt1.name() + '-' + df2.name() + ')'
			                                                                 , dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const diagTensor6& t1
	                                                       , const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf2)
	{
		return dimensioned<diagTensor6>(t1) - tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const DimensionedField<diagTensor6, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor6>& dt2)
	{
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(new DimensionedField<diagTensor6, GeoMesh>(
			IOobject('(' + df1.name() + '-' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const DimensionedField<diagTensor6, GeoMesh>& df1
	                                                       , const diagTensor6& t2)
	{
		return df1 - dimensioned<diagTensor6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor6>& dt2)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::New(tdf1, '(' + df1.name() + '-' + dt2.name() + ')'
			                                                                 , df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf1
	                                                       , const diagTensor6& t2)
	{
		return tdf1 - dimensioned<diagTensor6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const DimensionedField<sphericalTensor6, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor6, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(new DimensionedField<diagTensor6, GeoMesh>(
			IOobject('(' + df1.name() + '+' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const DimensionedField<sphericalTensor6, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::New(tdf2, '(' + df1.name() + '+' + df2.name() + ')'
			                                                                 , df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor6, GeoMesh>& df2)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, sphericalTensor6, GeoMesh>::New(
				tdf1, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor6, sphericalTensor6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor6, sphericalTensor6, sphericalTensor6, diagTensor6, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor6, sphericalTensor6, sphericalTensor6, diagTensor6, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const DimensionedField<sphericalTensor6, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor6, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(new DimensionedField<diagTensor6, GeoMesh>(
			IOobject('(' + df1.name() + '-' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const DimensionedField<sphericalTensor6, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::New(tdf2, '(' + df1.name() + '-' + df2.name() + ')'
			                                                                 , df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor6, GeoMesh>& df2)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, sphericalTensor6, GeoMesh>::New(
				tdf1, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor6, sphericalTensor6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor6, sphericalTensor6, sphericalTensor6, diagTensor6, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor6, sphericalTensor6, sphericalTensor6, diagTensor6, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const dimensioned<sphericalTensor6>& dt1
	                                                       , const DimensionedField<diagTensor6, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(new DimensionedField<diagTensor6, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const sphericalTensor6& t1
	                                                       , const DimensionedField<diagTensor6, GeoMesh>& df2)
	{
		return dimensioned<sphericalTensor6>(t1) + df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const dimensioned<sphericalTensor6>& dt1
	                                                       , const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::New(tdf2, '(' + dt1.name() + '+' + df2.name() + ')'
			                                                                 , dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const sphericalTensor6& t1
	                                                       , const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf2)
	{
		return dimensioned<sphericalTensor6>(t1) + tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const DimensionedField<sphericalTensor6, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor6>& dt2)
	{
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(new DimensionedField<diagTensor6, GeoMesh>(
			IOobject('(' + df1.name() + '+' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const DimensionedField<sphericalTensor6, GeoMesh>& df1
	                                                       , const diagTensor6& t2)
	{
		return df1 + dimensioned<diagTensor6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor6>& dt2)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, sphericalTensor6, GeoMesh>::New(
				tdf1, '(' + df1.name() + '+' + dt2.name() + ')', df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor6, sphericalTensor6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf1
	                                                       , const diagTensor6& t2)
	{
		return tdf1 + dimensioned<diagTensor6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const dimensioned<sphericalTensor6>& dt1
	                                                       , const DimensionedField<diagTensor6, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(new DimensionedField<diagTensor6, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const sphericalTensor6& t1
	                                                       , const DimensionedField<diagTensor6, GeoMesh>& df2)
	{
		return dimensioned<sphericalTensor6>(t1) - df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const dimensioned<sphericalTensor6>& dt1
	                                                       , const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::New(tdf2, '(' + dt1.name() + '-' + df2.name() + ')'
			                                                                 , dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const sphericalTensor6& t1
	                                                       , const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf2)
	{
		return dimensioned<sphericalTensor6>(t1) - tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const DimensionedField<sphericalTensor6, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor6>& dt2)
	{
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(new DimensionedField<diagTensor6, GeoMesh>(
			IOobject('(' + df1.name() + '-' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const DimensionedField<sphericalTensor6, GeoMesh>& df1
	                                                       , const diagTensor6& t2)
	{
		return df1 - dimensioned<diagTensor6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor6>& dt2)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, sphericalTensor6, GeoMesh>::New(
				tdf1, '(' + df1.name() + '-' + dt2.name() + ')', df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor6, sphericalTensor6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf1
	                                                       , const diagTensor6& t2)
	{
		return tdf1 - dimensioned<diagTensor6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const DimensionedField<diagTensor6, GeoMesh>& df1
	                                                       , const DimensionedField<sphericalTensor6, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(new DimensionedField<diagTensor6, GeoMesh>(
			IOobject('(' + df1.name() + '+' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const DimensionedField<diagTensor6, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, sphericalTensor6, GeoMesh>::New(
				tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor6, sphericalTensor6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf1
	                                                       , const DimensionedField<sphericalTensor6, GeoMesh>& df2)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + df2.name() + ')'
			                                                                 , df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor6, diagTensor6, diagTensor6, sphericalTensor6, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor6, diagTensor6, diagTensor6, sphericalTensor6, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const DimensionedField<diagTensor6, GeoMesh>& df1
	                                                       , const DimensionedField<sphericalTensor6, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(new DimensionedField<diagTensor6, GeoMesh>(
			IOobject('(' + df1.name() + '-' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const DimensionedField<diagTensor6, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, sphericalTensor6, GeoMesh>::New(
				tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor6, sphericalTensor6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf1
	                                                       , const DimensionedField<sphericalTensor6, GeoMesh>& df2)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::New(tdf1, '(' + df1.name() + '-' + df2.name() + ')'
			                                                                 , df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor6, diagTensor6, diagTensor6, sphericalTensor6, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor6, diagTensor6, diagTensor6, sphericalTensor6, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const dimensioned<diagTensor6>& dt1
	                                                       , const DimensionedField<sphericalTensor6, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(new DimensionedField<diagTensor6, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const diagTensor6& t1
	                                                       , const DimensionedField<sphericalTensor6, GeoMesh>& df2)
	{
		return dimensioned<diagTensor6>(t1) + df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const dimensioned<diagTensor6>& dt1
	                                                       , const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, sphericalTensor6, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '+' + df2.name() + ')', dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor6, sphericalTensor6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const diagTensor6& t1
	                                                       , const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf2)
	{
		return dimensioned<diagTensor6>(t1) + tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const DimensionedField<diagTensor6, GeoMesh>& df1
	                                                       , const dimensioned<sphericalTensor6>& dt2)
	{
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(new DimensionedField<diagTensor6, GeoMesh>(
			IOobject('(' + df1.name() + '+' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const DimensionedField<diagTensor6, GeoMesh>& df1
	                                                       , const sphericalTensor6& t2)
	{
		return df1 + dimensioned<sphericalTensor6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf1
	                                                       , const dimensioned<sphericalTensor6>& dt2)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + dt2.name() + ')'
			                                                                 , df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf1
	                                                       , const sphericalTensor6& t2)
	{
		return tdf1 + dimensioned<sphericalTensor6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const dimensioned<diagTensor6>& dt1
	                                                       , const DimensionedField<sphericalTensor6, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(new DimensionedField<diagTensor6, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const diagTensor6& t1
	                                                       , const DimensionedField<sphericalTensor6, GeoMesh>& df2)
	{
		return dimensioned<diagTensor6>(t1) - df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const dimensioned<diagTensor6>& dt1
	                                                       , const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor6, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, sphericalTensor6, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '+' + df2.name() + ')', dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor6, sphericalTensor6, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const diagTensor6& t1
	                                                       , const tmp<DimensionedField<sphericalTensor6, GeoMesh>>& tdf2)
	{
		return dimensioned<diagTensor6>(t1) - tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const DimensionedField<diagTensor6, GeoMesh>& df1
	                                                       , const dimensioned<sphericalTensor6>& dt2)
	{
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(new DimensionedField<diagTensor6, GeoMesh>(
			IOobject('(' + df1.name() + '+' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const DimensionedField<diagTensor6, GeoMesh>& df1
	                                                       , const sphericalTensor6& t2)
	{
		return df1 - dimensioned<sphericalTensor6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf1
	                                                       , const dimensioned<sphericalTensor6>& dt2)
	{
		const DimensionedField<diagTensor6, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor6, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + dt2.name() + ')'
			                                                                 , df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor6, diagTensor6, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor6, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor6, GeoMesh>>& tdf1
	                                                       , const sphericalTensor6& t2)
	{
		return tdf1 - dimensioned<sphericalTensor6>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> inv(const DimensionedField<diagTensor8, GeoMesh>& df1)
	{
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(new DimensionedField<diagTensor8, GeoMesh>(
			IOobject("inv" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), inv(df1.dimensions())));
		inv(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> inv(const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf1)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::New(tdf1, "inv" "(" + df1.name() + ')'
			                                                                 , inv(df1.dimensions())));
		inv(tRes().field(), df1.field());
		reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> diag(const DimensionedField<diagTensor8, GeoMesh>& df1)
	{
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(new DimensionedField<diagTensor8, GeoMesh>(
			IOobject("diag" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh(), diag(df1.dimensions())));
		diag(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> diag(const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf1)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::New(tdf1, "diag" "(" + df1.name() + ')'
			                                                                 , diag(df1.dimensions())));
		diag(tRes().field(), df1.field());
		reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> contractLinear(const DimensionedField<diagTensor8, GeoMesh>& df1)
	{
		tmp<DimensionedField<vector8, GeoMesh>> tRes(new DimensionedField<vector8, GeoMesh>(
			IOobject("contractLinear" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, contractLinear(df1.dimensions())));
		contractLinear(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> contractLinear(const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf1)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector8, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector8, diagTensor8, GeoMesh>::New(tdf1, "contractLinear" "(" + df1.name() + ')'
			                                                             , contractLinear(df1.dimensions())));
		contractLinear(tRes().field(), df1.field());
		reuseTmpDimensionedField<vector8, diagTensor8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> contractScalar(const DimensionedField<diagTensor8, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(new DimensionedField<scalar, GeoMesh>(
			IOobject("contractScalar" "(" + df1.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, contractLinear(df1.dimensions())));
		contractScalar(tRes().field(), df1.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> contractScalar(const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf1)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, diagTensor8, GeoMesh>::New(tdf1, "contractScalar" "(" + df1.name() + ')'
			                                                            , contractLinear(df1.dimensions())));
		contractScalar(tRes().field(), df1.field());
		reuseTmpDimensionedField<scalar, diagTensor8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor8, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(new DimensionedField<diagTensor8, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::New(tdf2, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                 , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor8, GeoMesh>& df2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + df2.name() + ')'
			                                                            , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor8, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor8, scalar, scalar, diagTensor8, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor8, scalar, scalar, diagTensor8, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const dimensioned<scalar>& dt1
	                                                       , const DimensionedField<diagTensor8, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(new DimensionedField<diagTensor8, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const scalar& t1
	                                                       , const DimensionedField<diagTensor8, GeoMesh>& df2)
	{
		return dimensioned<scalar>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const dimensioned<scalar>& dt1
	                                                       , const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::New(tdf2, '(' + dt1.name() + '|' + df2.name() + ')'
			                                                                 , dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const scalar& t1
	                                                       , const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf2)
	{
		return dimensioned<scalar>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor8>& dt2)
	{
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(new DimensionedField<diagTensor8, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1
	                                                       , const diagTensor8& t2)
	{
		return df1 / dimensioned<diagTensor8>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor8>& dt2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + dt2.name() + ')'
			                                                            , df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor8, scalar, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1
	                                                       , const diagTensor8& t2)
	{
		return tdf1 / dimensioned<diagTensor8>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator /(const DimensionedField<vector8, GeoMesh>& df1
	                                                   , const DimensionedField<diagTensor8, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector8, GeoMesh>> tRes(new DimensionedField<vector8, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator /(const DimensionedField<vector8, GeoMesh>& df1
	                                                   , const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector8, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector8, diagTensor8, GeoMesh>::New(tdf2, '(' + df1.name() + '|' + df2.name() + ')'
			                                                             , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<vector8, diagTensor8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator /(const tmp<DimensionedField<vector8, GeoMesh>>& tdf1
	                                                   , const DimensionedField<diagTensor8, GeoMesh>& df2)
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
	                                                   , const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<vector8, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector8, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<vector8, vector8, vector8, diagTensor8, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<vector8, vector8, vector8, diagTensor8, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator /(const dimensioned<vector8>& dt1
	                                                   , const DimensionedField<diagTensor8, GeoMesh>& df2)
	{
		tmp<DimensionedField<vector8, GeoMesh>> tRes(new DimensionedField<vector8, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator /(const vector8& t1
	                                                   , const DimensionedField<diagTensor8, GeoMesh>& df2)
	{
		return dimensioned<vector8>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator /(const dimensioned<vector8>& dt1
	                                                   , const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<vector8, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector8, diagTensor8, GeoMesh>::New(tdf2, '(' + dt1.name() + '|' + df2.name() + ')'
			                                                             , dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<vector8, diagTensor8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator /(const vector8& t1
	                                                   , const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf2)
	{
		return dimensioned<vector8>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator /(const DimensionedField<vector8, GeoMesh>& df1
	                                                   , const dimensioned<diagTensor8>& dt2)
	{
		tmp<DimensionedField<vector8, GeoMesh>> tRes(new DimensionedField<vector8, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator /(const DimensionedField<vector8, GeoMesh>& df1
	                                                   , const diagTensor8& t2)
	{
		return df1 / dimensioned<diagTensor8>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<vector8, GeoMesh>> operator /(const tmp<DimensionedField<vector8, GeoMesh>>& tdf1
	                                                   , const dimensioned<diagTensor8>& dt2)
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
	                                                   , const diagTensor8& t2)
	{
		return tdf1 / dimensioned<diagTensor8>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const DimensionedField<diagTensor8, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor8, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(new DimensionedField<diagTensor8, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const DimensionedField<diagTensor8, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::New(tdf2, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                 , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor8, GeoMesh>& df2)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                 , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor8, diagTensor8, diagTensor8, diagTensor8, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor8, diagTensor8, diagTensor8, diagTensor8, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const dimensioned<diagTensor8>& dt1
	                                                       , const DimensionedField<diagTensor8, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(new DimensionedField<diagTensor8, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const diagTensor8& t1
	                                                       , const DimensionedField<diagTensor8, GeoMesh>& df2)
	{
		return dimensioned<diagTensor8>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const dimensioned<diagTensor8>& dt1
	                                                       , const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::New(tdf2, '(' + dt1.name() + '|' + df2.name() + ')'
			                                                                 , dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const diagTensor8& t1
	                                                       , const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf2)
	{
		return dimensioned<diagTensor8>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const DimensionedField<diagTensor8, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor8>& dt2)
	{
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(new DimensionedField<diagTensor8, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const DimensionedField<diagTensor8, GeoMesh>& df1
	                                                       , const diagTensor8& t2)
	{
		return df1 / dimensioned<diagTensor8>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor8>& dt2)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + dt2.name() + ')'
			                                                                 , df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf1
	                                                       , const diagTensor8& t2)
	{
		return tdf1 / dimensioned<diagTensor8>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const DimensionedField<sphericalTensor8, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor8, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(new DimensionedField<diagTensor8, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const DimensionedField<sphericalTensor8, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::New(tdf2, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                 , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor8, GeoMesh>& df2)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, sphericalTensor8, GeoMesh>::New(
				tdf1, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor8, sphericalTensor8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor8, sphericalTensor8, sphericalTensor8, diagTensor8, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor8, sphericalTensor8, sphericalTensor8, diagTensor8, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const dimensioned<sphericalTensor8>& dt1
	                                                       , const DimensionedField<diagTensor8, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(new DimensionedField<diagTensor8, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const sphericalTensor8& t1
	                                                       , const DimensionedField<diagTensor8, GeoMesh>& df2)
	{
		return dimensioned<sphericalTensor8>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const dimensioned<sphericalTensor8>& dt1
	                                                       , const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::New(tdf2, '(' + dt1.name() + '|' + df2.name() + ')'
			                                                                 , dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const sphericalTensor8& t1
	                                                       , const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf2)
	{
		return dimensioned<sphericalTensor8>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const DimensionedField<sphericalTensor8, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor8>& dt2)
	{
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(new DimensionedField<diagTensor8, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const DimensionedField<sphericalTensor8, GeoMesh>& df1
	                                                       , const diagTensor8& t2)
	{
		return df1 / dimensioned<diagTensor8>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor8>& dt2)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, sphericalTensor8, GeoMesh>::New(
				tdf1, '(' + df1.name() + '|' + dt2.name() + ')', df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor8, sphericalTensor8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf1
	                                                       , const diagTensor8& t2)
	{
		return tdf1 / dimensioned<diagTensor8>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const DimensionedField<diagTensor8, GeoMesh>& df1
	                                                       , const DimensionedField<sphericalTensor8, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(new DimensionedField<diagTensor8, GeoMesh>(
			IOobject('(' + df1.name() + '|' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const DimensionedField<diagTensor8, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, sphericalTensor8, GeoMesh>::New(
				tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor8, sphericalTensor8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf1
	                                                       , const DimensionedField<sphericalTensor8, GeoMesh>& df2)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + df2.name() + ')'
			                                                                 , df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor8, diagTensor8, diagTensor8, sphericalTensor8, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor8, diagTensor8, diagTensor8, sphericalTensor8, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const dimensioned<diagTensor8>& dt1
	                                                       , const DimensionedField<sphericalTensor8, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(new DimensionedField<diagTensor8, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const diagTensor8& t1
	                                                       , const DimensionedField<sphericalTensor8, GeoMesh>& df2)
	{
		return dimensioned<diagTensor8>(t1) / df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const dimensioned<diagTensor8>& dt1
	                                                       , const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, sphericalTensor8, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '|' + df2.name() + ')', dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor8, sphericalTensor8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const diagTensor8& t1
	                                                       , const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf2)
	{
		return dimensioned<diagTensor8>(t1) / tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const DimensionedField<diagTensor8, GeoMesh>& df1
	                                                       , const dimensioned<sphericalTensor8>& dt2)
	{
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(new DimensionedField<diagTensor8, GeoMesh>(
			IOobject('(' + df1.name() + '|' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const DimensionedField<diagTensor8, GeoMesh>& df1
	                                                       , const sphericalTensor8& t2)
	{
		return df1 / dimensioned<sphericalTensor8>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf1
	                                                       , const dimensioned<sphericalTensor8>& dt2)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + dt2.name() + ')'
			                                                                 , df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator /(const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf1
	                                                       , const sphericalTensor8& t2)
	{
		return tdf1 / dimensioned<sphericalTensor8>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const DimensionedField<diagTensor8, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor8, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(new DimensionedField<diagTensor8, GeoMesh>(
			IOobject('(' + df1.name() + '+' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const DimensionedField<diagTensor8, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::New(tdf2, '(' + df1.name() + '+' + df2.name() + ')'
			                                                                 , df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor8, GeoMesh>& df2)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + df2.name() + ')'
			                                                                 , df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor8, diagTensor8, diagTensor8, diagTensor8, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor8, diagTensor8, diagTensor8, diagTensor8, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const DimensionedField<diagTensor8, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor8, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(new DimensionedField<diagTensor8, GeoMesh>(
			IOobject('(' + df1.name() + '-' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const DimensionedField<diagTensor8, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::New(tdf2, '(' + df1.name() + '-' + df2.name() + ')'
			                                                                 , df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor8, GeoMesh>& df2)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::New(tdf1, '(' + df1.name() + '-' + df2.name() + ')'
			                                                                 , df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor8, diagTensor8, diagTensor8, diagTensor8, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor8, diagTensor8, diagTensor8, diagTensor8, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const dimensioned<diagTensor8>& dt1
	                                                       , const DimensionedField<diagTensor8, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(new DimensionedField<diagTensor8, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const diagTensor8& t1
	                                                       , const DimensionedField<diagTensor8, GeoMesh>& df2)
	{
		return dimensioned<diagTensor8>(t1) + df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const dimensioned<diagTensor8>& dt1
	                                                       , const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::New(tdf2, '(' + dt1.name() + '+' + df2.name() + ')'
			                                                                 , dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const diagTensor8& t1
	                                                       , const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf2)
	{
		return dimensioned<diagTensor8>(t1) + tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const DimensionedField<diagTensor8, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor8>& dt2)
	{
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(new DimensionedField<diagTensor8, GeoMesh>(
			IOobject('(' + df1.name() + '+' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const DimensionedField<diagTensor8, GeoMesh>& df1
	                                                       , const diagTensor8& t2)
	{
		return df1 + dimensioned<diagTensor8>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor8>& dt2)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + dt2.name() + ')'
			                                                                 , df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf1
	                                                       , const diagTensor8& t2)
	{
		return tdf1 + dimensioned<diagTensor8>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const dimensioned<diagTensor8>& dt1
	                                                       , const DimensionedField<diagTensor8, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(new DimensionedField<diagTensor8, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const diagTensor8& t1
	                                                       , const DimensionedField<diagTensor8, GeoMesh>& df2)
	{
		return dimensioned<diagTensor8>(t1) - df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const dimensioned<diagTensor8>& dt1
	                                                       , const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::New(tdf2, '(' + dt1.name() + '-' + df2.name() + ')'
			                                                                 , dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const diagTensor8& t1
	                                                       , const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf2)
	{
		return dimensioned<diagTensor8>(t1) - tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const DimensionedField<diagTensor8, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor8>& dt2)
	{
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(new DimensionedField<diagTensor8, GeoMesh>(
			IOobject('(' + df1.name() + '-' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const DimensionedField<diagTensor8, GeoMesh>& df1
	                                                       , const diagTensor8& t2)
	{
		return df1 - dimensioned<diagTensor8>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor8>& dt2)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::New(tdf1, '(' + df1.name() + '-' + dt2.name() + ')'
			                                                                 , df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf1
	                                                       , const diagTensor8& t2)
	{
		return tdf1 - dimensioned<diagTensor8>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const DimensionedField<sphericalTensor8, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor8, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(new DimensionedField<diagTensor8, GeoMesh>(
			IOobject('(' + df1.name() + '+' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const DimensionedField<sphericalTensor8, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::New(tdf2, '(' + df1.name() + '+' + df2.name() + ')'
			                                                                 , df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor8, GeoMesh>& df2)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, sphericalTensor8, GeoMesh>::New(
				tdf1, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor8, sphericalTensor8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor8, sphericalTensor8, sphericalTensor8, diagTensor8, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor8, sphericalTensor8, sphericalTensor8, diagTensor8, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const DimensionedField<sphericalTensor8, GeoMesh>& df1
	                                                       , const DimensionedField<diagTensor8, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(new DimensionedField<diagTensor8, GeoMesh>(
			IOobject('(' + df1.name() + '-' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const DimensionedField<sphericalTensor8, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::New(tdf2, '(' + df1.name() + '-' + df2.name() + ')'
			                                                                 , df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf1
	                                                       , const DimensionedField<diagTensor8, GeoMesh>& df2)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, sphericalTensor8, GeoMesh>::New(
				tdf1, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor8, sphericalTensor8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df1 = tdf1();
		const DimensionedField<diagTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor8, sphericalTensor8, sphericalTensor8, diagTensor8, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor8, sphericalTensor8, sphericalTensor8, diagTensor8, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const dimensioned<sphericalTensor8>& dt1
	                                                       , const DimensionedField<diagTensor8, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(new DimensionedField<diagTensor8, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const sphericalTensor8& t1
	                                                       , const DimensionedField<diagTensor8, GeoMesh>& df2)
	{
		return dimensioned<sphericalTensor8>(t1) + df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const dimensioned<sphericalTensor8>& dt1
	                                                       , const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::New(tdf2, '(' + dt1.name() + '+' + df2.name() + ')'
			                                                                 , dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const sphericalTensor8& t1
	                                                       , const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf2)
	{
		return dimensioned<sphericalTensor8>(t1) + tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const DimensionedField<sphericalTensor8, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor8>& dt2)
	{
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(new DimensionedField<diagTensor8, GeoMesh>(
			IOobject('(' + df1.name() + '+' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const DimensionedField<sphericalTensor8, GeoMesh>& df1
	                                                       , const diagTensor8& t2)
	{
		return df1 + dimensioned<diagTensor8>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor8>& dt2)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, sphericalTensor8, GeoMesh>::New(
				tdf1, '(' + df1.name() + '+' + dt2.name() + ')', df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor8, sphericalTensor8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf1
	                                                       , const diagTensor8& t2)
	{
		return tdf1 + dimensioned<diagTensor8>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const dimensioned<sphericalTensor8>& dt1
	                                                       , const DimensionedField<diagTensor8, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(new DimensionedField<diagTensor8, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const sphericalTensor8& t1
	                                                       , const DimensionedField<diagTensor8, GeoMesh>& df2)
	{
		return dimensioned<sphericalTensor8>(t1) - df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const dimensioned<sphericalTensor8>& dt1
	                                                       , const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::New(tdf2, '(' + dt1.name() + '-' + df2.name() + ')'
			                                                                 , dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const sphericalTensor8& t1
	                                                       , const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf2)
	{
		return dimensioned<sphericalTensor8>(t1) - tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const DimensionedField<sphericalTensor8, GeoMesh>& df1
	                                                       , const dimensioned<diagTensor8>& dt2)
	{
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(new DimensionedField<diagTensor8, GeoMesh>(
			IOobject('(' + df1.name() + '-' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const DimensionedField<sphericalTensor8, GeoMesh>& df1
	                                                       , const diagTensor8& t2)
	{
		return df1 - dimensioned<diagTensor8>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf1
	                                                       , const dimensioned<diagTensor8>& dt2)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, sphericalTensor8, GeoMesh>::New(
				tdf1, '(' + df1.name() + '-' + dt2.name() + ')', df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor8, sphericalTensor8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf1
	                                                       , const diagTensor8& t2)
	{
		return tdf1 - dimensioned<diagTensor8>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const DimensionedField<diagTensor8, GeoMesh>& df1
	                                                       , const DimensionedField<sphericalTensor8, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(new DimensionedField<diagTensor8, GeoMesh>(
			IOobject('(' + df1.name() + '+' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const DimensionedField<diagTensor8, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, sphericalTensor8, GeoMesh>::New(
				tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor8, sphericalTensor8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf1
	                                                       , const DimensionedField<sphericalTensor8, GeoMesh>& df2)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + df2.name() + ')'
			                                                                 , df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor8, diagTensor8, diagTensor8, sphericalTensor8, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '+' + df2.name() + ')', df1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor8, diagTensor8, diagTensor8, sphericalTensor8, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const DimensionedField<diagTensor8, GeoMesh>& df1
	                                                       , const DimensionedField<sphericalTensor8, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(new DimensionedField<diagTensor8, GeoMesh>(
			IOobject('(' + df1.name() + '-' + df2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const DimensionedField<diagTensor8, GeoMesh>& df1
	                                                       , const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, sphericalTensor8, GeoMesh>::New(
				tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor8, sphericalTensor8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf1
	                                                       , const DimensionedField<sphericalTensor8, GeoMesh>& df2)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::New(tdf1, '(' + df1.name() + '-' + df2.name() + ')'
			                                                                 , df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf1
	                                                       , const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<diagTensor8, diagTensor8, diagTensor8, sphericalTensor8, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '-' + df2.name() + ')', df1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), df2.field());
		reuseTmpTmpDimensionedField<diagTensor8, diagTensor8, diagTensor8, sphericalTensor8, GeoMesh>::clear(tdf1, tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const dimensioned<diagTensor8>& dt1
	                                                       , const DimensionedField<sphericalTensor8, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(new DimensionedField<diagTensor8, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const diagTensor8& t1
	                                                       , const DimensionedField<sphericalTensor8, GeoMesh>& df2)
	{
		return dimensioned<diagTensor8>(t1) + df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const dimensioned<diagTensor8>& dt1
	                                                       , const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, sphericalTensor8, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '+' + df2.name() + ')', dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor8, sphericalTensor8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const diagTensor8& t1
	                                                       , const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf2)
	{
		return dimensioned<diagTensor8>(t1) + tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const DimensionedField<diagTensor8, GeoMesh>& df1
	                                                       , const dimensioned<sphericalTensor8>& dt2)
	{
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(new DimensionedField<diagTensor8, GeoMesh>(
			IOobject('(' + df1.name() + '+' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const DimensionedField<diagTensor8, GeoMesh>& df1
	                                                       , const sphericalTensor8& t2)
	{
		return df1 + dimensioned<sphericalTensor8>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf1
	                                                       , const dimensioned<sphericalTensor8>& dt2)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + dt2.name() + ')'
			                                                                 , df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator +(const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf1
	                                                       , const sphericalTensor8& t2)
	{
		return tdf1 + dimensioned<sphericalTensor8>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const dimensioned<diagTensor8>& dt1
	                                                       , const DimensionedField<sphericalTensor8, GeoMesh>& df2)
	{
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(new DimensionedField<diagTensor8, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + df2.name() + ')', df2.instance(), df2.db()), df2.mesh()
			, dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), df2.field());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const diagTensor8& t1
	                                                       , const DimensionedField<sphericalTensor8, GeoMesh>& df2)
	{
		return dimensioned<diagTensor8>(t1) - df2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const dimensioned<diagTensor8>& dt1
	                                                       , const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor8, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, sphericalTensor8, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '+' + df2.name() + ')', dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes().field(), dt1.value(), tdf2().field());
		reuseTmpDimensionedField<diagTensor8, sphericalTensor8, GeoMesh>::clear(tdf2);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const diagTensor8& t1
	                                                       , const tmp<DimensionedField<sphericalTensor8, GeoMesh>>& tdf2)
	{
		return dimensioned<diagTensor8>(t1) - tdf2;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const DimensionedField<diagTensor8, GeoMesh>& df1
	                                                       , const dimensioned<sphericalTensor8>& dt2)
	{
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(new DimensionedField<diagTensor8, GeoMesh>(
			IOobject('(' + df1.name() + '+' + dt2.name() + ')', df1.instance(), df1.db()), df1.mesh()
			, df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), df1.field(), dt2.value());
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const DimensionedField<diagTensor8, GeoMesh>& df1
	                                                       , const sphericalTensor8& t2)
	{
		return df1 - dimensioned<sphericalTensor8>(t2);
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf1
	                                                       , const dimensioned<sphericalTensor8>& dt2)
	{
		const DimensionedField<diagTensor8, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<diagTensor8, GeoMesh>> tRes(
			reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + dt2.name() + ')'
			                                                                 , df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes().field(), tdf1().field(), dt2.value());
		reuseTmpDimensionedField<diagTensor8, diagTensor8, GeoMesh>::clear(tdf1);
		return tRes;
	}

	template <class GeoMesh>
	tmp<DimensionedField<diagTensor8, GeoMesh>> operator -(const tmp<DimensionedField<diagTensor8, GeoMesh>>& tdf1
	                                                       , const sphericalTensor8& t2)
	{
		return tdf1 - dimensioned<sphericalTensor8>(t2);
	}

}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#undef DiagTensorN_FieldFunctions

#include <undefFieldFunctionsM.hxx>