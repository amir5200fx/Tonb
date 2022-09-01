#include <MeshBase_Tools.hxx>

#include <Mesh3d_Element.hxx>
#include <Mesh2d_Element.hxx>
#include <Pln_Curve.hxx>
#include <TModel_ParaCurve.hxx>
#include <GModel_ParaCurve.hxx>
#include <GeoMesh2d_Background.hxx>
#include <GeoMesh2d_Data.hxx>
#include <Geo_BoxTools.hxx>
#include <Entity2d_MeshValue.hxx>
#include <Entity2d_MetricMeshValue.hxx>
#include <Entity2d_Metric1.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_Curve.hxx>

#include <armadillo.h>

using namespace arma;

std::shared_ptr<tnbLib::Entity2d_Box> 
tnbLib::MeshBase_Tools::CalcBoundingBox
(
	const std::shared_ptr<Mesh2d_Element>& theElement
)
{
	Debug_Null_Pointer(theElement);
	const auto[p0, p1, p2] = theElement->RetrieveCoords();
	auto t = Geo_BoxTools::GeoBox(p0, p1, p2);
	return std::move(t);
}

std::shared_ptr<tnbLib::Entity3d_Box>
tnbLib::MeshBase_Tools::CalcBoundingBox
(
	const std::shared_ptr<Mesh3d_Element>& theElement
)
{
	Debug_Null_Pointer(theElement);
	const auto[p0, p1, p2, p3] = theElement->RetrieveCoords();
	auto t = Geo_BoxTools::GetBox(p0, p1, p2, p3);
	return std::move(t);
}

tnbLib::Pnt2d 
tnbLib::MeshBase_Tools::CalcAnalyCoord
(
	const Pnt2d & theP0,
	const Pnt2d & theP1, 
	const Pnt2d & theCentre, 
	const Entity2d_Metric1 & m0, 
	const Standard_Real h,
	const Standard_Real len
)
{
	static const Standard_Real c3 = 0.86602540378443864676372317075294;
	const auto invH2 = (Standard_Real)1.0 / (h * h);

	Entity2d_Metric1 m(invH2*m0.A(), invH2*m0.B(), invH2*m0.C());
	const auto D = std::sqrt(m.Determinant());
	const auto cte = c3 / (D * len);

	auto dU = theP1 - theCentre;

	vec2 U;
	U(0) = dU.X();
	U(1) = dU.Y();

	mat22 orthM;
	orthM(0, 0) = -m.B();
	orthM(0, 1) = -m.C();
	orthM(1, 0) = m.A();
	orthM(1, 1) = m.B();

	U = cte * (orthM * U);

	Pnt2d P(theCentre.X() + U(0), theCentre.Y() + U(1));
	return std::move(P);
}

void tnbLib::MeshBase_Tools::SetSourcesToMesh
(
	const std::vector<std::pair<Pnt2d, Standard_Real>>& theSources, 
	const Standard_Real theBaseSize, 
	GeoMesh2d_Background & theMesh
)
{
	const auto& mesh = *theMesh.Mesh();
	if (mesh.Elements().empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "the element list of the background mesh is empty!" << endl
			<< abort(FatalError);
	}

	auto& sources = theMesh.Sources();
	sources.resize(theSources.size(), theBaseSize);

	auto start = mesh.Elements().at(0);
	for (const auto& x : theSources)
	{
		const auto current = mesh.TriangleLocation(start, x.first);
		if (NOT current)
		{
			FatalErrorIn(FunctionSIG)
				<< "the point is outside of the mesh!" << endl
				<< " - domain's of the mesh: " << theMesh.BoundingBox() << endl
				<< " - coordinates of the point: " << x.first << endl
				<< abort(FatalError);
		}
		start = current;

		const auto& currentRef = *current;
		auto n0 = Index_Of(currentRef.Node0()->Index());
		auto n1 = Index_Of(currentRef.Node1()->Index());
		auto n2 = Index_Of(currentRef.Node2()->Index());

		auto v0 = sources[n0];
		auto v1 = sources[n1];
		auto v2 = sources[n2];

		if (v0 < x.second) sources[n0] = v0;
		if (v1 < x.second) sources[n1] = v1;
		if (v2 < x.second) sources[n2] = v2;
	}
}

