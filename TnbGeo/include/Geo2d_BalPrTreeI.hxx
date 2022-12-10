#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
template<class T>
inline Standard_Boolean
tnbLib::Geo2d_BalPrTree<T>::IsUnbalanced
(
	const leafNode * leaf
) const
{
	if (leaf->SNeighbors().size() > MaxUnbalancing()) return Standard_True;
	if (leaf->ENeighbors().size() > MaxUnbalancing()) return Standard_True;
	if (leaf->NNeighbors().size() > MaxUnbalancing()) return Standard_True;
	if (leaf->WNeighbors().size() > MaxUnbalancing()) return Standard_True;
	return Standard_False;
}

template<class T>
inline void tnbLib::Geo2d_BalPrTree<T>::SwitchToClear(internalNode *& t)
{
	if (t->Sw()) Clear(t->SwRef());
	if (t->Se()) Clear(t->SeRef());
	if (t->Ne()) Clear(t->NeRef());
	if (t->Nw()) Clear(t->NwRef());
}

template<class T>
inline void tnbLib::Geo2d_BalPrTree<T>::Clear(node *& t)
{
	leafNode* leaf =
		dynamic_cast<leafNode*>(t);

	if (leaf)
	{
		delete t;
		t = nullptr;
	}
	else
	{
		internalNode* Internal =
			dynamic_cast<internalNode*>(t);

		SwitchToClear(Internal);
		delete t;
		t = nullptr;
	}
}

template<class T>
inline void tnbLib::Geo2d_BalPrTree<T>::SwitchToInsert
(
	const T & theItem,
	const Pnt2d & theCentre,
	const std::shared_ptr<boxType>& theBox,
	internalNode *& t
)
{
	switch (CalcQuadrant(geom::CoordinateOf(theItem), theCentre))
	{
	case Geo2d_BalPrTreeQuad::SW:
		Insert(theItem, std::make_shared<Entity2d_Box>(theBox->SubDivide(Box2d_SubDivideAlgorithm_Quad_SW)), t->SwRef());
		break;
	case Geo2d_BalPrTreeQuad::SE:
		Insert(theItem, std::make_shared<Entity2d_Box>(theBox->SubDivide(Box2d_SubDivideAlgorithm_Quad_SE)), t->SeRef());
		break;
	case Geo2d_BalPrTreeQuad::NE:
		Insert(theItem, std::make_shared<Entity2d_Box>(theBox->SubDivide(Box2d_SubDivideAlgorithm_Quad_NE)), t->NeRef());
		break;
	case Geo2d_BalPrTreeQuad::NW:
		Insert(theItem, std::make_shared<Entity2d_Box>(theBox->SubDivide(Box2d_SubDivideAlgorithm_Quad_NW)), t->NwRef());
		break;
	default:
		FatalErrorIn(FunctionSIG)
			<< "unspecified type of octant has been detected!" << endl
			<< abort(FatalError);
		break;
	}
}

template<class T>
inline void tnbLib::Geo2d_BalPrTree<T>::Insert
(
	const T & theItem,
	const std::shared_ptr<boxType>& theBox,
	node *& t
)
{
	if (!t)
	{
		/*leafNode* leaf = new leafNode;
		leaf->SetBox(std::move(theBox));
		leaf->Insert(theItem);

		t = leaf;*/

		//Base::Increment();
		//return;
		auto interNode = new internalNode;
		interNode->SetBox(theBox);

		auto SwPtr = CreateNewLeaf(std::make_shared<Entity2d_Box>(theBox->SubDivide(Box2d_SubDivideAlgorithm_Quad_SW)));
		auto SePtr = CreateNewLeaf(std::make_shared<Entity2d_Box>(theBox->SubDivide(Box2d_SubDivideAlgorithm_Quad_SE)));
		auto NePtr = CreateNewLeaf(std::make_shared<Entity2d_Box>(theBox->SubDivide(Box2d_SubDivideAlgorithm_Quad_NE)));
		auto NwPtr = CreateNewLeaf(std::make_shared<Entity2d_Box>(theBox->SubDivide(Box2d_SubDivideAlgorithm_Quad_NW)));

		interNode->SwRef() = SwPtr;
		interNode->SeRef() = SePtr;
		interNode->NeRef() = NePtr;
		interNode->NwRef() = NwPtr;

		LinkInners(interNode);

		const auto coord = theBox->CalcCentre();
		SwitchToInsert(theItem, coord, theBox, interNode);

		t = interNode;

		Base::Increment();
		return;
	}

	leafNode* leaf = dynamic_cast<leafNode*>(t);
	if (leaf)
	{
		if (NOT IsFull(leaf))
		{
			leaf->Insert(theItem);

			Base::Increment();
			return;
		}
		else
		{
			NbSubdivideRef()++;

			if (NbSubdivide() >= MAX_INNER_SUBDIVIDE)
			{
				FatalErrorIn(FunctionSIG)
					<< "unable to insert the item into the tree!" << endl
					<< " - the max nb. of inner subdivision has been encountered!" << endl
					<< " - Max. nb. of subdivide: " << MAX_INNER_SUBDIVIDE << endl
					<< abort(FatalError);
			}

			const auto& pItems = leaf->Bucket();
			const auto& b = *leaf->Box();

			auto interNode = new internalNode;
			interNode->SetBox(leaf->Box());

			// Subdivide the Leaf
			auto SwPtr = CreateNewLeaf(std::make_shared<Entity2d_Box>(b.SubDivide(Box2d_SubDivideAlgorithm_Quad_SW)));
			auto SePtr = CreateNewLeaf(std::make_shared<Entity2d_Box>(b.SubDivide(Box2d_SubDivideAlgorithm_Quad_SE)));
			auto NePtr = CreateNewLeaf(std::make_shared<Entity2d_Box>(b.SubDivide(Box2d_SubDivideAlgorithm_Quad_NE)));
			auto NwPtr = CreateNewLeaf(std::make_shared<Entity2d_Box>(b.SubDivide(Box2d_SubDivideAlgorithm_Quad_NW)));

			Debug_Null_Pointer(SwPtr);
			Debug_Null_Pointer(SePtr);
			Debug_Null_Pointer(NePtr);
			Debug_Null_Pointer(NwPtr);

			SwPtr->FatherRef() = interNode;
			SePtr->FatherRef() = interNode;
			NePtr->FatherRef() = interNode;
			NwPtr->FatherRef() = interNode;

			interNode->SwRef() = SwPtr;
			interNode->SeRef() = SePtr;
			interNode->NeRef() = NePtr;
			interNode->NwRef() = NwPtr;

			LinkInners(interNode);

			// Remove Old Leaf from Neighbors
			RemoveLeafFromNeighbors(leaf);

			FillNeighbors(Geo2d_BalPrTreeQuad::SW, leaf, interNode, SwPtr);
			FillNeighbors(Geo2d_BalPrTreeQuad::SE, leaf, interNode, SePtr);
			FillNeighbors(Geo2d_BalPrTreeQuad::NE, leaf, interNode, NePtr);
			FillNeighbors(Geo2d_BalPrTreeQuad::NW, leaf, interNode, NwPtr);

			//UpdateFather(leaf, interNode);

			const auto coord = b.CalcCentre();
			for (const auto& x : pItems)
			{
				SwitchToInsert(x, coord, leaf->Box(), interNode);
			}

			SwitchToInsert(theItem, coord, leaf->Box(), interNode);

			if (leaf)
			{
				delete leaf;
				t = nullptr;
			}

			t = interNode;
		}
	}
	else
	{
		internalNode* Internal =
			dynamic_cast<internalNode*>(t);

		SwitchToInsert
		(
			theItem,
			Internal->Box()->CalcCentre(),
			Internal->Box(),
			Internal
		);
	}
}

template<class T>
inline void tnbLib::Geo2d_BalPrTree<T>::NullifyPointer
(
	node *& t,
	internalNode *& Internal
)
{
	if
		(
			!Internal->Sw() &&
			!Internal->Se() &&
			!Internal->Ne() &&
			!Internal->Nw()
			)
	{
		delete t;
		t = nullptr;
	}
}

