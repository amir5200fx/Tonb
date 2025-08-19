#include <Marine_SectTools.hxx>

#include <Cad2d_RemoveNonManifold.hxx>
#include <Marine_PlnCurves.hxx>
#include <Marine_SectionType.hxx>
#include <Pln_Tools.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_CurveTools.hxx>
#include <Geo_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <gp_Lin2d.hxx>
#include <Geom2d_Curve.hxx>

namespace tnbLib
{

	auto MakeSegment(const Pnt2d& coord, const gp_Lin2d& line, const Marine_PlnCurveType t)
	{
		auto pproj = Geo_Tools::ProjectToLine_cgal(coord, Geo_Tools::GetLine(line));

		auto geom = Pln_CurveTools::MakeSegment(coord, pproj);
		auto curve = Marine_SectTools::CurveCreator(geom, Marine_SectTools::ConvertType(t));
		return std::move(curve);
	}

	auto RetrieveSymmCurves(const std::vector<std::shared_ptr<Pln_Curve>>& curves, const gp_Ax2d& ax, const Marine_PlnCurveType t)
	{
		gp_Trsf2d tr;
		tr.SetMirror(ax);
		std::vector<Handle(Geom2d_Curve)> gCurves;
		gCurves.reserve(curves.size());
		for (const auto& x : curves)
		{
			const auto& geometry = x->Geometry();
			auto copy = Handle(Geom2d_Curve)::DownCast(geometry->Transformed(tr));
			Debug_Null_Pointer(copy);
			gCurves.push_back(std::move(copy));
		}

		std::vector<std::shared_ptr<Pln_Curve>> allCurves;
		allCurves.reserve(2 * curves.size());
		for (const auto& x : curves)
		{
			allCurves.push_back(x);
		}
		for (const auto& x : Marine_SectTools::CurveCreator(gCurves, Marine_SectTools::ConvertType(t)))
		{
			allCurves.push_back(x);
		}
		return std::move(allCurves);
	}
}

tnbLib::Marine_PlnCurveType 
tnbLib::Marine_SectTools::CheckCurveType
(
	const std::vector<std::shared_ptr<Pln_Curve>>& theCurves
)
{
	for (const auto& x : theCurves)
	{
		if (NOT std::dynamic_pointer_cast<Marine_PlnCurve>(x))
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid type of the curve has been detected: " << endl
				<< " - type of the curve is not marine!" << endl
				<< abort(FatalError);
		}
	}

	auto iter = theCurves.begin();
	auto t0 = std::dynamic_pointer_cast<Marine_PlnCurve>(*iter)->CurveType();
	iter++;

	while (iter NOT_EQUAL theCurves.end())
	{
		if (std::dynamic_pointer_cast<Marine_PlnCurve>(*iter)->CurveType() NOT_EQUAL t0)
		{
			FatalErrorIn(FunctionSIG)
				<< "all curves must have the same type!" << endl
				<< abort(FatalError);
		}
		iter++;
	}
	return t0;
}

std::vector<std::shared_ptr<tnbLib::Pln_Curve>> 
tnbLib::Marine_SectTools::RepairSymmetricDeckSection
(
	const std::vector<std::shared_ptr<Pln_Curve>>& theCurves,
	const gp_Ax2d & theAxis,
	const Standard_Real theMinTol,
	const Standard_Real theMaxTol
)
{
	if (theMaxTol < theMinTol)
	{
		FatalErrorIn(FunctionSIG)
			<< "the maxTol must be bigger than minTol!" << endl
			<< " - minTol: " << theMinTol << endl
			<< " - maxTol:" << theMaxTol << endl
			<< abort(FatalError);
	}
	auto t = CheckCurveType(theCurves);

	const auto b = Pln_Tools::BoundingBox(theCurves);
	const auto d = b.Diameter();

	const auto minTol = d * theMinTol;
	const auto maxTol = d * theMaxTol;
	auto tol = minTol;

	const auto mergedEdges = Pln_Tools::RetrieveMergedEdges(theCurves, minTol, maxTol);

	Cad2d_RemoveNonManifold alg(mergedEdges);
	alg.Perform();

	const auto segments = alg.RetrieveCompundEdges();

	gp_Lin2d line(theAxis);

	std::vector<std::shared_ptr<Cad2d_RemoveNonManifold::Segment>> dangles;
	for (const auto& x : segments)
	{
		if (NOT x->IsRing())
		{
			Debug_Null_Pointer(x);

			const auto& n0 = x->Node0();
			const auto& n1 = x->Node1();

			Debug_Null_Pointer(n0);
			Debug_Null_Pointer(n1);

			auto d0 = line.Distance(n0->Vtx()->Coord());
			auto d1 = line.Distance(n1->Vtx()->Coord());

			if (d0 <= tol AND d1 <= tol)
			{
				continue;
			}

			if (d0 > tol AND d1 > tol)
			{
				FatalErrorIn(FunctionSIG)
					<< "invalid section has been detected!" << endl
					<< abort(FatalError);
			}

			dangles.push_back(x);
		}
	}
	
	std::vector<std::shared_ptr<Pln_Curve>> symCurves;
	for (const auto& x : theCurves)
	{
		symCurves.push_back(x);
	}

	for (const auto& x : dangles)
	{
		Debug_Null_Pointer(x);

		const auto& n0 = x->Node0();
		const auto& n1 = x->Node1();

		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);

		auto d0 = line.Distance(n0->Vtx()->Coord());
		auto d1 = line.Distance(n1->Vtx()->Coord());

		if (d0 > tol)
		{
			const auto& coord = n0->Vtx()->Coord();		
			auto curve = MakeSegment(coord, line, t);
			symCurves.push_back(std::move(curve));
		}
		else if (d1 > tol)
		{
			const auto& coord = n1->Vtx()->Coord();
			auto curve = MakeSegment(coord, line, t);
			symCurves.push_back(std::move(curve));
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "unexpected situation has been detected!" << endl
				<< abort(FatalError);
		}
	}

	auto allCurves = RetrieveSymmCurves(symCurves, theAxis, t);
	return std::move(allCurves);
}

