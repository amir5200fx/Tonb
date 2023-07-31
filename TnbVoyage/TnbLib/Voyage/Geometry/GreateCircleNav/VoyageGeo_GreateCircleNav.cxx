#include <VoyageGeo_GreateCircleNav.hxx>

#include <Geo_Tools.hxx>
#include <gp.hxx>

#define CHECK_ANGLE(x)  \
if (x < -PI) x += 2 * PI; \
if (x > PI) x -= 2 * PI;

void tnbLib::VoyageGeo_GreateCircleNav::Init()
{
	const auto phi1 = Phi1();
	const auto phi2 = Phi2();
	const auto landa1 = Landa1();
	const auto landa2 = Landa2();

	auto landa12 = landa2 - landa1;
	//std::cout << "landa12 = " << landa12;
	CHECK_ANGLE(landa12);
	//std::cout << " landa12 corrected: " << landa12 << std::endl;
	const auto cos_phi1 = std::cos(phi1);
	const auto cos_phi2 = std::cos(phi2);
	const auto sin_phi1 = std::sin(phi1);
	const auto sin_phi2 = std::sin(phi2);
	const auto cos_landa12 = std::cos(landa12);
	const auto sin_landa12 = std::sin(landa12);
	{
		const auto nume = cos_phi2 * std::sin(landa12);
		const auto denom = cos_phi1 * sin_phi2 - sin_phi1 * cos_phi2 * cos_landa12;
		theAlpha1_ = std::atan2(nume, denom);
		CHECK_ANGLE(theAlpha1_);
	}
	{
		const auto nume = cos_phi1 * std::sin(landa12);
		const auto denom = -cos_phi2 * sin_phi1 + sin_phi2 * cos_phi1 * cos_landa12;
		theAlpha2_ = std::atan2(nume, denom);
		CHECK_ANGLE(theAlpha2_);
	}
	//std::cout <<"alpha 1: " << Geo_Tools::RadianToDegree(theAlpha1_) << ", alpha 2: " << Geo_Tools::RadianToDegree(theAlpha2_) << std::endl;
	{
		const auto nume = std::sin(theAlpha1_) * cos_phi1;
		const auto cos_a1 = std::cos(theAlpha1_);
		const auto sin_a1 = std::sin(theAlpha1_);
		const auto denom = std::sqrt(cos_a1 * cos_a1 + sin_a1 * sin_a1 * sin_phi1 * sin_phi1);
		//std::cout << "a0 nume = " << nume << ", denoom = " << denom << std::endl;
		theAlpha0_ = std::atan2(nume, denom);
		CHECK_ANGLE(theAlpha0_);
		//std::cout << "alpha 0 = " << Geo_Tools::RadianToDegree(theAlpha0_) << std::endl;
	}
	{
		const auto s1 = cos_phi1 * sin_phi2 - sin_phi1 * cos_phi2 * cos_landa12;
		const auto s2 = cos_phi2 * sin_landa12;
		const auto nume = std::sqrt(s1 * s1 + s2 * s2);
		const auto denom = sin_phi1 * sin_phi2 + cos_phi1 * cos_phi2 * cos_landa12;
		theSigma12_ = std::atan2(nume, denom);
		CHECK_ANGLE(theSigma12_);
		//theSigma12_ = std::atan(nume / denom);
		//std::cout << "s12 = " << Geo_Tools::RadianToDegree(theSigma12_) << std::endl;
	}
	if (std::abs(phi1) <= gp::Resolution() AND std::abs(theAlpha1_ - 0.5 * PI) <= gp::Resolution())
	{
		theSigma01_ = 0;
	}
	else
	{
		theSigma01_ = std::atan2(std::tan(phi1), std::cos(theAlpha1_));
		CHECK_ANGLE(theSigma01_);
		//std::cout << " sigma 01: " << theSigma01_ << std::endl;
	}
	theSigma02_ = theSigma01_ + theSigma12_;
	//theLanda01_ = std::atan(std::sin(theAlpha0_) * std::sin(theSigma01_) / std::cos(theSigma01_));
	theLanda01_ = atan2(std::sin(theAlpha0_) * std::sin(theSigma01_), std::cos(theSigma01_));
	//std::cout << "landa01 = " << theLanda01_ << ", landa01 corrected: ";
	CHECK_ANGLE(theLanda01_);
	//std::cout << theLanda01_ << std::endl;
	theLanda0_ = landa1 - theLanda01_;
	CHECK_ANGLE(theLanda0_);
	/*std::cout << "s01 = " << Geo_Tools::RadianToDegree(theSigma01_) << std::endl;
	std::cout << "s02 = " << Geo_Tools::RadianToDegree(theSigma02_) << std::endl;
	std::cout << "landa0 = " << Geo_Tools::RadianToDegree(theLanda0_) << std::endl;
	std::cout << "landa01 = " << Geo_Tools::RadianToDegree(theLanda01_) << std::endl;
	std::cout << "dis = " << theSigma12_ * 6371 << std::endl;
	auto pp = CalcWayPoint(MEAN(theSigma01_, theSigma02_));
	std::cout << "mid = " << Geo_Tools::RadianToDegree(pp.X())<<", "<<Geo_Tools::RadianToDegree(pp.Y()) << std::endl;*/
}

