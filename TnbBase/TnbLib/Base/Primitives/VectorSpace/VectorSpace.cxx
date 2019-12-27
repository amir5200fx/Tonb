#include <VectorSpace.hxx>

#include <IOstreams.hxx>

#include <sstream>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from Istream
template<class Form, class Cmpt, int nCmpt>
tnbLib::VectorSpace<Form, Cmpt, nCmpt>::VectorSpace
(
	Istream& is
)
{
	// Read beginning of VectorSpace<Cmpt>
	is.readBegin("VectorSpace<Form, Cmpt, nCmpt>");

	for (int i = 0; i < nCmpt; i++)
	{
		is >> v_[i];
	}

	// Read end of VectorSpace<Cmpt>
	is.readEnd("VectorSpace<Form, Cmpt, nCmpt>");

	// Check state of Istream
	is.check("VectorSpace<Form, Cmpt, nCmpt>::VectorSpace(Istream&)");
}


// Return a string representation
template<class Form, class Cmpt, int nCmpt>
tnbLib::word tnbLib::name
(
	const VectorSpace<Form, Cmpt, nCmpt>& vs
)
{
	std::ostringstream buf;

	buf << '(';

	for (int i = 0; i < nCmpt - 1; i++)
	{
		buf << vs.v_[i] << ',';
	}

	buf << vs.v_[nCmpt - 1] << ')';

	return buf.str();
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class Form, class Cmpt, int nCmpt>
tnbLib::Istream& tnbLib::operator>>
(
	Istream& is,
	VectorSpace<Form, Cmpt, nCmpt>& vs
	)
{
	// Read beginning of VectorSpace<Cmpt, nCmpt>
	is.readBegin("VectorSpace<Form, Cmpt, nCmpt>");

	for (int i = 0; i < nCmpt; i++)
	{
		is >> vs.v_[i];
	}

	// Read end of VectorSpace<Cmpt, nCmpt>
	is.readEnd("VectorSpace<Form, Cmpt, nCmpt>");

	// Check state of Istream
	is.check("operator>>(Istream&, VectorSpace<Form, Cmpt, nCmpt>&)");

	return is;
}


template<class Form, class Cmpt, int nCmpt>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const VectorSpace<Form, Cmpt, nCmpt>& vs
	)
{
	os << token::BEGIN_LIST;

	for (int i = 0; i < nCmpt - 1; i++)
	{
		os << vs.v_[i] << token::SPACE;
	}

	os << vs.v_[nCmpt - 1] << token::END_LIST;

	// Check state of Ostream
	os.check("operator<<(Ostream&, const VectorSpace<Form, Cmpt, nCmpt>&)");

	return os;
}


// ************************************************************************* //