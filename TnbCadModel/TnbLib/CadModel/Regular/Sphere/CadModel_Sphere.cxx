#include <CadModel_Sphere.hxx>

#include <BRepPrimAPI_MakeSphere.hxx>

tnbLib::CadModel_Sphere::CadModel_Sphere
(
	const Pnt3d & theCentre, 
	const Standard_Real theRadius
)
{
	ChangeMaker() =
		std::make_shared<BRepPrimAPI_MakeSphere>(theCentre, theRadius);

	ChangeEntity() = Maker()->Shape();
	ChangePreviewEntity() = Entity();

	Change_IsDone() = Standard_True;
}

tnbLib::CadModel_Sphere::CadModel_Sphere
(
	const gp_Ax2 & Axis,
	const Standard_Real theRadius
)
{
	ChangeMaker() =
		std::make_shared<BRepPrimAPI_MakeSphere>(Axis, theRadius);

	ChangeEntity() = Maker()->Shape();
	ChangePreviewEntity() = Entity();

	Change_IsDone() = Standard_True;
}

tnbLib::CadModel_Sphere::CadModel_Sphere
(
	const gp_Ax2 & Axis,
	const Standard_Real theRadius, 
	const Standard_Real angle1
)
{
	ChangeMaker() =
		std::make_shared<BRepPrimAPI_MakeSphere>(Axis, theRadius, angle1);

	ChangeEntity() = Maker()->Shape();
	ChangePreviewEntity() = Entity();

	Change_IsDone() = Standard_True;
}

tnbLib::CadModel_Sphere::CadModel_Sphere
(
	const gp_Ax2 & Axis, 
	const Standard_Real theRadius, 
	const Standard_Real angle1, 
	const Standard_Real angle2
)
{
	ChangeMaker() =
		std::make_shared<BRepPrimAPI_MakeSphere>(Axis, theRadius, angle1, angle2);

	ChangeEntity() = Maker()->Shape();
	ChangePreviewEntity() = Entity();

	Change_IsDone() = Standard_True;
}

tnbLib::CadModel_Sphere::CadModel_Sphere
(
	const gp_Ax2 & Axis,
	const Standard_Real theRadius,
	const Standard_Real angle1, 
	const Standard_Real angle2, 
	const Standard_Real angle3
)
{
	ChangeMaker() =
		std::make_shared<BRepPrimAPI_MakeSphere>(Axis, theRadius, angle1, angle2, angle3);

	ChangeEntity() = Maker()->Shape();
	ChangePreviewEntity() = Entity();

	Change_IsDone() = Standard_True;
}