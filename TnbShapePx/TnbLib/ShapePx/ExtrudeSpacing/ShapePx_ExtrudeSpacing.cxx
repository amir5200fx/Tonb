#include <ShapePx_ExtrudeSpacing.hxx>

#include <Standard_Real.hxx>
#include <Geo_PriorityList.hxx>
#include <ShapePx_CustomSpacing.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <algorithm>

Standard_Real 
tnbLib::ShapePx_ExtrudeSpacing::Dx(const Span& p, const Standard_Integer n)
{
	const auto dx = (p.x1 - p.x0) / (Standard_Real)(n - 1);
	return dx;
}

std::vector<typename tnbLib::ShapePx_ExtrudeSpacing::dot_t>
tnbLib::ShapePx_ExtrudeSpacing::Xs
(
	const Span& p,
	const Standard_Integer n
)
{
	const auto dx = Dx(p, n);
	std::vector<dot_t> xs;
	xs.reserve(n);
	xs.push_back(std::make_shared<SpanDot>(p.x0));
	for (size_t i = 1; i < n; i++)
	{
		auto x = p.x0 + i * dx;
		xs.push_back(std::make_shared<Dot>(x));
	}
	xs.push_back(std::make_shared<SpanDot>(p.x1));
	return std::move(xs);
}

void tnbLib::ShapePx_ExtrudeSpacing::CalcMinDelta()
{
	theMinDelta_ = RealLast();
	for (const auto& x : theSpans_)
	{
		theMinDelta_ = std::min(Dx(x, theMinNbSections_), theMinDelta_);
	}
}

const Standard_Integer tnbLib::ShapePx_ExtrudeSpacing::DEFAULT_MIN_NB_SECTIONS(3);

std::shared_ptr<tnbLib::ShapePx_CustomSpacing> 
tnbLib::ShapePx_ExtrudeSpacing::Spacing() const
{
	if (NOT IsDone())
	{
		FatalErrorIn(FunctionSIG)
			<< "the algorithm is not performed!" << endl
			<< abort(FatalError);
	}
	std::vector<Standard_Real> xs;
	xs.reserve(Merged().size());
	for (const auto& x : Merged())
	{
		xs.push_back(x->x);
	}
	auto spacing = std::make_shared<ShapePx_CustomSpacing>(std::move(xs));
	return std::move(spacing);
}

void tnbLib::ShapePx_ExtrudeSpacing::Perform()
{
	CalcMinDelta();

	std::vector<dot_t> dots;
	for (const auto& x : theSpans_)
	{
		auto xs = Xs(x, MinNbSections());
		for (const auto& d : xs)
		{
			dots.push_back(std::move(d));
		}
	}

	std::sort(dots.begin(), dots.end(), &Dot::IsLess);

	std::vector<dot_t> merged;
	auto iter = dots.begin();
	auto x0 = *iter;
	merged.push_back(x0);
	iter++;
	while (iter NOT_EQUAL dots.end())
	{
		auto x1 = *iter;
		if ((x1->x - x0->x) < (0.499*theMinDelta_) AND x1->IsSpan())
		{
			if (NOT merged[merged.size() - 1]->IsSpan()) merged.pop_back();
			merged.push_back(x1);
		}
		else
		{
			merged.push_back(x1);
		}
		x0 = x1;
		iter++;
	}
	theMerged_ = std::move(merged);
	Change_IsDone() = Standard_True;
}

void tnbLib::ShapePx_ExtrudeSpacing::SetMinNbSections(const Standard_Integer n)
{
	theMinNbSections_ = std::max(n, DEFAULT_MIN_NB_SECTIONS);
}

void tnbLib::ShapePx_ExtrudeSpacing::ImportSpan(const Span & p)
{
	theSpans_.push_back(p);
}

void tnbLib::ShapePx_ExtrudeSpacing::ImportSpan(Span && p)
{
	theSpans_.push_back(std::move(p));
}