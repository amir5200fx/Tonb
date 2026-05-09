#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
template<class T>
inline Standard_Boolean tnbLib::Geo2d_ApprxSpace<T>::IsUnbalance
(
	const Geo2d_ApprxSpaceNode_Leaf * leaf
) const
{
	if (leaf->SNeighbors().size() > theMaxUnbalancing_) return Standard_True;
	if (leaf->ENeighbors().size() > theMaxUnbalancing_) return Standard_True;
	if (leaf->NNeighbors().size() > theMaxUnbalancing_) return Standard_True;
	if (leaf->WNeighbors().size() > theMaxUnbalancing_) return Standard_True;
	return Standard_False;
}

template<class T>
inline void tnbLib::Geo2d_ApprxSpace<T>::Subdivide(Geo2d_ApprxSpaceNode *& t) const
{
	auto leaf = dynamic_cast<Geo2d_ApprxSpaceNode_Leaf*>(t);
	Debug_Null_Pointer(leaf);

	if (leaf->Level() > theMaxLevel_) return;

	if (theSubdivider(leaf->Box(), theObject_))
	{
		const auto lev = leaf->Level();
		const auto& b = leaf->Box();

		auto inter = new Geo2d_ApprxSpaceNode_Internal(lev);

		auto swPtr = CreateLeaf(lev + 1, b.SubDivide(Box2d_SubDivideAlgorithm_Quad_SW));
		auto sePtr = CreateLeaf(lev + 1, b.SubDivide(Box2d_SubDivideAlgorithm_Quad_SE));
		auto nePtr = CreateLeaf(lev + 1, b.SubDivide(Box2d_SubDivideAlgorithm_Quad_NE));
		auto nwPtr = CreateLeaf(lev + 1, b.SubDivide(Box2d_SubDivideAlgorithm_Quad_NW));

		Debug_Null_Pointer(swPtr);
		Debug_Null_Pointer(sePtr);
		Debug_Null_Pointer(nePtr);
		Debug_Null_Pointer(nwPtr);

		swPtr->FatherRef() = inter;
		sePtr->FatherRef() = inter;
		nePtr->FatherRef() = inter;
		nwPtr->FatherRef() = inter;

		inter->SwRef() = swPtr;
		inter->SeRef() = sePtr;
		inter->NeRef() = nePtr;
		inter->NwRef() = nwPtr;

		InnerLinks(inter);

		// Remove Old Leaf from Neighbors
		RemoveLeafFromNeighbors(leaf);

		FillNeighbors(Geo2d_ApprxSpaceQuadrant::Sw, leaf, inter, swPtr);
		FillNeighbors(Geo2d_ApprxSpaceQuadrant::Se, leaf, inter, sePtr);
		FillNeighbors(Geo2d_ApprxSpaceQuadrant::Ne, leaf, inter, nePtr);
		FillNeighbors(Geo2d_ApprxSpaceQuadrant::Nw, leaf, inter, nwPtr);

		UpdateFather(leaf, inter);

		if (leaf)
		{
			delete leaf;
			leaf = 0;
		}

		t = inter;

		Subdivide(inter->SwRef());
		Subdivide(inter->SeRef());
		Subdivide(inter->NeRef());
		Subdivide(inter->NwRef());
	}
}

template<class T>
inline void tnbLib::Geo2d_ApprxSpace<T>::ForcedSubdivide(Geo2d_ApprxSpaceNode *& t) const
{
	auto leaf = dynamic_cast<Geo2d_ApprxSpaceNode_Leaf*>(t);
	Debug_Null_Pointer(leaf);

	if (leaf->Level() > theMinLevel_) return;

	const auto lev = leaf->Level();
	const auto& b = leaf->Box();

	auto inter = new Geo2d_ApprxSpaceNode_Internal(lev);

	auto swPtr = CreateLeaf(lev + 1, b.SubDivide(Box2d_SubDivideAlgorithm_Quad_SW));
	auto sePtr = CreateLeaf(lev + 1, b.SubDivide(Box2d_SubDivideAlgorithm_Quad_SE));
	auto nePtr = CreateLeaf(lev + 1, b.SubDivide(Box2d_SubDivideAlgorithm_Quad_NE));
	auto nwPtr = CreateLeaf(lev + 1, b.SubDivide(Box2d_SubDivideAlgorithm_Quad_NW));

	Debug_Null_Pointer(swPtr);
	Debug_Null_Pointer(sePtr);
	Debug_Null_Pointer(nePtr);
	Debug_Null_Pointer(nwPtr);

	swPtr->FatherRef() = inter;
	sePtr->FatherRef() = inter;
	nePtr->FatherRef() = inter;
	nwPtr->FatherRef() = inter;

	inter->SwRef() = swPtr;
	inter->SeRef() = sePtr;
	inter->NeRef() = nePtr;
	inter->NwRef() = nwPtr;

	InnerLinks(inter);

	// Remove Old Leaf from Neighbors
	RemoveLeafFromNeighbors(leaf);

	FillNeighbors(Geo2d_ApprxSpaceQuadrant::Sw, leaf, inter, swPtr);
	FillNeighbors(Geo2d_ApprxSpaceQuadrant::Se, leaf, inter, sePtr);
	FillNeighbors(Geo2d_ApprxSpaceQuadrant::Ne, leaf, inter, nePtr);
	FillNeighbors(Geo2d_ApprxSpaceQuadrant::Nw, leaf, inter, nwPtr);

	UpdateFather(leaf, inter);

	if (leaf)
	{
		delete leaf;
		leaf = 0;
	}

	t = inter;

	ForcedSubdivide(inter->SwRef());
	ForcedSubdivide(inter->SeRef());
	ForcedSubdivide(inter->NeRef());
	ForcedSubdivide(inter->NwRef());
}

