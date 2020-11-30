#include <SectPx_Edge.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::SectPx_Edge::typeName_("edge");

tnbLib::SectPx_Edge::SectPx_Edge
(
	const std::shared_ptr<SectPx_Pnt>& theP0,
	const std::shared_ptr<SectPx_Pnt>& theP1
)
	: theP0_(theP0)
	, theP1_(theP1)
{
}

tnbLib::SectPx_Edge::SectPx_Edge
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<SectPx_Pnt>& theP0, 
	const std::shared_ptr<SectPx_Pnt>& theP1
)
	: SectPx_RegObj(theIndex)
	, theP0_(theP0)
	, theP1_(theP1)
{
}

tnbLib::SectPx_Edge::SectPx_Edge
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const std::shared_ptr<SectPx_Pnt>& theP0,
	const std::shared_ptr<SectPx_Pnt>& theP1
)
	: SectPx_RegObj(theIndex, theName)
	, theP0_(theP0)
	, theP1_(theP1)
{
}

Standard_Integer 
tnbLib::SectPx_Edge::IndexOf
(
	const std::shared_ptr<SectPx_Pnt>& thePnt
) const
{
	if (theP0_ IS_EQUAL thePnt)
	{
		return 0;
	}
	else if (theP1_ IS_EQUAL thePnt)
	{
		return 1;
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "the pnt is not belong to the edge" << endl
			<< abort(FatalError);
		return 0;
	}
}

std::shared_ptr<tnbLib::SectPx_Pnt> 
tnbLib::SectPx_Edge::Point
(
	const Standard_Integer theIndex
) const
{
#ifdef _DEBUG
	if (NOT INSIDE(theIndex, 0, 1))
	{
		FatalErrorIn(FunctionSIG)
			<< "bad index: " << theIndex << endl
			<< " the valid index must be 0 or 1" << endl
			<< abort(FatalError);
	}
#endif // _DEBUG

	return (&theP0_)[theIndex];
}

std::shared_ptr<tnbLib::SectPx_Pnt> 
tnbLib::SectPx_Edge::Other
(
	const std::shared_ptr<SectPx_Pnt>& thePnt
) const
{
	const auto& p0 = theP0_;
	Debug_Null_Pointer(p0);

	if (thePnt IS_EQUAL p0)
	{
		return theP1_;
	}
	else
	{
#ifdef _DEBUG	
		const auto& p1 = theP1_;
		if (thePnt NOT_EQUAL p1)
		{
			FatalErrorIn(FunctionSIG)
				<< "the pnt is not belong to the segment!" << endl
				<< abort(FatalError);
		}
#endif // _DEBUG
		return theP0_;
	}
}

tnbLib::word 
tnbLib::SectPx_Edge::RegObjTypeName() const
{
	return typeName_;
}

typename tnbLib::sectPxLib::regObjType 
tnbLib::SectPx_Edge::RegObjType() const
{
	return sectPxLib::regObjType::edge;
}

Standard_Boolean 
tnbLib::SectPx_Edge::IsEdge() const
{
	return Standard_True;
}

Standard_Boolean 
tnbLib::SectPx_Edge::IsFrameRegObj() const
{
	return Standard_True;
}