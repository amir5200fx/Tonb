#include <StbGMaker_GeometricSailCreator_Plane.hxx>

tnbLib::stbGmakerLib::GeometricSailCreator_Plane::GeometricSailCreator_Plane
(
	const std::shared_ptr<Cad2d_Plane>& thePlane
)
	: thePlane_(thePlane)
{
	// empty body
}

tnbLib::stbGmakerLib::GeometricSailCreator_Plane::GeometricSailCreator_Plane
(
	std::shared_ptr<Cad2d_Plane>&& thePlane
)
	: thePlane_(std::move(thePlane))
{
	// empty body
}

tnbLib::stbGmakerLib::GeometricSailCreator_Plane::GeometricSailCreator_Plane
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<Cad2d_Plane>& thePlane
)
	: StbGMaker_GeometricSailCreator(theIndex)
	, thePlane_(thePlane)
{
	// empty body
}

tnbLib::stbGmakerLib::GeometricSailCreator_Plane::GeometricSailCreator_Plane
(
	const Standard_Integer theIndex,
	std::shared_ptr<Cad2d_Plane>&& thePlane
)
	: StbGMaker_GeometricSailCreator(theIndex)
	, thePlane_(std::move(thePlane))
{
	// empty body
}

tnbLib::stbGmakerLib::GeometricSailCreator_Plane::GeometricSailCreator_Plane
(
	const Standard_Integer theIndex,
	const word & theName, 
	const std::shared_ptr<Cad2d_Plane>& thePlane
)
	: StbGMaker_GeometricSailCreator(theIndex, theName)
	, thePlane_(thePlane)
{
	// empty body
}

tnbLib::stbGmakerLib::GeometricSailCreator_Plane::GeometricSailCreator_Plane
(
	const Standard_Integer theIndex, 
	const word & theName,
	std::shared_ptr<Cad2d_Plane>&& thePlane
)
	: StbGMaker_GeometricSailCreator(theIndex, theName)
	, thePlane_(std::move(thePlane))
{
	// empty body
}

typename tnbLib::stbGmakerLib::sailCreatorType 
tnbLib::stbGmakerLib::GeometricSailCreator_Plane::Type() const
{
	return stbGmakerLib::sailCreatorType::plane;
}

#include <Marine_Models.hxx>

void tnbLib::stbGmakerLib::GeometricSailCreator_Plane::ExportAs
(
	std::shared_ptr<Marine_Model>& theModel
) const
{
	theModel = 
		std::make_shared<marineLib::Model_LateralPlnSail>
		(
			Index(), Name(),
			Plane()
			);
}