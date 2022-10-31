#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
template<class T>
inline Standard_Boolean 
tnbLib::Geo3d_BalPrTree<T>::IsUnbalanced
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

template<class T>
inline void tnbLib::Geo3d_BalPrTree<T>::SwitchToClear(internalNode *& t)
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

template<class T>
inline void tnbLib::Geo3d_BalPrTree<T>::Clear(node *& t)
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
inline void tnbLib::Geo3d_BalPrTree<T>::SwitchToInsert
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

template<class T>
inline void tnbLib::Geo3d_BalPrTree<T>::Insert
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

		auto Fwd_SwPtr = new leafNode(std::make_shared<Entity3d_Box>(theBox->SubDivide(Box3d_SubDivideAlgorithm_Fwd_SW)));
		auto Fwd_SePtr = new leafNode(std::make_shared<Entity3d_Box>(theBox->SubDivide(Box3d_SubDivideAlgorithm_Fwd_SE)));
		auto Fwd_NePtr = new leafNode(std::make_shared<Entity3d_Box>(theBox->SubDivide(Box3d_SubDivideAlgorithm_Fwd_NE)));
		auto Fwd_NwPtr = new leafNode(std::make_shared<Entity3d_Box>(theBox->SubDivide(Box3d_SubDivideAlgorithm_Fwd_NW)));

		auto Bwd_SwPtr = new leafNode(std::make_shared<Entity3d_Box>(theBox->SubDivide(Box3d_SubDivideAlgorithm_Aft_SW)));
		auto Bwd_SePtr = new leafNode(std::make_shared<Entity3d_Box>(theBox->SubDivide(Box3d_SubDivideAlgorithm_Aft_SE)));
		auto Bwd_NePtr = new leafNode(std::make_shared<Entity3d_Box>(theBox->SubDivide(Box3d_SubDivideAlgorithm_Aft_NE)));
		auto Bwd_NwPtr = new leafNode(std::make_shared<Entity3d_Box>(theBox->SubDivide(Box3d_SubDivideAlgorithm_Aft_NW)));

		interNode->FwdSwRef() = Fwd_SwPtr;
		interNode->FwdSeRef() = Fwd_SePtr;
		interNode->FwdNeRef() = Fwd_NePtr;
		interNode->FwdNwRef() = Fwd_NwPtr;

		interNode->BwdSwRef() = Bwd_SwPtr;
		interNode->BwdSeRef() = Bwd_SePtr;
		interNode->BwdNeRef() = Bwd_NePtr;
		interNode->BwdNwRef() = Bwd_NwPtr;

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

			/*std::cout << std::endl;
			std::cout << "fn size: " << leaf->FNeighbors().size() << std::endl;
			std::cout << "bn size: " << leaf->BNeighbors().size() << std::endl;
			std::cout << "en size: " << leaf->ENeighbors().size() << std::endl;
			std::cout << "wn size: " << leaf->WNeighbors().size() << std::endl;
			std::cout << "sn size: " << leaf->SNeighbors().size() << std::endl;
			std::cout << "nn size: " << leaf->NNeighbors().size() << std::endl;
			std::cout << std::endl;
			PAUSE;*/
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

template<class T>
inline void tnbLib::Geo3d_BalPrTree<T>::NullifyPointer
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

template<class T>
inline void tnbLib::Geo3d_BalPrTree<T>::SwitchToRemove
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

