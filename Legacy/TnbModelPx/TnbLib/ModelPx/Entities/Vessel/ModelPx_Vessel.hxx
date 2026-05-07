#pragma once
#ifndef _ModelPx_Vessel_Header
#define _ModelPx_Vessel_Header

#include <ModelPx_Entity.hxx>

namespace tnbLib
{

	class ModelPx_Vessel
		: public ModelPx_Entity
	{

		/*Private Data*/

	protected:


		template<class... _Types>
		ModelPx_Vessel(_Types&&... _Args)
			: ModelPx_Entity(_Args...)
		{}

	public:


		//- public functions and operators

		ModelPx_Type Type() const override
		{
			return ModelPx_Type::vessel;
		}
	};
}

#endif // !_ModelPx_Vessel_Header
