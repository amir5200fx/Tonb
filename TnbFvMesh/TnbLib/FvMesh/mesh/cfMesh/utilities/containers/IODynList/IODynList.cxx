#include <IODynList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class T, label staticSize>
	IODynList<T, staticSize>::IODynList(const IOobject& io)
		:
		regIOobject(io),
		DynList<T, staticSize>()
	{
		if
			(
				io.readOpt() == IOobject::MUST_READ
				|| (io.readOpt() == IOobject::READ_IF_PRESENT && headerOk())
				)
		{
			readStream(typeName) >> *this;
			close();
		}
	}


	template<class T, label staticSize>
	IODynList<T, staticSize>::IODynList
	(
		const IOobject& io,
		const label size
	)
		:
		regIOobject(io),
		DynList<T, staticSize>(size)
	{}


	template<class T, label staticSize>
	IODynList<T, staticSize>::IODynList
	(
		const IOobject& io,
		const DynList<T, staticSize>& list
	)
		:
		regIOobject(io),
		DynList<T, staticSize>()
	{
		if (io.readOpt() == IOobject::READ_IF_PRESENT && headerOk())
		{
			readStream(typeName) >> *this;
			close();
		}

		DynList<T, staticSize>::operator=(list);
	}


	template<class T, label staticSize>
	void IODynList<T, staticSize>::operator=
		(
			const IODynList<T, staticSize>& rhs
			)
	{
		DynList<T, staticSize>::operator=(rhs);
	}


	template<class T, label staticSize>
	void IODynList<T, staticSize>::operator=
		(
			const DynList<T, staticSize>& rhs
			)
	{
		DynList<T, staticSize>::operator=(rhs);
	}


	template<class T, label staticSize>
	bool IODynList<T, staticSize>::writeData(Ostream& os) const
	{
		return (os << *this).good();
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //