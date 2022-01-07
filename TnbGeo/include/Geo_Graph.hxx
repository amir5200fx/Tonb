#pragma once
#ifndef _Geo_Graph_Header
#define _Geo_Graph_Header

#include <Global_Macros.hxx>
#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <map>
#include <memory>

namespace tnbLib
{

	template<class EdgeType>
	class Geo_Graph
		: public Global_Indexed
		, public Global_Named
	{

	public:

		typedef typename EdgeType::nodeType nodeType;
		typedef EdgeType edgeType;

	private:

		/*Private Data*/

		std::map
			<
			Standard_Integer, 
			std::shared_ptr<EdgeType>
			> theEdges_;
		 

	public:


		// default constructor [1/5/2022 Amir]

		Geo_Graph()
		{}


		// constructors [1/5/2022 Amir]

		Geo_Graph
		(
			const Standard_Integer theIndex, 
			const word& theName
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
		{}


		// public functions and operators [1/5/2022 Amir]

		Standard_Integer NbEdges() const
		{
			return (Standard_Integer)theEdges_.size();
		}

		const std::map
			<
			Standard_Integer,
			std::shared_ptr<EdgeType>
			>& Edges() const
		{
			return theEdges_;
		}

		std::map
			<
			Standard_Integer,
			std::shared_ptr<EdgeType>
			>& Edges()
		{
			return theEdges_;
		}

		void Insert(const Standard_Integer theIndex, const std::shared_ptr<EdgeType>&);
		void Insert(const Standard_Integer theIndex, std::shared_ptr<EdgeType>&&);

		void Remove(const Standard_Integer theIndex)
		{
			auto iter = theEdges_.find(theIndex);
			if (iter IS_EQUAL theEdges_.end())
			{
				FatalErrorIn("void Remove(const Standard_Integer theIndex)")
					<< "the item is not in the tree: " << theIndex << endl
					<< abort(FatalError);
			}

			edgeType::deAttach(theIndex);

			theEdges_.erase(iter);
		}
	};
}

#endif // !_Geo_Graph_Header
