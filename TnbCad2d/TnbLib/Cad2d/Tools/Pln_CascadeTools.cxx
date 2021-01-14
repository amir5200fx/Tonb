#include <Pln_CascadeTools.hxx>

#include <Pnt2d.hxx>

#include <gp_Ax2d.hxx>
#include <gp_Circ2d.hxx>
#include <gp_Elips2d.hxx>
#include <gp_Hypr2d.hxx>
#include <gp_Parab2d.hxx>

gp_Circ2d 
tnbLib::Pln_CascadeTools::CreateCircle
(
	const gp_Ax2d & theAx, 
	const Standard_Real theRadius
)
{
	gp_Circ2d c(theAx, theRadius);
	return std::move(c);
}

gp_Elips2d 
tnbLib::Pln_CascadeTools::CreateEllipse
(
	const gp_Ax2d & theMajorAx, 
	const Standard_Real theMajorRadius,
	const Standard_Real theMinorRadius
)
{
	gp_Elips2d e(theMajorAx, theMajorRadius, theMinorRadius);
	return std::move(e);
}

gp_Hypr2d 
tnbLib::Pln_CascadeTools::CreateHyperbola
(
	const gp_Ax2d & theMajorAxis, 
	const Standard_Real theMajorRadius, 
	const Standard_Real theMinorRadius
)
{
	gp_Hypr2d h(theMajorAxis, theMajorRadius, theMinorRadius);
	return std::move(h);
}

gp_Parab2d 
tnbLib::Pln_CascadeTools::CreateParabola
(
	const gp_Ax2d & theMirrorAxis, 
	const Standard_Real theFocalLength
)
{
	gp_Parab2d p(theMirrorAxis, theFocalLength);
	return std::move(p);
}

gp_Parab2d 
tnbLib::Pln_CascadeTools::CreateParabola
(
	const gp_Ax2d & theMirrorAxis,
	const Pnt2d & theFocus
)
{
	gp_Parab2d p(theMirrorAxis, theFocus);
	return std::move(p);
}