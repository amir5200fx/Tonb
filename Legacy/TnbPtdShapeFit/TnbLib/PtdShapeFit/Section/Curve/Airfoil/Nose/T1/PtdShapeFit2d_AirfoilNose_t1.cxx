#include <PtdShapeFit2d_AirfoilNose_t1.hxx>

#include <PtdShapeFit_Par.hxx>

const char* tnbLib::curveLib::airfoilLib::Type1::xoPar::name = "xo";
const char* tnbLib::curveLib::airfoilLib::Type1::yoPar::name = "yo";

const char* tnbLib::curveLib::airfoilLib::Type1::upperMaxPar::name = "upperMax";
const char* tnbLib::curveLib::airfoilLib::Type1::upperMaxLocPar::name = "upperMaxLoc";
const char* tnbLib::curveLib::airfoilLib::Type1::upperNoseTightPar::name = "upperNoseTight";
const char* tnbLib::curveLib::airfoilLib::Type1::upperTightPar::name = "upperTight";

const char* tnbLib::curveLib::airfoilLib::Type1::lowerMaxPar::name = "lowerMax";
const char* tnbLib::curveLib::airfoilLib::Type1::lowerMaxLocPar::name = "lowerMaxLoc";
const char* tnbLib::curveLib::airfoilLib::Type1::lowerNoseTightPar::name = "lowerNoseTight";
const char* tnbLib::curveLib::airfoilLib::Type1::lowerTightPar::name = "lowerTight";

std::map<Standard_Integer, const char*> tnbLib::curveLib::airfoilLib::Type1::ParsMap;

namespace tnbLib
{

	namespace curveLib
	{
		class AirfoilNoseType1RunTime
		{

			/*Private Data*/

		public:

			// default constructor [4/28/2023 Payvand]

			AirfoilNoseType1RunTime()
			{
				SetConfig();
			}

			void SetConfig();

		};
	}
}

void tnbLib::curveLib::AirfoilNoseType1RunTime::SetConfig()
{
	{
		auto paired = std::make_pair(airfoilLib::Type1::xoPar::id, airfoilLib::Type1::xoPar::name);
		airfoilLib::Type1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type1::yoPar::id, airfoilLib::Type1::yoPar::name);
		airfoilLib::Type1::ParsMap.insert(std::move(paired));
	}

	{
		auto paired = std::make_pair(airfoilLib::Type1::upperMaxPar::id, airfoilLib::Type1::upperMaxPar::name);
		airfoilLib::Type1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type1::upperMaxLocPar::id, airfoilLib::Type1::upperMaxLocPar::name);
		airfoilLib::Type1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type1::upperNoseTightPar::id, airfoilLib::Type1::upperNoseTightPar::name);
		airfoilLib::Type1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type1::upperTightPar::id, airfoilLib::Type1::upperTightPar::name);
		airfoilLib::Type1::ParsMap.insert(std::move(paired));
	}

	{
		auto paired = std::make_pair(airfoilLib::Type1::lowerMaxPar::id, airfoilLib::Type1::lowerMaxPar::name);
		airfoilLib::Type1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type1::lowerMaxLocPar::id, airfoilLib::Type1::lowerMaxLocPar::name);
		airfoilLib::Type1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type1::lowerNoseTightPar::id, airfoilLib::Type1::lowerNoseTightPar::name);
		airfoilLib::Type1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type1::lowerTightPar::id, airfoilLib::Type1::lowerTightPar::name);
		airfoilLib::Type1::ParsMap.insert(std::move(paired));
	}
}

tnbLib::curveLib::AirfoilNoseType1RunTime myCurveLibAirfoilNoseType1RunTimeObj;

const unsigned int tnbLib::curveLib::airfoilLib::Type1::nb_parameters = 10;
unsigned short tnbLib::curveLib::airfoilLib::Type1::verbose(0);

const char*
tnbLib::curveLib::airfoilLib::Type1::ParName
(
	const Standard_Integer theIndex
) const
{
	return ParsMap.at(theIndex);
}

std::shared_ptr<tnbLib::curveLib::airfoilLib::Type1::Parameters>
tnbLib::curveLib::airfoilLib::Type1::RetrieveParChromosome
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
		Param p{ GetUpperMax(theChromosome),UpperMaxName() };
		pars.at(UpperMaxId()) = std::move(p);
	}
	{
		Param p{ GetUpperMaxLoc(theChromosome),UpperMaxLocName() };
		pars.at(UpperMaxLocId()) = std::move(p);
	}
	{
		Param p{ GetUpperNoseTight(theChromosome),UpperNoseTightName() };
		pars.at(UpperNoseTightId()) = std::move(p);
	}
	{
		Param p{ GetUpperTight(theChromosome),UpperTightName() };
		pars.at(UpperTightId()) = std::move(p);
	}

	{
		Param p{ GetLowerMax(theChromosome),LowerMaxName() };
		pars.at(LowerMaxId()) = std::move(p);
	}
	{
		Param p{ GetLowerMaxLoc(theChromosome),LowerMaxLocName() };
		pars.at(LowerMaxLocId()) = std::move(p);
	}
	{
		Param p{ GetLowerNoseTight(theChromosome),LowerNoseTightName() };
		pars.at(LowerNoseTightId()) = std::move(p);
	}
	{
		Param p{ GetLowerTight(theChromosome),LowerTightName() };
		pars.at(LowerTightId()) = std::move(p);
	}
	
	Parameters pchromRef = { std::move(pars) };
	auto pchrom = std::make_shared<Parameters>(std::move(pchromRef));
	return std::move(pchrom);
}

std::vector<std::shared_ptr<tnbLib::PtdShapeFit_Par>>
tnbLib::curveLib::airfoilLib::Type1::RetrieveParList() const
{
	std::vector<std::shared_ptr<PtdShapeFit_Par>> pars(NbPars());
	pars.at(XoId()) = Xo();
	pars.at(YoId()) = Yo();

	pars.at(UpperMaxId()) = UpperMax();
	pars.at(UpperMaxLocId()) = UpperMaxLoc();
	pars.at(UpperNoseTightId()) = UpperNoseTight();
	pars.at(UpperTightId()) = UpperTight();

	pars.at(LowerMaxId()) = LowerMax();
	pars.at(LowerMaxLocId()) = LowerMaxLoc();
	pars.at(LowerNoseTightId()) = LowerNoseTight();
	pars.at(LowerTightId()) = LowerTight();
	return std::move(pars);
}

std::vector<Standard_Real>
tnbLib::curveLib::airfoilLib::Type1::RetrieveChromosome
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

		chromosome.at(UpperMaxId()) = pars.x.at(UpperMaxId()).x;
		chromosome.at(UpperMaxLocId()) = pars.x.at(UpperMaxLocId()).x;
		chromosome.at(UpperNoseTightId()) = pars.x.at(UpperNoseTightId()).x;
		chromosome.at(UpperTightId()) = pars.x.at(UpperTightId()).x;

		chromosome.at(LowerMaxId()) = pars.x.at(LowerMaxId()).x;
		chromosome.at(LowerMaxLocId()) = pars.x.at(LowerMaxLocId()).x;
		chromosome.at(LowerNoseTightId()) = pars.x.at(LowerNoseTightId()).x;
		chromosome.at(LowerTightId()) = pars.x.at(LowerTightId()).x;

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

