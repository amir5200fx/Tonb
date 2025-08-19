#include <Aft3d_Element.hxx>

#include <Aft3d_Node.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::Pnt3d 
tnbLib::legLib::Aft3d_Element::CalcCentre() const
{
	const auto& n0 = Node0();
	const auto& n1 = Node1();
	const auto& n2 = Node2();
	const auto& n3 = Node3();
	Debug_Null_Pointer(n0);
	Debug_Null_Pointer(n1);
	Debug_Null_Pointer(n2);
	Debug_Null_Pointer(n3);

	const auto& p0 = n0->Coord();
	const auto& p1 = n1->Coord();
	const auto& p2 = n2->Coord();
	const auto& p3 = n3->Coord();
	auto pt = (p0 + p1 + p2 + p3) * 0.25;
	return std::move(pt);
}