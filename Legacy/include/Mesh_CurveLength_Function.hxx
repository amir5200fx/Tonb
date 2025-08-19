#pragma once
#ifndef _Mesh_CurveLength_Function_Header
#define _Mesh_CurveLength_Function_Header

#include <NumAlg_IntegFunc.hxx>
#include <Geo_Traits.hxx>

namespace tnbLib
{

	// Forward Declarations
	template<class gCurveType, class MetricPrcsrType>
	class Mesh_CurveEntity;

	template<class gCurveType, class MetricPrcsrType = void>
	class Mesh_CurveLength_Function
		: public NumAlg_IntegFunc
	{

	public:

		typedef Mesh_CurveEntity<gCurveType, MetricPrcsrType> entity;
		typedef typename cascadeLib::pt_type_from_curve<gCurveType>::ptType Point;
		typedef typename cascadeLib::vec_type_from_point<Point>::vcType Vector;

	private:

		/*Private Data*/

		const entity& theEntity_;

	public:

		Mesh_CurveLength_Function(const entity& theEntity);

		Standard_Real Value(const Standard_Real x) const override;
	};


	template<class gCurveType>
	class Mesh_CurveLength_Function<gCurveType, void>
		: public NumAlg_IntegFunc
	{

	public:

		typedef Mesh_CurveEntity<gCurveType, void> entity;
		typedef typename cascadeLib::pt_type_from_curve<gCurveType>::ptType Point;
		typedef typename cascadeLib::vec_type_from_point<Point>::vcType Vector;

	private:

		/*Private Data*/

		const entity& theEntity_;

	public:

		Mesh_CurveLength_Function(const entity& theEntity);

		Standard_Real Value(const Standard_Real x) const override;

	};
}

#include <Mesh_CurveLength_FunctionI.hxx>

#endif // !_Mesh_CurveLength_Function_Header