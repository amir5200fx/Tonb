#include <Geo_Naca4Digit.hxx>

#include <Geo_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::Geo_Naca4Digit::SetDefaults()
{
	auto& p = theParameters_;

	p.chord = 1.0;
	p.maxCamber = 0.4;
	p.maxCamberLoc = 0.4;
	p.maxThick = 0.1;
	p.nbSections = 20;
}

std::vector<Standard_Real> 
tnbLib::Geo_Naca4Digit::CosDistb
(
	const Standard_Integer n
)
{
	if (n < 1)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid nb. of segments to build a naca profile" << endl
			<< abort(FatalError);
	}

	std::vector<Standard_Real> xs;
	xs.reserve(n + 1);

	const auto dx = M_PI / (Standard_Real)n;
	for (size_t i = 0; i <= n; i++)
	{
		xs.push_back(0.5*(1.0 - cos(i*dx)));
	}
	return std::move(xs);
}

std::vector<Standard_Real> 
tnbLib::Geo_Naca4Digit::CalcCamberOffsets
(
	const std::vector<Standard_Real>& Xs,
	const Parameter & pars
)
{
	std::vector<Standard_Real> Ys;
	Ys.reserve(Xs.size());

	const auto camb = pars.maxCamber;
	const auto cambloc = pars.maxCamberLoc;

	for (const auto& x : Xs)
	{
		if (x <= cambloc)
		{
			auto yc = camb * (2 * cambloc*x - x * x) / (cambloc*cambloc);
			Ys.push_back(yc);
		}
		else
		{
			auto yc = ((1.0 - 2 * cambloc) + 2 * cambloc*x - x * x) / ((1.0 - cambloc)*(1.0 - cambloc));
			yc *= cambloc;
			Ys.push_back(yc);
		}
	}
	return std::move(Ys);
}

std::vector<Standard_Real> 
tnbLib::Geo_Naca4Digit::CalcThicknessDistb
(
	const std::vector<Standard_Real>& Xs, 
	const Parameter & pars
)
{
	static const auto c1 = (Standard_Real)0.126;
	static const auto c2 = (Standard_Real)0.3516;
	static const auto c3 = (Standard_Real)0.2843;
	static const auto c4 = (Standard_Real)0.1015;
	static const auto c5 = (Standard_Real)0.2969;

	std::vector<Standard_Real> Ys;
	Ys.reserve(Xs.size());

	for (const auto& x : Xs)
	{
		auto sum = x * (-c1 + x * (-c2 + x * (c3 - c4 * x)));
		Ys.push_back((pars.maxThick / 0.2)*(c5*sqrt(x) + sum));
	}
	return std::move(Ys);
}

std::vector<Standard_Real> 
tnbLib::Geo_Naca4Digit::CalcCamberTangentDistb
(
	const std::vector<Standard_Real>& Xs,
	const Parameter & pars
)
{
	std::vector<Standard_Real> Ys;
	Ys.reserve(Xs.size());

	const auto camb = pars.maxCamber;
	const auto cambloc = pars.maxCamberLoc;

	for (const auto& x : Xs)
	{
		if (x <= cambloc)
		{
			auto yc = camb * (2 * cambloc - 2 * x) / (cambloc*cambloc);
			Ys.push_back(yc);
		}
		else
		{
			auto yc = camb * (2 * cambloc - 2 * x) / ((1.0 - cambloc)*(1.0 - cambloc));
			Ys.push_back(yc);
		}
	}
	return std::move(Ys);
}

void tnbLib::Geo_Naca4Digit::Perform()
{
	const auto ts = CosDistb(Parameters().nbSections);

	const auto yc = CalcCamberOffsets(ts, Parameters());
	const auto yt = CalcThicknessDistb(ts, Parameters());
	const auto ypc = CalcCamberTangentDistb(ts, Parameters());

	auto& upper = UpperRef();
	auto& lower = LowerRef();

	if (CloseTail)
	{
		upper.reserve(Parameters().nbSections + 2);
		lower.reserve(Parameters().nbSections + 2);
	}
	else
	{
		upper.reserve(Parameters().nbSections + 1);
		lower.reserve(Parameters().nbSections + 1);
	}

	for (size_t i = 0; i < ts.size(); i++)
	{
		const auto angl = atan(ypc[i]);
		const auto cs = cos(angl);
		const auto sn = sin(angl);

		const auto xu = ts[i] - yt[i] * sn;
		const auto yu = yc[i] + yt[i] * cs;

		const auto xl = ts[i] + yt[i] * sn;
		const auto yl = yc[i] - yt[i] * cs;

		auto Pu = Pnt2d(xu*Parameters().chord, yu*Parameters().chord);
		auto Pl = Pnt2d(xl*Parameters().chord, yl*Parameters().chord);

		upper.push_back(std::move(Pu));
		lower.push_back(std::move(Pl));
	}

	if (CloseTail)
	{
		const auto n = upper.size();

		Entity2d_Line line0(upper[n - 2], upper[n - 1]);
		Entity2d_Line line1(lower[n - 2], lower[n - 1]);

		auto intersct = Geo_Tools::Intersection_cgal(line0, line1);
		if (NOT intersct->IsPoint())
		{
			FatalErrorIn(FunctionSIG)
				<< "something went wrong in calculating the intersection of the profiles of the naca!" << endl
				<< " - no intersection has been found" << endl
				<< abort(FatalError);
		}

		auto pt = Geo_Tools::GetIntersectionPoint(intersct);

		upper.push_back(pt);
		lower.push_back(std::move(pt));
	}

	Change_IsDone() = Standard_True;
}