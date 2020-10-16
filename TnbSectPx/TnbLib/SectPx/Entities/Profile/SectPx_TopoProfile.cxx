#include <SectPx_TopoProfile.hxx>

#include <SectPx_Node.hxx>
#include <SectPx_InterfaceMaker.hxx>
#include <SectPx_PntTools.hxx>
#include <SectPx_Pnt.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::SectPx_TopoProfile::SectPx_TopoProfile
(
	const std::shared_ptr<SectPx_Node>& theNode0, 
	const std::shared_ptr<SectPx_Node>& theNode1
)
	: theNode0_(theNode0)
	, theNode1_(theNode1)
	, SectPx_RegObj(0, "topoProfile")
{
	//- empty body
}

tnbLib::SectPx_TopoProfile::SectPx_TopoProfile
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<SectPx_Node>& theNode0,
	const std::shared_ptr<SectPx_Node>& theNode1
)
	: theNode0_(theNode0)
	, theNode1_(theNode1)
	, SectPx_RegObj(theIndex, "topoProfile")
{
	//- empty body
}

tnbLib::SectPx_TopoProfile::SectPx_TopoProfile
(
	const Standard_Integer theIndex,
	const word & theName, 
	const std::shared_ptr<SectPx_Node>& theNode0,
	const std::shared_ptr<SectPx_Node>& theNode1
)
	: theNode0_(theNode0)
	, theNode1_(theNode1)
	, SectPx_RegObj(theIndex, theName)
{
	//- empty body
}

void tnbLib::SectPx_TopoProfile::SetProfile
(
	const std::shared_ptr<SectPx_Node>& theNode,
	const std::shared_ptr<SectPx_TopoProfile>& theProfile
)
{
	Debug_Null_Pointer(theNode);
	Debug_Null_Pointer(theProfile);
	theNode->SetProfile(theProfile);
}

std::vector<tnbLib::Pnt2d> 
tnbLib::SectPx_TopoProfile::RetrieveCoords() const
{
	Update();

	auto pnts = SectPx_PntTools::TrackPnts(Node0(), Node1());

	std::vector<Pnt2d> coords;
	coords.reserve(pnts.size());
	for (const auto& x : pnts)
	{
		auto coord = x->Coord();
		coords.push_back(std::move(coord));
	}
	return std::move(coords);
}

tnbLib::sectPxLib::regObjType
tnbLib::SectPx_TopoProfile::RegObjType() const
{
	return sectPxLib::regObjType::profile;
}

Standard_Boolean
tnbLib::SectPx_TopoProfile::IsProfile() const
{
	return Standard_True;
}
