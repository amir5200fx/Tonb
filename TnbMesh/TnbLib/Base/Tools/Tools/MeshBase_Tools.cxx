#include <MeshBase_Tools.hxx>

#include <Pln_Curve.hxx>
#include <TModel_ParaCurve.hxx>
#include <GModel_ParaCurve.hxx>
#include <GeoMesh2d_Background.hxx>
#include <GeoMesh2d_Data.hxx>
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

		auto v0 = theSources[n0].second;
		auto v1 = theSources[n1].second;
		auto v2 = theSources[n2].second;

		if (sources[n0] <= x.second) sources[n0] = x.second;
		if (sources[n1] <= x.second) sources[n1] = x.second;
		if (sources[n2] <= x.second) sources[n2] = x.second;
	}
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