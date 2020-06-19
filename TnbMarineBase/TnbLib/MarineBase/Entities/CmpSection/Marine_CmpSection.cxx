#include <Marine_CmpSection.hxx>

#include <Geo_ItemSort.hxx>
#include <Entity2d_Box.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Wire.hxx>
#include <Pln_Tools.hxx>
#include <Marine_Section.hxx>
#include <Marine_SectTools.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <map>

void tnbLib::Marine_CmpSection::Insert(const std::shared_ptr<Marine_Section>& theSection)
{
	if (NOT Marine_SectTools::IsOuter(theSection))
	{
		FatalErrorIn
		(
			"void Marine_CmpSection::Insert(const std::shared_ptr<Marine_Section>& theSection)"
		)
			<< "the section is not outer!" << endl
			<< abort(FatalError);
	}
	theSections_.push_back(theSection);
}

tnbLib::Marine_CmpSection::Marine_CmpSection()
{
}

tnbLib::Marine_CmpSection::Marine_CmpSection
(
	const Standard_Integer theIndex
)
	: Marine_Entity(theIndex)
{
}

tnbLib::Marine_CmpSection::Marine_CmpSection
(
	const Standard_Integer theIndex,
	const word & theName
)
	: Marine_Entity(theIndex, theName)
{
}

tnbLib::Marine_CmpSection::Marine_CmpSection
(
	const std::shared_ptr<Marine_Section>& theSection
)
{
	Insert(theSection);
}

tnbLib::Marine_CmpSection::Marine_CmpSection
(
	const Standard_Integer theIndex,
	const std::shared_ptr<Marine_Section>& theSection
)
	: Marine_Entity(theIndex)
{
	Insert(theSection);
}

tnbLib::Marine_CmpSection::Marine_CmpSection
(
	const Standard_Integer theIndex,
	const word & theName, 
	const std::shared_ptr<Marine_Section>& theSection
)
	: Marine_Entity(theIndex, theName)
{
	Insert(theSection);
}

tnbLib::Entity2d_Box 
tnbLib::Marine_CmpSection::BoundingBox() const
{
	auto iter = Sections().begin();
	auto b = (*iter)->BoundingBox();

	iter++;
	while (iter NOT_EQUAL Sections().end())
	{
		b = Entity2d_Box::Union(b, (*iter)->BoundingBox());
		iter++;
	}
	return std::move(b);
}

tnbLib::Marine_SectionType 
tnbLib::Marine_CmpSection::Type() const
{
	const auto& sections = Sections();
	Debug_If_Condition(sections.empty());

	auto iter = sections.cbegin();
	return (*iter)->Type();
}

Standard_Real 
tnbLib::Marine_CmpSection::X() const
{
	return CoordinateSystem().Location().X();
}

void tnbLib::Marine_CmpSection::Transform
(
	const gp_Trsf2d & t
)
{
	for (const auto& x : Sections())
	{
		Debug_Null_Pointer(x);
		x->Transform(t);
	}
}

void tnbLib::Marine_CmpSection::ExportToPlt
(
	OFstream & File
) const
{
	for (const auto& x : Sections())
	{
		Debug_Null_Pointer(x);
		x->ExportToPlt(File);
	}
}

Standard_Boolean 
tnbLib::Marine_CmpSection::LessDiameterSize
(
	const std::shared_ptr<Pln_Wire>& theWire0,
	const std::shared_ptr<Pln_Wire>& theWire1
)
{
	Debug_Null_Pointer(theWire0);
	Debug_Null_Pointer(theWire1);

	const auto b0 = theWire0->BoundingBox(0);
	const auto b1 = theWire1->BoundingBox(0);

	return -b0.SquareDiameter() < -b1.SquareDiameter();
}

void tnbLib::Marine_CmpSection::SortWires
(
	std::vector<std::shared_ptr<Pln_Wire>>& theWires
)
{
	if (theWires.size() IS_EQUAL 1)
	{
		return;
	}

	Geo_ItemSort<std::shared_ptr<Pln_Wire>>
		sort(&LessDiameterSize);
	sort.Perform(theWires);
}

