#include <VoyageGeo_VelocityBackground.hxx>

#include <Mesh2d_Node.hxx>
#include <MeshBase_Tools.hxx>

template<>
void tnbLib::VoyageGeo_SingleVelocityBackground::ConnectTopology()
{
	if (const auto& mesh = this->Mesh())
	{
		if (mesh->Elements().size())
		{
			MeshBase_Tools::ConnectMesh(mesh->Elements());
		}
	}
}

template<>
tnbLib::Vec2d 
tnbLib::VoyageGeo_SingleVelocityBackground::InterpolateAt
(
	const Pnt2d& theCoord, 
	Standard_Boolean& Sense
) const
{
	Debug_Null_Pointer(this->Mesh());

	const auto& mesh = *this->Mesh();
	const auto ptr = mesh.TriangleLocation(this->CurrentElement(), theCoord);

	if (!ptr)
	{
		Sense = Standard_False;
		Vec2d value(-RealLast(), -RealLast());
		return value;
	}

	this->Current = ptr;
	const auto& element = *ptr;

	auto weights = element.InterpWeights(theCoord);

	Standard_Real sumA = 0;
	Vec2d numer(0.0, 0.0);

	const auto& sources = Sources();

	forThose(Index, 0, elementType::rank)
	{
		numer += weights[Index] * sources[element.Node(Index)->Index() - 1];
		sumA += weights[Index];
	}

	Sense = Standard_True;
	return (1.0 / sumA) * numer;
}