#include <VoyageMesh_BaseSize.hxx>

#include <VoyageMesh_BaseSizeInfo.hxx>
#include <Voyage_Tools.hxx>
#include <Geo2d_MetricPrcsrAnIso.hxx>
#include <Geo_ProfileFun.hxx>
#include <Entity2d_Polygon.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Real tnbLib::VoyageMesh_BaseSize::TRANS_POINT_CONST = 0.4;
unsigned short tnbLib::VoyageMesh_BaseSize::verbose(0);

std::vector<Standard_Real> 
tnbLib::VoyageMesh_BaseSize::CalcHs
(
	const Standard_Integer id,
	const Entity2d_Polygon& thePolygon,
	const std::vector<Standard_Real>& theLengths
) const
{
	const auto h0 = RetrieveH0(id, theLengths);
	const auto h1 = RetrieveH1(id, theLengths);
	const auto hm = RetrieveHmax(id, theLengths);
	if (verbose > 1)
	{
		Info << " - the turning point id. " << id << endl
			<< " - h0 = " << h0 << ", h1 = " << h1 << ", hm = " << hm << endl;
	}
	Standard_Real tot_len;
	if (verbose > 1)
	{
		Info << " # Calculate the parameters..." << endl;
	}
	const auto pars = Voyage_Tools::CalcParameters(thePolygon, *Metrics(), tot_len);
	if (verbose > 1)
	{
		Info << " # Calculate the profile..." << endl;
	}
	const auto profile = CalcProfile(h0, h1, hm);
	if (verbose > 1)
	{
		Info << endl
			<< " Calculate the value of the parameters..." << endl;
	}
	std::vector<Standard_Real> hs;
	hs.reserve(pars.size());
	for (const auto t : pars)
	{
		if (verbose > 1)
		{
			Info << " - u: " << t;
		}
		auto hi = profile->Value(t);
		hs.push_back(hi);
		if (verbose > 1)
		{
			Info << ", hi: " << hi << endl;
		}
	}
	return std::move(hs);  // NOLINT(clang-diagnostic-pessimizing-move)
}

void tnbLib::VoyageMesh_BaseSize::Perform()
{
	if (verbose)
	{
		Info << " /* Calculating the base size for each turning point */" << endl;
	}
	if (NOT Metrics())
	{
		FatalErrorIn(FunctionSIG) << endl  // NOLINT(clang-diagnostic-language-extension-token)
			<< "No metric processor has been found." << endl
			<< abort(FatalError);
	}
	if (Path().empty())
	{
		FatalErrorIn(FunctionSIG)  // NOLINT(clang-diagnostic-language-extension-token)
			<< "No valid path has been found." << endl
			<< abort(FatalError);
	}
	// Getting the global path
	const auto& path = Path();
	if (verbose)
	{
		Info << endl
			<< " - No. of turning points in the path: " << path.size() - 1 << endl;
	}
	if (verbose)
	{
		Info << endl
			<< " # Calculate the total length of the path..." << endl;
	}
	std::vector<Standard_Real> length;
	length.reserve(path.size());
	Standard_Real tot_len = 0;
	for (const auto& x : path)
	{
		Debug_Null_Pointer(x);
		auto len = Voyage_Tools::CalcLength(*x, *Metrics());
		length.push_back(len);
		tot_len += len;
	}
	if (verbose)
	{
		Info << " - total length: " << tot_len << endl;
	}
	Standard_Integer k = 0;
	theHs_ = std::make_shared<std::vector<std::vector<Standard_Real>>>();
	if (verbose)
	{
		Info << endl
			<< " # Calculating the base size for each turning point in the path..." << endl;
	}
	for (const auto& x : path)
	{
		auto hs = CalcHs(k++, *x, length);
		theHs_->push_back(std::move(hs));
	}
	Change_IsDone() = Standard_True;
	if (verbose)
	{
		Info << " /* The End of calculating the base size for each turning point */" << endl;
	}
}