#include <SectPx_Pnt_Empty.hxx>

#include <SectPx_MasterPnt.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::sectPxLib::Pnt_Empty::typeName_ = "pnt_empty";

tnbLib::sectPxLib::Pnt_Empty::Pnt_Empty
(
	const std::shared_ptr<SectPx_MasterPnt>& theMaster
)
	: theMaster_(theMaster)
{
	// empty body
}

tnbLib::sectPxLib::Pnt_Empty::Pnt_Empty
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<SectPx_MasterPnt>& theMaster
)
	: SectPx_SlavePnt(theIndex)
	, theMaster_(theMaster)
{
	// empty body
}

tnbLib::sectPxLib::Pnt_Empty::Pnt_Empty
(
	const Standard_Integer theIndex,
	const word & theName,
	const std::shared_ptr<SectPx_MasterPnt>& theMaster
)
	: SectPx_SlavePnt(theIndex, theName)
	, theMaster_(theMaster)
{
	// empty body
}

tnbLib::word 
tnbLib::sectPxLib::Pnt_Empty::RegObjTypeName() const
{
	return typeName_;
}

void tnbLib::sectPxLib::Pnt_Empty::SetMaster
(
	const std::shared_ptr<SectPx_MasterPnt>& theMaster
)
{
	theMaster_ = theMaster;
}

Standard_Real
tnbLib::sectPxLib::Pnt_Empty::xCoord() const
{
	if (NOT theMaster_)
	{
		FatalErrorIn(FunctionSIG)
			<< "the Pnt_Empty doesn't have any master" << endl
			<< abort(FatalError);
	}
	return theMaster_->xCoord();
}

Standard_Real 
tnbLib::sectPxLib::Pnt_Empty::yCoord() const
{
	if (NOT theMaster_)
	{
		FatalErrorIn(FunctionSIG)
			<< "the Pnt_Empty doesn't have any master" << endl
			<< abort(FatalError);
	}
	return theMaster_->yCoord();
}

tnbLib::Pnt2d tnbLib::sectPxLib::Pnt_Empty::Coord() const
{
	if (NOT theMaster_)
	{
		FatalErrorIn(FunctionSIG)
			<< "the Pnt_Empty doesn't have any master" << endl
			<< abort(FatalError);
	}
	return theMaster_->Coord();
}

Standard_Boolean
tnbLib::sectPxLib::Pnt_Empty::IsComplete() const
{
	return (Standard_Boolean)theMaster_;
}

typename tnbLib::sectPxLib::pntType 
tnbLib::sectPxLib::Pnt_Empty::PntType() const
{
	return sectPxLib::pntType::empty;
}

Standard_Boolean 
tnbLib::sectPxLib::Pnt_Empty::IsEmpty() const
{
	return Standard_True;
}

Standard_Integer 
tnbLib::sectPxLib::Pnt_Empty::NbChildMaps() const
{
	return 1;
}

Standard_Boolean 
tnbLib::sectPxLib::Pnt_Empty::HasChildMap() const
{
	return Standard_True;
}

Standard_Boolean
tnbLib::sectPxLib::Pnt_Empty::HasChild
(
	const std::shared_ptr<SectPx_Par>& thePar
) const
{
	return Standard_False;
}

std::shared_ptr<tnbLib::SectPx_Parent> 
tnbLib::sectPxLib::Pnt_Empty::ChildMap
(
	const Standard_Integer theIndex
) const
{
	Debug_If_Condition_Message(theIndex, "invalid index");
	return Master();
}

void tnbLib::sectPxLib::Pnt_Empty::RemoveThisFromChilds() const
{
	//- empty body
}

void tnbLib::sectPxLib::Pnt_Empty::AddThisToChilds() const
{
	//- empty body
}

void tnbLib::sectPxLib::Pnt_Empty::RemoveThisFromChild
(
	const std::shared_ptr<SectPx_Par>& thePar
) const
{
	//- empty body
}

void tnbLib::sectPxLib::Pnt_Empty::AddThisToChild
(
	const std::shared_ptr<SectPx_Par>& thePar
) const
{
	//- empty body
}