#include <Vec2d.hxx>

#include <Dir2d.hxx>

const tnbLib::Vec2d tnbLib::Vec2d::null((Standard_Real)1., (Standard_Real)0.);

tnbLib::Vec2d::Vec2d
(
	const Dir2d & V
)
	: gp_Vec2d(V.XY())
{}