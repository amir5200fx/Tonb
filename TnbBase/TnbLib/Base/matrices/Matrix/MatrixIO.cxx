#include <Matrix.hxx>

#include <Istream.hxx>
#include <Ostream.hxx>
#include <token.hxx>
#include <contiguous.hxx>

// * * * * * * * * * * * * * * * Ostream Operator *  * * * * * * * * * * * * //

template<class Form, class Type>
tnbLib::Matrix<Form, Type>::Matrix(Istream& is)
	:
	v_(NULL),
	n_(0),
	m_(0)
{
	operator>>(is, *this);
}


template<class Form, class Type>
tnbLib::Istream& tnbLib::operator>>(Istream& is, Matrix<Form, Type>& M)
{
	// Anull matrix
	M.clear();

	is.fatalCheck("operator>>(Istream&, Matrix<Form, Type>&)");

	token firstToken(is);

	is.fatalCheck("operator>>(Istream&, Matrix<Form, Type>&) : reading first token");

	if (firstToken.isLabel())
	{
		M.n_ = firstToken.labelToken();
		M.m_ = readLabel(is);

		label nm = M.n_*M.m_;

		// Read list contents depending on data format
		if (is.format() == IOstream::ASCII || !contiguous<Type>())
		{
			// Read beginning of contents
			char listDelimiter = is.readBeginList("Matrix");

			if (nm)
			{
				M.allocate();
				Type* v = M.v_[0];

				if (listDelimiter == token::BEGIN_LIST)
				{
					label k = 0;

					// loop over rows
					for (register label i = 0; i < M.n(); i++)
					{
						listDelimiter = is.readBeginList("MatrixRow");

						for (register label j = 0; j < M.m(); j++)
						{
							is >> v[k++];

							is.fatalCheck
							(
								"operator>>(Istream&, Matrix<Form, Type>&) : "
								"reading entry"
							);
						}

						is.readEndList("MatrixRow");
					}
				}
				else
				{
					Type element;
					is >> element;

					is.fatalCheck
					(
						"operator>>(Istream&, Matrix<Form, Type>&) : "
						"reading the single entry"
					);

					for (register label i = 0; i < nm; i++)
					{
						v[i] = element;
					}
				}
			}

			// Read end of contents
			is.readEndList("Matrix");
		}
		else
		{
			if (nm)
			{
				M.allocate();
				Type* v = M.v_[0];

				is.read(reinterpret_cast<char*>(v), nm * sizeof(Type));

				is.fatalCheck
				(
					"operator>>(Istream&, Matrix<Form, Type>&) : "
					"reading the binary block"
				);
			}
		}
	}
	else
	{
		FatalIOErrorIn("operator>>(Istream&, Matrix<Form, Type>&)", is)
			<< "incorrect first token, expected <int>, found "
			<< firstToken.info()
			<< exit(FatalIOError);
	}

	return is;
}


template<class Form, class Type>
tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const Matrix<Form, Type>& M)
{
	label nm = M.n_*M.m_;

	os << M.n() << token::SPACE << M.m();

	// Write list contents depending on data format
	if (os.format() == IOstream::ASCII || !contiguous<Type>())
	{
		if (nm)
		{
			bool uniform = false;

			const Type* v = M.v_[0];

			if (nm > 1 && contiguous<Type>())
			{
				uniform = true;

				for (register label i = 0; i < nm; i++)
				{
					if (v[i] != v[0])
					{
						uniform = false;
						break;
					}
				}
			}

			if (uniform)
			{
				// Write size of list and start contents delimiter
				os << token::BEGIN_BLOCK;

				// Write list contents
				os << v[0];

				// Write end of contents delimiter
				os << token::END_BLOCK;
			}
			// Fix: matrices smaller than 20x20 will be written square.
			// HJ, 22/Jan/2009
			else if (nm < 400 && contiguous<Type>())
			{
				// Write size of list and start contents delimiter
				os << token::BEGIN_LIST;

				label k = 0;

				// loop over rows
				for (register label i = 0; i < M.n(); i++)
				{
					os << nl << token::BEGIN_LIST;

					// Write row
					for (register label j = 0; j < M.m(); j++)
					{
						if (j > 0) os << token::SPACE;
						os << v[k++];
					}

					os << token::END_LIST;
				}

				// Write end of contents delimiter
				os << token::END_LIST;
			}
			else
			{
				// Write size of list and start contents delimiter
				os << nl << token::BEGIN_LIST;

				label k = 0;

				// loop over rows
				for (register label i = 0; i < M.n(); i++)
				{
					os << nl << token::BEGIN_LIST;

					// Write row
					for (register label j = 0; j < M.m(); j++)
					{
						os << nl << v[k++];
					}

					os << nl << token::END_LIST;
				}

				// Write end of contents delimiter
				os << nl << token::END_LIST << nl;
			}
		}
		else
		{
			os << token::BEGIN_LIST << token::END_LIST << nl;
		}
	}
	else
	{
		if (nm)
		{
			os.write(reinterpret_cast<const char*>(M.v_[0]), nm * sizeof(Type));
		}
	}

	// Check state of IOstream
	os.check("Ostream& operator<<(Ostream&, const Matrix&)");

	return os;
}


// ************************************************************************* //