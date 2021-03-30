#pragma once
#ifndef _Cad3d_TModelManager_Header
#define _Cad3d_TModelManager_Header

#include <TModel_VertexManager.hxx>
#include <TModel_PairedManager.hxx>
#include <TModel_SurfaceManager.hxx>
#include <Cad_Module.hxx>

namespace tnbLib
{

	class Cad3d_TModelManager
	{

		/*Private Data*/

		std::shared_ptr<TModel_VertexManager> theVertices_;
		std::shared_ptr<TModel_PairedManager> theEdges_;
		std::shared_ptr<TModel_SurfaceManager> theSurfaces_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbCad_EXPORT);


	protected:

		Cad3d_TModelManager()
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

		TnbCad_EXPORT Standard_Integer NbCorners() const;

		TnbCad_EXPORT Standard_Integer NbSegments() const;

		TnbCad_EXPORT Standard_Integer NbFaces() const;

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

		TnbCad_EXPORT std::vector<std::shared_ptr<TModel_Vertex>>
			RetrieveCorners() const;

		TnbCad_EXPORT std::vector<std::shared_ptr<TModel_Paired>>
			RetrieveSegments() const;

		TnbCad_EXPORT std::vector<std::shared_ptr<TModel_Surface>>
			RetrieveFaces() const;

		TnbCad_EXPORT void RetrieveCornersTo
		(
			std::vector<std::shared_ptr<TModel_Vertex>>& theVertices
		) const;

		TnbCad_EXPORT void RetrieveSegmentsTo
		(
			std::vector<std::shared_ptr<TModel_Paired>>& theEdges
		) const;

		TnbCad_EXPORT void RetrieveFacesTo
		(
			std::vector<std::shared_ptr<TModel_Surface>>& theSurfaces
		) const;
	};
}

#endif // !_Cad3d_TModelManager_Header
