#pragma once
#ifndef _TModel_VertexAdaptor_Header
#define _TModel_VertexAdaptor_Header

#include <Standard_TypeDef.hxx>
#include <Cad_Module.hxx>
#include <Global_Serialization.hxx>

#include <memory>
#include <map>

namespace tnbLib
{

	// Forward Declarations
	class TModel_Edge;
	class TModel_Surface;

	class TModel_VertexAdaptor
	{

		typedef std::map<Standard_Integer, std::weak_ptr<TModel_Edge>>
			edgeRegister;
		typedef std::map<Standard_Integer, std::weak_ptr<TModel_Surface>>
			faceRegister;

		/*Private Data*/

		edgeRegister theEdges_;
		faceRegister theFaces_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbCad_EXPORT);

	protected:

		//- default constructor

		TModel_VertexAdaptor()
		{}

	public:

		auto NbEdges() const
		{
			return (Standard_Integer)theEdges_.size();
		}

		auto NbFaces() const
		{
			return (Standard_Integer)theFaces_.size();
		}

		const auto& Edges() const
		{
			return theEdges_;
		}

		const auto& Faces() const
		{
			return theFaces_;
		}

		TnbCad_EXPORT void ImportToEdges
		(
			const Standard_Integer theIndex,
			const std::weak_ptr<TModel_Edge>& theEdge
		);

		TnbCad_EXPORT void ImportToSurfaces
		(
			const Standard_Integer theIndex,
			const std::weak_ptr<TModel_Surface>& theFace
		);

		TnbCad_EXPORT void ImportToSurfaces_dup
		(
			const Standard_Integer theIndex,
			const std::weak_ptr<TModel_Surface>& theFace
		);

		TnbCad_EXPORT void RemoveFromEdges(const Standard_Integer theIndex);

		TnbCad_EXPORT void RemoveFromFaces(const Standard_Integer theIndex);
	};
}

#endif // !_TModel_VertexAdaptor_Header
