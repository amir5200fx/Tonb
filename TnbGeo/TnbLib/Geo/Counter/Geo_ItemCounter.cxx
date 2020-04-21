#include <Geo_ItemCounter.hxx>

#include <error.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	const Standard_Integer Geo_ItemCounter::DEFAULT_SIZE(100);
}

void tnbLib::Geo_ItemCounter::ReSize()
{
	std::vector<Standard_Integer> items;
	items.reserve(theItems_.NbPriorities());

	Standard_Integer item;
	while (theItems_.RetrieveFromPriority(item))
	{
		items.push_back(item);
	}
	theItems_.InsertToPriority(items);
}

tnbLib::Geo_ItemCounter::Geo_ItemCounter()
	: theNbItems_(0)
{
	theItems_.SetSizeToPriority(DEFAULT_SIZE);
}

Standard_Integer 
tnbLib::Geo_ItemCounter::RetrieveIndex()
{
	if (theItems_.NbPriorities())
	{
		Standard_Integer item;
		theItems_.RetrieveFromPriority(item);

		return item;
	}
	++theNbItems_;
	return theNbItems_;
}

void tnbLib::Geo_ItemCounter::ReturnToCounter
(
	const Standard_Integer theIndex
)
{
	if (theIndex <= 0)
	{
		FatalErrorIn("void ReturnToCounter(const Standard_Integer theIndex)")
			<< "the index must be > 0" << endl
			<< abort(FatalError);
	}

	if (theItems_.overFlow())
	{
		ReSize();
	}
	theItems_.InsertToPriority(theIndex);
}