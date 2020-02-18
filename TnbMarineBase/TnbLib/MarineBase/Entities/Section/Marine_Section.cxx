#include <Marine_Section.hxx>

#include <Pln_Wire.hxx>
#include <error.hxx>
#include <OSstream.hxx>

void tnbLib::Marine_Section::CheckWire(const Pln_Wire& theWire, const char * theName)
{
	if (theWire.Orientation() NOT_EQUAL Pln_Orientation_CCW)
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
	const word & theName,
	const std::shared_ptr<Pln_Wire>& theWire
)
	: Marine_Entity(theIndex, theName)
	, theWire_(theWire)
{
	Debug_Null_Pointer(Wire());
	CheckWire(*Wire(), "Marine_Section::Marine_Section(const std::shared_ptr<Pln_Wire>& theWire)");
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