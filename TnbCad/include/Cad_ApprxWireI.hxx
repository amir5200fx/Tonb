#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
template<class WireType, bool RandSamples>
inline Standard_Integer 
tnbLib::Cad_ApprxWire<WireType, RandSamples>::NbPolygons() const
{
	return (Standard_Integer)theWire_->NbCurves();
}

template<class WireType, bool RandSamples>
inline void tnbLib::Cad_ApprxWire<WireType, RandSamples>::Perform()
{
	if (NOT Wire())
	{
		FatalErrorIn(FunctionSIG)
			<< "no wire has been loaded!" << endl
			<< abort(FatalError);
	}

	auto curves = RetrieveCurves(*Wire());
	std::vector<std::shared_ptr<Entity_Polygon<Point>>> polygons;
	polygons.reserve(curves.size());
	for (const auto& x : curves)
	{
		Debug_Null_Pointer(x);
		auto alg = 
			std::make_shared<Cad_ApprxCurve<curveType, RandSamples>>(x, AlgInfo());
		Debug_Null_Pointer(alg);

		alg->Perform();
		Debug_If_Condition_Message(NOT alg->IsDone(), "the application is not performed!");

		auto poly = alg->Polygon();
		polygons.push_back(std::move(poly));
	}
	PolygonsRef() = std::move(polygons);
	Change_IsDone() = Standard_True;
}