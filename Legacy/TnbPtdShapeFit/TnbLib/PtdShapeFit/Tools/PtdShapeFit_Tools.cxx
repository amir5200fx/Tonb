#include <PtdShapeFit_Tools.hxx>

#include <Cad_Shape.hxx>
#include <Cad2d_Plane.hxx>
#include <Pln_Tools.hxx>
#include <Pln_Wire.hxx>
#include <Pln_Curve.hxx>
#include <Pnt3d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <Geom2dConvert.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <Geom2d_Curve.hxx>

std::vector<std::pair<Standard_Real, Standard_Integer>> 
tnbLib::PtdShapeFit_Tools::Knots
(
	const Standard_Integer theNbQ,
	const Standard_Integer theDegree, 
	const Standard_Real theU0,
	const Standard_Real theU1
)
{
	if (theNbQ - 1 < theDegree)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid degree for the curve" << endl
			<< "p = " << theDegree << endl
			<< "n = " << theNbQ << endl
			<< abort(FatalError);
	}
	const auto u0 = theU0;
	const auto u1 = theU1;
	const auto n = theNbQ - 1;
	const auto p = theDegree;
	const auto nbKnots = n + p + 2;
	const auto nbInners = nbKnots - 2 * (p + 1);
	Debug_If_Condition(nbInners < 0);
	const auto du = (u1 - u0) / (nbInners + 1);

	std::vector<std::pair<Standard_Real, Standard_Integer>> Knots;
	Knots.reserve(nbInners + 2);
	for (size_t i = 0; i < nbInners + 2; i++)
	{
		auto u = u0 + i * du;
		auto paired = std::make_pair(u, 1);
		Knots.push_back(std::move(paired));
	}
	Knots[0].second = p + 1;
	Knots[Knots.size() - 1].second = p + 1;
	return std::move(Knots);
}

std::tuple
<
	std::vector<std::pair<tnbLib::Pnt2d, Standard_Real>>,
	std::vector<Standard_Real>, 
	std::vector<Standard_Integer>,
	Standard_Integer
>
tnbLib::PtdShapeFit_Tools::RetrievePoles(const Pln_Curve& theCurve)
{
	const auto& g = theCurve.Geometry();
	if (NOT g)
	{
		FatalErrorIn(FunctionSIG)
			<< "no geometry has been found." << endl
			<< abort(FatalError);
	}
	std::vector<std::pair<Pnt2d, Standard_Real>> coords;
	std::vector<Standard_Real> knots;
	std::vector<Standard_Integer> mults;
	Handle(Geom2d_BSplineCurve) bspline = Handle(Geom2d_BSplineCurve)::DownCast(g);
	if (NOT bspline)
	{
		bspline = Geom2dConvert::CurveToBSplineCurve(g);
		if (NOT bspline)
		{
			FatalErrorIn(FunctionSIG)
				<< "Failed to convert." << endl
				<< abort(FatalError);
		}
	}

	const auto& poles = bspline->Poles();
	for (Standard_Integer i = 1; i <= poles.Size(); i++)
	{
		Pnt2d pt = poles.Value(i);
		Standard_Real w = 1.0;
		if (bspline->Weights())
		{
			w = bspline->Weights()->Value(i);
		}
		//std::cout << "pt = " << pt << ", w = " << w << std::endl;
		auto paired = std::make_pair(std::move(pt), w);
		coords.push_back(std::move(paired));
	}
	//PAUSE;
	const auto& Knots = bspline->Knots();
	for (Standard_Integer i = 1; i <= Knots.Size(); i++)
	{
		knots.push_back(Knots.Value(i));
	}
	const auto& Mults = bspline->Multiplicities();
	for (Standard_Integer i = 1; i <= Mults.Size(); i++)
	{
		mults.push_back(Mults.Value(i));
	}
	auto t = 
		std::make_tuple
		(
			std::move(coords), std::move(knots),
			std::move(mults), bspline->Degree()
		);
	return std::move(t);
}

