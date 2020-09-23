#pragma once
#ifndef _StbGMaker_Edge_Header
#define _StbGMaker_Edge_Header

#include <Entity3d_PolygonFwd.hxx>

namespace tnbLib
{

	// Forward Declarations

	template<class PlnEdge>
	class StbGMaker_Edge
		: public PlnEdge
	{

		/*Private Data*/

		std::shared_ptr<Entity3d_Polygon> theMesh3d_;

	public:

		template<class... _Types>
		StbGMaker_Edge(_Types&&... Args)
			: PlnEdge(Args...)
		{}

		const auto& Mesh3d() const
		{
			return theMesh3d_;
		}

		void SetMesh3d
		(
			const std::shared_ptr<Entity3d_Polygon>&& theMesh
		)
		{
			theMesh3d_ = std::move(theMesh);
		}

		void SetMesh3d
		(
			const std::shared_ptr<Entity3d_Polygon>& theMesh
		)
		{
			theMesh3d_ = theMesh;
		}
	};
}

#endif // !_StbGMaker_Edge_Header
