#pragma once
#ifndef _Mesh3d_SetEdgeSources_Header
#define _Mesh3d_SetEdgeSources_Header

#include <Mesh_Module.hxx>
#include <Mesh3d_SetSourcesNodeFwd.hxx>
#include <GeoMesh3d_SingleBackgroundFwd.hxx>
#include <Entity3d_ChainFwd.hxx>
#include <Global_Done.hxx>

#include <memory>

namespace tnbLib
{

	class Mesh3d_SetEdgeSources
		: public Global_Done
	{

		/*Private Data*/

		const std::vector<Standard_Real>& theValues_;
		std::shared_ptr<Entity3d_Chain> theEdges_;

		std::shared_ptr<GeoMesh3d_SingleBackground> theMesh_;

		Standard_Real theTolerance_;

	public:


		static TnbMesh_EXPORT const Standard_Real DEFAULT_TOLERANCE;

		// default constructor [8/18/2022 Amir]


		// constructors [8/18/2022 Amir]

		Mesh3d_SetEdgeSources
		(
			const std::vector<Standard_Real>& theValues,
			const std::shared_ptr<Entity3d_Chain>& theEdges,
			const std::shared_ptr<GeoMesh3d_SingleBackground>& theMesh
		)
			: theValues_(theValues)
			, theEdges_(theEdges)
			, theMesh_(theMesh)
			, theTolerance_(DEFAULT_TOLERANCE)
		{}

		Mesh3d_SetEdgeSources
		(
			const std::vector<Standard_Real>& theValues,
			const std::shared_ptr<Entity3d_Chain>& theEdges,
			const std::shared_ptr<GeoMesh3d_SingleBackground>& theMesh,
			const Standard_Real theTol
		)
			: theValues_(theValues)
			, theEdges_(theEdges)
			, theMesh_(theMesh)
			, theTolerance_(theTol)
		{}


		// public functions and operators [8/18/2022 Amir]

		auto Tolerance() const
		{
			return theTolerance_;
		}

		const auto& Values() const
		{
			return theValues_;
		}

		const auto& Edges() const
		{
			return theEdges_;
		}

		const auto& Mesh() const
		{
			return theMesh_;
		}

		TnbMesh_EXPORT void Perform();


		void SetTolerance(const Standard_Real theTol)
		{
			theTolerance_ = theTol;
		}

	};
}

#endif // !_Mesh3d_SetEdgeSources_Header
