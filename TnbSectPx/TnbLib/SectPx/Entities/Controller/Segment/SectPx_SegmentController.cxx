#include <SectPx_SegmentController.hxx>

#include <SectPx_Segment.hxx>
#include <SectPx_CPtsMap.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::SectPx_SegmentController::typeName_("segment controller");

tnbLib::SectPx_SegmentController::SectPx_SegmentController
(
	const Standard_Integer theIndex
)
	: SectPx_Controller(theIndex)
{
	// empty body
}

tnbLib::SectPx_SegmentController::SectPx_SegmentController
(
	const Standard_Integer theIndex,
	const word & theName
)
	: SectPx_Controller(theIndex, theName)
{
	// empty body
}

void tnbLib::SectPx_SegmentController::SetCPts
(
	const std::shared_ptr<SectPx_CPtsMap>& theCPts
)
{
	Debug_Null_Pointer(theCPts);
	const auto& segment = theCPts->Segment();

	if (segment->Controller().lock())
	{
		FatalErrorIn(FunctionSIG)
			<< "the segment already has a controller!" << endl
			<< abort(FatalError);
	}

	segment->SetController(std::dynamic_pointer_cast<SectPx_SegmentController>(This()));

	theCPts_ = theCPts;
}

tnbLib::word 
tnbLib::SectPx_SegmentController::RegObjTypeName() const
{
	return typeName_;
}

Standard_Boolean 
tnbLib::SectPx_SegmentController::IsOnSegment() const
{
	return Standard_True;
}

Standard_Integer 
tnbLib::SectPx_SegmentController::NbChildMaps() const
{
	return 1;
}

Standard_Boolean 
tnbLib::SectPx_SegmentController::HasChildMap() const
{
	return Standard_True;
}

Standard_Boolean 
tnbLib::SectPx_SegmentController::HasChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	return Standard_False;
}

std::shared_ptr<tnbLib::SectPx_Parent>
tnbLib::SectPx_SegmentController::ChildMap
(
	const Standard_Integer theIndex
) const
{
	Debug_If_Condition_Message(!theIndex, "invalid index");
	return CPts();
}

void tnbLib::SectPx_SegmentController::RemoveThisFromChildren() const
{
	// empty body
}

void tnbLib::SectPx_SegmentController::AddThisToChildren() const
{
	 // empty body
}

void tnbLib::SectPx_SegmentController::RemoveThisFromChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	 // empty body
}

void tnbLib::SectPx_SegmentController::AddThisToChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	// empty body
}