std::vector<Standard_Real>
tnbLib::MeshBase_Tools::CalcDeterminants
(
	const std::vector<Pnt2d> & pts,
	const Entity2d_MetricMeshValue & theMs
)
{
	const auto& bMesh = theMs.Mesh();
	Debug_Null_Pointer(bMesh);

	auto elemnts = MakeMesh(*bMesh);
#ifdef _DEBUG
	if (elemnts.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "the list of elements is empty!" << endl
			<< abort(FatalError);
	}
#endif // _DEBUG
	auto start = elemnts.front();
	const auto& ms = theMs.Values();

	std::vector<Standard_Real> hs;
	hs.reserve(pts.size());
	for (const auto& x : pts)
	{
		auto loc = ElementLocation(start, x);
		if (NOT loc)
		{
			auto b = Entity2d_Box::BoundingBoxOf(bMesh->Points());
			FatalErrorIn(FunctionSIG)
				<< "the point is outside of the domain!" << endl
				<< " - coord: " << x << endl
				<< " - domain: " << b << endl
				<< abort(FatalError);
		}
		auto[v0, v1, v2] = loc->Nodes();

		const auto& m0 = ms.at(Index_Of(v0->Index()));
		const auto& m1 = ms.at(Index_Of(v1->Index()));
		const auto& m2 = ms.at(Index_Of(v2->Index()));

		auto det0 = m0.Determinant();
		auto det1 = m1.Determinant();
		auto det2 = m2.Determinant();

		auto ws = loc->InterpWeights(x);

		Standard_Real sumA = ws[0] + ws[1] + ws[2];
		Standard_Real numer = ws[0] * det0 + ws[1] * det1 + ws[2] * det2;

		auto h = (1.0 / sumA)*numer;
		hs.push_back(h);
	}
	return std::move(hs);
}

std::shared_ptr<tnbLib::Entity2d_MeshValue> 
tnbLib::MeshBase_Tools::CalcDeterminants
(
	const std::shared_ptr<Entity2d_Triangulation> & theAprx,
	const Entity2d_MetricMeshValue & theMs
)
{
	Debug_Null_Pointer(theAprx);

	const auto& bMesh = theMs.Mesh();
	Debug_Null_Pointer(bMesh);

	auto elemnts = MakeMesh(*bMesh);
#ifdef _DEBUG
	if (elemnts.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "the list of elements is empty!" << endl
			<< abort(FatalError);
	}
#endif // _DEBUG
	auto start = elemnts.front();

	const auto& ms = theMs.Values();
	const auto& pts = theAprx->Points();
	std::vector<Standard_Real> hs;
	hs.reserve(pts.size());
	for (const auto& x : pts)
	{
		auto loc = ElementLocation(start, x);
		if (NOT loc)
		{
			FatalErrorIn(FunctionSIG)
				<< "the point is outside of the domain!" << endl
				<< " - coord: " << x << endl
				<< abort(FatalError);
		}
		auto[v0, v1, v2] = loc->Nodes();

		const auto& m0 = ms.at(Index_Of(v0->Index()));
		const auto& m1 = ms.at(Index_Of(v1->Index()));
		const auto& m2 = ms.at(Index_Of(v2->Index()));

		auto det0 = m0.Determinant();
		auto det1 = m1.Determinant();
		auto det2 = m2.Determinant();

		auto ws = loc->InterpWeights(x);
		
		Standard_Real sumA = ws[0] + ws[1] + ws[2];
		Standard_Real numer = ws[0] * det0 + ws[1] * det1 + ws[2] * det2;
		
		auto h = (1.0 / sumA)*numer;
		hs.push_back(h);
	}
	auto approximated = std::make_shared<Entity2d_MeshValue>();
	Debug_Null_Pointer(approximated);

	approximated->SetMesh(theAprx);
	approximated->SetValues(std::move(hs));
	return std::move(approximated);
}

