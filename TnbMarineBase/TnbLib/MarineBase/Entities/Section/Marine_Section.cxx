#include <Marine_Section.hxx>

#include <Entity2d_Box.hxx>
#include <Pln_Wire.hxx>
#include <error.hxx>
#include <OSstream.hxx>

void tnbLib::Marine_Section::CheckWire(const Pln_Wire& theWire, const char * theName)
{
	if (theWire.Orientation() NOT_EQUAL Pln_Orientation::Pln_Orientation_CCW)
	{
		FatalErrorIn(theName)
			<< "the wire must be ccw" << endl
			<< abort(FatalError);
	}
}

tnbLib::Marine_Section::Marine_Section
(
	const std::shared_ptr<Pln_Wire>& theWire
)
	: theWire_(theWire)
{
	Debug_Null_Pointer(Wire());
	CheckWire(*Wire(), "Marine_Section::Marine_Section(const std::shared_ptr<Pln_Wire>& theWire)");
}

tnbLib::Marine_Section::Marine_Section
(
	const std::shared_ptr<Pln_Wire>&& theWire
)
	: theWire_(std::move(theWire))
{
	Debug_Null_Pointer(Wire());
	CheckWire(*Wire(), "Marine_Section::Marine_Section(const std::shared_ptr<Pln_Wire>& theWire)");
}

tnbLib::Marine_Section::Marine_Section
(
	const Standard_Integer theIndex,
	const std::shared_ptr<Pln_Wire>& theWire
)
	: Marine_Entity(theIndex)
	, theWire_(theWire)
{
	Debug_Null_Pointer(Wire());
	CheckWire(*Wire(), "Marine_Section::Marine_Section(const std::shared_ptr<Pln_Wire>& theWire)");
}

tnbLib::Marine_Section::Marine_Section
(
	const Standard_Integer theIndex,
	const std::shared_ptr<Pln_Wire>&& theWire
)
	: Marine_Entity(theIndex)
	, theWire_(theWire)
{
	Debug_Null_Pointer(Wire());
	CheckWire(*Wire(), "Marine_Section::Marine_Section(const std::shared_ptr<Pln_Wire>& theWire)");
}

tnbLib::Marine_Section::Marine_Section
(
	const Standard_Integer theIndex, 
	const word & theName,
	const std::shared_ptr<Pln_Wire>& theWire
)
	: Marine_Entity(theIndex, theName)
	, theWire_(theWire)
{
	Debug_Null_Pointer(Wire());
	CheckWire(*Wire(), "Marine_Section::Marine_Section(const std::shared_ptr<Pln_Wire>& theWire)");
}

tnbLib::Marine_Section::Marine_Section
(
	const Standard_Integer theIndex,
	const word & theName,
	const std::shared_ptr<Pln_Wire>&& theWire
)
	: Marine_Entity(theIndex, theName)
	, theWire_(theWire)
{
	Debug_Null_Pointer(Wire());
	CheckWire(*Wire(), "Marine_Section::Marine_Section(const std::shared_ptr<Pln_Wire>& theWire)");
}

tnbLib::Entity2d_Box 
tnbLib::Marine_Section::BoundingBox() const
{
	Debug_Null_Pointer(Wire());
	return Wire()->BoundingBox(0);
}

void tnbLib::Marine_Section::Transform
(
	const gp_Trsf2d & t
)
{
	Wire()->Transform(t);
	CoordinateSystem().Transform(t);
}

void tnbLib::Marine_Section::ExportToPlt
(
	OFstream & File
) const
{
	Wire()->ExportToPlt(File);
}

Standard_Real 
tnbLib::Marine_Section::GetXcoord
(
	const std::shared_ptr<Marine_Section>& theSection
)
{
	Debug_Null_Pointer(theSection);
	return theSection->CoordinateSystem().Location().X();
}

//std::shared_ptr<tnbLib::Marine_Section> 
//tnbLib::Marine_Section::Copy() const
//{
//	auto wire = std::dynamic_pointer_cast<Pln_Wire>(Wire()->Copy());
//	Debug_Null_Pointer(wire);
//
//	auto copy = std::make_shared<Marine_Section>(Index(), Name(), wire);
//	Debug_Null_Pointer(copy);
//
//	return std::move(copy);
//}