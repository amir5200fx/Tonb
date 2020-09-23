#pragma once
#ifndef _Cad2d_Modeler_Registry_Header
#define _Cad2d_Modeler_Registry_Header

#include <Standard_TypeDef.hxx>

#include <map>
#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Vertex;
	class Pln_Edge;

	namespace cad2dLib
	{

		class Modeler_Registry
		{

			/*Private Data*/

			std::map<Standard_Integer, std::shared_ptr<Pln_Edge>>
				theEdges_;

		protected:

			Modeler_Registry();


			std::shared_ptr<Pln_Edge>
				RemoveEdgeFromRegistry
				(
					const Standard_Integer theIndex
				);

			void RegisterToEdges
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Pln_Edge>& theEdge
			);

		public:

			static const std::shared_ptr<Pln_Edge> null_edge;

			Standard_Boolean 
				IsContainEdge
				(
					const Standard_Integer theIndex
				) const;

			Standard_Boolean 
				IsContain
				(
					const std::shared_ptr<Pln_Edge>& theEdge
				) const;

			auto NbEdges() const
			{
				return (Standard_Integer)theEdges_.size();
			}

			const auto& Edges() const
			{
				return theEdges_;
			}

			std::shared_ptr<Pln_Edge>
				SelectEdge
				(
					const Standard_Integer theIndex
				) const;

			static Standard_Boolean
				IsNull
				(
					const std::shared_ptr<Pln_Edge>& theEdge
				);
		};
	}
}

#endif // !_Cad2d_Modeler_Registry_Header
