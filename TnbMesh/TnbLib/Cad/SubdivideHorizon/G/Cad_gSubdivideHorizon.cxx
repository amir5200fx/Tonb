#include <Cad_gSubdivideHorizon.hxx>

#ifdef _DEBUG
#include <Cad_SubdivideHorizonTools.hxx>
#include <Aft2d_gPlnCurveSurface.hxx>
#include <Pln_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
#endif // _DEBUG

#ifdef _DEBUG
template<>
void tnbLib::Cad_gSubdivideHorizon::Perform
(
	const std::vector<std::shared_ptr<Aft2d_gPlnCurveSurface>>& theCurves
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
#endif // _DEBUG
