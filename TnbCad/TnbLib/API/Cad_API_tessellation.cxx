#include <Cad_API.hxx>

#include <Cad_Tools.hxx>
#include <Cad_Shape.hxx>
#include <Cad_FastDiscrete.hxx>
#include <FastDiscrete_Params.hxx>
#include <Geo_Tools.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <opencascade/Poly_Triangulation.hxx>

tnbLib::api::cad::Tessellation::Tessellation(const chai::Cad&)
	: obj{ std::make_shared<FastDiscrete_Params>() }
{
	obj->Angle = Geo_Tools::DegToRadian(5.0);
	obj->Deflection = 1.e-3;
	obj->MinSize = 1.e-5;
	obj->InParallel = false;
	obj->Relative = true;
	obj->AdaptiveMin = false;
	obj->InternalVerticesMode = true;
	obj->ControlSurfaceDeflection = true;
}

tnbLib::api::cad::Tessellation::Tessellation()
	: obj{ std::make_shared<FastDiscrete_Params>() }
{
	obj->Angle = Geo_Tools::DegToRadian(5.0);
	obj->Deflection = 1.e-3;
	obj->MinSize = 1.e-5;
	obj->InParallel = false;
	obj->Relative = true;
	obj->AdaptiveMin = false;
	obj->InternalVerticesMode = true;
	obj->ControlSurfaceDeflection = true;
}


void tnbLib::api::cad::tessellate(const Shape& shape, const Tessellation& tessellation, unsigned short verbose)
{
	{
		Global_Timer timer;
		timer.SetInfo(Global_TimerInfo_ms);
		Cad_FastDiscrete::Triangulation(shape.shape->Shape(), *tessellation.obj);
	}
	if (verbose)
	{
		const auto surfaces = Cad_Tools::RetrieveTriangulation(shape.shape->Shape());
		Info << " - nb. of surfaces: " << surfaces.size() << "\n";
		size_t k = 0;
		size_t nbNodes = 0;
		size_t nbTris = 0;
		for (const auto& x : surfaces)
		{
			if (x)
			{
				Info << " - surface nb. " << k++ << ": "
					<< "nb. of nodes: " << x->NbNodes() << ", nb. of triangles: " << x->NbTriangles()
					<< ", Deflection: " << x->Deflection() << "\n";

				nbNodes += x->NbNodes();
				nbTris += x->NbTriangles();
			}
		}
		Info << "\n";
		Info << " - Total nb. of nodes: " << nbNodes << "\n";
		Info << " - Total nb. of triangles: " << nbTris << "\n";
		Info << "\n";
	}
}

void tnbLib::api::cad::set_angle(const Tessellation& t, double x)
{
	t.obj->Angle = x;
}

void tnbLib::api::cad::set_deflection(const Tessellation& t, double x)
{
	t.obj->Deflection = x;
}

void tnbLib::api::cad::set_min_size(const Tessellation& t, double x)
{
	t.obj->MinSize = x;
}

void tnbLib::api::cad::set_relative_mode(const Tessellation& t, bool status)
{
	t.obj->Relative = status;
}

void tnbLib::api::cad::set_parallel_mode(const Tessellation& t, bool status)
{
	t.obj->InParallel = status;
}

void tnbLib::api::cad::set_adaptive_min(const Tessellation& t, bool status)
{
	t.obj->AdaptiveMin = status;
}

void tnbLib::api::cad::set_internal_vertices_mode(const Tessellation& t, bool status)
{
	t.obj->InternalVerticesMode = status;
}

void tnbLib::api::cad::set_control_surf_deflection(const Tessellation& t, bool status)
{
	t.obj->ControlSurfaceDeflection = status;
}
