#include <PtdShapeFit2d_AirfoilGlobal_t1.hxx>

#include <PtdShapeFit_Par.hxx>

const char* tnbLib::curveLib::airfoilLib::Global_t1::xoPar::name = "xo";
const char* tnbLib::curveLib::airfoilLib::Global_t1::yoPar::name = "yo";

const char* tnbLib::curveLib::airfoilLib::Global_t1::noseAnglePar::name = "noseAngle";

const char* tnbLib::curveLib::airfoilLib::Global_t1::chordLenPar::name = "chordLen";

const char* tnbLib::curveLib::airfoilLib::Global_t1::upperMaxPar::name = "upperMax";
const char* tnbLib::curveLib::airfoilLib::Global_t1::upperMaxLocPar::name = "upperMaxLoc";
const char* tnbLib::curveLib::airfoilLib::Global_t1::upperNoseTightPar::name = "upperNoseTight";
const char* tnbLib::curveLib::airfoilLib::Global_t1::upperMaxTightPar::name = "upperMaxTight";
const char* tnbLib::curveLib::airfoilLib::Global_t1::upperTrailAnglePar::name = "upperTailAngle";
const char* tnbLib::curveLib::airfoilLib::Global_t1::upperMaxVelPar::name = "upperMaxVel";
const char* tnbLib::curveLib::airfoilLib::Global_t1::upperTrailVelPar::name = "upperTailVel";

const char* tnbLib::curveLib::airfoilLib::Global_t1::lowerMaxPar::name = "lowerMax";
const char* tnbLib::curveLib::airfoilLib::Global_t1::lowerMaxLocPar::name = "lowerMaxLoc";
const char* tnbLib::curveLib::airfoilLib::Global_t1::lowerNoseTightPar::name = "lowerNoseTight";
const char* tnbLib::curveLib::airfoilLib::Global_t1::lowerMaxTightPar::name = "lowerMaxTight";
const char* tnbLib::curveLib::airfoilLib::Global_t1::lowerTrailAnglePar::name = "lowerTailAngle";
const char* tnbLib::curveLib::airfoilLib::Global_t1::lowerMaxVelPar::name = "lowerMaxVel";
const char* tnbLib::curveLib::airfoilLib::Global_t1::lowerTrailVelPar::name = "lowerTailVel";

std::map<Standard_Integer, const char*> tnbLib::curveLib::airfoilLib::Global_t1::ParsMap;

namespace tnbLib
{

	namespace curveLib
	{
		class AirfoilGlobalType1RunTime
		{

			/*Private Data*/

		public:

			// default constructor [4/28/2023 Payvand]

			AirfoilGlobalType1RunTime()
			{
				SetConfig();
			}

			void SetConfig();

		};
	}
}

void tnbLib::curveLib::AirfoilGlobalType1RunTime::SetConfig()
{
	{
		auto paired = std::make_pair(airfoilLib::Global_t1::xoPar::id, airfoilLib::Global_t1::xoPar::name);
		airfoilLib::Global_t1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Global_t1::yoPar::id, airfoilLib::Global_t1::yoPar::name);
		airfoilLib::Global_t1::ParsMap.insert(std::move(paired));
	}

	{
		auto paired = std::make_pair(airfoilLib::Global_t1::noseAnglePar::id, airfoilLib::Global_t1::noseAnglePar::name);
		airfoilLib::Global_t1::ParsMap.insert(std::move(paired));
	}

	{
		auto paired = std::make_pair(airfoilLib::Global_t1::chordLenPar::id, airfoilLib::Global_t1::chordLenPar::name);
		airfoilLib::Global_t1::ParsMap.insert(std::move(paired));
	}

	{
		auto paired = std::make_pair(airfoilLib::Global_t1::upperMaxPar::id, airfoilLib::Global_t1::upperMaxPar::name);
		airfoilLib::Global_t1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Global_t1::upperMaxLocPar::id, airfoilLib::Global_t1::upperMaxLocPar::name);
		airfoilLib::Global_t1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Global_t1::upperNoseTightPar::id, airfoilLib::Global_t1::upperNoseTightPar::name);
		airfoilLib::Global_t1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Global_t1::upperMaxTightPar::id, airfoilLib::Global_t1::upperMaxTightPar::name);
		airfoilLib::Global_t1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Global_t1::upperTrailAnglePar::id, airfoilLib::Global_t1::upperTrailAnglePar::name);
		airfoilLib::Global_t1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Global_t1::upperMaxVelPar::id, airfoilLib::Global_t1::upperMaxVelPar::name);
		airfoilLib::Global_t1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Global_t1::upperTrailVelPar::id, airfoilLib::Global_t1::upperTrailVelPar::name);
		airfoilLib::Global_t1::ParsMap.insert(std::move(paired));
	}

	{
		auto paired = std::make_pair(airfoilLib::Global_t1::lowerMaxPar::id, airfoilLib::Global_t1::lowerMaxPar::name);
		airfoilLib::Global_t1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Global_t1::lowerMaxLocPar::id, airfoilLib::Global_t1::lowerMaxLocPar::name);
		airfoilLib::Global_t1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Global_t1::lowerNoseTightPar::id, airfoilLib::Global_t1::lowerNoseTightPar::name);
		airfoilLib::Global_t1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Global_t1::lowerMaxTightPar::id, airfoilLib::Global_t1::lowerMaxTightPar::name);
		airfoilLib::Global_t1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Global_t1::lowerTrailAnglePar::id, airfoilLib::Global_t1::lowerTrailAnglePar::name);
		airfoilLib::Global_t1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Global_t1::lowerMaxVelPar::id, airfoilLib::Global_t1::lowerMaxVelPar::name);
		airfoilLib::Global_t1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Global_t1::lowerTrailVelPar::id, airfoilLib::Global_t1::lowerTrailVelPar::name);
		airfoilLib::Global_t1::ParsMap.insert(std::move(paired));
	}
}

tnbLib::curveLib::AirfoilGlobalType1RunTime myCurveLibAirfoilGlobalType1RunTimeObj;

const unsigned int tnbLib::curveLib::airfoilLib::Global_t1::nb_parameters = 18;
unsigned short tnbLib::curveLib::airfoilLib::Global_t1::verbose(0);

const char*
tnbLib::curveLib::airfoilLib::Global_t1::ParName
(
	const Standard_Integer theIndex
) const
{
	return ParsMap.at(theIndex);
}

Standard_Integer 
tnbLib::curveLib::airfoilLib::Global_t1::NbPars() const
{
	return Standard_Integer(nb_parameters);
}

std::shared_ptr<tnbLib::curveLib::airfoilLib::Global_t1::Parameters>
tnbLib::curveLib::airfoilLib::Global_t1::RetrieveParChromosome
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
		Param p{ GetChordLen(theChromosome),ChordLenName() };
		pars.at(ChordLenId()) = std::move(p);
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
		Param p{ GetUpperMaxTight(theChromosome),UpperMaxTightName() };
		pars.at(UpperMaxTightId()) = std::move(p);
	}
	{
		Param p{ GetUpperTrailAngle(theChromosome),UpperTrailAngleName() };
		pars.at(UpperTrailAngleId()) = std::move(p);
	}
	{
		Param p{ GetUpperMaxVel(theChromosome),UpperMaxVelName() };
		pars.at(UpperMaxVelId()) = std::move(p);
	}
	{
		Param p{ GetUpperTrailVel(theChromosome),UpperTrailVelName() };
		pars.at(UpperTrailVelId()) = std::move(p);
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
		Param p{ GetLowerMaxTight(theChromosome),LowerMaxTightName() };
		pars.at(LowerMaxTightId()) = std::move(p);
	}
	{
		Param p{ GetLowerTrailAngle(theChromosome),LowerTrailAngleName() };
		pars.at(LowerTrailAngleId()) = std::move(p);
	}
	{
		Param p{ GetLowerMaxVel(theChromosome),LowerMaxVelName() };
		pars.at(LowerMaxVelId()) = std::move(p);
	}
	{
		Param p{ GetLowerTrailVel(theChromosome),LowerTrailVelName() };
		pars.at(LowerTrailVelId()) = std::move(p);
	}

	Parameters pchromRef = { std::move(pars) };
	auto pchrom = std::make_shared<Parameters>(std::move(pchromRef));
	return std::move(pchrom);
}

std::vector<std::shared_ptr<tnbLib::PtdShapeFit_Par>>
tnbLib::curveLib::airfoilLib::Global_t1::RetrieveParList() const
{
	std::vector<std::shared_ptr<PtdShapeFit_Par>> pars(NbPars());
	pars.at(XoId()) = Xo();
	pars.at(YoId()) = Yo();

	pars.at(NoseAngleId()) = NoseAngle();

	pars.at(ChordLenId()) = ChordLen();

	pars.at(UpperMaxId()) = UpperMax();
	pars.at(UpperMaxLocId()) = UpperMaxLoc();
	pars.at(UpperNoseTightId()) = UpperNoseTight();
	pars.at(UpperMaxTightId()) = UpperMaxTight();
	pars.at(UpperTrailAngleId()) = UpperTrailAngle();
	pars.at(UpperMaxVelId()) = UpperMaxVel();
	pars.at(UpperTrailVelId()) = UpperTrailVel();

	pars.at(LowerMaxId()) = LowerMax();
	pars.at(LowerMaxLocId()) = LowerMaxLoc();
	pars.at(LowerNoseTightId()) = LowerNoseTight();
	pars.at(LowerMaxTightId()) = LowerMaxTight();
	pars.at(LowerTrailAngleId()) = LowerTrailAngle();
	pars.at(LowerMaxVelId()) = LowerMaxVel();
	pars.at(LowerTrailVelId()) = LowerTrailVel();
	return std::move(pars);
}

std::vector<Standard_Real>
tnbLib::curveLib::airfoilLib::Global_t1::RetrieveChromosome
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

		chromosome.at(ChordLenId()) = pars.x.at(ChordLenId()).x;

		chromosome.at(UpperMaxId()) = pars.x.at(UpperMaxId()).x;
		chromosome.at(UpperMaxLocId()) = pars.x.at(UpperMaxLocId()).x;
		chromosome.at(UpperNoseTightId()) = pars.x.at(UpperNoseTightId()).x;
		chromosome.at(UpperMaxTightId()) = pars.x.at(UpperMaxTightId()).x;

		chromosome.at(UpperTrailAngleId()) = pars.x.at(UpperTrailAngleId()).x;
		chromosome.at(UpperMaxVelId()) = pars.x.at(UpperMaxVelId()).x;
		chromosome.at(UpperTrailVelId()) = pars.x.at(UpperTrailVelId()).x;

		chromosome.at(LowerMaxId()) = pars.x.at(LowerMaxId()).x;
		chromosome.at(LowerMaxLocId()) = pars.x.at(LowerMaxLocId()).x;
		chromosome.at(LowerNoseTightId()) = pars.x.at(LowerNoseTightId()).x;
		chromosome.at(LowerMaxTightId()) = pars.x.at(LowerMaxTightId()).x;

		chromosome.at(LowerTrailAngleId()) = pars.x.at(LowerTrailAngleId()).x;
		chromosome.at(LowerMaxVelId()) = pars.x.at(LowerMaxVelId()).x;
		chromosome.at(LowerTrailVelId()) = pars.x.at(LowerTrailVelId()).x;

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

void tnbLib::curveLib::airfoilLib::Global_t1::SetParameters
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
		Param x = { GetChordLen(theXs),ChordLenName() };
		pars.at(ChordLenId()) = std::move(x);
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
		Param x = { GetUpperMaxTight(theXs),UpperMaxTightName() };
		pars.at(UpperMaxTightId()) = std::move(x);
	}

	{
		Param x = { GetUpperTrailAngle(theXs),UpperTrailAngleName() };
		pars.at(UpperTrailAngleId()) = std::move(x);
	}
	{
		Param x = { GetUpperMaxVel(theXs),UpperMaxVelName() };
		pars.at(UpperMaxVelId()) = std::move(x);
	}
	{
		Param x = { GetUpperTrailVel(theXs),UpperTrailVelName() };
		pars.at(UpperTrailVelId()) = std::move(x);
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
		Param x = { GetLowerMaxTight(theXs),LowerMaxTightName() };
		pars.at(LowerMaxTightId()) = std::move(x);
	}

	{
		Param x = { GetLowerTrailAngle(theXs),LowerTrailAngleName() };
		pars.at(LowerTrailAngleId()) = std::move(x);
	}
	{
		Param x = { GetLowerMaxVel(theXs),LowerMaxVelName() };
		pars.at(LowerMaxVelId()) = std::move(x);
	}
	{
		Param x = { GetLowerTrailVel(theXs),LowerTrailVelName() };
		pars.at(LowerTrailVelId()) = std::move(x);
	}

	Parameters xPars = { std::move(pars) };
	ParsRef() = std::make_shared<Parameters>(std::move(xPars));
}

