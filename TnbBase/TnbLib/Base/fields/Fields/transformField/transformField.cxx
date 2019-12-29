#include <transformField.hxx>

#include <FieldM.hxx>
#include <FieldReuseFunctions.hxx>
#include <diagTensor.hxx>

// * * * * * * * * * * * * * * * global functions  * * * * * * * * * * * * * //

void tnbLib::transform
(
	vectorField& rtf,
	const quaternion& q,
	const vectorField& tf
)
{
	tensor t = q.R();
	TFOR_ALL_F_OP_FUNC_S_F(vector, rtf, =, transform, tensor, t, vector, tf)
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::transform
(
	const quaternion& q,
	const vectorField& tf
)
{
	tmp<vectorField > tranf(new vectorField(tf.size()));
	transform(tranf(), q, tf);
	return tranf;
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::transform
(
	const quaternion& q,
	const tmp<vectorField>& ttf
)
{
	tmp<vectorField > tranf = reuseTmp<vector, vector>::New(ttf);
	transform(tranf(), q, ttf());
	reuseTmp<vector, vector>::clear(ttf);
	return tranf;
}


void tnbLib::transform
(
	vectorField& rtf,
	const septernion& tr,
	const vectorField& tf
)
{
	vector T = tr.t();

	// Check if any rotation
	if (mag(tr.r().R() - I) > SMALL)
	{
		transform(rtf, tr.r(), tf);

		if (mag(T) > VSMALL)
		{
			rtf += T;
		}
	}
	else
	{
		if (mag(T) > VSMALL)
		{
			TFOR_ALL_F_OP_S_OP_F(vector, rtf, =, vector, T, +, vector, tf);
		}
		else
		{
			rtf = tf;
		}
	}
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::transform
(
	const septernion& tr,
	const vectorField& tf
)
{
	tmp<vectorField > tranf(new vectorField(tf.size()));
	transform(tranf(), tr, tf);
	return tranf;
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::transform
(
	const septernion& tr,
	const tmp<vectorField>& ttf
)
{
	tmp<vectorField > tranf = reuseTmp<vector, vector>::New(ttf);
	transform(tranf(), tr, ttf());
	reuseTmp<vector, vector>::clear(ttf);
	return tranf;
}


// ************************************************************************* //