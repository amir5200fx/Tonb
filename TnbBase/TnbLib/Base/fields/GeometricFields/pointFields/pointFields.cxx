#include <pointFields.hxx>

#include <polyMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	defineTemplateTypeNameAndDebug(pointScalarField::DimensionedInternalField, 0);
	defineTemplateTypeNameAndDebug(pointVectorField::DimensionedInternalField, 0);
	defineTemplateTypeNameAndDebug(pointSphericalTensorField::DimensionedInternalField, 0);
	defineTemplateTypeNameAndDebug(pointSymmTensorField::DimensionedInternalField, 0);
	defineTemplateTypeNameAndDebug(pointSymmTensor4thOrderField::DimensionedInternalField, 0);
	defineTemplateTypeNameAndDebug(pointDiagTensorField::DimensionedInternalField, 0);
	defineTemplateTypeNameAndDebug(pointTensorField::DimensionedInternalField, 0);

	defineTemplateTypeNameAndDebug(pointScalarField, 0);
	defineTemplateTypeNameAndDebug(pointVectorField, 0);
	defineTemplateTypeNameAndDebug(pointSphericalTensorField, 0);
	defineTemplateTypeNameAndDebug(pointSymmTensorField, 0);
	defineTemplateTypeNameAndDebug(pointSymmTensor4thOrderField, 0);
	defineTemplateTypeNameAndDebug(pointDiagTensorField, 0);
	defineTemplateTypeNameAndDebug(pointTensorField, 0);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //