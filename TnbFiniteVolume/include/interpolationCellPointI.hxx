#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
inline Type tnbLib::interpolationCellPoint<Type>::interpolate
(
	const cellPointWeight& cpw
) const
{
	const FixedList<scalar, 4>& weights = cpw.weights();
	const FixedList<label, 3>& faceVertices = cpw.faceVertices();

	Type t = psip_[faceVertices[0]] * weights[0];
	t += psip_[faceVertices[1]] * weights[1];
	t += psip_[faceVertices[2]] * weights[2];
	t += this->psi_[cpw.cell()] * weights[3];

	return t;
}


template<class Type>
inline Type tnbLib::interpolationCellPoint<Type>::interpolate
(
	const vector& position,
	const label celli,
	const label facei
) const
{
	return interpolate(cellPointWeight(this->pMesh_, position, celli, facei));
}


// ************************************************************************* //
