#include <SectPx_ProfileQ.hxx>

#include <Pnt2d.hxx>
#include <SectPx_Pnt.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::vector<tnbLib::Pnt2d> 
tnbLib::SectPx_ProfileQ::RetrievePnts() const
{
	std::vector<Pnt2d> Q;
	Q.reserve(NbQ());

	for (const auto& x : theQ_)
	{
		Debug_Null_Pointer(x);
		Q.push_back(x->Coord());
	}
	return std::move(Q);
}