template<class T>
inline void tnbLib::Geo2d_BalPrTree<T>::SwitchToRemove
(
	const T & theItem,
	internalNode *& t
)
{
	switch (CalcQuadrant(geom::CoordinateOf(theItem), t->Box()->CalcCentre()))
	{
	case Geo2d_BalPrTreeQuad::SW:
		Remove(theItem, t->SwRef());
		break;
	case Geo2d_BalPrTreeQuad::SE:
		Remove(theItem, t->SeRef());
		break;
	case Geo2d_BalPrTreeQuad::NE:
		Remove(theItem, t->NeRef());
		break;
	case Geo2d_BalPrTreeQuad::NW:
		Remove(theItem, t->NwRef());
		break;
	default:
		FatalErrorIn(FunctionSIG)
			<< "Unspecified type of octant has been detected!" << endl
			<< abort(FatalError);
		break;
	}
}

template<class T>
inline void tnbLib::Geo2d_BalPrTree<T>::Remove(const T & theItem, node *& t)
{
	if (!t)
	{
		FatalErrorIn(FunctionSIG)
			<< "Item is not in tree"
			<< abort(FatalError);
	}

	leafNode* leaf =
		dynamic_cast<leafNode*>(t);

	if (leaf)
	{
		Standard_Integer bSize = leaf->Size();
		leaf->Remove(theItem);

		if (leaf->Size() >= bSize)
		{
			FatalErrorIn(FunctionSIG)
				<< "Item is not in tree"
				<< abort(FatalError);
		}

		Base::Decrement();

		if (leaf->IsEmpty())
		{
			delete t;
			t = nullptr;
		}
	}
	else
	{
		internalNode* Internal =
			dynamic_cast<internalNode*>(t);

		SwitchToRemove(theItem, Internal);

		NullifyPointer(t, Internal);
	}
}

template<class T>
inline void tnbLib::Geo2d_BalPrTree<T>::LinkInners(internalNode * t) const
{
	auto swPtr = dynamic_cast<leafNode*>(t->Sw());
	auto sePtr = dynamic_cast<leafNode*>(t->Se());
	auto nePtr = dynamic_cast<leafNode*>(t->Ne());
	auto nwPtr = dynamic_cast<leafNode*>(t->Nw());

	Debug_Null_Pointer(swPtr);
	Debug_Null_Pointer(sePtr);
	Debug_Null_Pointer(nePtr);
	Debug_Null_Pointer(nwPtr);

	swPtr->ENeighborsRef().push_back(sePtr);
	swPtr->NNeighborsRef().push_back(nwPtr);

	sePtr->WNeighborsRef().push_back(swPtr);
	sePtr->NNeighborsRef().push_back(nePtr);

	nePtr->WNeighborsRef().push_back(nwPtr);
	nePtr->SNeighborsRef().push_back(sePtr);

	nwPtr->ENeighborsRef().push_back(nePtr);
	nwPtr->SNeighborsRef().push_back(swPtr);
}

template<class T>
inline void tnbLib::Geo2d_BalPrTree<T>::RemoveLeafFromNeighbors(leafNode * old) const
{
	for (const auto& x : old->SNeighbors())
	{
		x->NNeighborsRef().remove(old);
	}
	for (const auto& x : old->ENeighbors())
	{
		x->WNeighborsRef().remove(old);
	}
	for (const auto& x : old->NNeighbors())
	{
		x->SNeighborsRef().remove(old);
	}
	for (const auto& x : old->WNeighbors())
	{
		x->ENeighborsRef().remove(old);
	}
}