void tnbLib::curveLib::airfoilLib::Type1::SetParameters
(
	const std::vector<Standard_Real>& theXs
)
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
		Param x = { GetUpperMax(theXs),UpperMaxName() };
		pars.at(UpperMaxId()) = std::move(x);
	}
	{
		Param x = { GetUpperMaxLoc(theXs),UpperMaxLocName() };
		pars.at(UpperMaxLocId()) = std::move(x);
	}
	{
		Param x = { GetUpperNoseTight(theXs),UpperNoseTightName() };
		pars.at(UpperNoseTightId()) = std::move(x);
	}
	{
		Param x = { GetUpperTight(theXs),UpperTightName() };
		pars.at(UpperTightId()) = std::move(x);
	}

	{
		Param x = { GetLowerMax(theXs),LowerMaxName() };
		pars.at(LowerMaxId()) = std::move(x);
	}
	{
		Param x = { GetLowerMaxLoc(theXs),LowerMaxLocName() };
		pars.at(LowerMaxLocId()) = std::move(x);
	}
	{
		Param x = { GetLowerNoseTight(theXs),LowerNoseTightName() };
		pars.at(LowerNoseTightId()) = std::move(x);
	}
	{
		Param x = { GetLowerTight(theXs),LowerTightName() };
		pars.at(LowerTightId()) = std::move(x);
	}

	Parameters xPars = { std::move(pars) };
	ParsRef() = std::make_shared<Parameters>(std::move(xPars));
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Type1::NbPars() const
{
	return Standard_Integer(nb_parameters);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Type1::XoId()
{
	return Standard_Integer(xoPar::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Type1::YoId()
{
	return Standard_Integer(yoPar::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Type1::UpperMaxId()
{
	return Standard_Integer(upperMaxPar::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Type1::UpperMaxLocId()
{
	return Standard_Integer(upperMaxLocPar::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Type1::UpperNoseTightId()
{
	return Standard_Integer(upperNoseTightPar::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Type1::UpperTightId()
{
	return Standard_Integer(upperTightPar::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Type1::LowerMaxId()
{
	return Standard_Integer(lowerMaxPar::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Type1::LowerMaxLocId()
{
	return Standard_Integer(lowerMaxLocPar::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Type1::LowerNoseTightId()
{
	return Standard_Integer(lowerNoseTightPar::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Type1::LowerTightId()
{
	return Standard_Integer(lowerTightPar::id);
}

Standard_Real
tnbLib::curveLib::airfoilLib::Type1::GetXo(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(XoId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Type1::GetYo(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(YoId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Type1::GetUpperMax(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(UpperMaxId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Type1::GetUpperMaxLoc(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(UpperMaxLocId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Type1::GetUpperNoseTight(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(UpperNoseTightId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Type1::GetUpperTight(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(UpperTightId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Type1::GetLowerMax(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(LowerMaxId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Type1::GetLowerMaxLoc(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(LowerMaxLocId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Type1::GetLowerNoseTight(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(LowerNoseTightId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Type1::GetLowerTight(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(LowerTightId());
}

void tnbLib::curveLib::airfoilLib::Type1::InsertXo
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

void tnbLib::curveLib::airfoilLib::Type1::InsertYo
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

void tnbLib::curveLib::airfoilLib::Type1::InsertUpperMax
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(UpperMaxId()) = x;
}

void tnbLib::curveLib::airfoilLib::Type1::InsertUpperMaxLoc
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(UpperMaxLocId()) = x;
}

void tnbLib::curveLib::airfoilLib::Type1::InsertUpperNoseTight
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(UpperNoseTightId()) = x;
}

void tnbLib::curveLib::airfoilLib::Type1::InsertUpperTight
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(UpperTightId()) = x;
}

void tnbLib::curveLib::airfoilLib::Type1::InsertLowerMax
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(LowerMaxId()) = x;
}

void tnbLib::curveLib::airfoilLib::Type1::InsertLowerMaxLoc
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(LowerMaxLocId()) = x;
}

void tnbLib::curveLib::airfoilLib::Type1::InsertLowerNoseTight
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(LowerNoseTightId()) = x;
}

void tnbLib::curveLib::airfoilLib::Type1::InsertLowerTight
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(LowerTightId()) = x;
}

void tnbLib::curveLib::airfoilLib::Type1::CheckVector(const std::vector<Standard_Real>& xs)
{
	if (xs.size() NOT_EQUAL Type1::nb_parameters)
	{
		FatalErrorIn(FunctionSIG)
			<< "the vector is incompatible with this section." << endl
			<< abort(FatalError);
	}
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Type1::CreateXo
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type1::xoPar::id + 1);
	par->SetName("xo");
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Type1::CreateYo
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type1::yoPar::id + 1);
	par->SetName("yo");
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Type1::CreateUpperMax
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type1::upperMaxPar::id + 1);
	par->SetName(UpperMaxName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Type1::CreateUpperMaxLoc
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type1::upperMaxLocPar::id + 1);
	par->SetName(UpperMaxLocName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Type1::CreateUpperNoseTight
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type1::upperNoseTightPar::id + 1);
	par->SetName(UpperNoseTightName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Type1::CreateUpperTight
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type1::upperTightPar::id + 1);
	par->SetName(UpperTightName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Type1::CreateLowerMax
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type1::lowerMaxPar::id + 1);
	par->SetName(LowerMaxName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Type1::CreateLowerMaxLoc
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type1::lowerMaxLocPar::id + 1);
	par->SetName(LowerMaxLocName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Type1::CreateLowerNoseTight
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type1::lowerNoseTightPar::id + 1);
	par->SetName(LowerNoseTightName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Type1::CreateLowerTight
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type1::lowerTightPar::id + 1);
	par->SetName(LowerTightName());
	return std::move(par);
}

std::tuple
<
	tnbLib::curveLib::airfoilLib::Type1::xoPar,
	tnbLib::curveLib::airfoilLib::Type1::yoPar,

	tnbLib::curveLib::airfoilLib::Type1::upperMaxPar,
	tnbLib::curveLib::airfoilLib::Type1::upperMaxLocPar,
	tnbLib::curveLib::airfoilLib::Type1::upperNoseTightPar,
	tnbLib::curveLib::airfoilLib::Type1::upperTightPar,

	tnbLib::curveLib::airfoilLib::Type1::lowerMaxPar,
	tnbLib::curveLib::airfoilLib::Type1::lowerMaxLocPar,
	tnbLib::curveLib::airfoilLib::Type1::lowerNoseTightPar,
	tnbLib::curveLib::airfoilLib::Type1::lowerTightPar
>
tnbLib::curveLib::airfoilLib::Type1::RetrieveParameters(const std::vector<Standard_Real>& xs)
{
	xoPar p0 = { GetXo(xs) };
	yoPar p1 = { GetYo(xs) };

	upperMaxPar p2 = { GetUpperMax(xs) };
	upperMaxLocPar p3 = { GetUpperMaxLoc(xs) };
	upperNoseTightPar p4 = { GetUpperNoseTight(xs) };
	upperTightPar p5 = { GetUpperTight(xs) };

	lowerMaxPar p6 = { GetLowerMax(xs) };
	lowerMaxLocPar p7 = { GetLowerMaxLoc(xs) };
	lowerNoseTightPar p8 = { GetLowerNoseTight(xs) };
	lowerTightPar p9 = { GetLowerTight(xs) };

	auto t = std::make_tuple
	(
		std::move(p0),
		std::move(p1),
		std::move(p2),
		std::move(p3),
		std::move(p4),
		std::move(p5),
		std::move(p6),
		std::move(p7),
		std::move(p8),
		std::move(p9)
	);
	return std::move(t);
}

std::shared_ptr<tnbLib::curveLib::airfoilLib::Type1::Parameters>
tnbLib::curveLib::airfoilLib::Type1::CreateParChromosome
(
	const Standard_Real theXo,
	const Standard_Real theYo,
	const Standard_Real theUpperMax,
	const Standard_Real theUppermaxLoc,
	const Standard_Real theUpperNoseTight,
	const Standard_Real theUpperTight,
	const Standard_Real theLowerMax,
	const Standard_Real theLowermaxLoc, 
	const Standard_Real theLowerNoseTight, 
	const Standard_Real theLowerTight
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
		Param p{ theUpperMax,upperMaxPar::name };
		pars.at(UpperMaxId()) = std::move(p);
	}
	{
		Param p{ theUppermaxLoc,upperMaxLocPar::name };
		pars.at(UpperMaxLocId()) = std::move(p);
	}
	{
		Param p{ theUpperNoseTight,upperNoseTightPar::name };
		pars.at(UpperNoseTightId()) = std::move(p);
	}
	{
		Param p{ theUpperTight,upperTightPar::name };
		pars.at(UpperTightId()) = std::move(p);
	}

	{
		Param p{ theLowerMax,lowerMaxPar::name };
		pars.at(LowerMaxId()) = std::move(p);
	}
	{
		Param p{ theLowermaxLoc,lowerMaxLocPar::name };
		pars.at(LowerMaxLocId()) = std::move(p);
	}
	{
		Param p{ theLowerNoseTight,lowerNoseTightPar::name };
		pars.at(LowerNoseTightId()) = std::move(p);
	}
	{
		Param p{ theLowerTight,lowerTightPar::name };
		pars.at(LowerTightId()) = std::move(p);
	}
	Parameters pchromRef = { std::move(pars) };
	auto pchrom = std::make_shared<Parameters>(std::move(pchromRef));
	return std::move(pchrom);
}