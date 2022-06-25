#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
template<class T>
inline void tnbLib::Geo3d_ApprxSpace<T>::Subdivide(Geo3d_ApprxSpaceNode *& t) const
{
	auto leaf = dynamic_cast<Geo3d_ApprxSpaceNode_Leaf*>(t);
	Debug_Null_Pointer(leaf);
	
	if (leaf->Level() > MaxLev()) return;
	if (theSubdivider(*leaf->BoundingBox(), theObject_))
	{
		const auto lev = leaf->Level();
		const auto& b = *leaf->BoundingBox();

		auto inter = new Geo3d_ApprxSpaceNode_Internal(lev);

		auto fwd_swPtr = CreateLeaf(lev + 1, b.SubDivide(Box3d_SubDivideAlgorithm_Fwd_SW));
		auto fwd_sePtr = CreateLeaf(lev + 1, b.SubDivide(Box3d_SubDivideAlgorithm_Fwd_SE));
		auto fwd_nePtr = CreateLeaf(lev + 1, b.SubDivide(Box3d_SubDivideAlgorithm_Fwd_NE));
		auto fwd_nwPtr = CreateLeaf(lev + 1, b.SubDivide(Box3d_SubDivideAlgorithm_Fwd_NW));

		auto bwd_swPtr = CreateLeaf(lev + 1, b.SubDivide(Box3d_SubDivideAlgorithm_Aft_SW));
		auto bwd_sePtr = CreateLeaf(lev + 1, b.SubDivide(Box3d_SubDivideAlgorithm_Aft_SE));
		auto bwd_nePtr = CreateLeaf(lev + 1, b.SubDivide(Box3d_SubDivideAlgorithm_Aft_NE));
		auto bwd_nwPtr = CreateLeaf(lev + 1, b.SubDivide(Box3d_SubDivideAlgorithm_Aft_NW));

		Debug_Null_Pointer(fwd_swPtr);
		Debug_Null_Pointer(fwd_sePtr);
		Debug_Null_Pointer(fwd_nePtr);
		Debug_Null_Pointer(fwd_nwPtr);

		Debug_Null_Pointer(bwd_swPtr);
		Debug_Null_Pointer(bwd_sePtr);
		Debug_Null_Pointer(bwd_nePtr);
		Debug_Null_Pointer(bwd_nwPtr);

		fwd_swPtr->FatherRef() = inter;
		fwd_sePtr->FatherRef() = inter;
		fwd_nePtr->FatherRef() = inter;
		fwd_nwPtr->FatherRef() = inter;

		bwd_swPtr->FatherRef() = inter;
		bwd_sePtr->FatherRef() = inter;
		bwd_nePtr->FatherRef() = inter;
		bwd_nwPtr->FatherRef() = inter;

		inter->FwdSwRef() = fwd_swPtr;
		inter->FwdSeRef() = fwd_sePtr;
		inter->FwdNeRef() = fwd_nePtr;
		inter->FwdNwRef() = fwd_nwPtr;

		inter->BwdSwRef() = bwd_swPtr;
		inter->BwdSeRef() = bwd_sePtr;
		inter->BwdNeRef() = bwd_nePtr;
		inter->BwdNwRef() = bwd_nwPtr;

		LinkInners(inter);

		// Remove Old Leaf from Neighbors
		RemoveLeafFromNeighbors(leaf);

		FillNeighbors(Geo3d_ApprxSpaceOctant::Fwd_Sw, leaf, inter, fwd_swPtr);
		FillNeighbors(Geo3d_ApprxSpaceOctant::Fwd_Se, leaf, inter, fwd_sePtr);
		FillNeighbors(Geo3d_ApprxSpaceOctant::Fwd_Ne, leaf, inter, fwd_nePtr);
		FillNeighbors(Geo3d_ApprxSpaceOctant::Fwd_Nw, leaf, inter, fwd_nwPtr);

		FillNeighbors(Geo3d_ApprxSpaceOctant::Bwd_Sw, leaf, inter, bwd_swPtr);
		FillNeighbors(Geo3d_ApprxSpaceOctant::Bwd_Se, leaf, inter, bwd_sePtr);
		FillNeighbors(Geo3d_ApprxSpaceOctant::Bwd_Ne, leaf, inter, bwd_nePtr);
		FillNeighbors(Geo3d_ApprxSpaceOctant::Bwd_Nw, leaf, inter, bwd_nwPtr);

		UpdateFather(leaf, inter);

		if (leaf)
		{
			delete leaf;
			leaf = 0;
		}

		t = inter;

		Subdivide(inter->FwdSwRef());
		Subdivide(inter->FwdSeRef());
		Subdivide(inter->FwdNeRef());
		Subdivide(inter->FwdNwRef());

		Subdivide(inter->BwdSwRef());
		Subdivide(inter->BwdSeRef());
		Subdivide(inter->BwdNeRef());
		Subdivide(inter->BwdNwRef());
	}
}

