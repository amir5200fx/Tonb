#include <SectPx_Node.hxx>

const char* tnbLib::SectPx_Node::typeName_("node");

tnbLib::SectPx_Node::SectPx_Node
(
	const std::shared_ptr<SectPx_Pnt>& thePnt
)
	: thePnt_(thePnt)
{
	//- empty body
}

tnbLib::SectPx_Node::SectPx_Node
(
	const Standard_Integer theIndex,
	const std::shared_ptr<SectPx_Pnt>& thePnt
)
	: thePnt_(thePnt)
	, SectPx_RegObj(theIndex)
{
	//- empty body
}

tnbLib::SectPx_Node::SectPx_Node
(
	const Standard_Integer theIndex, 
	const word & theName,
	const std::shared_ptr<SectPx_Pnt>& thePnt
)
	: thePnt_(thePnt)
	, SectPx_RegObj(theIndex, theName)
{
	//- empty body
}

tnbLib::word 
tnbLib::SectPx_Node::RegObjTypeName() const
{
	return typeName_;
}

Standard_Boolean 
tnbLib::SectPx_Node::IsNode() const
{
	return Standard_True;
}

tnbLib::sectPxLib::regObjType 
tnbLib::SectPx_Node::RegObjType() const
{
	return sectPxLib::regObjType::node;
}