std::vector<std::shared_ptr<tnbLib::Pln_Curve>> 
tnbLib::Marine_SectTools::RepairFullDeckSection
(
	const std::vector<std::shared_ptr<Pln_Curve>>& theCurves, 
	const gp_Ax2d & theAxis, 
	const Standard_Real theMinTol,
	const Standard_Real theMaxTol
)
{
	if (theMaxTol < theMinTol)
	{
		FatalErrorIn(FunctionSIG)
			<< "the maxTol must be bigger than minTol!" << endl
			<< " - minTol: " << theMinTol << endl
			<< " - maxTol:" << theMaxTol << endl
			<< abort(FatalError);
	}
	auto t = CheckCurveType(theCurves);

	const auto b = Pln_Tools::BoundingBox(theCurves);
	const auto d = b.Diameter();

	const auto minTol = d * theMinTol;
	const auto maxTol = d * theMaxTol;
	auto tol = minTol;

	const auto mergedEdges = Pln_Tools::RetrieveMergedEdges(theCurves, minTol, maxTol);

	Cad2d_RemoveNonManifold alg(mergedEdges);
	alg.Perform();

	const auto segments = alg.RetrieveCompundEdges();

	gp_Lin2d line(theAxis);

	std::vector<std::shared_ptr<Cad2d_RemoveNonManifold::Segment>> dangles;
	for (const auto& x : segments)
	{
		if (NOT x->IsRing())
		{
			Debug_Null_Pointer(x);

			const auto& n0 = x->Node0();
			const auto& n1 = x->Node1();

			Debug_Null_Pointer(n0);
			Debug_Null_Pointer(n1);

			auto d0 = line.Distance(n0->Vtx()->Coord());
			auto d1 = line.Distance(n1->Vtx()->Coord());

			if (d0 > tol AND d1 > tol)
			{
				dangles.push_back(x);
			}
		}
	}

	std::vector<std::shared_ptr<Pln_Curve>> allCurves;
	for (const auto& x : theCurves)
	{
		allCurves.push_back(x);
	}

	for (const auto& x : theCurves)
	{
		allCurves.push_back(x);
	}

	for (const auto& x : dangles)
	{
		Debug_Null_Pointer(x);

		const auto& n0 = x->Node0();
		const auto& n1 = x->Node1();

		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);

		auto geom = Pln_CurveTools::MakeSegment(n0->Vtx()->Coord(), n1->Vtx()->Coord());
		auto curve = Marine_SectTools::CurveCreator(geom, Marine_SectTools::ConvertType(t));
		allCurves.push_back(std::move(curve));
	}
	return std::move(allCurves);
}

