#pragma once
template<class PlnType, bool RandSamples>
inline Standard_Integer 
tnbLib::Cad_ApprxParaPlane<PlnType, RandSamples>::NbPolygons() const
{
	return (Standard_Integer)thePolygons_.size();
}

template<class PlnType, bool RandSamples>
inline void tnbLib::Cad_ApprxParaPlane<PlnType, RandSamples>::Perform()
{
	if (NOT Plane())
	{
		FatalErrorIn(FunctionSIG)
			<< "no plane has been loaded!" << endl
			<< abort(FatalError);
	}
	auto wires = RetrieveWires(Plane());
	std::vector<std::shared_ptr<Entity_Polygon<Point>>> polygons;
	for (const auto& x : wires)
	{
		Debug_Null_Pointer(x);
		auto alg = std::make_shared<Cad_ApprxWire<wireType, RandSamples>>(x, ApproxInfo());
		Debug_Null_Pointer(alg);

		alg->Perform();
		Debug_If_Condition_Message(NOT alg->IsDone(), "the application is not performed!");

		auto polys = alg->Polygons();
		for (const auto& p : polys)
		{
			Debug_Null_Pointer(p);
			polygons.push_back(std::move(p));
		}
	}
	PolygonsRef() = std::move(polygons);
	Change_IsDone() = Standard_True;
}