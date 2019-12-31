#include <List.hxx>

#include <Istream.hxx>
#include <token.hxx>
#include <SLList.hxx>
#include <contiguous.hxx>

// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

// Construct from Istream
template<class T>
tnbLib::List<T>::List(Istream& is)
	:
	UList<T>(NULL, 0)
{
	operator>>(is, *this);
}


template<class T>
tnbLib::Istream& tnbLib::operator>>(Istream& is, List<T>& L)
{
	// Anull list
	L.setSize(0);

	is.fatalCheck("operator>>(Istream&, List<T>&)");

	token firstToken(is);

	is.fatalCheck("operator>>(Istream&, List<T>&) : reading first token");

	if (firstToken.isCompound())
	{
		L.transfer
		(
			dynamicCast<token::Compound<List<T> > >
			(
				firstToken.transferCompoundToken()
				)
		);
	}
	else if (firstToken.isLabel())
	{
		label s = firstToken.labelToken();

		// Set list length to that read
		L.setSize(s);

		// Read list contents depending on data format

		if (is.format() == IOstream::ASCII || !contiguous<T>())
		{
			// Read beginning of contents
			char delimiter = is.readBeginList("List");

			if (s)
			{
				if (delimiter == token::BEGIN_LIST)
				{
					for (register label i = 0; i < s; i++)
					{
						is >> L[i];

						is.fatalCheck
						(
							"operator>>(Istream&, List<T>&) : reading entry"
						);
					}
				}
				else
				{
					T element;
					is >> element;

					is.fatalCheck
					(
						"operator>>(Istream&, List<T>&) : "
						"reading the single entry"
					);

					for (register label i = 0; i < s; i++)
					{
						L[i] = element;
					}
				}
			}

			// Read end of contents
			is.readEndList("List");
		}
		else
		{
			if (s)
			{
				is.read(reinterpret_cast<char*>(L.data()), s * sizeof(T));

				is.fatalCheck
				(
					"operator>>(Istream&, List<T>&) : reading the binary block"
				);
			}
		}
	}
	else if (firstToken.isPunctuation())
	{
		if (firstToken.pToken() != token::BEGIN_LIST)
		{
			FatalIOErrorIn("operator>>(Istream&, List<T>&)", is)
				<< "incorrect first token, expected '(', found "
				<< firstToken.info()
				<< exit(FatalIOError);
		}

		// Putback the openning bracket
		is.putBack(firstToken);

		// Now read as a singly-linked list
		SLList<T> sll(is);

		// Convert the singly-linked list to this list
		L = sll;
	}
	else
	{
		FatalIOErrorIn("operator>>(Istream&, List<T>&)", is)
			<< "incorrect first token, expected <int> or '(', found "
			<< firstToken.info()
			<< exit(FatalIOError);
	}

	return is;
}


template<class T>
tnbLib::List<T> tnbLib::readList(Istream& is)
{
	List<T> L;
	token firstToken(is);
	is.putBack(firstToken);

	if (firstToken.isPunctuation())
	{
		if (firstToken.pToken() != token::BEGIN_LIST)
		{
			FatalIOErrorIn("readList<T>(Istream&)", is)
				<< "incorrect first token, expected '(', found "
				<< firstToken.info()
				<< exit(FatalIOError);
		}

		// read via a singly-linked list
		L = SLList<T>(is);
	}
	else
	{
		// create list with a single item
		L.setSize(1);

		is >> L[0];
	}

	return L;
}


// ************************************************************************* //