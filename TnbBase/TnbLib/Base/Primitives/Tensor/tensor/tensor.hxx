#pragma once
#ifndef _tensor_Header
#define _tensor_Header

#include <TensorTemplate.hxx>
#include <vector.hxx>
#include <sphericalTensor.hxx>
#include <symmTensor.hxx>
#include <contiguous.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	typedef Tensor<scalar> tensor;

	vector eigenValues(const tensor& T);
	vector eigenVector
	(
		const tensor& T,
		const scalar lambda,
		const vector& direction1,
		const vector& direction2
	);
	tensor eigenVectors(const tensor& T, const vector& lambdas);
	tensor eigenVectors(const tensor& T);

	vector eigenValues(const symmTensor& T);
	vector eigenVector
	(
		const symmTensor& T,
		const scalar lambda,
		const vector& direction1,
		const vector& direction2
	);
	tensor eigenVectors(const symmTensor& T, const vector& lambdas);
	tensor eigenVectors(const symmTensor& T);

	//- Data associated with tensor type are contiguous
	template<>
	inline bool contiguous<tensor>() { return true; }


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_tensor_Header
