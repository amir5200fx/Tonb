#include <PtdModel_Shape_PropBladeParent.hxx>

tnbLib::ptdModel::Shape_PropBladeParent::Shape_PropBladeParent
(
	const std::shared_ptr<PtdModel_BladeGlobalPars>& theInfo,
	const std::shared_ptr<Cad_Shape>& theShape,
	const std::vector<std::shared_ptr<PtdModel_Face>>& theFaces
)
	: Shape_PropBlade(theShape)
	, theInfo_(theInfo)
	, theFaces_(theFaces)
	, theAx_(gp::XOY())
{
	//- empty body
}

tnbLib::ptdModel::Shape_PropBladeParent::Shape_PropBladeParent
(
	std::shared_ptr<PtdModel_BladeGlobalPars>&& theInfo,
	std::shared_ptr<Cad_Shape>&& theShape,
	std::vector<std::shared_ptr<PtdModel_Face>>&& theFaces
)
	: Shape_PropBlade(std::move(theShape))
	, theInfo_(std::move(theInfo))
	, theFaces_(std::move(theFaces))
	, theAx_(gp::XOY())
{
	//- empty body
}

tnbLib::ptdModel::Shape_PropBladeParent::Shape_PropBladeParent
(
	const Standard_Integer theIndex,
	const word& theName,
	const std::shared_ptr<PtdModel_BladeGlobalPars>& theInfo,
	const std::shared_ptr<Cad_Shape>& theShape,
	const std::vector<std::shared_ptr<PtdModel_Face>>& theFaces
)
	: Shape_PropBlade(theIndex, theName, theShape)
	, theInfo_(theInfo)
	, theFaces_(theFaces)
	, theAx_(gp::XOY())
{
	//- empty body
}

tnbLib::ptdModel::Shape_PropBladeParent::Shape_PropBladeParent
(
	const Standard_Integer theIndex,
	const word& theName,
	std::shared_ptr<PtdModel_BladeGlobalPars>&& theInfo,
	std::shared_ptr<Cad_Shape>&& theShape,
	std::vector<std::shared_ptr<PtdModel_Face>>&& theFaces
)
	: Shape_PropBlade(theIndex, theName, std::move(theShape))
	, theInfo_(std::move(theInfo))
	, theFaces_(std::move(theFaces))
	, theAx_(gp::XOY())
{
	//- empty body
}

void tnbLib::ptdModel::Shape_PropBladeParent::SetInfo(const std::shared_ptr<PtdModel_BladeGlobalPars>& theInfo)
{
	theInfo_ = theInfo;
}

void tnbLib::ptdModel::Shape_PropBladeParent::SetInfo(std::shared_ptr<PtdModel_BladeGlobalPars>&& theInfo)
{
	theInfo_ = std::move(theInfo);
}

void tnbLib::ptdModel::Shape_PropBladeParent::SetFaces(const std::vector<std::shared_ptr<PtdModel_Face>>& theFaces)
{
	theFaces_ = theFaces;
}

void tnbLib::ptdModel::Shape_PropBladeParent::SetFaces(std::vector<std::shared_ptr<PtdModel_Face>>&& theFaces)
{
	theFaces_ = std::move(theFaces);
}

void tnbLib::ptdModel::Shape_PropBladeParent::SetAxis(const gp_Ax2 & theAx)
{
	theAx_ = theAx;
}