template<class T>
inline void tnbLib::Geo2d_BalPrTree<T>::FillNeighbors
(
	const Geo2d_BalPrTreeQuad o,
	leafNode * old,
	internalNode * father,
	leafNode * t
) const
{
	const auto& SN = old->SNeighbors();
	const auto& EN = old->ENeighbors();
	const auto& NN = old->NNeighbors();
	const auto& WN = old->WNeighbors();

	auto swPtr = dynamic_cast<leafNode*>(father->Sw());
	auto sePtr = dynamic_cast<leafNode*>(father->Se());
	auto nePtr = dynamic_cast<leafNode*>(father->Ne());
	auto nwPtr = dynamic_cast<leafNode*>(father->Nw());

	Debug_Null_Pointer(swPtr);
	Debug_Null_Pointer(sePtr);
	Debug_Null_Pointer(nePtr);
	Debug_Null_Pointer(nwPtr);

	const auto& tBox = *old->Box();
	auto c = tBox.CalcCentre();

	std::vector<leafNode*> QSN, QEN, QNN, QWN;
	switch (o)
	{
	case Geo2d_BalPrTreeQuad::SW:
	{
		if (WN.size() <= 1) for (const auto& x : WN) QWN.push_back(x);
		else
			for (const auto& x : WN)
			{
				if (IsSW(x->Box()->CalcCentre(), c))
				{
					QWN.push_back(x);
				}
			}

		if (SN.size() <= 1) for (const auto& x : SN) QSN.push_back(x);
		else
			for (const auto& x : SN)
			{
				if (IsSW(x->Box()->CalcCentre(), c))
				{
					QSN.push_back(x);
				}
			}
		break;
	}
	case Geo2d_BalPrTreeQuad::SE:
	{
		if (SN.size() <= 1) for (const auto& x : SN) QSN.push_back(x);
		else
			for (const auto& x : SN)
			{
				if (IsSE(x->Box()->CalcCentre(), c))
				{
					QSN.push_back(x);
				}
			}

		if (EN.size() <= 1) for (const auto& x : EN) QEN.push_back(x);
		else
			for (const auto& x : EN)
			{
				if (IsSE(x->Box()->CalcCentre(), c))
				{
					QEN.push_back(x);
				}
			}
		break;
	}
	case Geo2d_BalPrTreeQuad::NE:
	{
		if (EN.size() <= 1) for (const auto& x : EN) QEN.push_back(x);
		else
			for (const auto& x : EN)
			{
				if (IsNE(x->Box()->CalcCentre(), c))
				{
					QEN.push_back(x);
				}
			}

		if (NN.size() <= 1) for (const auto& x : NN) QNN.push_back(x);
		else
			for (const auto& x : NN)
			{
				if (IsNE(x->Box()->CalcCentre(), c))
				{
					QNN.push_back(x);
				}
			}
		break;
	}
	case Geo2d_BalPrTreeQuad::NW:
	{
		if (NN.size() <= 1) for (const auto& x : NN) QNN.push_back(x);
		else
			for (const auto& x : NN)
			{
				if (IsNW(x->Box()->CalcCentre(), c))
				{
					QNN.push_back(x);
				}
			}

		if (WN.size() <= 1) for (const auto& x : WN) QWN.push_back(x);
		else
			for (const auto& x : WN)
			{
				if (IsNW(x->Box()->CalcCentre(), c))
				{
					QWN.push_back(x);
				}
			}
		break;
	}
	default:
		FatalErrorIn(FunctionSIG)
			<< "unspecified type of octant has been detected." << endl
			<< abort(FatalError);
		break;
	}
	for (const auto& x : QSN)
	{
		x->NNeighborsRef().push_back(t);
		t->SNeighborsRef().push_back(x);
	}
	for (const auto& x : QEN)
	{
		x->WNeighborsRef().push_back(t);
		t->ENeighborsRef().push_back(x);
	}
	for (const auto& x : QNN)
	{
		x->SNeighborsRef().push_back(t);
		t->NNeighborsRef().push_back(x);
	}
	for (const auto& x : QWN)
	{
		x->ENeighborsRef().push_back(t);
		t->WNeighborsRef().push_back(x);
	}
}

