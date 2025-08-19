#pragma once
#ifndef _StbGMaker_Edge_Header
#define _StbGMaker_Edge_Header

#include <Entity3d_PolygonFwd.hxx>
#include <Global_Serialization.hxx>
#include <StbGMaker_Module.hxx>

namespace tnbLib
{

	// Forward Declarations

	template<class PlnEdge>
	class StbGMaker_Edge
		: public PlnEdge
	{

		/*Private Data*/

		std::shared_ptr<Entity3d_Polygon> theMesh3d_;


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

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


#include <StbGMaker_EdgeI.hxx>

#endif // !_StbGMaker_Edge_Header
