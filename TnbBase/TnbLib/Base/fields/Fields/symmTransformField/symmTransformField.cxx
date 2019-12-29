#include <symmTransformField.hxx>

#include <FieldM.hxx>
#include <FieldReuseFunctions.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * global functions  * * * * * * * * * * * * * //

	template<class Type>
	void transform
	(
		Field<Type>& rtf,
		const symmTensorField& trf,
		const Field<Type>& tf
	)
	{
		if (trf.size() == 1)
		{
			return transform(rtf, trf[0], tf);
		}
		else
		{
			TFOR_ALL_F_OP_FUNC_F_F
			(
				Type, rtf, =, transform, symmTensor, trf, Type, tf
			)
		}
	}


	template<class Type>
	tmp<Field<Type> > transform
	(
		const symmTensorField& trf,
		const Field<Type>& tf
	)
	{
		tmp<Field<Type> > tranf(new Field<Type>(tf.size()));
		transform(tranf(), trf, tf);
		return tranf;
	}


	template<class Type>
	tmp<Field<Type> > transform
	(
		const symmTensorField& trf,
		const tmp<Field<Type> >& ttf
	)
	{
		tmp<Field<Type> > tranf = reuseTmp<Type, Type>::New(ttf);
		transform(tranf(), trf, ttf());
		reuseTmp<Type, Type>::clear(ttf);
		return tranf;
	}


	template<class Type>
	tmp<Field<Type> > transform
	(
		const tmp<symmTensorField>& ttrf,
		const Field<Type>& tf
	)
	{
		tmp<Field<Type> > tranf(new Field<Type>(tf.size()));
		transform(tranf(), ttrf(), tf);
		ttrf.clear();
		return tranf;
	}


	template<class Type>
	tmp<Field<Type> > transform
	(
		const tmp<symmTensorField>& ttrf,
		const tmp<Field<Type> >& ttf
	)
	{
		tmp<Field<Type> > tranf = reuseTmp<Type, Type>::New(ttf);
		transform(tranf(), ttrf(), ttf());
		reuseTmp<Type, Type>::clear(ttf);
		ttrf.clear();
		return tranf;
	}


	template<class Type>
	void transform
	(
		Field<Type>& rtf,
		const symmTensor& t,
		const Field<Type>& tf
	)
	{
		TFOR_ALL_F_OP_FUNC_S_F(Type, rtf, =, transform, tensor, t, Type, tf)
	}


	template<class Type>
	tmp<Field<Type> > transform
	(
		const symmTensor& t,
		const Field<Type>& tf
	)
	{
		tmp<Field<Type> > tranf(new Field<Type>(tf.size()));
		transform(tranf(), t, tf);
		return tranf;
	}


	template<class Type>
	tmp<Field<Type> > transform
	(
		const symmTensor& t,
		const tmp<Field<Type> >& ttf
	)
	{
		tmp<Field<Type> > tranf = reuseTmp<Type, Type>::New(ttf);
		transform(tranf(), t, ttf());
		reuseTmp<Type, Type>::clear(ttf);
		return tranf;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //