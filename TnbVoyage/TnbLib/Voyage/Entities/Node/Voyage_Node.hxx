#pragma once
#ifndef _Voyage_Node_Header
#define _Voyage_Node_Header

#include <Voyage_Entity.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{

	class Voyage_Node
		: public Voyage_Entity
	{

		/*Private Data*/

		Pnt2d theCoord_;

	protected:

		// default constructor [7/9/2023 Payvand]

		Voyage_Node()
		{}

		// constructors [7/9/2023 Payvand]

		Voyage_Node(const Standard_Integer theIndex, const word& theName)
			: Voyage_Entity(theIndex, theName)
		{}

	public:

		// Public functions and operators [7/9/2023 Payvand]

		const auto& Coord() const
		{
			return theCoord_;
		}

		void SetCoord(const Pnt2d& theCoord) { theCoord_ = theCoord; }
		void SetCoord(Pnt2d&& theCoord) { theCoord_ = std::move(theCoord); }

	};

}



#endif // !_Voyage_Node_Header