template<class T>
inline void tnbLib::Geo3d_ApprxSpace<T>::ForceSubdivide(Geo3d_ApprxSpaceNode *& t) const
{
	auto leaf = dynamic_cast<Geo3d_ApprxSpaceNode_Leaf*>(t);
	Debug_Null_Pointer(leaf);

	if (leaf->Level() > this->MinLev()) return;

	const auto lev = leaf->Level();
	const auto& b = *leaf->BoundingBox();

	auto inter = new Geo3d_ApprxSpaceNode_Internal(lev);

	auto fwd_swPtr = CreateLeaf(lev + 1, b.SubDivide(Box3d_SubDivideAlgorithm_Fwd_SW));
	auto fwd_sePtr = CreateLeaf(lev + 1, b.SubDivide(Box3d_SubDivideAlgorithm_Fwd_SE));
	auto fwd_nePtr = CreateLeaf(lev + 1, b.SubDivide(Box3d_SubDivideAlgorithm_Fwd_NE));
	auto fwd_nwPtr = CreateLeaf(lev + 1, b.SubDivide(Box3d_SubDivideAlgorithm_Fwd_NW));

	auto bwd_swPtr = CreateLeaf(lev + 1, b.SubDivide(Box3d_SubDivideAlgorithm_Aft_SW));
	auto bwd_sePtr = CreateLeaf(lev + 1, b.SubDivide(Box3d_SubDivideAlgorithm_Aft_SE));
	auto bwd_nePtr = CreateLeaf(lev + 1, b.SubDivide(Box3d_SubDivideAlgorithm_Aft_NE));
	auto bwd_nwPtr = CreateLeaf(lev + 1, b.SubDivide(Box3d_SubDivideAlgorithm_Aft_NW));

	Debug_Null_Pointer(fwd_swPtr);
	Debug_Null_Pointer(fwd_sePtr);
	Debug_Null_Pointer(fwd_nePtr);
	Debug_Null_Pointer(fwd_nwPtr);

	Debug_Null_Pointer(bwd_swPtr);
	Debug_Null_Pointer(bwd_sePtr);
	Debug_Null_Pointer(bwd_nePtr);
	Debug_Null_Pointer(bwd_nwPtr);

	fwd_swPtr->FatherRef() = inter;
	fwd_sePtr->FatherRef() = inter;
	fwd_nePtr->FatherRef() = inter;
	fwd_nwPtr->FatherRef() = inter;

	bwd_swPtr->FatherRef() = inter;
	bwd_sePtr->FatherRef() = inter;
	bwd_nePtr->FatherRef() = inter;
	bwd_nwPtr->FatherRef() = inter;

	inter->FwdSwRef() = fwd_swPtr;
	inter->FwdSeRef() = fwd_sePtr;
	inter->FwdNeRef() = fwd_nePtr;
	inter->FwdNwRef() = fwd_nwPtr;

	inter->BwdSwRef() = bwd_swPtr;
	inter->BwdSeRef() = bwd_sePtr;
	inter->BwdNeRef() = bwd_nePtr;
	inter->BwdNwRef() = bwd_nwPtr;

	LinkInners(inter);

	// Remove Old Leaf from Neighbors
	RemoveLeafFromNeighbors(leaf);

	FillNeighbors(Geo3d_ApprxSpaceOctant::Fwd_Sw, leaf, inter, fwd_swPtr);
	FillNeighbors(Geo3d_ApprxSpaceOctant::Fwd_Se, leaf, inter, fwd_sePtr);
	FillNeighbors(Geo3d_ApprxSpaceOctant::Fwd_Ne, leaf, inter, fwd_nePtr);
	FillNeighbors(Geo3d_ApprxSpaceOctant::Fwd_Nw, leaf, inter, fwd_nwPtr);

	FillNeighbors(Geo3d_ApprxSpaceOctant::Bwd_Sw, leaf, inter, bwd_swPtr);
	FillNeighbors(Geo3d_ApprxSpaceOctant::Bwd_Se, leaf, inter, bwd_sePtr);
	FillNeighbors(Geo3d_ApprxSpaceOctant::Bwd_Ne, leaf, inter, bwd_nePtr);
	FillNeighbors(Geo3d_ApprxSpaceOctant::Bwd_Nw, leaf, inter, bwd_nwPtr);

	UpdateFather(leaf, inter);

	if (leaf)
	{
		delete leaf;
		leaf = 0;
	}

	t = inter;

	ForceSubdivide(inter->FwdSwRef());
	ForceSubdivide(inter->FwdSeRef());
	ForceSubdivide(inter->FwdNeRef());
	ForceSubdivide(inter->FwdNwRef());

	ForceSubdivide(inter->BwdSwRef());
	ForceSubdivide(inter->BwdSeRef());
	ForceSubdivide(inter->BwdNeRef());
	ForceSubdivide(inter->BwdNwRef());
}