template<class T>
inline void tnbLib::Geo3d_BalPrTree<T>::Remove(const T & theItem, node *& t)
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
inline void tnbLib::Geo3d_BalPrTree<T>::LinkInners(internalNode * t) const
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

	fwd_swPtr->ENeighborsRef().push_back(fwd_sePtr);
	fwd_swPtr->NNeighborsRef().push_back(fwd_nwPtr);
	fwd_swPtr->BNeighborsRef().push_back(bwd_swPtr);

	fwd_sePtr->WNeighborsRef().push_back(fwd_swPtr);
	fwd_sePtr->NNeighborsRef().push_back(fwd_nePtr);
	fwd_sePtr->BNeighborsRef().push_back(bwd_sePtr);

	fwd_nePtr->WNeighborsRef().push_back(fwd_nwPtr);
	fwd_nePtr->SNeighborsRef().push_back(fwd_sePtr);
	fwd_nePtr->BNeighborsRef().push_back(bwd_nePtr);

	fwd_nwPtr->ENeighborsRef().push_back(fwd_nePtr);
	fwd_nwPtr->SNeighborsRef().push_back(fwd_swPtr);
	fwd_nwPtr->BNeighborsRef().push_back(bwd_nwPtr);

	bwd_swPtr->ENeighborsRef().push_back(bwd_sePtr);
	bwd_swPtr->NNeighborsRef().push_back(bwd_nwPtr);
	bwd_swPtr->FNeighborsRef().push_back(fwd_swPtr);

	bwd_sePtr->WNeighborsRef().push_back(bwd_swPtr);
	bwd_sePtr->NNeighborsRef().push_back(bwd_nePtr);
	bwd_sePtr->FNeighborsRef().push_back(fwd_sePtr);

	bwd_nePtr->WNeighborsRef().push_back(bwd_nwPtr);
	bwd_nePtr->SNeighborsRef().push_back(bwd_sePtr);
	bwd_nePtr->FNeighborsRef().push_back(fwd_nePtr);

	bwd_nwPtr->ENeighborsRef().push_back(bwd_nePtr);
	bwd_nwPtr->SNeighborsRef().push_back(bwd_swPtr);
	bwd_nwPtr->FNeighborsRef().push_back(fwd_nwPtr);
}

template<class T>
inline void tnbLib::Geo3d_BalPrTree<T>::RemoveLeafFromNeighbors(leafNode * old) const
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
	for (const auto& x : old->BNeighbors())
	{
		x->FNeighborsRef().remove(old);
	}
	for (const auto& x : old->FNeighbors())
	{
		x->BNeighborsRef().remove(old);
	}
}

