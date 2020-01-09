#include <GeometricVectorNFields.hxx>

#define TEMPLATE template<template<class> class PatchField, class GeoMesh>
#include <GeometricFieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define VectorN_FieldFunctions(tensorType, diagTensorType, sphericalTensorType, vectorType, CmptType, args) \
                                                                                \
UNARY_FUNCTION(CmptType, vectorType, cmptSum, cmptSum)                          \
                                                                                \
BINARY_FUNCTION(vectorType, vectorType, vectorType, cmptMultiply)               \
BINARY_TYPE_FUNCTION(vectorType, vectorType, vectorType, cmptMultiply)          \
                                                                                \
BINARY_OPERATOR(vectorType, CmptType, vectorType, *,'*',multiply)               \
BINARY_TYPE_OPERATOR(vectorType, CmptType, vectorType, *,'*',multiply)          \
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

	template <template<class> class PatchField, class GeoMesh>
	void cmptSum(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<vector2, PatchField, GeoMesh>& gf1)
	{
		tnbLib::cmptSum(res.internalField(), gf1.internalField());
		tnbLib::cmptSum(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> cmptSum(const GeometricField<vector2, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("cmptSum" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), cmptSum(gf1.dimensions())));
		tnbLib::cmptSum(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> cmptSum(const tmp<GeometricField<vector2, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<vector2, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, vector2, PatchField, GeoMesh>::New(tgf1, "cmptSum" "(" + gf1.name() + ')',
			                                                                  cmptSum(gf1.dimensions())));
		tnbLib::cmptSum(tRes(), gf1);
		reuseTmpGeometricField<scalar, vector2, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void cmptMultiply(GeometricField<vector2, PatchField, GeoMesh>& res,
	                  const GeometricField<vector2, PatchField, GeoMesh>& gf1,
	                  const GeometricField<vector2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::cmptMultiply(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::cmptMultiply(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> cmptMultiply(const GeometricField<vector2, PatchField, GeoMesh>& gf1,
	                                                               const GeometricField<vector2, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(new GeometricField<vector2, PatchField, GeoMesh>(
			IOobject("cmptMultiply" "(" + gf1.name() + ',' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ,
			         IOobject::NO_WRITE), gf1.mesh(), cmptMultiply(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> cmptMultiply(const GeometricField<vector2, PatchField, GeoMesh>& gf1,
	                                                               const tmp<GeometricField<vector2, PatchField, GeoMesh>>&
	                                                               tgf2)
	{
		const GeometricField<vector2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::New(
				tgf2, "cmptMultiply" "(" + gf1.name() + ',' + gf2.name() + ')', cmptMultiply(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> cmptMultiply(
		const tmp<GeometricField<vector2, PatchField, GeoMesh>>& tgf1,
		const GeometricField<vector2, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<vector2, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::New(
				tgf1, "cmptMultiply" "(" + gf1.name() + ',' + gf2.name() + ')', cmptMultiply(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> cmptMultiply(
		const tmp<GeometricField<vector2, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<vector2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<vector2, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<vector2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<vector2, vector2, vector2, vector2, PatchField, GeoMesh>::New(
				tgf1, tgf2, "cmptMultiply" "(" + gf1.name() + ',' + gf2.name() + ')',
				cmptMultiply(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<vector2, vector2, vector2, vector2, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void cmptMultiply(GeometricField<vector2, PatchField, GeoMesh>& res, const dimensioned<vector2>& dt1,
	                  const GeometricField<vector2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::cmptMultiply(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::cmptMultiply(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> cmptMultiply(const dimensioned<vector2>& dt1,
	                                                               const GeometricField<vector2, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(new GeometricField<vector2, PatchField, GeoMesh>(
			IOobject("cmptMultiply" "(" + dt1.name() + ',' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ,
			         IOobject::NO_WRITE), gf2.mesh(), cmptMultiply(dt1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> cmptMultiply(const vector2& t1,
	                                                               const GeometricField<vector2, PatchField, GeoMesh>& gf2)
	{
		return cmptMultiply(dimensioned<vector2>(t1), gf2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> cmptMultiply(const dimensioned<vector2>& dt1,
	                                                               const tmp<GeometricField<vector2, PatchField, GeoMesh>>&
	                                                               tgf2)
	{
		const GeometricField<vector2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::New(
				tgf2, "cmptMultiply" "(" + dt1.name() + gf2.name() + ',' + ')', cmptMultiply(dt1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), dt1, gf2);
		reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> cmptMultiply(const vector2& t1,
	                                                               const tmp<GeometricField<vector2, PatchField, GeoMesh>>&
	                                                               tgf2)
	{
		return cmptMultiply(dimensioned<vector2>(t1), tgf2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void cmptMultiply(GeometricField<vector2, PatchField, GeoMesh>& res,
	                  const GeometricField<vector2, PatchField, GeoMesh>& gf1, const dimensioned<vector2>& dt2)
	{
		tnbLib::cmptMultiply(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::cmptMultiply(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> cmptMultiply(const GeometricField<vector2, PatchField, GeoMesh>& gf1,
	                                                               const dimensioned<vector2>& dt2)
	{
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(new GeometricField<vector2, PatchField, GeoMesh>(
			IOobject("cmptMultiply" "(" + gf1.name() + ',' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ,
			         IOobject::NO_WRITE), gf1.mesh(), cmptMultiply(gf1.dimensions(), dt2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> cmptMultiply(const GeometricField<vector2, PatchField, GeoMesh>& gf1,
	                                                               const vector2& t2)
	{
		return cmptMultiply(gf1, dimensioned<vector2>(t2));
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> cmptMultiply(
		const tmp<GeometricField<vector2, PatchField, GeoMesh>>& tgf1, const dimensioned<vector2>& dt2)
	{
		const GeometricField<vector2, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::New(
				tgf1, "cmptMultiply" "(" + gf1.name() + ',' + dt2.name() + ')', cmptMultiply(gf1.dimensions(), dt2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, dt2);
		reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> cmptMultiply(
		const tmp<GeometricField<vector2, PatchField, GeoMesh>>& tgf1, const vector2& t2)
	{
		return cmptMultiply(tgf1, dimensioned<vector2>(t2));
	}

	template <template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<vector2, PatchField, GeoMesh>& res,
	              const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	              const GeometricField<vector2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::multiply(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::multiply(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator *(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const GeometricField<vector2, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(new GeometricField<vector2, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '*' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator *(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const tmp<GeometricField<vector2, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + '*' + gf2.name() + ')',
			                                                                   gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const GeometricField<vector2, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector2, scalar, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '*' + gf2.name() + ')',
			                                                                  gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector2, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<vector2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<vector2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<vector2, scalar, scalar, vector2, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '*' + gf2.name() + ')', gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<vector2, scalar, scalar, vector2, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<vector2, PatchField, GeoMesh>& res, const dimensioned<scalar>& dt1,
	              const GeometricField<vector2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::multiply(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::multiply(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator *(const dimensioned<scalar>& dt1,
	                                                             const GeometricField<vector2, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(new GeometricField<vector2, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '*' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator *(const scalar& t1,
	                                                             const GeometricField<vector2, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<scalar>(t1) * gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator *(const dimensioned<scalar>& dt1,
	                                                             const tmp<GeometricField<vector2, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::New(tgf2, '(' + dt1.name() + '*' + gf2.name() + ')',
			                                                                   dt1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), dt1, gf2);
		reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator *(const scalar& t1,
	                                                             const tmp<GeometricField<vector2, PatchField, GeoMesh>>&
	                                                             tgf2) { return dimensioned<scalar>(t1) * tgf2; }

	template <template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<vector2, PatchField, GeoMesh>& res,
	              const GeometricField<scalar, PatchField, GeoMesh>& gf1, const dimensioned<vector2>& dt2)
	{
		tnbLib::multiply(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::multiply(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator *(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const dimensioned<vector2>& dt2)
	{
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(new GeometricField<vector2, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '*' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() * dt2.dimensions()));
		tnbLib::multiply(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator *(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const vector2& t2)
	{
		return gf1 * dimensioned<vector2>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const dimensioned<vector2>& dt2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector2, scalar, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '*' + dt2.name() + ')',
			                                                                  gf1.dimensions() * dt2.dimensions()));
		tnbLib::multiply(tRes(), gf1, dt2);
		reuseTmpGeometricField<vector2, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const vector2& t2)
	{
		return tgf1 * dimensioned<vector2>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<vector2, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	            const GeometricField<vector2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator /(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const GeometricField<vector2, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(new GeometricField<vector2, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator /(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const tmp<GeometricField<vector2, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + '|' + gf2.name() + ')',
			                                                                   gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const GeometricField<vector2, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector2, scalar, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '|' + gf2.name() + ')',
			                                                                  gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector2, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<vector2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<vector2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<vector2, scalar, scalar, vector2, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<vector2, scalar, scalar, vector2, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<vector2, PatchField, GeoMesh>& res, const dimensioned<scalar>& dt1,
	            const GeometricField<vector2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
	                                                             const GeometricField<vector2, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(new GeometricField<vector2, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator /(const scalar& t1,
	                                                             const GeometricField<vector2, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<scalar>(t1) / gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
	                                                             const tmp<GeometricField<vector2, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::New(tgf2, '(' + dt1.name() + '|' + gf2.name() + ')',
			                                                                   dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator /(const scalar& t1,
	                                                             const tmp<GeometricField<vector2, PatchField, GeoMesh>>&
	                                                             tgf2) { return dimensioned<scalar>(t1) / tgf2; }

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<vector2, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	            const dimensioned<vector2>& dt2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator /(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const dimensioned<vector2>& dt2)
	{
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(new GeometricField<vector2, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator /(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const vector2& t2)
	{
		return gf1 / dimensioned<vector2>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const dimensioned<vector2>& dt2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector2, scalar, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '|' + dt2.name() + ')',
			                                                                  gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		reuseTmpGeometricField<vector2, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const vector2& t2)
	{
		return tgf1 / dimensioned<vector2>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<vector2, PatchField, GeoMesh>& res, const GeometricField<vector2, PatchField, GeoMesh>& gf1,
	         const GeometricField<vector2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator +(const GeometricField<vector2, PatchField, GeoMesh>& gf1,
	                                                             const GeometricField<vector2, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(new GeometricField<vector2, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator +(const GeometricField<vector2, PatchField, GeoMesh>& gf1,
	                                                             const tmp<GeometricField<vector2, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + '+' + gf2.name() + ')',
			                                                                   gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<vector2, PatchField, GeoMesh>>& tgf1,
		const GeometricField<vector2, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<vector2, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '+' + gf2.name() + ')',
			                                                                   gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<vector2, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<vector2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<vector2, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<vector2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<vector2, vector2, vector2, vector2, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<vector2, vector2, vector2, vector2, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<vector2, PatchField, GeoMesh>& res,
	              const GeometricField<vector2, PatchField, GeoMesh>& gf1,
	              const GeometricField<vector2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator -(const GeometricField<vector2, PatchField, GeoMesh>& gf1,
	                                                             const GeometricField<vector2, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(new GeometricField<vector2, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator -(const GeometricField<vector2, PatchField, GeoMesh>& gf1,
	                                                             const tmp<GeometricField<vector2, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + '-' + gf2.name() + ')',
			                                                                   gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<vector2, PatchField, GeoMesh>>& tgf1,
		const GeometricField<vector2, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<vector2, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '-' + gf2.name() + ')',
			                                                                   gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<vector2, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<vector2, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<vector2, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<vector2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<vector2, vector2, vector2, vector2, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<vector2, vector2, vector2, vector2, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<vector2, PatchField, GeoMesh>& res, const dimensioned<vector2>& dt1,
	         const GeometricField<vector2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::add(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator +(const dimensioned<vector2>& dt1,
	                                                             const GeometricField<vector2, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(new GeometricField<vector2, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator +(const vector2& t1,
	                                                             const GeometricField<vector2, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<vector2>(t1) + gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator +(const dimensioned<vector2>& dt1,
	                                                             const tmp<GeometricField<vector2, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::New(tgf2, '(' + dt1.name() + '+' + gf2.name() + ')',
			                                                                   dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator +(const vector2& t1,
	                                                             const tmp<GeometricField<vector2, PatchField, GeoMesh>>&
	                                                             tgf2) { return dimensioned<vector2>(t1) + tgf2; }

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<vector2, PatchField, GeoMesh>& res, const GeometricField<vector2, PatchField, GeoMesh>& gf1,
	         const dimensioned<vector2>& dt2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator +(const GeometricField<vector2, PatchField, GeoMesh>& gf1,
	                                                             const dimensioned<vector2>& dt2)
	{
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(new GeometricField<vector2, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator +(const GeometricField<vector2, PatchField, GeoMesh>& gf1,
	                                                             const vector2& t2)
	{
		return gf1 + dimensioned<vector2>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<vector2, PatchField, GeoMesh>>& tgf1, const dimensioned<vector2>& dt2)
	{
		const GeometricField<vector2, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '+' + dt2.name() + ')',
			                                                                   gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<vector2, PatchField, GeoMesh>>& tgf1, const vector2& t2)
	{
		return tgf1 + dimensioned<vector2>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<vector2, PatchField, GeoMesh>& res, const dimensioned<vector2>& dt1,
	              const GeometricField<vector2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator -(const dimensioned<vector2>& dt1,
	                                                             const GeometricField<vector2, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(new GeometricField<vector2, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator -(const vector2& t1,
	                                                             const GeometricField<vector2, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<vector2>(t1) - gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator -(const dimensioned<vector2>& dt1,
	                                                             const tmp<GeometricField<vector2, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::New(tgf2, '(' + dt1.name() + '-' + gf2.name() + ')',
			                                                                   dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator -(const vector2& t1,
	                                                             const tmp<GeometricField<vector2, PatchField, GeoMesh>>&
	                                                             tgf2) { return dimensioned<vector2>(t1) - tgf2; }

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<vector2, PatchField, GeoMesh>& res,
	              const GeometricField<vector2, PatchField, GeoMesh>& gf1, const dimensioned<vector2>& dt2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator -(const GeometricField<vector2, PatchField, GeoMesh>& gf1,
	                                                             const dimensioned<vector2>& dt2)
	{
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(new GeometricField<vector2, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator -(const GeometricField<vector2, PatchField, GeoMesh>& gf1,
	                                                             const vector2& t2)
	{
		return gf1 - dimensioned<vector2>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<vector2, PatchField, GeoMesh>>& tgf1, const dimensioned<vector2>& dt2)
	{
		const GeometricField<vector2, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector2, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '-' + dt2.name() + ')',
			                                                                   gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		reuseTmpGeometricField<vector2, vector2, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector2, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<vector2, PatchField, GeoMesh>>& tgf1, const vector2& t2)
	{
		return tgf1 - dimensioned<vector2>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void cmptSum(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<vector3, PatchField, GeoMesh>& gf1)
	{
		tnbLib::cmptSum(res.internalField(), gf1.internalField());
		tnbLib::cmptSum(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> cmptSum(const GeometricField<vector3, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("cmptSum" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), cmptSum(gf1.dimensions())));
		tnbLib::cmptSum(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> cmptSum(const tmp<GeometricField<vector3, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<vector3, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, vector3, PatchField, GeoMesh>::New(tgf1, "cmptSum" "(" + gf1.name() + ')',
			                                                                  cmptSum(gf1.dimensions())));
		tnbLib::cmptSum(tRes(), gf1);
		reuseTmpGeometricField<scalar, vector3, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void cmptMultiply(GeometricField<vector3, PatchField, GeoMesh>& res,
	                  const GeometricField<vector3, PatchField, GeoMesh>& gf1,
	                  const GeometricField<vector3, PatchField, GeoMesh>& gf2)
	{
		tnbLib::cmptMultiply(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::cmptMultiply(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> cmptMultiply(const GeometricField<vector3, PatchField, GeoMesh>& gf1,
	                                                               const GeometricField<vector3, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(new GeometricField<vector3, PatchField, GeoMesh>(
			IOobject("cmptMultiply" "(" + gf1.name() + ',' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ,
			         IOobject::NO_WRITE), gf1.mesh(), cmptMultiply(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> cmptMultiply(const GeometricField<vector3, PatchField, GeoMesh>& gf1,
	                                                               const tmp<GeometricField<vector3, PatchField, GeoMesh>>&
	                                                               tgf2)
	{
		const GeometricField<vector3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::New(
				tgf2, "cmptMultiply" "(" + gf1.name() + ',' + gf2.name() + ')', cmptMultiply(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> cmptMultiply(
		const tmp<GeometricField<vector3, PatchField, GeoMesh>>& tgf1,
		const GeometricField<vector3, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<vector3, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::New(
				tgf1, "cmptMultiply" "(" + gf1.name() + ',' + gf2.name() + ')', cmptMultiply(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> cmptMultiply(
		const tmp<GeometricField<vector3, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<vector3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<vector3, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<vector3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<vector3, vector3, vector3, vector3, PatchField, GeoMesh>::New(
				tgf1, tgf2, "cmptMultiply" "(" + gf1.name() + ',' + gf2.name() + ')',
				cmptMultiply(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<vector3, vector3, vector3, vector3, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void cmptMultiply(GeometricField<vector3, PatchField, GeoMesh>& res, const dimensioned<vector3>& dt1,
	                  const GeometricField<vector3, PatchField, GeoMesh>& gf2)
	{
		tnbLib::cmptMultiply(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::cmptMultiply(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> cmptMultiply(const dimensioned<vector3>& dt1,
	                                                               const GeometricField<vector3, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(new GeometricField<vector3, PatchField, GeoMesh>(
			IOobject("cmptMultiply" "(" + dt1.name() + ',' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ,
			         IOobject::NO_WRITE), gf2.mesh(), cmptMultiply(dt1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> cmptMultiply(const vector3& t1,
	                                                               const GeometricField<vector3, PatchField, GeoMesh>& gf2)
	{
		return cmptMultiply(dimensioned<vector3>(t1), gf2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> cmptMultiply(const dimensioned<vector3>& dt1,
	                                                               const tmp<GeometricField<vector3, PatchField, GeoMesh>>&
	                                                               tgf2)
	{
		const GeometricField<vector3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::New(
				tgf2, "cmptMultiply" "(" + dt1.name() + gf2.name() + ',' + ')', cmptMultiply(dt1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), dt1, gf2);
		reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> cmptMultiply(const vector3& t1,
	                                                               const tmp<GeometricField<vector3, PatchField, GeoMesh>>&
	                                                               tgf2)
	{
		return cmptMultiply(dimensioned<vector3>(t1), tgf2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void cmptMultiply(GeometricField<vector3, PatchField, GeoMesh>& res,
	                  const GeometricField<vector3, PatchField, GeoMesh>& gf1, const dimensioned<vector3>& dt2)
	{
		tnbLib::cmptMultiply(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::cmptMultiply(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> cmptMultiply(const GeometricField<vector3, PatchField, GeoMesh>& gf1,
	                                                               const dimensioned<vector3>& dt2)
	{
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(new GeometricField<vector3, PatchField, GeoMesh>(
			IOobject("cmptMultiply" "(" + gf1.name() + ',' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ,
			         IOobject::NO_WRITE), gf1.mesh(), cmptMultiply(gf1.dimensions(), dt2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> cmptMultiply(const GeometricField<vector3, PatchField, GeoMesh>& gf1,
	                                                               const vector3& t2)
	{
		return cmptMultiply(gf1, dimensioned<vector3>(t2));
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> cmptMultiply(
		const tmp<GeometricField<vector3, PatchField, GeoMesh>>& tgf1, const dimensioned<vector3>& dt2)
	{
		const GeometricField<vector3, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::New(
				tgf1, "cmptMultiply" "(" + gf1.name() + ',' + dt2.name() + ')', cmptMultiply(gf1.dimensions(), dt2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, dt2);
		reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> cmptMultiply(
		const tmp<GeometricField<vector3, PatchField, GeoMesh>>& tgf1, const vector3& t2)
	{
		return cmptMultiply(tgf1, dimensioned<vector3>(t2));
	}

	template <template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<vector3, PatchField, GeoMesh>& res,
	              const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	              const GeometricField<vector3, PatchField, GeoMesh>& gf2)
	{
		tnbLib::multiply(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::multiply(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator *(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const GeometricField<vector3, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(new GeometricField<vector3, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '*' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator *(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const tmp<GeometricField<vector3, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + '*' + gf2.name() + ')',
			                                                                   gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const GeometricField<vector3, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector3, scalar, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '*' + gf2.name() + ')',
			                                                                  gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector3, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<vector3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<vector3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<vector3, scalar, scalar, vector3, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '*' + gf2.name() + ')', gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<vector3, scalar, scalar, vector3, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<vector3, PatchField, GeoMesh>& res, const dimensioned<scalar>& dt1,
	              const GeometricField<vector3, PatchField, GeoMesh>& gf2)
	{
		tnbLib::multiply(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::multiply(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator *(const dimensioned<scalar>& dt1,
	                                                             const GeometricField<vector3, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(new GeometricField<vector3, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '*' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator *(const scalar& t1,
	                                                             const GeometricField<vector3, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<scalar>(t1) * gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator *(const dimensioned<scalar>& dt1,
	                                                             const tmp<GeometricField<vector3, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::New(tgf2, '(' + dt1.name() + '*' + gf2.name() + ')',
			                                                                   dt1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), dt1, gf2);
		reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator *(const scalar& t1,
	                                                             const tmp<GeometricField<vector3, PatchField, GeoMesh>>&
	                                                             tgf2) { return dimensioned<scalar>(t1) * tgf2; }

	template <template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<vector3, PatchField, GeoMesh>& res,
	              const GeometricField<scalar, PatchField, GeoMesh>& gf1, const dimensioned<vector3>& dt2)
	{
		tnbLib::multiply(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::multiply(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator *(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const dimensioned<vector3>& dt2)
	{
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(new GeometricField<vector3, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '*' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() * dt2.dimensions()));
		tnbLib::multiply(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator *(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const vector3& t2)
	{
		return gf1 * dimensioned<vector3>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const dimensioned<vector3>& dt2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector3, scalar, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '*' + dt2.name() + ')',
			                                                                  gf1.dimensions() * dt2.dimensions()));
		tnbLib::multiply(tRes(), gf1, dt2);
		reuseTmpGeometricField<vector3, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const vector3& t2)
	{
		return tgf1 * dimensioned<vector3>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<vector3, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	            const GeometricField<vector3, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator /(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const GeometricField<vector3, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(new GeometricField<vector3, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator /(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const tmp<GeometricField<vector3, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + '|' + gf2.name() + ')',
			                                                                   gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const GeometricField<vector3, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector3, scalar, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '|' + gf2.name() + ')',
			                                                                  gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector3, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<vector3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<vector3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<vector3, scalar, scalar, vector3, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<vector3, scalar, scalar, vector3, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<vector3, PatchField, GeoMesh>& res, const dimensioned<scalar>& dt1,
	            const GeometricField<vector3, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
	                                                             const GeometricField<vector3, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(new GeometricField<vector3, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator /(const scalar& t1,
	                                                             const GeometricField<vector3, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<scalar>(t1) / gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
	                                                             const tmp<GeometricField<vector3, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::New(tgf2, '(' + dt1.name() + '|' + gf2.name() + ')',
			                                                                   dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator /(const scalar& t1,
	                                                             const tmp<GeometricField<vector3, PatchField, GeoMesh>>&
	                                                             tgf2) { return dimensioned<scalar>(t1) / tgf2; }

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<vector3, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	            const dimensioned<vector3>& dt2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator /(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const dimensioned<vector3>& dt2)
	{
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(new GeometricField<vector3, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator /(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const vector3& t2)
	{
		return gf1 / dimensioned<vector3>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const dimensioned<vector3>& dt2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector3, scalar, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '|' + dt2.name() + ')',
			                                                                  gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		reuseTmpGeometricField<vector3, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const vector3& t2)
	{
		return tgf1 / dimensioned<vector3>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<vector3, PatchField, GeoMesh>& res, const GeometricField<vector3, PatchField, GeoMesh>& gf1,
	         const GeometricField<vector3, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator +(const GeometricField<vector3, PatchField, GeoMesh>& gf1,
	                                                             const GeometricField<vector3, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(new GeometricField<vector3, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator +(const GeometricField<vector3, PatchField, GeoMesh>& gf1,
	                                                             const tmp<GeometricField<vector3, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + '+' + gf2.name() + ')',
			                                                                   gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<vector3, PatchField, GeoMesh>>& tgf1,
		const GeometricField<vector3, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<vector3, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '+' + gf2.name() + ')',
			                                                                   gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<vector3, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<vector3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<vector3, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<vector3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<vector3, vector3, vector3, vector3, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<vector3, vector3, vector3, vector3, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<vector3, PatchField, GeoMesh>& res,
	              const GeometricField<vector3, PatchField, GeoMesh>& gf1,
	              const GeometricField<vector3, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator -(const GeometricField<vector3, PatchField, GeoMesh>& gf1,
	                                                             const GeometricField<vector3, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(new GeometricField<vector3, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator -(const GeometricField<vector3, PatchField, GeoMesh>& gf1,
	                                                             const tmp<GeometricField<vector3, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + '-' + gf2.name() + ')',
			                                                                   gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<vector3, PatchField, GeoMesh>>& tgf1,
		const GeometricField<vector3, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<vector3, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '-' + gf2.name() + ')',
			                                                                   gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<vector3, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<vector3, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<vector3, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<vector3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<vector3, vector3, vector3, vector3, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<vector3, vector3, vector3, vector3, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<vector3, PatchField, GeoMesh>& res, const dimensioned<vector3>& dt1,
	         const GeometricField<vector3, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::add(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator +(const dimensioned<vector3>& dt1,
	                                                             const GeometricField<vector3, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(new GeometricField<vector3, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator +(const vector3& t1,
	                                                             const GeometricField<vector3, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<vector3>(t1) + gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator +(const dimensioned<vector3>& dt1,
	                                                             const tmp<GeometricField<vector3, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::New(tgf2, '(' + dt1.name() + '+' + gf2.name() + ')',
			                                                                   dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator +(const vector3& t1,
	                                                             const tmp<GeometricField<vector3, PatchField, GeoMesh>>&
	                                                             tgf2) { return dimensioned<vector3>(t1) + tgf2; }

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<vector3, PatchField, GeoMesh>& res, const GeometricField<vector3, PatchField, GeoMesh>& gf1,
	         const dimensioned<vector3>& dt2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator +(const GeometricField<vector3, PatchField, GeoMesh>& gf1,
	                                                             const dimensioned<vector3>& dt2)
	{
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(new GeometricField<vector3, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator +(const GeometricField<vector3, PatchField, GeoMesh>& gf1,
	                                                             const vector3& t2)
	{
		return gf1 + dimensioned<vector3>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<vector3, PatchField, GeoMesh>>& tgf1, const dimensioned<vector3>& dt2)
	{
		const GeometricField<vector3, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '+' + dt2.name() + ')',
			                                                                   gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<vector3, PatchField, GeoMesh>>& tgf1, const vector3& t2)
	{
		return tgf1 + dimensioned<vector3>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<vector3, PatchField, GeoMesh>& res, const dimensioned<vector3>& dt1,
	              const GeometricField<vector3, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator -(const dimensioned<vector3>& dt1,
	                                                             const GeometricField<vector3, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(new GeometricField<vector3, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator -(const vector3& t1,
	                                                             const GeometricField<vector3, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<vector3>(t1) - gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator -(const dimensioned<vector3>& dt1,
	                                                             const tmp<GeometricField<vector3, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector3, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::New(tgf2, '(' + dt1.name() + '-' + gf2.name() + ')',
			                                                                   dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator -(const vector3& t1,
	                                                             const tmp<GeometricField<vector3, PatchField, GeoMesh>>&
	                                                             tgf2) { return dimensioned<vector3>(t1) - tgf2; }

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<vector3, PatchField, GeoMesh>& res,
	              const GeometricField<vector3, PatchField, GeoMesh>& gf1, const dimensioned<vector3>& dt2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator -(const GeometricField<vector3, PatchField, GeoMesh>& gf1,
	                                                             const dimensioned<vector3>& dt2)
	{
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(new GeometricField<vector3, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator -(const GeometricField<vector3, PatchField, GeoMesh>& gf1,
	                                                             const vector3& t2)
	{
		return gf1 - dimensioned<vector3>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<vector3, PatchField, GeoMesh>>& tgf1, const dimensioned<vector3>& dt2)
	{
		const GeometricField<vector3, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector3, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '-' + dt2.name() + ')',
			                                                                   gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		reuseTmpGeometricField<vector3, vector3, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector3, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<vector3, PatchField, GeoMesh>>& tgf1, const vector3& t2)
	{
		return tgf1 - dimensioned<vector3>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void cmptSum(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<vector4, PatchField, GeoMesh>& gf1)
	{
		tnbLib::cmptSum(res.internalField(), gf1.internalField());
		tnbLib::cmptSum(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> cmptSum(const GeometricField<vector4, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("cmptSum" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), cmptSum(gf1.dimensions())));
		tnbLib::cmptSum(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> cmptSum(const tmp<GeometricField<vector4, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<vector4, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, vector4, PatchField, GeoMesh>::New(tgf1, "cmptSum" "(" + gf1.name() + ')',
			                                                                  cmptSum(gf1.dimensions())));
		tnbLib::cmptSum(tRes(), gf1);
		reuseTmpGeometricField<scalar, vector4, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void cmptMultiply(GeometricField<vector4, PatchField, GeoMesh>& res,
	                  const GeometricField<vector4, PatchField, GeoMesh>& gf1,
	                  const GeometricField<vector4, PatchField, GeoMesh>& gf2)
	{
		tnbLib::cmptMultiply(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::cmptMultiply(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> cmptMultiply(const GeometricField<vector4, PatchField, GeoMesh>& gf1,
	                                                               const GeometricField<vector4, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(new GeometricField<vector4, PatchField, GeoMesh>(
			IOobject("cmptMultiply" "(" + gf1.name() + ',' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ,
			         IOobject::NO_WRITE), gf1.mesh(), cmptMultiply(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> cmptMultiply(const GeometricField<vector4, PatchField, GeoMesh>& gf1,
	                                                               const tmp<GeometricField<vector4, PatchField, GeoMesh>>&
	                                                               tgf2)
	{
		const GeometricField<vector4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::New(
				tgf2, "cmptMultiply" "(" + gf1.name() + ',' + gf2.name() + ')', cmptMultiply(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> cmptMultiply(
		const tmp<GeometricField<vector4, PatchField, GeoMesh>>& tgf1,
		const GeometricField<vector4, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<vector4, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::New(
				tgf1, "cmptMultiply" "(" + gf1.name() + ',' + gf2.name() + ')', cmptMultiply(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> cmptMultiply(
		const tmp<GeometricField<vector4, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<vector4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<vector4, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<vector4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<vector4, vector4, vector4, vector4, PatchField, GeoMesh>::New(
				tgf1, tgf2, "cmptMultiply" "(" + gf1.name() + ',' + gf2.name() + ')',
				cmptMultiply(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<vector4, vector4, vector4, vector4, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void cmptMultiply(GeometricField<vector4, PatchField, GeoMesh>& res, const dimensioned<vector4>& dt1,
	                  const GeometricField<vector4, PatchField, GeoMesh>& gf2)
	{
		tnbLib::cmptMultiply(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::cmptMultiply(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> cmptMultiply(const dimensioned<vector4>& dt1,
	                                                               const GeometricField<vector4, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(new GeometricField<vector4, PatchField, GeoMesh>(
			IOobject("cmptMultiply" "(" + dt1.name() + ',' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ,
			         IOobject::NO_WRITE), gf2.mesh(), cmptMultiply(dt1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> cmptMultiply(const vector4& t1,
	                                                               const GeometricField<vector4, PatchField, GeoMesh>& gf2)
	{
		return cmptMultiply(dimensioned<vector4>(t1), gf2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> cmptMultiply(const dimensioned<vector4>& dt1,
	                                                               const tmp<GeometricField<vector4, PatchField, GeoMesh>>&
	                                                               tgf2)
	{
		const GeometricField<vector4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::New(
				tgf2, "cmptMultiply" "(" + dt1.name() + gf2.name() + ',' + ')', cmptMultiply(dt1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), dt1, gf2);
		reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> cmptMultiply(const vector4& t1,
	                                                               const tmp<GeometricField<vector4, PatchField, GeoMesh>>&
	                                                               tgf2)
	{
		return cmptMultiply(dimensioned<vector4>(t1), tgf2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void cmptMultiply(GeometricField<vector4, PatchField, GeoMesh>& res,
	                  const GeometricField<vector4, PatchField, GeoMesh>& gf1, const dimensioned<vector4>& dt2)
	{
		tnbLib::cmptMultiply(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::cmptMultiply(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> cmptMultiply(const GeometricField<vector4, PatchField, GeoMesh>& gf1,
	                                                               const dimensioned<vector4>& dt2)
	{
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(new GeometricField<vector4, PatchField, GeoMesh>(
			IOobject("cmptMultiply" "(" + gf1.name() + ',' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ,
			         IOobject::NO_WRITE), gf1.mesh(), cmptMultiply(gf1.dimensions(), dt2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> cmptMultiply(const GeometricField<vector4, PatchField, GeoMesh>& gf1,
	                                                               const vector4& t2)
	{
		return cmptMultiply(gf1, dimensioned<vector4>(t2));
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> cmptMultiply(
		const tmp<GeometricField<vector4, PatchField, GeoMesh>>& tgf1, const dimensioned<vector4>& dt2)
	{
		const GeometricField<vector4, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::New(
				tgf1, "cmptMultiply" "(" + gf1.name() + ',' + dt2.name() + ')', cmptMultiply(gf1.dimensions(), dt2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, dt2);
		reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> cmptMultiply(
		const tmp<GeometricField<vector4, PatchField, GeoMesh>>& tgf1, const vector4& t2)
	{
		return cmptMultiply(tgf1, dimensioned<vector4>(t2));
	}

	template <template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<vector4, PatchField, GeoMesh>& res,
	              const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	              const GeometricField<vector4, PatchField, GeoMesh>& gf2)
	{
		tnbLib::multiply(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::multiply(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator *(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const GeometricField<vector4, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(new GeometricField<vector4, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '*' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator *(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const tmp<GeometricField<vector4, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + '*' + gf2.name() + ')',
			                                                                   gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const GeometricField<vector4, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector4, scalar, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '*' + gf2.name() + ')',
			                                                                  gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector4, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<vector4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<vector4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<vector4, scalar, scalar, vector4, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '*' + gf2.name() + ')', gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<vector4, scalar, scalar, vector4, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<vector4, PatchField, GeoMesh>& res, const dimensioned<scalar>& dt1,
	              const GeometricField<vector4, PatchField, GeoMesh>& gf2)
	{
		tnbLib::multiply(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::multiply(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator *(const dimensioned<scalar>& dt1,
	                                                             const GeometricField<vector4, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(new GeometricField<vector4, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '*' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator *(const scalar& t1,
	                                                             const GeometricField<vector4, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<scalar>(t1) * gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator *(const dimensioned<scalar>& dt1,
	                                                             const tmp<GeometricField<vector4, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::New(tgf2, '(' + dt1.name() + '*' + gf2.name() + ')',
			                                                                   dt1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), dt1, gf2);
		reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator *(const scalar& t1,
	                                                             const tmp<GeometricField<vector4, PatchField, GeoMesh>>&
	                                                             tgf2) { return dimensioned<scalar>(t1) * tgf2; }

	template <template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<vector4, PatchField, GeoMesh>& res,
	              const GeometricField<scalar, PatchField, GeoMesh>& gf1, const dimensioned<vector4>& dt2)
	{
		tnbLib::multiply(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::multiply(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator *(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const dimensioned<vector4>& dt2)
	{
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(new GeometricField<vector4, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '*' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() * dt2.dimensions()));
		tnbLib::multiply(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator *(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const vector4& t2)
	{
		return gf1 * dimensioned<vector4>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const dimensioned<vector4>& dt2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector4, scalar, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '*' + dt2.name() + ')',
			                                                                  gf1.dimensions() * dt2.dimensions()));
		tnbLib::multiply(tRes(), gf1, dt2);
		reuseTmpGeometricField<vector4, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const vector4& t2)
	{
		return tgf1 * dimensioned<vector4>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<vector4, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	            const GeometricField<vector4, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator /(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const GeometricField<vector4, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(new GeometricField<vector4, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator /(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const tmp<GeometricField<vector4, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + '|' + gf2.name() + ')',
			                                                                   gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const GeometricField<vector4, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector4, scalar, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '|' + gf2.name() + ')',
			                                                                  gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector4, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<vector4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<vector4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<vector4, scalar, scalar, vector4, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<vector4, scalar, scalar, vector4, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<vector4, PatchField, GeoMesh>& res, const dimensioned<scalar>& dt1,
	            const GeometricField<vector4, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
	                                                             const GeometricField<vector4, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(new GeometricField<vector4, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator /(const scalar& t1,
	                                                             const GeometricField<vector4, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<scalar>(t1) / gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
	                                                             const tmp<GeometricField<vector4, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::New(tgf2, '(' + dt1.name() + '|' + gf2.name() + ')',
			                                                                   dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator /(const scalar& t1,
	                                                             const tmp<GeometricField<vector4, PatchField, GeoMesh>>&
	                                                             tgf2) { return dimensioned<scalar>(t1) / tgf2; }

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<vector4, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	            const dimensioned<vector4>& dt2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator /(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const dimensioned<vector4>& dt2)
	{
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(new GeometricField<vector4, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator /(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const vector4& t2)
	{
		return gf1 / dimensioned<vector4>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const dimensioned<vector4>& dt2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector4, scalar, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '|' + dt2.name() + ')',
			                                                                  gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		reuseTmpGeometricField<vector4, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const vector4& t2)
	{
		return tgf1 / dimensioned<vector4>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<vector4, PatchField, GeoMesh>& res, const GeometricField<vector4, PatchField, GeoMesh>& gf1,
	         const GeometricField<vector4, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator +(const GeometricField<vector4, PatchField, GeoMesh>& gf1,
	                                                             const GeometricField<vector4, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(new GeometricField<vector4, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator +(const GeometricField<vector4, PatchField, GeoMesh>& gf1,
	                                                             const tmp<GeometricField<vector4, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + '+' + gf2.name() + ')',
			                                                                   gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<vector4, PatchField, GeoMesh>>& tgf1,
		const GeometricField<vector4, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<vector4, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '+' + gf2.name() + ')',
			                                                                   gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<vector4, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<vector4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<vector4, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<vector4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<vector4, vector4, vector4, vector4, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<vector4, vector4, vector4, vector4, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<vector4, PatchField, GeoMesh>& res,
	              const GeometricField<vector4, PatchField, GeoMesh>& gf1,
	              const GeometricField<vector4, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator -(const GeometricField<vector4, PatchField, GeoMesh>& gf1,
	                                                             const GeometricField<vector4, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(new GeometricField<vector4, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator -(const GeometricField<vector4, PatchField, GeoMesh>& gf1,
	                                                             const tmp<GeometricField<vector4, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + '-' + gf2.name() + ')',
			                                                                   gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<vector4, PatchField, GeoMesh>>& tgf1,
		const GeometricField<vector4, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<vector4, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '-' + gf2.name() + ')',
			                                                                   gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<vector4, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<vector4, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<vector4, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<vector4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<vector4, vector4, vector4, vector4, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<vector4, vector4, vector4, vector4, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<vector4, PatchField, GeoMesh>& res, const dimensioned<vector4>& dt1,
	         const GeometricField<vector4, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::add(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator +(const dimensioned<vector4>& dt1,
	                                                             const GeometricField<vector4, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(new GeometricField<vector4, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator +(const vector4& t1,
	                                                             const GeometricField<vector4, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<vector4>(t1) + gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator +(const dimensioned<vector4>& dt1,
	                                                             const tmp<GeometricField<vector4, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::New(tgf2, '(' + dt1.name() + '+' + gf2.name() + ')',
			                                                                   dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator +(const vector4& t1,
	                                                             const tmp<GeometricField<vector4, PatchField, GeoMesh>>&
	                                                             tgf2) { return dimensioned<vector4>(t1) + tgf2; }

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<vector4, PatchField, GeoMesh>& res, const GeometricField<vector4, PatchField, GeoMesh>& gf1,
	         const dimensioned<vector4>& dt2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator +(const GeometricField<vector4, PatchField, GeoMesh>& gf1,
	                                                             const dimensioned<vector4>& dt2)
	{
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(new GeometricField<vector4, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator +(const GeometricField<vector4, PatchField, GeoMesh>& gf1,
	                                                             const vector4& t2)
	{
		return gf1 + dimensioned<vector4>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<vector4, PatchField, GeoMesh>>& tgf1, const dimensioned<vector4>& dt2)
	{
		const GeometricField<vector4, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '+' + dt2.name() + ')',
			                                                                   gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<vector4, PatchField, GeoMesh>>& tgf1, const vector4& t2)
	{
		return tgf1 + dimensioned<vector4>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<vector4, PatchField, GeoMesh>& res, const dimensioned<vector4>& dt1,
	              const GeometricField<vector4, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator -(const dimensioned<vector4>& dt1,
	                                                             const GeometricField<vector4, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(new GeometricField<vector4, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator -(const vector4& t1,
	                                                             const GeometricField<vector4, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<vector4>(t1) - gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator -(const dimensioned<vector4>& dt1,
	                                                             const tmp<GeometricField<vector4, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector4, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::New(tgf2, '(' + dt1.name() + '-' + gf2.name() + ')',
			                                                                   dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator -(const vector4& t1,
	                                                             const tmp<GeometricField<vector4, PatchField, GeoMesh>>&
	                                                             tgf2) { return dimensioned<vector4>(t1) - tgf2; }

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<vector4, PatchField, GeoMesh>& res,
	              const GeometricField<vector4, PatchField, GeoMesh>& gf1, const dimensioned<vector4>& dt2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator -(const GeometricField<vector4, PatchField, GeoMesh>& gf1,
	                                                             const dimensioned<vector4>& dt2)
	{
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(new GeometricField<vector4, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator -(const GeometricField<vector4, PatchField, GeoMesh>& gf1,
	                                                             const vector4& t2)
	{
		return gf1 - dimensioned<vector4>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<vector4, PatchField, GeoMesh>>& tgf1, const dimensioned<vector4>& dt2)
	{
		const GeometricField<vector4, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector4, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '-' + dt2.name() + ')',
			                                                                   gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		reuseTmpGeometricField<vector4, vector4, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector4, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<vector4, PatchField, GeoMesh>>& tgf1, const vector4& t2)
	{
		return tgf1 - dimensioned<vector4>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void cmptSum(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<vector6, PatchField, GeoMesh>& gf1)
	{
		tnbLib::cmptSum(res.internalField(), gf1.internalField());
		tnbLib::cmptSum(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> cmptSum(const GeometricField<vector6, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("cmptSum" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), cmptSum(gf1.dimensions())));
		tnbLib::cmptSum(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> cmptSum(const tmp<GeometricField<vector6, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<vector6, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, vector6, PatchField, GeoMesh>::New(tgf1, "cmptSum" "(" + gf1.name() + ')',
			                                                                  cmptSum(gf1.dimensions())));
		tnbLib::cmptSum(tRes(), gf1);
		reuseTmpGeometricField<scalar, vector6, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void cmptMultiply(GeometricField<vector6, PatchField, GeoMesh>& res,
	                  const GeometricField<vector6, PatchField, GeoMesh>& gf1,
	                  const GeometricField<vector6, PatchField, GeoMesh>& gf2)
	{
		tnbLib::cmptMultiply(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::cmptMultiply(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> cmptMultiply(const GeometricField<vector6, PatchField, GeoMesh>& gf1,
	                                                               const GeometricField<vector6, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(new GeometricField<vector6, PatchField, GeoMesh>(
			IOobject("cmptMultiply" "(" + gf1.name() + ',' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ,
			         IOobject::NO_WRITE), gf1.mesh(), cmptMultiply(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> cmptMultiply(const GeometricField<vector6, PatchField, GeoMesh>& gf1,
	                                                               const tmp<GeometricField<vector6, PatchField, GeoMesh>>&
	                                                               tgf2)
	{
		const GeometricField<vector6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::New(
				tgf2, "cmptMultiply" "(" + gf1.name() + ',' + gf2.name() + ')', cmptMultiply(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> cmptMultiply(
		const tmp<GeometricField<vector6, PatchField, GeoMesh>>& tgf1,
		const GeometricField<vector6, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<vector6, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::New(
				tgf1, "cmptMultiply" "(" + gf1.name() + ',' + gf2.name() + ')', cmptMultiply(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> cmptMultiply(
		const tmp<GeometricField<vector6, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<vector6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<vector6, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<vector6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<vector6, vector6, vector6, vector6, PatchField, GeoMesh>::New(
				tgf1, tgf2, "cmptMultiply" "(" + gf1.name() + ',' + gf2.name() + ')',
				cmptMultiply(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<vector6, vector6, vector6, vector6, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void cmptMultiply(GeometricField<vector6, PatchField, GeoMesh>& res, const dimensioned<vector6>& dt1,
	                  const GeometricField<vector6, PatchField, GeoMesh>& gf2)
	{
		tnbLib::cmptMultiply(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::cmptMultiply(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> cmptMultiply(const dimensioned<vector6>& dt1,
	                                                               const GeometricField<vector6, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(new GeometricField<vector6, PatchField, GeoMesh>(
			IOobject("cmptMultiply" "(" + dt1.name() + ',' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ,
			         IOobject::NO_WRITE), gf2.mesh(), cmptMultiply(dt1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> cmptMultiply(const vector6& t1,
	                                                               const GeometricField<vector6, PatchField, GeoMesh>& gf2)
	{
		return cmptMultiply(dimensioned<vector6>(t1), gf2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> cmptMultiply(const dimensioned<vector6>& dt1,
	                                                               const tmp<GeometricField<vector6, PatchField, GeoMesh>>&
	                                                               tgf2)
	{
		const GeometricField<vector6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::New(
				tgf2, "cmptMultiply" "(" + dt1.name() + gf2.name() + ',' + ')', cmptMultiply(dt1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), dt1, gf2);
		reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> cmptMultiply(const vector6& t1,
	                                                               const tmp<GeometricField<vector6, PatchField, GeoMesh>>&
	                                                               tgf2)
	{
		return cmptMultiply(dimensioned<vector6>(t1), tgf2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void cmptMultiply(GeometricField<vector6, PatchField, GeoMesh>& res,
	                  const GeometricField<vector6, PatchField, GeoMesh>& gf1, const dimensioned<vector6>& dt2)
	{
		tnbLib::cmptMultiply(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::cmptMultiply(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> cmptMultiply(const GeometricField<vector6, PatchField, GeoMesh>& gf1,
	                                                               const dimensioned<vector6>& dt2)
	{
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(new GeometricField<vector6, PatchField, GeoMesh>(
			IOobject("cmptMultiply" "(" + gf1.name() + ',' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ,
			         IOobject::NO_WRITE), gf1.mesh(), cmptMultiply(gf1.dimensions(), dt2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> cmptMultiply(const GeometricField<vector6, PatchField, GeoMesh>& gf1,
	                                                               const vector6& t2)
	{
		return cmptMultiply(gf1, dimensioned<vector6>(t2));
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> cmptMultiply(
		const tmp<GeometricField<vector6, PatchField, GeoMesh>>& tgf1, const dimensioned<vector6>& dt2)
	{
		const GeometricField<vector6, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::New(
				tgf1, "cmptMultiply" "(" + gf1.name() + ',' + dt2.name() + ')', cmptMultiply(gf1.dimensions(), dt2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, dt2);
		reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> cmptMultiply(
		const tmp<GeometricField<vector6, PatchField, GeoMesh>>& tgf1, const vector6& t2)
	{
		return cmptMultiply(tgf1, dimensioned<vector6>(t2));
	}

	template <template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<vector6, PatchField, GeoMesh>& res,
	              const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	              const GeometricField<vector6, PatchField, GeoMesh>& gf2)
	{
		tnbLib::multiply(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::multiply(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator *(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const GeometricField<vector6, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(new GeometricField<vector6, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '*' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator *(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const tmp<GeometricField<vector6, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + '*' + gf2.name() + ')',
			                                                                   gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const GeometricField<vector6, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector6, scalar, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '*' + gf2.name() + ')',
			                                                                  gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector6, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<vector6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<vector6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<vector6, scalar, scalar, vector6, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '*' + gf2.name() + ')', gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<vector6, scalar, scalar, vector6, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<vector6, PatchField, GeoMesh>& res, const dimensioned<scalar>& dt1,
	              const GeometricField<vector6, PatchField, GeoMesh>& gf2)
	{
		tnbLib::multiply(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::multiply(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator *(const dimensioned<scalar>& dt1,
	                                                             const GeometricField<vector6, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(new GeometricField<vector6, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '*' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator *(const scalar& t1,
	                                                             const GeometricField<vector6, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<scalar>(t1) * gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator *(const dimensioned<scalar>& dt1,
	                                                             const tmp<GeometricField<vector6, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::New(tgf2, '(' + dt1.name() + '*' + gf2.name() + ')',
			                                                                   dt1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), dt1, gf2);
		reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator *(const scalar& t1,
	                                                             const tmp<GeometricField<vector6, PatchField, GeoMesh>>&
	                                                             tgf2) { return dimensioned<scalar>(t1) * tgf2; }

	template <template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<vector6, PatchField, GeoMesh>& res,
	              const GeometricField<scalar, PatchField, GeoMesh>& gf1, const dimensioned<vector6>& dt2)
	{
		tnbLib::multiply(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::multiply(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator *(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const dimensioned<vector6>& dt2)
	{
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(new GeometricField<vector6, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '*' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() * dt2.dimensions()));
		tnbLib::multiply(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator *(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const vector6& t2)
	{
		return gf1 * dimensioned<vector6>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const dimensioned<vector6>& dt2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector6, scalar, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '*' + dt2.name() + ')',
			                                                                  gf1.dimensions() * dt2.dimensions()));
		tnbLib::multiply(tRes(), gf1, dt2);
		reuseTmpGeometricField<vector6, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const vector6& t2)
	{
		return tgf1 * dimensioned<vector6>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<vector6, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	            const GeometricField<vector6, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator /(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const GeometricField<vector6, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(new GeometricField<vector6, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator /(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const tmp<GeometricField<vector6, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + '|' + gf2.name() + ')',
			                                                                   gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const GeometricField<vector6, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector6, scalar, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '|' + gf2.name() + ')',
			                                                                  gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector6, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<vector6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<vector6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<vector6, scalar, scalar, vector6, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<vector6, scalar, scalar, vector6, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<vector6, PatchField, GeoMesh>& res, const dimensioned<scalar>& dt1,
	            const GeometricField<vector6, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
	                                                             const GeometricField<vector6, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(new GeometricField<vector6, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator /(const scalar& t1,
	                                                             const GeometricField<vector6, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<scalar>(t1) / gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
	                                                             const tmp<GeometricField<vector6, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::New(tgf2, '(' + dt1.name() + '|' + gf2.name() + ')',
			                                                                   dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator /(const scalar& t1,
	                                                             const tmp<GeometricField<vector6, PatchField, GeoMesh>>&
	                                                             tgf2) { return dimensioned<scalar>(t1) / tgf2; }

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<vector6, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	            const dimensioned<vector6>& dt2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator /(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const dimensioned<vector6>& dt2)
	{
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(new GeometricField<vector6, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator /(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const vector6& t2)
	{
		return gf1 / dimensioned<vector6>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const dimensioned<vector6>& dt2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector6, scalar, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '|' + dt2.name() + ')',
			                                                                  gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		reuseTmpGeometricField<vector6, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const vector6& t2)
	{
		return tgf1 / dimensioned<vector6>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<vector6, PatchField, GeoMesh>& res, const GeometricField<vector6, PatchField, GeoMesh>& gf1,
	         const GeometricField<vector6, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator +(const GeometricField<vector6, PatchField, GeoMesh>& gf1,
	                                                             const GeometricField<vector6, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(new GeometricField<vector6, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator +(const GeometricField<vector6, PatchField, GeoMesh>& gf1,
	                                                             const tmp<GeometricField<vector6, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + '+' + gf2.name() + ')',
			                                                                   gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<vector6, PatchField, GeoMesh>>& tgf1,
		const GeometricField<vector6, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<vector6, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '+' + gf2.name() + ')',
			                                                                   gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<vector6, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<vector6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<vector6, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<vector6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<vector6, vector6, vector6, vector6, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<vector6, vector6, vector6, vector6, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<vector6, PatchField, GeoMesh>& res,
	              const GeometricField<vector6, PatchField, GeoMesh>& gf1,
	              const GeometricField<vector6, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator -(const GeometricField<vector6, PatchField, GeoMesh>& gf1,
	                                                             const GeometricField<vector6, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(new GeometricField<vector6, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator -(const GeometricField<vector6, PatchField, GeoMesh>& gf1,
	                                                             const tmp<GeometricField<vector6, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + '-' + gf2.name() + ')',
			                                                                   gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<vector6, PatchField, GeoMesh>>& tgf1,
		const GeometricField<vector6, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<vector6, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '-' + gf2.name() + ')',
			                                                                   gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<vector6, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<vector6, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<vector6, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<vector6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<vector6, vector6, vector6, vector6, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<vector6, vector6, vector6, vector6, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<vector6, PatchField, GeoMesh>& res, const dimensioned<vector6>& dt1,
	         const GeometricField<vector6, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::add(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator +(const dimensioned<vector6>& dt1,
	                                                             const GeometricField<vector6, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(new GeometricField<vector6, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator +(const vector6& t1,
	                                                             const GeometricField<vector6, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<vector6>(t1) + gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator +(const dimensioned<vector6>& dt1,
	                                                             const tmp<GeometricField<vector6, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::New(tgf2, '(' + dt1.name() + '+' + gf2.name() + ')',
			                                                                   dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator +(const vector6& t1,
	                                                             const tmp<GeometricField<vector6, PatchField, GeoMesh>>&
	                                                             tgf2) { return dimensioned<vector6>(t1) + tgf2; }

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<vector6, PatchField, GeoMesh>& res, const GeometricField<vector6, PatchField, GeoMesh>& gf1,
	         const dimensioned<vector6>& dt2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator +(const GeometricField<vector6, PatchField, GeoMesh>& gf1,
	                                                             const dimensioned<vector6>& dt2)
	{
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(new GeometricField<vector6, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator +(const GeometricField<vector6, PatchField, GeoMesh>& gf1,
	                                                             const vector6& t2)
	{
		return gf1 + dimensioned<vector6>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<vector6, PatchField, GeoMesh>>& tgf1, const dimensioned<vector6>& dt2)
	{
		const GeometricField<vector6, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '+' + dt2.name() + ')',
			                                                                   gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<vector6, PatchField, GeoMesh>>& tgf1, const vector6& t2)
	{
		return tgf1 + dimensioned<vector6>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<vector6, PatchField, GeoMesh>& res, const dimensioned<vector6>& dt1,
	              const GeometricField<vector6, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator -(const dimensioned<vector6>& dt1,
	                                                             const GeometricField<vector6, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(new GeometricField<vector6, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator -(const vector6& t1,
	                                                             const GeometricField<vector6, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<vector6>(t1) - gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator -(const dimensioned<vector6>& dt1,
	                                                             const tmp<GeometricField<vector6, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector6, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::New(tgf2, '(' + dt1.name() + '-' + gf2.name() + ')',
			                                                                   dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator -(const vector6& t1,
	                                                             const tmp<GeometricField<vector6, PatchField, GeoMesh>>&
	                                                             tgf2) { return dimensioned<vector6>(t1) - tgf2; }

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<vector6, PatchField, GeoMesh>& res,
	              const GeometricField<vector6, PatchField, GeoMesh>& gf1, const dimensioned<vector6>& dt2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator -(const GeometricField<vector6, PatchField, GeoMesh>& gf1,
	                                                             const dimensioned<vector6>& dt2)
	{
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(new GeometricField<vector6, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator -(const GeometricField<vector6, PatchField, GeoMesh>& gf1,
	                                                             const vector6& t2)
	{
		return gf1 - dimensioned<vector6>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<vector6, PatchField, GeoMesh>>& tgf1, const dimensioned<vector6>& dt2)
	{
		const GeometricField<vector6, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector6, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '-' + dt2.name() + ')',
			                                                                   gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		reuseTmpGeometricField<vector6, vector6, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector6, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<vector6, PatchField, GeoMesh>>& tgf1, const vector6& t2)
	{
		return tgf1 - dimensioned<vector6>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void cmptSum(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<vector8, PatchField, GeoMesh>& gf1)
	{
		tnbLib::cmptSum(res.internalField(), gf1.internalField());
		tnbLib::cmptSum(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> cmptSum(const GeometricField<vector8, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("cmptSum" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), cmptSum(gf1.dimensions())));
		tnbLib::cmptSum(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> cmptSum(const tmp<GeometricField<vector8, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<vector8, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, vector8, PatchField, GeoMesh>::New(tgf1, "cmptSum" "(" + gf1.name() + ')',
			                                                                  cmptSum(gf1.dimensions())));
		tnbLib::cmptSum(tRes(), gf1);
		reuseTmpGeometricField<scalar, vector8, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void cmptMultiply(GeometricField<vector8, PatchField, GeoMesh>& res,
	                  const GeometricField<vector8, PatchField, GeoMesh>& gf1,
	                  const GeometricField<vector8, PatchField, GeoMesh>& gf2)
	{
		tnbLib::cmptMultiply(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::cmptMultiply(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> cmptMultiply(const GeometricField<vector8, PatchField, GeoMesh>& gf1,
	                                                               const GeometricField<vector8, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(new GeometricField<vector8, PatchField, GeoMesh>(
			IOobject("cmptMultiply" "(" + gf1.name() + ',' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ,
			         IOobject::NO_WRITE), gf1.mesh(), cmptMultiply(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> cmptMultiply(const GeometricField<vector8, PatchField, GeoMesh>& gf1,
	                                                               const tmp<GeometricField<vector8, PatchField, GeoMesh>>&
	                                                               tgf2)
	{
		const GeometricField<vector8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::New(
				tgf2, "cmptMultiply" "(" + gf1.name() + ',' + gf2.name() + ')', cmptMultiply(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> cmptMultiply(
		const tmp<GeometricField<vector8, PatchField, GeoMesh>>& tgf1,
		const GeometricField<vector8, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<vector8, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::New(
				tgf1, "cmptMultiply" "(" + gf1.name() + ',' + gf2.name() + ')', cmptMultiply(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> cmptMultiply(
		const tmp<GeometricField<vector8, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<vector8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<vector8, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<vector8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<vector8, vector8, vector8, vector8, PatchField, GeoMesh>::New(
				tgf1, tgf2, "cmptMultiply" "(" + gf1.name() + ',' + gf2.name() + ')',
				cmptMultiply(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<vector8, vector8, vector8, vector8, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void cmptMultiply(GeometricField<vector8, PatchField, GeoMesh>& res, const dimensioned<vector8>& dt1,
	                  const GeometricField<vector8, PatchField, GeoMesh>& gf2)
	{
		tnbLib::cmptMultiply(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::cmptMultiply(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> cmptMultiply(const dimensioned<vector8>& dt1,
	                                                               const GeometricField<vector8, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(new GeometricField<vector8, PatchField, GeoMesh>(
			IOobject("cmptMultiply" "(" + dt1.name() + ',' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ,
			         IOobject::NO_WRITE), gf2.mesh(), cmptMultiply(dt1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> cmptMultiply(const vector8& t1,
	                                                               const GeometricField<vector8, PatchField, GeoMesh>& gf2)
	{
		return cmptMultiply(dimensioned<vector8>(t1), gf2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> cmptMultiply(const dimensioned<vector8>& dt1,
	                                                               const tmp<GeometricField<vector8, PatchField, GeoMesh>>&
	                                                               tgf2)
	{
		const GeometricField<vector8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::New(
				tgf2, "cmptMultiply" "(" + dt1.name() + gf2.name() + ',' + ')', cmptMultiply(dt1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes(), dt1, gf2);
		reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> cmptMultiply(const vector8& t1,
	                                                               const tmp<GeometricField<vector8, PatchField, GeoMesh>>&
	                                                               tgf2)
	{
		return cmptMultiply(dimensioned<vector8>(t1), tgf2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void cmptMultiply(GeometricField<vector8, PatchField, GeoMesh>& res,
	                  const GeometricField<vector8, PatchField, GeoMesh>& gf1, const dimensioned<vector8>& dt2)
	{
		tnbLib::cmptMultiply(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::cmptMultiply(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> cmptMultiply(const GeometricField<vector8, PatchField, GeoMesh>& gf1,
	                                                               const dimensioned<vector8>& dt2)
	{
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(new GeometricField<vector8, PatchField, GeoMesh>(
			IOobject("cmptMultiply" "(" + gf1.name() + ',' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ,
			         IOobject::NO_WRITE), gf1.mesh(), cmptMultiply(gf1.dimensions(), dt2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> cmptMultiply(const GeometricField<vector8, PatchField, GeoMesh>& gf1,
	                                                               const vector8& t2)
	{
		return cmptMultiply(gf1, dimensioned<vector8>(t2));
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> cmptMultiply(
		const tmp<GeometricField<vector8, PatchField, GeoMesh>>& tgf1, const dimensioned<vector8>& dt2)
	{
		const GeometricField<vector8, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::New(
				tgf1, "cmptMultiply" "(" + gf1.name() + ',' + dt2.name() + ')', cmptMultiply(gf1.dimensions(), dt2.dimensions())));
		tnbLib::cmptMultiply(tRes(), gf1, dt2);
		reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> cmptMultiply(
		const tmp<GeometricField<vector8, PatchField, GeoMesh>>& tgf1, const vector8& t2)
	{
		return cmptMultiply(tgf1, dimensioned<vector8>(t2));
	}

	template <template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<vector8, PatchField, GeoMesh>& res,
	              const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	              const GeometricField<vector8, PatchField, GeoMesh>& gf2)
	{
		tnbLib::multiply(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::multiply(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator *(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const GeometricField<vector8, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(new GeometricField<vector8, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '*' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator *(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const tmp<GeometricField<vector8, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + '*' + gf2.name() + ')',
			                                                                   gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const GeometricField<vector8, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector8, scalar, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '*' + gf2.name() + ')',
			                                                                  gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector8, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<vector8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<vector8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<vector8, scalar, scalar, vector8, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '*' + gf2.name() + ')', gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<vector8, scalar, scalar, vector8, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<vector8, PatchField, GeoMesh>& res, const dimensioned<scalar>& dt1,
	              const GeometricField<vector8, PatchField, GeoMesh>& gf2)
	{
		tnbLib::multiply(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::multiply(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator *(const dimensioned<scalar>& dt1,
	                                                             const GeometricField<vector8, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(new GeometricField<vector8, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '*' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator *(const scalar& t1,
	                                                             const GeometricField<vector8, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<scalar>(t1) * gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator *(const dimensioned<scalar>& dt1,
	                                                             const tmp<GeometricField<vector8, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::New(tgf2, '(' + dt1.name() + '*' + gf2.name() + ')',
			                                                                   dt1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes(), dt1, gf2);
		reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator *(const scalar& t1,
	                                                             const tmp<GeometricField<vector8, PatchField, GeoMesh>>&
	                                                             tgf2) { return dimensioned<scalar>(t1) * tgf2; }

	template <template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<vector8, PatchField, GeoMesh>& res,
	              const GeometricField<scalar, PatchField, GeoMesh>& gf1, const dimensioned<vector8>& dt2)
	{
		tnbLib::multiply(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::multiply(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator *(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const dimensioned<vector8>& dt2)
	{
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(new GeometricField<vector8, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '*' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() * dt2.dimensions()));
		tnbLib::multiply(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator *(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const vector8& t2)
	{
		return gf1 * dimensioned<vector8>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const dimensioned<vector8>& dt2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector8, scalar, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '*' + dt2.name() + ')',
			                                                                  gf1.dimensions() * dt2.dimensions()));
		tnbLib::multiply(tRes(), gf1, dt2);
		reuseTmpGeometricField<vector8, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const vector8& t2)
	{
		return tgf1 * dimensioned<vector8>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<vector8, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	            const GeometricField<vector8, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator /(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const GeometricField<vector8, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(new GeometricField<vector8, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator /(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const tmp<GeometricField<vector8, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + '|' + gf2.name() + ')',
			                                                                   gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const GeometricField<vector8, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector8, scalar, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '|' + gf2.name() + ')',
			                                                                  gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector8, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<vector8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<vector8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<vector8, scalar, scalar, vector8, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<vector8, scalar, scalar, vector8, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<vector8, PatchField, GeoMesh>& res, const dimensioned<scalar>& dt1,
	            const GeometricField<vector8, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::divide(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
	                                                             const GeometricField<vector8, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(new GeometricField<vector8, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '|' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator /(const scalar& t1,
	                                                             const GeometricField<vector8, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<scalar>(t1) / gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
	                                                             const tmp<GeometricField<vector8, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::New(tgf2, '(' + dt1.name() + '|' + gf2.name() + ')',
			                                                                   dt1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes(), dt1, gf2);
		reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator /(const scalar& t1,
	                                                             const tmp<GeometricField<vector8, PatchField, GeoMesh>>&
	                                                             tgf2) { return dimensioned<scalar>(t1) / tgf2; }

	template <template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<vector8, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	            const dimensioned<vector8>& dt2)
	{
		tnbLib::divide(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::divide(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator /(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const dimensioned<vector8>& dt2)
	{
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(new GeometricField<vector8, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '|' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator /(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
	                                                             const vector8& t2)
	{
		return gf1 / dimensioned<vector8>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const dimensioned<vector8>& dt2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector8, scalar, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '|' + dt2.name() + ')',
			                                                                  gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes(), gf1, dt2);
		reuseTmpGeometricField<vector8, scalar, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1, const vector8& t2)
	{
		return tgf1 / dimensioned<vector8>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<vector8, PatchField, GeoMesh>& res, const GeometricField<vector8, PatchField, GeoMesh>& gf1,
	         const GeometricField<vector8, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator +(const GeometricField<vector8, PatchField, GeoMesh>& gf1,
	                                                             const GeometricField<vector8, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(new GeometricField<vector8, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator +(const GeometricField<vector8, PatchField, GeoMesh>& gf1,
	                                                             const tmp<GeometricField<vector8, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + '+' + gf2.name() + ')',
			                                                                   gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<vector8, PatchField, GeoMesh>>& tgf1,
		const GeometricField<vector8, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<vector8, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '+' + gf2.name() + ')',
			                                                                   gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<vector8, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<vector8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<vector8, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<vector8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<vector8, vector8, vector8, vector8, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '+' + gf2.name() + ')', gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<vector8, vector8, vector8, vector8, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<vector8, PatchField, GeoMesh>& res,
	              const GeometricField<vector8, PatchField, GeoMesh>& gf1,
	              const GeometricField<vector8, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator -(const GeometricField<vector8, PatchField, GeoMesh>& gf1,
	                                                             const GeometricField<vector8, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(new GeometricField<vector8, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator -(const GeometricField<vector8, PatchField, GeoMesh>& gf1,
	                                                             const tmp<GeometricField<vector8, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + '-' + gf2.name() + ')',
			                                                                   gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<vector8, PatchField, GeoMesh>>& tgf1,
		const GeometricField<vector8, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<vector8, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '-' + gf2.name() + ')',
			                                                                   gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<vector8, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<vector8, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<vector8, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<vector8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<vector8, vector8, vector8, vector8, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '-' + gf2.name() + ')', gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<vector8, vector8, vector8, vector8, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<vector8, PatchField, GeoMesh>& res, const dimensioned<vector8>& dt1,
	         const GeometricField<vector8, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::add(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator +(const dimensioned<vector8>& dt1,
	                                                             const GeometricField<vector8, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(new GeometricField<vector8, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '+' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator +(const vector8& t1,
	                                                             const GeometricField<vector8, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<vector8>(t1) + gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator +(const dimensioned<vector8>& dt1,
	                                                             const tmp<GeometricField<vector8, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::New(tgf2, '(' + dt1.name() + '+' + gf2.name() + ')',
			                                                                   dt1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes(), dt1, gf2);
		reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator +(const vector8& t1,
	                                                             const tmp<GeometricField<vector8, PatchField, GeoMesh>>&
	                                                             tgf2) { return dimensioned<vector8>(t1) + tgf2; }

	template <template<class> class PatchField, class GeoMesh>
	void add(GeometricField<vector8, PatchField, GeoMesh>& res, const GeometricField<vector8, PatchField, GeoMesh>& gf1,
	         const dimensioned<vector8>& dt2)
	{
		tnbLib::add(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::add(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator +(const GeometricField<vector8, PatchField, GeoMesh>& gf1,
	                                                             const dimensioned<vector8>& dt2)
	{
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(new GeometricField<vector8, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '+' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator +(const GeometricField<vector8, PatchField, GeoMesh>& gf1,
	                                                             const vector8& t2)
	{
		return gf1 + dimensioned<vector8>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<vector8, PatchField, GeoMesh>>& tgf1, const dimensioned<vector8>& dt2)
	{
		const GeometricField<vector8, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '+' + dt2.name() + ')',
			                                                                   gf1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes(), gf1, dt2);
		reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<vector8, PatchField, GeoMesh>>& tgf1, const vector8& t2)
	{
		return tgf1 + dimensioned<vector8>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<vector8, PatchField, GeoMesh>& res, const dimensioned<vector8>& dt1,
	              const GeometricField<vector8, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::subtract(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator -(const dimensioned<vector8>& dt1,
	                                                             const GeometricField<vector8, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(new GeometricField<vector8, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '-' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator -(const vector8& t1,
	                                                             const GeometricField<vector8, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<vector8>(t1) - gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator -(const dimensioned<vector8>& dt1,
	                                                             const tmp<GeometricField<vector8, PatchField, GeoMesh>>&
	                                                             tgf2)
	{
		const GeometricField<vector8, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::New(tgf2, '(' + dt1.name() + '-' + gf2.name() + ')',
			                                                                   dt1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes(), dt1, gf2);
		reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator -(const vector8& t1,
	                                                             const tmp<GeometricField<vector8, PatchField, GeoMesh>>&
	                                                             tgf2) { return dimensioned<vector8>(t1) - tgf2; }

	template <template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<vector8, PatchField, GeoMesh>& res,
	              const GeometricField<vector8, PatchField, GeoMesh>& gf1, const dimensioned<vector8>& dt2)
	{
		tnbLib::subtract(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::subtract(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator -(const GeometricField<vector8, PatchField, GeoMesh>& gf1,
	                                                             const dimensioned<vector8>& dt2)
	{
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(new GeometricField<vector8, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '-' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator -(const GeometricField<vector8, PatchField, GeoMesh>& gf1,
	                                                             const vector8& t2)
	{
		return gf1 - dimensioned<vector8>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<vector8, PatchField, GeoMesh>>& tgf1, const dimensioned<vector8>& dt2)
	{
		const GeometricField<vector8, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector8, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '-' + dt2.name() + ')',
			                                                                   gf1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes(), gf1, dt2);
		reuseTmpGeometricField<vector8, vector8, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector8, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<vector8, PatchField, GeoMesh>>& tgf1, const vector8& t2)
	{
		return tgf1 - dimensioned<vector8>(t2);
	}

}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#undef VectorN_FieldFunctions

#include <undefFieldFunctionsM.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// ************************************************************************* //