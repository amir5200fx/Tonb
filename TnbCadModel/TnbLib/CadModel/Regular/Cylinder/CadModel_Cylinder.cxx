#include <CadModel_Cylinder.hxx>

#include <BRepPrimAPI_MakeCylinder.hxx>

tnbLib::CadModel_Cylinder::CadModel_Cylinder
(
	const gp_Ax2 & Axes,
	const Standard_Real R,
	const Standard_Real H
)
{
	ChangeMaker() = std::make_shared<BRepPrimAPI_MakeCylinder>(Axes, R, H);

	ChangeEntity() = Maker()->Shape();
	ChangePreviewEntity() = Entity();

	Change_IsDone() = Standard_True;
}

tnbLib::CadModel_Cylinder::CadModel_Cylinder
(
	const gp_Ax2 & Axes,
	const Standard_Real R,
	const Standard_Real H,
	const Standard_Real Angle
)
{
	ChangeMaker() = std::make_shared<BRepPrimAPI_MakeCylinder>(Axes, R, H, Angle);

	ChangeEntity() = Maker()->Shape();
	ChangePreviewEntity() = Entity();

	Change_IsDone() = Standard_True;
}