void tnbLib::Marine_CmpSection::RetrieveInnerOuterWires
(
	std::list<std::shared_ptr<Pln_Wire>>& theWires, 
	std::shared_ptr<Pln_Wire>& theOuter,
	std::vector<std::shared_ptr<Pln_Wire>>& theInners
)
{
	if (theWires.size() IS_EQUAL 1)
	{
		theOuter = theWires.front();
		theWires.pop_front();
		return;
	}

	theOuter = theWires.front();
	theWires.pop_front();

	const auto outerBox = theOuter->BoundingBox(0);

	std::vector<std::list<std::shared_ptr<Pln_Wire>>::iterator> removes;
	auto iter = theWires.begin();
	while (iter NOT_EQUAL theWires.end())
	{
		const auto& x = (*iter);
		if (Entity2d_Box::IsInside(x->BoundingBox(0), outerBox))
		{
			theInners.push_back(x);
			removes.push_back(iter);
		}

		iter++;
	}

	for (const auto& x : removes)
	{
		theWires.erase(x);
	}
}

//namespace tnbLib
//{
//
//	namespace createCmpSection
//	{
//
//		static Standard_Boolean LessDiameterSize
//		(
//			const std::shared_ptr<Pln_Wire>& theWire0,
//			const std::shared_ptr<Pln_Wire>& theWire1
//		)
//		{
//			Debug_Null_Pointer(theWire0);
//			Debug_Null_Pointer(theWire1);
//
//			const auto& b0 = theWire0->BoundingBox();
//			const auto& b1 = theWire1->BoundingBox();
//
//			Debug_Null_Pointer(b0);
//			Debug_Null_Pointer(b1);
//
//			return -b0->SquareDiameter() < -b1->SquareDiameter();
//		}
//
//		static void SortWires(std::vector<std::shared_ptr<Pln_Wire>>& theWires)
//		{
//			if (theWires.size() IS_EQUAL 1)
//			{
//				return;
//			}
//
//			Geo_ItemSort<std::shared_ptr<Pln_Wire>>
//				sort(&LessDiameterSize);
//			sort.Perform(theWires);
//		}
//
//		static void RetrieveInnerOuterWires
//		(
//			std::list<std::shared_ptr<Pln_Wire>>& theWires,
//			std::shared_ptr<Pln_Wire>& theOuter,
//			std::vector<std::shared_ptr<Pln_Wire>>& theInners
//		)
//		{
//			if (theWires.size() IS_EQUAL 1)
//			{
//				theOuter = theWires.front();
//				theWires.pop_front();
//				return;
//			}
//
//			theOuter = theWires.front();
//			theWires.pop_front();
//
//			std::vector<std::list<std::shared_ptr<Pln_Wire>>::iterator> removes;
//			auto iter = theWires.begin();
//			while (iter NOT_EQUAL theWires.end())
//			{
//				const auto& x = (*iter);
//				if (Entity2d_Box::IsInside(*x->BoundingBox(), *theOuter->BoundingBox()))
//				{
//					theInners.push_back(x);
//					removes.push_back(iter);
//				}
//
//				iter++;
//			}
//
//			for (const auto& x : removes)
//			{
//				theWires.erase(x);
//			}
//		}
//	}
//}

#include <gp_Pln.hxx>
#include <Geom_Plane.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopExp_Explorer.hxx>
#include <BRep_Tool.hxx>
#include <GeomProjLib.hxx>

#include <TopLoc_Datum3D.hxx>

std::vector<TopoDS_Edge>
tnbLib::Marine_CmpSection::RetrieveEdges
(
	const TopoDS_Shape & theEdges
)
{
	std::vector<TopoDS_Edge> edges;
	for
		(
			TopExp_Explorer explorer(theEdges, TopAbs_EDGE);
			explorer.More();
			explorer.Next()
			)
	{
		auto edge = TopoDS::Edge(explorer.Current());
		if (NOT edge.IsNull())
		{
			edges.push_back(edge);
		}
	}
	return std::move(edges);
}

std::vector<Handle(Geom2d_Curve)>
tnbLib::Marine_CmpSection::RetrieveParaCurves
(
	const std::vector<TopoDS_Edge>& theEdges,
	const gp_Ax2& theSystem
)
{
	Handle(Geom_Plane) plane = new Geom_Plane(gp_Pln(theSystem));
	Debug_Null_Pointer(plane);

	TopLoc_Location loc;

	std::vector<Handle(Geom2d_Curve)> curves;
	curves.reserve(theEdges.size());

	for (const auto& x : theEdges)
	{
		Standard_Real first, last;
		auto curve = BRep_Tool::CurveOnPlane(x, plane, loc, first, last);

		if (curve.IsNull())
		{
			FatalErrorIn("std::vector<Handle(Geom2d_Curve)> Marine_CmpSection::RetrieveParaCurves(Args...)")
				<< "Failed to Calculate the parametric curve" << endl
				<< abort(FatalError);
		}

		curves.push_back(std::move(curve));
	}
	return std::move(curves);
}