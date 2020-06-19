#include <Marine_xCmpSection.hxx>

#include <Pln_Curve.hxx>
#include <Pln_Tools.hxx>
#include <Pln_Wire.hxx>
#include <Marine_Section.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <TopoDS_Edge.hxx>
#include <TopoDS_Shape.hxx>

//tnbLib::Marine_xCmpSection::Marine_xCmpSection()
//{
//}
//
//tnbLib::Marine_xCmpSection::Marine_xCmpSection
//(
//	const Standard_Integer theIndex
//)
//	: Marine_CmpSection(theIndex)
//{
//}
//
//tnbLib::Marine_xCmpSection::Marine_xCmpSection
//(
//	const Standard_Integer theIndex,
//	const word & theName
//)
//	: Marine_CmpSection(theIndex, theName)
//{
//}

std::shared_ptr<tnbLib::Marine_CmpSection>
tnbLib::Marine_xCmpSection::Copy() const
{
	auto copy = std::make_shared<Marine_xCmpSection>(Index(), Name());
	Debug_Null_Pointer(copy);

	for (const auto& x : Sections())
	{
		Debug_Null_Pointer(x);
		copy->Insert(x->Copy());
		copy->CoordinateSystem() = CoordinateSystem();
	}
	return std::move(copy);
}

//std::shared_ptr<tnbLib::Marine_CmpSection> 
//tnbLib::Marine_xCmpSection::CreateCmpSection
//(
//	const std::vector<std::shared_ptr<Pln_Curve>>& theCurves, 
//	const gp_Ax2 & theSystem,
//	const Standard_Real theMinTol,
//	const Standard_Real theMaxTol
//)
//{
//	auto wires = Pln_Tools::RetrieveWires(theCurves, theMinTol, theMaxTol);
//
//	SortWires(wires);
//
//	Standard_Integer K = 0;
//	for (const auto& x : wires)
//	{
//		Debug_Null_Pointer(x);
//		x->SetIndex(++K);
//	}
//
//	std::list<std::shared_ptr<Pln_Wire>> wireList;
//	for (const auto& x : wires)
//	{
//		Debug_Null_Pointer(x);
//		wireList.push_back(x);
//	}
//
//	K = 0;
//	auto cmpSection = std::make_shared<Marine_xCmpSection>();
//	Debug_Null_Pointer(cmpSection);
//
//	cmpSection->SetCoordinateSystem(theSystem);
//
//	auto& sections = cmpSection->ChangeSections();
//	while (NOT wireList.empty())
//	{
//		std::shared_ptr<Pln_Wire> outer;
//		auto inners = std::make_shared<std::vector<std::shared_ptr<Pln_Wire>>>();
//		Debug_Null_Pointer(inners);
//
//		RetrieveInnerOuterWires(wireList, outer, *inners);
//
//		if (NOT outer)
//		{
//			FatalErrorIn("std::shared_ptr<tnbLib::Marine_CmpSection> Marine_CmpSection::CreateCmpSection(Args...)")
//				<< "Invalid section" << endl
//				<< abort(FatalError);
//		}
//
//		if (outer->Orientation() NOT_EQUAL Pln_Orientation::Pln_Orientation_CCW)
//		{
//			outer->ApplyOrientation(Pln_Orientation::Pln_Orientation_CCW);
//		}
//
//		if (inners->empty())
//		{
//			auto section = std::make_shared<Marine_Section>(++K, outer);
//			Debug_Null_Pointer(section);
//
//			sections.push_back(std::move(section));
//		}
//		else
//		{
//			FatalErrorIn("std::shared_ptr<tnbLib::Marine_CmpSection> Marine_CmpSection::CreateCmpSection(Args...)")
//				<< "the section shouldn't contain any inner wire" << endl
//				<< abort(FatalError);
//
//			/*for (const auto& x : *inners)
//			{
//				Debug_Null_Pointer(x);
//				if (x->Orientation() NOT_EQUAL Pln_Orientation::Pln_Orientation_CW)
//				{
//					x->ApplyOrientation(Pln_Orientation::Pln_Orientation_CW);
//				}
//			}
//
//			auto section = std::make_shared<Marine_Section>(++K, outer, inners);
//			Debug_Null_Pointer(section);
//
//			sections.push_back(std::move(section));*/
//		}
//	}
//
//	return std::move(cmpSection);
//}

//std::shared_ptr<tnbLib::Marine_CmpSection> 
//tnbLib::Marine_xCmpSection::CreateCmpSection
//(
//	const std::vector<Handle(Geom2d_Curve)>& theCurves,
//	const gp_Ax2 & theSystem, 
//	const Standard_Real theMinTol, 
//	const Standard_Real theMaxTol
//)
//{
//	std::vector<std::shared_ptr<Pln_Curve>> curves;
//	curves.reserve(theCurves.size());
//
//	Standard_Integer K = 0;
//	for (const auto& x : theCurves)
//	{
//		Debug_Null_Pointer(x);
//
//		if (NOT Pln_Tools::IsBounded(x))
//		{
//			FatalErrorIn("std::shared_ptr<Marine_CmpSection> Marine_CmpSection::CreateCmpSection(Args....)")
//				<< "the curve is not bounded" << endl
//				<< abort(FatalError);
//		}
//
//		curves.push_back(std::make_shared<Pln_Curve>(++K, x));
//	}
//
//	auto section = CreateCmpSection(curves, theSystem, theMinTol, theMaxTol);
//	return std::move(section);
//}

//std::shared_ptr<tnbLib::Marine_CmpSection> 
//tnbLib::Marine_xCmpSection::CreateCmpSection
//(
//	const TopoDS_Shape & theEdges, 
//	const gp_Ax2 & theSystem, 
//	const Standard_Real theMinTol,
//	const Standard_Real theMaxTol
//)
//{
//	auto edges = RetrieveEdges(theEdges);
//	auto curves = RetrieveParaCurves(edges, theSystem);
//
//	auto cmpSection =
//		CreateCmpSection(curves, theSystem, theMinTol, theMaxTol);
//
//	return std::move(cmpSection);
//}