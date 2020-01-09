#include <GeometricDiagTensorNFields.hxx>

#include <ExpandTensorNField.hxx>

#define TEMPLATE template<template<class> class PatchField, class GeoMesh>
#include <GeometricFieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define DiagTensorN_FieldFunctions(tensorType, diagTensorType, sphericalTensorType, vectorType, CmptType, args) \
                                                                                        \
UNARY_FUNCTION(diagTensorType, diagTensorType,inv,inv)                                  \
UNARY_FUNCTION(diagTensorType, diagTensorType,diag,diag)                                \
UNARY_FUNCTION(CmptType, diagTensorType,contractScalar,contractScalar)                  \
UNARY_FUNCTION(vectorType, diagTensorType,contractLinear,contractLinear)                \
                                                                                        \
BINARY_OPERATOR(diagTensorType, CmptType, diagTensorType, *,'*',multiply)               \
BINARY_TYPE_OPERATOR(diagTensorType, CmptType, diagTensorType, *,'*',multiply)          \
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

	template <template<class> class PatchField, class GeoMesh>
	void inv(GeometricField<diagTensor2, PatchField, GeoMesh>& res,
	         const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1)
	{
		tnbLib::inv(res.internalField(), gf1.internalField());
		tnbLib::inv(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> inv(const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject("inv" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			inv(gf1.dimensions())));
		tnbLib::inv(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> inv(
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf1, "inv" "(" + gf1.name() + ')', inv(gf1.dimensions())));
		tnbLib::inv(tRes(), gf1);
		reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void diag(GeometricField<diagTensor2, PatchField, GeoMesh>& res,
	          const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1)
	{
		tnbLib::diag(res.internalField(), gf1.internalField());
		tnbLib::diag(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> diag(const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject("diag" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			diag(gf1.dimensions())));
		tnbLib::diag(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> diag(
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf1, "diag" "(" + gf1.name() + ')', diag(gf1.dimensions())));
		tnbLib::diag(tRes(), gf1);
		reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void contractScalar(GeometricField<scalar, PatchField, GeoMesh>& res,
	                    const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1)
	{
		tnbLib::contractScalar(res.internalField(), gf1.internalField());
		tnbLib::contractScalar(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> contractScalar(
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("contractScalar" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), contractScalar(gf1.dimensions())));
		tnbLib::contractScalar(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> contractScalar(
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, diagTensor2, PatchField, GeoMesh>::New(
				tgf1, "contractScalar" "(" + gf1.name() + ')', contractScalar(gf1.dimensions())));
		tnbLib::contractScalar(tRes(), gf1);
		reuseTmpGeometricField<scalar, diagTensor2, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void contractLinear(GeometricField<vector2, PatchField, GeoMesh>& res,
	                    const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1)
	{
		tnbLib::contractLinear(res.internalField(), gf1.internalField());
		tnbLib::contractLinear(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> contractLinear(
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(new GeometricField<vector2, PatchField, GeoMesh>(
			IOobject("contractLinear" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), contractLinear(gf1.dimensions())));
		tnbLib::contractLinear(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> contractLinear(
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector2, diagTensor2, PatchField, GeoMesh>::New(
				tgf1, "contractLinear" "(" + gf1.name() + ')', contractLinear(gf1.dimensions())));
		tnbLib::contractLinear(tRes(), gf1);
		reuseTmpGeometricField<vector2, diagTensor2, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<diagTensor2, PatchField, GeoMesh>& res,
	              const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	              const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::multiply(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::multiply(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator *(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1, const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '*' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator *(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '*' + gf2.name() + ')', gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, scalar, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '*' + gf2.name() + ')', gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor2, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor2, scalar, scalar, diagTensor2, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '*' + gf2.name() + ')', gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor2, scalar, scalar, diagTensor2, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<diagTensor2, PatchField, GeoMesh>& res, const dimensioned<scalar>& dt1,
	              const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::multiply(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::multiply(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator *(const dimensioned<scalar>& dt1,
	                                                                 const GeometricField<diagTensor2, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '*' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator *(const scalar& t1,
	                                                                 const GeometricField<diagTensor2, PatchField, GeoMesh>
	                                                                 & gf2) { return dimensioned<scalar>(t1) * gf2; }

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator *(const dimensioned<scalar>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '*' + gf2.name() + ')', dt1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator *(const scalar& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor2, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<scalar>(t1) * tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<diagTensor2, PatchField, GeoMesh>& res,
	              const GeometricField<scalar, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor2>& dt2)
	{
		tnbLib::multiply(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::multiply(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator *(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor2>& dt2)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '*' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() * dt2.dimensions()));
		tnbLib::multiply(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator *(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1, const diagTensor2& t2)
	{
		return gf1 * dimensioned<diagTensor2>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor2>& dt2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, scalar, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '*' + dt2.name() + ')', gf1.dimensions() * dt2.dimensions()));
		tnbLib::multiply(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor2, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const diagTensor2& t2)
	{
		return tgf1 * dimensioned<diagTensor2>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor2, PatchField, GeoMesh>& res,
	            const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	            const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1, const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, scalar, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor2, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor2, scalar, scalar, diagTensor2, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor2, scalar, scalar, diagTensor2, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor2, PatchField, GeoMesh>& res, const dimensioned<scalar>& dt1,
	            const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
	                                                                 const GeometricField<diagTensor2, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(const scalar& t1,
	                                                                 const GeometricField<diagTensor2, PatchField, GeoMesh>
	                                                                 & gf2) { return dimensioned<scalar>(t1) / gf2; }

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '|' + gf2.name() + ')', dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(const scalar& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor2, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<scalar>(t1) / tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor2, PatchField, GeoMesh>& res,
	            const GeometricField<scalar, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor2>& dt2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor2>& dt2)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1, const diagTensor2& t2)
	{
		return gf1 / dimensioned<diagTensor2>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor2>& dt2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, scalar, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + dt2.name() + ')', gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor2, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const diagTensor2& t2)
	{
		return tgf1 / dimensioned<diagTensor2>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<vector2, PatchField, GeoMesh>& res, const GeometricField<vector2, PatchField, GeoMesh>& gf1,
	            const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator /(const GeometricField<vector2, PatchField, GeoMesh>& gf1,
	                                                             const GeometricField<diagTensor2, PatchField, GeoMesh>&
	                                                             gf2)
	{
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(new GeometricField<vector2, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator /(const GeometricField<vector2, PatchField, GeoMesh>& gf1,
	                                                             const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>
	                                                             >& tgf2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector2, diagTensor2, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector2, diagTensor2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<vector2, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<vector2, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '|' + gf2.name() + ')',
			                                                                   gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<vector2, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<vector2, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<vector2, vector2, vector2, diagTensor2, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<vector2, vector2, vector2, diagTensor2, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<vector2, PatchField, GeoMesh>& res, const dimensioned<vector2>& dt1,
	            const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator /(const dimensioned<vector2>& dt1,
	                                                             const GeometricField<diagTensor2, PatchField, GeoMesh>&
	                                                             gf2)
	{
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(new GeometricField<vector2, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator /(const vector2& t1,
	                                                             const GeometricField<diagTensor2, PatchField, GeoMesh>&
	                                                             gf2) { return dimensioned<vector2>(t1) / gf2; }

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator /(const dimensioned<vector2>& dt1,
	                                                             const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>
	                                                             >& tgf2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector2, diagTensor2, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '|' + gf2.name() + ')', dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		reuseTmpGeometricField<vector2, diagTensor2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator /(const vector2& t1,
	                                                             const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>
	                                                             >& tgf2) { return dimensioned<vector2>(t1) / tgf2; }

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<vector2, PatchField, GeoMesh>& res, const GeometricField<vector2, PatchField, GeoMesh>& gf1,
	            const dimensioned<diagTensor2>& dt2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator /(const GeometricField<vector2, PatchField, GeoMesh>& gf1,
	                                                             const dimensioned<diagTensor2>& dt2)
	{
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(new GeometricField<vector2, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator /(const GeometricField<vector2, PatchField, GeoMesh>& gf1,
	                                                             const diagTensor2& t2)
	{
		return gf1 / dimensioned<diagTensor2>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<vector2, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor2>& dt2)
	{
		const GeometricField<vector2, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '|' + dt2.name() + ')',
			                                                                   gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<vector2, PatchField, GeoMesh>>& tgf1, const diagTensor2& t2)
	{
		return tgf1 / dimensioned<diagTensor2>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor2, PatchField, GeoMesh>& res,
	            const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1,
	            const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1,
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor2, diagTensor2, diagTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor2, diagTensor2, diagTensor2, diagTensor2, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor2, PatchField, GeoMesh>& res, const dimensioned<diagTensor2>& dt1,
	            const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(const dimensioned<diagTensor2>& dt1,
	                                                                 const GeometricField<diagTensor2, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(const diagTensor2& t1,
	                                                                 const GeometricField<diagTensor2, PatchField, GeoMesh>
	                                                                 & gf2) { return dimensioned<diagTensor2>(t1) / gf2; }

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(const dimensioned<diagTensor2>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '|' + gf2.name() + ')', dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(const diagTensor2& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor2, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<diagTensor2>(t1) / tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor2, PatchField, GeoMesh>& res,
	            const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor2>& dt2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor2>& dt2)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1, const diagTensor2& t2)
	{
		return gf1 / dimensioned<diagTensor2>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor2>& dt2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + dt2.name() + ')', gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf1, const diagTensor2& t2)
	{
		return tgf1 / dimensioned<diagTensor2>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor2, PatchField, GeoMesh>& res,
	            const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf1,
	            const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf1,
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<sphericalTensor2, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, sphericalTensor2, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor2, sphericalTensor2, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<sphericalTensor2, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor2, sphericalTensor2, sphericalTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor2, sphericalTensor2, sphericalTensor2, diagTensor2, PatchField, GeoMesh>::
			clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor2, PatchField, GeoMesh>& res, const dimensioned<sphericalTensor2>& dt1,
	            const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(const dimensioned<sphericalTensor2>& dt1,
	                                                                 const GeometricField<diagTensor2, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(const sphericalTensor2& t1,
	                                                                 const GeometricField<diagTensor2, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		return dimensioned<sphericalTensor2>(t1) / gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(const dimensioned<sphericalTensor2>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '|' + gf2.name() + ')', dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(const sphericalTensor2& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor2, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<sphericalTensor2>(t1) / tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor2, PatchField, GeoMesh>& res,
	            const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor2>& dt2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor2>& dt2)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf1, const diagTensor2& t2)
	{
		return gf1 / dimensioned<diagTensor2>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<sphericalTensor2, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor2>& dt2)
	{
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, sphericalTensor2, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + dt2.name() + ')', gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor2, sphericalTensor2, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<sphericalTensor2, PatchField, GeoMesh>>& tgf1, const diagTensor2& t2)
	{
		return tgf1 / dimensioned<diagTensor2>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor2, PatchField, GeoMesh>& res,
	            const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1,
	            const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1,
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<sphericalTensor2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, sphericalTensor2, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor2, sphericalTensor2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf1,
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<sphericalTensor2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor2, diagTensor2, diagTensor2, sphericalTensor2, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor2, diagTensor2, diagTensor2, sphericalTensor2, PatchField, GeoMesh>::
			clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor2, PatchField, GeoMesh>& res, const dimensioned<diagTensor2>& dt1,
	            const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(const dimensioned<diagTensor2>& dt1,
	                                                                 const GeometricField<
		                                                                 sphericalTensor2, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(const diagTensor2& t1,
	                                                                 const GeometricField<
		                                                                 sphericalTensor2, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<diagTensor2>(t1) / gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(const dimensioned<diagTensor2>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 sphericalTensor2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, sphericalTensor2, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '|' + gf2.name() + ')', dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor2, sphericalTensor2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(const diagTensor2& t1,
	                                                                 const tmp<GeometricField<
		                                                                 sphericalTensor2, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<diagTensor2>(t1) / tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor2, PatchField, GeoMesh>& res,
	            const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1, const dimensioned<sphericalTensor2>& dt2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1, const dimensioned<sphericalTensor2>& dt2)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1, const sphericalTensor2& t2)
	{
		return gf1 / dimensioned<sphericalTensor2>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf1, const dimensioned<sphericalTensor2>& dt2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + dt2.name() + ')', gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf1, const sphericalTensor2& t2)
	{
		return tgf1 / dimensioned<sphericalTensor2>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor2, PatchField, GeoMesh>& res,
	         const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1,
	         const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1,
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor2, diagTensor2, diagTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor2, diagTensor2, diagTensor2, diagTensor2, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor2, PatchField, GeoMesh>& res,
	              const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1,
	              const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1,
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor2, diagTensor2, diagTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor2, diagTensor2, diagTensor2, diagTensor2, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor2, PatchField, GeoMesh>& res, const dimensioned<diagTensor2>& dt1,
	         const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::add(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(const dimensioned<diagTensor2>& dt1,
	                                                                 const GeometricField<diagTensor2, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(const diagTensor2& t1,
	                                                                 const GeometricField<diagTensor2, PatchField, GeoMesh>
	                                                                 & gf2) { return dimensioned<diagTensor2>(t1) + gf2; }

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(const dimensioned<diagTensor2>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '+' + gf2.name() + ')', dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(const diagTensor2& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor2, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<diagTensor2>(t1) + tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor2, PatchField, GeoMesh>& res,
	         const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor2>& dt2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor2>& dt2)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1, const diagTensor2& t2)
	{
		return gf1 + dimensioned<diagTensor2>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor2>& dt2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + dt2.name() + ')', gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf1, const diagTensor2& t2)
	{
		return tgf1 + dimensioned<diagTensor2>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor2, PatchField, GeoMesh>& res, const dimensioned<diagTensor2>& dt1,
	              const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(const dimensioned<diagTensor2>& dt1,
	                                                                 const GeometricField<diagTensor2, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(const diagTensor2& t1,
	                                                                 const GeometricField<diagTensor2, PatchField, GeoMesh>
	                                                                 & gf2) { return dimensioned<diagTensor2>(t1) - gf2; }

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(const dimensioned<diagTensor2>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '-' + gf2.name() + ')', dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(const diagTensor2& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor2, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<diagTensor2>(t1) - tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor2, PatchField, GeoMesh>& res,
	              const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor2>& dt2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor2>& dt2)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1, const diagTensor2& t2)
	{
		return gf1 - dimensioned<diagTensor2>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor2>& dt2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '-' + dt2.name() + ')', gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf1, const diagTensor2& t2)
	{
		return tgf1 - dimensioned<diagTensor2>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor2, PatchField, GeoMesh>& res,
	         const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf1,
	         const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf1,
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<sphericalTensor2, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, sphericalTensor2, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor2, sphericalTensor2, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<sphericalTensor2, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor2, sphericalTensor2, sphericalTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor2, sphericalTensor2, sphericalTensor2, diagTensor2, PatchField, GeoMesh>::
			clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor2, PatchField, GeoMesh>& res,
	              const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf1,
	              const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf1,
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<sphericalTensor2, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, sphericalTensor2, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor2, sphericalTensor2, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<sphericalTensor2, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor2, sphericalTensor2, sphericalTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor2, sphericalTensor2, sphericalTensor2, diagTensor2, PatchField, GeoMesh>::
			clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor2, PatchField, GeoMesh>& res, const dimensioned<sphericalTensor2>& dt1,
	         const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::add(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(const dimensioned<sphericalTensor2>& dt1,
	                                                                 const GeometricField<diagTensor2, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(const sphericalTensor2& t1,
	                                                                 const GeometricField<diagTensor2, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		return dimensioned<sphericalTensor2>(t1) + gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(const dimensioned<sphericalTensor2>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '+' + gf2.name() + ')', dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(const sphericalTensor2& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor2, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<sphericalTensor2>(t1) + tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor2, PatchField, GeoMesh>& res,
	         const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor2>& dt2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor2>& dt2)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf1, const diagTensor2& t2)
	{
		return gf1 + dimensioned<diagTensor2>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<sphericalTensor2, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor2>& dt2)
	{
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, sphericalTensor2, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + dt2.name() + ')', gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor2, sphericalTensor2, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<sphericalTensor2, PatchField, GeoMesh>>& tgf1, const diagTensor2& t2)
	{
		return tgf1 + dimensioned<diagTensor2>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor2, PatchField, GeoMesh>& res, const dimensioned<sphericalTensor2>& dt1,
	              const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(const dimensioned<sphericalTensor2>& dt1,
	                                                                 const GeometricField<diagTensor2, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(const sphericalTensor2& t1,
	                                                                 const GeometricField<diagTensor2, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		return dimensioned<sphericalTensor2>(t1) - gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(const dimensioned<sphericalTensor2>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '-' + gf2.name() + ')', dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(const sphericalTensor2& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor2, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<sphericalTensor2>(t1) - tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor2, PatchField, GeoMesh>& res,
	              const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor2>& dt2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor2>& dt2)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf1, const diagTensor2& t2)
	{
		return gf1 - dimensioned<diagTensor2>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<sphericalTensor2, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor2>& dt2)
	{
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, sphericalTensor2, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '-' + dt2.name() + ')', gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor2, sphericalTensor2, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<sphericalTensor2, PatchField, GeoMesh>>& tgf1, const diagTensor2& t2)
	{
		return tgf1 - dimensioned<diagTensor2>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor2, PatchField, GeoMesh>& res,
	         const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1,
	         const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1,
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<sphericalTensor2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, sphericalTensor2, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor2, sphericalTensor2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf1,
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<sphericalTensor2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor2, diagTensor2, diagTensor2, sphericalTensor2, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor2, diagTensor2, diagTensor2, sphericalTensor2, PatchField, GeoMesh>::
			clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor2, PatchField, GeoMesh>& res,
	              const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1,
	              const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1,
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<sphericalTensor2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, sphericalTensor2, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor2, sphericalTensor2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf1,
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<sphericalTensor2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor2, diagTensor2, diagTensor2, sphericalTensor2, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor2, diagTensor2, diagTensor2, sphericalTensor2, PatchField, GeoMesh>::
			clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor2, PatchField, GeoMesh>& res, const dimensioned<diagTensor2>& dt1,
	         const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::add(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(const dimensioned<diagTensor2>& dt1,
	                                                                 const GeometricField<
		                                                                 sphericalTensor2, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(const diagTensor2& t1,
	                                                                 const GeometricField<
		                                                                 sphericalTensor2, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<diagTensor2>(t1) + gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(const dimensioned<diagTensor2>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 sphericalTensor2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, sphericalTensor2, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '+' + gf2.name() + ')', dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor2, sphericalTensor2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(const diagTensor2& t1,
	                                                                 const tmp<GeometricField<
		                                                                 sphericalTensor2, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<diagTensor2>(t1) + tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor2, PatchField, GeoMesh>& res,
	         const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1, const dimensioned<sphericalTensor2>& dt2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1, const dimensioned<sphericalTensor2>& dt2)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1, const sphericalTensor2& t2)
	{
		return gf1 + dimensioned<sphericalTensor2>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf1, const dimensioned<sphericalTensor2>& dt2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + dt2.name() + ')', gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf1, const sphericalTensor2& t2)
	{
		return tgf1 + dimensioned<sphericalTensor2>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor2, PatchField, GeoMesh>& res, const dimensioned<diagTensor2>& dt1,
	              const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(const dimensioned<diagTensor2>& dt1,
	                                                                 const GeometricField<
		                                                                 sphericalTensor2, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(const diagTensor2& t1,
	                                                                 const GeometricField<
		                                                                 sphericalTensor2, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<diagTensor2>(t1) - gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(const dimensioned<diagTensor2>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 sphericalTensor2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, sphericalTensor2, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '+' + gf2.name() + ')', dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor2, sphericalTensor2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(const diagTensor2& t1,
	                                                                 const tmp<GeometricField<
		                                                                 sphericalTensor2, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<diagTensor2>(t1) - tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor2, PatchField, GeoMesh>& res,
	              const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1, const dimensioned<sphericalTensor2>& dt2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1, const dimensioned<sphericalTensor2>& dt2)
	{
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor2, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1, const sphericalTensor2& t2)
	{
		return gf1 - dimensioned<sphericalTensor2>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf1, const dimensioned<sphericalTensor2>& dt2)
	{
		const GeometricField<diagTensor2, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + dt2.name() + ')', gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor2, diagTensor2, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor2, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor2, PatchField, GeoMesh>>& tgf1, const sphericalTensor2& t2)
	{
		return tgf1 - dimensioned<sphericalTensor2>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void inv(GeometricField<diagTensor3, PatchField, GeoMesh>& res,
	         const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1)
	{
		tnbLib::inv(res.internalField(), gf1.internalField());
		tnbLib::inv(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> inv(const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject("inv" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			inv(gf1.dimensions())));
		tnbLib::inv(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> inv(
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf1, "inv" "(" + gf1.name() + ')', inv(gf1.dimensions())));
		tnbLib::inv(tRes(), gf1);
		reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void diag(GeometricField<diagTensor3, PatchField, GeoMesh>& res,
	          const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1)
	{
		tnbLib::diag(res.internalField(), gf1.internalField());
		tnbLib::diag(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> diag(const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject("diag" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			diag(gf1.dimensions())));
		tnbLib::diag(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> diag(
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf1, "diag" "(" + gf1.name() + ')', diag(gf1.dimensions())));
		tnbLib::diag(tRes(), gf1);
		reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void contractScalar(GeometricField<scalar, PatchField, GeoMesh>& res,
	                    const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1)
	{
		tnbLib::contractScalar(res.internalField(), gf1.internalField());
		tnbLib::contractScalar(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> contractScalar(
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("contractScalar" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), contractScalar(gf1.dimensions())));
		tnbLib::contractScalar(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> contractScalar(
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, diagTensor3, PatchField, GeoMesh>::New(
				tgf1, "contractScalar" "(" + gf1.name() + ')', contractScalar(gf1.dimensions())));
		tnbLib::contractScalar(tRes(), gf1);
		reuseTmpGeometricField<scalar, diagTensor3, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void contractLinear(GeometricField<vector3, PatchField, GeoMesh>& res,
	                    const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1)
	{
		tnbLib::contractLinear(res.internalField(), gf1.internalField());
		tnbLib::contractLinear(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> contractLinear(
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(new GeometricField<vector3, PatchField, GeoMesh>(
			IOobject("contractLinear" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), contractLinear(gf1.dimensions())));
		tnbLib::contractLinear(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> contractLinear(
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector3, diagTensor3, PatchField, GeoMesh>::New(
				tgf1, "contractLinear" "(" + gf1.name() + ')', contractLinear(gf1.dimensions())));
		tnbLib::contractLinear(tRes(), gf1);
		reuseTmpGeometricField<vector3, diagTensor3, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<diagTensor3, PatchField, GeoMesh>& res,
	              const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	              const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		tnbLib::multiply(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::multiply(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator *(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1, const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '*' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator *(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '*' + gf2.name() + ')', gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, scalar, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '*' + gf2.name() + ')', gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor3, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor3, scalar, scalar, diagTensor3, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '*' + gf2.name() + ')', gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor3, scalar, scalar, diagTensor3, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<diagTensor3, PatchField, GeoMesh>& res, const dimensioned<scalar>& dt1,
	              const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		tnbLib::multiply(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::multiply(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator *(const dimensioned<scalar>& dt1,
	                                                                 const GeometricField<diagTensor3, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '*' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator *(const scalar& t1,
	                                                                 const GeometricField<diagTensor3, PatchField, GeoMesh>
	                                                                 & gf2) { return dimensioned<scalar>(t1) * gf2; }

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator *(const dimensioned<scalar>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '*' + gf2.name() + ')', dt1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator *(const scalar& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor3, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<scalar>(t1) * tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<diagTensor3, PatchField, GeoMesh>& res,
	              const GeometricField<scalar, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor3>& dt2)
	{
		tnbLib::multiply(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::multiply(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator *(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor3>& dt2)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '*' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() * dt2.dimensions()));
		tnbLib::multiply(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator *(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1, const diagTensor3& t2)
	{
		return gf1 * dimensioned<diagTensor3>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor3>& dt2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, scalar, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '*' + dt2.name() + ')', gf1.dimensions() * dt2.dimensions()));
		tnbLib::multiply(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor3, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const diagTensor3& t2)
	{
		return tgf1 * dimensioned<diagTensor3>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor3, PatchField, GeoMesh>& res,
	            const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	            const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1, const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, scalar, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor3, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor3, scalar, scalar, diagTensor3, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor3, scalar, scalar, diagTensor3, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor3, PatchField, GeoMesh>& res, const dimensioned<scalar>& dt1,
	            const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
	                                                                 const GeometricField<diagTensor3, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(const scalar& t1,
	                                                                 const GeometricField<diagTensor3, PatchField, GeoMesh>
	                                                                 & gf2) { return dimensioned<scalar>(t1) / gf2; }

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '|' + gf2.name() + ')', dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(const scalar& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor3, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<scalar>(t1) / tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor3, PatchField, GeoMesh>& res,
	            const GeometricField<scalar, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor3>& dt2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor3>& dt2)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1, const diagTensor3& t2)
	{
		return gf1 / dimensioned<diagTensor3>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor3>& dt2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, scalar, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + dt2.name() + ')', gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor3, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const diagTensor3& t2)
	{
		return tgf1 / dimensioned<diagTensor3>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<vector3, PatchField, GeoMesh>& res, const GeometricField<vector3, PatchField, GeoMesh>& gf1,
	            const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator /(const GeometricField<vector3, PatchField, GeoMesh>& gf1,
	                                                             const GeometricField<diagTensor3, PatchField, GeoMesh>&
	                                                             gf2)
	{
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(new GeometricField<vector3, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator /(const GeometricField<vector3, PatchField, GeoMesh>& gf1,
	                                                             const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>
	                                                             >& tgf2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector3, diagTensor3, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector3, diagTensor3, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<vector3, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<vector3, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '|' + gf2.name() + ')',
			                                                                   gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<vector3, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<vector3, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<vector3, vector3, vector3, diagTensor3, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<vector3, vector3, vector3, diagTensor3, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<vector3, PatchField, GeoMesh>& res, const dimensioned<vector3>& dt1,
	            const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator /(const dimensioned<vector3>& dt1,
	                                                             const GeometricField<diagTensor3, PatchField, GeoMesh>&
	                                                             gf2)
	{
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(new GeometricField<vector3, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator /(const vector3& t1,
	                                                             const GeometricField<diagTensor3, PatchField, GeoMesh>&
	                                                             gf2) { return dimensioned<vector3>(t1) / gf2; }

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator /(const dimensioned<vector3>& dt1,
	                                                             const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>
	                                                             >& tgf2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector3, diagTensor3, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '|' + gf2.name() + ')', dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		reuseTmpGeometricField<vector3, diagTensor3, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator /(const vector3& t1,
	                                                             const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>
	                                                             >& tgf2) { return dimensioned<vector3>(t1) / tgf2; }

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<vector3, PatchField, GeoMesh>& res, const GeometricField<vector3, PatchField, GeoMesh>& gf1,
	            const dimensioned<diagTensor3>& dt2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator /(const GeometricField<vector3, PatchField, GeoMesh>& gf1,
	                                                             const dimensioned<diagTensor3>& dt2)
	{
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(new GeometricField<vector3, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator /(const GeometricField<vector3, PatchField, GeoMesh>& gf1,
	                                                             const diagTensor3& t2)
	{
		return gf1 / dimensioned<diagTensor3>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<vector3, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor3>& dt2)
	{
		const GeometricField<vector3, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '|' + dt2.name() + ')',
			                                                                   gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<vector3, PatchField, GeoMesh>>& tgf1, const diagTensor3& t2)
	{
		return tgf1 / dimensioned<diagTensor3>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor3, PatchField, GeoMesh>& res,
	            const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1,
	            const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1,
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor3, diagTensor3, diagTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor3, diagTensor3, diagTensor3, diagTensor3, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor3, PatchField, GeoMesh>& res, const dimensioned<diagTensor3>& dt1,
	            const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(const dimensioned<diagTensor3>& dt1,
	                                                                 const GeometricField<diagTensor3, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(const diagTensor3& t1,
	                                                                 const GeometricField<diagTensor3, PatchField, GeoMesh>
	                                                                 & gf2) { return dimensioned<diagTensor3>(t1) / gf2; }

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(const dimensioned<diagTensor3>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '|' + gf2.name() + ')', dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(const diagTensor3& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor3, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<diagTensor3>(t1) / tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor3, PatchField, GeoMesh>& res,
	            const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor3>& dt2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor3>& dt2)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1, const diagTensor3& t2)
	{
		return gf1 / dimensioned<diagTensor3>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor3>& dt2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + dt2.name() + ')', gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf1, const diagTensor3& t2)
	{
		return tgf1 / dimensioned<diagTensor3>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor3, PatchField, GeoMesh>& res,
	            const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf1,
	            const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf1,
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<sphericalTensor3, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, sphericalTensor3, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor3, sphericalTensor3, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<sphericalTensor3, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor3, sphericalTensor3, sphericalTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor3, sphericalTensor3, sphericalTensor3, diagTensor3, PatchField, GeoMesh>::
			clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor3, PatchField, GeoMesh>& res, const dimensioned<sphericalTensor3>& dt1,
	            const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(const dimensioned<sphericalTensor3>& dt1,
	                                                                 const GeometricField<diagTensor3, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(const sphericalTensor3& t1,
	                                                                 const GeometricField<diagTensor3, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		return dimensioned<sphericalTensor3>(t1) / gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(const dimensioned<sphericalTensor3>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '|' + gf2.name() + ')', dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(const sphericalTensor3& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor3, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<sphericalTensor3>(t1) / tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor3, PatchField, GeoMesh>& res,
	            const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor3>& dt2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor3>& dt2)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf1, const diagTensor3& t2)
	{
		return gf1 / dimensioned<diagTensor3>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<sphericalTensor3, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor3>& dt2)
	{
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, sphericalTensor3, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + dt2.name() + ')', gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor3, sphericalTensor3, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<sphericalTensor3, PatchField, GeoMesh>>& tgf1, const diagTensor3& t2)
	{
		return tgf1 / dimensioned<diagTensor3>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor3, PatchField, GeoMesh>& res,
	            const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1,
	            const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1,
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<sphericalTensor3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, sphericalTensor3, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor3, sphericalTensor3, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf1,
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<sphericalTensor3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor3, diagTensor3, diagTensor3, sphericalTensor3, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor3, diagTensor3, diagTensor3, sphericalTensor3, PatchField, GeoMesh>::
			clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor3, PatchField, GeoMesh>& res, const dimensioned<diagTensor3>& dt1,
	            const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(const dimensioned<diagTensor3>& dt1,
	                                                                 const GeometricField<
		                                                                 sphericalTensor3, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(const diagTensor3& t1,
	                                                                 const GeometricField<
		                                                                 sphericalTensor3, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<diagTensor3>(t1) / gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(const dimensioned<diagTensor3>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 sphericalTensor3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, sphericalTensor3, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '|' + gf2.name() + ')', dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor3, sphericalTensor3, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(const diagTensor3& t1,
	                                                                 const tmp<GeometricField<
		                                                                 sphericalTensor3, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<diagTensor3>(t1) / tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor3, PatchField, GeoMesh>& res,
	            const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1, const dimensioned<sphericalTensor3>& dt2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1, const dimensioned<sphericalTensor3>& dt2)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1, const sphericalTensor3& t2)
	{
		return gf1 / dimensioned<sphericalTensor3>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf1, const dimensioned<sphericalTensor3>& dt2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + dt2.name() + ')', gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf1, const sphericalTensor3& t2)
	{
		return tgf1 / dimensioned<sphericalTensor3>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor3, PatchField, GeoMesh>& res,
	         const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1,
	         const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1,
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor3, diagTensor3, diagTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor3, diagTensor3, diagTensor3, diagTensor3, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor3, PatchField, GeoMesh>& res,
	              const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1,
	              const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1,
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor3, diagTensor3, diagTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor3, diagTensor3, diagTensor3, diagTensor3, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor3, PatchField, GeoMesh>& res, const dimensioned<diagTensor3>& dt1,
	         const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::add(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(const dimensioned<diagTensor3>& dt1,
	                                                                 const GeometricField<diagTensor3, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(const diagTensor3& t1,
	                                                                 const GeometricField<diagTensor3, PatchField, GeoMesh>
	                                                                 & gf2) { return dimensioned<diagTensor3>(t1) + gf2; }

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(const dimensioned<diagTensor3>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '+' + gf2.name() + ')', dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(const diagTensor3& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor3, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<diagTensor3>(t1) + tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor3, PatchField, GeoMesh>& res,
	         const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor3>& dt2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor3>& dt2)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1, const diagTensor3& t2)
	{
		return gf1 + dimensioned<diagTensor3>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor3>& dt2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + dt2.name() + ')', gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf1, const diagTensor3& t2)
	{
		return tgf1 + dimensioned<diagTensor3>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor3, PatchField, GeoMesh>& res, const dimensioned<diagTensor3>& dt1,
	              const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(const dimensioned<diagTensor3>& dt1,
	                                                                 const GeometricField<diagTensor3, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(const diagTensor3& t1,
	                                                                 const GeometricField<diagTensor3, PatchField, GeoMesh>
	                                                                 & gf2) { return dimensioned<diagTensor3>(t1) - gf2; }

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(const dimensioned<diagTensor3>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '-' + gf2.name() + ')', dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(const diagTensor3& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor3, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<diagTensor3>(t1) - tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor3, PatchField, GeoMesh>& res,
	              const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor3>& dt2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor3>& dt2)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1, const diagTensor3& t2)
	{
		return gf1 - dimensioned<diagTensor3>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor3>& dt2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '-' + dt2.name() + ')', gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf1, const diagTensor3& t2)
	{
		return tgf1 - dimensioned<diagTensor3>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor3, PatchField, GeoMesh>& res,
	         const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf1,
	         const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf1,
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<sphericalTensor3, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, sphericalTensor3, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor3, sphericalTensor3, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<sphericalTensor3, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor3, sphericalTensor3, sphericalTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor3, sphericalTensor3, sphericalTensor3, diagTensor3, PatchField, GeoMesh>::
			clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor3, PatchField, GeoMesh>& res,
	              const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf1,
	              const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf1,
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<sphericalTensor3, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, sphericalTensor3, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor3, sphericalTensor3, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<sphericalTensor3, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor3, sphericalTensor3, sphericalTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor3, sphericalTensor3, sphericalTensor3, diagTensor3, PatchField, GeoMesh>::
			clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor3, PatchField, GeoMesh>& res, const dimensioned<sphericalTensor3>& dt1,
	         const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::add(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(const dimensioned<sphericalTensor3>& dt1,
	                                                                 const GeometricField<diagTensor3, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(const sphericalTensor3& t1,
	                                                                 const GeometricField<diagTensor3, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		return dimensioned<sphericalTensor3>(t1) + gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(const dimensioned<sphericalTensor3>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '+' + gf2.name() + ')', dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(const sphericalTensor3& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor3, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<sphericalTensor3>(t1) + tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor3, PatchField, GeoMesh>& res,
	         const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor3>& dt2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor3>& dt2)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf1, const diagTensor3& t2)
	{
		return gf1 + dimensioned<diagTensor3>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<sphericalTensor3, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor3>& dt2)
	{
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, sphericalTensor3, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + dt2.name() + ')', gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor3, sphericalTensor3, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<sphericalTensor3, PatchField, GeoMesh>>& tgf1, const diagTensor3& t2)
	{
		return tgf1 + dimensioned<diagTensor3>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor3, PatchField, GeoMesh>& res, const dimensioned<sphericalTensor3>& dt1,
	              const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(const dimensioned<sphericalTensor3>& dt1,
	                                                                 const GeometricField<diagTensor3, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(const sphericalTensor3& t1,
	                                                                 const GeometricField<diagTensor3, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		return dimensioned<sphericalTensor3>(t1) - gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(const dimensioned<sphericalTensor3>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '-' + gf2.name() + ')', dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(const sphericalTensor3& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor3, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<sphericalTensor3>(t1) - tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor3, PatchField, GeoMesh>& res,
	              const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor3>& dt2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor3>& dt2)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf1, const diagTensor3& t2)
	{
		return gf1 - dimensioned<diagTensor3>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<sphericalTensor3, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor3>& dt2)
	{
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, sphericalTensor3, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '-' + dt2.name() + ')', gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor3, sphericalTensor3, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<sphericalTensor3, PatchField, GeoMesh>>& tgf1, const diagTensor3& t2)
	{
		return tgf1 - dimensioned<diagTensor3>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor3, PatchField, GeoMesh>& res,
	         const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1,
	         const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1,
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<sphericalTensor3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, sphericalTensor3, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor3, sphericalTensor3, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf1,
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<sphericalTensor3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor3, diagTensor3, diagTensor3, sphericalTensor3, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor3, diagTensor3, diagTensor3, sphericalTensor3, PatchField, GeoMesh>::
			clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor3, PatchField, GeoMesh>& res,
	              const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1,
	              const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1,
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<sphericalTensor3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, sphericalTensor3, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor3, sphericalTensor3, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf1,
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<sphericalTensor3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor3, diagTensor3, diagTensor3, sphericalTensor3, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor3, diagTensor3, diagTensor3, sphericalTensor3, PatchField, GeoMesh>::
			clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor3, PatchField, GeoMesh>& res, const dimensioned<diagTensor3>& dt1,
	         const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::add(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(const dimensioned<diagTensor3>& dt1,
	                                                                 const GeometricField<
		                                                                 sphericalTensor3, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(const diagTensor3& t1,
	                                                                 const GeometricField<
		                                                                 sphericalTensor3, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<diagTensor3>(t1) + gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(const dimensioned<diagTensor3>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 sphericalTensor3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, sphericalTensor3, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '+' + gf2.name() + ')', dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor3, sphericalTensor3, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(const diagTensor3& t1,
	                                                                 const tmp<GeometricField<
		                                                                 sphericalTensor3, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<diagTensor3>(t1) + tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor3, PatchField, GeoMesh>& res,
	         const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1, const dimensioned<sphericalTensor3>& dt2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1, const dimensioned<sphericalTensor3>& dt2)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1, const sphericalTensor3& t2)
	{
		return gf1 + dimensioned<sphericalTensor3>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf1, const dimensioned<sphericalTensor3>& dt2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + dt2.name() + ')', gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf1, const sphericalTensor3& t2)
	{
		return tgf1 + dimensioned<sphericalTensor3>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor3, PatchField, GeoMesh>& res, const dimensioned<diagTensor3>& dt1,
	              const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(const dimensioned<diagTensor3>& dt1,
	                                                                 const GeometricField<
		                                                                 sphericalTensor3, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(const diagTensor3& t1,
	                                                                 const GeometricField<
		                                                                 sphericalTensor3, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<diagTensor3>(t1) - gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(const dimensioned<diagTensor3>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 sphericalTensor3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, sphericalTensor3, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '+' + gf2.name() + ')', dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor3, sphericalTensor3, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(const diagTensor3& t1,
	                                                                 const tmp<GeometricField<
		                                                                 sphericalTensor3, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<diagTensor3>(t1) - tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor3, PatchField, GeoMesh>& res,
	              const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1, const dimensioned<sphericalTensor3>& dt2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1, const dimensioned<sphericalTensor3>& dt2)
	{
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor3, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1, const sphericalTensor3& t2)
	{
		return gf1 - dimensioned<sphericalTensor3>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf1, const dimensioned<sphericalTensor3>& dt2)
	{
		const GeometricField<diagTensor3, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + dt2.name() + ')', gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor3, diagTensor3, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor3, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor3, PatchField, GeoMesh>>& tgf1, const sphericalTensor3& t2)
	{
		return tgf1 - dimensioned<sphericalTensor3>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void inv(GeometricField<diagTensor4, PatchField, GeoMesh>& res,
	         const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1)
	{
		tnbLib::inv(res.internalField(), gf1.internalField());
		tnbLib::inv(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> inv(const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject("inv" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			inv(gf1.dimensions())));
		tnbLib::inv(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> inv(
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf1, "inv" "(" + gf1.name() + ')', inv(gf1.dimensions())));
		tnbLib::inv(tRes(), gf1);
		reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void diag(GeometricField<diagTensor4, PatchField, GeoMesh>& res,
	          const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1)
	{
		tnbLib::diag(res.internalField(), gf1.internalField());
		tnbLib::diag(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> diag(const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject("diag" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			diag(gf1.dimensions())));
		tnbLib::diag(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> diag(
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf1, "diag" "(" + gf1.name() + ')', diag(gf1.dimensions())));
		tnbLib::diag(tRes(), gf1);
		reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void contractScalar(GeometricField<scalar, PatchField, GeoMesh>& res,
	                    const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1)
	{
		tnbLib::contractScalar(res.internalField(), gf1.internalField());
		tnbLib::contractScalar(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> contractScalar(
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("contractScalar" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), contractScalar(gf1.dimensions())));
		tnbLib::contractScalar(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> contractScalar(
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, diagTensor4, PatchField, GeoMesh>::New(
				tgf1, "contractScalar" "(" + gf1.name() + ')', contractScalar(gf1.dimensions())));
		tnbLib::contractScalar(tRes(), gf1);
		reuseTmpGeometricField<scalar, diagTensor4, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void contractLinear(GeometricField<vector4, PatchField, GeoMesh>& res,
	                    const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1)
	{
		tnbLib::contractLinear(res.internalField(), gf1.internalField());
		tnbLib::contractLinear(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> contractLinear(
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(new GeometricField<vector4, PatchField, GeoMesh>(
			IOobject("contractLinear" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), contractLinear(gf1.dimensions())));
		tnbLib::contractLinear(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> contractLinear(
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector4, diagTensor4, PatchField, GeoMesh>::New(
				tgf1, "contractLinear" "(" + gf1.name() + ')', contractLinear(gf1.dimensions())));
		tnbLib::contractLinear(tRes(), gf1);
		reuseTmpGeometricField<vector4, diagTensor4, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<diagTensor4, PatchField, GeoMesh>& res,
	              const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	              const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		tnbLib::multiply(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::multiply(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator *(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1, const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '*' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator *(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '*' + gf2.name() + ')', gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, scalar, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '*' + gf2.name() + ')', gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor4, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor4, scalar, scalar, diagTensor4, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '*' + gf2.name() + ')', gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor4, scalar, scalar, diagTensor4, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<diagTensor4, PatchField, GeoMesh>& res, const dimensioned<scalar>& dt1,
	              const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		tnbLib::multiply(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::multiply(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator *(const dimensioned<scalar>& dt1,
	                                                                 const GeometricField<diagTensor4, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '*' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator *(const scalar& t1,
	                                                                 const GeometricField<diagTensor4, PatchField, GeoMesh>
	                                                                 & gf2) { return dimensioned<scalar>(t1) * gf2; }

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator *(const dimensioned<scalar>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '*' + gf2.name() + ')', dt1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator *(const scalar& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor4, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<scalar>(t1) * tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<diagTensor4, PatchField, GeoMesh>& res,
	              const GeometricField<scalar, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor4>& dt2)
	{
		tnbLib::multiply(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::multiply(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator *(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor4>& dt2)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '*' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() * dt2.dimensions()));
		tnbLib::multiply(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator *(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1, const diagTensor4& t2)
	{
		return gf1 * dimensioned<diagTensor4>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor4>& dt2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, scalar, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '*' + dt2.name() + ')', gf1.dimensions() * dt2.dimensions()));
		tnbLib::multiply(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor4, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const diagTensor4& t2)
	{
		return tgf1 * dimensioned<diagTensor4>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor4, PatchField, GeoMesh>& res,
	            const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	            const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1, const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, scalar, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor4, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor4, scalar, scalar, diagTensor4, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor4, scalar, scalar, diagTensor4, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor4, PatchField, GeoMesh>& res, const dimensioned<scalar>& dt1,
	            const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
	                                                                 const GeometricField<diagTensor4, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(const scalar& t1,
	                                                                 const GeometricField<diagTensor4, PatchField, GeoMesh>
	                                                                 & gf2) { return dimensioned<scalar>(t1) / gf2; }

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '|' + gf2.name() + ')', dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(const scalar& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor4, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<scalar>(t1) / tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor4, PatchField, GeoMesh>& res,
	            const GeometricField<scalar, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor4>& dt2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor4>& dt2)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1, const diagTensor4& t2)
	{
		return gf1 / dimensioned<diagTensor4>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor4>& dt2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, scalar, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + dt2.name() + ')', gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor4, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const diagTensor4& t2)
	{
		return tgf1 / dimensioned<diagTensor4>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<vector4, PatchField, GeoMesh>& res, const GeometricField<vector4, PatchField, GeoMesh>& gf1,
	            const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator /(const GeometricField<vector4, PatchField, GeoMesh>& gf1,
	                                                             const GeometricField<diagTensor4, PatchField, GeoMesh>&
	                                                             gf2)
	{
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(new GeometricField<vector4, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator /(const GeometricField<vector4, PatchField, GeoMesh>& gf1,
	                                                             const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>
	                                                             >& tgf2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector4, diagTensor4, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector4, diagTensor4, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<vector4, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<vector4, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '|' + gf2.name() + ')',
			                                                                   gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<vector4, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<vector4, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<vector4, vector4, vector4, diagTensor4, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<vector4, vector4, vector4, diagTensor4, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<vector4, PatchField, GeoMesh>& res, const dimensioned<vector4>& dt1,
	            const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator /(const dimensioned<vector4>& dt1,
	                                                             const GeometricField<diagTensor4, PatchField, GeoMesh>&
	                                                             gf2)
	{
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(new GeometricField<vector4, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator /(const vector4& t1,
	                                                             const GeometricField<diagTensor4, PatchField, GeoMesh>&
	                                                             gf2) { return dimensioned<vector4>(t1) / gf2; }

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator /(const dimensioned<vector4>& dt1,
	                                                             const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>
	                                                             >& tgf2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector4, diagTensor4, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '|' + gf2.name() + ')', dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		reuseTmpGeometricField<vector4, diagTensor4, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator /(const vector4& t1,
	                                                             const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>
	                                                             >& tgf2) { return dimensioned<vector4>(t1) / tgf2; }

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<vector4, PatchField, GeoMesh>& res, const GeometricField<vector4, PatchField, GeoMesh>& gf1,
	            const dimensioned<diagTensor4>& dt2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator /(const GeometricField<vector4, PatchField, GeoMesh>& gf1,
	                                                             const dimensioned<diagTensor4>& dt2)
	{
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(new GeometricField<vector4, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator /(const GeometricField<vector4, PatchField, GeoMesh>& gf1,
	                                                             const diagTensor4& t2)
	{
		return gf1 / dimensioned<diagTensor4>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<vector4, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor4>& dt2)
	{
		const GeometricField<vector4, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '|' + dt2.name() + ')',
			                                                                   gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<vector4, PatchField, GeoMesh>>& tgf1, const diagTensor4& t2)
	{
		return tgf1 / dimensioned<diagTensor4>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor4, PatchField, GeoMesh>& res,
	            const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1,
	            const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1,
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor4, diagTensor4, diagTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor4, diagTensor4, diagTensor4, diagTensor4, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor4, PatchField, GeoMesh>& res, const dimensioned<diagTensor4>& dt1,
	            const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(const dimensioned<diagTensor4>& dt1,
	                                                                 const GeometricField<diagTensor4, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(const diagTensor4& t1,
	                                                                 const GeometricField<diagTensor4, PatchField, GeoMesh>
	                                                                 & gf2) { return dimensioned<diagTensor4>(t1) / gf2; }

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(const dimensioned<diagTensor4>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '|' + gf2.name() + ')', dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(const diagTensor4& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor4, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<diagTensor4>(t1) / tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor4, PatchField, GeoMesh>& res,
	            const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor4>& dt2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor4>& dt2)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1, const diagTensor4& t2)
	{
		return gf1 / dimensioned<diagTensor4>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor4>& dt2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + dt2.name() + ')', gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf1, const diagTensor4& t2)
	{
		return tgf1 / dimensioned<diagTensor4>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor4, PatchField, GeoMesh>& res,
	            const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf1,
	            const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf1,
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<sphericalTensor4, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, sphericalTensor4, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor4, sphericalTensor4, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<sphericalTensor4, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor4, sphericalTensor4, sphericalTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor4, sphericalTensor4, sphericalTensor4, diagTensor4, PatchField, GeoMesh>::
			clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor4, PatchField, GeoMesh>& res, const dimensioned<sphericalTensor4>& dt1,
	            const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(const dimensioned<sphericalTensor4>& dt1,
	                                                                 const GeometricField<diagTensor4, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(const sphericalTensor4& t1,
	                                                                 const GeometricField<diagTensor4, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		return dimensioned<sphericalTensor4>(t1) / gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(const dimensioned<sphericalTensor4>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '|' + gf2.name() + ')', dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(const sphericalTensor4& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor4, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<sphericalTensor4>(t1) / tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor4, PatchField, GeoMesh>& res,
	            const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor4>& dt2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor4>& dt2)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf1, const diagTensor4& t2)
	{
		return gf1 / dimensioned<diagTensor4>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<sphericalTensor4, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor4>& dt2)
	{
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, sphericalTensor4, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + dt2.name() + ')', gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor4, sphericalTensor4, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<sphericalTensor4, PatchField, GeoMesh>>& tgf1, const diagTensor4& t2)
	{
		return tgf1 / dimensioned<diagTensor4>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor4, PatchField, GeoMesh>& res,
	            const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1,
	            const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1,
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<sphericalTensor4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, sphericalTensor4, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor4, sphericalTensor4, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf1,
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<sphericalTensor4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor4, diagTensor4, diagTensor4, sphericalTensor4, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor4, diagTensor4, diagTensor4, sphericalTensor4, PatchField, GeoMesh>::
			clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor4, PatchField, GeoMesh>& res, const dimensioned<diagTensor4>& dt1,
	            const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(const dimensioned<diagTensor4>& dt1,
	                                                                 const GeometricField<
		                                                                 sphericalTensor4, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(const diagTensor4& t1,
	                                                                 const GeometricField<
		                                                                 sphericalTensor4, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<diagTensor4>(t1) / gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(const dimensioned<diagTensor4>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 sphericalTensor4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, sphericalTensor4, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '|' + gf2.name() + ')', dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor4, sphericalTensor4, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(const diagTensor4& t1,
	                                                                 const tmp<GeometricField<
		                                                                 sphericalTensor4, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<diagTensor4>(t1) / tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor4, PatchField, GeoMesh>& res,
	            const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1, const dimensioned<sphericalTensor4>& dt2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1, const dimensioned<sphericalTensor4>& dt2)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1, const sphericalTensor4& t2)
	{
		return gf1 / dimensioned<sphericalTensor4>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf1, const dimensioned<sphericalTensor4>& dt2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + dt2.name() + ')', gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf1, const sphericalTensor4& t2)
	{
		return tgf1 / dimensioned<sphericalTensor4>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor4, PatchField, GeoMesh>& res,
	         const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1,
	         const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1,
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor4, diagTensor4, diagTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor4, diagTensor4, diagTensor4, diagTensor4, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor4, PatchField, GeoMesh>& res,
	              const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1,
	              const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1,
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor4, diagTensor4, diagTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor4, diagTensor4, diagTensor4, diagTensor4, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor4, PatchField, GeoMesh>& res, const dimensioned<diagTensor4>& dt1,
	         const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::add(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(const dimensioned<diagTensor4>& dt1,
	                                                                 const GeometricField<diagTensor4, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(const diagTensor4& t1,
	                                                                 const GeometricField<diagTensor4, PatchField, GeoMesh>
	                                                                 & gf2) { return dimensioned<diagTensor4>(t1) + gf2; }

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(const dimensioned<diagTensor4>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '+' + gf2.name() + ')', dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(const diagTensor4& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor4, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<diagTensor4>(t1) + tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor4, PatchField, GeoMesh>& res,
	         const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor4>& dt2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor4>& dt2)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1, const diagTensor4& t2)
	{
		return gf1 + dimensioned<diagTensor4>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor4>& dt2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + dt2.name() + ')', gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf1, const diagTensor4& t2)
	{
		return tgf1 + dimensioned<diagTensor4>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor4, PatchField, GeoMesh>& res, const dimensioned<diagTensor4>& dt1,
	              const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(const dimensioned<diagTensor4>& dt1,
	                                                                 const GeometricField<diagTensor4, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(const diagTensor4& t1,
	                                                                 const GeometricField<diagTensor4, PatchField, GeoMesh>
	                                                                 & gf2) { return dimensioned<diagTensor4>(t1) - gf2; }

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(const dimensioned<diagTensor4>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '-' + gf2.name() + ')', dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(const diagTensor4& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor4, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<diagTensor4>(t1) - tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor4, PatchField, GeoMesh>& res,
	              const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor4>& dt2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor4>& dt2)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1, const diagTensor4& t2)
	{
		return gf1 - dimensioned<diagTensor4>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor4>& dt2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '-' + dt2.name() + ')', gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf1, const diagTensor4& t2)
	{
		return tgf1 - dimensioned<diagTensor4>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor4, PatchField, GeoMesh>& res,
	         const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf1,
	         const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf1,
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<sphericalTensor4, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, sphericalTensor4, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor4, sphericalTensor4, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<sphericalTensor4, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor4, sphericalTensor4, sphericalTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor4, sphericalTensor4, sphericalTensor4, diagTensor4, PatchField, GeoMesh>::
			clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor4, PatchField, GeoMesh>& res,
	              const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf1,
	              const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf1,
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<sphericalTensor4, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, sphericalTensor4, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor4, sphericalTensor4, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<sphericalTensor4, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor4, sphericalTensor4, sphericalTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor4, sphericalTensor4, sphericalTensor4, diagTensor4, PatchField, GeoMesh>::
			clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor4, PatchField, GeoMesh>& res, const dimensioned<sphericalTensor4>& dt1,
	         const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::add(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(const dimensioned<sphericalTensor4>& dt1,
	                                                                 const GeometricField<diagTensor4, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(const sphericalTensor4& t1,
	                                                                 const GeometricField<diagTensor4, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		return dimensioned<sphericalTensor4>(t1) + gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(const dimensioned<sphericalTensor4>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '+' + gf2.name() + ')', dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(const sphericalTensor4& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor4, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<sphericalTensor4>(t1) + tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor4, PatchField, GeoMesh>& res,
	         const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor4>& dt2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor4>& dt2)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf1, const diagTensor4& t2)
	{
		return gf1 + dimensioned<diagTensor4>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<sphericalTensor4, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor4>& dt2)
	{
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, sphericalTensor4, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + dt2.name() + ')', gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor4, sphericalTensor4, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<sphericalTensor4, PatchField, GeoMesh>>& tgf1, const diagTensor4& t2)
	{
		return tgf1 + dimensioned<diagTensor4>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor4, PatchField, GeoMesh>& res, const dimensioned<sphericalTensor4>& dt1,
	              const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(const dimensioned<sphericalTensor4>& dt1,
	                                                                 const GeometricField<diagTensor4, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(const sphericalTensor4& t1,
	                                                                 const GeometricField<diagTensor4, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		return dimensioned<sphericalTensor4>(t1) - gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(const dimensioned<sphericalTensor4>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '-' + gf2.name() + ')', dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(const sphericalTensor4& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor4, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<sphericalTensor4>(t1) - tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor4, PatchField, GeoMesh>& res,
	              const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor4>& dt2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor4>& dt2)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf1, const diagTensor4& t2)
	{
		return gf1 - dimensioned<diagTensor4>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<sphericalTensor4, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor4>& dt2)
	{
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, sphericalTensor4, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '-' + dt2.name() + ')', gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor4, sphericalTensor4, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<sphericalTensor4, PatchField, GeoMesh>>& tgf1, const diagTensor4& t2)
	{
		return tgf1 - dimensioned<diagTensor4>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor4, PatchField, GeoMesh>& res,
	         const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1,
	         const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1,
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<sphericalTensor4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, sphericalTensor4, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor4, sphericalTensor4, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf1,
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<sphericalTensor4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor4, diagTensor4, diagTensor4, sphericalTensor4, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor4, diagTensor4, diagTensor4, sphericalTensor4, PatchField, GeoMesh>::
			clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor4, PatchField, GeoMesh>& res,
	              const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1,
	              const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1,
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<sphericalTensor4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, sphericalTensor4, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor4, sphericalTensor4, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf1,
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<sphericalTensor4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor4, diagTensor4, diagTensor4, sphericalTensor4, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor4, diagTensor4, diagTensor4, sphericalTensor4, PatchField, GeoMesh>::
			clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor4, PatchField, GeoMesh>& res, const dimensioned<diagTensor4>& dt1,
	         const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::add(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(const dimensioned<diagTensor4>& dt1,
	                                                                 const GeometricField<
		                                                                 sphericalTensor4, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(const diagTensor4& t1,
	                                                                 const GeometricField<
		                                                                 sphericalTensor4, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<diagTensor4>(t1) + gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(const dimensioned<diagTensor4>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 sphericalTensor4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, sphericalTensor4, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '+' + gf2.name() + ')', dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor4, sphericalTensor4, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(const diagTensor4& t1,
	                                                                 const tmp<GeometricField<
		                                                                 sphericalTensor4, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<diagTensor4>(t1) + tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor4, PatchField, GeoMesh>& res,
	         const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1, const dimensioned<sphericalTensor4>& dt2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1, const dimensioned<sphericalTensor4>& dt2)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1, const sphericalTensor4& t2)
	{
		return gf1 + dimensioned<sphericalTensor4>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf1, const dimensioned<sphericalTensor4>& dt2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + dt2.name() + ')', gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf1, const sphericalTensor4& t2)
	{
		return tgf1 + dimensioned<sphericalTensor4>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor4, PatchField, GeoMesh>& res, const dimensioned<diagTensor4>& dt1,
	              const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(const dimensioned<diagTensor4>& dt1,
	                                                                 const GeometricField<
		                                                                 sphericalTensor4, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(const diagTensor4& t1,
	                                                                 const GeometricField<
		                                                                 sphericalTensor4, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<diagTensor4>(t1) - gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(const dimensioned<diagTensor4>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 sphericalTensor4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, sphericalTensor4, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '+' + gf2.name() + ')', dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor4, sphericalTensor4, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(const diagTensor4& t1,
	                                                                 const tmp<GeometricField<
		                                                                 sphericalTensor4, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<diagTensor4>(t1) - tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor4, PatchField, GeoMesh>& res,
	              const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1, const dimensioned<sphericalTensor4>& dt2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1, const dimensioned<sphericalTensor4>& dt2)
	{
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor4, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1, const sphericalTensor4& t2)
	{
		return gf1 - dimensioned<sphericalTensor4>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf1, const dimensioned<sphericalTensor4>& dt2)
	{
		const GeometricField<diagTensor4, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + dt2.name() + ')', gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor4, diagTensor4, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor4, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor4, PatchField, GeoMesh>>& tgf1, const sphericalTensor4& t2)
	{
		return tgf1 - dimensioned<sphericalTensor4>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void inv(GeometricField<diagTensor6, PatchField, GeoMesh>& res,
	         const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1)
	{
		tnbLib::inv(res.internalField(), gf1.internalField());
		tnbLib::inv(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> inv(const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject("inv" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			inv(gf1.dimensions())));
		tnbLib::inv(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> inv(
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf1, "inv" "(" + gf1.name() + ')', inv(gf1.dimensions())));
		tnbLib::inv(tRes(), gf1);
		reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void diag(GeometricField<diagTensor6, PatchField, GeoMesh>& res,
	          const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1)
	{
		tnbLib::diag(res.internalField(), gf1.internalField());
		tnbLib::diag(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> diag(const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject("diag" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			diag(gf1.dimensions())));
		tnbLib::diag(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> diag(
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf1, "diag" "(" + gf1.name() + ')', diag(gf1.dimensions())));
		tnbLib::diag(tRes(), gf1);
		reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void contractScalar(GeometricField<scalar, PatchField, GeoMesh>& res,
	                    const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1)
	{
		tnbLib::contractScalar(res.internalField(), gf1.internalField());
		tnbLib::contractScalar(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> contractScalar(
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("contractScalar" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), contractScalar(gf1.dimensions())));
		tnbLib::contractScalar(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> contractScalar(
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, diagTensor6, PatchField, GeoMesh>::New(
				tgf1, "contractScalar" "(" + gf1.name() + ')', contractScalar(gf1.dimensions())));
		tnbLib::contractScalar(tRes(), gf1);
		reuseTmpGeometricField<scalar, diagTensor6, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void contractLinear(GeometricField<vector6, PatchField, GeoMesh>& res,
	                    const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1)
	{
		tnbLib::contractLinear(res.internalField(), gf1.internalField());
		tnbLib::contractLinear(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> contractLinear(
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(new GeometricField<vector6, PatchField, GeoMesh>(
			IOobject("contractLinear" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), contractLinear(gf1.dimensions())));
		tnbLib::contractLinear(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> contractLinear(
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector6, diagTensor6, PatchField, GeoMesh>::New(
				tgf1, "contractLinear" "(" + gf1.name() + ')', contractLinear(gf1.dimensions())));
		tnbLib::contractLinear(tRes(), gf1);
		reuseTmpGeometricField<vector6, diagTensor6, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<diagTensor6, PatchField, GeoMesh>& res,
	              const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	              const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		tnbLib::multiply(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::multiply(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator *(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1, const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '*' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator *(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '*' + gf2.name() + ')', gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, scalar, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '*' + gf2.name() + ')', gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor6, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor6, scalar, scalar, diagTensor6, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '*' + gf2.name() + ')', gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor6, scalar, scalar, diagTensor6, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<diagTensor6, PatchField, GeoMesh>& res, const dimensioned<scalar>& dt1,
	              const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		tnbLib::multiply(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::multiply(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator *(const dimensioned<scalar>& dt1,
	                                                                 const GeometricField<diagTensor6, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '*' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator *(const scalar& t1,
	                                                                 const GeometricField<diagTensor6, PatchField, GeoMesh>
	                                                                 & gf2) { return dimensioned<scalar>(t1) * gf2; }

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator *(const dimensioned<scalar>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '*' + gf2.name() + ')', dt1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator *(const scalar& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor6, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<scalar>(t1) * tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<diagTensor6, PatchField, GeoMesh>& res,
	              const GeometricField<scalar, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor6>& dt2)
	{
		tnbLib::multiply(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::multiply(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator *(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor6>& dt2)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '*' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() * dt2.dimensions()));
		tnbLib::multiply(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator *(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1, const diagTensor6& t2)
	{
		return gf1 * dimensioned<diagTensor6>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor6>& dt2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, scalar, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '*' + dt2.name() + ')', gf1.dimensions() * dt2.dimensions()));
		tnbLib::multiply(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor6, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const diagTensor6& t2)
	{
		return tgf1 * dimensioned<diagTensor6>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor6, PatchField, GeoMesh>& res,
	            const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	            const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1, const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, scalar, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor6, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor6, scalar, scalar, diagTensor6, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor6, scalar, scalar, diagTensor6, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor6, PatchField, GeoMesh>& res, const dimensioned<scalar>& dt1,
	            const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
	                                                                 const GeometricField<diagTensor6, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(const scalar& t1,
	                                                                 const GeometricField<diagTensor6, PatchField, GeoMesh>
	                                                                 & gf2) { return dimensioned<scalar>(t1) / gf2; }

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '|' + gf2.name() + ')', dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(const scalar& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor6, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<scalar>(t1) / tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor6, PatchField, GeoMesh>& res,
	            const GeometricField<scalar, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor6>& dt2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor6>& dt2)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1, const diagTensor6& t2)
	{
		return gf1 / dimensioned<diagTensor6>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor6>& dt2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, scalar, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + dt2.name() + ')', gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor6, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const diagTensor6& t2)
	{
		return tgf1 / dimensioned<diagTensor6>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<vector6, PatchField, GeoMesh>& res, const GeometricField<vector6, PatchField, GeoMesh>& gf1,
	            const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator /(const GeometricField<vector6, PatchField, GeoMesh>& gf1,
	                                                             const GeometricField<diagTensor6, PatchField, GeoMesh>&
	                                                             gf2)
	{
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(new GeometricField<vector6, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator /(const GeometricField<vector6, PatchField, GeoMesh>& gf1,
	                                                             const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>
	                                                             >& tgf2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector6, diagTensor6, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector6, diagTensor6, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<vector6, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<vector6, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '|' + gf2.name() + ')',
			                                                                   gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<vector6, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<vector6, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<vector6, vector6, vector6, diagTensor6, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<vector6, vector6, vector6, diagTensor6, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<vector6, PatchField, GeoMesh>& res, const dimensioned<vector6>& dt1,
	            const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator /(const dimensioned<vector6>& dt1,
	                                                             const GeometricField<diagTensor6, PatchField, GeoMesh>&
	                                                             gf2)
	{
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(new GeometricField<vector6, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator /(const vector6& t1,
	                                                             const GeometricField<diagTensor6, PatchField, GeoMesh>&
	                                                             gf2) { return dimensioned<vector6>(t1) / gf2; }

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator /(const dimensioned<vector6>& dt1,
	                                                             const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>
	                                                             >& tgf2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector6, diagTensor6, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '|' + gf2.name() + ')', dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		reuseTmpGeometricField<vector6, diagTensor6, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator /(const vector6& t1,
	                                                             const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>
	                                                             >& tgf2) { return dimensioned<vector6>(t1) / tgf2; }

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<vector6, PatchField, GeoMesh>& res, const GeometricField<vector6, PatchField, GeoMesh>& gf1,
	            const dimensioned<diagTensor6>& dt2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator /(const GeometricField<vector6, PatchField, GeoMesh>& gf1,
	                                                             const dimensioned<diagTensor6>& dt2)
	{
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(new GeometricField<vector6, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator /(const GeometricField<vector6, PatchField, GeoMesh>& gf1,
	                                                             const diagTensor6& t2)
	{
		return gf1 / dimensioned<diagTensor6>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<vector6, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor6>& dt2)
	{
		const GeometricField<vector6, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '|' + dt2.name() + ')',
			                                                                   gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<vector6, PatchField, GeoMesh>>& tgf1, const diagTensor6& t2)
	{
		return tgf1 / dimensioned<diagTensor6>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor6, PatchField, GeoMesh>& res,
	            const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1,
	            const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1,
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor6, diagTensor6, diagTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor6, diagTensor6, diagTensor6, diagTensor6, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor6, PatchField, GeoMesh>& res, const dimensioned<diagTensor6>& dt1,
	            const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(const dimensioned<diagTensor6>& dt1,
	                                                                 const GeometricField<diagTensor6, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(const diagTensor6& t1,
	                                                                 const GeometricField<diagTensor6, PatchField, GeoMesh>
	                                                                 & gf2) { return dimensioned<diagTensor6>(t1) / gf2; }

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(const dimensioned<diagTensor6>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '|' + gf2.name() + ')', dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(const diagTensor6& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor6, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<diagTensor6>(t1) / tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor6, PatchField, GeoMesh>& res,
	            const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor6>& dt2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor6>& dt2)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1, const diagTensor6& t2)
	{
		return gf1 / dimensioned<diagTensor6>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor6>& dt2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + dt2.name() + ')', gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf1, const diagTensor6& t2)
	{
		return tgf1 / dimensioned<diagTensor6>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor6, PatchField, GeoMesh>& res,
	            const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf1,
	            const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf1,
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<sphericalTensor6, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, sphericalTensor6, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor6, sphericalTensor6, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<sphericalTensor6, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor6, sphericalTensor6, sphericalTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor6, sphericalTensor6, sphericalTensor6, diagTensor6, PatchField, GeoMesh>::
			clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor6, PatchField, GeoMesh>& res, const dimensioned<sphericalTensor6>& dt1,
	            const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(const dimensioned<sphericalTensor6>& dt1,
	                                                                 const GeometricField<diagTensor6, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(const sphericalTensor6& t1,
	                                                                 const GeometricField<diagTensor6, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		return dimensioned<sphericalTensor6>(t1) / gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(const dimensioned<sphericalTensor6>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '|' + gf2.name() + ')', dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(const sphericalTensor6& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor6, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<sphericalTensor6>(t1) / tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor6, PatchField, GeoMesh>& res,
	            const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor6>& dt2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor6>& dt2)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf1, const diagTensor6& t2)
	{
		return gf1 / dimensioned<diagTensor6>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<sphericalTensor6, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor6>& dt2)
	{
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, sphericalTensor6, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + dt2.name() + ')', gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor6, sphericalTensor6, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<sphericalTensor6, PatchField, GeoMesh>>& tgf1, const diagTensor6& t2)
	{
		return tgf1 / dimensioned<diagTensor6>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor6, PatchField, GeoMesh>& res,
	            const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1,
	            const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1,
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<sphericalTensor6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, sphericalTensor6, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor6, sphericalTensor6, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf1,
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<sphericalTensor6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor6, diagTensor6, diagTensor6, sphericalTensor6, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor6, diagTensor6, diagTensor6, sphericalTensor6, PatchField, GeoMesh>::
			clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor6, PatchField, GeoMesh>& res, const dimensioned<diagTensor6>& dt1,
	            const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(const dimensioned<diagTensor6>& dt1,
	                                                                 const GeometricField<
		                                                                 sphericalTensor6, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(const diagTensor6& t1,
	                                                                 const GeometricField<
		                                                                 sphericalTensor6, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<diagTensor6>(t1) / gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(const dimensioned<diagTensor6>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 sphericalTensor6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, sphericalTensor6, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '|' + gf2.name() + ')', dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor6, sphericalTensor6, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(const diagTensor6& t1,
	                                                                 const tmp<GeometricField<
		                                                                 sphericalTensor6, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<diagTensor6>(t1) / tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor6, PatchField, GeoMesh>& res,
	            const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1, const dimensioned<sphericalTensor6>& dt2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1, const dimensioned<sphericalTensor6>& dt2)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1, const sphericalTensor6& t2)
	{
		return gf1 / dimensioned<sphericalTensor6>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf1, const dimensioned<sphericalTensor6>& dt2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + dt2.name() + ')', gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf1, const sphericalTensor6& t2)
	{
		return tgf1 / dimensioned<sphericalTensor6>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor6, PatchField, GeoMesh>& res,
	         const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1,
	         const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1,
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor6, diagTensor6, diagTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor6, diagTensor6, diagTensor6, diagTensor6, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor6, PatchField, GeoMesh>& res,
	              const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1,
	              const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1,
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor6, diagTensor6, diagTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor6, diagTensor6, diagTensor6, diagTensor6, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor6, PatchField, GeoMesh>& res, const dimensioned<diagTensor6>& dt1,
	         const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::add(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(const dimensioned<diagTensor6>& dt1,
	                                                                 const GeometricField<diagTensor6, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(const diagTensor6& t1,
	                                                                 const GeometricField<diagTensor6, PatchField, GeoMesh>
	                                                                 & gf2) { return dimensioned<diagTensor6>(t1) + gf2; }

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(const dimensioned<diagTensor6>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '+' + gf2.name() + ')', dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(const diagTensor6& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor6, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<diagTensor6>(t1) + tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor6, PatchField, GeoMesh>& res,
	         const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor6>& dt2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor6>& dt2)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1, const diagTensor6& t2)
	{
		return gf1 + dimensioned<diagTensor6>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor6>& dt2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + dt2.name() + ')', gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf1, const diagTensor6& t2)
	{
		return tgf1 + dimensioned<diagTensor6>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor6, PatchField, GeoMesh>& res, const dimensioned<diagTensor6>& dt1,
	              const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(const dimensioned<diagTensor6>& dt1,
	                                                                 const GeometricField<diagTensor6, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(const diagTensor6& t1,
	                                                                 const GeometricField<diagTensor6, PatchField, GeoMesh>
	                                                                 & gf2) { return dimensioned<diagTensor6>(t1) - gf2; }

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(const dimensioned<diagTensor6>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '-' + gf2.name() + ')', dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(const diagTensor6& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor6, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<diagTensor6>(t1) - tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor6, PatchField, GeoMesh>& res,
	              const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor6>& dt2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor6>& dt2)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1, const diagTensor6& t2)
	{
		return gf1 - dimensioned<diagTensor6>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor6>& dt2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '-' + dt2.name() + ')', gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf1, const diagTensor6& t2)
	{
		return tgf1 - dimensioned<diagTensor6>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor6, PatchField, GeoMesh>& res,
	         const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf1,
	         const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf1,
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<sphericalTensor6, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, sphericalTensor6, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor6, sphericalTensor6, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<sphericalTensor6, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor6, sphericalTensor6, sphericalTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor6, sphericalTensor6, sphericalTensor6, diagTensor6, PatchField, GeoMesh>::
			clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor6, PatchField, GeoMesh>& res,
	              const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf1,
	              const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf1,
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<sphericalTensor6, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, sphericalTensor6, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor6, sphericalTensor6, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<sphericalTensor6, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor6, sphericalTensor6, sphericalTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor6, sphericalTensor6, sphericalTensor6, diagTensor6, PatchField, GeoMesh>::
			clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor6, PatchField, GeoMesh>& res, const dimensioned<sphericalTensor6>& dt1,
	         const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::add(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(const dimensioned<sphericalTensor6>& dt1,
	                                                                 const GeometricField<diagTensor6, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(const sphericalTensor6& t1,
	                                                                 const GeometricField<diagTensor6, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		return dimensioned<sphericalTensor6>(t1) + gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(const dimensioned<sphericalTensor6>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '+' + gf2.name() + ')', dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(const sphericalTensor6& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor6, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<sphericalTensor6>(t1) + tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor6, PatchField, GeoMesh>& res,
	         const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor6>& dt2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor6>& dt2)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf1, const diagTensor6& t2)
	{
		return gf1 + dimensioned<diagTensor6>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<sphericalTensor6, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor6>& dt2)
	{
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, sphericalTensor6, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + dt2.name() + ')', gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor6, sphericalTensor6, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<sphericalTensor6, PatchField, GeoMesh>>& tgf1, const diagTensor6& t2)
	{
		return tgf1 + dimensioned<diagTensor6>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor6, PatchField, GeoMesh>& res, const dimensioned<sphericalTensor6>& dt1,
	              const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(const dimensioned<sphericalTensor6>& dt1,
	                                                                 const GeometricField<diagTensor6, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(const sphericalTensor6& t1,
	                                                                 const GeometricField<diagTensor6, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		return dimensioned<sphericalTensor6>(t1) - gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(const dimensioned<sphericalTensor6>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '-' + gf2.name() + ')', dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(const sphericalTensor6& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor6, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<sphericalTensor6>(t1) - tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor6, PatchField, GeoMesh>& res,
	              const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor6>& dt2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor6>& dt2)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf1, const diagTensor6& t2)
	{
		return gf1 - dimensioned<diagTensor6>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<sphericalTensor6, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor6>& dt2)
	{
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, sphericalTensor6, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '-' + dt2.name() + ')', gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor6, sphericalTensor6, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<sphericalTensor6, PatchField, GeoMesh>>& tgf1, const diagTensor6& t2)
	{
		return tgf1 - dimensioned<diagTensor6>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor6, PatchField, GeoMesh>& res,
	         const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1,
	         const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1,
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<sphericalTensor6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, sphericalTensor6, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor6, sphericalTensor6, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf1,
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<sphericalTensor6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor6, diagTensor6, diagTensor6, sphericalTensor6, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor6, diagTensor6, diagTensor6, sphericalTensor6, PatchField, GeoMesh>::
			clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor6, PatchField, GeoMesh>& res,
	              const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1,
	              const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1,
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<sphericalTensor6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, sphericalTensor6, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor6, sphericalTensor6, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf1,
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<sphericalTensor6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor6, diagTensor6, diagTensor6, sphericalTensor6, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor6, diagTensor6, diagTensor6, sphericalTensor6, PatchField, GeoMesh>::
			clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor6, PatchField, GeoMesh>& res, const dimensioned<diagTensor6>& dt1,
	         const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::add(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(const dimensioned<diagTensor6>& dt1,
	                                                                 const GeometricField<
		                                                                 sphericalTensor6, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(const diagTensor6& t1,
	                                                                 const GeometricField<
		                                                                 sphericalTensor6, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<diagTensor6>(t1) + gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(const dimensioned<diagTensor6>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 sphericalTensor6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, sphericalTensor6, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '+' + gf2.name() + ')', dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor6, sphericalTensor6, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(const diagTensor6& t1,
	                                                                 const tmp<GeometricField<
		                                                                 sphericalTensor6, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<diagTensor6>(t1) + tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor6, PatchField, GeoMesh>& res,
	         const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1, const dimensioned<sphericalTensor6>& dt2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1, const dimensioned<sphericalTensor6>& dt2)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1, const sphericalTensor6& t2)
	{
		return gf1 + dimensioned<sphericalTensor6>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf1, const dimensioned<sphericalTensor6>& dt2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + dt2.name() + ')', gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf1, const sphericalTensor6& t2)
	{
		return tgf1 + dimensioned<sphericalTensor6>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor6, PatchField, GeoMesh>& res, const dimensioned<diagTensor6>& dt1,
	              const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(const dimensioned<diagTensor6>& dt1,
	                                                                 const GeometricField<
		                                                                 sphericalTensor6, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(const diagTensor6& t1,
	                                                                 const GeometricField<
		                                                                 sphericalTensor6, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<diagTensor6>(t1) - gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(const dimensioned<diagTensor6>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 sphericalTensor6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, sphericalTensor6, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '+' + gf2.name() + ')', dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor6, sphericalTensor6, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(const diagTensor6& t1,
	                                                                 const tmp<GeometricField<
		                                                                 sphericalTensor6, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<diagTensor6>(t1) - tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor6, PatchField, GeoMesh>& res,
	              const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1, const dimensioned<sphericalTensor6>& dt2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1, const dimensioned<sphericalTensor6>& dt2)
	{
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor6, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1, const sphericalTensor6& t2)
	{
		return gf1 - dimensioned<sphericalTensor6>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf1, const dimensioned<sphericalTensor6>& dt2)
	{
		const GeometricField<diagTensor6, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + dt2.name() + ')', gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor6, diagTensor6, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor6, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor6, PatchField, GeoMesh>>& tgf1, const sphericalTensor6& t2)
	{
		return tgf1 - dimensioned<sphericalTensor6>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void inv(GeometricField<diagTensor8, PatchField, GeoMesh>& res,
	         const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1)
	{
		tnbLib::inv(res.internalField(), gf1.internalField());
		tnbLib::inv(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> inv(const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject("inv" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			inv(gf1.dimensions())));
		tnbLib::inv(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> inv(
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf1, "inv" "(" + gf1.name() + ')', inv(gf1.dimensions())));
		tnbLib::inv(tRes(), gf1);
		reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void diag(GeometricField<diagTensor8, PatchField, GeoMesh>& res,
	          const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1)
	{
		tnbLib::diag(res.internalField(), gf1.internalField());
		tnbLib::diag(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> diag(const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject("diag" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			diag(gf1.dimensions())));
		tnbLib::diag(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> diag(
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf1, "diag" "(" + gf1.name() + ')', diag(gf1.dimensions())));
		tnbLib::diag(tRes(), gf1);
		reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void contractScalar(GeometricField<scalar, PatchField, GeoMesh>& res,
	                    const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1)
	{
		tnbLib::contractScalar(res.internalField(), gf1.internalField());
		tnbLib::contractScalar(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> contractScalar(
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("contractScalar" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), contractScalar(gf1.dimensions())));
		tnbLib::contractScalar(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> contractScalar(
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, diagTensor8, PatchField, GeoMesh>::New(
				tgf1, "contractScalar" "(" + gf1.name() + ')', contractScalar(gf1.dimensions())));
		tnbLib::contractScalar(tRes(), gf1);
		reuseTmpGeometricField<scalar, diagTensor8, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void contractLinear(GeometricField<vector8, PatchField, GeoMesh>& res,
	                    const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1)
	{
		tnbLib::contractLinear(res.internalField(), gf1.internalField());
		tnbLib::contractLinear(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> contractLinear(
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(new GeometricField<vector8, PatchField, GeoMesh>(
			IOobject("contractLinear" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), contractLinear(gf1.dimensions())));
		tnbLib::contractLinear(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> contractLinear(
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector8, diagTensor8, PatchField, GeoMesh>::New(
				tgf1, "contractLinear" "(" + gf1.name() + ')', contractLinear(gf1.dimensions())));
		tnbLib::contractLinear(tRes(), gf1);
		reuseTmpGeometricField<vector8, diagTensor8, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<diagTensor8, PatchField, GeoMesh>& res,
	              const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	              const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		tnbLib::multiply(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::multiply(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator *(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1, const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '*' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator *(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '*' + gf2.name() + ')', gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, scalar, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '*' + gf2.name() + ')', gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor8, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor8, scalar, scalar, diagTensor8, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '*' + gf2.name() + ')', gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor8, scalar, scalar, diagTensor8, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<diagTensor8, PatchField, GeoMesh>& res, const dimensioned<scalar>& dt1,
	              const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		tnbLib::multiply(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::multiply(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator *(const dimensioned<scalar>& dt1,
	                                                                 const GeometricField<diagTensor8, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '*' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator *(const scalar& t1,
	                                                                 const GeometricField<diagTensor8, PatchField, GeoMesh>
	                                                                 & gf2) { return dimensioned<scalar>(t1) * gf2; }

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator *(const dimensioned<scalar>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '*' + gf2.name() + ')', dt1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator *(const scalar& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor8, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<scalar>(t1) * tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<diagTensor8, PatchField, GeoMesh>& res,
	              const GeometricField<scalar, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor8>& dt2)
	{
		tnbLib::multiply(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::multiply(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator *(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor8>& dt2)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '*' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() * dt2.dimensions()));
		tnbLib::multiply(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator *(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1, const diagTensor8& t2)
	{
		return gf1 * dimensioned<diagTensor8>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor8>& dt2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, scalar, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '*' + dt2.name() + ')', gf1.dimensions() * dt2.dimensions()));
		tnbLib::multiply(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor8, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const diagTensor8& t2)
	{
		return tgf1 * dimensioned<diagTensor8>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor8, PatchField, GeoMesh>& res,
	            const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	            const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1, const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, scalar, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor8, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor8, scalar, scalar, diagTensor8, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor8, scalar, scalar, diagTensor8, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor8, PatchField, GeoMesh>& res, const dimensioned<scalar>& dt1,
	            const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
	                                                                 const GeometricField<diagTensor8, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(const scalar& t1,
	                                                                 const GeometricField<diagTensor8, PatchField, GeoMesh>
	                                                                 & gf2) { return dimensioned<scalar>(t1) / gf2; }

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '|' + gf2.name() + ')', dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(const scalar& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor8, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<scalar>(t1) / tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor8, PatchField, GeoMesh>& res,
	            const GeometricField<scalar, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor8>& dt2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor8>& dt2)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(
		const GeometricField<scalar, PatchField, GeoMesh>& gf1, const diagTensor8& t2)
	{
		return gf1 / dimensioned<diagTensor8>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor8>& dt2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, scalar, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + dt2.name() + ')', gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor8, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const diagTensor8& t2)
	{
		return tgf1 / dimensioned<diagTensor8>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<vector8, PatchField, GeoMesh>& res, const GeometricField<vector8, PatchField, GeoMesh>& gf1,
	            const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator /(const GeometricField<vector8, PatchField, GeoMesh>& gf1,
	                                                             const GeometricField<diagTensor8, PatchField, GeoMesh>&
	                                                             gf2)
	{
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(new GeometricField<vector8, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator /(const GeometricField<vector8, PatchField, GeoMesh>& gf1,
	                                                             const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>
	                                                             >& tgf2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector8, diagTensor8, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector8, diagTensor8, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<vector8, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<vector8, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '|' + gf2.name() + ')',
			                                                                   gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<vector8, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<vector8, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<vector8, vector8, vector8, diagTensor8, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<vector8, vector8, vector8, diagTensor8, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<vector8, PatchField, GeoMesh>& res, const dimensioned<vector8>& dt1,
	            const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator /(const dimensioned<vector8>& dt1,
	                                                             const GeometricField<diagTensor8, PatchField, GeoMesh>&
	                                                             gf2)
	{
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(new GeometricField<vector8, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator /(const vector8& t1,
	                                                             const GeometricField<diagTensor8, PatchField, GeoMesh>&
	                                                             gf2) { return dimensioned<vector8>(t1) / gf2; }

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator /(const dimensioned<vector8>& dt1,
	                                                             const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>
	                                                             >& tgf2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector8, diagTensor8, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '|' + gf2.name() + ')', dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		reuseTmpGeometricField<vector8, diagTensor8, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator /(const vector8& t1,
	                                                             const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>
	                                                             >& tgf2) { return dimensioned<vector8>(t1) / tgf2; }

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<vector8, PatchField, GeoMesh>& res, const GeometricField<vector8, PatchField, GeoMesh>& gf1,
	            const dimensioned<diagTensor8>& dt2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator /(const GeometricField<vector8, PatchField, GeoMesh>& gf1,
	                                                             const dimensioned<diagTensor8>& dt2)
	{
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(new GeometricField<vector8, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator /(const GeometricField<vector8, PatchField, GeoMesh>& gf1,
	                                                             const diagTensor8& t2)
	{
		return gf1 / dimensioned<diagTensor8>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<vector8, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor8>& dt2)
	{
		const GeometricField<vector8, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '|' + dt2.name() + ')',
			                                                                   gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<vector8, PatchField, GeoMesh>>& tgf1, const diagTensor8& t2)
	{
		return tgf1 / dimensioned<diagTensor8>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor8, PatchField, GeoMesh>& res,
	            const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1,
	            const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1,
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor8, diagTensor8, diagTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor8, diagTensor8, diagTensor8, diagTensor8, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor8, PatchField, GeoMesh>& res, const dimensioned<diagTensor8>& dt1,
	            const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(const dimensioned<diagTensor8>& dt1,
	                                                                 const GeometricField<diagTensor8, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(const diagTensor8& t1,
	                                                                 const GeometricField<diagTensor8, PatchField, GeoMesh>
	                                                                 & gf2) { return dimensioned<diagTensor8>(t1) / gf2; }

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(const dimensioned<diagTensor8>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '|' + gf2.name() + ')', dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(const diagTensor8& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor8, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<diagTensor8>(t1) / tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor8, PatchField, GeoMesh>& res,
	            const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor8>& dt2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor8>& dt2)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1, const diagTensor8& t2)
	{
		return gf1 / dimensioned<diagTensor8>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor8>& dt2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + dt2.name() + ')', gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf1, const diagTensor8& t2)
	{
		return tgf1 / dimensioned<diagTensor8>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor8, PatchField, GeoMesh>& res,
	            const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf1,
	            const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf1,
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<sphericalTensor8, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, sphericalTensor8, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor8, sphericalTensor8, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<sphericalTensor8, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor8, sphericalTensor8, sphericalTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor8, sphericalTensor8, sphericalTensor8, diagTensor8, PatchField, GeoMesh>::
			clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor8, PatchField, GeoMesh>& res, const dimensioned<sphericalTensor8>& dt1,
	            const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(const dimensioned<sphericalTensor8>& dt1,
	                                                                 const GeometricField<diagTensor8, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(const sphericalTensor8& t1,
	                                                                 const GeometricField<diagTensor8, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		return dimensioned<sphericalTensor8>(t1) / gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(const dimensioned<sphericalTensor8>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '|' + gf2.name() + ')', dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(const sphericalTensor8& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor8, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<sphericalTensor8>(t1) / tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor8, PatchField, GeoMesh>& res,
	            const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor8>& dt2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor8>& dt2)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf1, const diagTensor8& t2)
	{
		return gf1 / dimensioned<diagTensor8>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<sphericalTensor8, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor8>& dt2)
	{
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, sphericalTensor8, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + dt2.name() + ')', gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor8, sphericalTensor8, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<sphericalTensor8, PatchField, GeoMesh>>& tgf1, const diagTensor8& t2)
	{
		return tgf1 / dimensioned<diagTensor8>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor8, PatchField, GeoMesh>& res,
	            const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1,
	            const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1,
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<sphericalTensor8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, sphericalTensor8, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor8, sphericalTensor8, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf1,
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<sphericalTensor8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor8, diagTensor8, diagTensor8, sphericalTensor8, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor8, diagTensor8, diagTensor8, sphericalTensor8, PatchField, GeoMesh>::
			clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor8, PatchField, GeoMesh>& res, const dimensioned<diagTensor8>& dt1,
	            const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(const dimensioned<diagTensor8>& dt1,
	                                                                 const GeometricField<
		                                                                 sphericalTensor8, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(const diagTensor8& t1,
	                                                                 const GeometricField<
		                                                                 sphericalTensor8, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<diagTensor8>(t1) / gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(const dimensioned<diagTensor8>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 sphericalTensor8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, sphericalTensor8, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '|' + gf2.name() + ')', dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor8, sphericalTensor8, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(const diagTensor8& t1,
	                                                                 const tmp<GeometricField<
		                                                                 sphericalTensor8, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<diagTensor8>(t1) / tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<diagTensor8, PatchField, GeoMesh>& res,
	            const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1, const dimensioned<sphericalTensor8>& dt2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1, const dimensioned<sphericalTensor8>& dt2)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1, const sphericalTensor8& t2)
	{
		return gf1 / dimensioned<sphericalTensor8>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf1, const dimensioned<sphericalTensor8>& dt2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '|' + dt2.name() + ')', gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf1, const sphericalTensor8& t2)
	{
		return tgf1 / dimensioned<sphericalTensor8>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor8, PatchField, GeoMesh>& res,
	         const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1,
	         const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1,
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor8, diagTensor8, diagTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor8, diagTensor8, diagTensor8, diagTensor8, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor8, PatchField, GeoMesh>& res,
	              const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1,
	              const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1,
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor8, diagTensor8, diagTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor8, diagTensor8, diagTensor8, diagTensor8, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor8, PatchField, GeoMesh>& res, const dimensioned<diagTensor8>& dt1,
	         const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::add(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(const dimensioned<diagTensor8>& dt1,
	                                                                 const GeometricField<diagTensor8, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(const diagTensor8& t1,
	                                                                 const GeometricField<diagTensor8, PatchField, GeoMesh>
	                                                                 & gf2) { return dimensioned<diagTensor8>(t1) + gf2; }

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(const dimensioned<diagTensor8>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '+' + gf2.name() + ')', dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(const diagTensor8& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor8, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<diagTensor8>(t1) + tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor8, PatchField, GeoMesh>& res,
	         const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor8>& dt2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor8>& dt2)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1, const diagTensor8& t2)
	{
		return gf1 + dimensioned<diagTensor8>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor8>& dt2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + dt2.name() + ')', gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf1, const diagTensor8& t2)
	{
		return tgf1 + dimensioned<diagTensor8>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor8, PatchField, GeoMesh>& res, const dimensioned<diagTensor8>& dt1,
	              const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(const dimensioned<diagTensor8>& dt1,
	                                                                 const GeometricField<diagTensor8, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(const diagTensor8& t1,
	                                                                 const GeometricField<diagTensor8, PatchField, GeoMesh>
	                                                                 & gf2) { return dimensioned<diagTensor8>(t1) - gf2; }

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(const dimensioned<diagTensor8>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '-' + gf2.name() + ')', dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(const diagTensor8& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor8, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<diagTensor8>(t1) - tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor8, PatchField, GeoMesh>& res,
	              const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor8>& dt2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor8>& dt2)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1, const diagTensor8& t2)
	{
		return gf1 - dimensioned<diagTensor8>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor8>& dt2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '-' + dt2.name() + ')', gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf1, const diagTensor8& t2)
	{
		return tgf1 - dimensioned<diagTensor8>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor8, PatchField, GeoMesh>& res,
	         const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf1,
	         const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf1,
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<sphericalTensor8, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, sphericalTensor8, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor8, sphericalTensor8, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<sphericalTensor8, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor8, sphericalTensor8, sphericalTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor8, sphericalTensor8, sphericalTensor8, diagTensor8, PatchField, GeoMesh>::
			clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor8, PatchField, GeoMesh>& res,
	              const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf1,
	              const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf1,
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<sphericalTensor8, PatchField, GeoMesh>>& tgf1,
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, sphericalTensor8, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor8, sphericalTensor8, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<sphericalTensor8, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor8, sphericalTensor8, sphericalTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor8, sphericalTensor8, sphericalTensor8, diagTensor8, PatchField, GeoMesh>::
			clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor8, PatchField, GeoMesh>& res, const dimensioned<sphericalTensor8>& dt1,
	         const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::add(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(const dimensioned<sphericalTensor8>& dt1,
	                                                                 const GeometricField<diagTensor8, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(const sphericalTensor8& t1,
	                                                                 const GeometricField<diagTensor8, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		return dimensioned<sphericalTensor8>(t1) + gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(const dimensioned<sphericalTensor8>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '+' + gf2.name() + ')', dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(const sphericalTensor8& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor8, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<sphericalTensor8>(t1) + tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor8, PatchField, GeoMesh>& res,
	         const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor8>& dt2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor8>& dt2)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf1, const diagTensor8& t2)
	{
		return gf1 + dimensioned<diagTensor8>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<sphericalTensor8, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor8>& dt2)
	{
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, sphericalTensor8, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + dt2.name() + ')', gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor8, sphericalTensor8, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<sphericalTensor8, PatchField, GeoMesh>>& tgf1, const diagTensor8& t2)
	{
		return tgf1 + dimensioned<diagTensor8>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor8, PatchField, GeoMesh>& res, const dimensioned<sphericalTensor8>& dt1,
	              const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(const dimensioned<sphericalTensor8>& dt1,
	                                                                 const GeometricField<diagTensor8, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(const sphericalTensor8& t1,
	                                                                 const GeometricField<diagTensor8, PatchField, GeoMesh>
	                                                                 & gf2)
	{
		return dimensioned<sphericalTensor8>(t1) - gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(const dimensioned<sphericalTensor8>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '-' + gf2.name() + ')', dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(const sphericalTensor8& t1,
	                                                                 const tmp<GeometricField<
		                                                                 diagTensor8, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<sphericalTensor8>(t1) - tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor8, PatchField, GeoMesh>& res,
	              const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor8>& dt2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf1, const dimensioned<diagTensor8>& dt2)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf1, const diagTensor8& t2)
	{
		return gf1 - dimensioned<diagTensor8>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<sphericalTensor8, PatchField, GeoMesh>>& tgf1, const dimensioned<diagTensor8>& dt2)
	{
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, sphericalTensor8, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '-' + dt2.name() + ')', gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor8, sphericalTensor8, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<sphericalTensor8, PatchField, GeoMesh>>& tgf1, const diagTensor8& t2)
	{
		return tgf1 - dimensioned<diagTensor8>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor8, PatchField, GeoMesh>& res,
	         const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1,
	         const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1,
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<sphericalTensor8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, sphericalTensor8, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor8, sphericalTensor8, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf1,
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<sphericalTensor8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor8, diagTensor8, diagTensor8, sphericalTensor8, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor8, diagTensor8, diagTensor8, sphericalTensor8, PatchField, GeoMesh>::
			clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor8, PatchField, GeoMesh>& res,
	              const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1,
	              const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1,
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<sphericalTensor8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, sphericalTensor8, PatchField, GeoMesh>::New(
				tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor8, sphericalTensor8, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf1,
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<sphericalTensor8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<diagTensor8, diagTensor8, diagTensor8, sphericalTensor8, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<diagTensor8, diagTensor8, diagTensor8, sphericalTensor8, PatchField, GeoMesh>::
			clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor8, PatchField, GeoMesh>& res, const dimensioned<diagTensor8>& dt1,
	         const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::add(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(const dimensioned<diagTensor8>& dt1,
	                                                                 const GeometricField<
		                                                                 sphericalTensor8, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(const diagTensor8& t1,
	                                                                 const GeometricField<
		                                                                 sphericalTensor8, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<diagTensor8>(t1) + gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(const dimensioned<diagTensor8>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 sphericalTensor8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, sphericalTensor8, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '+' + gf2.name() + ')', dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor8, sphericalTensor8, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(const diagTensor8& t1,
	                                                                 const tmp<GeometricField<
		                                                                 sphericalTensor8, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<diagTensor8>(t1) + tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<diagTensor8, PatchField, GeoMesh>& res,
	         const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1, const dimensioned<sphericalTensor8>& dt2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1, const dimensioned<sphericalTensor8>& dt2)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1, const sphericalTensor8& t2)
	{
		return gf1 + dimensioned<sphericalTensor8>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf1, const dimensioned<sphericalTensor8>& dt2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + dt2.name() + ')', gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf1, const sphericalTensor8& t2)
	{
		return tgf1 + dimensioned<sphericalTensor8>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor8, PatchField, GeoMesh>& res, const dimensioned<diagTensor8>& dt1,
	              const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(const dimensioned<diagTensor8>& dt1,
	                                                                 const GeometricField<
		                                                                 sphericalTensor8, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(const diagTensor8& t1,
	                                                                 const GeometricField<
		                                                                 sphericalTensor8, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<diagTensor8>(t1) - gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(const dimensioned<diagTensor8>& dt1,
	                                                                 const tmp<GeometricField<
		                                                                 sphericalTensor8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<sphericalTensor8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, sphericalTensor8, PatchField, GeoMesh>::New(
				tgf2, '(' + dt1.name() + '+' + gf2.name() + ')', dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		reuseTmpGeometricField<diagTensor8, sphericalTensor8, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(const diagTensor8& t1,
	                                                                 const tmp<GeometricField<
		                                                                 sphericalTensor8, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<diagTensor8>(t1) - tgf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<diagTensor8, PatchField, GeoMesh>& res,
	              const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1, const dimensioned<sphericalTensor8>& dt2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1, const dimensioned<sphericalTensor8>& dt2)
	{
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(new GeometricField<diagTensor8, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1, const sphericalTensor8& t2)
	{
		return gf1 - dimensioned<sphericalTensor8>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf1, const dimensioned<sphericalTensor8>& dt2)
	{
		const GeometricField<diagTensor8, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::New(
				tgf1, '(' + gf1.name() + '+' + dt2.name() + ')', gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		reuseTmpGeometricField<diagTensor8, diagTensor8, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<diagTensor8, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<diagTensor8, PatchField, GeoMesh>>& tgf1, const sphericalTensor8& t2)
	{
		return tgf1 - dimensioned<sphericalTensor8>(t2);
	}

}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#undef DiagTensorN_FieldFunctions

#include <undefFieldFunctionsM.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// ************************************************************************* //