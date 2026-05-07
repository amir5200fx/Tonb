#pragma once
#ifndef _Mesh3d_SetSources_Header
#define _Mesh3d_SetSources_Header

#include <Mesh3d_SetSourcesNodeFwd.hxx>
#include <GeoMesh3d_SingleBackgroundFwd.hxx>
#include <Global_Done.hxx>

#include <memory>

namespace tnbLib
{

	class Mesh3d_SetSources
		: public Global_Done
	{

		/*Private Data*/

		const std::vector<std::shared_ptr<meshLib::setSources::Node>>& theValues_;

		std::shared_ptr<GeoMesh3d_SingleBackground> theMesh_;

		Standard_Real theTolerance_;

	public:

		static const Standard_Real DEFAULT_TOLERANCE;

		// default constructor [8/9/2022 Amir]


		// constructors [8/9/2022 Amir]

		Mesh3d_SetSources
		(
			const std::vector<std::shared_ptr<meshLib::setSources::Node>>& theValues,
			const std::shared_ptr<GeoMesh3d_SingleBackground>& theMesh
		)
			: theValues_(theValues)
			, theMesh_(theMesh)
			, theTolerance_(DEFAULT_TOLERANCE)
		{}

		Mesh3d_SetSources
		(
			const std::vector<std::shared_ptr<meshLib::setSources::Node>>& theValues,
			const std::shared_ptr<GeoMesh3d_SingleBackground>& theMesh,
			const Standard_Real theTol
		)
			: theValues_(theValues)
			, theMesh_(theMesh)
			, theTolerance_(theTol)
		{}

		// public functions and operators [8/9/2022 Amir]

		auto Tolerance() const
		{
			return theTolerance_;
		}

		const auto& Values() const
		{
			return theValues_;
		}

		const auto& Mesh() const
		{
			return theMesh_;
		}

		void Perform();


		void SetMesh(const std::shared_ptr<GeoMesh3d_SingleBackground>& theMesh)
		{
			theMesh_ = theMesh;
		}

		void SetMesh(std::shared_ptr<GeoMesh3d_SingleBackground>&& theMesh)
		{
			theMesh_ = std::move(theMesh);
		}

		void SetTolerance(const Standard_Real theTol)
		{
			theTolerance_ = theTol;
		}

	};
}

#endif // !_Mesh3d_SetSources_Header