std::vector<std::shared_ptr<tnbLib::Pln_Curve>> 
tnbLib::PtdShapeFit_Tools::RetrieveCurves
(
	const Cad2d_Plane& thePlane
)
{
	const auto& outer = thePlane.OuterWire();
	Debug_Null_Pointer(outer);
	std::vector<std::shared_ptr<Pln_Curve>> curves;
	for (const auto& x : outer->RetrieveCurves())
	{
		Debug_Null_Pointer(x);
		curves.push_back(x);
	}
	if (thePlane.InnerWires())
	{
		for (const auto& w : *thePlane.InnerWires())
		{
			for (const auto& x : w->RetrieveCurves())
			{
				Debug_Null_Pointer(x);
				curves.push_back(x);
			}
		}
	}
	return std::move(curves);
}

#include <BRepBuilderAPI_MakeFace.hxx>
#include <TopoDS_Face.hxx>
#include <Geom_BSplineSurface.hxx>
#include <Geom_Plane.hxx>
#include <TColgp_Array2OfPnt.hxx>
#include <TColStd_Array2OfReal.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <Standard_Handle.hxx>

namespace tnbLib
{
	namespace ptdShapeTools
	{

		std::pair<TColStd_Array1OfReal, TColStd_Array1OfInteger>
			Knots(const std::vector<std::pair<Standard_Real, Standard_Integer>>& theKnots)
		{
			TColStd_Array1OfReal knots(1, (Standard_Integer)theKnots.size());
			TColStd_Array1OfInteger mults(1, (Standard_Integer)theKnots.size());
			Standard_Integer K = 0;
			for (const auto& x : theKnots)
			{
				K++;
				knots.SetValue(K, x.first);
				mults.SetValue(K, x.second);
			}
			auto paired = std::make_pair(std::move(knots), std::move(mults));
			return std::move(paired);
		}

		std::pair<TColgp_Array2OfPnt, TColStd_Array2OfReal>
			RetrieveCtrlNet
			(
				const std::vector<std::vector<std::pair<Pnt2d, Standard_Real>>>& theQw,
				const std::vector<Handle(Geom_Plane)>& thePlanes
			)
		{
			TColgp_Array2OfPnt net(1, theQw.size(), 1, theQw.at(0).size());
			TColStd_Array2OfReal weight(1, theQw.size(), 1, theQw.at(0).size());
			for (Standard_Integer i = 0; i < theQw.size(); i++)
			{
				const auto& pl = thePlanes.at(i);
				Debug_Null_Pointer(pl);
				for (Standard_Integer j = 0; j < theQw.at(0).size(); j++)
				{
					const auto& pw = theQw.at(i).at(j);
					auto [u, v] = pw.first.Components();
					net.SetValue(i + 1, j + 1, pl->Value(u, v));
					weight.SetValue(i + 1, j + 1, pw.second);
				}
			}
			auto t = std::make_pair(std::move(net), std::move(weight));
			return std::move(t);
		}

		auto RetrievePlanes
		(
			const gp_Ax1& theAx,
			const std::vector<Standard_Real>& xs
		)
		{
			std::vector<Handle(Geom_Plane)> planes;
			planes.reserve(xs.size());
			for (auto loc : xs)
			{
				//std::cout << "loc = " << loc << std::endl;
				auto pt = Pnt3d(theAx.Location()) + loc * Pnt3d(theAx.Direction().XYZ());
				Handle(Geom_Plane) pl = new Geom_Plane(pt, theAx.Direction());
				planes.push_back(std::move(pl));
			}
			return std::move(planes);
		}

		auto RetrievePoles(const std::vector<std::shared_ptr<Pln_Curve>>& thePlanes)
		{
			std::vector<std::vector<std::pair<Pnt2d, Standard_Real>>> Qw;
			Qw.reserve(thePlanes.size());
			for (const auto& x : thePlanes)
			{
				Debug_Null_Pointer(x);
				auto [Pws, weights, mults, degree] = PtdShapeFit_Tools::RetrievePoles(*x);
				Qw.push_back(std::move(Pws));
			}
			auto [Pws, weights, mults, degree] = PtdShapeFit_Tools::RetrievePoles(*thePlanes.at(0));
			std::vector<std::pair<Standard_Real, Standard_Integer>> knots;
			knots.reserve(weights.size());
			for (size_t i = 0; i < weights.size(); i++)
			{
				auto paired = std::make_pair(weights.at(i), mults.at(i));
				knots.push_back(std::move(paired));
			}
			auto t = std::make_tuple(std::move(Qw), std::move(knots), degree);
			return std::move(t);
		}

