#pragma once
#ifndef _Geo_TopoChainAnalysis_Header
#define _Geo_TopoChainAnalysis_Header

#include <Geo_TopoChainAnalysis_Entity.hxx>
#include <Entity_StaticData.hxx>
#include <Knit_ChainRegistry.hxx>
#include <Knit_ChainNode_Type.hxx>
#include <Global_Done.hxx>

#include <map>

namespace tnbLib
{

	template<class NodeType, class EdgeType>
	class Geo_TopoChainAnalysisBase
		: public Knit_ChainRegistry<NodeType, EdgeType>
	{

		/*Private Data*/

	protected:

		// default constructor [4/1/2022 Amir]

		Geo_TopoChainAnalysisBase()
		{}

		// public functions and operators [4/1/2022 Amir]

	};

	template<class ChainTraits>
	class Geo_TopoChainAnalysis
		: public Global_Done
		, public Geo_TopoChainAnalysisBase<typename ChainTraits::nodeType, typename ChainTraits::edgeType>
	{

	public:
		
		typedef typename ChainTraits::nodeType nodeType;
		typedef typename ChainTraits::edgeType edgeType;
		typedef typename nodeType::ptType Point;

		typedef Geo_TopoChainAnalysis_Entity<edgeType> entityType;

		typedef Geo_TopoChainAnalysisBase<typename ChainTraits::nodeType, typename ChainTraits::edgeType>
			base;

	private:

		/*Private Data*/

		std::map<Standard_Integer, std::shared_ptr<entityType>> theRegister_;

		Standard_Integer theMaxIndex_;


		// private functions and operators [4/1/2022 Amir]

		std::shared_ptr<nodeType> Next(const std::shared_ptr<nodeType>&, std::shared_ptr<edgeType>&);
		std::shared_ptr<nodeType> FindStart(const Knit_ChainNode_Type) const;

		std::shared_ptr<entityType> GetEntity(const std::shared_ptr<nodeType>&);

		std::vector<std::shared_ptr<nodeType>> GetNodes() const;
		std::vector<std::shared_ptr<edgeType>> GetEdges() const;

		void SetTypes();
		void CompleteTopology();
		void UpdateNodeTypes(const std::shared_ptr<nodeType>&) const;

	public:


		// default constructor [4/1/2022 Amir]

		Geo_TopoChainAnalysis()
			: theMaxIndex_(0)
		{}


		// public functions and operators [4/1/2022 Amir]

		auto NbEntities() const
		{
			return (Standard_Integer)theRegister_.size();
		}

		const auto& Entities() const
		{
			return theRegister_;
		}

		std::shared_ptr<entityType> deAttachEntity(const Standard_Integer theIndex);

		void Perform();

		void Import(const Entity_StaticData<Point, connectivity::dual>& theChain);
		void reLink();
		void reReisterEdges();

		void DestroyEntity(const Standard_Integer theIndex);

		void Descrete();

		void RemoveFromRegistry(const Standard_Integer theIndex);
	};
}

#include <Geo_TopoChainAnalysisI.hxx>

#endif // !_Geo_TopoChainAnalysis_Header