template<class T>
inline void tnbLib::Geo3d_BalPrTree<T>::FillNeighbors
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
			{
				if (IsBwdSW(x->Box()->CalcCentre(), c))
				{
					QWN.push_back(x);
				}
				/*if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Bwd_SW)
					QWN.push_back(x);*/
			}

		if (SN.size() <= 1) for (const auto& x : SN) QSN.push_back(x);
		else
			for (const auto& x : SN)
			{
				if (IsBwdSW(x->Box()->CalcCentre(), c))
				{
					QSN.push_back(x);
				}
				/*if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Bwd_SW)
					QSN.push_back(x);*/
			}

		if (BN.size() <= 1) for (const auto& x : BN) QBN.push_back(x);
		else
			for (const auto& x : BN)
			{
				if (IsBwdSW(x->Box()->CalcCentre(), c))
				{
					QBN.push_back(x);
				}
				/*if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Bwd_SW)
					QBN.push_back(x);*/
			}
		break;
	}
	case Geo3d_BalPrTreeOctant::Bwd_SE:
	{
		if (SN.size() <= 1) for (const auto& x : SN) QSN.push_back(x);
		else
			for (const auto& x : SN)
			{
				if (IsBwdSE(x->Box()->CalcCentre(), c))
				{
					QSN.push_back(x);
				}
				/*if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Bwd_SE)
					QSN.push_back(x);*/
			}

		if (EN.size() <= 1) for (const auto& x : EN) QEN.push_back(x);
		else
			for (const auto& x : EN)
			{
				if (IsBwdSE(x->Box()->CalcCentre(), c))
				{
					QEN.push_back(x);
				}
				/*if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Bwd_SE)
					QEN.push_back(x);*/
			}

		if (BN.size() <= 1) for (const auto& x : BN) QBN.push_back(x);
		else
			for (const auto& x : BN)
			{
				if (IsBwdSE(x->Box()->CalcCentre(), c))
				{
					QBN.push_back(x);
				}
				/*if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Bwd_SE)
					QBN.push_back(x);*/
			}
		break;
	}
	case Geo3d_BalPrTreeOctant::Bwd_NE:
	{
		if (EN.size() <= 1) for (const auto& x : EN) QEN.push_back(x);
		else
			for (const auto& x : EN)
			{
				if (IsBwdNE(x->Box()->CalcCentre(), c))
				{
					QEN.push_back(x);
				}
				/*if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Bwd_NE)
					QEN.push_back(x);*/
			}

		if (NN.size() <= 1) for (const auto& x : NN) QNN.push_back(x);
		else
			for (const auto& x : NN)
			{
				if (IsBwdNE(x->Box()->CalcCentre(), c))
				{
					QNN.push_back(x);
				}
				/*if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Bwd_NE)
					QNN.push_back(x);*/
			}

		if (BN.size() <= 1) for (const auto& x : BN) QBN.push_back(x);
		else
			for (const auto& x : BN)
			{
				if (IsBwdNE(x->Box()->CalcCentre(), c))
				{
					QBN.push_back(x);
				}
				/*if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Bwd_NE)
					QBN.push_back(x);*/
			}
		break;
	}
	case Geo3d_BalPrTreeOctant::Bwd_NW:
	{
		if (NN.size() <= 1) for (const auto& x : NN) QNN.push_back(x);
		else
			for (const auto& x : NN)
			{
				if (IsBwdNW(x->Box()->CalcCentre(), c))
				{
					QBN.push_back(x);
				}
				/*if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Bwd_NW)
					QNN.push_back(x);*/
			}

		if (WN.size() <= 1) for (const auto& x : WN) QWN.push_back(x);
		else
			for (const auto& x : WN)
			{
				if (IsBwdNW(x->Box()->CalcCentre(), c))
				{
					QWN.push_back(x);
				}
				/*if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Bwd_NW)
					QWN.push_back(x);*/
			}

		if (BN.size() <= 1) for (const auto& x : BN) QBN.push_back(x);
		else
			for (const auto& x : BN)
			{
				if (IsBwdNW(x->Box()->CalcCentre(), c))
				{
					QBN.push_back(x);
				}
				/*if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Bwd_NW)
					QBN.push_back(x);*/
			}
		break;
	}
	case Geo3d_BalPrTreeOctant::Fwd_SW:
	{
		if (WN.size() <= 1) for (const auto& x : WN) QWN.push_back(x);
		else
			for (const auto& x : WN)
			{
				if (IsFwdSW(x->Box()->CalcCentre(), c))
				{
					QWN.push_back(x);
				}
				/*if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Fwd_SW)
					QWN.push_back(x);*/
			}

		if (SN.size() <= 1) for (const auto& x : SN) QSN.push_back(x);
		else
			for (const auto& x : SN)
			{
				if (IsFwdSW(x->Box()->CalcCentre(), c))
				{
					QSN.push_back(x);
				}
				/*if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Fwd_SW)
					QSN.push_back(x);*/
			}

		if (FN.size() <= 1) for (const auto& x : FN) QFN.push_back(x);
		else
			for (const auto& x : FN)
			{
				if (IsFwdSW(x->Box()->CalcCentre(), c))
				{
					QFN.push_back(x);
				}
				/*if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Fwd_SW)
					QFN.push_back(x);*/
			}

		break;
	}
	case Geo3d_BalPrTreeOctant::Fwd_SE:
	{
		if (SN.size() <= 1) for (const auto& x : SN) QSN.push_back(x);
		else
			for (const auto& x : SN)
			{
				if (IsFwdSE(x->Box()->CalcCentre(), c))
				{
					QSN.push_back(x);
				}
				/*if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Fwd_SE)
					QSN.push_back(x);*/
			}

		if (EN.size() <= 1) for (const auto& x : EN) QEN.push_back(x);
		else
			for (const auto& x : EN)
			{
				if (IsFwdSE(x->Box()->CalcCentre(), c))
				{
					QEN.push_back(x);
				}
				/*if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Fwd_SE)
					QEN.push_back(x);*/
			}

		if (FN.size() <= 1) for (const auto& x : FN) QFN.push_back(x);
		else
			for (const auto& x : FN)
			{
				if (IsFwdSE(x->Box()->CalcCentre(), c))
				{
					QFN.push_back(x);
				}
				/*if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Fwd_SE)
					QFN.push_back(x);*/
			}
		break;
	}
	case Geo3d_BalPrTreeOctant::Fwd_NE:
	{
		if (EN.size() <= 1) for (const auto& x : EN) QEN.push_back(x);
		else
			for (const auto& x : EN)
			{
				if (IsFwdNE(x->Box()->CalcCentre(), c))
				{
					QEN.push_back(x);
				}
				/*if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Fwd_NE)
					QEN.push_back(x);*/
			}

		if (NN.size() <= 1) for (const auto& x : NN) QNN.push_back(x);
		else
			for (const auto& x : NN)
			{
				if (IsFwdNE(x->Box()->CalcCentre(), c))
				{
					QNN.push_back(x);
				}
				/*if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Fwd_NE)
					QNN.push_back(x);*/
			}

		if (FN.size() <= 1) for (const auto& x : FN) QFN.push_back(x);
		else
			for (const auto& x : FN)
			{
				if (IsFwdNE(x->Box()->CalcCentre(), c))
				{
					QFN.push_back(x);
				}
				/*if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Fwd_NE)
					QFN.push_back(x);*/
			}
		break;
	}
	case Geo3d_BalPrTreeOctant::Fwd_NW:
	{
		if (NN.size() <= 1) for (const auto& x : NN) QNN.push_back(x);
		else
			for (const auto& x : NN)
			{
				if (IsFwdNW(x->Box()->CalcCentre(), c))
				{
					QNN.push_back(x);
				}
				/*if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Fwd_NW)
					QNN.push_back(x);*/
			}

		if (WN.size() <= 1) for (const auto& x : WN) QWN.push_back(x);
		else
			for (const auto& x : WN)
			{
				if (IsFwdNW(x->Box()->CalcCentre(), c))
				{
					QWN.push_back(x);
				}
				/*if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Fwd_NW)
					QWN.push_back(x);*/
			}

		if (FN.size() <= 1) for (const auto& x : FN) QFN.push_back(x);
		else
			for (const auto& x : FN)
			{
				if (IsFwdNW(x->Box()->CalcCentre(), c))
				{
					QFN.push_back(x);
				}
				/*if (CalcOctant(x->Box()->CalcCentre(), c) IS_EQUAL Geo3d_BalPrTreeOctant::Fwd_NW)
					QFN.push_back(x);*/
			}
		break;
	}
	default:
		FatalErrorIn(FunctionSIG)
			<< "unspecified type of octant has been detected." << endl
			<< abort(FatalError);
		break;
	}
	/*std::cout << std::endl;
	std::cout << "QSN size: " << QSN.size() << std::endl;
	std::cout << "QEN size: " << QEN.size() << std::endl;
	std::cout << "QNN size: " << QNN.size() << std::endl;
	std::cout << "QWN size: " << QWN.size() << std::endl;
	std::cout << "QBN size: " << QBN.size() << std::endl;
	std::cout << "QFN size: " << QFN.size() << std::endl;
	std::cout << std::endl;
	PAUSE;*/
	for (const auto& x : QSN)
	{
		x->NNeighborsRef().push_back(t);
		t->SNeighborsRef().push_back(x);
		//std::cout << "new neibor size: " << x->NNeighborsRef().size() << std::endl;
	}
	for (const auto& x : QEN)
	{
		x->WNeighborsRef().push_back(t);
		t->ENeighborsRef().push_back(x);
		//std::cout << "new neibor size: " << x->WNeighborsRef().size() << std::endl;
	}
	for (const auto& x : QNN)
	{
		x->SNeighborsRef().push_back(t);
		t->NNeighborsRef().push_back(x);
		//std::cout << "new neibor size: " << x->SNeighborsRef().size() << std::endl;
	}
	for (const auto& x : QWN)
	{
		x->ENeighborsRef().push_back(t);
		t->WNeighborsRef().push_back(x);
		//std::cout << "new neibor size: " << x->ENeighborsRef().size() << std::endl;
	}
	for (const auto& x : QBN)
	{
		x->FNeighborsRef().push_back(t);
		t->BNeighborsRef().push_back(x);
		//std::cout << "new neibor size: " << x->FNeighborsRef().size() << std::endl;
	}
	for (const auto& x : QFN)
	{
		x->BNeighborsRef().push_back(t);
		t->FNeighborsRef().push_back(x);
		//std::cout << "new neibor size: " << x->BNeighborsRef().size() << std::endl;
	}
	//PAUSE;
}

