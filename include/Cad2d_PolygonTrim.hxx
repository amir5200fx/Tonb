#pragma once
#ifndef _Cad2d_PolygonTrim_Header
#define _Cad2d_PolygonTrim_Header

#include <Global_Done.hxx>

#include <vector>
#include <memory>
#include <map>

namespace tnbLib
{

	// FOrward Declarations
	class Pln_Edge;
	class Pln_Curve;

	class Cad2d_PolygonTrim
		: public Global_Done
	{

		typedef std::vector<std::shared_ptr<Pln_Edge>> edgeList;

		/*Private Data*/

		std::shared_ptr<edgeList> theEdges_;

		std::map<Standard_Integer, std::shared_ptr<Pln_Curve>>
			theCurves_;

		std::vector<Standard_Integer> theIndices_;


		auto& ChangeSubCurves()
		{
			return theCurves_;
		}

		auto& ChangeIndices()
		{
			return theIndices_;
		}

	public:

		Cad2d_PolygonTrim();

		Cad2d_PolygonTrim
		(
			const std::shared_ptr<edgeList>& theEdges
		);
		
		const auto& Edges() const
		{
			return theEdges_;
		}

		const auto& Indices() const
		{
			return theIndices_;
		}

		const auto& SubCurves() const
		{
			return theCurves_;
		}

		void Perform(const Standard_Integer theTol = 1.0E-6);

		void LoadEdges
		(
			const std::shared_ptr<edgeList>& theEdges
		)
		{
			theEdges_ = theEdges;
		}
	};
}

#endif // !_Cad2d_PolygonTrim_Header
