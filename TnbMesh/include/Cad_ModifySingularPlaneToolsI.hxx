#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
#ifndef _DEBUG
template<class SurfPlnType>
inline std::vector<std::shared_ptr<typename tnbLib::Cad_ModifySingularPlaneTools<SurfPlnType>::curveType>>
tnbLib::Cad_ModifySingularPlaneTools<SurfPlnType>::SubCurves
(
	const std::shared_ptr<curveType>& theCurve,
	const std::list<Standard_Real>& thePars,
	const Standard_Real theTol
)
{
#ifdef _DEBUG
	auto x0 = thePars.front();
	for (auto x : thePars)
	{
		if (x < x0)
		{
			FatalErrorIn(FunctionSIG)
				<< "the list is not sorted!" << endl
				<< abort(FatalError);
		}
		x0 = x;
	}
#endif // _DEBUG
	std::vector<std::shared_ptr<curveType>> curves;
	auto curve = theCurve;
	for (auto x : thePars)
	{
		auto[c0, c1] = Split(x, curve);
		curves.push_back(std::move(c0));
		curve = std::move(c1);
	}
	curves.push_back(std::move(curve));
	return std::move(curves);
}

template<class SurfPlnType>
inline std::vector<std::shared_ptr<typename tnbLib::Cad_ModifySingularPlaneTools<SurfPlnType>::wireType>>
tnbLib::Cad_ModifySingularPlaneTools<SurfPlnType>::ModifyWires
(
	const std::vector<std::shared_ptr<wireType>>& theWires,
	const std::map<std::shared_ptr<curveType>, std::shared_ptr<std::list<Standard_Real>>>& theSubMap,
	const Standard_Real theTol
)
{
	std::vector<std::shared_ptr<wireType>> mWires;
	for (const auto& wire : theWires)
	{
		Debug_Null_Pointer(wire);

		std::vector<std::shared_ptr<curveType>> curves;
		for (const auto& x : wire->Curves())
		{
			Debug_Null_Pointer(x);
			const auto iter = theSubMap.find(x);
			if (iter IS_EQUAL theSubMap.end())
			{
				FatalErrorIn(FunctionSIG)
					<< "the curve is not found!" << endl
					<< abort(FatalError);
			}

			Debug_Null_Pointer(iter->second);
			auto& l = *iter->second;

			if (l.empty())
			{
				curves.push_back(x);
			}
			else
			{
				if (l.size() > 2)
				{
					l.sort();
				}

				auto subCurves = SubCurves(x, l, theTol);
				for (auto& sub : subCurves)
				{
					Debug_Null_Pointer(sub);
					curves.push_back(std::move(sub));
				}
			}
		}

		auto newWire =
			std::make_shared<wireType>(wire->Index(), wire->Name(), std::move(curves));
		Debug_Null_Pointer(newWire);
		mWires.push_back(std::move(newWire));
	}
	return std::move(mWires);
}

template<class SurfPlnType>
inline std::vector<std::shared_ptr<typename tnbLib::Cad_ModifySingularPlaneTools<SurfPlnType>::curveType>>
tnbLib::Cad_ModifySingularPlaneTools<SurfPlnType>::ModifyHorizons
(
	const std::vector<std::shared_ptr<curveType>>& theCurves,
	const std::map<std::shared_ptr<curveType>, std::shared_ptr<std::list<Standard_Real>>>& theSubMap,
	const Standard_Real theTol
)
{
	std::vector<std::shared_ptr<curveType>> curves;
	for (const auto& x : theCurves)
	{
		Debug_Null_Pointer(x);
		const auto iter = theSubMap.find(x);
		if (iter IS_EQUAL theSubMap.end())
		{
			FatalErrorIn(FunctionSIG)
				<< "the curve is not found!" << endl
				<< abort(FatalError);
		}

		Debug_Null_Pointer(iter->second);
		auto& l = *iter->second;

		if (l.empty())
		{
			curves.push_back(x);
		}
		else
		{
			if (l.size() > 2)
			{
				l.sort();
			}

			auto subCurves = SubCurves(x, l, theTol);
			if (subCurves.size())
			{
				for (auto& sub : subCurves)
				{
					Debug_Null_Pointer(sub);
					curves.push_back(std::move(sub));
				}
			}
			else
			{
				curves.push_back(x);
			}
		}
	}
	return std::move(curves);
}

template<class SurfPlnType>
inline std::list
<
	std::shared_ptr
	<
	tnbLib::Cad_SubdivideHorizon
	<typename tnbLib::Cad_ModifySingularPlaneTools<SurfPlnType>::curveType>
	>
>
tnbLib::Cad_ModifySingularPlaneTools<SurfPlnType>::CalcParts
(
	const std::vector<std::shared_ptr<Cad_SingularZone<SurfPlnType>>>& theZones,
	const std::vector<std::shared_ptr<curveType>>& theCurves
)
{
	std::list<std::shared_ptr<Cad_SubdivideHorizon<curveType>>> subsList;
	for (const auto& x : theZones)
	{
		Debug_Null_Pointer(x);
		const auto& zone = *x;
		for (Standard_Integer iz = 0; iz < zone.NbHorizons(); iz++)
		{
			const auto& horizon = zone.Horizon(iz);
			Debug_Null_Pointer(horizon);

			auto alg = std::make_shared<Cad_SubdivideHorizon<curveType>>(horizon);
			Debug_Null_Pointer(alg);

			alg->Perform(theCurves);
			Debug_If_Condition_Message(NOT alg->IsDone(), "the application is not performed!");
			subsList.push_back(std::move(alg));
		}
	}
	return std::move(subsList);
}
#endif // !_DEBUG


