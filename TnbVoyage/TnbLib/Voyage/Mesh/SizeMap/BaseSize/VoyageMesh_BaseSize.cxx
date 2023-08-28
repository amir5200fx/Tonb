#include <VoyageMesh_BaseSize.hxx>

#include <VoyageMesh_BaseSizeInfo.hxx>
#include <Voyage_Tools.hxx>
#include <Geo2d_MetricPrcsrAnIso.hxx>
#include <Geo2d_2ndNurbsPx_3Pts.hxx>
#include <Geo_ProfileFun.hxx>
#include <Entity2d_Polygon.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Real tnbLib::VoyageMesh_BaseSize::TRANS_POINT_CONST = 0.4;

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
	//std::cout << "h0 = " << h0 << ", hm = " << hm << ", h1 = " << h1 << std::endl;
	Standard_Real tot_len;
	auto pars = Voyage_Tools::CalcParameters(thePolygon, *Metrics(), tot_len);
	auto profile = CalcProfile(h0, h1, hm);

	std::vector<Standard_Real> hs;
	hs.reserve(pars.size());
	for (auto t : pars)
	{
		//std::cout << "t = " << t << ", value = "<< profile->Value(t) << std::endl;
		hs.push_back(profile->Value(t));
	}
	return std::move(hs);
}

void tnbLib::VoyageMesh_BaseSize::Perform()
{
	if (NOT Metrics())
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "No metric processor has been found." << endl
			<< abort(FatalError);
	}
	if (Path().empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "No valid path has been found." << endl
			<< abort(FatalError);
	}
	const auto& path = Path();
	std::vector<Standard_Real> tot_len;
	tot_len.reserve(path.size());
	for (const auto& x : path)
	{
		auto len = Voyage_Tools::CalcLength(*x, *Metrics());
		tot_len.push_back(len);
	}
	Standard_Integer k = 0;
	theHs_ = std::make_shared<std::vector<std::vector<Standard_Real>>>();
	for (const auto& x : path)
	{
		auto hs = CalcHs(k++, *x, tot_len);
		theHs_->push_back(std::move(hs));
	}
	Change_IsDone() = Standard_True;
}