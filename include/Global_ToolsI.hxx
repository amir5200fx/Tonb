#pragma once
#ifdef _DEBUG
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <gp.hxx>
#endif // _DEBUG
namespace tnbLib
{

	template<class Type>
	size_t Global_Tools::FindSpan
	(
		const Standard_Real x,
		const std::vector<Type>& theSorted,
		Standard_Real(*xValue)(const Type&)
	)
	{
#ifdef _DEBUG
		//CheckSorted(theSorted, "size_t Global_Tools::FindSpan(Args...)");
#endif // _DEBUG

		auto high = theSorted.size() - 1;
		if (x >= xValue(theSorted[high]))
		{
			return high;
		}

		size_t low = 0;
		auto mid = (low + high) / 2;
		while (x < xValue(theSorted[mid]) || x >= xValue(theSorted[mid + 1]))
		{
			if (x < xValue(theSorted[mid])) high = mid;
			else low = mid;
			mid = (low + high) / 2;
		}
		return mid;
	}

	inline Standard_Real 
		tnbLib::Global_Tools::LinearInterpolate
		(
			const Standard_Real x0,
			const Standard_Real x1,
			const Standard_Real y0,
			const Standard_Real y1,
			const Standard_Real x
		)
	{
#ifdef _DEBUG
		if (std::abs(x1 - x0) < gp::Resolution())
		{
			FatalErrorIn(FunctionSIG)
				<< "divided by zero has been detected!" << endl
				<< abort(FatalError);
		}
#endif // _DEBUG
		return y0 + (y1 - y0)*(x - x0) / (x1 - x0);
	}

	inline Standard_Real 
		Global_Tools::LinearInterpolate
		(
			const std::pair<Standard_Real, Standard_Real>& theXY0, 
			const std::pair<Standard_Real, Standard_Real>& theXY1,
			const Standard_Real x
		)
	{
		const auto x0 = theXY0.first;
		const auto y0 = theXY0.second;

		const auto x1 = theXY1.first;
		const auto y1 = theXY1.second;

		return LinearInterpolate(x0, x1, y0, y1, x);
	}
}