template<class T>
inline void tnbLib::Geo2d_BalPrTree<T>::Balance(node *& t)
{
	if (NOT t) return;
	auto leaf = dynamic_cast<leafNode*>(t);
	if (leaf)
	{
		if (NOT IsUnbalanced(leaf)) return;
		if (IsBalancedRef()) IsBalancedRef() = Standard_False;

		Debug_Null_Pointer(leaf->Box());
		const auto& b = *leaf->Box();

		auto interNode = new internalNode;
		interNode->SetBox(leaf->Box());

		// Subdivide the Leaf
		auto SwPtr = CreateNewLeaf(std::make_shared<Entity2d_Box>(b.SubDivide(Box2d_SubDivideAlgorithm_Quad_SW)));
		auto SePtr = CreateNewLeaf(std::make_shared<Entity2d_Box>(b.SubDivide(Box2d_SubDivideAlgorithm_Quad_SE)));
		auto NePtr = CreateNewLeaf(std::make_shared<Entity2d_Box>(b.SubDivide(Box2d_SubDivideAlgorithm_Quad_NE)));
		auto NwPtr = CreateNewLeaf(std::make_shared<Entity2d_Box>(b.SubDivide(Box2d_SubDivideAlgorithm_Quad_NW)));

		Debug_Null_Pointer(SwPtr);
		Debug_Null_Pointer(SePtr);
		Debug_Null_Pointer(NePtr);
		Debug_Null_Pointer(NwPtr);

		SwPtr->FatherRef() = interNode;
		SePtr->FatherRef() = interNode;
		NePtr->FatherRef() = interNode;
		NwPtr->FatherRef() = interNode;

		interNode->SwRef() = SwPtr;
		interNode->SeRef() = SePtr;
		interNode->NeRef() = NePtr;
		interNode->NwRef() = NwPtr;

		LinkInners(interNode);

		// Remove Old Leaf from Neighbors
		RemoveLeafFromNeighbors(leaf);

		FillNeighbors(Geo2d_BalPrTreeQuad::SW, leaf, interNode, SwPtr);
		FillNeighbors(Geo2d_BalPrTreeQuad::SE, leaf, interNode, SePtr);
		FillNeighbors(Geo2d_BalPrTreeQuad::NE, leaf, interNode, NePtr);
		FillNeighbors(Geo2d_BalPrTreeQuad::NW, leaf, interNode, NwPtr);

		//UpdateFather(leaf, (node*)interNode);

		if (t)
		{
			delete leaf;
			t = nullptr;
		}

		t = interNode;

		//std::exit(1);
		Balance(interNode->SwRef());
		Balance(interNode->SeRef());
		Balance(interNode->NeRef());
		Balance(interNode->NwRef());
	}
	else
	{
		auto inner = dynamic_cast<internalNode*>(t);
		Debug_Null_Pointer(inner);

		Balance(inner->SwRef());
		Balance(inner->SeRef());
		Balance(inner->NeRef());
		Balance(inner->NwRef());
	}
}

template<class T>
template<class ObjectType>
inline void tnbLib::Geo2d_BalPrTree<T>::Subdivide
(
	node *& t,
	Standard_Boolean(* theSubdivider)(const Entity2d_Box &, const ObjectType *),
	const ObjectType * theObject, 
	const Standard_Integer theLev,
	const Standard_Integer theMaxLev
)
{
	if (theLev > theMaxLev)
	{
		return;
	}

	if (NOT t) return;
	auto leaf = dynamic_cast<leafNode*>(t);

	if (theSubdivider(*leaf->Box(), theObject))
	{
		const auto& b = *leaf->Box();

		auto interNode = new internalNode;
		interNode->SetBox(leaf->Box());

		// Subdivide the Leaf
		auto SwPtr = CreateNewLeaf(std::make_shared<Entity2d_Box>(b.SubDivide(Box2d_SubDivideAlgorithm_Quad_SW)));
		auto SePtr = CreateNewLeaf(std::make_shared<Entity2d_Box>(b.SubDivide(Box2d_SubDivideAlgorithm_Quad_SE)));
		auto NePtr = CreateNewLeaf(std::make_shared<Entity2d_Box>(b.SubDivide(Box2d_SubDivideAlgorithm_Quad_NE)));
		auto NwPtr = CreateNewLeaf(std::make_shared<Entity2d_Box>(b.SubDivide(Box2d_SubDivideAlgorithm_Quad_NW)));

		Debug_Null_Pointer(SwPtr);
		Debug_Null_Pointer(SePtr);
		Debug_Null_Pointer(NePtr);
		Debug_Null_Pointer(NwPtr);

		SwPtr->FatherRef() = interNode;
		SePtr->FatherRef() = interNode;
		NePtr->FatherRef() = interNode;
		NwPtr->FatherRef() = interNode;

		interNode->SwRef() = SwPtr;
		interNode->SeRef() = SePtr;
		interNode->NeRef() = NePtr;
		interNode->NwRef() = NwPtr;

		LinkInners(interNode);

		// Remove Old Leaf from Neighbors
		RemoveLeafFromNeighbors(leaf);

		FillNeighbors(Geo2d_BalPrTreeQuad::SW, leaf, interNode, SwPtr);
		FillNeighbors(Geo2d_BalPrTreeQuad::SE, leaf, interNode, SePtr);
		FillNeighbors(Geo2d_BalPrTreeQuad::NE, leaf, interNode, NePtr);
		FillNeighbors(Geo2d_BalPrTreeQuad::NW, leaf, interNode, NwPtr);

		UpdateFather(leaf, (node*)interNode);

		if (t)
		{
			delete leaf;
			t = nullptr;
		}

		t = interNode;

		Subdivide(interNode->SwRef(), theSubdivider, theObject, theLev + 1, theMaxLev);
		Subdivide(interNode->SeRef(), theSubdivider, theObject, theLev + 1, theMaxLev);
		Subdivide(interNode->NeRef(), theSubdivider, theObject, theLev + 1, theMaxLev);
		Subdivide(interNode->NwRef(), theSubdivider, theObject, theLev + 1, theMaxLev);
	}
}

template<class T>
inline void tnbLib::Geo2d_BalPrTree<T>::SwitchToSearch
(
	const Entity2d_Box & theRegion,
	internalNode * t,
	std::list<T>& theItems
) const
{
	if (t->Sw())
	{
		if (theRegion.IsIntersect(*t->Sw()->Box()))
			Search(theRegion, t->Sw(), theItems);
	}

	if (t->Se())
	{
		if (theRegion.IsIntersect(*t->Se()->Box()))
			Search(theRegion, t->Se(), theItems);
	}

	if (t->Ne())
	{
		if (theRegion.IsIntersect(*t->Ne()->Box()))
			Search(theRegion, t->Ne(), theItems);
	}

	if (t->Nw())
	{
		if (theRegion.IsIntersect(*t->Nw()->Box()))
			Search(theRegion, t->Nw(), theItems);
	}
}

template<class T>
inline void tnbLib::Geo2d_BalPrTree<T>::SwitchToSearch
(
	const Entity2d_Box & theRegion,
	internalNode * t,
	std::vector<T>& theItems
) const
{
	if (t->Sw())
	{
		if (theRegion.IsIntersect(*t->Sw()->Box()))
			Search(theRegion, t->Sw(), theItems);
	}

	if (t->Se())
	{
		if (theRegion.IsIntersect(*t->Se()->Box()))
			Search(theRegion, t->Se(), theItems);
	}

	if (t->Ne())
	{
		if (theRegion.IsIntersect(*t->Ne()->Box()))
			Search(theRegion, t->Ne(), theItems);
	}

	if (t->Nw())
	{
		if (theRegion.IsIntersect(*t->Nw()->Box()))
			Search(theRegion, t->Nw(), theItems);
	}
}

template<class T>
inline void tnbLib::Geo2d_BalPrTree<T>::Search
(
	const Entity2d_Box & theBox,
	node * t,
	std::list<T>& theItems
) const
{
	leafNode* leaf = dynamic_cast<leafNode*>(t);
	if (leaf)
	{
		for (const auto& item : leaf->Bucket())
		{
			if (theBox.IsInside(geom::CoordinateOf(item)))
			{
				theItems.push_back(item);
			}
		}
	}
	else
	{
		internalNode* Internal =
			dynamic_cast<internalNode*>(t);

		SwitchToSearch(theBox, Internal, theItems);
	}
}

template<class T>
inline void tnbLib::Geo2d_BalPrTree<T>::Search
(
	const Entity2d_Box & theBox,
	node * t,
	std::vector<T>& theItems
) const
{
	leafNode* leaf = dynamic_cast<leafNode*>(t);
	if (leaf)
	{
		for (const auto& item : leaf->Bucket())
		{
			if (theBox.IsInside(geom::CoordinateOf(item)))
			{
				theItems.push_back(item);
			}
		}
	}
	else
	{
		internalNode* Internal =
			dynamic_cast<internalNode*>(t);

		SwitchToSearch(theBox, Internal, theItems);
	}
}

template<class T>
inline void tnbLib::Geo2d_BalPrTree<T>::SwitchToRetrieveLeavesTo
(
	internalNode * Internal,
	std::vector<leafNode*>& theItems
)
{
	if (Internal->Sw()) RetrieveLeavesTo(Internal->Sw(), theItems);
	if (Internal->Se()) RetrieveLeavesTo(Internal->Se(), theItems);
	if (Internal->Ne()) RetrieveLeavesTo(Internal->Ne(), theItems);
	if (Internal->Nw()) RetrieveLeavesTo(Internal->Nw(), theItems);
}