template<class T>
inline void tnbLib::Geo3d_BalPrTree<T>::Balance(node *& t)
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

		UpdateFather(leaf, (node*)interNode);

		if (t)
		{
			delete leaf;
			t = 0;
		}

		t = interNode;

		//std::exit(1);
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

template<class T>
inline void tnbLib::Geo3d_BalPrTree<T>::SwitchToSearch
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

template<class T>
inline void tnbLib::Geo3d_BalPrTree<T>::SwitchToSearch
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

template<class T>
inline void tnbLib::Geo3d_BalPrTree<T>::Search
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

template<class T>
inline void tnbLib::Geo3d_BalPrTree<T>::Search
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

template<class T>
inline void tnbLib::Geo3d_BalPrTree<T>::SwitchToRetrieveLeavesTo
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

template<class T>
inline void tnbLib::Geo3d_BalPrTree<T>::RetrieveLeavesTo
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

template<class T>
inline void tnbLib::Geo3d_BalPrTree<T>::SwitchToRetrieveTo
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

template<class T>
inline void tnbLib::Geo3d_BalPrTree<T>::SwitchToRetrieveTo
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

template<class T>
inline void tnbLib::Geo3d_BalPrTree<T>::RetrieveTo
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

template<class T>
inline void tnbLib::Geo3d_BalPrTree<T>::RetrieveTo
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

