#pragma once
#ifndef _Cad2d_EdgeEdgeTrim_Header
#define _Cad2d_EdgeEdgeTrim_Header

#include <Global_Done.hxx>
#include <Cad2d_Module.hxx>

#include <memory>
#include <map>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Cad2d_EdgeEdgeIntersection;
	class Pln_Edge;
	class Pln_Curve;

	class Cad2d_EdgeEdgeTrim
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Cad2d_EdgeEdgeIntersection> theIntersection_;

		std::map<Standard_Integer, std::shared_ptr<Pln_Curve>>
			theCurves_;


		auto& ChangeCurves()
		{
			return theCurves_;
		}

	public:

		TnbCad2d_EXPORT Cad2d_EdgeEdgeTrim();

		TnbCad2d_EXPORT Cad2d_EdgeEdgeTrim
		(
			const std::shared_ptr<Cad2d_EdgeEdgeIntersection>& theAlg
		);

		const auto& Intersection() const
		{
			return theIntersection_;
		}

		TnbCad2d_EXPORT const std::shared_ptr<Pln_Edge>& Edge0() const;

		TnbCad2d_EXPORT const std::shared_ptr<Pln_Edge>& Edge1() const;

		Standard_Integer NbCurves() const
		{
			return (Standard_Integer)theCurves_.size();
		}

		const auto& Curves() const
		{
			return theCurves_;
		}

		TnbCad2d_EXPORT std::vector<std::shared_ptr<Pln_Curve>> RetrieveCurves() const;

		TnbCad2d_EXPORT std::shared_ptr<Pln_Curve>
			SelectToTrim
			(
				const Standard_Integer theIndex
			);

		TnbCad2d_EXPORT void Perform(const Standard_Real theTol = 1.0E-6);

		void LoadIntersection
		(
			const std::shared_ptr<Cad2d_EdgeEdgeIntersection>& theAlg
		)
		{
			theIntersection_ = theAlg;
		}

		TnbCad2d_EXPORT void RetrieveCurvesTo
		(
			std::vector<std::shared_ptr<Pln_Curve>>& theCurves
		) const;
	};
}

#endif // !_Cad2d_EdgeEdgeTrim_Header
