#pragma once
#ifndef _Mesh3d_SetSourcesNodeFwd_Header
#define _Mesh3d_SetSourcesNodeFwd_Header

namespace tnbLib
{

	// Forward Declarations [8/10/2022 Amir]

	template<class Point, class Value>
	class Mesh_SetSourcesNode;

	class Pnt3d;

	namespace meshLib
	{
		namespace setSources
		{

			typedef Mesh_SetSourcesNode<Pnt3d, void>
				Node;
		}
	}
}

#endif // !_Mesh3d_SetSourcesNodeFwd_Header
