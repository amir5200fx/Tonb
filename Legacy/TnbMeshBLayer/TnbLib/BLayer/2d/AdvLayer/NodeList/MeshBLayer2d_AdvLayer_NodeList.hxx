#pragma once
#ifndef _MeshBLayer2d_AdvLayer_NodeList_Header
#define _MeshBLayer2d_AdvLayer_NodeList_Header

#include <MeshBLayer_Module.hxx>
#include <Geo_PriorityList.hxx>

#include <set>
#include <memory>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	// Forward Declarations [1/31/2023 Payvand]

	class MeshBLayer2d_Node;

	namespace meshBLayerLib
	{

		class AdvLayer_NodeList
		{

			/*Private Data*/

			Geo_PriorityList<std::shared_ptr<MeshBLayer2d_Node>> theList_;

		public:

			// default constructor [1/31/2023 Payvand]

			AdvLayer_NodeList()
			{}


			// constructors [1/31/2023 Payvand]



			// Public functions and operators [1/31/2023 Payvand]

			auto Size() const
			{
				return theList_.PrioritySize();
			}

			std::shared_ptr<MeshBLayer2d_Node> Pop();

			void Push(const std::shared_ptr<MeshBLayer2d_Node>&);
			void Push(const std::vector<std::shared_ptr<MeshBLayer2d_Node>>&);

		};
	}
}

#endif // !_MeshBLayer2d_AdvLayer_NodeList_Header
