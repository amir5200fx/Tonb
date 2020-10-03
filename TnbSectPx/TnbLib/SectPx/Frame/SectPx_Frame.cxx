#include <SectPx_Frame.hxx>

#include <SectPx_Registry.hxx>
#include <SectPx_Makers.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::SectPx_Frame::EntityMaker::EntityMaker
(
	const std::shared_ptr<SectPx_Registry>& theReg
)
{
	Par = std::make_shared<maker::Parameter>(theReg);
	Debug_Null_Pointer(Par);

	Pnt = std::make_shared<maker::Point>(theReg);
	Debug_Null_Pointer(Pnt);

	GeoMap = std::make_shared<maker::GeometricMap>(theReg);
	Debug_Null_Pointer(GeoMap);

	CmptProfile = std::make_shared<maker::CmptProfile>(theReg);
	Debug_Null_Pointer(CmptProfile);
}

void tnbLib::SectPx_Frame::AllocateMemory()
{
	theRegistry_ = std::make_shared<SectPx_Registry>();
	Debug_Null_Pointer(theRegistry_);

	theMakers_ = std::make_shared<EntityMaker>(theRegistry_);
	Debug_Null_Pointer(theMakers_);
}