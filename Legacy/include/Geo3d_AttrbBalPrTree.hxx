#pragma once
#ifndef _Geo3d_AttrbBalPrTree_Header
#define _Geo3d_AttrbBalPrTree_Header

#include <Geo3d_BalPrTree.hxx>
#include <Geo3d_AttrbBalPrTreeLeaf.hxx>

//#include "Pnt3d.hxx"

namespace tnbLib
{

	template<class T, class Attrb>
	class Geo3d_AttrbBalPrTree
		: public Geo3d_BalPrTreeInfo
		, public Geo3d_BalPrTreeBase
		, public Geo_SearchTree<T>
	{

	public:

		typedef typename remove_pointer<T>::type Type;
		typedef typename Type::ptType Point;

		typedef Geo3d_BalPrTreeBase Base;
		typedef Geo_SearchTree<T> geom;

		typedef Geo3d_BalPrTreeNode node;
		typedef Geo3d_AttrbBalPrTreeLeaf<T, Attrb> leafNode;
		typedef Geo3d_BalPrTreeInternal internalNode;
		typedef Entity3d_Box boxType;

	private:

		/*Private Data*/

		node* theRoot_;

		// private functions and operators [8/8/2022 Amir]

		Standard_Boolean IsFull(const leafNode* t) const
		{
			return t->Size() >= BUCKET_SIZE;
		}

		Standard_Boolean IsUnbalanced(const leafNode* leaf) const;

		void SwitchToClear(internalNode*& t);
		void Clear(node*& t);

		void SwitchToInsert(const T& theItem, const Pnt3d& theCentre, const std::shared_ptr<boxType>& theBox, internalNode*& t);
		void Insert(const T& theItem, const std::shared_ptr<boxType>& theBox, node*& t);

		void NullifyPointer(node*& t, internalNode*& Internal);
		void SwitchToRemove(const T& theItem, internalNode*& t);
		void Remove(const T& theItem, node*& t);

		void LinkInners(internalNode* t) const;
		void RemoveLeafFromNeighbors(leafNode* old) const;
		void FillNeighbors(const Geo3d_BalPrTreeOctant q, leafNode* old, internalNode* father, leafNode* t) const;

		void Balance(node*& t);

		void SwitchToSearch(const Entity3d_Box& theRegion, internalNode* t, std::list<T>& theItems) const;
		void SwitchToSearch(const Entity3d_Box& theRegion, internalNode* t, std::vector<T>& theItems) const;
		void SwitchToSearch(const Entity3d_Box& theRegion, internalNode* t, std::vector<leafNode*>& theItems) const;
		void Search(const Entity3d_Box& theBox, node* t, std::list<T>& theItems) const;
		void Search(const Entity3d_Box& theBox, node* t, std::vector<T>& theItems) const;
		void Search(const Entity3d_Box& theBox, node* t, std::vector<leafNode*>& theItems) const;

		void SwitchToRetrieveLeavesTo(internalNode* Internal, std::vector<leafNode*>& theItems) const;
		void RetrieveLeavesTo(node* t, std::vector<leafNode*>& theLeaves) const;

		void SwitchToRetrieveTo(internalNode* Internal, std::list<T>& theItems) const;
		void SwitchToRetrieveTo(internalNode* Internal, std::vector<T>& theItems) const;
		void RetrieveTo(node* t, std::list<T>& theItems) const;
		void RetrieveTo(node* t, std::vector<T>& theItems) const;

		static void UpdateFather(leafNode* t, node* inter);

	public:

		// default constructor [8/7/2022 Amir]

		Geo3d_AttrbBalPrTree()
		{}


		// constructors [8/8/2022 Amir]


		// public functions and operators [8/8/2022 Amir]

		~Geo3d_AttrbBalPrTree()
		{
			Clear();
		}

		Standard_Integer Size() const
		{
			return Base::NbItems();
		}

		Standard_Boolean IsEmpty() const
		{
			return !theRoot_;
		}

		std::vector<leafNode*> RetrieveLeaves(const Entity3d_Box& theRegion) const;

		void InsertToGeometry(const T& theItem) override;
		void InsertToGeometry(const std::vector<T>& theItems) override;

		void RemoveFromGeometry(const T& theItem) override;

		void GeometrySearch(const Standard_Real theRadius, const Pnt3d& theCentre, std::list<T>& theItems) const override;
		void GeometrySearch(const Standard_Real theRadius, const Pnt3d& theCentre, std::vector<T>& theItems) const override;
		void GeometrySearch(const Entity3d_Box& theRegion, std::list<T>& theList) const override;
		void GeometrySearch(const Entity3d_Box& theRegion, std::vector<T>& theItems) const override;
		void GeometrySearch(const Entity3d_Box& theRegion, std::vector<leafNode*>& theItems) const;

		void PostBalance();

		void Clear() override;

		void RetrieveLeavesTo(std::vector<leafNode*>&) const;
		void RetrieveLeavesTo(const Entity3d_Box& theRegion, std::vector<leafNode*>&) const;

		void RetrieveFromGeometryTo(std::list<T>& theItems) const override;
		void RetrieveFromGeometryTo(std::vector<T>& theItems) const override;
	};
}

#include <Geo3d_AttrbBalPrTreeI.hxx>

#endif // !_Geo3d_AttrbBalPrTree_Header
