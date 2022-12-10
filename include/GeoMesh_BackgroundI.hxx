#pragma once
#ifdef _DEBUG
#include <Entity_Box.hxx>
#endif // _DEBUG

namespace tnbLib
{

	template<class MeshData, class Type>
	Type GeoMesh_SingleBackground<MeshData, Type>::InterpolateAt
	(
		const Point & theCoord
	) const
	{
		Standard_Boolean Sense;
		auto Value = InterpolateAt(theCoord, Sense);

		if (NOT Sense)
		{
#ifdef _DEBUG
			Info << " - coordinate: " << theCoord << endl
				<< " - Bounding box: " << this->BoundingBox() << endl << endl;
#endif // _DEBUG

			FatalErrorIn("Type InterpolateAt(const Point& theCoord) const")
				<< "the element is not found!" << endl
				<< abort(FatalError);
		}
		return Value;
	}

	template<class MeshData, class Type>
	Type GeoMesh_SingleBackground<MeshData, Type>::InterpolateAt
	(
		const Point & theCoord,
		Standard_Boolean & Sense
	) const
	{
		Debug_Null_Pointer(this->Mesh());

		const auto& mesh = *this->Mesh();
		const auto ptr = mesh.TriangleLocation(this->CurrentElement(), theCoord);

		if (!ptr)
		{
			Sense = Standard_False;
			Type value(-RealLast());
			return value;
		}

		this->Current = ptr;
		const auto& element = *ptr;

		auto weights = element.InterpWeights(theCoord);

		Standard_Real sumA = 0;
		Type numer(0);

		const auto& sources = Sources();

		forThose(Index, 0, elementType::rank)
		{
			numer += weights[Index] * sources[element.Node(Index)->Index() - 1];
			sumA += weights[Index];
		}

		Sense = Standard_True;
		return (1.0 / sumA)*numer;
	}

	template<class MeshData, class Type>
	void GeoMesh_SingleBackground<MeshData, Type>::HvCorrection
	(
		const std::shared_ptr<hvInfo>& theInfo
	)
	{
		if (NOT theInfo)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "Null pointer has been detected!" << endl
				<< abort(FatalError);
		}

		std::vector<std::shared_ptr<nodeType>> nodes;
		base::Mesh()->RetrieveNodesTo(nodes);

		HvCorrection(nodes, theInfo->Factor(), theInfo->MaxNbIters());
	}
}