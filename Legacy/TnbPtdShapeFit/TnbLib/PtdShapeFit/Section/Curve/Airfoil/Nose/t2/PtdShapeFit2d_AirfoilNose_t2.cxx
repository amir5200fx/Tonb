#include <PtdShapeFit2d_AirfoilNose_t2.hxx>

#include <PtdShapeFit_Par.hxx>

const char* tnbLib::curveLib::airfoilLib::Type2::xoPar::name = "xo";
const char* tnbLib::curveLib::airfoilLib::Type2::yoPar::name = "yo";

const char* tnbLib::curveLib::airfoilLib::Type2::noseAnglePar::name = "noseAngle";

const char* tnbLib::curveLib::airfoilLib::Type2::upperMaxPar::name = "upperMax";
const char* tnbLib::curveLib::airfoilLib::Type2::upperMaxLocPar::name = "upperMaxLoc";
const char* tnbLib::curveLib::airfoilLib::Type2::upperMaxAnglePar::name = "upperMaxAngle";
const char* tnbLib::curveLib::airfoilLib::Type2::upperNoseTightPar::name = "upperNoseTight";
const char* tnbLib::curveLib::airfoilLib::Type2::upperTightPar::name = "upperTight";

const char* tnbLib::curveLib::airfoilLib::Type2::lowerMaxPar::name = "lowerMax";
const char* tnbLib::curveLib::airfoilLib::Type2::lowerMaxLocPar::name = "lowerMaxLoc";
const char* tnbLib::curveLib::airfoilLib::Type2::lowerMaxAnglePar::name = "lowerMaxAngle";
const char* tnbLib::curveLib::airfoilLib::Type2::lowerNoseTightPar::name = "lowerNoseTight";
const char* tnbLib::curveLib::airfoilLib::Type2::lowerTightPar::name = "lowerTight";

std::map<Standard_Integer, const char*> tnbLib::curveLib::airfoilLib::Type2::ParsMap;

namespace tnbLib
{

	namespace curveLib
	{
		class AirfoilNoseType2RunTime
		{

			/*Private Data*/

		public:

			// default constructor [4/28/2023 Payvand]

			AirfoilNoseType2RunTime()
			{
				SetConfig();
			}

			void SetConfig();

		};
	}
}

void tnbLib::curveLib::AirfoilNoseType2RunTime::SetConfig()
{
	{
		auto paired = std::make_pair(airfoilLib::Type2::xoPar::id, airfoilLib::Type2::xoPar::name);
		airfoilLib::Type2::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type2::yoPar::id, airfoilLib::Type2::yoPar::name);
		airfoilLib::Type2::ParsMap.insert(std::move(paired));
	}

	{
		auto paired = std::make_pair(airfoilLib::Type2::noseAnglePar::id, airfoilLib::Type2::noseAnglePar::name);
		airfoilLib::Type2::ParsMap.insert(std::move(paired));
	}

	{
		auto paired = std::make_pair(airfoilLib::Type2::upperMaxPar::id, airfoilLib::Type2::upperMaxPar::name);
		airfoilLib::Type2::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type2::upperMaxLocPar::id, airfoilLib::Type2::upperMaxLocPar::name);
		airfoilLib::Type2::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type2::upperMaxAnglePar::id, airfoilLib::Type2::upperMaxAnglePar::name);
		airfoilLib::Type2::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type2::upperNoseTightPar::id, airfoilLib::Type2::upperNoseTightPar::name);
		airfoilLib::Type2::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type2::upperTightPar::id, airfoilLib::Type2::upperTightPar::name);
		airfoilLib::Type2::ParsMap.insert(std::move(paired));
	}

	{
		auto paired = std::make_pair(airfoilLib::Type2::lowerMaxPar::id, airfoilLib::Type2::lowerMaxPar::name);
		airfoilLib::Type2::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type2::lowerMaxLocPar::id, airfoilLib::Type2::lowerMaxLocPar::name);
		airfoilLib::Type2::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type2::lowerMaxAnglePar::id, airfoilLib::Type2::lowerMaxAnglePar::name);
		airfoilLib::Type2::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type2::lowerNoseTightPar::id, airfoilLib::Type2::lowerNoseTightPar::name);
		airfoilLib::Type2::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type2::lowerTightPar::id, airfoilLib::Type2::lowerTightPar::name);
		airfoilLib::Type2::ParsMap.insert(std::move(paired));
	}
}