Standard_Real 
tnbLib::VoyageGeo_GreateCircleNav::Phi1() const
{
	return theP1_.X();
}

Standard_Real 
tnbLib::VoyageGeo_GreateCircleNav::Phi2() const
{
	return theP2_.X();
}

Standard_Real 
tnbLib::VoyageGeo_GreateCircleNav::Landa1() const
{
	return theP1_.Y();
}

Standard_Real 
tnbLib::VoyageGeo_GreateCircleNav::Landa2() const
{
	return theP2_.Y();
}

tnbLib::Pnt2d 
tnbLib::VoyageGeo_GreateCircleNav::CalcWayPoint(const Standard_Real x) const
{
	const auto cos_alpha0 = std::cos(theAlpha0_);
	const auto sin_alpha0 = std::sin(theAlpha0_);
	auto sin_x = std::sin(x);
	auto cos_x = std::cos(x);
	auto nume = cos_alpha0 * sin_x;
	auto denom = std::sqrt(cos_x * cos_x + sin_alpha0 * sin_alpha0 * sin_x * sin_x);

	auto phi = std::atan2(nume, denom);
	auto landa = theLanda0_ + std::atan2(sin_alpha0 * sin_x, cos_x);
	if (landa > PI) landa -= 2.0 * PI;
	if (landa < -PI) landa += 2.0 * PI;
	return { phi,landa };
}

