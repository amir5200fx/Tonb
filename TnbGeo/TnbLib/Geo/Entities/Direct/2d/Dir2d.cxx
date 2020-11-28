#include <Dir2d.hxx>

#include <Pnt2d.hxx>

const tnbLib::Dir2d tnbLib::Dir2d::null((Standard_Real)1., (Standard_Real)0.);

tnbLib::Dir2d::Dir2d
(
	const Pnt2d& theP0,
	const Pnt2d& theP1
)
{
	auto v = theP1 - theP0;

	*this = Dir2d(v.X(), v.Y());
}

//TNB_SAVE_IMPLEMENTATION(tnbLib::Dir2d)
//{
//	ar << X();
//	ar << Y();
//}
//
//TNB_LOAD_IMPLEMENTATION(tnbLib::Dir2d)
//{
//	Standard_Real x, y;
//	ar >> x;
//	ar >> y;
//	SetX(x);
//	SetY(y);
//}