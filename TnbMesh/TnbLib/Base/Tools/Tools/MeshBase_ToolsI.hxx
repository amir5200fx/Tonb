#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
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