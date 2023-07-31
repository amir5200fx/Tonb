#pragma once
#ifndef _Voyage_Node_Header
#define _Voyage_Node_Header

#include <Voyage_Entity.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{

	// Forward Declarations [7/21/2023 Payvand]
	class Voyage_Edge;

	class Voyage_Node
		: public Voyage_Entity
	{

		/*Private Data*/

		Pnt2d theCoord_;

		Standard_Real theTime_;


		std::map<Standard_Integer, std::weak_ptr<Voyage_Edge>>
			theEdges_;

	protected:

		// default constructor [7/9/2023 Payvand]

		Voyage_Node()
		{}

		// constructors [7/9/2023 Payvand]

		Voyage_Node(const Standard_Integer theIndex)
			: Voyage_Entity(theIndex)
		{}

	public:

		// Public functions and operators [7/9/2023 Payvand]

		const auto& Coord() const
		{
			return theCoord_;
		}

		auto Time() const { return theTime_; }

		auto NbEdges() const { return (Standard_Integer)theEdges_.size(); }
		const auto& Edges() const { return theEdges_; }

		void SetCoord(const Pnt2d& theCoord) { theCoord_ = theCoord; }
		void SetCoord(Pnt2d&& theCoord) { theCoord_ = std::move(theCoord); }

		void SetTime(const Standard_Real theTime) { theTime_ = theTime; }

		TnbVoyage_EXPORT void ImportEdge(const std::shared_ptr<Voyage_Edge>&);
		TnbVoyage_EXPORT void RemoveEdge(const Standard_Integer theIndex);


	};

}



#endif // !_Voyage_Node_Header
