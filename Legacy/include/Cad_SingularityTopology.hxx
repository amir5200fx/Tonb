#pragma once
#ifndef _Cad_SingularityTopology_Header
#define _Cad_SingularityTopology_Header

#include <Cad_SingularityTraits.hxx>
#include <Geo2d_TopoChainAnalysis.hxx>
#include <Global_Done.hxx>

#include <list>

#include "Geo2d_TopoChainAnalysis.hxx"

namespace tnbLib
{

	template<class SurfType>
	class Cad_SingularityTopology
		: public Global_Done
	{

	public:

		typedef typename cad_singularity_traits<SurfType>::parCurveType parCurveType;
		typedef typename cad_singularity_traits<SurfType>::parWireType parWireType;

		typedef typename Geo2d_TopoChainAnalysis::edgeType edgeType;

		typedef std::map<std::shared_ptr<edgeType>, std::shared_ptr<parCurveType>> edgeToCurveMap;
		typedef std::map<std::shared_ptr<parCurveType>, std::shared_ptr<Entity2d_Chain>> curveToChainMap;

	private:

		/*Private Data*/

		std::map<std::shared_ptr<edgeType>, std::shared_ptr<parCurveType>> theEdgeToCurve_;
		std::map<std::shared_ptr<parCurveType>, std::shared_ptr<Entity2d_Chain>> theCurveToChain_;

		std::shared_ptr<Geo2d_TopoChainAnalysis> theTopology_;


		// inputs [4/2/2022 Amir]
		const std::vector<std::shared_ptr<parWireType>>& theWires_;
		const std::vector<std::shared_ptr<parCurveType>>& theHorizons_;

	public:

		// default constructor [4/2/2022 Amir]


		// constructors [4/2/2022 Amir]

		Cad_SingularityTopology
		(
			const std::vector<std::shared_ptr<parWireType>>& theWires,
			const std::vector<std::shared_ptr<parCurveType>>& theHorizons
		)
			: theWires_(theWires)
			, theHorizons_(theHorizons)
		{}


		// public functions and operators [4/2/2022 Amir]

		const auto& EdgeToCurveMap() const
		{
			return theEdgeToCurve_;
		}

		const auto& CurveToChainMap() const
		{
			return theCurveToChain_;
		}

		const auto& Topology() const
		{
			return theTopology_;
		}

		const auto& Wires() const
		{
			return theWires_;
		}

		const auto& Horizons() const
		{
			return theHorizons_;
		}

		void Perform();

		static std::shared_ptr<Geo2d_TopoChainAnalysis>
			GetTopology
			(
				const std::map<std::shared_ptr<parCurveType>, std::shared_ptr<Entity2d_Chain>>&, 
				std::map<std::shared_ptr<edgeType>, std::shared_ptr<parCurveType>>&
			);

		
		
	};
}

#include <Cad_SingularityTopologyI.hxx>

#include <Cad_gSingularityTopology.hxx>

#endif // !_Cad_SingularityTopology_Header
