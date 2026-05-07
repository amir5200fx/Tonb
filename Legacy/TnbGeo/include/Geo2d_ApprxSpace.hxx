#pragma once
#ifndef _Geo2d_ApprxSpace_Header
#define _Geo2d_ApprxSpace_Header

#include <Geo2d_ApprxSpaceNode_Internal.hxx>
#include <Geo2d_ApprxSpaceNode_Leaf.hxx>
#include <Geo2d_ApprxSpaceQuadrant.hxx>

namespace tnbLib
{

	template<class T>
	class Geo2d_ApprxSpace
	{

		/*private Data*/


		const T* theObject_;

		Geo2d_ApprxSpaceNode* theRoot_;

		Entity2d_Box theDomain_;

		Standard_Integer theMinLevel_;
		Standard_Integer theMaxLevel_;
		Standard_Integer theMaxUnbalancing_;

		Standard_Integer theNbItems_;

		Standard_Boolean(*theSubdivider)(const Entity2d_Box&, const T*);
		Standard_Boolean IsBalanced_;

		//- private functions and operators

		Standard_Boolean IsUnbalance(const Geo2d_ApprxSpaceNode_Leaf* leaf) const;

		void Subdivide(Geo2d_ApprxSpaceNode*& t) const;
		void ForcedSubdivide(Geo2d_ApprxSpaceNode*& theNode) const;

		void InnerLinks(Geo2d_ApprxSpaceNode_Internal* t) const;
		void RemoveLeafFromNeighbors(Geo2d_ApprxSpaceNode_Leaf* old) const;
		void FillNeighbors(const Geo2d_ApprxSpaceQuadrant q, Geo2d_ApprxSpaceNode_Leaf* old, Geo2d_ApprxSpaceNode_Internal* father, Geo2d_ApprxSpaceNode_Leaf* t) const;

		void Balance(Geo2d_ApprxSpaceNode* &t);

		void RetrieveTo(Geo2d_ApprxSpaceNode* t, std::vector<Geo2d_ApprxSpaceNode*>& nodes) const;
		void RetrieveTo(Geo2d_ApprxSpaceNode* t, std::vector<Entity2d_Box>& boxes) const;

		void Clear(Geo2d_ApprxSpaceNode*& t);

		static Geo2d_ApprxSpaceNode_Leaf* CreateLeaf(const Standard_Integer theLev, const Entity2d_Box& b);
		static void UpdateFather(Geo2d_ApprxSpaceNode_Leaf* node, Geo2d_ApprxSpaceNode* inter);

	public:

		Geo2d_ApprxSpace()
			: theNbItems_(0)
			, theRoot_(NULL)
			, theMinLevel_(2)
			, theMaxLevel_(6)
			, theMaxUnbalancing_(2)
			, theObject_(NULL)
			, theSubdivider(NULL)
			, IsBalanced_(Standard_False)
		{}

		~Geo2d_ApprxSpace();

		void SetDomain(const Entity2d_Box& domain);
		void SetObject(const T*);
		void SetSubdivider(Standard_Boolean(*fun)(const Entity2d_Box&, const T*));
		void SetMaxLevel(const Standard_Integer lev);
		void SetMinLevel(const Standard_Integer lev);
		void SetMaxUnbalancingLevel(const Standard_Integer lev);

		void Init();
		void Perform();
		void Perform(std::vector<Geo2d_ApprxSpaceNode*>& nodes);

		void PostBalance();

		void Clear();

		std::vector<Geo2d_ApprxSpaceNode*> RetrieveNodes() const;
		std::vector<Entity2d_Box> RetrieveBoxes() const;

		void RetrieveNodesTo(std::vector<Geo2d_ApprxSpaceNode*>& nodes) const;
		void RetrieveBoxesTo(std::vector<Entity2d_Box>& boxes) const;

		static Geo2d_ApprxSpaceQuadrant CalcQuadrant(const Pnt2d&, const Pnt2d& centre);
	};
}

#include <Geo2d_ApprxSpaceI.hxx>

#endif // !_Geo2d_ApprxSpace_Header
