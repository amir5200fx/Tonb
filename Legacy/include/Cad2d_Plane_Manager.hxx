#pragma once
#ifndef _Cad2d_Plane_Manager_Header
#define _Cad2d_Plane_Manager_Header

#include <Cad2d_Module.hxx>
#include <Global_Serialization.hxx>
#include <Global_TypeDef.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	template<class EntityType>
	class Cad_EntityManager;

	class Pln_Entity;
	class Pln_Edge;
	class Pln_Vertex;

	namespace cad2dLib
	{

		class Plane_Manager
		{

			/*Private Data*/

			std::shared_ptr<Cad_EntityManager<Pln_Vertex>> theVertices_;
			std::shared_ptr<Cad_EntityManager<Pln_Edge>> theEdges_;

			/*private functions and operators*/
			TNB_SERIALIZATION(TnbCad2d_EXPORT);

		protected:

			Plane_Manager()
			{}


			auto& ChangeCorners()
			{
				return theVertices_;
			}

			auto& ChangeSegments()
			{
				return theEdges_;
			}

		public:

			TnbCad2d_EXPORT Standard_Integer NbCorners() const;

			TnbCad2d_EXPORT Standard_Integer NbSegments() const;

			const auto& Corners() const
			{
				return theVertices_;
			}

			const auto& Segments() const
			{
				return theEdges_;
			}

			TnbCad2d_EXPORT void RetrieveCornersTo
			(
				std::vector<std::shared_ptr<Pln_Entity>>& theEntities
			) const;

			TnbCad2d_EXPORT void RetrieveSegmentsTo
			(
				std::vector<std::shared_ptr<Pln_Entity>>& theEntities
			) const;
		};
	}
}

#endif // !_Cad2d_Plane_Manager_Header
