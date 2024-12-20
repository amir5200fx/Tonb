#pragma once
#ifdef _DEBUG
#include <TnbError.hxx>
#include <OSstream.hxx>

//#include <gp.hxx>
#endif // _DEBUG
#include <TnbError.hxx>
#include <OSstream.hxx>
template<class T>
inline std::shared_ptr<T> 
tnbLib::Global_Tools::Find
(
	const std::map<Standard_Integer, std::shared_ptr<T>>& theMap,
	const Standard_Integer theIndex
)
{
	auto iter = theMap.find(theIndex);
	if (iter IS_EQUAL theMap.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the item is not found!" << endl
			<< " - index: " << theIndex << endl
			<< abort(FatalError);
	}
	return iter->second;
}

template<class T>
inline void tnbLib::Global_Tools::Insert
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<T>& theItem,
	std::map<Standard_Integer, std::shared_ptr<T>>& theMap
)
{
	auto paired = std::make_pair(theIndex, theItem);
	auto insert = theMap.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data is detected!" << endl
			<< " - index: " << theIndex << endl
			<< abort(FatalError);
	}
}

template<class T>
inline void tnbLib::Global_Tools::Insert
(
	const Standard_Integer theIndex,
	std::shared_ptr<T>&& theItem,
	std::map<Standard_Integer, std::shared_ptr<T>>& theMap
)
{
	auto paired = std::make_pair(theIndex, std::move(theItem));
	auto insert = theMap.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data is detected!" << endl
			<< " - index: " << theIndex << endl
			<< abort(FatalError);
	}
}

template<class T>
inline void tnbLib::Global_Tools::InsertIgnoreDup
(
	const Standard_Integer theIndex,
	std::shared_ptr<T>&& theItem,
	std::map<Standard_Integer, std::shared_ptr<T>>& theMap
)
{
	auto paired = std::make_pair(theIndex, std::move(theItem));
	auto insert = theMap.insert(std::move(paired));
	if (NOT insert.second)
	{
		// do nothing [3/22/2022 Amir]
	}
}

template<class T>
inline void tnbLib::Global_Tools::InsertIgnoreDup
(
	const Standard_Integer theIndex,
	const std::shared_ptr<T>& theItem,
	std::map<Standard_Integer, std::shared_ptr<T>>& theMap
)
{
	auto item = theItem;
	InsertIgnoreDup(theIndex, std::move(item), theMap);
}

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
		if (std::abs(x1 - x0) < 1.e-28)
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

	template<class Type, class UpType>
	inline std::vector<std::shared_ptr<UpType>> 
		Global_Tools::UpCast
		(
			const std::vector<std::shared_ptr<Type>>& theList
		)
	{
		std::vector<std::shared_ptr<UpType>> l;
		l.reserve(theList.size());
		for (const auto& x : theList)
		{
			std::shared_ptr<UpType> up = x;
			l.push_back(std::move(up));
		}
		return std::move(l);
	}

	template<class T1, class T2>
	inline std::vector<std::pair<T1, T2>>
		tnbLib::Global_Tools::ConvertToPairedList
		(
			const std::vector<T1>& l1,
			const std::vector<T2>& l2
		)
	{
		if (l1.size() NOT_EQUAL l2.size())
		{
			FatalErrorIn(FunctionSIG)
				<< "the lists are not the same size!" << endl
				<< abort(FatalError);
		}
		std::vector<std::pair<T1, T2>> pairedlist;
		pairedlist.reserve(l1.size());
		for (size_t i = 0; i < l1.size(); i++)
		{
			auto p = std::make_pair(l1.at(i), l2.at(i));
			pairedlist.push_back(std::move(p));
		}
		return std::move(pairedlist);
	}
}

namespace tnbLib
{
	template<class Key, class T>
	std::vector<T>
		tnbLib::Global_Tools::RetrieveValuesToList(const std::map<Key, T>& theMap)
	{
		std::vector<T> values;
		values.reserve(theMap.size());
		for (const auto& x : theMap)
		{
			values.push_back(x.second);
		}
		return std::move(values);
	}
}