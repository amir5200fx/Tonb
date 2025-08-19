#pragma once
#ifndef _Cad2d_Subdivide_Header
#define _Cad2d_Subdivide_Header

#include <Global_Done.hxx>
#include <Cad2d_Module.hxx>

#include <memory>
#include <vector>
#include <tuple>

namespace tnbLib
{

	// Forward Declarations
	class Pln_CmpEdge;
	class Cad2d_Plane;
	class Cad2d_PlanePlaneIntersection;
	class Cad2d_IntsctEntity_Pair;
	class Geo_ApprxCurve_Info;

	class Cad2d_Subdivide
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Cad2d_PlanePlaneIntersection> theAlgorithm_;


		std::shared_ptr<Cad2d_Plane> thePlane0_;
		std::shared_ptr<Cad2d_Plane> thePlane1_;

		auto& ChangePlane0()
		{
			return thePlane0_;
		}

		auto& ChangePlane1()
		{
			return thePlane1_;
		}

	public:


		static TnbCad2d_EXPORT std::shared_ptr<Geo_ApprxCurve_Info> myApprxCurveInfo;
		static TnbCad2d_EXPORT Standard_Boolean overrideMyApprxCurveInfo;

		//- default constructor

		Cad2d_Subdivide()
		{}


		//- constructors


		//- public functions and operators

		const auto& IntersectionAlgorithm() const
		{
			return theAlgorithm_;
		}

		const auto& ModifiedPlane0() const
		{
			return thePlane0_;
		}

		const auto& ModifiedPlane1() const
		{
			return thePlane1_;
		}

		TnbCad2d_EXPORT void Perform();

		void LoadIntersectionAlgorithm
		(
			const std::shared_ptr<Cad2d_PlanePlaneIntersection>& theAlgorithm
		)
		{
			theAlgorithm_ = theAlgorithm;
		}

		void SetOverrideApprxInfo(const Standard_Boolean approxInfo)
		{
			overrideMyApprxCurveInfo = approxInfo;
		}

		void SetOverrideApprxInfo(const std::shared_ptr<Geo_ApprxCurve_Info>& approxInfo)
		{
			myApprxCurveInfo = approxInfo;
		}

		static TnbCad2d_EXPORT std::tuple<std::shared_ptr<Pln_CmpEdge>, std::shared_ptr<Pln_CmpEdge>>
			RetrieveSubEdges
			(
				const std::vector<std::shared_ptr<Cad2d_IntsctEntity_Pair>>& theEntities
			);
	};
}

#endif // !_Cad2d_Subdivide_Header