template<class T>
inline void tnbLib::Geo2d_ApprxSpace<T>::InnerLinks(Geo2d_ApprxSpaceNode_Internal * t) const
{
	auto swPtr = dynamic_cast<Geo2d_ApprxSpaceNode_Leaf*>(t->Sw());
	auto sePtr = dynamic_cast<Geo2d_ApprxSpaceNode_Leaf*>(t->Se());
	auto nePtr = dynamic_cast<Geo2d_ApprxSpaceNode_Leaf*>(t->Ne());
	auto nwPtr = dynamic_cast<Geo2d_ApprxSpaceNode_Leaf*>(t->Nw());

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
inline void tnbLib::Geo2d_ApprxSpace<T>::RemoveLeafFromNeighbors(Geo2d_ApprxSpaceNode_Leaf * old) const
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
inline void tnbLib::Geo2d_ApprxSpace<T>::FillNeighbors
(
	const Geo2d_ApprxSpaceQuadrant q, 
	Geo2d_ApprxSpaceNode_Leaf * old,
	Geo2d_ApprxSpaceNode_Internal * father, 
	Geo2d_ApprxSpaceNode_Leaf * t
) const
{
	auto swPtr = dynamic_cast<Geo2d_ApprxSpaceNode_Leaf*>(father->Sw());
	auto sePtr = dynamic_cast<Geo2d_ApprxSpaceNode_Leaf*>(father->Se());
	auto nePtr = dynamic_cast<Geo2d_ApprxSpaceNode_Leaf*>(father->Ne());
	auto nwPtr = dynamic_cast<Geo2d_ApprxSpaceNode_Leaf*>(father->Nw());

	Debug_Null_Pointer(swPtr);
	Debug_Null_Pointer(sePtr);
	Debug_Null_Pointer(nePtr);
	Debug_Null_Pointer(nwPtr);

	const auto& tBox = old->Box();
	const auto c = tBox.CalcCentre();

	const auto& SN = old->SNeighbors();
	const auto& EN = old->ENeighbors();
	const auto& NN = old->NNeighbors();
	const auto& WN = old->WNeighbors();

	std::vector<Geo2d_ApprxSpaceNode_Leaf*> QSN, QEN, QNN, QWN;

	switch (q)
	{
	case Geo2d_ApprxSpaceQuadrant::Sw:
	{
		if (WN.size() <= 1) for (const auto& x : WN) QWN.push_back(x);
		else 
			for (const auto& x : WN) 
				if (CalcQuadrant(x->Box().CalcCentre(), c) IS_EQUAL Geo2d_ApprxSpaceQuadrant::Sw) 
					QWN.push_back(x);

		if (SN.size() <= 1) for (const auto& x : SN) QSN.push_back(x);
		else
			for (const auto& x : SN)
				if (CalcQuadrant(x->Box().CalcCentre(), c) IS_EQUAL Geo2d_ApprxSpaceQuadrant::Sw)
					QSN.push_back(x);
		break;
	}
	case Geo2d_ApprxSpaceQuadrant::Se:
	{
		if (SN.size() <= 1) for (const auto& x : SN) QSN.push_back(x);
		else
			for (const auto& x : SN)
				if (CalcQuadrant(x->Box().CalcCentre(), c) IS_EQUAL Geo2d_ApprxSpaceQuadrant::Se)
					QSN.push_back(x);

		if (EN.size() <= 1) for (const auto& x : EN) QEN.push_back(x);
		else
			for (const auto& x : EN)
				if (CalcQuadrant(x->Box().CalcCentre(), c) IS_EQUAL Geo2d_ApprxSpaceQuadrant::Se)
					QEN.push_back(x);
		break;
	}
	case Geo2d_ApprxSpaceQuadrant::Ne:
	{
		if (EN.size() <= 1) for (const auto& x : EN) QEN.push_back(x);
		else
			for (const auto& x : EN)
				if (CalcQuadrant(x->Box().CalcCentre(), c) IS_EQUAL Geo2d_ApprxSpaceQuadrant::Ne)
					QEN.push_back(x);

		if (NN.size() <= 1) for (const auto& x : NN) QNN.push_back(x);
		else
			for (const auto& x : NN)
				if (CalcQuadrant(x->Box().CalcCentre(), c) IS_EQUAL Geo2d_ApprxSpaceQuadrant::Ne)
					QNN.push_back(x);
		break;
	}
	case Geo2d_ApprxSpaceQuadrant::Nw:
	{
		if (NN.size() <= 1) for (const auto& x : NN) QNN.push_back(x);
		else
			for (const auto& x : NN)
				if (CalcQuadrant(x->Box().CalcCentre(), c) IS_EQUAL Geo2d_ApprxSpaceQuadrant::Nw)
					QNN.push_back(x);

		if (WN.size() <= 1) for (const auto& x : WN) QWN.push_back(x);
		else
			for (const auto& x : WN)
				if (CalcQuadrant(x->Box().CalcCentre(), c) IS_EQUAL Geo2d_ApprxSpaceQuadrant::Nw)
					QWN.push_back(x);
		break;
	}
	default:
		FatalErrorIn(FunctionSIG)
			<< "unidentified case has been detected!" << endl
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
inline void tnbLib::Geo2d_ApprxSpace<T>::Balance(Geo2d_ApprxSpaceNode *& t)
{
	if (NOT t) return;

	auto leaf = dynamic_cast<Geo2d_ApprxSpaceNode_Leaf*>(t);
	if (leaf)
	{
		if (NOT IsUnbalance(leaf)) return;

		if (NOT IsBalanced_) IsBalanced_ = Standard_True;

		auto lev = leaf->Level();
		const Entity2d_Box& b = leaf->Box();

		auto newInternal = new Geo2d_ApprxSpaceNode_Internal(lev);

		auto swPtr = CreateLeaf(lev + 1, b.SubDivide(Box2d_SubDivideAlgorithm_Quad_SW));
		auto sePtr = CreateLeaf(lev + 1, b.SubDivide(Box2d_SubDivideAlgorithm_Quad_SE));
		auto nePtr = CreateLeaf(lev + 1, b.SubDivide(Box2d_SubDivideAlgorithm_Quad_NE));
		auto nwPtr = CreateLeaf(lev + 1, b.SubDivide(Box2d_SubDivideAlgorithm_Quad_NW));

		Debug_Null_Pointer(swPtr);
		Debug_Null_Pointer(sePtr);
		Debug_Null_Pointer(nePtr);
		Debug_Null_Pointer(nwPtr);

		newInternal->SwRef() = swPtr;
		newInternal->SeRef() = sePtr;
		newInternal->NeRef() = nePtr;
		newInternal->NwRef() = nwPtr;

		InnerLinks(newInternal);

		// Remove Old Leaf from Neighbors
		RemoveLeafFromNeighbors(leaf);

		FillNeighbors(Geo2d_ApprxSpaceQuadrant::Sw, leaf, newInternal, swPtr);
		FillNeighbors(Geo2d_ApprxSpaceQuadrant::Se, leaf, newInternal, sePtr);
		FillNeighbors(Geo2d_ApprxSpaceQuadrant::Ne, leaf, newInternal, nePtr);
		FillNeighbors(Geo2d_ApprxSpaceQuadrant::Nw, leaf, newInternal, nwPtr);

		if (t)
		{
			delete t;
			t = 0;
		}

		t = newInternal;

		Balance(newInternal->SwRef());
		Balance(newInternal->SeRef());
		Balance(newInternal->NeRef());
		Balance(newInternal->NwRef());
	}
	else
	{
		auto newInternal = dynamic_cast<Geo2d_ApprxSpaceNode_Internal*>(t);
		Debug_Null_Pointer(newInternal);

		Balance(newInternal->SwRef());
		Balance(newInternal->SeRef());
		Balance(newInternal->NeRef());
		Balance(newInternal->NwRef());
	}
}

template<class T>
inline void tnbLib::Geo2d_ApprxSpace<T>::RetrieveTo
(
	Geo2d_ApprxSpaceNode * t,
	std::vector<Geo2d_ApprxSpaceNode*>& nodes
) const
{
	if (NOT t) return;
	auto leaf = dynamic_cast<Geo2d_ApprxSpaceNode_Leaf*>(t);
	if (leaf)
	{
		nodes.push_back(t);
	}
	else
	{
		auto inter = dynamic_cast<Geo2d_ApprxSpaceNode_Internal*>(t);
		Debug_Null_Pointer(inter);

		RetrieveTo(inter->Sw(), nodes);
		RetrieveTo(inter->Se(), nodes);
		RetrieveTo(inter->Ne(), nodes);
		RetrieveTo(inter->Nw(), nodes);
	}
}

template<class T>
inline void tnbLib::Geo2d_ApprxSpace<T>::RetrieveTo
(
	Geo2d_ApprxSpaceNode * t,
	std::vector<Entity2d_Box>& boxes
) const
{
	if (NOT t) return;
	auto leaf = dynamic_cast<Geo2d_ApprxSpaceNode_Leaf*>(t);
	if (leaf)
	{
		boxes.push_back(leaf->Box());
	}
	else
	{
		auto inter = dynamic_cast<Geo2d_ApprxSpaceNode_Internal*>(t);
		Debug_Null_Pointer(inter);

		RetrieveTo(inter->Sw(), boxes);
		RetrieveTo(inter->Se(), boxes);
		RetrieveTo(inter->Ne(), boxes);
		RetrieveTo(inter->Nw(), boxes);
	}
}

template<class T>
inline void tnbLib::Geo2d_ApprxSpace<T>::Clear(Geo2d_ApprxSpaceNode *& t)
{
	auto leaf = dynamic_cast<Geo2d_ApprxSpaceNode_Leaf*>(t);
	if (leaf)
	{
		delete leaf;
		leaf = 0;
	}
	else
	{
		auto inter = dynamic_cast<Geo2d_ApprxSpaceNode_Internal*>(t);
		Debug_Null_Pointer(inter);

		if (inter->Sw()) Clear(inter->SwRef());
		if (inter->Se()) Clear(inter->SeRef());
		if (inter->Ne()) Clear(inter->NeRef());
		if (inter->Nw()) Clear(inter->NwRef());

		delete inter;
		inter = 0;
	}
}

template<class T>
inline tnbLib::Geo2d_ApprxSpaceNode_Leaf * 
tnbLib::Geo2d_ApprxSpace<T>::CreateLeaf
(
	const Standard_Integer theLev,
	const Entity2d_Box & b
)
{
	return new Geo2d_ApprxSpaceNode_Leaf(theLev, b);
}

template<class T>
inline void tnbLib::Geo2d_ApprxSpace<T>::UpdateFather
(
	Geo2d_ApprxSpaceNode_Leaf * node, 
	Geo2d_ApprxSpaceNode * inter
)
{
	if (NOT node->Father()) return;
	auto father = dynamic_cast<Geo2d_ApprxSpaceNode_Internal*>(node->Father());
	Debug_Null_Pointer(father);

	if (father->Sw() IS_EQUAL node) father->SwRef() = inter;
	else if (father->Se() IS_EQUAL node) father->SeRef() = inter;
	else if (father->Ne() IS_EQUAL node) father->NeRef() = inter;
	else if (father->Nw() IS_EQUAL node) father->NwRef() = inter;
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "Unexpected error has been detected!" << endl
			<< abort(FatalError);
	}
}

template<class T>
inline tnbLib::Geo2d_ApprxSpace<T>::~Geo2d_ApprxSpace()
{
	Clear(theRoot_);
}

template<class T>
inline void tnbLib::Geo2d_ApprxSpace<T>::SetDomain
(
	const Entity2d_Box & domain
)
{
	theDomain_ = domain;
}

template<class T>
inline void tnbLib::Geo2d_ApprxSpace<T>::SetObject(const T * obj)
{
	theObject_ = obj;
}

template<class T>
inline void tnbLib::Geo2d_ApprxSpace<T>::SetSubdivider
(
	Standard_Boolean(*fun)(const Entity2d_Box &, const T *)
)
{
	theSubdivider = fun;
}

template<class T>
inline void tnbLib::Geo2d_ApprxSpace<T>::SetMaxLevel(const Standard_Integer lev)
{
	theMaxLevel_ = lev;
}

template<class T>
inline void tnbLib::Geo2d_ApprxSpace<T>::SetMinLevel(const Standard_Integer lev)
{
	theMinLevel_ = lev;
}

template<class T>
inline void tnbLib::Geo2d_ApprxSpace<T>::SetMaxUnbalancingLevel(const Standard_Integer lev)
{
	theMaxUnbalancing_ = lev;
}

template<class T>
inline void tnbLib::Geo2d_ApprxSpace<T>::Init()
{
	theRoot_ = CreateLeaf(0, theDomain_);
	ForcedSubdivide(theRoot_);
}

template<class T>
inline void tnbLib::Geo2d_ApprxSpace<T>::Perform()
{
	if (NOT theSubdivider)
	{
		FatalErrorIn(FunctionSIG)
			<< "no subdivide function has been detected!" << endl
			<< abort(FatalError);
	}

	auto nodes = RetrieveNodes();
	for (auto& x : nodes)
	{
		Subdivide(x);
	}
}

template<class T>
inline void tnbLib::Geo2d_ApprxSpace<T>::Perform
(
	std::vector<Geo2d_ApprxSpaceNode*>& nodes
)
{
	if (NOT theSubdivider)
	{
		FatalErrorIn(FunctionSIG)
			<< "no subdivide function has been detected!" << endl
			<< abort(FatalError);
	}
	for (auto& x : nodes)
	{
		Subdivide(x);
	}
}

template<class T>
inline void tnbLib::Geo2d_ApprxSpace<T>::PostBalance()
{
	while (true)
	{
		IsBalanced_ = Standard_False;
		Balance(theRoot_);
		if (NOT IsBalanced_) break;
	}
}

template<class T>
inline void tnbLib::Geo2d_ApprxSpace<T>::Clear()
{
	Clear(theRoot_);
}

template<class T>
inline std::vector<tnbLib::Geo2d_ApprxSpaceNode*> 
tnbLib::Geo2d_ApprxSpace<T>::RetrieveNodes() const
{
	std::vector<Geo2d_ApprxSpaceNode*> nodes;
	RetrieveNodesTo(nodes);
	return std::move(nodes);
}

template<class T>
inline std::vector<tnbLib::Entity2d_Box> 
tnbLib::Geo2d_ApprxSpace<T>::RetrieveBoxes() const
{
	std::vector<Entity2d_Box> boxes;
	RetrieveBoxesTo(boxes);
	return std::move(boxes);
}

template<class T>
inline void tnbLib::Geo2d_ApprxSpace<T>::RetrieveNodesTo
(
	std::vector<Geo2d_ApprxSpaceNode*>& nodes
) const
{
	RetrieveTo(theRoot_, nodes);
}

template<class T>
inline void tnbLib::Geo2d_ApprxSpace<T>::RetrieveBoxesTo
(
	std::vector<Entity2d_Box>& boxes
) const
{
	RetrieveTo(theRoot_, boxes);
}

template<class T>
inline tnbLib::Geo2d_ApprxSpaceQuadrant 
tnbLib::Geo2d_ApprxSpace<T>::CalcQuadrant
(
	const Pnt2d & p, 
	const Pnt2d & centre
)
{
	if (p.X() <= centre.X())
	{
		if (p.Y() <= centre.Y())
		{
			return Geo2d_ApprxSpaceQuadrant::Sw;
		}
		else
		{
			return Geo2d_ApprxSpaceQuadrant::Nw;
		}
	}
	else
	{
		if (p.Y() <= centre.Y())
		{
			return Geo2d_ApprxSpaceQuadrant::Se;
		}
		else
		{
			return Geo2d_ApprxSpaceQuadrant::Ne;
		}
	}
}