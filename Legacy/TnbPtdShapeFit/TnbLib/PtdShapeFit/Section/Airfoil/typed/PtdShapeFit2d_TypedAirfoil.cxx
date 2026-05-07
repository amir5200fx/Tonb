#include <PtdShapeFit2d_TypedAirfoil.hxx>

#include <PtdShapeFit_Par.hxx>

const char* tnbLib::PtdShapeFit2d_TypedAirfoil::xoPar::name = "xo";
const char* tnbLib::PtdShapeFit2d_TypedAirfoil::yoPar::name = "yo";
const char* tnbLib::PtdShapeFit2d_TypedAirfoil::chordLenPar::name = "chordLen";
const char* tnbLib::PtdShapeFit2d_TypedAirfoil::anglePar::name = "angle";

const unsigned int tnbLib::PtdShapeFit2d_TypedAirfoil::nb_parameters(4);
unsigned short tnbLib::PtdShapeFit2d_TypedAirfoil::verbose(0);

std::map<Standard_Integer, const char*> tnbLib::PtdShapeFit2d_TypedAirfoil::ParsMap;

namespace tnbLib
{
	class PtdShapeFit2d_TypedAirfoilRunTime
	{

		/*Private Data*/

	public:

		// Default constructor [4/11/2023 Payvand]

		PtdShapeFit2d_TypedAirfoilRunTime()
		{
			SetConfig();
		}

		// Constructors [4/11/2023 Payvand]

		void SetConfig();
	};
}

void tnbLib::PtdShapeFit2d_TypedAirfoilRunTime::SetConfig()
{
	{
		auto paired = std::make_pair(PtdShapeFit2d_TypedAirfoil::xoPar::id, PtdShapeFit2d_TypedAirfoil::xoPar::name);
		PtdShapeFit2d_TypedAirfoil::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(PtdShapeFit2d_TypedAirfoil::yoPar::id, PtdShapeFit2d_TypedAirfoil::yoPar::name);
		PtdShapeFit2d_TypedAirfoil::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(PtdShapeFit2d_TypedAirfoil::chordLenPar::id, PtdShapeFit2d_TypedAirfoil::chordLenPar::name);
		PtdShapeFit2d_TypedAirfoil::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(PtdShapeFit2d_TypedAirfoil::anglePar::id, PtdShapeFit2d_TypedAirfoil::anglePar::name);
		PtdShapeFit2d_TypedAirfoil::ParsMap.insert(std::move(paired));
	}
}

tnbLib::PtdShapeFit2d_TypedAirfoilRunTime myPtdShapeFit2d_CircleRunTimeObj;

const char* 
tnbLib::PtdShapeFit2d_TypedAirfoil::ParName
(
	const Standard_Integer theIndex
) const
{
	return ParsMap.at(theIndex);
}

Standard_Integer 
tnbLib::PtdShapeFit2d_TypedAirfoil::NbPars() const
{
	return Standard_Integer(nb_parameters);
}

std::shared_ptr<tnbLib::PtdShapeFit2d_TypedAirfoil::Parameters>
tnbLib::PtdShapeFit2d_TypedAirfoil::RetrieveParChromosome
(
	const std::vector<Standard_Real>& theChromosome
) const
{
	std::vector<Param> pars(theChromosome.size());
	{
		Param p{ GetXo(theChromosome),xoPar::name };
		pars.at(XoId()) = std::move(p);
	}
	{
		Param p{ GetYo(theChromosome),yoPar::name };
		pars.at(YoId()) = std::move(p);
	}
	{
		Param p{ GetChordLen(theChromosome),chordLenPar::name };
		pars.at(ChordLenId()) = std::move(p);
	}
	{
		Param p{ GetChordLen(theChromosome),anglePar::name };
		pars.at(AngleId()) = std::move(p);
	}
	Parameters pchromRef = { std::move(pars) };
	auto pchrom = std::make_shared<Parameters>(std::move(pchromRef));
	return std::move(pchrom);
}

std::vector<std::shared_ptr<tnbLib::PtdShapeFit_Par>> 
tnbLib::PtdShapeFit2d_TypedAirfoil::RetrieveParList() const
{
	std::vector<std::shared_ptr<PtdShapeFit_Par>> pars(NbPars());
	pars.at(XoId()) = Xo();
	pars.at(YoId()) = Yo();
	pars.at(AngleId()) = Angle();
	pars.at(ChordLenId()) = ChordLen();
	return std::move(pars);
}

std::vector<Standard_Real> 
tnbLib::PtdShapeFit2d_TypedAirfoil::RetrieveChromosome
(
	const std::shared_ptr<Parameters>& thePars
) const
{
	std::vector<Standard_Real> chromosome(thePars->x.size());
	if (thePars)
	{
		const auto& pars = *thePars;
		chromosome.at(XoId()) = pars.x.at(XoId()).x;
		chromosome.at(YoId()) = pars.x.at(YoId()).x;
		chromosome.at(AngleId()) = pars.x.at(AngleId()).x;
		chromosome.at(ChordLenId()) = pars.x.at(ChordLenId()).x;
		return std::move(chromosome);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "no optimized result has been found." << endl
			<< abort(FatalError);
		return std::move(chromosome);
	}
}