template<class T>
inline void tnbLib::Geo2d_BalPrTree<T>::RetrieveLeavesTo
(
	node * t,
	std::vector<leafNode*>& theLeaves
)
{
	leafNode* leaf =
		dynamic_cast<leafNode*>(t);
	if (leaf)
	{
		theLeaves.push_back(leaf);
	}
	else
	{
		internalNode* Internal =
			dynamic_cast<internalNode*>(t);

		SwitchToRetrieveLeavesTo(Internal, theLeaves);
	}
}

template<class T>
inline void tnbLib::Geo2d_BalPrTree<T>::SwitchToRetrieveTo
(
	internalNode * Internal,
	std::list<T>& theItems
)
{
	if (Internal->Sw()) RetrieveTo(Internal->Sw(), theItems);
	if (Internal->Se()) RetrieveTo(Internal->Se(), theItems);
	if (Internal->Ne()) RetrieveTo(Internal->Ne(), theItems);
	if (Internal->Nw()) RetrieveTo(Internal->Nw(), theItems);
}

template<class T>
inline void tnbLib::Geo2d_BalPrTree<T>::SwitchToRetrieveTo
(
	internalNode * Internal,
	std::vector<T>& theItems
)
{
	if (Internal->Sw()) RetrieveTo(Internal->Sw(), theItems);
	if (Internal->Se()) RetrieveTo(Internal->Se(), theItems);
	if (Internal->Ne()) RetrieveTo(Internal->Ne(), theItems);
	if (Internal->Nw()) RetrieveTo(Internal->Nw(), theItems);
}

template<class T>
inline void tnbLib::Geo2d_BalPrTree<T>::RetrieveTo
(
	node * t,
	std::list<T>& theItems
)
{
	leafNode* leaf = dynamic_cast<leafNode*>(t);
	if (leaf)
	{
		for (const auto& item : leaf->Bucket())
			theItems.push_back(item);
	}
	else
	{
		internalNode* Internal =
			dynamic_cast<internalNode*>(t);

		SwitchToRetrieveTo(Internal, theItems);
	}
}

template<class T>
inline void tnbLib::Geo2d_BalPrTree<T>::RetrieveTo
(
	node * t,
	std::vector<T>& theItems
)
{
	leafNode* leaf = dynamic_cast<leafNode*>(t);
	if (leaf)
	{
		for (const auto& item : leaf->Bucket())
			theItems.push_back(item);
	}
	else
	{
		internalNode* Internal =
			dynamic_cast<internalNode*>(t);

		SwitchToRetrieveTo(Internal, theItems);
	}
}

template<class T>
inline typename tnbLib::Geo2d_BalPrTree<T>::leafNode* 
tnbLib::Geo2d_BalPrTree<T>::CreateNewLeaf(const std::shared_ptr<Entity2d_Box>& b)
{
	return new leafNode(b);
}

template<class T>
inline void tnbLib::Geo2d_BalPrTree<T>::UpdateFather
(
	leafNode * t,
	node * inter
)
{
	if (NOT t->Father()) return;
	auto father = dynamic_cast<internalNode*>(t->Father());
	Debug_Null_Pointer(father);

	if (father->Sw() IS_EQUAL t) father->SwRef() = inter;
	else if (father->Se() IS_EQUAL t) father->SeRef() = inter;
	else if (father->Ne() IS_EQUAL t) father->NeRef() = inter;
	else if (father->Nw() IS_EQUAL t) father->NwRef() = inter;
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "Unexpected error has been detected!" << endl
			<< abort(FatalError);
	}
}

template<class T>
inline Standard_Boolean tnbLib::Geo2d_BalPrTree<T>::IsBalanced() const
{
	std::vector<leafNode*> leaves;
	RetrieveLeavesTo(leaves);
	for (const auto& x : leaves)
	{
		if (IsUnbalanced(x))
		{
			return Standard_False;
		}
	}
	return Standard_True;
}

template<class T>
inline void tnbLib::Geo2d_BalPrTree<T>::InsertToGeometry(const T & theItem)
{
	Debug_If_Condition_Message
	(
		!geom::CoordinateOf, " No coordinate function for Pr-Tree"
	);
	this->NbSubdivideRef() = 0;
	auto b = std::make_shared<Entity2d_Box>(geom::GeometryBoundingBox());
	Insert(theItem, b, theRoot_);
}

