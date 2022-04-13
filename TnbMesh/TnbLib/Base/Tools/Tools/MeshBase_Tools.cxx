#include <MeshBase_Tools.hxx>

#include <Pln_Curve.hxx>
#include <TModel_ParaCurve.hxx>
#include <GModel_ParaCurve.hxx>
#include <GeoMesh2d_Background.hxx>
#include <GeoMesh2d_Data.hxx>
#include <Entity2d_MeshValue.hxx>
#include <Entity2d_MetricMeshValue.hxx>
#include <Entity2d_Metric1.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_Curve.hxx>

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
	static const auto cte = (1.0 - EPS6);

	const auto& p0 = theDomain.P0();
	const auto& p1 = theDomain.P1();

	const auto xmin = p0.X();
	const auto xmax = p1.X();
	const auto ymin = p0.Y();
	const auto ymax = p1.Y();

	const auto x0 = theCentre.X();
	const auto y0 = theCentre.Y();

	const auto du = theCoord - theCentre;
	const auto dx = du.X();
	const auto dy = du.Y();

	const auto x = theCoord.X();
	if (x > xmax)
	{
		const auto y = y0 + (dy / dx)*(xmax - x0);
		const auto du1 = Pnt2d(xmax, y) - theCentre;

		auto newPoint = theCentre + cte * du1;
		return std::move(newPoint);
	}

	if (x < xmin)
	{
		const auto y = y0 + (dy / dx)*(xmin - x0);
		const auto du1 = Pnt2d(xmin, y) - theCentre;

		auto newPoint = theCentre + cte * du1;
		return std::move(newPoint);
	}

	const auto y = theCoord.Y();
	if (y > ymax)
	{
		const auto x = x0 + (dx / dy)*(ymax - y0);
		const auto du1 = Pnt2d(x, ymax) - theCentre;

		auto newPoint = theCentre + cte * du1;
		return std::move(newPoint);
	}

	if (y < ymin)
	{
		const auto x = x0 + (dx / dy)*(ymin - y0);
		const auto du1 = Pnt2d(x, ymin) - theCentre;

		auto newPoint = theCentre + cte * du1;
		return std::move(newPoint);
	}

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