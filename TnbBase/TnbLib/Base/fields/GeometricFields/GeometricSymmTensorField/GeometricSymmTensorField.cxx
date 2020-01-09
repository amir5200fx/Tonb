#include <GeometricSymmTensorField.hxx>

#include <symmTensorFieldField.hxx>

#define TEMPLATE template<template<class> class PatchField, class GeoMesh>
#include <GeometricFieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template <template<class> class PatchField, class GeoMesh>
	void sqr(GeometricField<symmTensor, PatchField, GeoMesh>& res, const GeometricField<vector, PatchField, GeoMesh>& gf1)
	{
		tnbLib::sqr(res.internalField(), gf1.internalField());
		tnbLib::sqr(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> sqr(const GeometricField<vector, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(new GeometricField<symmTensor, PatchField, GeoMesh>(
			IOobject("sqr" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			sqr(gf1.dimensions())));
		tnbLib::sqr(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> sqr(const tmp<GeometricField<vector, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<vector, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<symmTensor, vector, PatchField, GeoMesh>::New(tgf1, "sqr" "(" + gf1.name() + ')',
			                                                                     sqr(gf1.dimensions())));
		tnbLib::sqr(tRes(), gf1);
		reuseTmpGeometricField<symmTensor, vector, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void innerSqr(GeometricField<symmTensor, PatchField, GeoMesh>& res,
	              const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::innerSqr(res.internalField(), gf1.internalField());
		tnbLib::innerSqr(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> innerSqr(
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(new GeometricField<symmTensor, PatchField, GeoMesh>(
			IOobject("innerSqr" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), sqr(gf1.dimensions())));
		tnbLib::innerSqr(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> innerSqr(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<symmTensor, symmTensor, PatchField, GeoMesh>::New(
				tgf1, "innerSqr" "(" + gf1.name() + ')', sqr(gf1.dimensions())));
		tnbLib::innerSqr(tRes(), gf1);
		reuseTmpGeometricField<symmTensor, symmTensor, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

		
	template <template<class> class PatchField, class GeoMesh>
	void tr(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::tr(res.internalField(), gf1.internalField());
		tnbLib::tr(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> tr(const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("tr" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			transform(gf1.dimensions())));
		tnbLib::tr(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> tr(const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, symmTensor, PatchField, GeoMesh>::New(tgf1, "tr" "(" + gf1.name() + ')',
			                                                                     transform(gf1.dimensions())));
		tnbLib::tr(tRes(), gf1);
		reuseTmpGeometricField<scalar, symmTensor, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void sph(GeometricField<sphericalTensor, PatchField, GeoMesh>& res,
	         const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::sph(res.internalField(), gf1.internalField());
		tnbLib::sph(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> sph(
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> tRes(
			new GeometricField<sphericalTensor, PatchField, GeoMesh>(
				IOobject("sph" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
				transform(gf1.dimensions())));
		tnbLib::sph(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> sph(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<sphericalTensor, symmTensor, PatchField, GeoMesh>::New(
				tgf1, "sph" "(" + gf1.name() + ')', transform(gf1.dimensions())));
		tnbLib::sph(tRes(), gf1);
		reuseTmpGeometricField<sphericalTensor, symmTensor, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void symm(GeometricField<symmTensor, PatchField, GeoMesh>& res,
	          const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::symm(res.internalField(), gf1.internalField());
		tnbLib::symm(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> symm(const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(new GeometricField<symmTensor, PatchField, GeoMesh>(
			IOobject("symm" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			transform(gf1.dimensions())));
		tnbLib::symm(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> symm(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<symmTensor, symmTensor, PatchField, GeoMesh>::New(
				tgf1, "symm" "(" + gf1.name() + ')', transform(gf1.dimensions())));
		tnbLib::symm(tRes(), gf1);
		reuseTmpGeometricField<symmTensor, symmTensor, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void twoSymm(GeometricField<symmTensor, PatchField, GeoMesh>& res,
	             const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::twoSymm(res.internalField(), gf1.internalField());
		tnbLib::twoSymm(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> twoSymm(
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(new GeometricField<symmTensor, PatchField, GeoMesh>(
			IOobject("twoSymm" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), transform(gf1.dimensions())));
		tnbLib::twoSymm(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> twoSymm(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<symmTensor, symmTensor, PatchField, GeoMesh>::New(
				tgf1, "twoSymm" "(" + gf1.name() + ')', transform(gf1.dimensions())));
		tnbLib::twoSymm(tRes(), gf1);
		reuseTmpGeometricField<symmTensor, symmTensor, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void dev(GeometricField<symmTensor, PatchField, GeoMesh>& res,
	         const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::dev(res.internalField(), gf1.internalField());
		tnbLib::dev(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> dev(const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(new GeometricField<symmTensor, PatchField, GeoMesh>(
			IOobject("dev" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			transform(gf1.dimensions())));
		tnbLib::dev(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> dev(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<symmTensor, symmTensor, PatchField, GeoMesh>::New(
				tgf1, "dev" "(" + gf1.name() + ')', transform(gf1.dimensions())));
		tnbLib::dev(tRes(), gf1);
		reuseTmpGeometricField<symmTensor, symmTensor, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void dev2(GeometricField<symmTensor, PatchField, GeoMesh>& res,
	          const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::dev2(res.internalField(), gf1.internalField());
		tnbLib::dev2(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> dev2(const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(new GeometricField<symmTensor, PatchField, GeoMesh>(
			IOobject("dev2" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			transform(gf1.dimensions())));
		tnbLib::dev2(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> dev2(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<symmTensor, symmTensor, PatchField, GeoMesh>::New(
				tgf1, "dev2" "(" + gf1.name() + ')', transform(gf1.dimensions())));
		tnbLib::dev2(tRes(), gf1);
		reuseTmpGeometricField<symmTensor, symmTensor, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void det(GeometricField<scalar, PatchField, GeoMesh>& res, const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::det(res.internalField(), gf1.internalField());
		tnbLib::det(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> det(const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(new GeometricField<scalar, PatchField, GeoMesh>(
			IOobject("det" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			pow3(gf1.dimensions())));
		tnbLib::det(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> det(const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<scalar, symmTensor, PatchField, GeoMesh>::New(tgf1, "det" "(" + gf1.name() + ')',
			                                                                     pow3(gf1.dimensions())));
		tnbLib::det(tRes(), gf1);
		reuseTmpGeometricField<scalar, symmTensor, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void cof(GeometricField<symmTensor, PatchField, GeoMesh>& res,
	         const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::cof(res.internalField(), gf1.internalField());
		tnbLib::cof(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> cof(const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(new GeometricField<symmTensor, PatchField, GeoMesh>(
			IOobject("cof" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			pow2(gf1.dimensions())));
		tnbLib::cof(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> cof(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<symmTensor, symmTensor, PatchField, GeoMesh>::New(
				tgf1, "cof" "(" + gf1.name() + ')', pow2(gf1.dimensions())));
		tnbLib::cof(tRes(), gf1);
		reuseTmpGeometricField<symmTensor, symmTensor, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
	
	template <template<class> class PatchField, class GeoMesh>
	void inv(GeometricField<symmTensor, PatchField, GeoMesh>& res,
	         const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::inv(res.internalField(), gf1.internalField());
		tnbLib::inv(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> inv(const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(new GeometricField<symmTensor, PatchField, GeoMesh>(
			IOobject("inv" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			inv(gf1.dimensions())));
		tnbLib::inv(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> inv(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<symmTensor, symmTensor, PatchField, GeoMesh>::New(
				tgf1, "inv" "(" + gf1.name() + ')', inv(gf1.dimensions())));
		tnbLib::inv(tRes(), gf1);
		reuseTmpGeometricField<symmTensor, symmTensor, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void hinv(GeometricField<symmTensor, PatchField, GeoMesh>& res,
	          const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::hinv(res.internalField(), gf1.internalField());
		tnbLib::hinv(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> hinv(const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(new GeometricField<symmTensor, PatchField, GeoMesh>(
			IOobject("hinv" "(" + gf1.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			hinv(gf1.dimensions())));
		tnbLib::hinv(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> hinv(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<symmTensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<symmTensor, symmTensor, PatchField, GeoMesh>::New(
				tgf1, "hinv" "(" + gf1.name() + ')', hinv(gf1.dimensions())));
		tnbLib::hinv(tRes(), gf1);
		reuseTmpGeometricField<symmTensor, symmTensor, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}


		// * * * * * * * * * * * * * * * global operators  * * * * * * * * * * * * * //

		
	template <template<class> class PatchField, class GeoMesh>
	void hdual(GeometricField<vector, PatchField, GeoMesh>& res,
	           const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tnbLib::hdual(res.internalField(), gf1.internalField());
		tnbLib::hdual(res.boundaryField(), gf1.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> operator *(const GeometricField<symmTensor, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<vector, PatchField, GeoMesh>> tRes(new GeometricField<vector, PatchField, GeoMesh>(
			IOobject("*" + gf1.name(), gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE), gf1.mesh(),
			transform(gf1.dimensions())));
		tnbLib::hdual(tRes(), gf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<vector, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<vector, symmTensor, PatchField, GeoMesh>::New(
				tgf1, "*" + gf1.name(), transform(gf1.dimensions())));
		tnbLib::hdual(tRes(), gf1);
		reuseTmpGeometricField<vector, symmTensor, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

		
	template <template<class> class PatchField, class GeoMesh>
	void dot(GeometricField<tensor, PatchField, GeoMesh>& res, const GeometricField<symmTensor, PatchField, GeoMesh>& gf1,
	         const GeometricField<symmTensor, PatchField, GeoMesh>& gf2)
	{
		tnbLib::dot(res.internalField(), gf1.internalField(), gf2.internalField());
		tnbLib::dot(res.boundaryField(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(const GeometricField<symmTensor, PatchField, GeoMesh>& gf1,
	                                                            const GeometricField<symmTensor, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<tensor, PatchField, GeoMesh>> tRes(new GeometricField<tensor, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '&' + gf2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() & gf2.dimensions()));
		tnbLib::dot(tRes(), gf1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(const GeometricField<symmTensor, PatchField, GeoMesh>& gf1,
	                                                            const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>&
	                                                            tgf2)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<tensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<tensor, symmTensor, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + '&' + gf2.name() + ')',
			                                                                     gf1.dimensions() & gf2.dimensions()));
		tnbLib::dot(tRes(), gf1, gf2);
		reuseTmpGeometricField<tensor, symmTensor, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf1,
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<tensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<tensor, symmTensor, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '&' + gf2.name() + ')',
			                                                                     gf1.dimensions() & gf2.dimensions()));
		tnbLib::dot(tRes(), gf1, gf2);
		reuseTmpGeometricField<tensor, symmTensor, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<tensor, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<tensor, symmTensor, symmTensor, symmTensor, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '&' + gf2.name() + ')', gf1.dimensions() & gf2.dimensions()));
		tnbLib::dot(tRes(), gf1, gf2);
		reuseTmpTmpGeometricField<tensor, symmTensor, symmTensor, symmTensor, PatchField, GeoMesh>::clear(tgf1, tgf2);
		return tRes;
	}
		
	template <template<class> class PatchField, class GeoMesh>
	void dot(GeometricField<tensor, PatchField, GeoMesh>& res, const dimensioned<symmTensor>& dt1,
	         const GeometricField<symmTensor, PatchField, GeoMesh>& gf2)
	{
		tnbLib::dot(res.internalField(), dt1.value(), gf2.internalField());
		tnbLib::dot(res.boundaryField(), dt1.value(), gf2.boundaryField());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(const dimensioned<symmTensor>& dt1,
	                                                            const GeometricField<symmTensor, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<tensor, PatchField, GeoMesh>> tRes(new GeometricField<tensor, PatchField, GeoMesh>(
			IOobject('(' + dt1.name() + '&' + gf2.name() + ')', gf2.instance(), gf2.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf2.mesh(), dt1.dimensions() & gf2.dimensions()));
		tnbLib::dot(tRes(), dt1, gf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(const symmTensor& t1,
	                                                            const GeometricField<symmTensor, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<symmTensor>(t1) & gf2;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(const dimensioned<symmTensor>& dt1,
	                                                            const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>&
	                                                            tgf2)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<tensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<tensor, symmTensor, PatchField, GeoMesh>::New(tgf2, '(' + dt1.name() + '&' + gf2.name() + ')',
			                                                                     dt1.dimensions() & gf2.dimensions()));
		tnbLib::dot(tRes(), dt1, gf2);
		reuseTmpGeometricField<tensor, symmTensor, PatchField, GeoMesh>::clear(tgf2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(const symmTensor& t1,
	                                                            const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>&
	                                                            tgf2) { return dimensioned<symmTensor>(t1) & tgf2; }

	template <template<class> class PatchField, class GeoMesh>
	void dot(GeometricField<tensor, PatchField, GeoMesh>& res, const GeometricField<symmTensor, PatchField, GeoMesh>& gf1,
	         const dimensioned<symmTensor>& dt2)
	{
		tnbLib::dot(res.internalField(), gf1.internalField(), dt2.value());
		tnbLib::dot(res.boundaryField(), gf1.boundaryField(), dt2.value());
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(const GeometricField<symmTensor, PatchField, GeoMesh>& gf1,
	                                                            const dimensioned<symmTensor>& dt2)
	{
		tmp<GeometricField<tensor, PatchField, GeoMesh>> tRes(new GeometricField<tensor, PatchField, GeoMesh>(
			IOobject('(' + gf1.name() + '&' + dt2.name() + ')', gf1.instance(), gf1.db(), IOobject::NO_READ, IOobject::NO_WRITE),
			gf1.mesh(), gf1.dimensions() & dt2.dimensions()));
		tnbLib::dot(tRes(), gf1, dt2);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(const GeometricField<symmTensor, PatchField, GeoMesh>& gf1,
	                                                            const symmTensor& t2)
	{
		return gf1 & dimensioned<symmTensor>(t2);
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf1, const dimensioned<symmTensor>& dt2)
	{
		const GeometricField<symmTensor, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<tensor, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<tensor, symmTensor, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '&' + dt2.name() + ')',
			                                                                     gf1.dimensions() & dt2.dimensions()));
		tnbLib::dot(tRes(), gf1, dt2);
		reuseTmpGeometricField<tensor, symmTensor, PatchField, GeoMesh>::clear(tgf1);
		return tRes;
	}

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tgf1, const symmTensor& t2)
	{
		return tgf1 & dimensioned<symmTensor>(t2);
	}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <undefFieldFunctionsM.hxx>

// ************************************************************************* //