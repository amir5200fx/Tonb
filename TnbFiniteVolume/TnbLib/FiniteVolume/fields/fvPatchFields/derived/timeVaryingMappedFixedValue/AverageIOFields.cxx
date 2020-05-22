#include <AverageIOField.hxx>

#include <fieldTypes.hxx>

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	typedef AverageIOField<scalar> scalarAverageIOField;
	typedef AverageIOField<vector> vectorAverageIOField;
	typedef AverageIOField<sphericalTensor> sphericalTensorAverageIOField;
	typedef AverageIOField<symmTensor> symmTensorAverageIOField;
	typedef AverageIOField<symmTensor4thOrder> symmTensor4thOrderAverageIOField;
	typedef AverageIOField<diagTensor> diagTensorAverageIOField;
	typedef AverageIOField<tensor> tensorAverageIOField;

	defineTemplateTypeNameAndDebugWithName
	(
		scalarAverageIOField,
		"scalarAverageField",
		0
	);
	defineTemplateTypeNameAndDebugWithName
	(
		vectorAverageIOField,
		"vectorAverageField",
		0
	);
	defineTemplateTypeNameAndDebugWithName
	(
		sphericalTensorAverageIOField,
		"sphericalTensorAverageField",
		0
	);
	defineTemplateTypeNameAndDebugWithName
	(
		symmTensorAverageIOField,
		"symmTensorAverageField",
		0
	);
	defineTemplateTypeNameAndDebugWithName
	(
		symmTensor4thOrderAverageIOField,
		"symmTensor4thOrderAverageField",
		0
	);
	defineTemplateTypeNameAndDebugWithName
	(
		diagTensorAverageIOField,
		"diagTensorAverageField",
		0
	);
	defineTemplateTypeNameAndDebugWithName
	(
		tensorAverageIOField,
		"tensorAverageField",
		0
	);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //