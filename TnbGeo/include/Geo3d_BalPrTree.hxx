#pragma once
#ifndef _Geo3d_BalPrTree_Header
#define _Geo3d_BalPrTree_Header

#include <Geo3d_BalPrTreeLeaf.hxx>
#include <Geo3d_BalPrTreeInternal.hxx>
#include <Geo_SearchTree.hxx>

namespace tnbLib
{

	enum class Geo3d_BalPrTreeOctant
	{
		Fwd_SW,
		Fwd_SE,
		Fwd_NW,
		Fwd_NE,
		Bwd_SW,
		Bwd_SE,
		Bwd_NW,
		Bwd_NE
	};

	class Geo3d_BalPrTreeBase
		: public Geo_SearchTree_Base
	{

	public:

		static TnbGeo_EXPORT const Standard_Integer DEFAULT_UNBALANCING;

	private:

		/*Private Data*/

		Standard_Integer theNbSubDivide_;
		Standard_Integer theMaxUnbalacing_;

		mutable Standard_Boolean IsBalanced_;

	protected:

		// default constructor [7/5/2022 Amir]

		Geo3d_BalPrTreeBase()
			: theNbSubDivide_(0)
			, theMaxUnbalacing_(DEFAULT_UNBALANCING)
			, IsBalanced_(Standard_False)
		{}

		// constructors [7/5/2022 Amir]


		auto NbSubdivide() const
		{
			return theNbSubDivide_;
		}

		auto& NbSubdivideRef()
		{
			return theNbSubDivide_;
		}

		auto& IsBalancedRef() const
		{
			return IsBalanced_;
		}

	public:

		// public functions and operators [7/5/2022 Amir]

		auto MaxUnbalancing() const
		{
			return theMaxUnbalacing_;
		}

		/*auto IsBalanced() const
		{
			return IsBalanced_;
		}*/

		void SetMaxUnbalancing(const Standard_Integer n)
		{
			theMaxUnbalacing_ = n;
		}

		static TnbGeo_EXPORT Geo3d_BalPrTreeOctant 
			CalcOctant
			(
				const Pnt3d& theCoord, 
				const Pnt3d& theCentre
			);

		static TnbGeo_EXPORT Standard_Boolean IsBwdSW(const Pnt3d& theCoord, const Pnt3d& theCentre);
		static TnbGeo_EXPORT Standard_Boolean IsBwdSE(const Pnt3d& theCoord, const Pnt3d& theCentre);
		static TnbGeo_EXPORT Standard_Boolean IsBwdNE(const Pnt3d& theCoord, const Pnt3d& theCentre);
		static TnbGeo_EXPORT Standard_Boolean IsBwdNW(const Pnt3d& theCoord, const Pnt3d& theCentre);

		static TnbGeo_EXPORT Standard_Boolean IsFwdSW(const Pnt3d& theCoord, const Pnt3d& theCentre);
		static TnbGeo_EXPORT Standard_Boolean IsFwdSE(const Pnt3d& theCoord, const Pnt3d& theCentre);
		static TnbGeo_EXPORT Standard_Boolean IsFwdNE(const Pnt3d& theCoord, const Pnt3d& theCentre);
		static TnbGeo_EXPORT Standard_Boolean IsFwdNW(const Pnt3d& theCoord, const Pnt3d& theCentre);
	};


	struct Geo3d_BalPrTreeInfo
	{

		int BUCKET_SIZE;
		int MAX_INNER_SUBDIVIDE;


		//- default constructor

		Geo3d_BalPrTreeInfo()
			: BUCKET_SIZE(8)
			, MAX_INNER_SUBDIVIDE(20)
		{}
	};

	template<class T>
	class Geo3d_BalPrTree
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
		typedef Geo3d_BalPrTreeLeaf<T> leafNode;
		typedef Geo3d_BalPrTreeInternal internalNode;
		typedef Entity3d_Box boxType;

	private:

		/*Private Data*/

		node* theRoot_;

		// private functions and operators [7/5/2022 Amir]


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
		void Search(const Entity3d_Box& theBox, node* t, std::list<T>& theItems) const;
		void Search(const Entity3d_Box& theBox, node* t, std::vector<T>& theItems) const;

		void SwitchToRetrieveLeavesTo(internalNode* Internal, std::vector<leafNode*>& theItems) const;
		void RetrieveLeavesTo(node* t, std::vector<leafNode*>& theLeaves) const;

		void SwitchToRetrieveTo(internalNode* Internal, std::list<T>& theItems) const;
		void SwitchToRetrieveTo(internalNode* Internal, std::vector<T>& theItems) const;
		void RetrieveTo(node* t, std::list<T>& theItems) const;
		void RetrieveTo(node* t, std::vector<T>& theItems) const;

		static void UpdateFather(leafNode* t, node* inter);

	public:


		// default constructor [7/9/2022 Amir]

		Geo3d_BalPrTree()
		{}


		// constructors [7/9/2022 Amir]


		// public functions and operators [7/9/2022 Amir]

		~Geo3d_BalPrTree()
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

		Standard_Boolean IsBalanced() const;

		void InsertToGeometry(const T& theItem) override;
		void InsertToGeometry(const std::vector<T>& theItems) override;

		void RemoveFromGeometry(const T& theItem) override;

		void GeometrySearch(const Standard_Real theRadius, const Pnt3d& theCentre, std::list<T>& theItems) const override;
		void GeometrySearch(const Standard_Real theRadius, const Pnt3d& theCentre, std::vector<T>& theItems) const override;
		void GeometrySearch(const Entity3d_Box& theRegion, std::list<T>& theList) const override;
		void GeometrySearch(const Entity3d_Box& theRegion, std::vector<T>& theItems) const override;

		void PostBalance();

		void Clear() override;

		void RetrieveLeavesTo(std::vector<leafNode*>&) const;

		void RetrieveFromGeometryTo(std::list<T>& theItems) const override;
		void RetrieveFromGeometryTo(std::vector<T>& theItems) const override;
	};
}

#include <Geo3d_BalPrTreeI.hxx>

#endif // !_Geo3d_BalPrTree_Header