template<class T>
inline void tnbLib::Geo3d_BalPrTree<T>::UpdateFather
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

template<class T>
inline Standard_Boolean tnbLib::Geo3d_BalPrTree<T>::IsBalanced() const
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
inline void tnbLib::Geo3d_BalPrTree<T>::InsertToGeometry(const T & theItem)
{
	Debug_If_Condition_Message
	(
		!geom::CoordinateOf, " No coordinate function for Pr-Tree"
	);
	this->NbSubdivideRef() = 0;
	auto b = std::make_shared<Entity3d_Box>(geom::GeometryBoundingBox());
	Insert(theItem, b, theRoot_);
}

template<class T>
inline void tnbLib::Geo3d_BalPrTree<T>::InsertToGeometry
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

template<class T>
inline void tnbLib::Geo3d_BalPrTree<T>::RemoveFromGeometry(const T & theItem)
{
	if (Size())
	{
		Remove(theItem, theRoot_);
	}
}

template<class T>
inline void tnbLib::Geo3d_BalPrTree<T>::GeometrySearch
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

template<class T>
inline void tnbLib::Geo3d_BalPrTree<T>::GeometrySearch
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

template<class T>
inline void tnbLib::Geo3d_BalPrTree<T>::GeometrySearch
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

template<class T>
inline void tnbLib::Geo3d_BalPrTree<T>::GeometrySearch
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

template<class T>
inline void tnbLib::Geo3d_BalPrTree<T>::PostBalance()
{
	size_t k = 0;
	
	while (true)
	{
		std::vector<leafNode*> leaves;
		RetrieveLeavesTo(leaves);
		IsBalancedRef() = Standard_True;
		for (const auto& x : leaves)
		{
			auto y = (node*)x;
			Balance(y);
		}	
		if (IsBalancedRef()) break;
	}
}

template<class T>
inline void tnbLib::Geo3d_BalPrTree<T>::Clear()
{
	Clear(theRoot_);
}

template<class T>
inline void tnbLib::Geo3d_BalPrTree<T>::RetrieveLeavesTo
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
inline void tnbLib::Geo3d_BalPrTree<T>::RetrieveFromGeometryTo(std::list<T>& theItems) const
{
	if (Size())
	{
		RetrieveTo(theRoot_, theItems);
	}
}

template<class T>
inline void tnbLib::Geo3d_BalPrTree<T>::RetrieveFromGeometryTo(std::vector<T>& theItems) const
{
	if (Size())
	{
		RetrieveTo(theRoot_, theItems);
	}
}