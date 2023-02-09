#pragma once
#ifndef _Geo_KnitChain_Header
#define _Geo_KnitChain_Header

#include <Global_Done.hxx>
#include <Entity_Polygon.hxx>
#include <Entity_StaticData.hxx>
#include <Knit_ChainNode_Type.hxx>
#include <Knit_ChainRegistry.hxx>

#include <vector>
#include <memory>

//#include "Geo3d_GraphNode.hxx"
//#include "Geo3d_KnitChainTraits.hxx"

namespace tnbLib
{

	// Forward Declarations [1/5/2022 Amir]

	template<class KnitTraits>
	class Geo_KnitChain
		: public Knit_ChainRegistry
		<
		typename KnitTraits::nodeType, 
		typename KnitTraits::edgeType
		>
		, public Global_Done
	{

	public:

		typedef typename KnitTraits::graphType graphType;
		typedef typename KnitTraits::nodeType nodeType;
		typedef typename KnitTraits::edgeType edgeType;
		typedef typename nodeType::Point Point;

		typedef Entity_Polygon<Point> polyType;

		typedef Knit_ChainRegistry
			<
			typename KnitTraits::nodeType,
			typename KnitTraits::edgeType
			> knitReg;

	private:

		/*Private Data*/

		std::shared_ptr<graphType> theGraph_;


		// private functions and operators [1/3/2022 Amir]

		std::shared_ptr<nodeType> Next(const std::shared_ptr<nodeType>&);
		std::shared_ptr<nodeType> FindStart(const Knit_ChainNode_Type) const;
		std::shared_ptr<polyType> GetPolygon(const std::shared_ptr<nodeType>&);

		void SetTypes();

	public:
	

		// default constructor [1/3/2022 Amir]

		Geo_KnitChain()
		{}

		// constructors [1/3/2022 Amir]


		// public functions and operators [1/3/2022 Amir]

		const auto& Graph() const
		{
			return theGraph_;
		}
			 
		void Perform();
		void Import(const Entity_StaticData<Point, connectivity::dual>& theChain);
	};
}

#include <Geo_KnitChainI.hxx>

#endif // !_Geo_KnitChain_Header
