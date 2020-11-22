#include <StbGMaker_AreaSailCreator_Const.hxx>

tnbLib::stbGmakerLib::AreaSailCreator_Const::AreaSailCreator_Const
(
	const Standard_Real theArea, 
	const Standard_Real theZbar
)
	: theArea_(theArea)
	, theZbar_(theZbar)
{
	// empty body
}

tnbLib::stbGmakerLib::AreaSailCreator_Const::AreaSailCreator_Const
(
	const Standard_Integer theIndex,
	const Standard_Real theArea,
	const Standard_Real theZbar
)
	: StbGMaker_AreaSailCreator(theIndex)
	, theArea_(theArea)
	, theZbar_(theZbar)
{
	// empty body
}

tnbLib::stbGmakerLib::AreaSailCreator_Const::AreaSailCreator_Const
(
	const Standard_Integer theIndex, 
	const word & theName,
	const Standard_Real theArea,
	const Standard_Real theZbar
)
	: StbGMaker_AreaSailCreator(theIndex, theName)
	, theArea_(theArea)
	, theZbar_(theZbar)
{
	// empty body
}

typename tnbLib::stbGmakerLib::sailCreatorType 
tnbLib::stbGmakerLib::AreaSailCreator_Const::Type() const
{
	return stbGmakerLib::sailCreatorType::constArea;
}

#include <Marine_Models.hxx>

void tnbLib::stbGmakerLib::AreaSailCreator_Const::ExportAs
(
	std::shared_ptr<Marine_Model>& theModel
) const
{
	auto body = 
		std::make_shared<marineLib::Model_ConstAreaSail>
		(
			Index(), Name(),
			Area(), zBar()
			);
	Debug_Null_Pointer(body);
	theModel = std::move(body);
}