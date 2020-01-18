#include <Entity2d_TriangulationN.hxx>

#include <error.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static inline Standard_Integer FindNeighborIndex
	(
		const connectivity::triple& theNeighb, 
		const Standard_Integer theE
	)
	{
		if (theNeighb.Value(0) IS_EQUAL theE) return 0;
		if (theNeighb.Value(1) IS_EQUAL theE) return 1;
		if (theNeighb.Value(2) IS_EQUAL theE) return 2;

		FatalErrorIn("Standard_Integer FindNeighborIndex(const connectivity::triple& theNeighb, const Standard_Integer theE)")
			<< "Invalid Data" << endl
			<< abort(FatalError);
		return 0;
	}

	static void Swap
	(
		std::vector<connectivity::triple>& Vtx, 
		std::vector<connectivity::triple>& Neighb, 
		const Standard_Integer E0, 
		const Standard_Integer theIndex
	)
	{
		SwapBox vb, nb;
		vb.V1 = Vtx[E0].Value(theIndex);
		vb.V2 = Vtx[E0].Value((theIndex + 1) % 3);
		vb.V0 = Vtx[E0].Value((theIndex + 2) % 3);

		nb.V0 = Neighb[E0].Value((theIndex + 1) % 3);
		nb.V1 = Neighb[E0].Value((theIndex + 2) % 3);

		auto E1 = Neighb[E0].Value(theIndex);
		auto nbIndex = FindNeighborIndex(Neighb[E1], E0);

		nb.V2 = Neighb[E1].Value((nbIndex + 1) % 3);
		nb.V3 = Neighb[E1].Value((nbIndex + 2) % 3);

		vb.V3 = Vtx[E1].Value(nbIndex);

		Vtx[E0].Value(0) = vb.V1;
		Vtx[E0].Value(1) = vb.V2;
		Vtx[E0].Value(2) = vb.V3;

		Vtx[E1].Value(0) = vb.V3;
		Vtx[E1].Value(1) = vb.V0;
		Vtx[E1].Value(2) = vb.V1;

		Neighb[E0].Value(0) = nb.V2;
		Neighb[E0].Value(1) = E1;
		Neighb[E0].Value(2) = nb.V1;

		Neighb[E1].Value(0) = nb.V0;
		Neighb[E1].Value(1) = E0;
		Neighb[E1].Value(2) = nb.V3;
	}
}

tnbLib::SwapBox
tnbLib::SwapBox::GetSwapBox
(
	const std::vector<connectivity::triple>& Vtx,
	const std::vector<connectivity::triple>& Neighb,
	const Standard_Integer E0,
	const Standard_Integer theIndex
)
{
	SwapBox vb;
	vb.V1 = Vtx[E0].Value(theIndex);
	vb.V2 = Vtx[E0].Value((theIndex + 1) % 3);
	vb.V0 = Vtx[E0].Value((theIndex + 2) % 3);

	auto E1 = Neighb[E0].Value(theIndex);
	auto nbIndex = FindNeighborIndex(Neighb[E1], E0);

	vb.V3 = Vtx[E1].Value(nbIndex);
	return std::move(vb);
}

template<>
void tnbLib::Entity2d_TriangulationN::Swap
(
	const Standard_Integer theElement,
	const Standard_Integer theEdge
)
{
	auto& Neighb = Neighbors();
	auto& Vtx = Connectivity();

	tnbLib::Swap(Vtx, Neighb, theElement, theEdge);
}