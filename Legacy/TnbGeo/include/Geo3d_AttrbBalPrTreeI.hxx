#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
template<class T, class Attrb>
inline Standard_Boolean 
tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::IsUnbalanced
(
	const leafNode * leaf
) const
{
	if (leaf->SNeighbors().size() > MaxUnbalancing()) return Standard_True;
	if (leaf->ENeighbors().size() > MaxUnbalancing()) return Standard_True;
	if (leaf->NNeighbors().size() > MaxUnbalancing()) return Standard_True;
	if (leaf->WNeighbors().size() > MaxUnbalancing()) return Standard_True;
	if (leaf->FNeighbors().size() > MaxUnbalancing()) return Standard_True;
	if (leaf->BNeighbors().size() > MaxUnbalancing()) return Standard_True;
	return Standard_False;
}

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::SwitchToClear(internalNode *& t)
{
	if (t->BwdSw()) Clear(t->BwdSwRef());
	if (t->BwdSe()) Clear(t->BwdSeRef());
	if (t->BwdNe()) Clear(t->BwdNeRef());
	if (t->BwdNw()) Clear(t->BwdNwRef());

	if (t->FwdSw()) Clear(t->FwdSwRef());
	if (t->FwdSe()) Clear(t->FwdSeRef());
	if (t->FwdNe()) Clear(t->FwdNeRef());
	if (t->FwdNw()) Clear(t->FwdNwRef());
}

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::Clear(node *& t)
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

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::SwitchToInsert
(
	const T & theItem, 
	const Pnt3d & theCentre, 
	const std::shared_ptr<boxType>& theBox,
	internalNode *& t
)
{
	switch (CalcOctant(geom::CoordinateOf(theItem), theCentre))
	{
	case Geo3d_BalPrTreeOctant::Bwd_SW:
		Insert(theItem, std::make_shared<Entity3d_Box>(theBox->SubDivide(Box3d_SubDivideAlgorithm_Aft_SW)), t->BwdSwRef());
		break;
	case Geo3d_BalPrTreeOctant::Bwd_SE:
		Insert(theItem, std::make_shared<Entity3d_Box>(theBox->SubDivide(Box3d_SubDivideAlgorithm_Aft_SE)), t->BwdSeRef());
		break;
	case Geo3d_BalPrTreeOctant::Bwd_NE:
		Insert(theItem, std::make_shared<Entity3d_Box>(theBox->SubDivide(Box3d_SubDivideAlgorithm_Aft_NE)), t->BwdNeRef());
		break;
	case Geo3d_BalPrTreeOctant::Bwd_NW:
		Insert(theItem, std::make_shared<Entity3d_Box>(theBox->SubDivide(Box3d_SubDivideAlgorithm_Aft_NW)), t->BwdNwRef());
		break;
	case Geo3d_BalPrTreeOctant::Fwd_SW:
		Insert(theItem, std::make_shared<Entity3d_Box>(theBox->SubDivide(Box3d_SubDivideAlgorithm_Fwd_SW)), t->FwdSwRef());
		break;
	case Geo3d_BalPrTreeOctant::Fwd_SE:
		Insert(theItem, std::make_shared<Entity3d_Box>(theBox->SubDivide(Box3d_SubDivideAlgorithm_Fwd_SE)), t->FwdSeRef());
		break;
	case Geo3d_BalPrTreeOctant::Fwd_NE:
		Insert(theItem, std::make_shared<Entity3d_Box>(theBox->SubDivide(Box3d_SubDivideAlgorithm_Fwd_NE)), t->FwdNeRef());
		break;
	case Geo3d_BalPrTreeOctant::Fwd_NW:
		Insert(theItem, std::make_shared<Entity3d_Box>(theBox->SubDivide(Box3d_SubDivideAlgorithm_Fwd_NW)), t->FwdNwRef());
		break;
	default:
		FatalErrorIn(FunctionSIG)
			<< "unspecified type of octant has been detected!" << endl
			<< abort(FatalError);
		break;
	}
}

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::Insert
(
	const T & theItem, 
	const std::shared_ptr<boxType>& theBox,
	node *& t
)
{
	if (!t)
	{
		leafNode* leaf = new leafNode;
		leaf->SetBox(std::move(theBox));
		leaf->Insert(theItem);

		t = leaf;

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
			auto Fwd_SwPtr = new leafNode(std::make_shared<Entity3d_Box>(b.SubDivide(Box3d_SubDivideAlgorithm_Fwd_SW)));
			auto Fwd_SePtr = new leafNode(std::make_shared<Entity3d_Box>(b.SubDivide(Box3d_SubDivideAlgorithm_Fwd_SE)));
			auto Fwd_NePtr = new leafNode(std::make_shared<Entity3d_Box>(b.SubDivide(Box3d_SubDivideAlgorithm_Fwd_NE)));
			auto Fwd_NwPtr = new leafNode(std::make_shared<Entity3d_Box>(b.SubDivide(Box3d_SubDivideAlgorithm_Fwd_NW)));

			auto Bwd_SwPtr = new leafNode(std::make_shared<Entity3d_Box>(b.SubDivide(Box3d_SubDivideAlgorithm_Aft_SW)));
			auto Bwd_SePtr = new leafNode(std::make_shared<Entity3d_Box>(b.SubDivide(Box3d_SubDivideAlgorithm_Aft_SE)));
			auto Bwd_NePtr = new leafNode(std::make_shared<Entity3d_Box>(b.SubDivide(Box3d_SubDivideAlgorithm_Aft_NE)));
			auto Bwd_NwPtr = new leafNode(std::make_shared<Entity3d_Box>(b.SubDivide(Box3d_SubDivideAlgorithm_Aft_NW)));

			Debug_Null_Pointer(Fwd_SwPtr);
			Debug_Null_Pointer(Fwd_SePtr);
			Debug_Null_Pointer(Fwd_NePtr);
			Debug_Null_Pointer(Fwd_NwPtr);

			Debug_Null_Pointer(Bwd_SwPtr);
			Debug_Null_Pointer(Bwd_SePtr);
			Debug_Null_Pointer(Bwd_NePtr);
			Debug_Null_Pointer(Bwd_NwPtr);

			Fwd_SwPtr->FatherRef() = interNode;
			Fwd_SePtr->FatherRef() = interNode;
			Fwd_NePtr->FatherRef() = interNode;
			Fwd_NwPtr->FatherRef() = interNode;

			Bwd_SwPtr->FatherRef() = interNode;
			Bwd_SePtr->FatherRef() = interNode;
			Bwd_NePtr->FatherRef() = interNode;
			Bwd_NwPtr->FatherRef() = interNode;

			interNode->FwdSwRef() = Fwd_SwPtr;
			interNode->FwdSeRef() = Fwd_SePtr;
			interNode->FwdNeRef() = Fwd_NePtr;
			interNode->FwdNwRef() = Fwd_NwPtr;

			interNode->BwdSwRef() = Bwd_SwPtr;
			interNode->BwdSeRef() = Bwd_SePtr;
			interNode->BwdNeRef() = Bwd_NePtr;
			interNode->BwdNwRef() = Bwd_NwPtr;

			LinkInners(interNode);

			// Remove Old Leaf from Neighbors
			RemoveLeafFromNeighbors(leaf);

			FillNeighbors(Geo3d_BalPrTreeOctant::Fwd_SW, leaf, interNode, Fwd_SwPtr);
			FillNeighbors(Geo3d_BalPrTreeOctant::Fwd_SE, leaf, interNode, Fwd_SePtr);
			FillNeighbors(Geo3d_BalPrTreeOctant::Fwd_NE, leaf, interNode, Fwd_NePtr);
			FillNeighbors(Geo3d_BalPrTreeOctant::Fwd_NW, leaf, interNode, Fwd_NwPtr);

			FillNeighbors(Geo3d_BalPrTreeOctant::Bwd_SW, leaf, interNode, Bwd_SwPtr);
			FillNeighbors(Geo3d_BalPrTreeOctant::Bwd_SE, leaf, interNode, Bwd_SePtr);
			FillNeighbors(Geo3d_BalPrTreeOctant::Bwd_NE, leaf, interNode, Bwd_NePtr);
			FillNeighbors(Geo3d_BalPrTreeOctant::Bwd_NW, leaf, interNode, Bwd_NwPtr);

			UpdateFather(leaf, interNode);

			const auto coord = b.CalcCentre();
			for (const auto& x : pItems)
			{
				SwitchToInsert(x, coord, leaf->Box(), interNode);
			}

			SwitchToInsert(theItem, coord, leaf->Box(), interNode);

			if (leaf)
			{
				delete leaf;
				leaf = 0;
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

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::NullifyPointer
(
	node *& t, 
	internalNode *& Internal
)
{
	if
		(
			!Internal->BwdSw() &&
			!Internal->BwdSe() &&
			!Internal->BwdNe() &&
			!Internal->BwdNw() &&

			!Internal->FwdSw() &&
			!Internal->FwdSe() &&
			!Internal->FwdNe() &&
			!Internal->FwdNw()
			)
	{
		delete t;
		t = nullptr;
	}
}

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::SwitchToRemove
(
	const T & theItem, 
	internalNode *& t
)
{
	switch (CalcOctant(geom::CoordinateOf(theItem), t->Box()->CalcCentre()))
	{
	case Geo3d_BalPrTreeOctant::Bwd_SW:
		Remove(theItem, t->BwdSwRef());
		break;
	case Geo3d_BalPrTreeOctant::Bwd_SE:
		Remove(theItem, t->BwdSeRef());
		break;
	case Geo3d_BalPrTreeOctant::Bwd_NE:
		Remove(theItem, t->BwdNeRef());
		break;
	case Geo3d_BalPrTreeOctant::Bwd_NW:
		Remove(theItem, t->BwdNwRef());
		break;
	case Geo3d_BalPrTreeOctant::Fwd_SW:
		Remove(theItem, t->FwdSwRef());
		break;
	case Geo3d_BalPrTreeOctant::Fwd_SE:
		Remove(theItem, t->FwdSeRef());
		break;
	case Geo3d_BalPrTreeOctant::Fwd_NE:
		Remove(theItem, t->FwdNeRef());
		break;
	case Geo3d_BalPrTreeOctant::Fwd_NW:
		Remove(theItem, t->FwdNwRef());
		break;
	default:
		FatalErrorIn(FunctionSIG)
			<< "Unspecified type of octant has been detected!" << endl
			<< abort(FatalError);
		break;
	}
}

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::Remove
(
	const T & theItem,
	node *& t
)
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

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::LinkInners(internalNode * t) const
{
	auto fwd_swPtr = dynamic_cast<leafNode*>(t->FwdSw());
	auto fwd_sePtr = dynamic_cast<leafNode*>(t->FwdSe());
	auto fwd_nePtr = dynamic_cast<leafNode*>(t->FwdNe());
	auto fwd_nwPtr = dynamic_cast<leafNode*>(t->FwdNw());

	auto bwd_swPtr = dynamic_cast<leafNode*>(t->BwdSw());
	auto bwd_sePtr = dynamic_cast<leafNode*>(t->BwdSe());
	auto bwd_nePtr = dynamic_cast<leafNode*>(t->BwdNe());
	auto bwd_nwPtr = dynamic_cast<leafNode*>(t->BwdNw());

	Debug_Null_Pointer(fwd_swPtr);
	Debug_Null_Pointer(fwd_sePtr);
	Debug_Null_Pointer(fwd_nePtr);
	Debug_Null_Pointer(fwd_nwPtr);

	Debug_Null_Pointer(bwd_swPtr);
	Debug_Null_Pointer(bwd_sePtr);
	Debug_Null_Pointer(bwd_nePtr);
	Debug_Null_Pointer(bwd_nwPtr);

	fwd_swPtr->ENeighborsRef().insert(fwd_sePtr);
	fwd_swPtr->NNeighborsRef().insert(fwd_nwPtr);
	fwd_swPtr->BNeighborsRef().insert(bwd_swPtr);

	fwd_sePtr->WNeighborsRef().insert(fwd_swPtr);
	fwd_sePtr->NNeighborsRef().insert(fwd_nePtr);
	fwd_sePtr->BNeighborsRef().insert(bwd_sePtr);

	fwd_nePtr->WNeighborsRef().insert(fwd_nwPtr);
	fwd_nePtr->SNeighborsRef().insert(fwd_sePtr);
	fwd_nePtr->BNeighborsRef().insert(bwd_nePtr);

	fwd_nwPtr->ENeighborsRef().insert(fwd_nePtr);
	fwd_nwPtr->SNeighborsRef().insert(fwd_swPtr);
	fwd_nwPtr->BNeighborsRef().insert(bwd_nwPtr);

	bwd_swPtr->ENeighborsRef().insert(bwd_sePtr);
	bwd_swPtr->NNeighborsRef().insert(bwd_nwPtr);
	bwd_swPtr->FNeighborsRef().insert(fwd_swPtr);

	bwd_sePtr->WNeighborsRef().insert(bwd_swPtr);
	bwd_sePtr->NNeighborsRef().insert(bwd_nePtr);
	bwd_sePtr->FNeighborsRef().insert(fwd_sePtr);

	bwd_nePtr->WNeighborsRef().insert(bwd_nwPtr);
	bwd_nePtr->SNeighborsRef().insert(bwd_sePtr);
	bwd_nePtr->FNeighborsRef().insert(fwd_nePtr);

	bwd_nwPtr->ENeighborsRef().insert(bwd_nePtr);
	bwd_nwPtr->SNeighborsRef().insert(bwd_swPtr);
	bwd_nwPtr->FNeighborsRef().insert(fwd_nwPtr);
}

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::RemoveLeafFromNeighbors(leafNode * old) const
{
	for (const auto& x : old->SNeighbors())
	{
		x->NNeighborsRef().erase(old);
	}
	for (const auto& x : old->ENeighbors())
	{
		x->WNeighborsRef().erase(old);
	}
	for (const auto& x : old->NNeighbors())
	{
		x->SNeighborsRef().erase(old);
	}
	for (const auto& x : old->WNeighbors())
	{
		x->ENeighborsRef().erase(old);
	}
	for (const auto& x : old->BNeighbors())
	{
		x->FNeighborsRef().erase(old);
	}
	for (const auto& x : old->FNeighbors())
	{
		x->BNeighborsRef().erase(old);
	}
}

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::FillNeighbors
(
	const Geo3d_BalPrTreeOctant o, 
	leafNode * old, 
	internalNode * father,
	leafNode * t
) const
{
	const auto& SN = old->SNeighbors();
	const auto& EN = old->ENeighbors();
	const auto& NN = old->NNeighbors();
	const auto& WN = old->WNeighbors();
	const auto& BN = old->BNeighbors();
	const auto& FN = old->FNeighbors();

	auto fwd_swPtr = dynamic_cast<leafNode*>(father->FwdSw());
	auto fwd_sePtr = dynamic_cast<leafNode*>(father->FwdSe());
	auto fwd_nePtr = dynamic_cast<leafNode*>(father->FwdNe());
	auto fwd_nwPtr = dynamic_cast<leafNode*>(father->FwdNw());

	auto bwd_swPtr = dynamic_cast<leafNode*>(father->BwdSw());
	auto bwd_sePtr = dynamic_cast<leafNode*>(father->BwdSe());
	auto bwd_nePtr = dynamic_cast<leafNode*>(father->BwdNe());
	auto bwd_nwPtr = dynamic_cast<leafNode*>(father->BwdNw());

	Debug_Null_Pointer(fwd_swPtr);
	Debug_Null_Pointer(fwd_sePtr);
	Debug_Null_Pointer(fwd_nePtr);
	Debug_Null_Pointer(fwd_nwPtr);

	Debug_Null_Pointer(bwd_swPtr);
	Debug_Null_Pointer(bwd_sePtr);
	Debug_Null_Pointer(bwd_nePtr);
	Debug_Null_Pointer(bwd_nwPtr);

	const auto& tBox = *old->Box();
	auto c = tBox.CalcCentre();

	std::vector<leafNode*> QSN, QEN, QNN, QWN, QFN, QBN;
	switch (o)
	{
	case Geo3d_BalPrTreeOctant::Bwd_SW:
	{
		if (WN.size() <= 1) for (const auto& x : WN) QWN.push_back(x);
		else
			for (const auto& x : WN)
				if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Bwd_SW)
					QWN.push_back(x);

		if (SN.size() <= 1) for (const auto& x : SN) QSN.push_back(x);
		else
			for (const auto& x : SN)
				if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Bwd_SW)
					QSN.push_back(x);

		if (BN.size() <= 1) for (const auto& x : BN) QBN.push_back(x);
		else
			for (const auto& x : BN)
				if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Bwd_SW)
					QBN.push_back(x);
		break;
	}
	case Geo3d_BalPrTreeOctant::Bwd_SE:
	{
		if (SN.size() <= 1) for (const auto& x : SN) QSN.push_back(x);
		else
			for (const auto& x : SN)
				if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Bwd_SE)
					QSN.push_back(x);

		if (EN.size() <= 1) for (const auto& x : EN) QEN.push_back(x);
		else
			for (const auto& x : EN)
				if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Bwd_SE)
					QEN.push_back(x);

		if (BN.size() <= 1) for (const auto& x : BN) QBN.push_back(x);
		else
			for (const auto& x : BN)
				if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Bwd_SE)
					QBN.push_back(x);
		break;
	}
	case Geo3d_BalPrTreeOctant::Bwd_NE:
	{
		if (EN.size() <= 1) for (const auto& x : EN) QEN.push_back(x);
		else
			for (const auto& x : EN)
				if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Bwd_NE)
					QEN.push_back(x);

		if (NN.size() <= 1) for (const auto& x : NN) QNN.push_back(x);
		else
			for (const auto& x : NN)
				if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Bwd_NE)
					QNN.push_back(x);

		if (BN.size() <= 1) for (const auto& x : BN) QBN.push_back(x);
		else
			for (const auto& x : BN)
				if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Bwd_NE)
					QBN.push_back(x);
		break;
	}
	case Geo3d_BalPrTreeOctant::Bwd_NW:
	{
		if (NN.size() <= 1) for (const auto& x : NN) QNN.push_back(x);
		else
			for (const auto& x : NN)
				if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Bwd_NW)
					QNN.push_back(x);

		if (WN.size() <= 1) for (const auto& x : WN) QWN.push_back(x);
		else
			for (const auto& x : WN)
				if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Bwd_NW)
					QWN.push_back(x);

		if (BN.size() <= 1) for (const auto& x : BN) QBN.push_back(x);
		else
			for (const auto& x : BN)
				if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Bwd_NW)
					QBN.push_back(x);
		break;
	}
	case Geo3d_BalPrTreeOctant::Fwd_SW:
	{
		if (WN.size() <= 1) for (const auto& x : WN) QWN.push_back(x);
		else
			for (const auto& x : WN)
				if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Fwd_SW)
					QWN.push_back(x);

		if (SN.size() <= 1) for (const auto& x : SN) QSN.push_back(x);
		else
			for (const auto& x : SN)
				if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Fwd_SW)
					QSN.push_back(x);

		if (FN.size() <= 1) for (const auto& x : FN) QFN.push_back(x);
		else
			for (const auto& x : FN)
				if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Fwd_SW)
					QFN.push_back(x);
		break;
	}
	case Geo3d_BalPrTreeOctant::Fwd_SE:
	{
		if (SN.size() <= 1) for (const auto& x : SN) QSN.push_back(x);
		else
			for (const auto& x : SN)
				if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Fwd_SE)
					QSN.push_back(x);

		if (EN.size() <= 1) for (const auto& x : EN) QEN.push_back(x);
		else
			for (const auto& x : EN)
				if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Fwd_SE)
					QEN.push_back(x);

		if (FN.size() <= 1) for (const auto& x : FN) QFN.push_back(x);
		else
			for (const auto& x : FN)
				if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Fwd_SE)
					QFN.push_back(x);
		break;
	}
	case Geo3d_BalPrTreeOctant::Fwd_NE:
	{
		if (EN.size() <= 1) for (const auto& x : EN) QEN.push_back(x);
		else
			for (const auto& x : EN)
				if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Fwd_NE)
					QEN.push_back(x);

		if (NN.size() <= 1) for (const auto& x : NN) QNN.push_back(x);
		else
			for (const auto& x : NN)
				if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Fwd_NE)
					QNN.push_back(x);

		if (FN.size() <= 1) for (const auto& x : FN) QFN.push_back(x);
		else
			for (const auto& x : FN)
				if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Fwd_NE)
					QFN.push_back(x);
		break;
	}
	case Geo3d_BalPrTreeOctant::Fwd_NW:
	{
		if (NN.size() <= 1) for (const auto& x : NN) QNN.push_back(x);
		else
			for (const auto& x : NN)
				if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Fwd_NW)
					QNN.push_back(x);

		if (WN.size() <= 1) for (const auto& x : WN) QWN.push_back(x);
		else
			for (const auto& x : WN)
				if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Fwd_NW)
					QWN.push_back(x);

		if (FN.size() <= 1) for (const auto& x : FN) QFN.push_back(x);
		else
			for (const auto& x : FN)
				if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Fwd_NW)
					QFN.push_back(x);
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
		x->NNeighborsRef().insert(t);
		t->SNeighborsRef().insert(x);
	}
	for (const auto& x : QEN)
	{
		x->WNeighborsRef().insert(t);
		t->ENeighborsRef().insert(x);
	}
	for (const auto& x : QNN)
	{
		x->SNeighborsRef().insert(t);
		t->NNeighborsRef().insert(x);
	}
	for (const auto& x : QWN)
	{
		x->ENeighborsRef().insert(t);
		t->WNeighborsRef().insert(x);
	}
	for (const auto& x : QBN)
	{
		x->FNeighborsRef().insert(t);
		t->BNeighborsRef().insert(x);
	}
	for (const auto& x : QFN)
	{
		x->BNeighborsRef().insert(t);
		t->FNeighborsRef().insert(x);
	}
}

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::Balance(node *& t)
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
		auto Fwd_SwPtr = new leafNode(std::make_shared<Entity3d_Box>(b.SubDivide(Box3d_SubDivideAlgorithm_Fwd_SW)));
		auto Fwd_SePtr = new leafNode(std::make_shared<Entity3d_Box>(b.SubDivide(Box3d_SubDivideAlgorithm_Fwd_SE)));
		auto Fwd_NePtr = new leafNode(std::make_shared<Entity3d_Box>(b.SubDivide(Box3d_SubDivideAlgorithm_Fwd_NE)));
		auto Fwd_NwPtr = new leafNode(std::make_shared<Entity3d_Box>(b.SubDivide(Box3d_SubDivideAlgorithm_Fwd_NW)));

		auto Bwd_SwPtr = new leafNode(std::make_shared<Entity3d_Box>(b.SubDivide(Box3d_SubDivideAlgorithm_Aft_SW)));
		auto Bwd_SePtr = new leafNode(std::make_shared<Entity3d_Box>(b.SubDivide(Box3d_SubDivideAlgorithm_Aft_SE)));
		auto Bwd_NePtr = new leafNode(std::make_shared<Entity3d_Box>(b.SubDivide(Box3d_SubDivideAlgorithm_Aft_NE)));
		auto Bwd_NwPtr = new leafNode(std::make_shared<Entity3d_Box>(b.SubDivide(Box3d_SubDivideAlgorithm_Aft_NW)));

		Debug_Null_Pointer(Fwd_SwPtr);
		Debug_Null_Pointer(Fwd_SePtr);
		Debug_Null_Pointer(Fwd_NePtr);
		Debug_Null_Pointer(Fwd_NwPtr);

		Debug_Null_Pointer(Bwd_SwPtr);
		Debug_Null_Pointer(Bwd_SePtr);
		Debug_Null_Pointer(Bwd_NePtr);
		Debug_Null_Pointer(Bwd_NwPtr);

		Fwd_SwPtr->FatherRef() = interNode;
		Fwd_SePtr->FatherRef() = interNode;
		Fwd_NePtr->FatherRef() = interNode;
		Fwd_NwPtr->FatherRef() = interNode;

		Bwd_SwPtr->FatherRef() = interNode;
		Bwd_SePtr->FatherRef() = interNode;
		Bwd_NePtr->FatherRef() = interNode;
		Bwd_NwPtr->FatherRef() = interNode;

		interNode->FwdSwRef() = Fwd_SwPtr;
		interNode->FwdSeRef() = Fwd_SePtr;
		interNode->FwdNeRef() = Fwd_NePtr;
		interNode->FwdNwRef() = Fwd_NwPtr;

		interNode->BwdSwRef() = Bwd_SwPtr;
		interNode->BwdSeRef() = Bwd_SePtr;
		interNode->BwdNeRef() = Bwd_NePtr;
		interNode->BwdNwRef() = Bwd_NwPtr;

		LinkInners(interNode);

		// Remove Old Leaf from Neighbors
		RemoveLeafFromNeighbors(leaf);

		FillNeighbors(Geo3d_BalPrTreeOctant::Fwd_SW, leaf, interNode, Fwd_SwPtr);
		FillNeighbors(Geo3d_BalPrTreeOctant::Fwd_SE, leaf, interNode, Fwd_SePtr);
		FillNeighbors(Geo3d_BalPrTreeOctant::Fwd_NE, leaf, interNode, Fwd_NePtr);
		FillNeighbors(Geo3d_BalPrTreeOctant::Fwd_NW, leaf, interNode, Fwd_NwPtr);

		FillNeighbors(Geo3d_BalPrTreeOctant::Bwd_SW, leaf, interNode, Bwd_SwPtr);
		FillNeighbors(Geo3d_BalPrTreeOctant::Bwd_SE, leaf, interNode, Bwd_SePtr);
		FillNeighbors(Geo3d_BalPrTreeOctant::Bwd_NE, leaf, interNode, Bwd_NePtr);
		FillNeighbors(Geo3d_BalPrTreeOctant::Bwd_NW, leaf, interNode, Bwd_NwPtr);

		UpdateFather(leaf, interNode);

		if (t)
		{
			delete t;
			t = 0;
		}

		t = interNode;

		Balance(interNode->FwdSwRef());
		Balance(interNode->FwdSeRef());
		Balance(interNode->FwdNeRef());
		Balance(interNode->FwdNwRef());

		Balance(interNode->BwdSwRef());
		Balance(interNode->BwdSeRef());
		Balance(interNode->BwdNeRef());
		Balance(interNode->BwdNwRef());
	}
	else
	{
		auto inner = dynamic_cast<internalNode*>(t);
		Debug_Null_Pointer(inner);

		Balance(inner->FwdSwRef());
		Balance(inner->FwdSeRef());
		Balance(inner->FwdNeRef());
		Balance(inner->FwdNwRef());

		Balance(inner->BwdSwRef());
		Balance(inner->BwdSeRef());
		Balance(inner->BwdNeRef());
		Balance(inner->BwdNwRef());
	}
}

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::SwitchToSearch
(
	const Entity3d_Box & theRegion,
	internalNode * t,
	std::list<T>& theItems
) const
{
	if (t->BwdSw())
	{
		if (theRegion.IsIntersect(*t->BwdSw()->Box()))
			Search(theRegion, t->BwdSw(), theItems);
	}

	if (t->BwdSe())
	{
		if (theRegion.IsIntersect(*t->BwdSe()->Box()))
			Search(theRegion, t->BwdSe(), theItems);
	}

	if (t->BwdNe())
	{
		if (theRegion.IsIntersect(*t->BwdNe()->Box()))
			Search(theRegion, t->BwdNe(), theItems);
	}

	if (t->BwdNw())
	{
		if (theRegion.IsIntersect(*t->BwdNw()->Box()))
			Search(theRegion, t->BwdNw(), theItems);
	}

	if (t->FwdSw())
	{
		if (theRegion.IsIntersect(*t->FwdSw()->Box()))
			Search(theRegion, t->FwdSw(), theItems);
	}

	if (t->FwdSe())
	{
		if (theRegion.IsIntersect(*t->FwdSe()->Box()))
			Search(theRegion, t->FwdSe(), theItems);
	}

	if (t->FwdNe())
	{
		if (theRegion.IsIntersect(*t->FwdNe()->Box()))
			Search(theRegion, t->FwdNe(), theItems);
	}

	if (t->FwdNw())
	{
		if (theRegion.IsIntersect(*t->FwdNw()->Box()))
			Search(theRegion, t->FwdNw(), theItems);
	}
}

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::SwitchToSearch
(
	const Entity3d_Box & theRegion,
	internalNode * t,
	std::vector<T>& theItems
) const
{
	if (t->BwdSw())
	{
		if (theRegion.IsIntersect(*t->BwdSw()->Box()))
			Search(theRegion, t->BwdSw(), theItems);
	}

	if (t->BwdSe())
	{
		if (theRegion.IsIntersect(*t->BwdSe()->Box()))
			Search(theRegion, t->BwdSe(), theItems);
	}

	if (t->BwdNe())
	{
		if (theRegion.IsIntersect(*t->BwdNe()->Box()))
			Search(theRegion, t->BwdNe(), theItems);
	}

	if (t->BwdNw())
	{
		if (theRegion.IsIntersect(*t->BwdNw()->Box()))
			Search(theRegion, t->BwdNw(), theItems);
	}

	if (t->FwdSw())
	{
		if (theRegion.IsIntersect(*t->FwdSw()->Box()))
			Search(theRegion, t->FwdSw(), theItems);
	}

	if (t->FwdSe())
	{
		if (theRegion.IsIntersect(*t->FwdSe()->Box()))
			Search(theRegion, t->FwdSe(), theItems);
	}

	if (t->FwdNe())
	{
		if (theRegion.IsIntersect(*t->FwdNe()->Box()))
			Search(theRegion, t->FwdNe(), theItems);
	}

	if (t->FwdNw())
	{
		if (theRegion.IsIntersect(*t->FwdNw()->Box()))
			Search(theRegion, t->FwdNw(), theItems);
	}
}

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::SwitchToSearch
(
	const Entity3d_Box & theRegion,
	internalNode * t,
	std::vector<leafNode*>& theItems
) const
{
	if (t->BwdSw())
	{
		if (theRegion.IsIntersect(*t->BwdSw()->Box()))
			Search(theRegion, t->BwdSw(), theItems);
	}

	if (t->BwdSe())
	{
		if (theRegion.IsIntersect(*t->BwdSe()->Box()))
			Search(theRegion, t->BwdSe(), theItems);
	}

	if (t->BwdNe())
	{
		if (theRegion.IsIntersect(*t->BwdNe()->Box()))
			Search(theRegion, t->BwdNe(), theItems);
	}

	if (t->BwdNw())
	{
		if (theRegion.IsIntersect(*t->BwdNw()->Box()))
			Search(theRegion, t->BwdNw(), theItems);
	}

	if (t->FwdSw())
	{
		if (theRegion.IsIntersect(*t->FwdSw()->Box()))
			Search(theRegion, t->FwdSw(), theItems);
	}

	if (t->FwdSe())
	{
		if (theRegion.IsIntersect(*t->FwdSe()->Box()))
			Search(theRegion, t->FwdSe(), theItems);
	}

	if (t->FwdNe())
	{
		if (theRegion.IsIntersect(*t->FwdNe()->Box()))
			Search(theRegion, t->FwdNe(), theItems);
	}

	if (t->FwdNw())
	{
		if (theRegion.IsIntersect(*t->FwdNw()->Box()))
			Search(theRegion, t->FwdNw(), theItems);
	}
}

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::Search
(
	const Entity3d_Box & theBox,
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

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::Search
(
	const Entity3d_Box & theBox,
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

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::Search
(
	const Entity3d_Box & theBox,
	node * t,
	std::vector<leafNode*>& theItems
) const
{
	leafNode* leaf = dynamic_cast<leafNode*>(t);
	if (leaf)
	{
		if (leaf->Box()->IsIntersect(theBox))
		{
			theItems.push_back(leaf);
		}
	}
	else
	{
		internalNode* Internal =
			dynamic_cast<internalNode*>(t);

		SwitchToSearch(theBox, Internal, theItems);
	}
}

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::SwitchToRetrieveLeavesTo
(
	internalNode * Internal,
	std::vector<leafNode*>& theItems
) const
{
	if (Internal->BwdSw()) RetrieveLeavesTo(Internal->BwdSw(), theItems);
	if (Internal->BwdSe()) RetrieveLeavesTo(Internal->BwdSe(), theItems);
	if (Internal->BwdNe()) RetrieveLeavesTo(Internal->BwdNe(), theItems);
	if (Internal->BwdNw()) RetrieveLeavesTo(Internal->BwdNw(), theItems);

	if (Internal->FwdSw()) RetrieveLeavesTo(Internal->FwdSw(), theItems);
	if (Internal->FwdSe()) RetrieveLeavesTo(Internal->FwdSe(), theItems);
	if (Internal->FwdNe()) RetrieveLeavesTo(Internal->FwdNe(), theItems);
	if (Internal->FwdNw()) RetrieveLeavesTo(Internal->FwdNw(), theItems);
}

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::RetrieveLeavesTo
(
	node * t,
	std::vector<leafNode*>& theLeaves
) const
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

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::SwitchToRetrieveTo
(
	internalNode * Internal,
	std::list<T>& theItems
) const
{
	if (Internal->BwdSw()) RetrieveTo(Internal->BwdSw(), theItems);
	if (Internal->BwdSe()) RetrieveTo(Internal->BwdSe(), theItems);
	if (Internal->BwdNe()) RetrieveTo(Internal->BwdNe(), theItems);
	if (Internal->BwdNw()) RetrieveTo(Internal->BwdNw(), theItems);

	if (Internal->FwdSw()) RetrieveTo(Internal->FwdSw(), theItems);
	if (Internal->FwdSe()) RetrieveTo(Internal->FwdSe(), theItems);
	if (Internal->FwdNe()) RetrieveTo(Internal->FwdNe(), theItems);
	if (Internal->FwdNw()) RetrieveTo(Internal->FwdNw(), theItems);
}

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::SwitchToRetrieveTo
(
	internalNode * Internal, 
	std::vector<T>& theItems
) const
{
	if (Internal->BwdSw()) RetrieveTo(Internal->BwdSw(), theItems);
	if (Internal->BwdSe()) RetrieveTo(Internal->BwdSe(), theItems);
	if (Internal->BwdNe()) RetrieveTo(Internal->BwdNe(), theItems);
	if (Internal->BwdNw()) RetrieveTo(Internal->BwdNw(), theItems);

	if (Internal->FwdSw()) RetrieveTo(Internal->FwdSw(), theItems);
	if (Internal->FwdSe()) RetrieveTo(Internal->FwdSe(), theItems);
	if (Internal->FwdNe()) RetrieveTo(Internal->FwdNe(), theItems);
	if (Internal->FwdNw()) RetrieveTo(Internal->FwdNw(), theItems);
}

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::RetrieveTo
(
	node * t,
	std::list<T>& theItems
) const
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

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::RetrieveTo
(
	node * t, 
	std::vector<T>& theItems
) const
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

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::UpdateFather
(
	leafNode * t,
	node * inter
)
{
	if (NOT t->Father()) return;
	auto father = dynamic_cast<internalNode*>(t->Father());
	Debug_Null_Pointer(father);

	if (father->FwdSw() IS_EQUAL t) father->FwdSwRef() = inter;
	else if (father->FwdSe() IS_EQUAL t) father->FwdSeRef() = inter;
	else if (father->FwdNe() IS_EQUAL t) father->FwdNeRef() = inter;
	else if (father->FwdNw() IS_EQUAL t) father->FwdNwRef() = inter;
	else if (father->BwdSw() IS_EQUAL t) father->BwdSwRef() = inter;
	else if (father->BwdSe() IS_EQUAL t) father->BwdSeRef() = inter;
	else if (father->BwdNe() IS_EQUAL t) father->BwdNeRef() = inter;
	else if (father->BwdNw() IS_EQUAL t) father->BwdNwRef() = inter;
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "Unexpected error has been detected!" << endl
			<< abort(FatalError);
	}
}

template<class T, class Attrb>
inline std::vector<typename tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::leafNode*> 
tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::RetrieveLeaves
(
	const Entity3d_Box & theRegion
) const
{
	std::vector<leafNode*> items;
	GeometrySearch(theRegion, items);
	return std::move(items);
}

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::InsertToGeometry
(
	const T & theItem
)
{
	Debug_If_Condition_Message
	(
		!geom::CoordinateOf, " No coordinate function for Pr-Tree"
	);
	NbSubdivideRef() = 0;
	auto b = std::make_shared<Entity3d_Box>(geom::GeometryBoundingBox());
	Insert(theItem, b, theRoot_);
}

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::InsertToGeometry
(
	const std::vector<T>& theItems
)
{
	Debug_If_Condition_Message
	(
		!geom::CoordinateOf, " No coordinate function for Pr-Tree"
	);
	auto b = std::make_shared<Entity3d_Box>(geom::GeometryBoundingBox());
	for (const auto& x : theItems)
	{
		Insert(x, b, theRoot_);
	}
}

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::RemoveFromGeometry
(
	const T & theItem
)
{
	if (Size())
	{
		Remove(theItem, theRoot_);
	}
}

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::GeometrySearch
(
	const Standard_Real theRadius, 
	const Pnt3d & theCentre,
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

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::GeometrySearch
(
	const Standard_Real theRadius, 
	const Pnt3d & theCentre,
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

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::GeometrySearch
(
	const Entity3d_Box & theRegion, 
	std::list<T>& theList
) const
{
	if (Size())
	{
		Search(theRegion, theRoot_, theList);
	}
}

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::GeometrySearch
(
	const Entity3d_Box & theRegion, 
	std::vector<T>& theItems
) const
{
	if (Size())
	{
		Search(theRegion, theRoot_, theItems);
	}
}

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::GeometrySearch
(
	const Entity3d_Box & theRegion,
	std::vector<leafNode*>& theItems
) const
{
	if (Size())
	{
		Search(theRegion, theRoot_, theItems);
	}
}

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::PostBalance()
{
	while (true)
	{
		IsBalancedRef() = Standard_True;
		Balance(theRoot_);
		if (IsBalancedRef()) break;
	}
}

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::Clear()
{
	Clear(theRoot_);
}

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::RetrieveLeavesTo
(
	std::vector<leafNode*>& theLeaves
) const
{
	if (Size())
	{
		RetrieveLeavesTo(theRoot_, theLeaves);
	}
}

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::RetrieveLeavesTo
(
	const Entity3d_Box & theRegion,
	std::vector<leafNode*>& theItems
) const
{
	if (Size())
	{
		GeometrySearch(theRegion, theItems);
	}
}

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::RetrieveFromGeometryTo
(
	std::list<T>& theItems
) const
{
	if (Size())
	{
		RetrieveTo(theRoot_, theItems);
	}
}

template<class T, class Attrb>
inline void tnbLib::Geo3d_AttrbBalPrTree<T, Attrb>::RetrieveFromGeometryTo
(
	std::vector<T>& theItems
) const
{
	if (Size())
	{
		RetrieveTo(theRoot_, theItems);
	}
}