tnbLib::curveLib::AirfoilNoseType2RunTime myCurveLibAirfoilNoseType2RunTimeObj;

const unsigned int tnbLib::curveLib::airfoilLib::Type2::nb_parameters = 12;
unsigned short tnbLib::curveLib::airfoilLib::Type2::verbose(0);

const char*
tnbLib::curveLib::airfoilLib::Type2::ParName
(
	const Standard_Integer theIndex
) const
{
	return ParsMap.at(theIndex);
}

std::shared_ptr<tnbLib::curveLib::airfoilLib::Type2::Parameters>
tnbLib::curveLib::airfoilLib::Type2::RetrieveParChromosome
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
		Param p{ GetNoseAngle(theChromosome),NoseAngleName() };
		pars.at(NoseAngleId()) = std::move(p);
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
		Param p{ GetUpperMaxAngle(theChromosome),UpperMaxAngleName() };
		pars.at(UpperMaxAngleId()) = std::move(p);
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
		Param p{ GetLowerMaxAngle(theChromosome),LowerMaxAngleName() };
		pars.at(LowerMaxAngleId()) = std::move(p);
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
tnbLib::curveLib::airfoilLib::Type2::RetrieveParList() const
{
	std::vector<std::shared_ptr<PtdShapeFit_Par>> pars(NbPars());
	pars.at(XoId()) = Xo();
	pars.at(YoId()) = Yo();

	pars.at(NoseAngleId()) = NoseAngle();

	pars.at(UpperMaxId()) = UpperMax();
	pars.at(UpperMaxLocId()) = UpperMaxLoc();
	pars.at(UpperMaxAngleId()) = UpperMaxAngle();
	pars.at(UpperNoseTightId()) = UpperNoseTight();
	pars.at(UpperTightId()) = UpperTight();

	pars.at(LowerMaxId()) = LowerMax();
	pars.at(LowerMaxLocId()) = LowerMaxLoc();
	pars.at(LowerMaxAngleId()) = LowerMaxAngle();
	pars.at(LowerNoseTightId()) = LowerNoseTight();
	pars.at(LowerTightId()) = LowerTight();
	return std::move(pars);
}

std::vector<Standard_Real>
tnbLib::curveLib::airfoilLib::Type2::RetrieveChromosome
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

		chromosome.at(NoseAngleId()) = pars.x.at(NoseAngleId()).x;

		chromosome.at(UpperMaxId()) = pars.x.at(UpperMaxId()).x;
		chromosome.at(UpperMaxLocId()) = pars.x.at(UpperMaxLocId()).x;
		chromosome.at(UpperMaxAngleId()) = pars.x.at(UpperMaxAngleId()).x;
		chromosome.at(UpperNoseTightId()) = pars.x.at(UpperNoseTightId()).x;
		chromosome.at(UpperTightId()) = pars.x.at(UpperTightId()).x;

		chromosome.at(LowerMaxId()) = pars.x.at(LowerMaxId()).x;
		chromosome.at(LowerMaxLocId()) = pars.x.at(LowerMaxLocId()).x;
		chromosome.at(LowerMaxAngleId()) = pars.x.at(LowerMaxAngleId()).x;
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

