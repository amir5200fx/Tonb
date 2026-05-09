#pragma once
#ifndef _Geo_GraphNode_Header
#define _Geo_GraphNode_Header

#include <Global_Macros.hxx>
#include <Global_Indexed.hxx>
#include <Global_AccessMethod.hxx>
#include <Geo_GraphNodeAdaptor.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <memory>
#include <map>

namespace tnbLib
{

	template<class NodeTraits>
	class Geo_GraphNode
		: public Global_Indexed
		, public Geo_GraphNodeAdaptor<typename NodeTraits::nodeAdaptType>
	{

	public:

		typedef typename NodeTraits::edgeType edgeType;
		typedef Geo_GraphNodeAdaptor<typename NodeTraits::nodeAdaptType> adaptor;
		typedef typename NodeTraits::ptType Point;

	private:

		/*Private Data*/

		Point theCoord_;

		std::map
			<
			Standard_Integer,
			std::weak_ptr<edgeType>
			> theEdges_;

	public:

		typedef Point ptType;

		// default constructor [1/5/2022 Amir]

		Geo_GraphNode()
		{}


		// constructors [1/5/2022 Amir]

		explicit Geo_GraphNode
		(
			const Standard_Integer theIndex
		)
			: Global_Indexed(theIndex)
		{}

		Geo_GraphNode
		(
			const Standard_Integer theIndex,
			const Point& theCoord
		)
			: Global_Indexed(theIndex)
			, theCoord_(theCoord)
		{}

		Geo_GraphNode
		(
			const Standard_Integer theIndex,
			Point&& theCoord
		)
			: Global_Indexed(theIndex)
			, theCoord_(std::move(theCoord))
		{}


		virtual ~Geo_GraphNode()
		{}


		// public functions and operators [1/5/2022 Amir]

		Standard_Integer NbEdges() const
		{
			return (Standard_Integer)theEdges_.size();
		}

		const std::map
			<
			Standard_Integer,
			std::weak_ptr<edgeType>
			>& Edges() const
		{
			return theEdges_;
		}

		std::map
			<
			Standard_Integer,
			std::weak_ptr<edgeType>
			>& Edges()
		{
			return theEdges_;
		}

		Standard_Boolean IsManifold() const;
		Standard_Boolean IsBoundary() const;
		Standard_Boolean IsOrphan() const;

		std::vector<std::weak_ptr<edgeType>> RetrieveEdges() const;

		void InsertToEdges(const Standard_Integer theIndex, const std::shared_ptr<edgeType>& theEdge);
		void InsertToEdges(const Standard_Integer theIndex, std::shared_ptr<edgeType>&& theEdge);

		void RemoveFromEdges(const Standard_Integer theIndex);
		void ClearEdges();

		//- Macros
		GLOBAL_ACCESS_SINGLE(Point, Coord)
	};
}

#include <Geo_GraphNodeI.hxx>

#endif // !_Geo_GraphNode_Header
