#include <Dir3d.hxx>

#include <Pnt3d.hxx>

const tnbLib::Dir3d tnbLib::Dir3d::null(1.0, 0, 0);

tnbLib::Dir3d::Dir3d
(
	const Pnt3d & theP0,
	const Pnt3d & theP1
)
{
	auto v = theP1 - theP0;
	*this = Dir3d(v.XYZ());
}

//TNB_SAVE_IMPLEMENTATION(tnbLib::Dir3d)
//{
//	ar << X();
//	ar << Y();
//	ar << Z();
//}
//
//TNB_LOAD_IMPLEMENTATION(tnbLib::Dir3d)
//{
//	Standard_Real x, y, z;
//	ar >> x;
//	ar >> y;
//	ar >> z;
//	SetX(x);
//	SetY(y);
//	SetZ(z);
//}