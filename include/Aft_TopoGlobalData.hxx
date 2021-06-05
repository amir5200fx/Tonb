#pragma once
#ifndef _Aft_TopoGlobalData_Header
#define _Aft_TopoGlobalData_Header

#include <Standard_TypeDef.hxx>
#include <Aft_TypeTraits.hxx>

#include <memory>

namespace tnbLib
{

	template<class ElemntType, int dim = 2>
	class Aft_TopoGlobalData
	{

	public:

		typedef typename sub_type<ElemntType, ElemntType::rank - 1>::type edgeType;
		typedef typename sub_type<ElemntType, ElemntType::rank - 2>::type nodeType;
		typedef ElemntType elmntType;

	private:

		/*Private Data*/


		//- private functions and operators

		void RemoveFromTopology(const std::shared_ptr<edgeType>& theEdge, const Standard_Boolean bndCheck);

	public:

		void AttachToMeshNodes(const std::shared_ptr<elmntType>& theElement);
		void AttachToMeshNodes(const std::shared_ptr<edgeType>& theEdge);

		void AttachToFrontNodes(const std::shared_ptr<edgeType>& theEdge);

		void deAttachFromMesh(const std::shared_ptr<elmntType>& theElement);
		void deAttachFromMesh(const std::shared_ptr<edgeType>& theEdge);

		void deAttachFromFront(const std::shared_ptr<edgeType>& theEdge);


	};
}

#include <Aft_TopoGlobalDataI.hxx>

#endif // !_Aft_TopoGlobalData_Header
