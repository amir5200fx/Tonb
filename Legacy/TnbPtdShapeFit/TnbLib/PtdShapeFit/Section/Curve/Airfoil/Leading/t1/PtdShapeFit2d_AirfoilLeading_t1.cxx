#include <PtdShapeFit2d_AirfoilLeading_t1.hxx>

#include <PtdShapeFit_Par.hxx>

const char* tnbLib::curveLib::airfoilLib::Leading_t1::xoPar::name = "xo";
const char* tnbLib::curveLib::airfoilLib::Leading_t1::yoPar::name = "yo";

const char* tnbLib::curveLib::airfoilLib::Leading_t1::noseAnglePar::name = "noseAngle";

const char* tnbLib::curveLib::airfoilLib::Leading_t1::upperMaxPar::name = "upperMax";
const char* tnbLib::curveLib::airfoilLib::Leading_t1::upperMaxLocPar::name = "upperMaxLoc";
const char* tnbLib::curveLib::airfoilLib::Leading_t1::upperMaxAnglePar::name = "upperMaxAngle";
const char* tnbLib::curveLib::airfoilLib::Leading_t1::upperTightPar::name = "upperTight";
const char* tnbLib::curveLib::airfoilLib::Leading_t1::upperWeight0Par::name = "upperWeight0";
const char* tnbLib::curveLib::airfoilLib::Leading_t1::upperWeight1Par::name = "upperWeight1";
const char* tnbLib::curveLib::airfoilLib::Leading_t1::upperWeight2Par::name = "upperWeight2";

const char* tnbLib::curveLib::airfoilLib::Leading_t1::lowerMaxPar::name = "lowerMax";
const char* tnbLib::curveLib::airfoilLib::Leading_t1::lowerMaxLocPar::name = "lowerMaxLoc";
const char* tnbLib::curveLib::airfoilLib::Leading_t1::lowerMaxAnglePar::name = "lowerMaxAngle";
const char* tnbLib::curveLib::airfoilLib::Leading_t1::lowerTightPar::name = "lowerTight";
const char* tnbLib::curveLib::airfoilLib::Leading_t1::lowerWeight0Par::name = "lowerWeight0";
const char* tnbLib::curveLib::airfoilLib::Leading_t1::lowerWeight1Par::name = "lowerWeight1";
const char* tnbLib::curveLib::airfoilLib::Leading_t1::lowerWeight2Par::name = "lowerWeight2";

std::map<Standard_Integer, const char*> tnbLib::curveLib::airfoilLib::Leading_t1::ParsMap;

namespace tnbLib
{

	namespace curveLib
	{
		class AirfoilLeadingType1RunTime
		{

			/*Private Data*/

		public:

			// default constructor [4/28/2023 Payvand]

			AirfoilLeadingType1RunTime()
			{
				SetConfig();
			}

			void SetConfig();

		};
	}
}

void tnbLib::curveLib::AirfoilLeadingType1RunTime::SetConfig()
{
	{
		auto paired = std::make_pair(airfoilLib::Leading_t1::xoPar::id, airfoilLib::Leading_t1::xoPar::name);
		airfoilLib::Leading_t1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Leading_t1::yoPar::id, airfoilLib::Leading_t1::yoPar::name);
		airfoilLib::Leading_t1::ParsMap.insert(std::move(paired));
	}

	{
		auto paired = std::make_pair(airfoilLib::Leading_t1::noseAnglePar::id, airfoilLib::Leading_t1::noseAnglePar::name);
		airfoilLib::Leading_t1::ParsMap.insert(std::move(paired));
	}

	{
		auto paired = std::make_pair(airfoilLib::Leading_t1::upperMaxPar::id, airfoilLib::Leading_t1::upperMaxPar::name);
		airfoilLib::Leading_t1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Leading_t1::upperMaxLocPar::id, airfoilLib::Leading_t1::upperMaxLocPar::name);
		airfoilLib::Leading_t1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Leading_t1::upperMaxAnglePar::id, airfoilLib::Leading_t1::upperMaxAnglePar::name);
		airfoilLib::Leading_t1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Leading_t1::upperTightPar::id, airfoilLib::Leading_t1::upperTightPar::name);
		airfoilLib::Leading_t1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Leading_t1::upperWeight0Par::id, airfoilLib::Leading_t1::upperWeight0Par::name);
		airfoilLib::Leading_t1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Leading_t1::upperWeight1Par::id, airfoilLib::Leading_t1::upperWeight1Par::name);
		airfoilLib::Leading_t1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Leading_t1::upperWeight2Par::id, airfoilLib::Leading_t1::upperWeight2Par::name);
		airfoilLib::Leading_t1::ParsMap.insert(std::move(paired));
	}

	{
		auto paired = std::make_pair(airfoilLib::Leading_t1::lowerMaxPar::id, airfoilLib::Leading_t1::lowerMaxPar::name);
		airfoilLib::Leading_t1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Leading_t1::lowerMaxLocPar::id, airfoilLib::Leading_t1::lowerMaxLocPar::name);
		airfoilLib::Leading_t1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Leading_t1::lowerMaxAnglePar::id, airfoilLib::Leading_t1::lowerMaxAnglePar::name);
		airfoilLib::Leading_t1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Leading_t1::lowerTightPar::id, airfoilLib::Leading_t1::lowerTightPar::name);
		airfoilLib::Leading_t1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Leading_t1::lowerWeight0Par::id, airfoilLib::Leading_t1::lowerWeight0Par::name);
		airfoilLib::Leading_t1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Leading_t1::lowerWeight1Par::id, airfoilLib::Leading_t1::lowerWeight1Par::name);
		airfoilLib::Leading_t1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Leading_t1::lowerWeight2Par::id, airfoilLib::Leading_t1::lowerWeight2Par::name);
		airfoilLib::Leading_t1::ParsMap.insert(std::move(paired));
	}
}

tnbLib::curveLib::AirfoilLeadingType1RunTime myCurveLibAirfoilLeadingType1RunTimeObj;

const unsigned int tnbLib::curveLib::airfoilLib::Leading_t1::nb_parameters = 17;
unsigned short tnbLib::curveLib::airfoilLib::Leading_t1::verbose(0);

const char*
tnbLib::curveLib::airfoilLib::Leading_t1::ParName
(
	const Standard_Integer theIndex
) const
{
	return ParsMap.at(theIndex);
}

std::shared_ptr<tnbLib::curveLib::airfoilLib::Leading_t1::Parameters>
tnbLib::curveLib::airfoilLib::Leading_t1::RetrieveParChromosome
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
		Param p{ GetUpperTight(theChromosome),UpperTightName() };
		pars.at(UpperTightId()) = std::move(p);
	}
	{
		Param p{ GetUpperWeight0(theChromosome),UpperWeight0Name() };
		pars.at(UpperWeight0Id()) = std::move(p);
	}
	{
		Param p{ GetUpperWeight1(theChromosome),UpperWeight1Name() };
		pars.at(UpperWeight1Id()) = std::move(p);
	}
	{
		Param p{ GetUpperWeight2(theChromosome),UpperWeight2Name() };
		pars.at(UpperWeight2Id()) = std::move(p);
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
		Param p{ GetLowerTight(theChromosome),LowerTightName() };
		pars.at(LowerTightId()) = std::move(p);
	}
	{
		Param p{ GetLowerWeight0(theChromosome),LowerWeight0Name() };
		pars.at(LowerWeight0Id()) = std::move(p);
	}
	{
		Param p{ GetLowerWeight1(theChromosome),LowerWeight1Name() };
		pars.at(LowerWeight1Id()) = std::move(p);
	}
	{
		Param p{ GetLowerWeight2(theChromosome),LowerWeight2Name() };
		pars.at(LowerWeight2Id()) = std::move(p);
	}

	Parameters pchromRef = { std::move(pars) };
	auto pchrom = std::make_shared<Parameters>(std::move(pchromRef));
	return std::move(pchrom);
}

std::vector<std::shared_ptr<tnbLib::PtdShapeFit_Par>>
tnbLib::curveLib::airfoilLib::Leading_t1::RetrieveParList() const
{
	std::vector<std::shared_ptr<PtdShapeFit_Par>> pars(NbPars());
	pars.at(XoId()) = Xo();
	pars.at(YoId()) = Yo();

	pars.at(NoseAngleId()) = NoseAngle();

	pars.at(UpperMaxId()) = UpperMax();
	pars.at(UpperMaxLocId()) = UpperMaxLoc();
	pars.at(UpperMaxAngleId()) = UpperMaxAngle();
	pars.at(UpperTightId()) = UpperTight();
	pars.at(UpperWeight0Id()) = UpperWeight0();
	pars.at(UpperWeight1Id()) = UpperWeight1();
	pars.at(UpperWeight2Id()) = UpperWeight2();

	pars.at(LowerMaxId()) = LowerMax();
	pars.at(LowerMaxLocId()) = LowerMaxLoc();
	pars.at(LowerMaxAngleId()) = LowerMaxAngle();
	pars.at(LowerTightId()) = LowerTight();
	pars.at(LowerWeight0Id()) = LowerWeight0();
	pars.at(LowerWeight1Id()) = LowerWeight1();
	pars.at(LowerWeight2Id()) = LowerWeight2();
	return std::move(pars);
}

std::vector<Standard_Real>
tnbLib::curveLib::airfoilLib::Leading_t1::RetrieveChromosome
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
		chromosome.at(UpperTightId()) = pars.x.at(UpperTightId()).x;
		chromosome.at(UpperWeight0Id()) = pars.x.at(UpperWeight0Id()).x;
		chromosome.at(UpperWeight1Id()) = pars.x.at(UpperWeight1Id()).x;
		chromosome.at(UpperWeight2Id()) = pars.x.at(UpperWeight2Id()).x;

		chromosome.at(LowerMaxId()) = pars.x.at(LowerMaxId()).x;
		chromosome.at(LowerMaxLocId()) = pars.x.at(LowerMaxLocId()).x;
		chromosome.at(LowerMaxAngleId()) = pars.x.at(LowerMaxAngleId()).x;
		chromosome.at(LowerTightId()) = pars.x.at(LowerTightId()).x;
		chromosome.at(LowerWeight0Id()) = pars.x.at(LowerWeight0Id()).x;
		chromosome.at(LowerWeight1Id()) = pars.x.at(LowerWeight1Id()).x;
		chromosome.at(LowerWeight2Id()) = pars.x.at(LowerWeight2Id()).x;

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

void tnbLib::curveLib::airfoilLib::Leading_t1::SetParameters
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
		Param x = { GetUpperTight(theXs),UpperTightName() };
		pars.at(UpperTightId()) = std::move(x);
	}
	{
		Param x = { GetUpperWeight0(theXs),UpperWeight0Name() };
		pars.at(UpperWeight0Id()) = std::move(x);
	}
	{
		Param x = { GetUpperWeight1(theXs),UpperWeight1Name() };
		pars.at(UpperWeight1Id()) = std::move(x);
	}
	{
		Param x = { GetUpperWeight2(theXs),UpperWeight2Name() };
		pars.at(UpperWeight2Id()) = std::move(x);
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
		Param x = { GetLowerTight(theXs),LowerTightName() };
		pars.at(LowerTightId()) = std::move(x);
	}

	{
		Param x = { GetLowerWeight0(theXs),LowerWeight0Name() };
		pars.at(LowerWeight0Id()) = std::move(x);
	}
	{
		Param x = { GetLowerWeight1(theXs),LowerWeight1Name() };
		pars.at(LowerWeight1Id()) = std::move(x);
	}
	{
		Param x = { GetLowerWeight2(theXs),LowerWeight2Name() };
		pars.at(LowerWeight2Id()) = std::move(x);
	}

	Parameters xPars = { std::move(pars) };
	ParsRef() = std::make_shared<Parameters>(std::move(xPars));
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Leading_t1::NbPars() const
{
	return Standard_Integer(nb_parameters);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Leading_t1::XoId()
{
	return Standard_Integer(xoPar::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Leading_t1::YoId()
{
	return Standard_Integer(yoPar::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Leading_t1::NoseAngleId()
{
	return Standard_Integer(noseAnglePar::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Leading_t1::UpperMaxId()
{
	return Standard_Integer(upperMaxPar::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Leading_t1::UpperMaxLocId()
{
	return Standard_Integer(upperMaxLocPar::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Leading_t1::UpperMaxAngleId()
{
	return Standard_Integer(upperMaxAnglePar::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Leading_t1::UpperTightId()
{
	return Standard_Integer(upperTightPar::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Leading_t1::UpperWeight0Id()
{
	return Standard_Integer(upperWeight0Par::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Leading_t1::UpperWeight1Id()
{
	return Standard_Integer(upperWeight1Par::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Leading_t1::UpperWeight2Id()
{
	return Standard_Integer(upperWeight2Par::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Leading_t1::LowerMaxId()
{
	return Standard_Integer(lowerMaxPar::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Leading_t1::LowerMaxLocId()
{
	return Standard_Integer(lowerMaxLocPar::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Leading_t1::LowerMaxAngleId()
{
	return Standard_Integer(lowerMaxAnglePar::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Leading_t1::LowerTightId()
{
	return Standard_Integer(lowerTightPar::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Leading_t1::LowerWeight0Id()
{
	return Standard_Integer(lowerWeight0Par::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Leading_t1::LowerWeight1Id()
{
	return Standard_Integer(lowerWeight1Par::id);
}

Standard_Integer
tnbLib::curveLib::airfoilLib::Leading_t1::LowerWeight2Id()
{
	return Standard_Integer(lowerWeight2Par::id);
}

Standard_Real
tnbLib::curveLib::airfoilLib::Leading_t1::GetXo(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(XoId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Leading_t1::GetYo(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(YoId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Leading_t1::GetNoseAngle(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(NoseAngleId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Leading_t1::GetUpperMax(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(UpperMaxId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Leading_t1::GetUpperMaxLoc(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(UpperMaxLocId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Leading_t1::GetUpperMaxAngle(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(UpperMaxAngleId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Leading_t1::GetUpperTight(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(UpperTightId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Leading_t1::GetUpperWeight0(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(UpperWeight0Id());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Leading_t1::GetUpperWeight1(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(UpperWeight1Id());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Leading_t1::GetUpperWeight2(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(UpperWeight2Id());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Leading_t1::GetLowerMax(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(LowerMaxId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Leading_t1::GetLowerMaxLoc(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(LowerMaxLocId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Leading_t1::GetLowerMaxAngle(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(LowerMaxAngleId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Leading_t1::GetLowerTight(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(LowerTightId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Leading_t1::GetLowerWeight0(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(LowerWeight0Id());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Leading_t1::GetLowerWeight1(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(LowerWeight1Id());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Leading_t1::GetLowerWeight2(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(LowerWeight2Id());
}

void tnbLib::curveLib::airfoilLib::Leading_t1::InsertXo
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

void tnbLib::curveLib::airfoilLib::Leading_t1::InsertYo
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

void tnbLib::curveLib::airfoilLib::Leading_t1::InsertNoseAngle
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

void tnbLib::curveLib::airfoilLib::Leading_t1::InsertUpperMax
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

void tnbLib::curveLib::airfoilLib::Leading_t1::InsertUpperMaxLoc
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

void tnbLib::curveLib::airfoilLib::Leading_t1::InsertUpperMaxAngle
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

void tnbLib::curveLib::airfoilLib::Leading_t1::InsertUpperTight
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

void tnbLib::curveLib::airfoilLib::Leading_t1::InsertUpperWeight0
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(UpperWeight0Id()) = x;
}

void tnbLib::curveLib::airfoilLib::Leading_t1::InsertUpperWeight1
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(UpperWeight1Id()) = x;
}

void tnbLib::curveLib::airfoilLib::Leading_t1::InsertUpperWeight2
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(UpperWeight2Id()) = x;
}

void tnbLib::curveLib::airfoilLib::Leading_t1::InsertLowerMax
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

void tnbLib::curveLib::airfoilLib::Leading_t1::InsertLowerMaxLoc
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

void tnbLib::curveLib::airfoilLib::Leading_t1::InsertLowerMaxAngle
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

void tnbLib::curveLib::airfoilLib::Leading_t1::InsertLowerTight
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

void tnbLib::curveLib::airfoilLib::Leading_t1::InsertLowerWeight0
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(LowerWeight0Id()) = x;
}

void tnbLib::curveLib::airfoilLib::Leading_t1::InsertLowerWeight1
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(LowerWeight1Id()) = x;
}

void tnbLib::curveLib::airfoilLib::Leading_t1::InsertLowerWeight2
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(LowerWeight2Id()) = x;
}

void tnbLib::curveLib::airfoilLib::Leading_t1::CheckVector(const std::vector<Standard_Real>& xs)
{
	if (xs.size() NOT_EQUAL Leading_t1::nb_parameters)
	{
		FatalErrorIn(FunctionSIG)
			<< "the vector is incompatible with this section." << endl
			<< abort(FatalError);
	}
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Leading_t1::CreateXo
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Leading_t1::xoPar::id + 1);
	par->SetName("xo");
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Leading_t1::CreateYo
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Leading_t1::yoPar::id + 1);
	par->SetName("yo");
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Leading_t1::CreateNoseAngle
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Leading_t1::noseAnglePar::id + 1);
	par->SetName(NoseAngleName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Leading_t1::CreateUpperMax
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Leading_t1::upperMaxPar::id + 1);
	par->SetName(UpperMaxName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Leading_t1::CreateUpperMaxLoc
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Leading_t1::upperMaxLocPar::id + 1);
	par->SetName(UpperMaxLocName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Leading_t1::CreateUpperMaxAngle
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Leading_t1::upperMaxAnglePar::id + 1);
	par->SetName(UpperMaxAngleName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Leading_t1::CreateUpperTight
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Leading_t1::upperTightPar::id + 1);
	par->SetName(UpperTightName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Leading_t1::CreateUpperWeight0
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Leading_t1::upperWeight0Par::id + 1);
	par->SetName(UpperWeight0Name());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Leading_t1::CreateUpperWeight1
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Leading_t1::upperWeight1Par::id + 1);
	par->SetName(UpperWeight1Name());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Leading_t1::CreateUpperWeight2
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Leading_t1::upperWeight2Par::id + 1);
	par->SetName(UpperWeight2Name());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Leading_t1::CreateLowerMax
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Leading_t1::lowerMaxPar::id + 1);
	par->SetName(LowerMaxName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Leading_t1::CreateLowerMaxLoc
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Leading_t1::lowerMaxLocPar::id + 1);
	par->SetName(LowerMaxLocName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Leading_t1::CreateLowerMaxAngle
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Leading_t1::lowerMaxAnglePar::id + 1);
	par->SetName(LowerMaxAngleName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Leading_t1::CreateLowerTight
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Leading_t1::lowerTightPar::id + 1);
	par->SetName(LowerTightName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Leading_t1::CreateLowerWeight0
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Leading_t1::lowerWeight0Par::id + 1);
	par->SetName(LowerWeight0Name());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Leading_t1::CreateLowerWeight1
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Leading_t1::lowerWeight0Par::id + 1);
	par->SetName(LowerWeight1Name());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Leading_t1::CreateLowerWeight2
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Leading_t1::lowerWeight0Par::id + 1);
	par->SetName(LowerWeight2Name());
	return std::move(par);
}

std::tuple
<
	tnbLib::curveLib::airfoilLib::Leading_t1::xoPar,
	tnbLib::curveLib::airfoilLib::Leading_t1::yoPar,

	tnbLib::curveLib::airfoilLib::Leading_t1::noseAnglePar,

	tnbLib::curveLib::airfoilLib::Leading_t1::upperMaxPar,
	tnbLib::curveLib::airfoilLib::Leading_t1::upperMaxLocPar,
	tnbLib::curveLib::airfoilLib::Leading_t1::upperMaxAnglePar,
	tnbLib::curveLib::airfoilLib::Leading_t1::upperTightPar,
	tnbLib::curveLib::airfoilLib::Leading_t1::upperWeight0Par,
	tnbLib::curveLib::airfoilLib::Leading_t1::upperWeight1Par,
	tnbLib::curveLib::airfoilLib::Leading_t1::upperWeight2Par,

	tnbLib::curveLib::airfoilLib::Leading_t1::lowerMaxPar,
	tnbLib::curveLib::airfoilLib::Leading_t1::lowerMaxLocPar,
	tnbLib::curveLib::airfoilLib::Leading_t1::lowerMaxAnglePar,
	tnbLib::curveLib::airfoilLib::Leading_t1::lowerTightPar,
	tnbLib::curveLib::airfoilLib::Leading_t1::lowerWeight0Par,
	tnbLib::curveLib::airfoilLib::Leading_t1::lowerWeight1Par,
	tnbLib::curveLib::airfoilLib::Leading_t1::lowerWeight2Par
>
tnbLib::curveLib::airfoilLib::Leading_t1::RetrieveParameters(const std::vector<Standard_Real>& xs)
{
	xoPar p0 = { GetXo(xs) };
	yoPar p1 = { GetYo(xs) };

	noseAnglePar p2 = { GetNoseAngle(xs) };

	upperMaxPar p3 = { GetUpperMax(xs) };
	upperMaxLocPar p4 = { GetUpperMaxLoc(xs) };
	upperMaxAnglePar p5 = { GetUpperMaxAngle(xs) };
	upperTightPar p6 = { GetUpperTight(xs) };
	upperWeight0Par p7 = { GetUpperWeight0(xs) };
	upperWeight1Par p8 = { GetUpperWeight1(xs) };
	upperWeight2Par p9 = { GetUpperWeight2(xs) };

	lowerMaxPar p10 = { GetLowerMax(xs) };
	lowerMaxLocPar p11 = { GetLowerMaxLoc(xs) };
	lowerMaxAnglePar p12 = { GetLowerMaxAngle(xs) };
	lowerTightPar p13 = { GetLowerTight(xs) };
	lowerWeight0Par p14 = { GetLowerWeight0(xs) };
	lowerWeight1Par p15 = { GetLowerWeight1(xs) };
	lowerWeight2Par p16 = { GetLowerWeight2(xs) };

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
		std::move(p12),
		std::move(p13),
		std::move(p14),
		std::move(p15),
		std::move(p16)
	);
	return std::move(t);
}

std::shared_ptr<tnbLib::curveLib::airfoilLib::Leading_t1::Parameters>
tnbLib::curveLib::airfoilLib::Leading_t1::CreateParChromosome
(
	const Standard_Real theXo,
	const Standard_Real theYo,
	const Standard_Real theNoseAngle,
	const Standard_Real theUpperMax, 
	const Standard_Real theUpperMaxLoc, 
	const Standard_Real theUpperMaxAngle,
	const Standard_Real theUpperTight, 
	const Standard_Real theUpperWeight0,
	const Standard_Real theUpperWeight1,
	const Standard_Real theUpperWeight2, 
	const Standard_Real theLowerMax,
	const Standard_Real theLowerMaxLoc, 
	const Standard_Real theLowerMaxAngle,
	const Standard_Real theLowerTight, 
	const Standard_Real theLowerWeight0,
	const Standard_Real theLowerWeight1, 
	const Standard_Real theLowerWeight2
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
		Param p{ theUpperMaxLoc,upperMaxLocPar::name };
		pars.at(UpperMaxLocId()) = std::move(p);
	}
	{
		Param p{ theUpperMaxLoc,upperMaxAnglePar::name };
		pars.at(UpperMaxAngleId()) = std::move(p);
	}
	{
		Param p{ theUpperTight,upperTightPar::name };
		pars.at(UpperTightId()) = std::move(p);
	}
	{
		Param p{ theUpperWeight0,upperWeight0Par::name };
		pars.at(UpperWeight0Id()) = std::move(p);
	}
	{
		Param p{ theUpperWeight1,upperWeight1Par::name };
		pars.at(UpperWeight1Id()) = std::move(p);
	}
	{
		Param p{ theUpperWeight2,upperWeight2Par::name };
		pars.at(UpperWeight2Id()) = std::move(p);
	}

	{
		Param p{ theLowerMax,lowerMaxPar::name };
		pars.at(LowerMaxId()) = std::move(p);
	}
	{
		Param p{ theLowerMaxLoc,lowerMaxLocPar::name };
		pars.at(LowerMaxLocId()) = std::move(p);
	}
	{
		Param p{ theLowerMaxLoc,lowerMaxAnglePar::name };
		pars.at(LowerMaxAngleId()) = std::move(p);
	}
	{
		Param p{ theLowerTight,lowerTightPar::name };
		pars.at(LowerTightId()) = std::move(p);
	}
	{
		Param p{ theLowerWeight0,lowerWeight0Par::name };
		pars.at(LowerWeight0Id()) = std::move(p);
	}
	{
		Param p{ theLowerWeight1,lowerWeight1Par::name };
		pars.at(LowerWeight1Id()) = std::move(p);
	}
	{
		Param p{ theLowerWeight2,lowerWeight2Par::name };
		pars.at(LowerWeight2Id()) = std::move(p);
	}
	Parameters pchromRef = { std::move(pars) };
	auto pchrom = std::make_shared<Parameters>(std::move(pchromRef));
	return std::move(pchrom);
}