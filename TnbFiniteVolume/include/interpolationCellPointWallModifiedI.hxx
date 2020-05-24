#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
inline Type tnbLib::interpolationCellPointWallModified<Type>::interpolate
(
	const cellPointWeightWallModified& cpw
) const
{
	const FixedList<scalar, 4>& weights = cpw.weights();
	const FixedList<label, 3>& faceVertices = cpw.faceVertices();

	Type t = this->psip_[faceVertices[0]] * weights[0];
	t += this->psip_[faceVertices[1]] * weights[1];
	t += this->psip_[faceVertices[2]] * weights[2];
	t += this->psi_[cpw.cell()] * weights[3];

	return t;
}


template<class Type>
inline Type tnbLib::interpolationCellPointWallModified<Type>::interpolate
(
	const vector& position,
	const label celli,
	const label facei
) const
{
	return
		interpolate
		(
			cellPointWeightWallModified
			(
				this->pMesh_,
				position,
				celli,
				facei
			)
		);
}


// ************************************************************************* //