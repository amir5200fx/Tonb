#pragma once
#ifndef _VoyageMesh_Entity_Header
#define _VoyageMesh_Entity_Header

#include <Global_TypeDef.hxx>

namespace tnbLib
{

	template<class MeshEntity>
	class VoyageMesh_Entity
		: public MeshEntity
	{

		/*Private Data*/

	public:

		//- default constructor

		//- constructors

		template<class... _Types>
		VoyageMesh_Entity(_Types&&... _Args)
			: MeshEntity(_Args...)
		{}

		//- Public functions and operators


	};

}

#endif // !_VoyageMesh_Entity_Header
