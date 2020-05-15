#include <edgeMesh.hxx>

#include <IFstream.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// construct from file
tnbLib::edgeMesh::edgeMesh(const fileName& fname)
	:
	points_(0),
	edges_(0),
	pointEdgesPtr_(NULL)
{
	IFstream is(fname);

	if (is.good())
	{
		is >> points_ >> edges_;
	}
	else
	{
		FatalErrorIn("edgeMesh::edgeMesh(const fileName&)")
			<< "cannot open file " << fname
			<< abort(FatalError);
	}
}


// construct from Istream
tnbLib::edgeMesh::edgeMesh(Istream& is)
	:
	points_(is),
	edges_(is),
	pointEdgesPtr_(NULL)
{
	// Check state of Istream
	is.check("edgeMesh::edgeMesh(Istream&)");
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const edgeMesh& em)
{
	os << em.points_ << nl << em.edges_ << endl;

	// Check state of Ostream
	os.check("Ostream& operator<<(Ostream&, const edgeMesh&)");

	return os;
}


tnbLib::Istream& tnbLib::operator>>(Istream& is, edgeMesh& em)
{
	is >> em.points_ >> em.edges_;

	// Check state of Istream
	is.check("Istream& operator>>(Istream&, edgeMesh&)");

	return is;
}


// ************************************************************************* //