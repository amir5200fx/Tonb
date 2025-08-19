#include <Pln_CascadeTools.hxx>

#include <Pnt2d.hxx>

#include <opencascade/gp_Circ2d.hxx>
#include <opencascade/gp_Elips2d.hxx>
#include <opencascade/gp_Hypr2d.hxx>
#include <opencascade/gp_Parab2d.hxx>

gp_Circ2d 
tnbLib::Pln_CascadeTools::CreateCircle
(
	const gp_Ax2d & theAx, 
	const Standard_Real theRadius
)
{
	try {
		return { theAx, theRadius };
	}
	catch (const Standard_ConstructionError& err) {
		FatalErrorIn(FunctionSIG) << "\n"
			<< "Couldn't construct the circle: \n"
			<< err.GetMessageString() << "\n"
			<< tnbLib::abort(FatalError);
	}
	return {};
}

gp_Elips2d 
tnbLib::Pln_CascadeTools::CreateEllipse
(
	const gp_Ax2d & theMajorAx, 
	const Standard_Real theMajorRadius,
	const Standard_Real theMinorRadius
)
{
	try {
		return { theMajorAx, theMajorRadius, theMinorRadius };
	}
	catch (const Standard_ConstructionError& err) {
		FatalErrorIn(FunctionSIG) << "\n"
			<< "Couldn't construct the ellipse.\n"
			<< err.GetMessageString() << "\n"
			<< tnbLib::abort(FatalError);
	}
	return{};
}

gp_Hypr2d 
tnbLib::Pln_CascadeTools::CreateHyperbola
(
	const gp_Ax2d & theMajorAxis, 
	const Standard_Real theMajorRadius, 
	const Standard_Real theMinorRadius
)
{
	try {
		return { theMajorAxis, theMajorRadius, theMinorRadius };
	}
	catch (const Standard_ConstructionError& err) {
		FatalErrorIn(FunctionSIG) << "\n"
			<< "Couldn't construct the hyperbola.\n"
			<< err.GetMessageString() << "\n"
			<< tnbLib::abort(FatalError);
	}
	return {};
}

gp_Parab2d 
tnbLib::Pln_CascadeTools::CreateParabola
(
	const gp_Ax2d & theMirrorAxis, 
	const Standard_Real theFocalLength
)
{
	try {
		return { theMirrorAxis, theFocalLength };
	}
	catch (const Standard_ConstructionError& err) {
		FatalErrorIn(FunctionSIG) << "\n"
			<< "Couldn't construct the parabola.\n"
			<< err.GetMessageString() << "\n"
			<< tnbLib::abort(FatalError);
	}
	return {};
}

gp_Parab2d 
tnbLib::Pln_CascadeTools::CreateParabola
(
	const gp_Ax2d & theMirrorAxis,
	const Pnt2d & theFocus
)
{
	try {
		return { theMirrorAxis, theFocus };
	}
	catch (const Standard_ConstructionError& err) {
		FatalErrorIn(FunctionSIG) << "\n"
			<< "Couldn't construct the parabola.\n"
			<< err.GetMessageString() << "\n"
			<< tnbLib::abort(FatalError);
	}
	return {};
}

#include <opencascade/Geom2dAPI_ProjectPointOnCurve.hxx>
#include <opencascade/gp_Pnt2d.hxx>
#include <opencascade/Geom2d_Curve.hxx>
#include <opencascade/TColgp_Array1OfPnt2d.hxx>


std::pair<tnbLib::Pnt2d, Standard_Real>
tnbLib::Pln_CascadeTools::Project(const Pnt2d& thePnt, const opencascade::handle<Geom2d_Curve>& theGeom)
{
	// Project the point onto the curve
	Geom2dAPI_ProjectPointOnCurve projector;
	projector.Init(thePnt, theGeom);
	if (projector.NbPoints() > 0)
	{
		// Get the projected point
		auto pt = projector.NearestPoint();
		// Get the parameter on the curve
		auto p = projector.LowerDistanceParameter();
		return { pt, p };
	}
	FatalErrorIn(FunctionSIG) << endl
		<< " couldn't calculate the projected point!" << endl
		<< abort(FatalError);
	return { Pnt2d::null, 0 };
}
