#pragma once
#ifndef _Cad2d_Modeler_Registry_Header
#define _Cad2d_Modeler_Registry_Header

#include <Cad2d_Module.hxx>
#include <Global_Serialization.hxx>
#include <Global_TypeDef.hxx>

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


			/*private functions and operators*/
			TNB_SERIALIZATION(TnbCad2d_EXPORT);

			auto& ChangeEdges()
			{
				return theEdges_;
			}

		protected:

			TnbCad2d_EXPORT Modeler_Registry();


			TnbCad2d_EXPORT std::shared_ptr<Pln_Edge>
				RemoveEdgeFromRegistry
				(
					const Standard_Integer theIndex
				);

			TnbCad2d_EXPORT void RegisterToEdges
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Pln_Edge>& theEdge
			);

		public:

			static TnbCad2d_EXPORT const std::shared_ptr<Pln_Edge> null_edge;

			TnbCad2d_EXPORT Standard_Boolean
				IsContainEdge
				(
					const Standard_Integer theIndex
				) const;

			TnbCad2d_EXPORT Standard_Boolean
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

			TnbCad2d_EXPORT std::shared_ptr<Pln_Edge>
				SelectEdge
				(
					const Standard_Integer theIndex
				) const;

			static TnbCad2d_EXPORT Standard_Boolean
				IsNull
				(
					const std::shared_ptr<Pln_Edge>& theEdge
				);
		};
	}
}

#endif // !_Cad2d_Modeler_Registry_Header
