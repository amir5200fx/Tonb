#include <NumAlg_InterplFunc.hxx>

std::pair<Standard_Real, Standard_Real> 
tnbLib::NumAlg_InterplFunc::Mirror
(
	const std::pair<Standard_Real, Standard_Real>& theQ, 
	const std::pair<Standard_Real, Standard_Real>& theTarget
)
{
	const auto x = 2 * theTarget.first - theQ.first;
	const auto y = 2 * theTarget.second - theQ.second;
	auto t = std::make_pair(x, y);
	return std::move(t);
}

std::vector<std::pair<Standard_Real, Standard_Real>> 
tnbLib::NumAlg_InterplFunc::ReproduceOffsets
(
	const std::vector<std::pair<Standard_Real, Standard_Real>>& theQs
)
{
	if (theQs.size() >= 5)
	{
		return theQs;
	}
	else
	{
		std::vector<std::pair<Standard_Real, Standard_Real>> Qs;
		for (const auto& x : theQs)
		{
			Qs.push_back(x);
		}
		const auto n = Qs.size();
		for (int i = n - 2; i >= 0; i--)
		{
			const auto& pt = Qs[i];
			auto ptp = Mirror(pt, Qs[n - 1]);
			Qs.push_back(std::move(ptp));
		}
#ifdef _DEBUG
		if (theQs.size() < 5)
		{
			FatalErrorIn(FunctionSIG)
				<< "unexpected error has been found!" << endl
				<< abort(FatalError);
		}
#endif // _DEBUG
		return std::move(Qs);
	}
}