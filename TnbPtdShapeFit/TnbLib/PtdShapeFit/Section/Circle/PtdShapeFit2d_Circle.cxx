#include <PtdShapeFit2d_Circle.hxx>

#include <PtdShapeFit_Par.hxx>

const char* tnbLib::PtdShapeFit2d_Circle::xoPar::name = "xo";
const char* tnbLib::PtdShapeFit2d_Circle::yoPar::name = "yo";
const char* tnbLib::PtdShapeFit2d_Circle::radiusPar::name = "rad";

const unsigned int tnbLib::PtdShapeFit2d_Circle::nb_parameters(3);
unsigned short tnbLib::PtdShapeFit2d_Circle::verbose(0);

Standard_Integer 
tnbLib::PtdShapeFit2d_Circle::NbPars() const
{
	return Standard_Integer(nb_parameters);
}

std::vector<std::shared_ptr<tnbLib::PtdShapeFit_Par>> 
tnbLib::PtdShapeFit2d_Circle::RetrieveParList() const
{
	std::vector<std::shared_ptr<PtdShapeFit_Par>> pars(NbPars());
	pars.at(XoId()) = Xo();
	pars.at(YoId()) = Yo();
	pars.at(RadiusId()) = Radius();
	return std::move(pars);
}

void tnbLib::PtdShapeFit2d_Circle::SetParameters(const std::vector<Standard_Real>& theXs)
{
	std::vector<Param> pars(NbPars());
	{
		Param x = { GetXo(theXs),XoName() };
		pars.at(XoId()) = std::move(x);
	}
	{
		Param x = { GetYo(theXs),YoName() };
		pars.at(YoId()) = std::move(x);
	}
	{
		Param x = { GetRadius(theXs),RadiusName() };
		pars.at(RadiusId()) = std::move(x);
	}
	Parameters xPars = { std::move(pars) };
	ParsRef() = std::make_shared<Parameters>(std::move(xPars));
}

Standard_Integer 
tnbLib::PtdShapeFit2d_Circle::XoId()
{
	return Standard_Integer(xoPar::id);
}

Standard_Integer 
tnbLib::PtdShapeFit2d_Circle::YoId()
{
	return Standard_Integer(yoPar::id);
}

Standard_Integer 
tnbLib::PtdShapeFit2d_Circle::RadiusId()
{
	return Standard_Integer(radiusPar::id);
}

Standard_Real 
tnbLib::PtdShapeFit2d_Circle::GetXo(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(XoId());
}

Standard_Real 
tnbLib::PtdShapeFit2d_Circle::GetYo(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(YoId());
}

void tnbLib::PtdShapeFit2d_Circle::InsertXo
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(XoId()) = x;
}

void tnbLib::PtdShapeFit2d_Circle::InsertYo
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(YoId()) = x;
}

void tnbLib::PtdShapeFit2d_Circle::InsertRadius
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(RadiusId()) = x;
}

std::tuple
<
	tnbLib::PtdShapeFit2d_Circle::xoPar,
	tnbLib::PtdShapeFit2d_Circle::yoPar,
	tnbLib::PtdShapeFit2d_Circle::radiusPar
>
tnbLib::PtdShapeFit2d_Circle::RetrieveParameters(const std::vector<Standard_Real>& xs)
{
	xoPar p0 = { GetXo(xs) };
	yoPar p1 = { GetYo(xs) };
	radiusPar p2 = { GetRadius(xs) };

	auto t = std::make_tuple(std::move(p0), std::move(p1), std::move(p2));
	return std::move(t);
}

Standard_Real 
tnbLib::PtdShapeFit2d_Circle::GetRadius(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(RadiusId());
}

void tnbLib::PtdShapeFit2d_Circle::CheckVector(const std::vector<Standard_Real>& xs)
{
	if (xs.size() NOT_EQUAL PtdShapeFit2d_Circle::nb_parameters)
	{
		FatalErrorIn(FunctionSIG)
			<< "the vector is incompatible with this section." << endl
			<< abort(FatalError);
	}
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::PtdShapeFit2d_Circle::CreateXo
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)PtdShapeFit2d_Circle::xoPar::id + 1);
	par->SetName("xo");
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::PtdShapeFit2d_Circle::CreateYo
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)PtdShapeFit2d_Circle::yoPar::id + 1);
	par->SetName("yo");
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::PtdShapeFit2d_Circle::CreateRadius
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)PtdShapeFit2d_Circle::radiusPar::id + 1);
	par->SetName("radius");
	return std::move(par);
}