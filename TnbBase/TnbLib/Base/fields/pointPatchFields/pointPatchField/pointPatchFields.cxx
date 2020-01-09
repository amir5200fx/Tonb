#include <pointPatchFields.hxx>

#include <fieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	typedef PointPatchField
		<pointPatchField, pointMesh, pointPatch, DummyMatrix, scalar>
		basePointPatchScalarField;

	typedef PointPatchField
		<pointPatchField, pointMesh, pointPatch, DummyMatrix, vector>
		basePointPatchVectorField;

	typedef PointPatchField
		<pointPatchField, pointMesh, pointPatch, DummyMatrix, sphericalTensor>
		basePointPatchSphericalTensorField;

	typedef PointPatchField
		<pointPatchField, pointMesh, pointPatch, DummyMatrix, symmTensor>
		basePointPatchSymmTensorField;

	typedef PointPatchField
		<pointPatchField, pointMesh, pointPatch, DummyMatrix, symmTensor4thOrder>
		basePointPatchSymmTensor4thOrderField;

	typedef PointPatchField
		<pointPatchField, pointMesh, pointPatch, DummyMatrix, diagTensor>
		basePointPatchDiagTensorField;

	typedef PointPatchField
		<pointPatchField, pointMesh, pointPatch, DummyMatrix, tensor>
		basePointPatchTensorField;

	defineNamedTemplateTypeNameAndDebug(basePointPatchScalarField, 0);
	defineTemplateRunTimeSelectionTable(basePointPatchScalarField, PointPatch);
	defineTemplateRunTimeSelectionTable(basePointPatchScalarField, patchMapper);
	defineTemplateRunTimeSelectionTable(basePointPatchScalarField, dictionary);

	defineNamedTemplateTypeNameAndDebug(basePointPatchVectorField, 0);
	defineTemplateRunTimeSelectionTable(basePointPatchVectorField, PointPatch);
	defineTemplateRunTimeSelectionTable(basePointPatchVectorField, patchMapper);
	defineTemplateRunTimeSelectionTable(basePointPatchVectorField, dictionary);

	defineNamedTemplateTypeNameAndDebug(basePointPatchSphericalTensorField, 0);
	defineTemplateRunTimeSelectionTable(basePointPatchSphericalTensorField, PointPatch);
	defineTemplateRunTimeSelectionTable(basePointPatchSphericalTensorField, patchMapper);
	defineTemplateRunTimeSelectionTable(basePointPatchSphericalTensorField, dictionary);

	defineNamedTemplateTypeNameAndDebug(basePointPatchSymmTensorField, 0);
	defineTemplateRunTimeSelectionTable(basePointPatchSymmTensorField, PointPatch);
	defineTemplateRunTimeSelectionTable(basePointPatchSymmTensorField, patchMapper);
	defineTemplateRunTimeSelectionTable(basePointPatchSymmTensorField, dictionary);

	defineNamedTemplateTypeNameAndDebug(basePointPatchSymmTensor4thOrderField, 0);
	defineTemplateRunTimeSelectionTable(basePointPatchSymmTensor4thOrderField, PointPatch);
	defineTemplateRunTimeSelectionTable(basePointPatchSymmTensor4thOrderField, patchMapper);
	defineTemplateRunTimeSelectionTable(basePointPatchSymmTensor4thOrderField, dictionary);

	defineNamedTemplateTypeNameAndDebug(basePointPatchDiagTensorField, 0);
	defineTemplateRunTimeSelectionTable(basePointPatchDiagTensorField, PointPatch);
	defineTemplateRunTimeSelectionTable(basePointPatchDiagTensorField, patchMapper);
	defineTemplateRunTimeSelectionTable(basePointPatchDiagTensorField, dictionary);

	defineNamedTemplateTypeNameAndDebug(basePointPatchTensorField, 0);
	defineTemplateRunTimeSelectionTable(basePointPatchTensorField, PointPatch);
	defineTemplateRunTimeSelectionTable(basePointPatchTensorField, patchMapper);
	defineTemplateRunTimeSelectionTable(basePointPatchTensorField, dictionary);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //