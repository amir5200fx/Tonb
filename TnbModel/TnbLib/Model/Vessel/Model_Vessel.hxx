#pragma once
#ifndef _Model_Vessel_Header
#define _Model_Vessel_Header

#include <Model_Entity.hxx>

#include <vector>

class Geom_Surface;

#include <Standard_Handle.hxx>

namespace tnbLib
{

	class Model_Vessel
		: public Model_Entity
	{

		/*Private Data*/

		std::vector<Handle(Geom_Surface)> thePatches_;

	protected:

		// default constructor [12/21/2022 Payvand]

		Model_Vessel()
		{}

		// constructors [12/21/2022 Payvand]

		Model_Vessel(const Standard_Integer theIndex, const word& theName)
			: Model_Entity(theIndex, theName)
		{}


		// Protected functions and operators [12/21/2022 Payvand]

		auto& PatchesRef()
		{
			return thePatches_;
		}


	public:

		// Public functions and operators [12/21/2022 Payvand]

		virtual Standard_Boolean IsDisplacement() const
		{
			return Standard_False;
		}

		const auto& Patches() const
		{
			return thePatches_;
		}

	};
}

#endif // !_Model_Vessel_Header