std::vector<tnbLib::Pnt2d> 
tnbLib::VoyageGeo_GreateCircleNav::CalcWayPoints
(
	const std::vector<Standard_Real>& theXs
) const
{
	const auto phi1 = Phi1();
	const auto phi2 = Phi2();
	auto landa1 = Landa1();
	const auto landa2 = Landa2();

	const auto cos_alpha0 = std::cos(theAlpha0_);
	const auto sin_alpha0 = std::sin(theAlpha0_);

	auto x0 = theXs.at(0);
	auto sin_x = std::sin(x0);
	auto cos_x = std::cos(x0);
	auto nume = cos_alpha0 * sin_x;
	auto denom = std::sqrt(cos_x * cos_x + sin_alpha0 * sin_alpha0 * sin_x * sin_x);

	auto phi = std::atan2(nume, denom);
	CHECK_ANGLE(phi);

	/*std::cout << " DPHI = " << std::abs(phi - phi1) << std::endl;
	std::cout << "PHI = " << phi << std::endl;
	std::cout << "F0: " << this->Sigma1() << std::endl;
	std::cout << "F1: " << this->Sigma2() << std::endl;
	std::cout << "DF: " << this->Sigma2() - this->Sigma1() << std::endl;
	std::cout << "phi1 = " << phi1 << ", landa1 = " << Landa1() << std::endl;
	std::cout << "phi2 = " << phi2 << ", landa2 = " << landa2 << std::endl;
	std::cout << "T = " << T << std::endl;
	PAUSE;*/
	std::vector<Pnt2d> coords;
	coords.reserve(theXs.size());
	for (auto x : theXs)
	{
		auto sin_x = std::sin(x);
		auto cos_x = std::cos(x);
		//auto phi = std::asin(cos_alpha0 * sin_x);
		auto nume = cos_alpha0 * sin_x;
		auto denom = std::sqrt(cos_x * cos_x + sin_alpha0 * sin_alpha0 * sin_x * sin_x);

		auto phi = std::atan2(nume, denom);
		CHECK_ANGLE(phi);
		//auto phi = std::atan(nume / denom);
		//std::cout << "phi = " << phi << ", inv = " << std::atan(nume / denom) << std::endl;
		//phi += T;
		auto landa0 = std::atan2(sin_alpha0 * sin_x, cos_x);
		CHECK_ANGLE(landa0);
		auto landa = theLanda0_ + landa0;
		//auto landa = theLanda0_ + std::atan(sin_alpha0 * sin_x / cos_x);
		CHECK_ANGLE(landa);
		//std::cout << " nume = " << nume << ", denom = " << denom << std::endl;
		//std::cout << "x= " << x << " , phi = " << phi << ", landa = " << landa << std::endl;
		coords.push_back({ phi,landa });
	}
	
	return std::move(coords);
	//const auto phi1 = Phi1();
	//const auto phi2 = Phi2();
	//auto landa1 = Landa1();
	//const auto landa2 = Landa2();

	//auto sin_phi1 = std::sin(phi1);
	//auto cos_phi1 = std::cos(phi1);
	//auto sin_phi2 = std::sin(phi2);
	//auto cos_phi2 = std::cos(phi2);

	//auto landa12 = landa2 - landa1;
	//if (landa12 > PI) landa12 -= 2.0 * PI;
	//if (landa12 < -PI) landa12 += 2.0 * PI;

	//auto cos_sigma = sin_phi1 * sin_phi2 + cos_phi1 * cos_phi2 * std::cos(landa12);
	//if (cos_sigma > 1.0) cos_sigma = 1.0;
	//if (cos_sigma < -1.0) cos_sigma = -1.0;
	//auto sigma = std::acos(cos_sigma);

	//auto sin_sigma = std::sin(sigma);
	////auto cos_sigma = std::cos(sigma);

	//auto cos_a1 = (sin_phi2 - sin_phi1 * cos_sigma) / cos_phi1 * sin_sigma;
	//if (cos_a1 > 1.0) cos_a1 = 1.0;
	//if (cos_a1 < -1.0) cos_a1 = -1.0;
	//auto kprime = std::acos(cos_a1);
	//Standard_Real Kop;
	//if (landa12 >= 0) Kop = kprime;
	//else Kop = PI - kprime;
	////std::cout << "cos_a1 = " << cos_a1 << std::endl;
	////PAUSE;
	//std::vector<Pnt2d> coords;
	//coords.reserve(theXs.size());
	//for (auto x : theXs)
	//{
	//	auto cos_sx = std::cos(/*sigma * x*/Geo_Tools::DegToRadian(0.5));
	//	auto sin_sx = std::sin(/*sigma * x*/Geo_Tools::DegToRadian(0.5));
	//	auto sin_phix = sin_phi1 * cos_sx + cos_phi1 * sin_sx * /*cos_a1*/std::cos(Kop);
	//	std::cout << "sin_phix = " << sin_phix << std::endl;
	//	auto phix = std::asin(sin_phix);

	//	auto cos_dlanda12 = cos_sx / (cos_phi1 * std::cos(phix)) - std::tan(phi1) * std::tan(phix);
	//	if (cos_dlanda12 > 1.0) cos_dlanda12 = 1.0;
	//	if (cos_dlanda12 < -1.0) cos_dlanda12 = -1.0;
	//	//std::cout << "cos_dlanda12 = " << cos_dlanda12 << std::endl;
	//	auto xx = std::acos(cos_dlanda12);
	//	auto landax = xx + landa1;
	//	//if (landax > PI) landax -= 2.0 * PI;
	//	//if (landax < -PI) landax += 2.0 * PI;
	//	auto cos_y = (sin_phi1 - cos_sx * sin_phix) / (sin_sx * std::cos(phix));
	//	auto y = std::acos(cos_y);
	//	if (xx >= 0) Kop = xx;
	//	else Kop = PI - xx;
	//	coords.push_back({ phix,landax });
	//	std::cout << "x= " << x << " , phi = " << phix << ", landa = " << landax << std::endl;
	//	sin_phi1 = std::sin(phix);
	//	cos_phi1 = std::cos(phix);
	//	landa1 = landax;
	//}
	//std::cout << "phi1 = " << phi1 << ", landa1 = " << Landa1() << std::endl;
	//std::cout << "phi2 = " << phi2 << ", landa2 = " << landa2 << std::endl;
	//PAUSE;
	//return std::move(coords);
	

}