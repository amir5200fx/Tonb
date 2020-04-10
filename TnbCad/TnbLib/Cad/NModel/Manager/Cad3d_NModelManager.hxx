#pragma once
#ifndef _Cad3d_NModelManager_Header
#define _Cad3d_NModelManager_Header

#include <NModel_VertexManager.hxx>
#include <NModel_SegmentManager.hxx>
#include <NModel_SurfaceManager.hxx>

namespace tnbLib
{

	class Cad3d_NModelManager
	{

		/*Private Data*/

		std::shared_ptr<NModel_VertexManager> theVertices_;
		std::shared_ptr<NModel_SegmentManager> theEdges_;
		std::shared_ptr<NModel_SurfaceManager> theSurfaces_;


	protected:

		Cad3d_NModelManager()
		{}

		auto& ChangeCorners()
		{
			return theVertices_;
		}

		auto& ChangeSegments()
		{
			return theEdges_;
		}

		auto& ChangeFaces()
		{
			return theSurfaces_;
		}

	public:

		Standard_Integer NbCorners() const;

		Standard_Integer NbSegments() const;

		Standard_Integer NbFaces() const;

		const auto& Corners() const
		{
			return theVertices_;
		}

		const auto& Segments() const
		{
			return theEdges_;
		}

		const auto& Faces() const
		{
			return theSurfaces_;
		}

		std::vector<std::shared_ptr<NModel_Vertex>>
			RetrieveCorners() const;

		std::vector<std::shared_ptr<NModel_Segment>>
			RetrieveSegments() const;

		std::vector<std::shared_ptr<NModel_Surface>>
			RetrieveFaces() const;

		void RetrieveCornersTo
		(
			std::vector<std::shared_ptr<NModel_Vertex>>& theVertices
		) const;

		void RetrieveSegmentsTo
		(
			std::vector<std::shared_ptr<NModel_Segment>>& theEdges
		) const;

		void RetrieveFacesTo
		(
			std::vector<std::shared_ptr<NModel_Surface>>& theSurfaces
		) const;
	};
}

#endif // !_Cad3d_NModelManager_Header
