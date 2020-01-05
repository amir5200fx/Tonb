#include <transformList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template <class T>
tnbLib::List<T> tnbLib::transform
(
	const tensor& rotTensor,
	const UList<T>& field
)
{
	List<T> newField(field.size());

	forAll(field, i)
	{
		newField[i] = transform(rotTensor, field[i]);
	}

	return newField;
}


template <class T>
void tnbLib::transformList
(
	const tensorField& rotTensor,
	UList<T>& field
)
{
	if (rotTensor.size() == 1)
	{
		forAll(field, i)
		{
			field[i] = transform(rotTensor[0], field[i]);
		}
	}
	else if (rotTensor.size() == field.size())
	{
		forAll(field, i)
		{
			field[i] = transform(rotTensor[i], field[i]);
		}
	}
	else
	{
		FatalErrorIn
		(
			"transformList(const tensorField&, UList<T>&)"
		) << "Sizes of field and transformation not equal. field:"
			<< field.size() << " transformation:" << rotTensor.size()
			<< abort(FatalError);
	}
}


template <class T>
void tnbLib::transformList
(
	const tensorField& rotTensor,
	Map<T>& field
)
{
	if (rotTensor.size() == 1)
	{
		forAllIter(typename Map<T>, field, iter)
		{
			iter() = transform(rotTensor[0], iter());
		}
	}
	else
	{
		FatalErrorIn
		(
			"transformList(const tensorField&, Map<T>&)"
		) << "Multiple transformation tensors not supported. field:"
			<< field.size() << " transformation:" << rotTensor.size()
			<< abort(FatalError);
	}
}


template <class T>
void tnbLib::transformList
(
	const tensorField& rotTensor,
	EdgeMap<T>& field
)
{
	if (rotTensor.size() == 1)
	{
		forAllIter(typename EdgeMap<T>, field, iter)
		{
			iter() = transform(rotTensor[0], iter());
		}
	}
	else
	{
		FatalErrorIn
		(
			"transformList(const tensorField&, EdgeMap<T>&)"
		) << "Multiple transformation tensors not supported. field:"
			<< field.size() << " transformation:" << rotTensor.size()
			<< abort(FatalError);
	}
}


// ************************************************************************* //