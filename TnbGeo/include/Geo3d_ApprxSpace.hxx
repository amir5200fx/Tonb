#pragma once
#ifndef _Geo3d_ApprxSpace_Header
#define _Geo3d_ApprxSpace_Header

#include <Geo3d_ApprxSpaceNode_Internal.hxx>
#include <Geo3d_ApprxSpaceNode_Leaf.hxx>
#include <Geo3d_ApprxSpaceOctant.hxx>
#include <Entity3d_Box.hxx>

namespace tnbLib
{

	class Geo3d_ApprxSpace_Base
	{

		/*Private Data*/

		Standard_Integer theMinLev_;
		Standard_Integer theMaxLev_;
		Standard_Integer theMaxUnbalacing_;

		Standard_Integer theSize_;

		Standard_Boolean IsBalanced_;

	protected:

		static const Standard_Integer DEFAULT_MIN_LEV;
		static const Standard_Integer DEFAULT_MAX_LEV;
		static const Standard_Integer DEFAULT_UNBALANCING;

		// default constructor [6/24/2022 Amir]

		Geo3d_ApprxSpace_Base()
			: theMinLev_(DEFAULT_MIN_LEV)
			, theMaxLev_(DEFAULT_MAX_LEV)
			, theMaxUnbalacing_(DEFAULT_UNBALANCING)
			, theSize_(0)
			, IsBalanced_(Standard_False)
		{}


		auto& SizeRef()
		{
			return theSize_;
		}

		auto& IsBalancedRef()
		{
			return IsBalanced_;
		}

	public:

		// public functions and operators [6/24/2022 Amir]

		auto MinLev() const
		{
			return theMinLev_;
		}

		auto MaxLev() const
		{
			return theMaxLev_;
		}

		auto MaxUnbalancing() const
		{
			return theMaxUnbalacing_;
		}

		auto Size() const
		{
			return theSize_;
		}

		auto IsBalanced() const
		{
			return IsBalanced_;
		}

		void SetMinLev(const Standard_Integer n)
		{
			theMinLev_ = n;
		}

		void SetMaxLev(const Standard_Integer n)
		{
			theMaxLev_ = n;
		}

		void SetMaxUnbalancing(const Standard_Integer n)
		{
			theMaxUnbalacing_ = n;
		}
	};

	template<class T>
	class Geo3d_ApprxSpace
		: public Geo3d_ApprxSpace_Base
	{

		/*Private Data*/


		// inputs [6/24/2022 Amir]

		const T* theObject_;

		Geo3d_ApprxSpaceNode* theRoot_;

		Entity3d_Box theDomain_;

		Standard_Boolean(*theSubdivider)(const Entity3d_Box&, const T*);


		// private functions and operators [6/24/2022 Amir]

		Standard_Boolean IsUnbalance(const Geo3d_ApprxSpaceNode_Leaf* leaf) const;

		void Subdivide(Geo3d_ApprxSpaceNode*& t) const;
		void ForceSubdivide(Geo3d_ApprxSpaceNode*& t) const;

		void LinkInners(Geo3d_ApprxSpaceNode_Internal* t) const;
		void RemoveLeafFromNeighbors(Geo3d_ApprxSpaceNode_Leaf* old) const;
		void FillNeighbors
		(
			const Geo3d_ApprxSpaceOctant q,
			Geo3d_ApprxSpaceNode_Leaf* old, 
			Geo3d_ApprxSpaceNode_Internal* father,
			Geo3d_ApprxSpaceNode_Leaf* t
		) const;

		void Balance(Geo3d_ApprxSpaceNode* &t);

		void Clear(Geo3d_ApprxSpaceNode*& t);


		// static functions [6/24/2022 Amir]

		static Geo3d_ApprxSpaceNode_Leaf* CreateLeaf(const Standard_Integer theLev, const Entity3d_Box& b);
		static void UpdateFather(Geo3d_ApprxSpaceNode_Leaf* node, Geo3d_ApprxSpaceNode* inter);

	public:

		// default constructor [6/24/2022 Amir]


		// public functions and operators [6/24/2022 Amir]

		const auto& Domain() const
		{
			return theDomain_;
		}

		void SetObject(const T*);
		void SetSubdivider(Standard_Boolean(*fun)(const Entity3d_Box&, const T*));

		void SetDomain(const Entity3d_Box& theDomain)
		{
			theDomain_ = theDomain;
		}

		void SetDomain(Entity3d_Box&& theDomain)
		{
			theDomain_ = std::move(theDomain);
		}


		// static functions and operators [6/24/2022 Amir]

		static Geo3d_ApprxSpaceOctant CalcOctant(const Pnt3d&, const Pnt3d& centre);
	};
}

#include <Geo3d_ApprxSpaceI.hxx>

#endif // !_Geo3d_ApprxSpace_Header
