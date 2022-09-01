#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
#include <GeoMesh3d_Background.hxx>
template<class SourceType>
inline void tnbLib::MeshBase_Tools::SetSourcesToMesh3d
(
	const std::vector<std::shared_ptr<SourceType>>& theSources,
	const Standard_Real theBaseSize,
	GeoMesh3d_Background & theMesh
)
{
	const auto& mesh = *theMesh.Mesh();
	if (mesh.Elements().empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "the element list of the background mesh is empty!" << endl
			<< abort(FatalError);
	}

	auto& sources = theMesh.Sources();
	//sources.resize(theSources.size(), theBaseSize);

	auto start = mesh.Elements().at(0);
	for (const auto& x : theSources)
	{
		const auto current = mesh.TriangleLocation(start, x->Coord());
		if (NOT current)
		{
			FatalErrorIn(FunctionSIG)
				<< "the point is outside of the mesh!" << endl
				<< " - domain's of the mesh: " << theMesh.BoundingBox() << endl
				<< " - coordinates of the point: " << x->Coord() << endl
				<< abort(FatalError);
		}
		start = current;

		const auto& currentRef = *current;
		auto n0 = Index_Of(currentRef.Node0()->Index());
		auto n1 = Index_Of(currentRef.Node1()->Index());
		auto n2 = Index_Of(currentRef.Node2()->Index());
		auto n3 = Index_Of(currentRef.Node3()->Index());

		auto v0 = sources.at(n0);
		auto v1 = sources.at(n1);
		auto v2 = sources.at(n2);
		auto v3 = sources.at(n3);

		if (x->H() < v0) sources.at(n0) = x->H();
		if (x->H() < v1) sources.at(n1) = x->H();
		if (x->H() < v2) sources.at(n2) = x->H();
		if (x->H() < v3) sources.at(n3) = x->H();
	}
}

template<class ElementType>
inline std::shared_ptr<ElementType> 
tnbLib::MeshBase_Tools::ElementLocation
(
	const std::shared_ptr<ElementType>& theStart,
	const typename ElementType::Point & theCoord
)
{
	if (NOT theStart)
	{
		FatalErrorIn(FunctionSIG)
			<< "Null element has been encountered!" << endl
			<< abort(FatalError);
	}

	auto neighbor = theStart;
	auto element = theStart;

	while (Standard_True)
	{
		for (auto i = 0; i <= ElementType::rank; i++)
		{
			Debug_Null_Pointer(element->SubEntity<ElementType::rank - 1>(i));
			const auto& entity = *element->SubEntity<ElementType::rank - 1>(i);

			auto leftElement = entity.LeftElement().lock();
			if (leftElement == element)
			{
				if (entity.IsRightSide(theCoord))
				{
					neighbor = entity.RightElement().lock();
					if (!neighbor)
					{
						//- the point is outside the background mesh
						return nullptr;
					}
					break;
				}
			}
			else
			{
				if (entity.IsLeftSide(theCoord))
				{
					neighbor = leftElement;
					if (!neighbor)
					{
						//- the point is outside the background mesh
						return nullptr;
					}
					break;
				}
			}


		}

		if (neighbor == element)
		{
			// Found the Triangle
			return neighbor;
		}

		element = neighbor;
	}
	return nullptr;
}

inline Standard_Real 
tnbLib::MeshBase_Tools::CalcRadius
(
	const Standard_Real growthRate,
	const Standard_Real theTarget,
	const Standard_Real theBase
)
{
	const auto H = theBase - theTarget;
	Debug_If_Condition_Message(H < 0, "invalid element size");

	const auto theta = asin(growthRate);
	return H / tan(theta);
}