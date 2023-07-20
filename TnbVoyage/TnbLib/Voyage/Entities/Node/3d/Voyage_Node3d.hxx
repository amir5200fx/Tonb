#pragma once
#ifndef _Voyage_Node3d_Header
#define _Voyage_Node3d_Header

#include <Voyage_Node.hxx>

namespace tnbLib
{

	class Voyage_Node3d
		: public Voyage_Node
	{

		/*Private Data*/

		Standard_Real theTime_;

	public:

		// default constructor [6/17/2023 Payvand]

		Voyage_Node3d()
			: theTime_(0)
		{}


		// constructors [6/17/2023 Payvand]


		// Public functions and operators [6/17/2023 Payvand]

		auto Time() const { return theTime_; }

		void SetTime(const Standard_Real theTime) { theTime_ = theTime; }

	};
}

#endif // !_Voyage_Node3d_Header