tnbLib::Pnt2d 
tnbLib::MeshBase_Tools::CorrectCoord
(
	const Pnt2d & theCentre, 
	const Pnt2d & theCoord,
	const Entity2d_Box & theDomain
)
{
	const auto& p0 = theDomain.P0();
	const auto& p1 = theDomain.P1();

	const auto xmin = p0.X();
	const auto xmax = p1.X();
	const auto ymin = p0.Y();
	const auto ymax = p1.Y();

	const auto x0 = theCentre.X();
	const auto y0 = theCentre.Y();

	const auto xp = theCoord.X();
	const auto yp = theCoord.Y();

	if (xp > xmax)
	{
		const auto tx = (xmax - x0) / (xp - x0);
		if (yp > ymax)
		{
			const auto ty = (ymax - y0) / (yp - y0);
			const auto t = std::min(tx, ty);

			Pnt2d newPoint(x0 + t * (xp - x0), y0 + t * (yp - y0));
			return std::move(newPoint);
		}
		
		if (yp < ymin)
		{
			const auto ty = (ymin - y0) / (yp - y0);
			const auto t = std::min(tx, ty);

			Pnt2d newPoint(x0 + t * (xp - x0), y0 + t * (yp - y0));
			return std::move(newPoint);
		}
		const auto y = y0 + (yp - y0)*tx;

		Pnt2d newPoint(xmax, y);
		return std::move(newPoint);
	}

	if (xp < xmin)
	{
		const auto tx = (xmin - x0) / (xp - x0);
		if (yp > ymax)
		{
			const auto ty = (ymax - y0) / (yp - y0);
			const auto t = std::min(tx, ty);

			Pnt2d newPoint(x0 + t * (xp - x0), y0 + t * (yp - y0));
			return std::move(newPoint);
		}

		if (yp < ymin)
		{
			const auto ty = (ymin - y0) / (yp - y0);
			const auto t = std::min(tx, ty);

			Pnt2d newPoint(x0 + t * (xp - x0), y0 + t * (yp - y0));
			return std::move(newPoint);
		}
		const auto y = y0 + (yp - y0)*tx;

		Pnt2d newPoint(xmin, y);
		return std::move(newPoint);
	}
	
	if (yp > ymax)
	{
		const auto t = (ymax - y0) / (yp - y0);
		const auto x = x0 + (xp - x0)*t;

		Pnt2d newPoint(x, ymax);
		return std::move(newPoint);
	}

	if (yp < ymin)
	{
		const auto t = (ymin - y0) / (yp - y0);
		const auto x = x0 + (xp - x0)*t;

		Pnt2d newPoint(x, ymin);
		return std::move(newPoint);
	}

	Info << " - Coord: " << theCoord << endl;
	Info << " - Domain: " << theDomain << endl;
	FatalErrorIn(FunctionSIG)
		<< "unpredictable condition is occurred!" << endl
		<< abort(FatalError);
	return Pnt2d::null;
}

const Handle(Geom2d_Curve)& 
tnbLib::MeshBase_Tools::Geometry
(
	const std::shared_ptr<Pln_Curve>& theCurve
)
{
	Debug_Null_Pointer(theCurve);
	return theCurve->Geometry();
}

const Handle(Geom2d_Curve)&
tnbLib::MeshBase_Tools::Geometry
(
	const std::shared_ptr<TModel_ParaCurve>& theCurve
)
{
	Debug_Null_Pointer(theCurve);
	return theCurve->Geometry();
}

const Handle(Geom2d_Curve)&
tnbLib::MeshBase_Tools::Geometry
(
	const std::shared_ptr<GModel_ParaCurve>& theCurve
)
{
	Debug_Null_Pointer(theCurve);
	return theCurve->Geometry();
}

Standard_Real 
tnbLib::MeshBase_Tools::FirstParameter
(
	const std::shared_ptr<Pln_Curve>& theCurve
)
{
	Debug_Null_Pointer(theCurve);
	return theCurve->FirstParameter();
}

Standard_Real
tnbLib::MeshBase_Tools::FirstParameter
(
	const std::shared_ptr<TModel_ParaCurve>& theCurve
)
{
	Debug_Null_Pointer(theCurve);
	return theCurve->FirstParameter();
}

Standard_Real
tnbLib::MeshBase_Tools::FirstParameter
(
	const std::shared_ptr<GModel_ParaCurve>& theCurve
)
{
	Debug_Null_Pointer(theCurve);
	return theCurve->FirstParameter();
}

Standard_Real
tnbLib::MeshBase_Tools::LastParameter
(
	const std::shared_ptr<Pln_Curve>& theCurve
)
{
	Debug_Null_Pointer(theCurve);
	return theCurve->LastParameter();
}

Standard_Real
tnbLib::MeshBase_Tools::LastParameter
(
	const std::shared_ptr<TModel_ParaCurve>& theCurve
)
{
	Debug_Null_Pointer(theCurve);
	return theCurve->LastParameter();
}

Standard_Real
tnbLib::MeshBase_Tools::LastParameter
(
	const std::shared_ptr<GModel_ParaCurve>& theCurve
)
{
	Debug_Null_Pointer(theCurve);
	return theCurve->LastParameter();
}