void tnbLib::PtdShapeFit2d_TypedAirfoil::SetParameters
(const std::vector<Standard_Real>& theXs)
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
		Param x = { GetAngle(theXs),AngleName() };
		pars.at(AngleId()) = std::move(x);
	}
	{
		Param x = { GetChordLen(theXs),ChordLenName() };
		pars.at(ChordLenId()) = std::move(x);
	}
	Parameters xPars = { std::move(pars) };
	ParsRef() = std::make_shared<Parameters>(std::move(xPars));
}

Standard_Integer
tnbLib::PtdShapeFit2d_TypedAirfoil::XoId()
{
	return Standard_Integer(xoPar::id);
}

Standard_Integer
tnbLib::PtdShapeFit2d_TypedAirfoil::YoId()
{
	return Standard_Integer(yoPar::id);
}

Standard_Integer 
tnbLib::PtdShapeFit2d_TypedAirfoil::ChordLenId()
{
	return Standard_Integer(chordLenPar::id);
}

Standard_Integer
tnbLib::PtdShapeFit2d_TypedAirfoil::AngleId()
{
	return Standard_Integer(anglePar::id);
}

Standard_Real
tnbLib::PtdShapeFit2d_TypedAirfoil::GetXo(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(XoId());
}

Standard_Real
tnbLib::PtdShapeFit2d_TypedAirfoil::GetYo(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(YoId());
}

Standard_Real 
tnbLib::PtdShapeFit2d_TypedAirfoil::GetChordLen(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(ChordLenId());
}

Standard_Real
tnbLib::PtdShapeFit2d_TypedAirfoil::GetAngle(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(AngleId());
}

void tnbLib::PtdShapeFit2d_TypedAirfoil::InsertXo
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

void tnbLib::PtdShapeFit2d_TypedAirfoil::InsertYo
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

void tnbLib::PtdShapeFit2d_TypedAirfoil::InsertChordLen
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(ChordLenId()) = x;
}

void tnbLib::PtdShapeFit2d_TypedAirfoil::InsertAngle
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(AngleId()) = x;
}

std::tuple
<
	tnbLib::PtdShapeFit2d_TypedAirfoil::xoPar,
	tnbLib::PtdShapeFit2d_TypedAirfoil::yoPar,
	tnbLib::PtdShapeFit2d_TypedAirfoil::chordLenPar,
	tnbLib::PtdShapeFit2d_TypedAirfoil::anglePar
>
tnbLib::PtdShapeFit2d_TypedAirfoil::RetrieveParameters(const std::vector<Standard_Real>& xs)
{
	xoPar p0 = { GetXo(xs) };
	yoPar p1 = { GetYo(xs) };
	chordLenPar p2 = { GetChordLen(xs) };
	anglePar p3 = { GetAngle(xs) };

	auto t = std::make_tuple(std::move(p0), std::move(p1), std::move(p2), std::move(p3));
	return std::move(t);
}

void tnbLib::PtdShapeFit2d_TypedAirfoil::CheckVector(const std::vector<Standard_Real>& xs)
{
	if (xs.size() NOT_EQUAL PtdShapeFit2d_TypedAirfoil::nb_parameters)
	{
		FatalErrorIn(FunctionSIG)
			<< "the vector is incompatible with this section." << endl
			<< abort(FatalError);
	}
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::PtdShapeFit2d_TypedAirfoil::CreateXo
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)PtdShapeFit2d_TypedAirfoil::xoPar::id + 1);
	par->SetName(xoPar::name);
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::PtdShapeFit2d_TypedAirfoil::CreateYo
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)PtdShapeFit2d_TypedAirfoil::yoPar::id + 1);
	par->SetName(yoPar::name);
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::PtdShapeFit2d_TypedAirfoil::CreateChordLen
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)PtdShapeFit2d_TypedAirfoil::chordLenPar::id + 1);
	par->SetName(chordLenPar::name);
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::PtdShapeFit2d_TypedAirfoil::CreateAngle
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)PtdShapeFit2d_TypedAirfoil::anglePar::id + 1);
	par->SetName(anglePar::name);
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit2d_TypedAirfoil::Parameters>
tnbLib::PtdShapeFit2d_TypedAirfoil::CreateParChromosome
(
	const Standard_Real theXo,
	const Standard_Real theYo,
	const Standard_Real theAngle,
	const Standard_Real theRadius
)
{
	std::vector<Param> pars(nb_parameters);
	{
		Param p{ theXo,xoPar::name };
		pars.at(XoId()) = std::move(p);
	}
	{
		Param p{ theYo,yoPar::name };
		pars.at(YoId()) = std::move(p);
	}
	{
		Param p{ theAngle,anglePar::name };
		pars.at(AngleId()) = std::move(p);
	}
	{
		Param p{ theRadius,chordLenPar::name };
		pars.at(ChordLenId()) = std::move(p);
	}
	Parameters pchromRef = { std::move(pars) };
	auto pchrom = std::make_shared<Parameters>(std::move(pchromRef));
	return std::move(pchrom);
}