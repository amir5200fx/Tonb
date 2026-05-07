#pragma once
#ifndef _Cad_TModelManager_Header
#define _Cad_TModelManager_Header

#include <TModel_CornerManager.hxx>
#include <TModel_SegmentManager.hxx>
#include <TModel_FaceManager.hxx>
#include <Cad_Module.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Cad_SolidMaker;

	class Cad_TModelManager
	{

		friend class Cad_SolidMaker;

		/*Private Data*/

		std::shared_ptr<TModel_CornerManager> theVertices_;
		std::shared_ptr<TModel_SegmentManager> theEdges_;
		std::shared_ptr<TModel_FaceManager> theSurfaces_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbCad_EXPORT);


	protected:

		Cad_TModelManager()
		{}

		auto& CornersRef()
		{
			return theVertices_;
		}

		auto& SegmentsRef()
		{
			return theEdges_;
		}

		auto& FacesRef()
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

#endif // !_Cad_TModelManager_Header
