#pragma once
#ifndef _MeshBLayer2d_Entity_Header
#define _MeshBLayer2d_Entity_Header

#include <MeshBLayer_Module.hxx>
#include <Global_Indexed.hxx>

#include <memory>

namespace tnbLib
{

	class MeshBLayer2d_Entity
		: public Global_Indexed
		, public std::enable_shared_from_this<MeshBLayer2d_Entity>
	{

		/*Private Data*/

	protected:

		// default constructor [1/30/2023 Payvand]

		MeshBLayer2d_Entity()
		{}


		// constructors [1/30/2023 Payvand]

		explicit MeshBLayer2d_Entity(const Standard_Integer theIndex)
			: Global_Indexed(theIndex)
		{}

	public:

		// Public functions and operators [1/30/2023 Payvand]

		virtual ~MeshBLayer2d_Entity()
		{}
	};
}

#endif // !_MeshBLayer2d_Entity_Header