template<class T>
inline void tnbLib::Geo3d_ApprxSpace<T>::LinkInners(Geo3d_ApprxSpaceNode_Internal * t) const
{
	auto fwd_swPtr = dynamic_cast<Geo3d_ApprxSpaceNode_Leaf*>(t->FwdSw());
	auto fwd_sePtr = dynamic_cast<Geo3d_ApprxSpaceNode_Leaf*>(t->FwdSe());
	auto fwd_nePtr = dynamic_cast<Geo3d_ApprxSpaceNode_Leaf*>(t->FwdNe());
	auto fwd_nwPtr = dynamic_cast<Geo3d_ApprxSpaceNode_Leaf*>(t->FwdNw());

	auto bwd_swPtr = dynamic_cast<Geo3d_ApprxSpaceNode_Leaf*>(t->BwdSw());
	auto bwd_sePtr = dynamic_cast<Geo3d_ApprxSpaceNode_Leaf*>(t->BwdSe());
	auto bwd_nePtr = dynamic_cast<Geo3d_ApprxSpaceNode_Leaf*>(t->BwdNe());
	auto bwd_nwPtr = dynamic_cast<Geo3d_ApprxSpaceNode_Leaf*>(t->BwdNw());

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
inline void tnbLib::Geo3d_ApprxSpace<T>::RemoveLeafFromNeighbors(Geo3d_ApprxSpaceNode_Leaf * old) const
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
inline void tnbLib::Geo3d_ApprxSpace<T>::FillNeighbors
(
	const Geo3d_ApprxSpaceOctant o,
	Geo3d_ApprxSpaceNode_Leaf * old, 
	Geo3d_ApprxSpaceNode_Internal * father,
	Geo3d_ApprxSpaceNode_Leaf * t
) const
{
	const auto& SN = old->SNeighbors();
	const auto& EN = old->ENeighbors();
	const auto& NN = old->NNeighbors();
	const auto& WN = old->WNeighbors();
	const auto& BN = old->BNeighbors();
	const auto& FN = old->FNeighbors();

	auto fwd_swPtr = dynamic_cast<Geo3d_ApprxSpaceNode_Leaf*>(father->FwdSw());
	auto fwd_sePtr = dynamic_cast<Geo3d_ApprxSpaceNode_Leaf*>(father->FwdSe());
	auto fwd_nePtr = dynamic_cast<Geo3d_ApprxSpaceNode_Leaf*>(father->FwdNe());
	auto fwd_nwPtr = dynamic_cast<Geo3d_ApprxSpaceNode_Leaf*>(father->FwdNw());

	auto bwd_swPtr = dynamic_cast<Geo3d_ApprxSpaceNode_Leaf*>(father->BwdSw());
	auto bwd_sePtr = dynamic_cast<Geo3d_ApprxSpaceNode_Leaf*>(father->BwdSe());
	auto bwd_nePtr = dynamic_cast<Geo3d_ApprxSpaceNode_Leaf*>(father->BwdNe());
	auto bwd_nwPtr = dynamic_cast<Geo3d_ApprxSpaceNode_Leaf*>(father->BwdNw());

	Debug_Null_Pointer(fwd_swPtr);
	Debug_Null_Pointer(fwd_sePtr);
	Debug_Null_Pointer(fwd_nePtr);
	Debug_Null_Pointer(fwd_nwPtr);

	Debug_Null_Pointer(bwd_swPtr);
	Debug_Null_Pointer(bwd_sePtr);
	Debug_Null_Pointer(bwd_nePtr);
	Debug_Null_Pointer(bwd_nwPtr);

	const auto& tBox = *old->BoundingBox();
	auto c = tBox.CalcCentre();

	std::vector<Geo3d_ApprxSpaceNode_Leaf*> QSN, QEN, QNN, QWN, QFN, QBN;
	switch (o)
	{
	case Geo3d_ApprxSpaceOctant::Bwd_Sw:
	{
		if (WN.size() <= 1) for (const auto& x : WN) QWN.push_back(x);
		else
			for (const auto& x : WN)
				if (CalcOctant(x->BoundingBox()->CalcCentre(), c) IS_EQUAL Geo3d_ApprxSpaceOctant::Bwd_Sw)
					QWN.push_back(x);

		if (SN.size() <= 1) for (const auto& x : SN) QSN.push_back(x);
		else
			for (const auto& x : SN)
				if (CalcOctant(x->BoundingBox()->CalcCentre(), c) IS_EQUAL Geo3d_ApprxSpaceOctant::Bwd_Sw)
					QSN.push_back(x);

		if (BN.size() <= 1) for (const auto& x : BN) QBN.push_back(x);
		else
			for (const auto& x : BN)
				if (CalcOctant(x->BoundingBox()->CalcCentre(), c) IS_EQUAL Geo3d_ApprxSpaceOctant::Bwd_Sw)
					QBN.push_back(x);
		break;
	}
	case Geo3d_ApprxSpaceOctant::Bwd_Se:
	{
		if (SN.size() <= 1) for (const auto& x : SN) QSN.push_back(x);
		else
			for (const auto& x : SN)
				if (CalcOctant(x->BoundingBox()->CalcCentre(), c) IS_EQUAL Geo3d_ApprxSpaceOctant::Bwd_Se)
					QSN.push_back(x);

		if (EN.size() <= 1) for (const auto& x : EN) QEN.push_back(x);
		else
			for (const auto& x : EN)
				if (CalcOctant(x->BoundingBox()->CalcCentre(), c) IS_EQUAL Geo3d_ApprxSpaceOctant::Bwd_Se)
					QEN.push_back(x);

		if (BN.size() <= 1) for (const auto& x : BN) QBN.push_back(x);
		else
			for (const auto& x : BN)
				if (CalcOctant(x->BoundingBox()->CalcCentre(), c) IS_EQUAL Geo3d_ApprxSpaceOctant::Bwd_Se)
					QBN.push_back(x);
		break;
	}
	case Geo3d_ApprxSpaceOctant::Bwd_Ne:
	{
		if (EN.size() <= 1) for (const auto& x : EN) QEN.push_back(x);
		else
			for (const auto& x : EN)
				if (CalcOctant(x->BoundingBox()->CalcCentre(), c) IS_EQUAL Geo3d_ApprxSpaceOctant::Bwd_Ne)
					QEN.push_back(x);

		if (NN.size() <= 1) for (const auto& x : NN) QNN.push_back(x);
		else
			for (const auto& x : NN)
				if (CalcOctant(x->BoundingBox()->CalcCentre(), c) IS_EQUAL Geo3d_ApprxSpaceOctant::Bwd_Ne)
					QNN.push_back(x);

		if (BN.size() <= 1) for (const auto& x : BN) QBN.push_back(x);
		else
			for (const auto& x : BN)
				if (CalcOctant(x->BoundingBox()->CalcCentre(), c) IS_EQUAL Geo3d_ApprxSpaceOctant::Bwd_Ne)
					QBN.push_back(x);
		break;
	}
	case Geo3d_ApprxSpaceOctant::Bwd_Nw:
	{
		if (NN.size() <= 1) for (const auto& x : NN) QNN.push_back(x);
		else
			for (const auto& x : NN)
				if (CalcOctant(x->BoundingBox()->CalcCentre(), c) IS_EQUAL Geo3d_ApprxSpaceOctant::Bwd_Nw)
					QNN.push_back(x);

		if (WN.size() <= 1) for (const auto& x : WN) QWN.push_back(x);
		else
			for (const auto& x : WN)
				if (CalcOctant(x->BoundingBox()->CalcCentre(), c) IS_EQUAL Geo3d_ApprxSpaceOctant::Bwd_Nw)
					QWN.push_back(x);

		if (BN.size() <= 1) for (const auto& x : BN) QBN.push_back(x);
		else
			for (const auto& x : BN)
				if (CalcOctant(x->BoundingBox()->CalcCentre(), c) IS_EQUAL Geo3d_ApprxSpaceOctant::Bwd_Nw)
					QBN.push_back(x);
		break;
	}
	case Geo3d_ApprxSpaceOctant::Fwd_Sw:
	{
		if (WN.size() <= 1) for (const auto& x : WN) QWN.push_back(x);
		else
			for (const auto& x : WN)
				if (CalcOctant(x->BoundingBox()->CalcCentre(), c) IS_EQUAL Geo3d_ApprxSpaceOctant::Fwd_Sw)
					QWN.push_back(x);

		if (SN.size() <= 1) for (const auto& x : SN) QSN.push_back(x);
		else
			for (const auto& x : SN)
				if (CalcOctant(x->BoundingBox()->CalcCentre(), c) IS_EQUAL Geo3d_ApprxSpaceOctant::Fwd_Sw)
					QSN.push_back(x);

		if (FN.size() <= 1) for (const auto& x : FN) QFN.push_back(x);
		else
			for (const auto& x : FN)
				if (CalcOctant(x->BoundingBox()->CalcCentre(), c) IS_EQUAL Geo3d_ApprxSpaceOctant::Fwd_Sw)
					QFN.push_back(x);
		break;
	}
	case Geo3d_ApprxSpaceOctant::Fwd_Se:
	{
		if (SN.size() <= 1) for (const auto& x : SN) QSN.push_back(x);
		else
			for (const auto& x : SN)
				if (CalcOctant(x->BoundingBox()->CalcCentre(), c) IS_EQUAL Geo3d_ApprxSpaceOctant::Fwd_Se)
					QSN.push_back(x);

		if (EN.size() <= 1) for (const auto& x : EN) QEN.push_back(x);
		else
			for (const auto& x : EN)
				if (CalcOctant(x->BoundingBox()->CalcCentre(), c) IS_EQUAL Geo3d_ApprxSpaceOctant::Fwd_Se)
					QEN.push_back(x);

		if (FN.size() <= 1) for (const auto& x : FN) QFN.push_back(x);
		else
			for (const auto& x : FN)
				if (CalcOctant(x->BoundingBox()->CalcCentre(), c) IS_EQUAL Geo3d_ApprxSpaceOctant::Fwd_Se)
					QFN.push_back(x);
		break;
	}
	case Geo3d_ApprxSpaceOctant::Fwd_Ne:
	{
		if (EN.size() <= 1) for (const auto& x : EN) QEN.push_back(x);
		else
			for (const auto& x : EN)
				if (CalcOctant(x->BoundingBox()->CalcCentre(), c) IS_EQUAL Geo3d_ApprxSpaceOctant::Fwd_Ne)
					QEN.push_back(x);

		if (NN.size() <= 1) for (const auto& x : NN) QNN.push_back(x);
		else
			for (const auto& x : NN)
				if (CalcOctant(x->BoundingBox()->CalcCentre(), c) IS_EQUAL Geo3d_ApprxSpaceOctant::Fwd_Ne)
					QNN.push_back(x);

		if (FN.size() <= 1) for (const auto& x : FN) QFN.push_back(x);
		else
			for (const auto& x : FN)
				if (CalcOctant(x->BoundingBox()->CalcCentre(), c) IS_EQUAL Geo3d_ApprxSpaceOctant::Fwd_Ne)
					QFN.push_back(x);
		break;
	}
	case Geo3d_ApprxSpaceOctant::Fwd_Nw:
	{
		if (NN.size() <= 1) for (const auto& x : NN) QNN.push_back(x);
		else
			for (const auto& x : NN)
				if (CalcOctant(x->BoundingBox()->CalcCentre(), c) IS_EQUAL Geo3d_ApprxSpaceOctant::Fwd_Nw)
					QNN.push_back(x);

		if (WN.size() <= 1) for (const auto& x : WN) QWN.push_back(x);
		else
			for (const auto& x : WN)
				if (CalcOctant(x->BoundingBox()->CalcCentre(), c) IS_EQUAL Geo3d_ApprxSpaceOctant::Fwd_Nw)
					QWN.push_back(x);

		if (FN.size() <= 1) for (const auto& x : FN) QFN.push_back(x);
		else
			for (const auto& x : FN)
				if (CalcOctant(x->BoundingBox()->CalcCentre(), c) IS_EQUAL Geo3d_ApprxSpaceOctant::Fwd_Nw)
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
	for (const auto& x : QBN)
	{
		x->FNeighborsRef().push_back(t);
		t->BNeighborsRef().push_back(x);
	}
	for (const auto& x : QFN)
	{
		x->BNeighborsRef().push_back(t);
		t->FNeighborsRef().push_back(x);
	}
}

template<class T>
inline void tnbLib::Geo3d_ApprxSpace<T>::Balance(Geo3d_ApprxSpaceNode *& t)
{
	if (NOT t) return;
	auto leaf = dynamic_cast<Geo3d_ApprxSpaceNode_Leaf*>(t);
	if (leaf)
	{
		if (NOT IsUnbalance(leaf)) return;

		if (NOT IsBalanced()) IsBalancedRef() = Standard_True;

		auto lev = leaf->Level();
		const Entity3d_Box& b = *leaf->BoundingBox();

		auto newInternal = new Geo3d_ApprxSpaceNode_Internal(lev);

		auto fwd_swPtr = CreateLeaf(lev + 1, b.SubDivide(Box3d_SubDivideAlgorithm_Fwd_SW));
		auto fwd_sePtr = CreateLeaf(lev + 1, b.SubDivide(Box3d_SubDivideAlgorithm_Fwd_SE));
		auto fwd_nePtr = CreateLeaf(lev + 1, b.SubDivide(Box3d_SubDivideAlgorithm_Fwd_NE));
		auto fwd_nwPtr = CreateLeaf(lev + 1, b.SubDivide(Box3d_SubDivideAlgorithm_Fwd_NW));

		auto bwd_swPtr = CreateLeaf(lev + 1, b.SubDivide(Box3d_SubDivideAlgorithm_Aft_SW));
		auto bwd_sePtr = CreateLeaf(lev + 1, b.SubDivide(Box3d_SubDivideAlgorithm_Aft_SE));
		auto bwd_nePtr = CreateLeaf(lev + 1, b.SubDivide(Box3d_SubDivideAlgorithm_Aft_NE));
		auto bwd_nwPtr = CreateLeaf(lev + 1, b.SubDivide(Box3d_SubDivideAlgorithm_Aft_NW));

		Debug_Null_Pointer(fwd_swPtr);
		Debug_Null_Pointer(fwd_sePtr);
		Debug_Null_Pointer(fwd_nePtr);
		Debug_Null_Pointer(fwd_nwPtr);

		Debug_Null_Pointer(bwd_swPtr);
		Debug_Null_Pointer(bwd_sePtr);
		Debug_Null_Pointer(bwd_nePtr);
		Debug_Null_Pointer(bwd_nwPtr);

		newInternal->FwdSwRef() = fwd_swPtr;
		newInternal->FwdSeRef() = fwd_sePtr;
		newInternal->FwdNeRef() = fwd_nePtr;
		newInternal->FwdNwRef() = fwd_nwPtr;

		newInternal->BwdSwRef() = bwd_swPtr;
		newInternal->BwdSeRef() = bwd_sePtr;
		newInternal->BwdNeRef() = bwd_nePtr;
		newInternal->BwdNwRef() = bwd_nwPtr;

		LinkInners(newInternal);

		// Remove Old Leaf from Neighbors
		RemoveLeafFromNeighbors(leaf);

		FillNeighbors(Geo3d_ApprxSpaceOctant::Fwd_Sw, leaf, newInternal, fwd_swPtr);
		FillNeighbors(Geo3d_ApprxSpaceOctant::Fwd_Se, leaf, newInternal, fwd_sePtr);
		FillNeighbors(Geo3d_ApprxSpaceOctant::Fwd_Ne, leaf, newInternal, fwd_nePtr);
		FillNeighbors(Geo3d_ApprxSpaceOctant::Fwd_Nw, leaf, newInternal, fwd_nwPtr);

		FillNeighbors(Geo3d_ApprxSpaceOctant::Bwd_Sw, leaf, newInternal, bwd_swPtr);
		FillNeighbors(Geo3d_ApprxSpaceOctant::Bwd_Se, leaf, newInternal, bwd_sePtr);
		FillNeighbors(Geo3d_ApprxSpaceOctant::Bwd_Ne, leaf, newInternal, bwd_nePtr);
		FillNeighbors(Geo3d_ApprxSpaceOctant::Bwd_Nw, leaf, newInternal, bwd_nwPtr);

		if (t)
		{
			delete t;
			t = 0;
		}

		t = newInternal;

		Balance(newInternal->FwdSwRef());
		Balance(newInternal->FwdSeRef());
		Balance(newInternal->FwdNeRef());
		Balance(newInternal->FwdNwRef());

		Balance(newInternal->BwdSwRef());
		Balance(newInternal->BwdSeRef());
		Balance(newInternal->BwdNeRef());
		Balance(newInternal->BwdNwRef());
	}
	else
	{
		auto inner = dynamic_cast<Geo3d_ApprxSpaceNode_Internal*>(t);
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