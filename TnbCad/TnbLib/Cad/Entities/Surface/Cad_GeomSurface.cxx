#include <Cad_GeomSurface.hxx>

#include <Entity2d_Box.hxx>
#include <Entity3d_Box.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom_BoundedSurface.hxx>

void tnbLib::Cad_GeomSurface::CheckBounded(const Handle(Geom_Surface)& s)
{
	auto bounded = Handle(Geom_BoundedSurface)::DownCast(s);
	if (NOT bounded)
	{
		FatalErrorIn(FunctionSIG)
			<< "the surface is not bounded!" << endl
			<< abort(FatalError);
	}
}

tnbLib::Cad_GeomSurface::Cad_GeomSurface
(
	const Handle(Geom_Surface)& theSurface
)
	: theSurface_(theSurface)
{
	CheckBounded(Geometry());
}

tnbLib::Cad_GeomSurface::Cad_GeomSurface
(
	Handle(Geom_Surface) && theSurface
)
	: theSurface_(std::move(theSurface))
{
	CheckBounded(Geometry());
}

tnbLib::Cad_GeomSurface::Cad_GeomSurface
(
	const Standard_Integer theIndex, 
	const Handle(Geom_Surface)& theSurface
)
	: Global_Indexed(theIndex)
	, theSurface_(theSurface)
{
	CheckBounded(Geometry());
}

tnbLib::Cad_GeomSurface::Cad_GeomSurface
(
	const Standard_Integer theIndex, 
	Handle(Geom_Surface) && theSurface
)
	: Global_Indexed(theIndex)
	, theSurface_(std::move(theSurface))
{
	CheckBounded(Geometry());
}

tnbLib::Cad_GeomSurface::Cad_GeomSurface
(
	const Standard_Integer theIndex, 
	const word & theName,
	const Handle(Geom_Surface)& theSurface
)
	: Global_Indexed(theIndex)
	, Global_Named(theName)
	, theSurface_(theSurface)
{
	CheckBounded(Geometry());
}

tnbLib::Cad_GeomSurface::Cad_GeomSurface
(
	const Standard_Integer theIndex, 
	const word & theName, 
	Handle(Geom_Surface) && theSurface
)
	: Global_Indexed(theIndex)
	, Global_Named(theName)
	, theSurface_(std::move(theSurface))
{
	CheckBounded(Geometry());
}

Standard_Real 
tnbLib::Cad_GeomSurface::FirstParameterU() const
{
	Standard_Real u0, u1, v0, v1;
	theSurface_->Bounds(u0, u1, v0, v1);
	return u0;
}

Standard_Real 
tnbLib::Cad_GeomSurface::LastParameterU() const
{
	Standard_Real u0, u1, v0, v1;
	theSurface_->Bounds(u0, u1, v0, v1);
	return u1;
}

Standard_Real 
tnbLib::Cad_GeomSurface::FirstParameterV() const
{
	Standard_Real u0, u1, v0, v1;
	theSurface_->Bounds(u0, u1, v0, v1);
	return v0;
}

Standard_Real 
tnbLib::Cad_GeomSurface::LastParameterV() const
{
	Standard_Real u0, u1, v0, v1;
	theSurface_->Bounds(u0, u1, v0, v1);
	return v1;
}

tnbLib::Pnt3d 
tnbLib::Cad_GeomSurface::Value
(
	const Standard_Real u, 
	const Standard_Real v
) const
{
	auto p = theSurface_->Value(u, v);
	return std::move(p);
}

tnbLib::Pnt3d 
tnbLib::Cad_GeomSurface::Value(const Pnt2d & v) const
{
	auto p = theSurface_->Value(v.X(), v.Y());
	return std::move(p);
}

tnbLib::Entity2d_Box 
tnbLib::Cad_GeomSurface::ParametricBoundingBox() const
{
	Standard_Real u0, u1, v0, v1;
	theSurface_->Bounds(u0, u1, v0, v1);
	Entity2d_Box b(Pnt2d(u0, v0), Pnt2d(u1, v1));
	return std::move(b);
}