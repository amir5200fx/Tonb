#pragma once
#ifndef _Voyage_Edge_Header
#define _Voyage_Edge_Header

#include <Voyage_Entity.hxx>

#include <array>

namespace tnbLib
{

	// Forward Declarations [6/17/2023 Payvand]
	class Voyage_Node;


	class Voyage_Edge
		: public Voyage_Entity
	{

		/*Private Data*/

		std::array<std::shared_ptr<Voyage_Node>, 2> theNodes_;

	public:

		// default constructor [6/17/2023 Payvand]

		Voyage_Edge()
		{}

		// constructors [6/17/2023 Payvand]




	};
}

#endif // !_Voyage_Edge_Header