template<class T>
inline void tnbLib::Geo2d_BalPrTree<T>::InsertToGeometry
(
	const std::vector<T>& theItems
)
{
	Debug_If_Condition_Message
	(
		!geom::CoordinateOf, " No coordinate function for Pr-Tree"
	);
	auto b = std::make_shared<Entity2d_Box>(geom::GeometryBoundingBox());
	for (const auto& x : theItems)
	{
		Insert(x, b, theRoot_);
	}
}

template<class T>
inline void tnbLib::Geo2d_BalPrTree<T>::RemoveFromGeometry(const T & theItem)
{
	if (Size())
	{
		Remove(theItem, theRoot_);
	}
}

template<class T>
inline void tnbLib::Geo2d_BalPrTree<T>::GeometrySearch
(
	const Standard_Real theRadius,
	const Pnt2d & theCentre,
	std::list<T>& theItems
) const
{
	if (Size())
	{
		Search
		(
			Entity_Box<Point>::Box(theCentre, theRadius),
			theRoot_,
			theItems
		);
	}
}

template<class T>
inline void tnbLib::Geo2d_BalPrTree<T>::GeometrySearch
(
	const Standard_Real theRadius,
	const Pnt2d & theCentre,
	std::vector<T>& theItems
) const
{
	if (Size())
	{
		Search
		(
			Entity_Box<Point>::Box(theCentre, theRadius),
			theRoot_,
			theItems
		);
	}
}

template<class T>
inline void tnbLib::Geo2d_BalPrTree<T>::GeometrySearch
(
	const Entity2d_Box & theRegion,
	std::list<T>& theList
) const
{
	if (Size())
	{
		Search(theRegion, theRoot_, theList);
	}
}

template<class T>
inline void tnbLib::Geo2d_BalPrTree<T>::GeometrySearch
(
	const Entity2d_Box & theRegion,
	std::vector<T>& theItems
) const
{
	if (Size())
	{
		Search(theRegion, theRoot_, theItems);
	}
}

template<class T>
inline void tnbLib::Geo2d_BalPrTree<T>::PostBalance()
{
	size_t k = 0;

	while (true)
	{
		k++;
		IsBalancedRef() = Standard_True;
		Balance(theRoot_);
		if (IsBalancedRef()) break;
	}
}

template<class T>
template<class ObjectType>
inline void tnbLib::Geo2d_BalPrTree<T>::PostSubdivide
(
	const leafNode* theNode,
	Standard_Boolean(* theSubdivider)(const Entity2d_Box &, const ObjectType *),
	const ObjectType* theObject,
	const Standard_Integer theMaxLev
)
{
	auto leaf = (node*)theNode;
	Subdivide(leaf, theSubdivider, theObject, 0, theMaxLev);
}

template<class T>
template<class ObjectType>
inline void tnbLib::Geo2d_BalPrTree<T>::PostSubdivide
(
	node *& t, 
	Standard_Boolean(*theSubdivider)(const Entity2d_Box &, const ObjectType *),
	const ObjectType * theObject,
	const Standard_Integer theMaxLev
)
{
	Subdivide(t, theSubdivider, theObject, 0, theMaxLev);
}

template<class T>
inline void tnbLib::Geo2d_BalPrTree<T>::Clear()
{
	Clear(theRoot_);
}

template<class T>
inline void tnbLib::Geo2d_BalPrTree<T>::RetrieveLeavesTo
(
	std::vector<leafNode*>& theLeaves
) const
{
	if (Size())
	{
		RetrieveLeavesTo(theRoot_, theLeaves);
	}
}

template<class T>
inline void tnbLib::Geo2d_BalPrTree<T>::RetrieveFromGeometryTo(std::list<T>& theItems) const
{
	if (Size())
	{
		RetrieveTo(theRoot_, theItems);
	}
}

template<class T>
inline void tnbLib::Geo2d_BalPrTree<T>::RetrieveFromGeometryTo(std::vector<T>& theItems) const
{
	if (Size())
	{
		RetrieveTo(theRoot_, theItems);
	}
}