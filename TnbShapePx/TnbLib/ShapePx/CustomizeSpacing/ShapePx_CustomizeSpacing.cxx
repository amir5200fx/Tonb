#include <ShapePx_CustomizeSpacing.hxx>

#include <ShapePx_CustomSpacing.hxx>

void tnbLib::ShapePx_CustomizeSpacing::AllocateMemory()
{
	theXs_.SetSizeToPriority(100);
}

std::vector<Standard_Real> 
tnbLib::ShapePx_CustomizeSpacing::Xs() const
{
	std::vector<Standard_Real> xs;
	xs.reserve(theXs_.NbPriorities());

	Standard_Real x;
	while (theXs_.RetrieveFromPriority(x))
	{
		xs.push_back(x);
	}
	return std::move(xs);
}

std::shared_ptr<tnbLib::ShapePx_CustomSpacing> 
tnbLib::ShapePx_CustomizeSpacing::Spacing() const
{
	auto xs = Xs();
	auto spacing = std::make_shared<ShapePx_CustomSpacing>(std::move(xs));
	return std::move(spacing);
}

void tnbLib::ShapePx_CustomizeSpacing::Insert(const Standard_Real x) const
{
	if (theXs_.overFlow())
	{
		theXs_.SetSizeToPriority(theXs_.PrioritySize() * 2 + 1);
	}
}

void tnbLib::ShapePx_CustomizeSpacing::Insert(const std::vector<Standard_Real>& xs) const
{
	for (auto x : xs)
	{
		Insert(x);
	}
}