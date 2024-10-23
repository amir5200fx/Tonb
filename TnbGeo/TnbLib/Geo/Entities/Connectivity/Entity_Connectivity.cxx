#include <Entity_Connectivity.hxx>

template<>
Standard_Boolean tnbLib::connectivity::quadruple::IsDegenerated() const
{
	if (Value(0) == Value(1)) return Standard_True;
	if (Value(0) == Value(2)) return Standard_True;
	if (Value(0) == Value(3)) return Standard_True;
	if (Value(1) == Value(2)) return Standard_True;
	if (Value(2) == Value(3)) return Standard_True;
	return Standard_False;
}

template<>
Standard_Boolean tnbLib::connectivity::quadruple_3d::IsDegenerated() const
{
	if (Value(0) == Value(1)) return Standard_True;
	if (Value(0) == Value(2)) return Standard_True;
	if (Value(0) == Value(3)) return Standard_True;
	if (Value(1) == Value(2)) return Standard_True;
	if (Value(2) == Value(3)) return Standard_True;
	return Standard_False;
}

template <>
Standard_Boolean tnbLib::connectivity::octuple::IsDegenerated() const
{
	NotImplemented
	return Standard_True;
}

std::vector<tnbLib::connectivity::dual>
tnbLib::dualConnectivityList
(
	const Standard_Integer theNbEdges
)
{
	std::vector<connectivity::dual> Edges(theNbEdges);
	Standard_Integer k = 0;
	for (auto& x : Edges)
	{
		x.Value(0) = k * 2 + 1;
		x.Value(1) = k * 2 + 2;

		++k;
	}
	return Edges;
}

std::vector<tnbLib::connectivity::dual>
tnbLib::dualConnectivityList_Chain
(
	const Standard_Integer theNbEdges,
	const Standard_Boolean IsClosed
)
{
	std::vector<connectivity::dual> Edges(theNbEdges);
	Standard_Integer k = 0;
	for (auto& x : Edges)
	{
		x.Value(0) = k + 1;
		x.Value(1) = k + 2;

		++k;
	}

	if (IsClosed)
	{
		Edges[Edges.size() - 1].Value(1) = 1;
	}

	return Edges;
}

tnbLib::connectivity::triple tnbLib::rise(const connectivity::dual& dual)
{
	return { { dual.Value(0), dual.Value(1), dual.Value(0) } };
}

tnbLib::connectivity::quadruple tnbLib::rise(const connectivity::triple& t)
{
	return { {t.Value(0), t.Value(1), t.Value(2), t.Value(0)} };
}

tnbLib::connectivity::octuple tnbLib::rise(const connectivity::sextuple& s)
{
	return { {s.Value(0), s.Value(1), s.Value(2), s.Value(2), s.Value(3), s.Value(4), s.Value(5), s.Value(5)} };
}
