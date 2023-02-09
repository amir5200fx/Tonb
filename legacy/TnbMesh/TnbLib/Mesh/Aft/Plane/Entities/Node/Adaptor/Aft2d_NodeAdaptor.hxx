#pragma once
#ifndef _Aft2d_NodeAdaptor_Header
#define _Aft2d_NodeAdaptor_Header

#include <Mesh_Module.hxx>
#include <Global_Serialization.hxx>

#include <map>
#include <memory>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	namespace legLib
	{

		// Forward Declarations [2/1/2023 Payvand]
		class Aft2d_Edge;
		class Aft2d_Element;

		class Aft2d_NodeAdaptor
		{

			/*Private Data*/

			std::map<Standard_Integer, std::shared_ptr<Aft2d_Edge>>
				theEdges_;
			std::map<Standard_Integer, std::shared_ptr<Aft2d_Element>>
				theElements_;

			std::map<Standard_Integer, std::shared_ptr<Aft2d_Edge>>
				theFronts_;

			// Private functions and operators [2/1/2023 Payvand]

			TNB_SERIALIZATION(TnbLegMesh_EXPORT);

		protected:

			// default constructor [2/1/2023 Payvand]

			Aft2d_NodeAdaptor()
			{}


			// COnstructors [2/1/2023 Payvand]


		public:

			// Public functions and operators [2/1/2023 Payvand]

			auto NbEdges() const
			{
				return (Standard_Integer)theEdges_.size();
			}

			auto NbElements() const
			{
				return (Standard_Integer)theElements_.size();
			}

			auto NbFronts() const
			{
				return (Standard_Integer)theFronts_.size();
			}

			const auto& Edges() const
			{
				return theEdges_;
			}

			const auto& Elements() const
			{
				return theElements_;
			}

			const auto& Fronts() const
			{
				return theFronts_;
			}

			std::shared_ptr<Aft2d_Edge> RemoveFromEdges(const Standard_Integer theIndex);
			std::shared_ptr<Aft2d_Element> RemoveFromElements(const Standard_Integer theIndex);
			std::shared_ptr<Aft2d_Edge> RemoveFromFronts(const Standard_Integer theIndex);

			void InsertToEdges(const Standard_Integer theIndex, const std::shared_ptr<Aft2d_Edge>&);
			void InsertToElements(const Standard_Integer theIndex, const std::shared_ptr<Aft2d_Element>&);

			void InsertToFronts(const Standard_Integer theIndex, const std::shared_ptr<Aft2d_Edge>&);
		};
	}
}

#endif // !_Aft2d_NodeAdaptor_Header
