#pragma once
#ifndef _Mesh_CurveRemesh_Header
#define _Mesh_CurveRemesh_Header

#include <Global_Done.hxx>
#include <Entity_Box.hxx>
#include <Entity_StaticData.hxx>
#include <Mesh_VariationRateInfo.hxx>
#include <Mesh_CurveRemeshTraits.hxx>
#include <Mesh_Curve_Info.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	template<class CurveType>
	class Mesh_CurveRemesh
		: public Global_Done
	{

	public:

		typedef typename Mesh_CurveRemeshTraits<CurveType>::Point Point;
		typedef typename Mesh_CurveRemeshTraits<CurveType>::BackMesh backMesh;
		typedef typename Mesh_CurveRemeshTraits<CurveType>::SizeMap sizeMap;
		typedef Entity_StaticData<Point, connectivity::dual> chainData;
		typedef Entity_Box<Point> box;

	private:

		/*Private Data*/

		Standard_Real theBaseSize_;
		Standard_Real theMinSize_;

		Standard_Real theUnderRelaxation_;

		Standard_Real theSpanAngle_;

		Standard_Integer theMaxNbIterations_;
		Standard_Integer theMaxNbSmoothing_;
		Standard_Integer theNbSamples_;

		Standard_Integer theMinSubdivision_;
		Standard_Integer theMaxSubdivision_;
		Standard_Integer theUnbalancing_;

		Standard_Boolean useRandSamples_;

		Standard_Real theIterTolerance_;
		Standard_Real theSmoothingFactor_;

		Mesh_VariationRateInfo theRate_;
		
		std::shared_ptr<Mesh_Curve_Info> theInfo_;

		std::shared_ptr<backMesh> theBackmesh_;
		std::shared_ptr<chainData> theChain_;
		std::shared_ptr<box> theBoundaingBox_;

		std::vector<std::shared_ptr<CurveType>> theCurves_;


		/*Private functions and operators*/

		Standard_Real Discretize(const std::shared_ptr<sizeMap>&);

	public:

		static TnbMesh_EXPORT unsigned short verbose;

		//- default constructor

		Mesh_CurveRemesh();


		//- public functions and operators

		Standard_Integer MaxNbIterations() const;
		Standard_Integer MaxNbSmoothing() const;
		Standard_Integer NbSamples() const;

		Standard_Integer MinNbSubdivisions() const;
		Standard_Integer MaxNbSubdivisions() const;
		Standard_Integer UnbalancingLev() const;

		Standard_Boolean IsUsedRandSamples() const;

		Standard_Real BaseSize() const;
		Standard_Real MinSize() const;
		Standard_Real UnderRelaxation() const;
		Standard_Real SpanAngle() const;
		Standard_Real IterTolerance() const;
		Standard_Real SmoothingFactor() const;

		Mesh_VariationRateInfo VariationRate() const;

		const std::shared_ptr<Mesh_Curve_Info>& MeshInfo() const;
		const std::shared_ptr<backMesh>& BackgroundMesh() const;
		const std::shared_ptr<chainData>& Chain() const;
		const std::shared_ptr<box>& BoundingBox() const;

		const std::vector<std::shared_ptr<CurveType>>& Curves() const;

		void Perform();

		void SetBaseSize(const Standard_Real);
		void SetMinSize(const Standard_Real);
		void SetUnderRelaxation(const Standard_Real);
		void SetSpanAngle(const Standard_Real);

		void SetMaxNbIterations(const Standard_Integer);
		void SetMaxNbSmoothing(const Standard_Integer);

		void SetIterTolerance(const Standard_Real);
		void SetSmoothingFactor(const Standard_Real);

		void SetVariationRate(const Mesh_VariationRateInfo);

		void LoadCurves(const std::vector<std::shared_ptr<CurveType>>&);
		void LoadCurves(std::vector<std::shared_ptr<CurveType>>&&);
	};
}

#include <Mesh_CurveRemeshI.hxx>

#endif // !_Mesh_CurveRemesh_Header
