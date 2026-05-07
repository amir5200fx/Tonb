#include <SectPx_Interface.hxx>

#include <SectPx_EmptyInterface.hxx>



tnbLib::SectPx_Interface::SectPx_Interface
(
	const std::shared_ptr<SectPx_Node>& theNode
)
	: theNode_(theNode)
	, SectPx_RegObj(0, "interface")
{
	//- empty body
}

tnbLib::SectPx_Interface::SectPx_Interface
(
	const Standard_Integer theIndex,
	const std::shared_ptr<SectPx_Node>& theNode
)
	: theNode_(theNode)
	, SectPx_RegObj(theIndex, "interface")
{
	//- empty body
}

tnbLib::SectPx_Interface::SectPx_Interface
(
	const Standard_Integer theIndex,
	const word & theName, 
	const std::shared_ptr<SectPx_Node>& theNode
)
	: theNode_(theNode)
	, SectPx_RegObj(theIndex, theName)
{
	//- empty body
}

Standard_Boolean 
tnbLib::SectPx_Interface::IsEmpty() const
{
	return Standard_False;
}

Standard_Boolean
tnbLib::SectPx_Interface::IsPaired() const
{
	return Standard_False;
}

tnbLib::sectPxLib::regObjType
tnbLib::SectPx_Interface::RegObjType() const
{
	return sectPxLib::regObjType::Interface;
}

Standard_Boolean 
tnbLib::SectPx_Interface::IsInterface() const
{
	return Standard_True;
}

Standard_Boolean 
tnbLib::SectPx_Interface::IsFrameRegObj() const
{
	return Standard_True;
}