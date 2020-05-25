#include <RodriguesRotation.hxx>

#include <mathematicalConstants.hxx>
#include <vectorField.hxx>
#include <Identity.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::tensor tnbLib::RodriguesRotation
(
	const vector& rotationAxis,
	const scalar& rotationAngle,
	const bool inDegrees
)
{
	tensor rotTensor;
	scalar theta = rotationAngle;

	if (inDegrees)
	{
		theta *= mathematicalConstant::pi / 180.0;
	}

	scalar sinTheta = sin(theta);
	scalar cosTheta = cos(theta);
	scalar oneMinusCosTheta = 1.0 - cosTheta;

	scalar magRotAxis = mag(rotationAxis);

	if (magRotAxis < SMALL)
	{
		FatalErrorIn
		(
			"tensor RodriguesRotation\n"
			"(\n"
			"    const vector& rotationAxis,\n"
			"    const scalar& rotationAngle\n"
			")"
		) << "Incorrectly defined axis: " << rotationAxis
			<< abort(FatalError);
	}

	vector unitVector = rotationAxis / magRotAxis;

	scalar wx = unitVector.x();
	scalar wy = unitVector.y();
	scalar wz = unitVector.z();

	rotTensor.xx() = cosTheta + sqr(wx)*oneMinusCosTheta;
	rotTensor.yy() = cosTheta + sqr(wy)*oneMinusCosTheta;
	rotTensor.zz() = cosTheta + sqr(wz)*oneMinusCosTheta;

	rotTensor.xy() = wx * wy*oneMinusCosTheta - wz * sinTheta;
	rotTensor.xz() = wy * sinTheta + wx * wz*oneMinusCosTheta;

	rotTensor.yx() = wz * sinTheta + wx * wy*oneMinusCosTheta;
	rotTensor.yz() = -wx * sinTheta + wy * wz*oneMinusCosTheta;

	rotTensor.zx() = -wy * sinTheta + wx * wz*oneMinusCosTheta;
	rotTensor.zy() = wx * sinTheta + wy * wz*oneMinusCosTheta;

	return rotTensor;
}

tnbLib::tensor tnbLib::RodriguesRotation2
(
	const vector& rotationAxis,
	const scalar& rotationAngle,
	const bool inDegrees
)
{
	scalar magRotAxis = mag(rotationAxis);

	if (magRotAxis < SMALL)
	{
		FatalErrorIn
		(
			"tensor RodriguesRotation2\n"
			"(\n"
			"    const vector& rotationAxis,\n"
			"    const scalar& rotationAngle\n"
			")"
		) << "Incorrectly defined axis: " << rotationAxis
			<< abort(FatalError);
	}

	scalar theta = rotationAngle;

	if (inDegrees)
	{
		theta *= mathematicalConstant::pi / 180.0;
	}

	const vector k = rotationAxis / magRotAxis;
	const scalar k1 = k[0];
	const scalar k2 = k[1];
	const scalar k3 = k[2];

	// [k]_x
	const tensor rotationT(
		0, -k3, k2,
		k3, 0, -k1,
		-k2, k1, 0
	);

	// kk' - I
	const tensor projectionT(
		k1*k1 - 1.0, k1*k2, k1*k3,
		k2*k1, k2*k2 - 1.0, k2*k3,
		k3*k1, k3*k2, k3*k3 - 1.0);

	const scalar cosTheta = cos(theta);
	const scalar sinTheta = sin(theta);

	return I + sinTheta * rotationT + (1 - cosTheta)*projectionT;

}

tnbLib::tensor tnbLib::RodriguesRotation
(
	const vector& rotationAxis,
	const vector& vi,
	const vector& vf
)
{
	scalar magRotAxis = mag(rotationAxis);

	if (magRotAxis < SMALL)
	{
		FatalErrorIn
		(
			"tensor RodriguesRotation\n"
			"(\n"
			"    const vector& rotationAxis,\n"
			"    const vector& vi\n"
			"    const vector& vf\n"
			")"
		) << "Incorrectly defined axis: " << rotationAxis
			<< abort(FatalError);
	}

	const vector k = rotationAxis / magRotAxis;
	const scalar k1 = k[0];
	const scalar k2 = k[1];
	const scalar k3 = k[2];

	// [k]_x
	const tensor rotationT(
		0, -k3, k2,
		k3, 0, -k1,
		-k2, k1, 0
	);

	// kk' - I
	const tensor projectionT(
		k1*k1 - 1.0, k1*k2, k1*k3,
		k2*k1, k2*k2 - 1.0, k2*k3,
		k3*k1, k3*k2, k3*k3 - 1.0);

	// Project both vectors onto the plane defined by the rotation axis
	vector nvi = -(projectionT & vi);
	vector nvf = -(projectionT & vf);
	nvi = nvi / mag(nvi);
	nvf = nvf / mag(nvf);

	const vector crossNviNvf = nvi ^ nvf;
	const scalar cosTheta = nvi & nvf;
	const scalar sinTheta = mag(crossNviNvf) * sign(crossNviNvf & k);

	return I + sinTheta * rotationT + (1 - cosTheta)*projectionT;
}

tnbLib::tensorField tnbLib::RodriguesRotation
(
	const vector& rotationAxis,
	const vectorField& vi,
	const vectorField& vf
)
{
	scalar magRotAxis = mag(rotationAxis);

	if (magRotAxis < SMALL)
	{
		FatalErrorIn
		(
			"tensor RodriguesRotation\n"
			"(\n"
			"    const vector& rotationAxis,\n"
			"    const vectorField& vi\n"
			"    const vectorField& vf\n"
			")"
		) << "Incorrectly defined axis: " << rotationAxis
			<< abort(FatalError);
	}

	const vector k = rotationAxis / magRotAxis;
	const scalar k1 = k[0];
	const scalar k2 = k[1];
	const scalar k3 = k[2];

	// [k]_x
	const tensor rotationT(
		0, -k3, k2,
		k3, 0, -k1,
		-k2, k1, 0
	);

	// kk' - I
	const tensor projectionT(
		k1*k1 - 1.0, k1*k2, k1*k3,
		k2*k1, k2*k2 - 1.0, k2*k3,
		k3*k1, k3*k2, k3*k3 - 1.0);

	// Project both vectors onto the plane defined by the rotation axis
	vectorField nvi = -(projectionT & vi);
	vectorField nvf = -(projectionT & vf);
	nvi = nvi / mag(nvi);
	nvf = nvf / mag(nvf);

	const vectorField crossNviNvf = nvi ^ nvf;
	const scalarField cosTheta = nvi & nvf;
	const scalarField sinTheta = mag(crossNviNvf) * sign(crossNviNvf & k);

	const tensorField I_F(vi.size(), I);
	const tensorField rotationT_F(vi.size(), rotationT);
	const tensorField projectionT_F(vi.size(), projectionT);

	return I_F + sinTheta * rotationT_F + (1 - cosTheta)*projectionT_F;
}


// ************************************************************************* //