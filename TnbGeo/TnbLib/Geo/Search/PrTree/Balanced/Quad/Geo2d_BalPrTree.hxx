#pragma once
#ifndef _Geo2d_BalPrTree_Header
#define _Geo2d_BalPrTree_Header

#include <Geo2d_BalPrTreeLeaf.hxx>
#include <Geo2d_BalPrTreeInternal.hxx>
#include <Geo_SearchTree.hxx>

namespace tnbLib
{

	enum class Geo2d_BalPrTreeQuad
	{
		SW,
		SE,
		NW,
		NE
	};

	class Geo2d_BalPrTreeBase
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

		// default constructor [11/9/2022 Amir]

		Geo2d_BalPrTreeBase()
			: theNbSubDivide_(0)
			, theMaxUnbalacing_(DEFAULT_UNBALANCING)
			, IsBalanced_(Standard_False)
		{}


		// constructors [11/9/2022 Amir]


		// Protected functions and operators [11/9/2022 Amir]

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

		// Public functions and operators [11/9/2022 Amir]

		auto MaxUnbalancing() const
		{
			return theMaxUnbalacing_;
		}

		void SetMaxUnbalancing(const Standard_Integer n)
		{
			theMaxUnbalacing_ = n;
		}

		static TnbGeo_EXPORT Geo2d_BalPrTreeQuad
			CalcQuadrant
			(
				const Pnt2d& theCoord,
				const Pnt2d& theCentre
			);

		static TnbGeo_EXPORT Standard_Boolean IsSW(const Pnt2d& theCoord, const Pnt2d& theCentre);
		static TnbGeo_EXPORT Standard_Boolean IsSE(const Pnt2d& theCoord, const Pnt2d& theCentre);
		static TnbGeo_EXPORT Standard_Boolean IsNE(const Pnt2d& theCoord, const Pnt2d& theCentre);
		static TnbGeo_EXPORT Standard_Boolean IsNW(const Pnt2d& theCoord, const Pnt2d& theCentre);
	};


	struct Geo2d_BalPrTreeInfo
	{

		int BUCKET_SIZE;
		int MAX_INNER_SUBDIVIDE;


		//- default constructor

		Geo2d_BalPrTreeInfo()
			: BUCKET_SIZE(8)
			, MAX_INNER_SUBDIVIDE(20)
		{}
	};

	template<class T>
	class Geo2d_BalPrTree
		: public Geo2d_BalPrTreeInfo
		, public Geo2d_BalPrTreeBase
		, public Geo_SearchTree<T>
	{

	public:

		typedef typename remove_pointer<T>::type Type;
		typedef typename Type::ptType Point;

		typedef Geo2d_BalPrTreeBase Base;
		typedef Geo_SearchTree<T> geom;

		typedef Geo2d_BalPrTreeNode node;
		typedef Geo2d_BalPrTreeLeaf<T> leafNode;
		typedef Geo2d_BalPrTreeInternal internalNode;
		typedef Entity2d_Box boxType;

	private:

		/*Private Data*/

		node* theRoot_;

		// Private functions and operators [11/9/2022 Amir]

		Standard_Boolean IsFull(const leafNode* t) const
		{
			return t->Size() >= BUCKET_SIZE;
		}

		Standard_Boolean IsUnbalanced(const leafNode* leaf) const;

		void SwitchToClear(internalNode*& t);
		void Clear(node*& t);

		void SwitchToInsert
		(
			const T& theItem,
			const Pnt2d& theCentre,
			const std::shared_ptr<boxType>& theBox,
			internalNode*& t
		);

		void Insert(const T& theItem, const std::shared_ptr<boxType>& theBox, node*& t);

		void NullifyPointer(node*& t, internalNode*& Internal);
		void SwitchToRemove(const T& theItem, internalNode*& t);
		void Remove(const T& theItem, node*& t);

		void LinkInners(internalNode* t) const;
		void RemoveLeafFromNeighbors(leafNode* old) const;
		void FillNeighbors
		(
			const Geo2d_BalPrTreeQuad q,
			leafNode* old,
			internalNode* father, 
			leafNode* t
		) const;

		void Balance(node*& t);

		template<class ObjectType>
		void Subdivide
		(
			node*&, 
			Standard_Boolean(*)(const Entity2d_Box&, const ObjectType*), 
			const ObjectType*,
			const Standard_Integer theLev,
			const Standard_Integer theMaxLev
		);

		void SwitchToSearch(const Entity2d_Box& theRegion, internalNode* t, std::list<T>& theItems) const;
		void SwitchToSearch(const Entity2d_Box& theRegion, internalNode* t, std::vector<T>& theItems) const;
		void Search(const Entity2d_Box& theBox, node* t, std::list<T>& theItems) const;
		void Search(const Entity2d_Box& theBox, node* t, std::vector<T>& theItems) const;

		static void SwitchToRetrieveLeavesTo(internalNode* Internal, std::vector<leafNode*>& theItems);
		//static void RetrieveLeavesTo(node* t, std::vector<leafNode*>& theLeaves);

		static void SwitchToRetrieveTo(internalNode* Internal, std::list<T>& theItems);
		static void SwitchToRetrieveTo(internalNode* Internal, std::vector<T>& theItems);	

		virtual leafNode* CreateNewLeaf(const std::shared_ptr<Entity2d_Box>& b);

		static void UpdateFather(leafNode* t, node* inter);

	public:


		// default constructor [11/9/2022 Amir]

		Geo2d_BalPrTree()
		{}


		// constructors [11/9/2022 Amir]


		// Public functions and operators [11/9/2022 Amir]

		~Geo2d_BalPrTree()
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

		auto Root() const
		{
			return theRoot_;
		}

		Standard_Boolean IsBalanced() const;

		void InsertToGeometry(const T& theItem) override;
		void InsertToGeometry(const std::vector<T>& theItems) override;

		void RemoveFromGeometry(const T& theItem) override;

		void GeometrySearch(const Standard_Real theRadius, const Pnt2d& theCentre, std::list<T>& theItems) const override;
		void GeometrySearch(const Standard_Real theRadius, const Pnt2d& theCentre, std::vector<T>& theItems) const override;
		void GeometrySearch(const Entity2d_Box& theRegion, std::list<T>& theList) const override;
		void GeometrySearch(const Entity2d_Box& theRegion, std::vector<T>& theItems) const override;

		void PostBalance();

		template<class ObjectType>
		void PostSubdivide
		(
			const leafNode*, 
			Standard_Boolean(*)(const Entity2d_Box&, const ObjectType*),
			const ObjectType*, 
			const Standard_Integer theMaxLev
		);

		template<class ObjectType>
		void PostSubdivide
		(
			node*&,
			Standard_Boolean(*)(const Entity2d_Box&, const ObjectType*), 
			const ObjectType*,
			const Standard_Integer theMaxLev
		);

		void Clear() override;

		void RetrieveLeavesTo(std::vector<leafNode*>&) const;
		static void RetrieveLeavesTo(node* t, std::vector<leafNode*>&);

		void RetrieveFromGeometryTo(std::list<T>& theItems) const override;
		void RetrieveFromGeometryTo(std::vector<T>& theItems) const override;

		static void RetrieveTo(node* t, std::list<T>& theItems);
		static void RetrieveTo(node* t, std::vector<T>& theItems);
	};
}

#include <Geo2d_BalPrTreeI.hxx>

#endif // !_Geo2d_BalPrTree_Header