void tnbLib::curveLib::airfoilLib::Type2::SetParameters
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
		Param x = { GetNoseAngle(theXs),NoseAngleName() };
		pars.at(NoseAngleId()) = std::move(x);
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
		Param x = { GetUpperMaxAngle(theXs),UpperMaxAngleName() };
		pars.at(UpperMaxAngleId()) = std::move(x);
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
		Param x = { GetLowerMaxAngle(theXs),LowerMaxAngleName() };
		pars.at(LowerMaxAngleId()) = std::move(x);
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
tnbLib::curveLib::airfoilLib::Type2::NbPars() const
{
	return Standard_Integer(nb_parameters);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Type2::XoId()
{
	return Standard_Integer(xoPar::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Type2::YoId()
{
	return Standard_Integer(yoPar::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Type2::NoseAngleId()
{
	return Standard_Integer(noseAnglePar::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Type2::UpperMaxId()
{
	return Standard_Integer(upperMaxPar::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Type2::UpperMaxLocId()
{
	return Standard_Integer(upperMaxLocPar::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Type2::UpperMaxAngleId()
{
	return Standard_Integer(upperMaxAnglePar::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Type2::UpperNoseTightId()
{
	return Standard_Integer(upperNoseTightPar::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Type2::UpperTightId()
{
	return Standard_Integer(upperTightPar::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Type2::LowerMaxId()
{
	return Standard_Integer(lowerMaxPar::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Type2::LowerMaxLocId()
{
	return Standard_Integer(lowerMaxLocPar::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Type2::LowerMaxAngleId()
{
	return Standard_Integer(lowerMaxAnglePar::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Type2::LowerNoseTightId()
{
	return Standard_Integer(lowerNoseTightPar::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Type2::LowerTightId()
{
	return Standard_Integer(lowerTightPar::id);
}

Standard_Real
tnbLib::curveLib::airfoilLib::Type2::GetXo(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(XoId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Type2::GetYo(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(YoId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Type2::GetNoseAngle(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(NoseAngleId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Type2::GetUpperMax(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(UpperMaxId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Type2::GetUpperMaxLoc(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(UpperMaxLocId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Type2::GetUpperMaxAngle(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(UpperMaxAngleId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Type2::GetUpperNoseTight(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(UpperNoseTightId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Type2::GetUpperTight(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(UpperTightId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Type2::GetLowerMax(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(LowerMaxId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Type2::GetLowerMaxLoc(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(LowerMaxLocId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Type2::GetLowerMaxAngle(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(LowerMaxAngleId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Type2::GetLowerNoseTight(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(LowerNoseTightId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Type2::GetLowerTight(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(LowerTightId());
}

void tnbLib::curveLib::airfoilLib::Type2::InsertXo
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

void tnbLib::curveLib::airfoilLib::Type2::InsertYo
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

void tnbLib::curveLib::airfoilLib::Type2::InsertNoseAngle
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(NoseAngleId()) = x;
}

void tnbLib::curveLib::airfoilLib::Type2::InsertUpperMax
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

void tnbLib::curveLib::airfoilLib::Type2::InsertUpperMaxLoc
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

void tnbLib::curveLib::airfoilLib::Type2::InsertUpperMaxAngle
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(UpperMaxAngleId()) = x;
}

void tnbLib::curveLib::airfoilLib::Type2::InsertUpperNoseTight
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

void tnbLib::curveLib::airfoilLib::Type2::InsertUpperTight
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

void tnbLib::curveLib::airfoilLib::Type2::InsertLowerMax
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

void tnbLib::curveLib::airfoilLib::Type2::InsertLowerMaxLoc
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

void tnbLib::curveLib::airfoilLib::Type2::InsertLowerMaxAngle
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(LowerMaxAngleId()) = x;
}

void tnbLib::curveLib::airfoilLib::Type2::InsertLowerNoseTight
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

void tnbLib::curveLib::airfoilLib::Type2::InsertLowerTight
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

void tnbLib::curveLib::airfoilLib::Type2::CheckVector(const std::vector<Standard_Real>& xs)
{
	if (xs.size() NOT_EQUAL Type2::nb_parameters)
	{
		FatalErrorIn(FunctionSIG)
			<< "the vector is incompatible with this section." << endl
			<< abort(FatalError);
	}
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Type2::CreateXo
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type2::xoPar::id + 1);
	par->SetName("xo");
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Type2::CreateYo
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type2::yoPar::id + 1);
	par->SetName("yo");
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Type2::CreateNoseAngle
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type2::noseAnglePar::id + 1);
	par->SetName(NoseAngleName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Type2::CreateUpperMax
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type2::upperMaxPar::id + 1);
	par->SetName(UpperMaxName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Type2::CreateUpperMaxLoc
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type2::upperMaxLocPar::id + 1);
	par->SetName(UpperMaxLocName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Type2::CreateUpperMaxAngle
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type2::upperMaxAnglePar::id + 1);
	par->SetName(UpperMaxAngleName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Type2::CreateUpperNoseTight
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type2::upperNoseTightPar::id + 1);
	par->SetName(UpperNoseTightName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Type2::CreateUpperTight
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type2::upperTightPar::id + 1);
	par->SetName(UpperTightName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Type2::CreateLowerMax
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type2::lowerMaxPar::id + 1);
	par->SetName(LowerMaxName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Type2::CreateLowerMaxLoc
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type2::lowerMaxLocPar::id + 1);
	par->SetName(LowerMaxLocName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Type2::CreateLowerMaxAngle
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type2::lowerMaxAnglePar::id + 1);
	par->SetName(LowerMaxAngleName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Type2::CreateLowerNoseTight
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type2::lowerNoseTightPar::id + 1);
	par->SetName(LowerNoseTightName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Type2::CreateLowerTight
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type2::lowerTightPar::id + 1);
	par->SetName(LowerTightName());
	return std::move(par);
}

std::tuple
<
	tnbLib::curveLib::airfoilLib::Type2::xoPar,
	tnbLib::curveLib::airfoilLib::Type2::yoPar,

	tnbLib::curveLib::airfoilLib::Type2::noseAnglePar,

	tnbLib::curveLib::airfoilLib::Type2::upperMaxPar,
	tnbLib::curveLib::airfoilLib::Type2::upperMaxLocPar,
	tnbLib::curveLib::airfoilLib::Type2::upperMaxAnglePar,
	tnbLib::curveLib::airfoilLib::Type2::upperNoseTightPar,
	tnbLib::curveLib::airfoilLib::Type2::upperTightPar,

	tnbLib::curveLib::airfoilLib::Type2::lowerMaxPar,
	tnbLib::curveLib::airfoilLib::Type2::lowerMaxLocPar,
	tnbLib::curveLib::airfoilLib::Type2::lowerMaxAnglePar,
	tnbLib::curveLib::airfoilLib::Type2::lowerNoseTightPar,
	tnbLib::curveLib::airfoilLib::Type2::lowerTightPar
>
tnbLib::curveLib::airfoilLib::Type2::RetrieveParameters(const std::vector<Standard_Real>& xs)
{
	xoPar p0 = { GetXo(xs) };
	yoPar p1 = { GetYo(xs) };

	noseAnglePar p2 = { GetNoseAngle(xs) };

	upperMaxPar p3 = { GetUpperMax(xs) };
	upperMaxLocPar p4 = { GetUpperMaxLoc(xs) };
	upperMaxAnglePar p5 = { GetUpperMaxAngle(xs) };
	upperNoseTightPar p6 = { GetUpperNoseTight(xs) };
	upperTightPar p7 = { GetUpperTight(xs) };

	lowerMaxPar p8 = { GetLowerMax(xs) };
	lowerMaxLocPar p9 = { GetLowerMaxLoc(xs) };
	lowerMaxAnglePar p10 = { GetLowerMaxAngle(xs) };
	lowerNoseTightPar p11 = { GetLowerNoseTight(xs) };
	lowerTightPar p12 = { GetLowerTight(xs) };

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
		std::move(p9),
		std::move(p10),
		std::move(p11),
		std::move(p12)
	);
	return std::move(t);
}

std::shared_ptr<tnbLib::curveLib::airfoilLib::Type2::Parameters>
tnbLib::curveLib::airfoilLib::Type2::CreateParChromosome
(
	const Standard_Real theXo,
	const Standard_Real theYo,
	const Standard_Real theNoseAngle,
	const Standard_Real theUpperMax,
	const Standard_Real theUppermaxLoc,
	const Standard_Real theUpperMaxAngle,
	const Standard_Real theUpperNoseTight,
	const Standard_Real theUpperTight,
	const Standard_Real theLowerMax,
	const Standard_Real theLowermaxLoc,
	const Standard_Real theLowermaxAngle,
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
		Param p{ theYo,noseAnglePar::name };
		pars.at(NoseAngleId()) = std::move(p);
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
		Param p{ theUppermaxLoc,upperMaxAnglePar::name };
		pars.at(UpperMaxAngleId()) = std::move(p);
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
		Param p{ theLowermaxLoc,lowerMaxAnglePar::name };
		pars.at(LowerMaxAngleId()) = std::move(p);
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