std::vector<std::shared_ptr<tnbLib::Pln_Curve>> 
tnbLib::Marine_SectTools::RepairSymmetricStation
(
	const std::vector<std::shared_ptr<Pln_Curve>>& theCurves,
	const gp_Ax2d & theAxis,
	const Standard_Real theMinTol, 
	const Standard_Real theMaxTol
)
{
	if (theMaxTol < theMinTol)
	{
		FatalErrorIn(FunctionSIG)
			<< "the maxTol must be bigger than minTol!" << endl
			<< " - minTol: " << theMinTol << endl
			<< " - maxTol:" << theMaxTol << endl
			<< abort(FatalError);
	}
	auto t = CheckCurveType(theCurves);

	const auto b = Pln_Tools::BoundingBox(theCurves);
	const auto d = b.Diameter();

	const auto minTol = d * theMinTol;
	const auto maxTol = d * theMaxTol;
	auto tol = minTol;

	const auto mergedEdges = Pln_Tools::RetrieveMergedEdges(theCurves, minTol, maxTol);

	Cad2d_RemoveNonManifold alg(mergedEdges);
	alg.Perform();

	const auto segments = alg.RetrieveCompundEdges();
	//std::cout <<"loc: "<< theAxis.Location() << std::endl;
	//std::cout << "dir: " << theAxis.Direction() << std::endl;
	gp_Lin2d line(theAxis);

	std::vector<std::shared_ptr<Cad2d_RemoveNonManifold::Segment>> dangles;
	for (const auto& x : segments)
	{
		if (NOT x->IsRing())
		{
			Debug_Null_Pointer(x);

			const auto& n0 = x->Node0();
			const auto& n1 = x->Node1();

			Debug_Null_Pointer(n0);
			Debug_Null_Pointer(n1);

			auto d0 = line.Distance(n0->Vtx()->Coord());
			auto d1 = line.Distance(n1->Vtx()->Coord());

			//std::cout << d0 << ", " << d1 << std::endl;
			//std::cout << "tol = " << tol << std::endl;

			if (d0 <= tol AND d1 <= tol)
			{
				continue;
			}

			if (d0 > tol AND d1 > tol)
			{
				FatalErrorIn(FunctionSIG)
					<< "invalid section has been detected!" << endl
					<< " - tol: " << tol << endl
					<< " - d0: " << d0 << endl
					<< " - d1: " << d1 << endl
					<< abort(FatalError);
			}

			dangles.push_back(x);
		}
	}

	if (dangles.size() > 1)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid section  has been detected!" << endl
			<< abort(FatalError);
	}

	std::vector<std::shared_ptr<Pln_Curve>> symCurves;
	for (const auto& x : theCurves)
	{
		symCurves.push_back(x);
	}

	const auto& seg = segments[0];
	Debug_Null_Pointer(seg);

	const auto& n0 = seg->Node0();
	const auto& n1 = seg->Node1();

	Debug_Null_Pointer(n0);
	Debug_Null_Pointer(n1);

	auto d0 = line.Distance(n0->Vtx()->Coord());
	auto d1 = line.Distance(n1->Vtx()->Coord());

	if (d0 > tol)
	{
		const auto& coord = n0->Vtx()->Coord();
		auto curve = MakeSegment(coord, line, t);
		symCurves.push_back(std::move(curve));
	}
	else if (d1 > tol)
	{
		const auto& coord = n1->Vtx()->Coord();
		auto curve = MakeSegment(coord, line, t);
		symCurves.push_back(std::move(curve));
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "unexpected situation has been detected!" << endl
			<< abort(FatalError);
	}

	auto allCurves = RetrieveSymmCurves(symCurves, theAxis, t);
	return std::move(allCurves);
}

std::vector<std::shared_ptr<tnbLib::Pln_Curve>> 
tnbLib::Marine_SectTools::RepairFullStation
(
	const std::vector<std::shared_ptr<Pln_Curve>>& theCurves, 
	const gp_Ax2d & theAxis,
	const Standard_Real theMinTol, 
	const Standard_Real theMaxTol
)
{
	if (theMaxTol < theMinTol)
	{
		FatalErrorIn(FunctionSIG)
			<< "the maxTol must be bigger than minTol!" << endl
			<< " - minTol: " << theMinTol << endl
			<< " - maxTol:" << theMaxTol << endl
			<< abort(FatalError);
	}
	auto t = CheckCurveType(theCurves);

	const auto b = Pln_Tools::BoundingBox(theCurves);
	const auto d = b.Diameter();

	const auto minTol = d * theMinTol;
	const auto maxTol = d * theMaxTol;
	auto tol = minTol;

	const auto mergedEdges = Pln_Tools::RetrieveMergedEdges(theCurves, minTol, maxTol);

	Cad2d_RemoveNonManifold alg(mergedEdges);
	alg.Perform();

	const auto segments = alg.RetrieveCompundEdges();

	gp_Lin2d line(theAxis);

	std::vector<std::shared_ptr<Cad2d_RemoveNonManifold::Segment>> dangles;
	for (const auto& x : segments)
	{
		if (NOT x->IsRing())
		{
			Debug_Null_Pointer(x);

			const auto& n0 = x->Node0();
			const auto& n1 = x->Node1();

			Debug_Null_Pointer(n0);
			Debug_Null_Pointer(n1);

			auto d0 = line.Distance(n0->Vtx()->Coord());
			auto d1 = line.Distance(n1->Vtx()->Coord());

			if (d0 > tol AND d1 > tol)
			{
				dangles.push_back(x);
			}
		}
	}

	if (dangles.size() > 1)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid section  has been detected!" << endl
			<< abort(FatalError);
	}

	std::vector<std::shared_ptr<Pln_Curve>> allCurves;
	for (const auto& x : theCurves)
	{
		allCurves.push_back(x);
	}

	for (const auto& x : theCurves)
	{
		allCurves.push_back(x);
	}

	const auto& seg = segments[0];
	Debug_Null_Pointer(seg);

	const auto& n0 = seg->Node0();
	const auto& n1 = seg->Node1();

	Debug_Null_Pointer(n0);
	Debug_Null_Pointer(n1);

	auto geom = Pln_CurveTools::MakeSegment(n0->Vtx()->Coord(), n1->Vtx()->Coord());
	auto curve = Marine_SectTools::CurveCreator(geom, Marine_SectTools::ConvertType(t));
	allCurves.push_back(std::move(curve));

	return std::move(allCurves);
}