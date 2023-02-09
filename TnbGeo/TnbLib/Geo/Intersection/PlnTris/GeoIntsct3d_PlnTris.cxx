#include <GeoIntsct3d_PlnTris.hxx>

#include <Entity3d_Triangulation.hxx>
#include <Entity3d_Triangle.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <gp_Pln.hxx>

const unsigned short tnbLib::GeoIntsct3d_PlnTris::pntIntsct::nbPoints = 1;
const unsigned short tnbLib::GeoIntsct3d_PlnTris::segIntsct::nbPoints = 2;
const unsigned short tnbLib::GeoIntsct3d_PlnTris::triIntsct::nbPoints = 3;

const std::string tnbLib::GeoIntsct3d_PlnTris::intsctEntity::extension = ".gIntsctPlnTris";

Standard_Boolean 
tnbLib::GeoIntsct3d_PlnTris::intsctEntity::IsPoint() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::GeoIntsct3d_PlnTris::intsctEntity::IsSegment() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::GeoIntsct3d_PlnTris::intsctEntity::IsTriangle() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::GeoIntsct3d_PlnTris::pntIntsct::IsPoint() const
{
	return Standard_True;
}

Standard_Integer 
tnbLib::GeoIntsct3d_PlnTris::pntIntsct::NbPoints() const
{
	return (Standard_Integer)nbPoints;
}

tnbLib::Pnt3d 
tnbLib::GeoIntsct3d_PlnTris::pntIntsct::Point(const Standard_Integer /*theIndex*/) const
{
	return theCoord_;
}

std::vector<tnbLib::Pnt3d>
tnbLib::GeoIntsct3d_PlnTris::pntIntsct::RetrievePoints() const
{
	std::vector<Pnt3d> coords = { Coord() };
	return std::move(coords);
}

void tnbLib::GeoIntsct3d_PlnTris::pntIntsct::SetCoord(const Pnt3d& theCoord)
{
	theCoord_ = theCoord;
}

void tnbLib::GeoIntsct3d_PlnTris::pntIntsct::SetCoord(Pnt3d&& theCoord)
{
	theCoord_ = std::move(theCoord);
}

Standard_Boolean 
tnbLib::GeoIntsct3d_PlnTris::segIntsct::IsSegment() const
{
	return Standard_True;
}

Standard_Integer 
tnbLib::GeoIntsct3d_PlnTris::segIntsct::NbPoints() const
{
	return Standard_Integer(nbPoints);
}

tnbLib::Pnt3d 
tnbLib::GeoIntsct3d_PlnTris::segIntsct::Point(const Standard_Integer theIndex) const
{
	return Coords().at(theIndex);
}

std::vector<tnbLib::Pnt3d> 
tnbLib::GeoIntsct3d_PlnTris::segIntsct::RetrievePoints() const
{
	std::vector<Pnt3d> coords = { P0(), P1() };
	return std::move(coords);
}

void tnbLib::GeoIntsct3d_PlnTris::segIntsct::SetP0(const Pnt3d& theCoord)
{
	std::get<0>(theCoords_) = theCoord;
}

void tnbLib::GeoIntsct3d_PlnTris::segIntsct::SetP0(Pnt3d&& theCoord)
{
	std::get<0>(theCoords_) = std::move(theCoord);
}

void tnbLib::GeoIntsct3d_PlnTris::segIntsct::SetP1(const Pnt3d& theCoord)
{
	std::get<1>(theCoords_) = theCoord;
}

void tnbLib::GeoIntsct3d_PlnTris::segIntsct::SetP1(Pnt3d&& theCoord)
{
	std::get<1>(theCoords_) = std::move(theCoord);
}

Standard_Boolean 
tnbLib::GeoIntsct3d_PlnTris::triIntsct::IsTriangle() const
{
	return Standard_True;
}

Standard_Integer 
tnbLib::GeoIntsct3d_PlnTris::triIntsct::NbPoints() const
{
	return Standard_Integer(nbPoints);
}

tnbLib::Pnt3d 
tnbLib::GeoIntsct3d_PlnTris::triIntsct::Point(const Standard_Integer theIndex) const
{
	return Coords().at(theIndex);
}

std::vector<tnbLib::Pnt3d> 
tnbLib::GeoIntsct3d_PlnTris::triIntsct::RetrievePoints() const
{
	std::vector<Pnt3d> coords = { P0(), P1(), P2() };
	return std::move(coords);
}

void tnbLib::GeoIntsct3d_PlnTris::triIntsct::SetP0(const Pnt3d& theCoord)
{
	std::get<0>(theCoords_) = theCoord;
}

void tnbLib::GeoIntsct3d_PlnTris::triIntsct::SetP0(Pnt3d&& theCoord)
{
	std::get<0>(theCoords_) = std::move(theCoord);
}

void tnbLib::GeoIntsct3d_PlnTris::triIntsct::SetP1(const Pnt3d& theCoord)
{
	std::get<1>(theCoords_) = theCoord;
}

void tnbLib::GeoIntsct3d_PlnTris::triIntsct::SetP1(Pnt3d&& theCoord)
{
	std::get<1>(theCoords_) = std::move(theCoord);
}

void tnbLib::GeoIntsct3d_PlnTris::triIntsct::SetP2(const Pnt3d& theCoord)
{
	std::get<2>(theCoords_) = theCoord;
}

void tnbLib::GeoIntsct3d_PlnTris::triIntsct::SetP2(Pnt3d&& theCoord)
{
	std::get<2>(theCoords_) = std::move(theCoord);
}

const std::vector<std::shared_ptr<tnbLib::GeoIntsct3d_PlnTris::intsctEntity>>&
tnbLib::GeoIntsct3d_PlnTris::Entities() const
{
	CheckDone((*this));
	return theEntities_;
}

void tnbLib::GeoIntsct3d_PlnTris::Perform()
{
	if (NOT Plane())
	{
		FatalErrorIn(FunctionSIG)
			<< "no plane has been loaded." << endl
			<< abort(FatalError);
	}
	if (NOT Mesh())
	{
		FatalErrorIn(FunctionSIG)
			<< "no mesh has been loaded." << endl
			<< abort(FatalError);
	}

	auto ents = CalcIntersections(*Plane(), *Mesh());
	theEntities_ = std::move(ents);

	Change_IsDone() = Standard_True;
}

void tnbLib::GeoIntsct3d_PlnTris::SetPlane(const std::shared_ptr<gp_Pln>& thePlane)
{
	thePlane_ = thePlane;
}

void tnbLib::GeoIntsct3d_PlnTris::SetMesh(const std::shared_ptr<Entity3d_Triangulation>& theMesh)
{
	theMesh_ = theMesh;
}