Standard_Real
tnbLib::curveLib::airfoilLib::Global_t1::GetXo(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(XoId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Global_t1::GetYo(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(YoId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Global_t1::GetNoseAngle(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(NoseAngleId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Global_t1::GetChordLen(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(ChordLenId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Global_t1::GetUpperMax(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(UpperMaxId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Global_t1::GetUpperMaxLoc(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(UpperMaxLocId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Global_t1::GetUpperNoseTight(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(UpperNoseTightId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Global_t1::GetUpperMaxTight(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(UpperMaxTightId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Global_t1::GetUpperTrailAngle(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(UpperTrailAngleId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Global_t1::GetUpperMaxVel(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(UpperMaxVelId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Global_t1::GetUpperTrailVel(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(UpperTrailVelId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Global_t1::GetLowerMax(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(LowerMaxId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Global_t1::GetLowerMaxLoc(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(LowerMaxLocId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Global_t1::GetLowerNoseTight(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(LowerNoseTightId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Global_t1::GetLowerMaxTight(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(LowerMaxTightId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Global_t1::GetLowerTrailAngle(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(LowerTrailAngleId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Global_t1::GetLowerMaxVel(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(LowerMaxVelId());
}

Standard_Real
tnbLib::curveLib::airfoilLib::Global_t1::GetLowerTrailVel(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(LowerTrailVelId());
}

void tnbLib::curveLib::airfoilLib::Global_t1::InsertXo
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

void tnbLib::curveLib::airfoilLib::Global_t1::InsertYo
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

void tnbLib::curveLib::airfoilLib::Global_t1::InsertNoseAngle
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

void tnbLib::curveLib::airfoilLib::Global_t1::InsertChordLen
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

void tnbLib::curveLib::airfoilLib::Global_t1::InsertUpperMax
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

void tnbLib::curveLib::airfoilLib::Global_t1::InsertUpperMaxLoc
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

void tnbLib::curveLib::airfoilLib::Global_t1::InsertUpperNoseTight
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

void tnbLib::curveLib::airfoilLib::Global_t1::InsertUpperMaxTight
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(UpperMaxTightId()) = x;
}

void tnbLib::curveLib::airfoilLib::Global_t1::InsertUpperTrailAngle
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(UpperTrailAngleId()) = x;
}

void tnbLib::curveLib::airfoilLib::Global_t1::InsertUpperMaxVel
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(UpperMaxVelId()) = x;
}

void tnbLib::curveLib::airfoilLib::Global_t1::InsertUpperTrailVel
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(UpperTrailVelId()) = x;
}

void tnbLib::curveLib::airfoilLib::Global_t1::InsertLowerMax
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

void tnbLib::curveLib::airfoilLib::Global_t1::InsertLowerMaxLoc
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

void tnbLib::curveLib::airfoilLib::Global_t1::InsertLowerNoseTight
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

void tnbLib::curveLib::airfoilLib::Global_t1::InsertLowerMaxTight
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(LowerMaxTightId()) = x;
}

void tnbLib::curveLib::airfoilLib::Global_t1::InsertLowerTrailAngle
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(LowerTrailAngleId()) = x;
}

void tnbLib::curveLib::airfoilLib::Global_t1::InsertLowerMaxVel
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(LowerMaxVelId()) = x;
}

void tnbLib::curveLib::airfoilLib::Global_t1::InsertLowerTrailVel
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(LowerTrailVelId()) = x;
}

void tnbLib::curveLib::airfoilLib::Global_t1::CheckVector(const std::vector<Standard_Real>& xs)
{
	if (xs.size() NOT_EQUAL Global_t1::nb_parameters)
	{
		FatalErrorIn(FunctionSIG)
			<< "the vector is incompatible with this section." << endl
			<< abort(FatalError);
	}
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Global_t1::CreateXo
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Global_t1::xoPar::id + 1);
	par->SetName("xo");
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Global_t1::CreateYo
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Global_t1::yoPar::id + 1);
	par->SetName("yo");
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Global_t1::CreateNoseAngle
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Global_t1::noseAnglePar::id + 1);
	par->SetName(NoseAngleName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Global_t1::CreateChordLen
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Global_t1::chordLenPar::id + 1);
	par->SetName(ChordLenName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Global_t1::CreateUpperMax
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Global_t1::upperMaxPar::id + 1);
	par->SetName(UpperMaxName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Global_t1::CreateUpperMaxLoc
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Global_t1::upperMaxLocPar::id + 1);
	par->SetName(UpperMaxLocName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Global_t1::CreateUpperNoseTight
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Global_t1::upperNoseTightPar::id + 1);
	par->SetName(UpperNoseTightName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Global_t1::CreateUpperMaxTight
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Global_t1::upperMaxTightPar::id + 1);
	par->SetName(UpperMaxTightName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Global_t1::CreateUpperTrailAngle
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Global_t1::upperTrailAnglePar::id + 1);
	par->SetName(UpperTrailAngleName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Global_t1::CreateUpperMaxVel
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Global_t1::upperMaxVelPar::id + 1);
	par->SetName(UpperMaxVelName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Global_t1::CreateUpperTrailVel
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Global_t1::upperMaxVelPar::id + 1);
	par->SetName(UpperMaxVelName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Global_t1::CreateLowerMax
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Global_t1::lowerMaxPar::id + 1);
	par->SetName(LowerMaxName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Global_t1::CreateLowerMaxLoc
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Global_t1::lowerMaxLocPar::id + 1);
	par->SetName(LowerMaxLocName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Global_t1::CreateLowerNoseTight
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Global_t1::lowerNoseTightPar::id + 1);
	par->SetName(LowerNoseTightName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Global_t1::CreateLowerMaxTight
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Global_t1::lowerMaxTightPar::id + 1);
	par->SetName(LowerMaxTightName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Global_t1::CreateLowerTrailAngle
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Global_t1::lowerTrailAnglePar::id + 1);
	par->SetName(LowerTrailAngleName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Global_t1::CreateLowerMaxVel
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Global_t1::lowerMaxVelPar::id + 1);
	par->SetName(LowerMaxVelName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::curveLib::airfoilLib::Global_t1::CreateLowerTrailVel
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Global_t1::lowerTrailVelPar::id + 1);
	par->SetName(LowerTrailVelName());
	return std::move(par);
}

std::tuple
<
	tnbLib::curveLib::airfoilLib::Global_t1::xoPar,
	tnbLib::curveLib::airfoilLib::Global_t1::yoPar,

	tnbLib::curveLib::airfoilLib::Global_t1::noseAnglePar,

	tnbLib::curveLib::airfoilLib::Global_t1::chordLenPar,

	tnbLib::curveLib::airfoilLib::Global_t1::upperMaxPar,
	tnbLib::curveLib::airfoilLib::Global_t1::upperMaxLocPar,
	tnbLib::curveLib::airfoilLib::Global_t1::upperNoseTightPar,
	tnbLib::curveLib::airfoilLib::Global_t1::upperMaxTightPar,
	tnbLib::curveLib::airfoilLib::Global_t1::upperTrailAnglePar,
	tnbLib::curveLib::airfoilLib::Global_t1::upperMaxVelPar,
	tnbLib::curveLib::airfoilLib::Global_t1::upperTrailVelPar,

	tnbLib::curveLib::airfoilLib::Global_t1::lowerMaxPar,
	tnbLib::curveLib::airfoilLib::Global_t1::lowerMaxLocPar,
	tnbLib::curveLib::airfoilLib::Global_t1::lowerNoseTightPar,
	tnbLib::curveLib::airfoilLib::Global_t1::lowerMaxTightPar,
	tnbLib::curveLib::airfoilLib::Global_t1::lowerTrailAnglePar,
	tnbLib::curveLib::airfoilLib::Global_t1::lowerMaxVelPar,
	tnbLib::curveLib::airfoilLib::Global_t1::lowerTrailVelPar
>
tnbLib::curveLib::airfoilLib::Global_t1::RetrieveParameters(const std::vector<Standard_Real>& xs)
{
	xoPar p0 = { GetXo(xs) };
	yoPar p1 = { GetYo(xs) };

	noseAnglePar p2 = { GetNoseAngle(xs) };

	chordLenPar p3 = { GetChordLen(xs) };

	upperMaxPar p4 = { GetUpperMax(xs) };
	upperMaxLocPar p5 = { GetUpperMaxLoc(xs) };
	upperNoseTightPar p6 = { GetUpperNoseTight(xs) };
	upperMaxTightPar p7 = { GetUpperMaxTight(xs) };
	upperTrailAnglePar p8 = { GetUpperTrailAngle(xs) };
	upperMaxVelPar p9 = { GetUpperMaxVel(xs) };
	upperTrailVelPar p10 = { GetUpperTrailVel(xs) };

	lowerMaxPar p11 = { GetLowerMax(xs) };
	lowerMaxLocPar p12 = { GetLowerMaxLoc(xs) };
	lowerNoseTightPar p13 = { GetLowerNoseTight(xs) };
	lowerMaxTightPar p14 = { GetLowerMaxTight(xs) };
	lowerTrailAnglePar p15 = { GetLowerTrailAngle(xs) };
	lowerMaxVelPar p16 = { GetLowerMaxVel(xs) };
	lowerTrailVelPar p17 = { GetLowerTrailVel(xs) };

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
		std::move(p16),
		std::move(p17)
	);
	return std::move(t);
}

std::shared_ptr<tnbLib::curveLib::airfoilLib::Global_t1::Parameters>
tnbLib::curveLib::airfoilLib::Global_t1::CreateParChromosome
(
	const Standard_Real theXo,
	const Standard_Real theYo, 
	const Standard_Real theNoseAngle, 
	const Standard_Real theChordLen, 
	const Standard_Real theUpperMax, 
	const Standard_Real theUpperMaxLoc, 
	const Standard_Real theUpperNoseTight, 
	const Standard_Real theUpperMaxTight, 
	const Standard_Real theUpperTrailAngle, 
	const Standard_Real theUpperMaxVel, 
	const Standard_Real theUpperTrailVel, 
	const Standard_Real theLowerMax, 
	const Standard_Real theLowerMaxLoc, 
	const Standard_Real theLowerNoseTight, 
	const Standard_Real theLowerMaxTight, 
	const Standard_Real theLowerTrailAngle, 
	const Standard_Real theLowerMaxVel, 
	const Standard_Real theLowerTrailVel
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
		Param p{ theNoseAngle,noseAnglePar::name };
		pars.at(NoseAngleId()) = std::move(p);
	}

	{
		Param p{ theChordLen,chordLenPar::name };
		pars.at(ChordLenId()) = std::move(p);
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
		Param p{ theUpperNoseTight,upperNoseTightPar::name };
		pars.at(UpperNoseTightId()) = std::move(p);
	}
	{
		Param p{ theUpperMaxTight,upperMaxTightPar::name };
		pars.at(UpperMaxTightId()) = std::move(p);
	}

	{
		Param p{ theUpperTrailAngle,upperTrailAnglePar::name };
		pars.at(UpperTrailAngleId()) = std::move(p);
	}
	{
		Param p{ theUpperMaxVel,upperMaxVelPar::name };
		pars.at(UpperMaxVelId()) = std::move(p);
	}
	{
		Param p{ theUpperTrailVel,upperTrailVelPar::name };
		pars.at(UpperTrailVelId()) = std::move(p);
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
		Param p{ theLowerNoseTight,lowerNoseTightPar::name };
		pars.at(LowerNoseTightId()) = std::move(p);
	}
	{
		Param p{ theLowerMaxTight,lowerMaxTightPar::name };
		pars.at(LowerMaxTightId()) = std::move(p);
	}

	{
		Param p{ theLowerTrailAngle,lowerTrailAnglePar::name };
		pars.at(LowerTrailAngleId()) = std::move(p);
	}
	{
		Param p{ theLowerMaxVel,lowerMaxVelPar::name };
		pars.at(LowerMaxVelId()) = std::move(p);
	}
	{
		Param p{ theLowerTrailVel,lowerTrailVelPar::name };
		pars.at(LowerTrailVelId()) = std::move(p);
	}
	Parameters pchromRef = { std::move(pars) };
	auto pchrom = std::make_shared<Parameters>(std::move(pchromRef));
	return std::move(pchrom);
}