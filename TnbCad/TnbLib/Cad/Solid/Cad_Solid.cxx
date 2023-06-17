#include <Cad_Solid.hxx>

#include <Cad_tModelMaker.hxx>
#include <Cad_Tools.hxx>

tnbLib::Cad_Solid::Cad_Solid(const TopoDS_Shape& theShape)
{
	SetShape(theShape);
	Check();
}

tnbLib::Cad_Solid::Cad_Solid
(
	const Standard_Integer theIndex,
	const word& theName,
	const TopoDS_Shape& theShape
)
	: Cad_TModel(theIndex, theName)
{
	SetShape(theShape);
	Check();
}

void tnbLib::Cad_Solid::Check()
{
	Cad_Tools::CheckSolid(Shape());
}

Standard_Real 
tnbLib::Cad_Solid::CalcVolume() const
{
	return Cad_Tools::CalcVolume(Shape());
}

std::shared_ptr<tnbLib::Cad_Solid> 
tnbLib::Cad_Solid::MakeSolid
(
	const TopoDS_Shape& theShape,
	const MakerInfo& theInfo
)
{
	auto myInfo = 
		std::make_shared<Cad_tModelMaker::MakerInfo>
		(theInfo.modelInfo, theInfo.edgeInfo, theInfo.surfInfo);
	Cad_tModelMaker maker{ theShape, myInfo, theInfo.pairCrit };
	maker.MakeSolid();
	auto model = std::dynamic_pointer_cast<Cad_Solid>(maker.Model());
	Debug_Null_Pointer(model);
	return std::move(model);
}