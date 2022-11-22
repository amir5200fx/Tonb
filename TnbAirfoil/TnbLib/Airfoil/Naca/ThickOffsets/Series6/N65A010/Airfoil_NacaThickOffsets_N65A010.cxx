#include <Airfoil_NacaThickOffsets_N65A010.hxx>

std::vector<Standard_Real> tnbLib::Airfoil_NacaThickOffsets_N65A010::XOC = { 0.0,0.5,0.75,1.25,2.5,5.0,7.5,10.0,15.0,20.0,25.0,30.0,35.0,40.0,45.0,50.0,55.0,60.0,65.0,70.0,75.0,80.0,85.0,90.0,95.0,100.0 };
std::vector<Standard_Real> tnbLib::Airfoil_NacaThickOffsets_N65A010::TOC = { 0.0,0.765,0.928,1.183,1.623,2.182,2.65,3.04,3.658,4.127,4.483,4.742,4.912,4.995,4.983,4.863,4.632,4.304,3.899,3.432,2.912,2.352,1.771,1.188,0.604,0.021 };

void tnbLib::Airfoil_NacaThickOffsets_N65A010::RuntimeSettings::Init()
{
	auto& toc = Airfoil_NacaThickOffsets_N65A010::TOC;
	Standard_Real maxThick = RealFirst();
	for (auto x : toc)
	{
		if (x > maxThick) maxThick = x;
	}
	for (auto& x : toc)
	{
		x /= maxThick;
		//x /= 100.0;
	}
	auto& xoc = Airfoil_NacaThickOffsets_N65A010::XOC;
	for (auto& x : xoc)
	{
		x /= 100.0;
	}
}

static const tnbLib::Airfoil_NacaThickOffsets_N65A010::RuntimeSettings NACA_N65A010_RuntimeSettingsObj;

std::vector<std::pair<Standard_Real, Standard_Real>>
tnbLib::Airfoil_NacaThickOffsets_N65A010::Values
(
	const Standard_Real theMaxThick
) const
{
	auto tx = Airfoil_NacaThickOffsets_N65A010::TOC;
	for (auto& x : tx)
	{
		x *= theMaxThick;
	}
	std::vector<std::pair<Standard_Real, Standard_Real>> qs;
	qs.reserve(tx.size());
	for (size_t i = 0; i < tx.size(); i++)
	{
		auto xc = XOC.at(i);
		auto t = tx.at(i);

		auto paired = std::make_pair(xc, t);
		qs.push_back(std::move(paired));
	}
	return std::move(qs);
}