#include <featureEdgeMesh.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{

	defineTypeNameAndDebug(featureEdgeMesh, 0);

}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::featureEdgeMesh::featureEdgeMesh(const IOobject& io)
	:
	regIOobject(io),
	edgeMesh(pointField(0), edgeList(0))
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

	if (debug)
	{
		Pout << "featureEdgeMesh::featureEdgeMesh :"
			<< " constructed from IOobject :"
			<< " points:" << points().size()
			<< " edges:" << edges().size()
			<< endl;
	}
}


//- Construct from components
tnbLib::featureEdgeMesh::featureEdgeMesh
(
	const IOobject& io,
	const pointField& points,
	const edgeList& edges
)
	:
	regIOobject(io),
	edgeMesh(points, edges)
{}


// Construct as copy
tnbLib::featureEdgeMesh::featureEdgeMesh
(
	const IOobject& io,
	const featureEdgeMesh& em
)
	:
	regIOobject(io),
	edgeMesh(em)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::featureEdgeMesh::readData(Istream& is)
{
	is >> *this;
	return !is.bad();
}


bool tnbLib::featureEdgeMesh::writeData(Ostream& os) const
{
	os << *this;

	return os.good();
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //


// ************************************************************************* //