#pragma once
#ifndef _MeshBLayer2d_NodeAdaptor_Header
#define _MeshBLayer2d_NodeAdaptor_Header

#include <Global_TypeDef.hxx>

#include <map>
#include <memory>

namespace tnbLib
{

	// Forward Declarations [1/30/2023 Payvand]

	class MeshBLayer2d_Edge;

	class MeshBLayer2d_NodeAdaptor
	{

		/*Private Data*/

		std::map<Standard_Integer, std::weak_ptr<MeshBLayer2d_Edge>>
			theEdges_;

	protected:

		// default constructor [1/30/2023 Payvand]

		MeshBLayer2d_NodeAdaptor()
		{}


		// constructors [1/30/2023 Payvand]

	public:

		// Public functions and operators [1/30/2023 Payvand]

		auto NbEdges() const
		{
			return (Standard_Integer)theEdges_.size();
		}

		const auto& Edges() const
		{
			return theEdges_;
		}

		void SetEdge(const Standard_Integer theIndex, const std::shared_ptr<MeshBLayer2d_Edge>&);
	};
}

#endif // !_MeshBLayer2d_NodeAdaptor_Header
