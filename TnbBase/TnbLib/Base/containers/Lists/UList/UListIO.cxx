#include <UList.hxx>

#include <Ostream.hxx>
#include <token.hxx>
#include <contiguous.hxx>

// * * * * * * * * * * * * * * * Ostream Operator *  * * * * * * * * * * * * //

template<class T>
void tnbLib::UList<T>::writeEntry(Ostream& os) const
{
	if
		(
			size()
			&& token::compound::isCompound
			(
				"List<" + word(pTraits<T>::typeName) + '>'
			)
			)
	{
		os << word("List<" + word(pTraits<T>::typeName) + '>') << " ";
	}

	os << *this;
}


template<class T>
void tnbLib::UList<T>::writeEntry(const word& keyword, Ostream& os) const
{
	os.writeKeyword(keyword);
	writeEntry(os);
	os << token::END_STATEMENT << endl;
}


template<class T>
tnbLib::Ostream& tnbLib::operator<<(tnbLib::Ostream& os, const tnbLib::UList<T>& L)
{
	// Write list contents depending on data format
	if (os.format() == IOstream::ASCII || !contiguous<T>())
	{
		bool uniform = false;

		if (L.size() > 1 && contiguous<T>())
		{
			uniform = true;

			forAll(L, i)
			{
				if (L[i] != L[0])
				{
					uniform = false;
					break;
				}
			}
		}

		if (uniform)
		{
			// Write size and start delimiter
			os << L.size() << token::BEGIN_BLOCK;

			// Write contents
			os << L[0];

			// Write end delimiter
			os << token::END_BLOCK;
		}
		else if (L.size() < 11 && contiguous<T>())
		{
			// Write size and start delimiter
			os << L.size() << token::BEGIN_LIST;

			// Write contents
			forAll(L, i)
			{
				if (i > 0) os << token::SPACE;
				os << L[i];
			}

			// Write end delimiter
			os << token::END_LIST;
		}
		else
		{
			// Write size and start delimiter
			os << nl << L.size() << nl << token::BEGIN_LIST;

			// Write contents
			forAll(L, i)
			{
				os << nl << L[i];
			}

			// Write end delimiter
			os << nl << token::END_LIST << nl;
		}
	}
	else
	{
		os << nl << L.size() << nl;
		if (L.size())
		{
			os.write(reinterpret_cast<const char*>(L.v_), L.byteSize());
		}
	}

	// Check state of IOstream
	os.check("Ostream& operator<<(Ostream&, const UList&)");

	return os;
}


// ************************************************************************* //