#pragma once
#ifndef _MeshPost2d_AFBLayerMesh_Header
#define _MeshPost2d_AFBLayerMesh_Header

#include <MeshPostAF2d_Core.hxx>
#include <MeshPost_Module.hxx>
#include <Global_Done.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	class MeshPost2d_AFBLayerMesh
		: public MeshPostAF2d_Core
		, public Global_Done
	{

		/*Private Data*/

	public:

		// default constructor [9/1/2023 aamir]

		MeshPost2d_AFBLayerMesh()
		{}

		// constructors [9/1/2023 aamir]

		// Public functions and operators [9/1/2023 aamir]

		void Perform();



	};

}

#endif // !_MeshPost2d_AFBLayerMesh_Header