template<class SurfPlnType>
inline std::map
<
	std::shared_ptr
	<typename tnbLib::Cad_ModifySingularPlaneTools<SurfPlnType>::wireType>,
	Standard_Integer
>
tnbLib::Cad_ModifySingularPlaneTools<SurfPlnType>::WireToIndexMap
(
	const std::vector<std::shared_ptr<wireType>>& theWires
)
{
	std::map<std::shared_ptr<wireType>, Standard_Integer> wireToIndex;
	Standard_Integer k = 0;
	for (const auto& x : theWires)
	{
		Debug_Null_Pointer(x);
		auto paired = std::make_pair(x, ++k);
		auto insert = wireToIndex.insert(std::move(paired));
		if (NOT insert.second)
		{
			FatalErrorIn(FunctionSIG)
				<< "duplicate data has been found!" << endl
				<< abort(FatalError);
		}
	}
	return std::move(wireToIndex);
}

template<class SurfPlnType>
inline std::map
<
	std::shared_ptr<typename tnbLib::Cad_ModifySingularPlaneTools<SurfPlnType>::curveType>, 
	enum class tnbLib::Cad_ModifySingularPlaneTools<SurfPlnType>::pCurveType
>
tnbLib::Cad_ModifySingularPlaneTools<SurfPlnType>::CurveToTypeMap
(
	const std::vector<std::shared_ptr<curveType>>& theHorizons,
	const std::vector<std::shared_ptr<wireType>>& theWires
)
{
	std::map<std::shared_ptr<curveType>, pCurveType> curveToType;
	for (const auto& x : theHorizons)
	{
		Debug_Null_Pointer(x);
		auto paired = std::make_pair(x, pCurveType::horizon);
		auto insert = curveToType.insert(std::move(paired));
		if (NOT insert.second)
		{
			FatalErrorIn(FunctionSIG)
				<< "duplicate data has been detected!" << endl
				<< abort(FatalError);
		}
	}
	if (theWires.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid geometry has been found!" << endl
			<< abort(FatalError);
	}
	for (const auto& x : theWires.at(0)->Curves())
	{
		Debug_Null_Pointer(x);
		auto paired = std::make_pair(x, pCurveType::outerWire);
		auto insert = curveToType.insert(std::move(paired));
		if (NOT insert.second)
		{
			FatalErrorIn(FunctionSIG)
				<< "duplicate data has been detected!" << endl
				<< abort(FatalError);
		}
	}
	if (theWires.size() > 1)
	{
		for (size_t i = 1; i < theWires.size(); i++)
		{
			Debug_Null_Pointer(theWires[i]);
			for (const auto& x : theWires[i]->Curves())
			{
				Debug_Null_Pointer(x);
				auto paired = std::make_pair(x, pCurveType::innerWire);
				auto insert = curveToType.insert(std::move(paired));
				if (NOT insert.second)
				{
					FatalErrorIn(FunctionSIG)
						<< "duplicate data has been detected!" << endl
						<< abort(FatalError);
				}
			}
		}
	}
	return std::move(curveToType);
}

template<class SurfPlnType>
std::vector<std::shared_ptr<tnbLib::Entity2d_Polygon>> 
tnbLib::Cad_ModifySingularPlaneTools<SurfPlnType>::GetPolygons
(
	const std::vector<std::shared_ptr<wireType>>& theWires, 
	const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo
)
{
	if (NOT theInfo)
	{
		FatalErrorIn(FunctionSIG)
			<< "no info has been loaded!" << endl
			<< abort(FatalError);
	}
	std::vector<std::shared_ptr<Entity2d_Polygon>> polygons;
	polygons.reserve(theWires.size());
	for (const auto& x : theWires)
	{
		Debug_Null_Pointer(x);
		auto wire = GetPolygon(x, theInfo);
		polygons.push_back(std::move(wire));
	}
	return std::move(polygons);
}

template<class SurfPlnType>
inline std::vector<std::shared_ptr<typename tnbLib::Cad_ModifySingularPlaneTools<SurfPlnType>::curveType>> 
tnbLib::Cad_ModifySingularPlaneTools<SurfPlnType>::RetrieveCurves
(
	const wireType & theWire
)
{
	std::vector<std::shared_ptr<curveType>> curves;
	curves.reserve(theWire.NbCurves());
	for (const auto& x : theWire.Curves())
	{
		Debug_Null_Pointer(x);
		curves.push_back(x);
	}
	return std::move(curves);
}

template<class SurfPlnType>
inline std::vector
<
	std::shared_ptr<typename tnbLib::Cad_ModifySingularPlaneTools<SurfPlnType>::curveType>
>
tnbLib::Cad_ModifySingularPlaneTools<SurfPlnType>::RetrieveCurves
(
	const std::vector<std::shared_ptr<wireType>>& theWires
)
{
	std::vector<std::shared_ptr<curveType>> allCurves;
	for (const auto& x : theWires)
	{
		Debug_Null_Pointer(x);
		auto curves = RetrieveCurves(*x);
		for (auto& c : curves)
		{
			Debug_Null_Pointer(c);
			allCurves.push_back(std::move(c));
		}
	}
	return std::move(allCurves);
}