#pragma once
#ifndef _ModelPx_Parameter_Header
#define _ModelPx_Parameter_Header

#include <ModelPx_Entity.hxx>

namespace tnbLib
{

	class ModelPx_Parameter
		: public ModelPx_Entity
	{

		/*Private Data*/

	protected:

		//- default constructor

		ModelPx_Parameter()
		{}

		//- constructors

		ModelPx_Parameter(const Standard_Integer theIndex, const word& theName)
			: ModelPx_Entity(theIndex, theName)
		{}


	public:

		//- public functions and operators


	};
}

#endif // !_ModelPx_Parameter_Header