		auto RetrieveSurfaceCurves
		(
			const std::vector<std::vector<std::shared_ptr<Pln_Curve>>>& theCurves
		)
		{
			std::vector<std::vector<std::shared_ptr<Pln_Curve>>> allCurves;
			for (Standard_Integer j = 0; j < theCurves.at(0).size(); j++)
			{
				std::vector<std::shared_ptr<Pln_Curve>> curves;
				for (Standard_Integer i = 0; i < theCurves.size(); i++)
				{
					const auto& curve = theCurves.at(i).at(j);
					curves.push_back(curve);
				}
				allCurves.push_back(std::move(curves));
			}
			return std::move(allCurves);
		}
	}
}

std::shared_ptr<tnbLib::Cad_Shape> 
tnbLib::PtdShapeFit_Tools::MakeExtrudedSurface
(
	const std::vector<std::shared_ptr<Pln_Curve>>& theSections,
	const std::vector<Handle(Geom_Plane)>& thePlanes
)
{
	auto [poles, knots, vdegree] = ptdShapeTools::RetrievePoles(theSections);
	std::cout << "degree: " << vdegree << std::endl;
	auto [poleNet, weightNet] = ptdShapeTools::RetrieveCtrlNet(poles, thePlanes);

	auto degree = 3;
	if (theSections.size() < 3) degree = 1;
	else if (theSections.size() < 4) degree = 2;
	auto [vknots, vMults] = ptdShapeTools::Knots(knots);
	auto [uknots, uMults] = ptdShapeTools::Knots(Knots(theSections.size(), degree, 0.0, 1.0));

	try
	{
		Handle(Geom_Surface) surface = 
			new Geom_BSplineSurface
			(
				poleNet, weightNet,
				uknots, vknots, uMults, 
				vMults, degree, vdegree
			);
		BRepBuilderAPI_MakeFace maker(surface, 1.0E-6);
		if (NOT maker.IsDone())
		{
			FatalErrorIn(FunctionSIG)
				<< "Failed to build the face." << endl
				<< abort(FatalError);
		}
		auto shape = std::make_shared<Cad_Shape>(maker.Face());
		return std::move(shape);
	}
	catch (const Standard_Failure& x)
	{
		FatalErrorIn(FunctionSIG)
			<< "opencascade error message has been detected: Unable to create geometric surface" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

#include <TopoDS_Builder.hxx>
#include <TopoDS_Compound.hxx>
#include <Dir3d.hxx>

std::shared_ptr<tnbLib::Cad_Shape> 
tnbLib::PtdShapeFit_Tools::MakeExtrudedShape
(
	const std::vector<std::shared_ptr<Cad2d_Plane>>& thePlanes,
	const gp_Ax1& theAx, 
	const std::vector<Standard_Real>& theLocs
)
{
	//std::cout << "coord= " << theAx.Location() << std::endl;
	//std::cout << "dir = " << theAx.Direction() << std::endl;
	auto planes = ::tnbLib::ptdShapeTools::RetrievePlanes(theAx, theLocs);

	std::vector<std::vector<std::shared_ptr<Pln_Curve>>> allCurves;
	for (const auto& x : thePlanes)
	{
		Debug_Null_Pointer(x);
		auto curves = RetrieveCurves(*x);
		allCurves.push_back(std::move(curves));
	}
	auto surfCurves = ptdShapeTools::RetrieveSurfaceCurves(allCurves);

	std::vector<std::shared_ptr<Cad_Shape>> shapes;
	for (const auto& x : surfCurves)
	{
		auto shape = MakeExtrudedSurface(x, planes);
		shapes.push_back(std::move(shape));
	}

	TopoDS_Compound compound;
	TopoDS_Builder builder;
	builder.MakeCompound(compound);
	for (const auto& x : shapes)
	{
		builder.Add(compound, x->Shape());
	}

	auto shape = std::make_shared<Cad_Shape>(compound);
	return std::move(shape);
}