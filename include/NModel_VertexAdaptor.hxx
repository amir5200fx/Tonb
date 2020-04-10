#pragma once
#ifndef _NModel_VertexAdaptor_Header
#define _NModel_VertexAdaptor_Header

#include <Standard_TypeDef.hxx>

#include <memory>
#include <map>

namespace tnbLib
{

	// Forward Declarations
	class NModel_Edge;
	class NModel_Surface;

	class NModel_VertexAdaptor
	{

		typedef std::map<Standard_Integer, std::weak_ptr<NModel_Edge>>
			edgeRegister;
		typedef std::map<Standard_Integer, std::weak_ptr<NModel_Surface>>
			faceRegister;

		/*Private Data*/

		edgeRegister theEdges_;
		faceRegister theFaces_;

	protected:

		NModel_VertexAdaptor()
		{}

	public:

		Standard_Integer NbEdges() const
		{
			return (Standard_Integer)theEdges_.size();
		}

		Standard_Integer NbFaces() const
		{
			return (Standard_Integer)theFaces_.size();
		}

		const edgeRegister& Edges() const
		{
			return theEdges_;
		}

		const faceRegister& Faces() const
		{
			return theFaces_;
		}

		void ImportToEdges
		(
			const Standard_Integer theIndex,
			const std::weak_ptr<NModel_Edge>& theEdge
		)
		{
			theEdges_.insert(std::make_pair(theIndex, theEdge));
		}

		void ImportToSurfaces
		(
			const Standard_Integer theIndex,
			const std::weak_ptr<NModel_Surface>& theFace
		)
		{
			theFaces_.insert(std::make_pair(theIndex, theFace));
		}

		void ImportToSurfaces_dup
		(
			const Standard_Integer theIndex,
			const std::weak_ptr<NModel_Surface>& theFace
		);

		void RemoveFromEdges(const Standard_Integer theIndex);

		void RemoveFromFaces(const Standard_Integer theIndex);
	};
}

#endif // !_NModel_VertexAdaptor_Header