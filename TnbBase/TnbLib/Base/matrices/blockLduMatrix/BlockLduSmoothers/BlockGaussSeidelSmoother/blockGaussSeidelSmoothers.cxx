#include <blockGaussSeidelSmoothers.hxx>

#include <blockLduSmoothers.hxx>
#include <blockLduMatrices.hxx>
#include <addToRunTimeSelectionTable.hxx>

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	template <>
	const ::tnbLib::word blockGaussSeidelSmootherScalar::typeName(blockGaussSeidelSmootherScalar::typeName_());
	template <>
	::tnbLib::debug::debugSwitch blockGaussSeidelSmootherScalar::debug(
		std::string(blockGaussSeidelSmootherScalar::typeName_()), 0, "");;
	blockScalarSmoother::adddictionaryConstructorToTable<blockGaussSeidelSmootherScalar>
	addblockGaussSeidelSmootherScalardictionaryConstructorToblockScalarSmootherTable_;;
	template <>
	const ::tnbLib::word blockGaussSeidelSmootherVector::typeName(blockGaussSeidelSmootherVector::typeName_());
	template <>
	::tnbLib::debug::debugSwitch blockGaussSeidelSmootherVector::debug(
		std::string(blockGaussSeidelSmootherVector::typeName_()), 0, "");;
	blockVectorSmoother::adddictionaryConstructorToTable<blockGaussSeidelSmootherVector>
	addblockGaussSeidelSmootherVectordictionaryConstructorToblockVectorSmootherTable_;;
	template <>
	const ::tnbLib::word blockGaussSeidelSmootherTensor::typeName(blockGaussSeidelSmootherTensor::typeName_());
	template <>
	::tnbLib::debug::debugSwitch blockGaussSeidelSmootherTensor::debug(
		std::string(blockGaussSeidelSmootherTensor::typeName_()), 0, "");;
	blockTensorSmoother::adddictionaryConstructorToTable<blockGaussSeidelSmootherTensor>
	addblockGaussSeidelSmootherTensordictionaryConstructorToblockTensorSmootherTable_;;;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //