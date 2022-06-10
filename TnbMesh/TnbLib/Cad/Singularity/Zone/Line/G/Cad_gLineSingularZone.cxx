#include <Cad_gLineSingularZone.hxx>

#include <Cad_gLineSingularCurve.hxx>
#include <GModel_Surface.hxx>
#include <GModel_ParaCurve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
void tnbLib::Cad_gLineSingularZone::ProjectBoundariesToHorizons
(
	const GModel_Surface& theSurface
)
{
	return;
	//std::vector<std::shared_ptr<Aft2d_gPlnCurveSurface>> prjCurves;
	const auto& curves = this->Curves();
	Debug_If_Condition(curves.empty());

	std::vector<Pnt3d> offsets;
	offsets.reserve(curves.size() + 1);
	for (const auto& x : curves)
	{
		Debug_Null_Pointer(x);
		auto pt = theSurface.Value(x->FirstCoord());
		offsets.push_back(std::move(pt));
	}
	auto pt = theSurface.Value(curves.back()->LastCoord());
	offsets.push_back(std::move(pt));

	const auto horizons = this->Horizons();
	Standard_Boolean projected = Standard_False;
	for (const auto& x : horizons)
	{
		Debug_Null_Pointer(x);
		auto lineHorizon = std::dynamic_pointer_cast<Cad_gLineSingularCurve>(x);

		if (lineHorizon)
		{
			std::vector<Standard_Real>& projPars = lineHorizon->ProjParsRef();

			auto fp = lineHorizon->FirstParameter();
			auto lp = lineHorizon->LastParameter();

			Standard_Integer k = 0;
			for (const auto& Q : offsets)
			{
				auto pj = lineHorizon->ProjectAt(Q, theSurface);
				if (pj < fp) pj = fp;
				if (pj > lp) pj = lp;

				if (std::abs(fp - pj) > 1.0E-6 AND std::abs(lp - pj) > 1.0E-6)
				{
					//projPars.push_back(pj);
					if (NOT projected) projected = Standard_True;
				}
				
			}
		}

		if (projected) break;
	}
	if (projected)
	{
		NotImplemented;
	}
	/*for (const auto& x : horizons)
	{
		Debug_Null_Pointer(x);
		auto lineHorizon = std::dynamic_pointer_cast<Cad_gLineSingularCurve>(x);

		if (lineHorizon AND lineHorizon->HasSubcurves())
		{
			lineHorizon->CalcSubcurves();

			const auto& subs = lineHorizon->SubCurves();

		}
	}*/

}