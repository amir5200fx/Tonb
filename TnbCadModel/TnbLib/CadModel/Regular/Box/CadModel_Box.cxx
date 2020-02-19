#include <CadModel_Box.hxx>

#include <Pnt3d.hxx>
#include <BRepPrimAPI_MakeBox.hxx>

tnbLib::CadModel_Box::CadModel_Box
(
	const Pnt3d & theP0,
	const Pnt3d & theP1
)
{
	ChangeMaker() =
		std::make_shared<BRepPrimAPI_MakeBox>(theP0, theP1);

	ChangeEntity() = Maker()->Shape();
	ChangePreviewEntity() = Entity();

	Change_IsDone() = Standard_True;
}

tnbLib::CadModel_Box::CadModel_Box
(
	const Pnt3d & theP0, 
	const Standard_Real dx,
	const Standard_Real dy, 
	const Standard_Real dz
)
{
	ChangeMaker() =
		std::make_shared<BRepPrimAPI_MakeBox>(theP0, dx, dy, dz);

	ChangeEntity() = Maker()->Shape();
	ChangePreviewEntity() = Entity();

	Change_IsDone() = Standard_True;
}

tnbLib::CadModel_Box::CadModel_Box
(
	const gp_Ax2 & Axes, 
	const Standard_Real dx, 
	const Standard_Real dy, 
	const Standard_Real dz
)
{
	ChangeMaker() =
		std::make_shared<BRepPrimAPI_MakeBox>(Axes, dx, dy, dz);

	ChangeEntity() = Maker()->Shape();
	ChangePreviewEntity() = Entity();

	Change_IsDone() = Standard_True;
}