#pragma once
#include <Cad_SubdivideHorizonTools.hxx>
#include <Pln_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
#ifndef _DEBUG
template<class PlnCurveType>
inline void tnbLib::Cad_SubdivideHorizon<PlnCurveType>::Perform
(
	const std::vector<std::shared_ptr<PlnCurveType>>& theCurves
)
{
	if (NOT Horizon())
	{
		FatalErrorIn(FunctionSIG)
			<< "no horizon curve has been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Pln_Tools::IsBounded(Horizon()->Geometry()))
	{
		FatalErrorIn(FunctionSIG)
			<< "the geometry is not bounded!" << endl
			<< abort(FatalError);
	}

	for (const auto& x : theCurves)
	{
		Debug_Null_Pointer(x);
		if (NOT Pln_Tools::IsBounded(x->Geometry()))
		{
			FatalErrorIn(FunctionSIG)
				<< "the geometry is not bounded!" << endl
				<< abort(FatalError);
		}

		auto[pairs, intsct] =
			Cad_SubdivideHorizonTools::CalcIntersections(x->Geometry(), Horizon()->Geometry());
		if (intsct)
		{
			auto[pars0, pars1] = Cad_SubdivideHorizonTools::RetrieveParams(pairs);
			auto l = std::make_shared<std::list<Standard_Real>>();
			auto item = std::make_pair(x, l);

			for (auto ip : pars0)
			{
				l->push_back(ip);
			}

			if (l->size() > 1) l->sort();

			for (auto ip : pars1)
			{
				ParametersRef().push_back(ip);
			}

			auto insert = CurvesToParametersRef().insert(std::move(item));
			if (NOT insert.second)
			{
				FatalErrorIn(FunctionSIG)
					<< "duplicate data has been detected!" << endl
					<< abort(FatalError);
			}
		}
		else
		{
			auto item =
				std::make_pair(x, std::make_shared<std::list<Standard_Real>>());
			auto insert = CurvesToParametersRef().insert(std::move(item));
			if (NOT insert.second)
			{
				FatalErrorIn(FunctionSIG)
					<< "duplicate data has been detected!" << endl
					<< abort(FatalError);
			}
		}
	}

	if (ParametersRef().size() > 1) ParametersRef().sort();

	Change_IsDone() = Standard_True;
}
#endif // !_DEBUG

template<class PlnCurveType>
inline std::map<std::shared_ptr<PlnCurveType>, std::shared_ptr<std::list<Standard_Real>>> 
tnbLib::Cad_SubdivideHorizon<PlnCurveType>::Merge
(
	const std::list<std::shared_ptr<Cad_SubdivideHorizon>>& theList
)
{
	std::map<std::shared_ptr<PlnCurveType>, std::shared_ptr<std::list<Standard_Real>>> merged;
	for (const auto& x : theList)
	{
		Debug_Null_Pointer(x);

		const auto& xMap = x->CurvesToParameters();
		const auto& horizon = x->Horizon();
		Debug_Null_Pointer(horizon);

		//const auto& params = x->Parameters();

		for (const auto& ip : xMap)
		{
			auto iter = merged.find(ip.first);
			if (iter IS_EQUAL merged.end())
			{
				auto l = std::make_shared<std::list<Standard_Real>>();
				auto insert = merged.insert(std::make_pair(ip.first, l));
				if (NOT insert.second)
				{
					FatalErrorIn(FunctionSIG)
						<< "duplicate data has been found!" << endl
						<< abort(FatalError);
				}

				Debug_Null_Pointer(ip.second);
				for (auto p : *ip.second)
				{
					l->push_back(p);
				}
			}
			else
			{
				auto& l = *iter->second;

				Debug_Null_Pointer(ip.second);
				for (const auto p : *ip.second)
				{
					l.push_back(p);
				}
			}
		}

		/*auto l = std::make_shared<std::list<Standard_Real>>();
		auto insert = merged.insert(std::make_pair(x->Horizon(), l));
		if (NOT insert.second)
		{
			FatalErrorIn(FunctionSIG)
				<< "duplicate data has been found" << endl
				<< abort(FatalError);
		}
		for (auto p : params)
		{
			l->push_back(p);
		}*/
	}
	for (const auto& x : theList)
	{
		Debug_Null_Pointer(x);

		const auto& horizon = x->Horizon();
		Debug_Null_Pointer(horizon);

		const auto& params = x->Parameters();

		auto l = std::make_shared<std::list<Standard_Real>>();
		auto insert = merged.insert(std::make_pair(x->Horizon(), l));
		if (NOT insert.second)
		{
			FatalErrorIn(FunctionSIG)
				<< "duplicate data has been found" << endl
				<< abort(FatalError);
		}
		for (auto p : params)
		{
			l->push_back(p);
		}
	}
	for (const auto& x : merged)
	{
		x.second->sort();
	}
	return std::move(merged);
}