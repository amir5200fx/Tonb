#pragma once
#ifndef _Entity3d_PolyhedralMesh_Header
#define _Entity3d_PolyhedralMesh_Header

#include <Pnt3d.hxx>

#include <vector>

namespace tnbLib
{
	class Entity3d_PolyhedralMesh
	{
	public:
		class Face
		{
			/*Private Data*/
			std::vector<Standard_Integer> theIndices_;
		public:
			// default constructor
			Face() = default;
			// constructors
			Face(const std::vector<Standard_Integer>& theIndices)
				: theIndices_(theIndices)
			{}
			Face(std::vector<Standard_Integer>&& theIndices)
				: theIndices_(std::move(theIndices))
			{}
			// Public functions and operators
			const auto& Indices() const { return theIndices_; }

			Standard_Integer NbIndices() const { return static_cast<Standard_Integer>(theIndices_.size()); }

			void SetIndices(const std::vector<Standard_Integer>& theIndices) { theIndices_ = theIndices; }
			void SetIndices(std::vector<Standard_Integer>&& theIndices) { theIndices_ = std::move(theIndices); }
		};

		class Element
		{
			/*Private Data*/
			std::vector<Face> theFaces_;
		public:
			// default constructor
			Element() = default;
			// constructors
			Element(const std::vector<Face>& theFaces)
				: theFaces_(theFaces)
			{}
			Element(std::vector<Face>&& theFaces)
				: theFaces_(std::move(theFaces))
			{}

			// Public functions and operators
			const auto& Faces() const { return theFaces_; }
			TnbGeo_EXPORT Standard_Integer NbFaces() const;
 
			TnbGeo_EXPORT Standard_Integer NbNodes() const;
			TnbGeo_EXPORT std::vector<Standard_Integer> NodeIds() const;

			void SetFaces(const std::vector<Face>& theFaces) { theFaces_ = theFaces; }
			void SetFaces(std::vector<Face>&& theFaces) { theFaces_ = std::move(theFaces); }
		};
	private:
		/*Private Data*/
		std::vector<Pnt3d> theCoords_;
		std::vector<Element> theElements_;

	public:
		// default constructor
		Entity3d_PolyhedralMesh() = default;

		// constructors
		Entity3d_PolyhedralMesh(const std::vector<Pnt3d>& theCoords, const std::vector<Element>& theElements)
			: theCoords_(theCoords)
			, theElements_(theElements)
		{}
		Entity3d_PolyhedralMesh(std::vector<Pnt3d>&& theCoords, std::vector<Element>&& theElements)
			: theCoords_(std::move(theCoords))
			, theElements_(std::move(theElements))
		{}

		// Public functions and operators
		const auto& Coords() const { return theCoords_; }
		const auto& Elements() const { return theElements_; }

		void SetCoords(const std::vector<Pnt3d>& theCoords) { theCoords_ = theCoords; }
		void SetCoords(std::vector<Pnt3d>&& theCoords) { theCoords_ = std::move(theCoords); }
		void SetElements(const std::vector<Element>& theElements) { theElements_ = theElements; }
		void SetElements(std::vector<Element>&& theElements) { theElements_ = std::move(theElements); }

		TnbGeo_EXPORT void ExportToVtk(std::fstream& file) const;
	};
}

#endif