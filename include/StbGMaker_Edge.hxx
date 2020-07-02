#pragma once
#ifndef _StbGMaker_Edge_Header
#define _StbGMaker_Edge_Header

#include <Pln_Edge.hxx>
#include <Entity3d_PolygonFwd.hxx>

namespace tnbLib
{

	// Forward Declarations

	class StbGMaker_Edge
		: public Pln_Edge
	{

		/*Private Data*/

		std::shared_ptr<Entity3d_Polygon> theMesh3d_;

	public:

		template<class... _Types>
		StbGMaker_Edge(_Types&&... Args)
			: Pln_Edge(Args...)
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
