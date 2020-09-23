#pragma once
#ifndef _StbGMaker_HullCreator_Header
#define _StbGMaker_HullCreator_Header

#include <StbGMaker_Alg.hxx>
#include <StbGMaker_EntityCreator.hxx>
#include <Marine_ShapesFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Geo_xDistb;

	class StbGMaker_HullCreator
		: public StbGMaker_Alg
		, public StbGMaker_EntityCreator
	{

		/*Private Data*/

	protected:

		template<class... _Types>
		StbGMaker_HullCreator(_Types&&... _Args)
			: StbGMaker_EntityCreator(_Args...)
		{}

	public:

		virtual Standard_Boolean HasShape() const = 0;

	};
}

#endif // !_StbGMaker_HullCreator_Header
