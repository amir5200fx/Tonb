#include <IOLongList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class T, label Offset>
	IOLongList<T, Offset>::IOLongList(const IOobject& io)
		:
		regIOobject(io),
		LongList<T, Offset>()
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


	template<class T, label Offset>
	IOLongList<T, Offset>::IOLongList
	(
		const IOobject& io,
		const label size
	)
		:
		regIOobject(io),
		LongList<T, Offset>(size)
	{}


	template<class T, label Offset>
	IOLongList<T, Offset>::IOLongList
	(
		const IOobject& io,
		const LongList<T, Offset>& list
	)
		:
		regIOobject(io),
		LongList<T, Offset>()
	{
		if (io.readOpt() == IOobject::READ_IF_PRESENT && headerOk())
		{
			readStream(typeName) >> *this;
			close();
		}

		LongList<T, Offset>::operator=(list);
	}


	template<class T, label Offset>
	void IOLongList<T, Offset>::operator=
		(
			const IOLongList<T, Offset>& rhs
			)
	{
		LongList<T, Offset>::operator=(rhs);
	}


	template<class T, label Offset>
	void IOLongList<T, Offset>::operator=
		(
			const LongList<T, Offset>& rhs
			)
	{
		LongList<T, Offset>::operator=(rhs);
	}


	template<class T, label Offset>
	bool IOLongList<T, Offset>::writeData(Ostream& os) const
	{
		return (os << *this).good();
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //