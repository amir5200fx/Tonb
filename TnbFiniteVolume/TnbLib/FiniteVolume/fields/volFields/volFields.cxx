#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	defineTemplateTypeNameAndDebug(volScalarField::DimensionedInternalField, 0);
	defineTemplateTypeNameAndDebug(volVectorField::DimensionedInternalField, 0);
	defineTemplateTypeNameAndDebug(volSphericalTensorField::DimensionedInternalField, 0);
	defineTemplateTypeNameAndDebug(volSymmTensorField::DimensionedInternalField, 0);
	defineTemplateTypeNameAndDebug(volSymmTensor4thOrderField::DimensionedInternalField, 0);
	defineTemplateTypeNameAndDebug(volDiagTensorField::DimensionedInternalField, 0);
	defineTemplateTypeNameAndDebug(volTensorField::DimensionedInternalField, 0);

	defineTemplateTypeNameAndDebug(volScalarField, 0);
	defineTemplateTypeNameAndDebug(volVectorField, 0);
	defineTemplateTypeNameAndDebug(volSphericalTensorField, 0);
	defineTemplateTypeNameAndDebug(volSymmTensorField, 0);
	defineTemplateTypeNameAndDebug(volSymmTensor4thOrderField, 0);
	defineTemplateTypeNameAndDebug(volDiagTensorField, 0);
	defineTemplateTypeNameAndDebug(volTensorField, 0);

	template<>
	tmp<GeometricField<scalar, fvPatchField, volMesh> >
		GeometricField<scalar, fvPatchField, volMesh>::component
		(
			const direction
		) const
	{
		return *this;
	}

	template<>
	void GeometricField<scalar, fvPatchField, volMesh>::replace
	(
		const direction,
		const GeometricField<scalar, fvPatchField, volMesh>& gsf
	)
	{
		*this == gsf;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //