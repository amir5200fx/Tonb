#include <PtdShapeFit2d_Airfoil_t1.hxx>

#include <PtdShapeFit_Par.hxx>

const char* tnbLib::airfoilLib::Type1::xoPar::name = "xo";
const char* tnbLib::airfoilLib::Type1::yoPar::name = "yo";

const char* tnbLib::airfoilLib::Type1::chordLenPar::name = "chordlen";

const char* tnbLib::airfoilLib::Type1::maxCambPar::name = "maxCamb";
const char* tnbLib::airfoilLib::Type1::maxCambLocPar::name = "maxCambLoc";

const char* tnbLib::airfoilLib::Type1::leadCambSteepPar::name = "leadCambSteep";
const char* tnbLib::airfoilLib::Type1::leadCambSteepTightPar::name = "leadCambSteepTight";
const char* tnbLib::airfoilLib::Type1::leadCambSteepWeightPar::name = "leadCambSteepWeight";

const char* tnbLib::airfoilLib::Type1::trailCambSteepPar::name = "trailCambSteep";
const char* tnbLib::airfoilLib::Type1::trailCambSteepTightPar::name = "trailCambSteepTight";
const char* tnbLib::airfoilLib::Type1::trailCambSteepWeightPar::name = "trailCambSteepWeight";

const char* tnbLib::airfoilLib::Type1::maxThickPar::name = "maxThick";
const char* tnbLib::airfoilLib::Type1::maxThickLocPar::name = "maxThickLoc";

const char* tnbLib::airfoilLib::Type1::leadThickSteepPar::name = "leadThickSteep";
const char* tnbLib::airfoilLib::Type1::leadThickSteepTightPar::name = "leadThickSteepTight";
const char* tnbLib::airfoilLib::Type1::leadThickSteepWeightPar::name = "leadThickSteepWeight";

const char* tnbLib::airfoilLib::Type1::trailThickSteepPar::name = "trailThickSteep";
const char* tnbLib::airfoilLib::Type1::trailThickSteepTightPar::name = "trailThickSteepTight";
const char* tnbLib::airfoilLib::Type1::trailThickSteepWeightPar::name = "trailThickSteepWeight";

std::map<Standard_Integer, const char*> tnbLib::airfoilLib::Type1::ParsMap;

namespace tnbLib
{

	class PtdShapeFit2d_AirfoilType1RunTime
	{

		/*Private Data*/

	public:

		// default constructor [4/28/2023 Payvand]

		PtdShapeFit2d_AirfoilType1RunTime()
		{
			SetConfig();
		}

		void SetConfig();

	};
}

void tnbLib::PtdShapeFit2d_AirfoilType1RunTime::SetConfig()
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
		auto paired = std::make_pair(airfoilLib::Type1::chordLenPar::id, airfoilLib::Type1::chordLenPar::name);
		airfoilLib::Type1::ParsMap.insert(std::move(paired));
	}

	{
		auto paired = std::make_pair(airfoilLib::Type1::maxCambPar::id, airfoilLib::Type1::maxCambPar::name);
		airfoilLib::Type1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type1::maxCambLocPar::id, airfoilLib::Type1::maxCambLocPar::name);
		airfoilLib::Type1::ParsMap.insert(std::move(paired));
	}

	{
		auto paired = std::make_pair(airfoilLib::Type1::leadCambSteepPar::id, airfoilLib::Type1::leadCambSteepPar::name);
		airfoilLib::Type1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type1::leadCambSteepTightPar::id, airfoilLib::Type1::leadCambSteepTightPar::name);
		airfoilLib::Type1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type1::leadCambSteepWeightPar::id, airfoilLib::Type1::leadCambSteepWeightPar::name);
		airfoilLib::Type1::ParsMap.insert(std::move(paired));
	}

	{
		auto paired = std::make_pair(airfoilLib::Type1::trailCambSteepPar::id, airfoilLib::Type1::trailCambSteepPar::name);
		airfoilLib::Type1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type1::trailCambSteepTightPar::id, airfoilLib::Type1::trailCambSteepTightPar::name);
		airfoilLib::Type1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type1::trailCambSteepWeightPar::id, airfoilLib::Type1::trailCambSteepWeightPar::name);
		airfoilLib::Type1::ParsMap.insert(std::move(paired));
	}

	{
		auto paired = std::make_pair(airfoilLib::Type1::maxThickPar::id, airfoilLib::Type1::maxThickPar::name);
		airfoilLib::Type1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type1::maxThickLocPar::id, airfoilLib::Type1::maxThickLocPar::name);
		airfoilLib::Type1::ParsMap.insert(std::move(paired));
	}

	{
		auto paired = std::make_pair(airfoilLib::Type1::leadThickSteepPar::id, airfoilLib::Type1::leadThickSteepPar::name);
		airfoilLib::Type1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type1::leadThickSteepTightPar::id, airfoilLib::Type1::leadThickSteepTightPar::name);
		airfoilLib::Type1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type1::leadThickSteepWeightPar::id, airfoilLib::Type1::leadThickSteepWeightPar::name);
		airfoilLib::Type1::ParsMap.insert(std::move(paired));
	}

	{
		auto paired = std::make_pair(airfoilLib::Type1::trailThickSteepPar::id, airfoilLib::Type1::trailThickSteepPar::name);
		airfoilLib::Type1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type1::trailThickSteepTightPar::id, airfoilLib::Type1::trailThickSteepTightPar::name);
		airfoilLib::Type1::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type1::trailThickSteepWeightPar::id, airfoilLib::Type1::trailThickSteepWeightPar::name);
		airfoilLib::Type1::ParsMap.insert(std::move(paired));
	}
}

tnbLib::PtdShapeFit2d_AirfoilType1RunTime myPtdShapeFit2d_AirfoilType1RunTimeObj;

const unsigned int tnbLib::airfoilLib::Type1::nb_parameters = 19;
unsigned short tnbLib::airfoilLib::Type1::verbose(0);

const char* 
tnbLib::airfoilLib::Type1::ParName
(
	const Standard_Integer theIndex
) const
{
	return ParsMap.at(theIndex);
}

Standard_Integer 
tnbLib::airfoilLib::Type1::NbPars() const
{
	return Standard_Integer(nb_parameters);
}

std::shared_ptr<tnbLib::airfoilLib::Type1::Parameters> 
tnbLib::airfoilLib::Type1::RetrieveParChromosome
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
		Param p{ GetMaxCamb(theChromosome),maxCambPar::name };
		pars.at(MaxCambId()) = std::move(p);
	}
	{
		Param p{ GetMaxCambLoc(theChromosome),maxCambLocPar::name };
		pars.at(MaxCambLocId()) = std::move(p);
	}
	{
		Param p{ GetLeadCambSteep(theChromosome),leadCambSteepPar::name };
		pars.at(LeadCambSteepId()) = std::move(p);
	}
	{
		Param p{ GetLeadCambSteepTight(theChromosome),leadCambSteepTightPar::name };
		pars.at(LeadCambSteepTightId()) = std::move(p);
	}
	{
		Param p{ GetLeadCambSteepWeight(theChromosome), leadCambSteepWeightPar::name };
		pars.at(LeadCambSteepWeightId()) = std::move(p);
	}

	{
		Param p{ GetTrailCambSteep(theChromosome),trailCambSteepPar::name };
		pars.at(TrailCambSteepId()) = std::move(p);
	}
	{
		Param p{ GetTrailCambSteepTight(theChromosome),trailThickSteepTightPar::name };
		pars.at(TrailCambSteepTightId()) = std::move(p);
	}
	{
		Param p{ GetTrailCambSteepWeight(theChromosome),trailCambSteepWeightPar::name };
		pars.at(TrailCambSteepWeightId()) = std::move(p);
	}

	{
		Param p{ GetMaxThick(theChromosome),maxThickPar::name };
		pars.at(MaxThickId()) = std::move(p);
	}
	{
		Param p{ GetMaxThickLoc(theChromosome),maxThickLocPar::name };
		pars.at(MaxThickLocId()) = std::move(p);
	}

	{
		Param p{ GetLeadThickSteep(theChromosome),leadThickSteepPar::name };
		pars.at(LeadThickSteepId()) = std::move(p);
	}
	{
		Param p{ GetLeadThickSteepTight(theChromosome), leadThickSteepTightPar::name };
		pars.at(LeadThickSteepTightId()) = std::move(p);
	}
	{
		Param p{ GetLeadThickSteepWeight(theChromosome), leadThickSteepWeightPar::name };
		pars.at(LeadThickSteepWeightId()) = std::move(p);
	}

	{
		Param p{ GetTrailThickSteep(theChromosome),trailThickSteepPar::name };
		pars.at(TrailThickSteepId()) = std::move(p);
	}
	{
		Param p{ GetTrailThickSteepTight(theChromosome),trailThickSteepTightPar::name };
		pars.at(TrailThickSteepTightId()) = std::move(p);
	}
	{
		Param p{ GetTrailThickSteepWeight(theChromosome),trailThickSteepWeightPar::name };
		pars.at(TrailThickSteepWeightId()) = std::move(p);
	}
	Parameters pchromRef = { std::move(pars) };
	auto pchrom = std::make_shared<Parameters>(std::move(pchromRef));
	return std::move(pchrom);
}

std::vector<std::shared_ptr<tnbLib::PtdShapeFit_Par>> 
tnbLib::airfoilLib::Type1::RetrieveParList() const
{
	std::vector<std::shared_ptr<PtdShapeFit_Par>> pars(NbPars());
	pars.at(XoId()) = Xo();
	pars.at(YoId()) = Yo();

	pars.at(ChordLenId()) = ChordLen();

	pars.at(MaxCambId()) = MaxCamb();
	pars.at(MaxCambLocId()) = MaxCambLoc();

	pars.at(LeadCambSteepId()) = LeadCambSteep();
	pars.at(LeadCambSteepTightId()) = LeadCambSteepTight();
	pars.at(LeadCambSteepWeightId()) = LeadCambSteepWeight();

	pars.at(TrailCambSteepId()) = TrailCambSteep();
	pars.at(TrailCambSteepTightId()) = TrailCambSteepTight();
	pars.at(TrailCambSteepWeightId()) = TrailCambSteepWeight();

	pars.at(MaxThickId()) = MaxThick();
	pars.at(MaxThickLocId()) = MaxThickLoc();

	pars.at(LeadThickSteepId()) = LeadThickSteep();
	pars.at(LeadThickSteepTightId()) = LeadThickSteepTight();
	pars.at(LeadThickSteepWeightId()) = LeadThickSteepWeight();

	pars.at(TrailThickSteepId()) = TrailThickSteep();
	pars.at(TrailThickSteepTightId()) = TrailThickSteepTight();
	pars.at(TrailThickSteepWeightId()) = TrailThickSteepWeight();
	return std::move(pars);
}

std::vector<Standard_Real> 
tnbLib::airfoilLib::Type1::RetrieveChromosome
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

		chromosome.at(ChordLenId()) = pars.x.at(ChordLenId()).x;

		chromosome.at(MaxCambId()) = pars.x.at(MaxCambId()).x;
		chromosome.at(MaxCambLocId()) = pars.x.at(MaxCambLocId()).x;

		chromosome.at(LeadCambSteepId()) = pars.x.at(LeadCambSteepId()).x;
		chromosome.at(LeadCambSteepTightId()) = pars.x.at(LeadCambSteepTightId()).x;
		chromosome.at(LeadCambSteepWeightId()) = pars.x.at(LeadCambSteepWeightId()).x;

		chromosome.at(TrailCambSteepId()) = pars.x.at(TrailCambSteepId()).x;
		chromosome.at(TrailCambSteepTightId()) = pars.x.at(TrailCambSteepTightId()).x;
		chromosome.at(TrailCambSteepWeightId()) = pars.x.at(TrailCambSteepWeightId()).x;

		chromosome.at(MaxThickId()) = pars.x.at(MaxThickId()).x;
		chromosome.at(MaxThickLocId()) = pars.x.at(MaxThickLocId()).x;

		chromosome.at(LeadThickSteepId()) = pars.x.at(LeadThickSteepId()).x;
		chromosome.at(LeadThickSteepTightId()) = pars.x.at(LeadThickSteepTightId()).x;
		chromosome.at(LeadThickSteepWeightId()) = pars.x.at(LeadThickSteepWeightId()).x;

		chromosome.at(TrailThickSteepId()) = pars.x.at(TrailThickSteepId()).x;
		chromosome.at(TrailThickSteepTightId()) = pars.x.at(TrailThickSteepTightId()).x;
		chromosome.at(TrailThickSteepWeightId()) = pars.x.at(TrailThickSteepWeightId()).x;

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

void tnbLib::airfoilLib::Type1::SetParameters
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
		Param x = { GetChordLen(theXs),ChordLenName() };
		pars.at(ChordLenId()) = std::move(x);
	}

	{
		Param x = { GetMaxCamb(theXs),MaxCambName() };
		pars.at(MaxCambId()) = std::move(x);
	}
	{
		Param x{ GetMaxCambLoc(theXs),MaxCambLocName() };
		pars.at(MaxCambLocId()) = std::move(x);
	}

	{
		Param x{ GetLeadCambSteep(theXs),LeadCambSteepName() };
		pars.at(LeadCambSteepId()) = std::move(x);
	}
	{
		Param x{ GetLeadCambSteepTight(theXs),LeadCambSteepTightName() };
		pars.at(LeadCambSteepTightId()) = std::move(x);
	}
	{
		Param x{ GetLeadCambSteepWeight(theXs),LeadCambSteepWeightName() };
		pars.at(LeadCambSteepWeightId()) = std::move(x);
	}

	{
		Param x{ GetTrailCambSteep(theXs),TrailCambSteepName() };
		pars.at(TrailCambSteepId()) = std::move(x);
	}
	{
		Param x{ GetTrailCambSteepTight(theXs),TrailCambSteepTightName() };
		pars.at(TrailCambSteepTightId()) = std::move(x);
	}
	{
		Param x{ GetTrailCambSteepWeight(theXs),TrailCambSteepWeightName() };
		pars.at(TrailCambSteepWeightId()) = std::move(x);
	}

	{
		Param x = { GetMaxThick(theXs),MaxThickName() };
		pars.at(MaxThickId()) = std::move(x);
	}
	{
		Param x{ GetMaxThickLoc(theXs),MaxThickLocName() };
		pars.at(MaxThickLocId()) = std::move(x);
	}

	{
		Param x{ GetLeadThickSteep(theXs),LeadThickSteepName() };
		pars.at(LeadThickSteepId()) = std::move(x);
	}
	{
		Param x{ GetLeadThickSteepTight(theXs),LeadThickSteepTightName() };
		pars.at(LeadThickSteepTightId()) = std::move(x);
	}
	{
		Param x{ GetLeadThickSteepWeight(theXs),LeadThickSteepWeightName() };
		pars.at(LeadThickSteepWeightId()) = std::move(x);
	}

	{
		Param x{ GetTrailThickSteep(theXs),TrailThickSteepName() };
		pars.at(TrailThickSteepId()) = std::move(x);
	}
	{
		Param x{ GetTrailThickSteepTight(theXs),TrailThickSteepTightName() };
		pars.at(TrailThickSteepTightId()) = std::move(x);
	}
	{
		Param x{ GetTrailThickSteepWeight(theXs),TrailThickSteepWeightName() };
		pars.at(TrailThickSteepWeightId()) = std::move(x);
	}

	Parameters xPars = { std::move(pars) };
	ParsRef() = std::make_shared<Parameters>(std::move(xPars));
}

Standard_Integer 
tnbLib::airfoilLib::Type1::XoId()
{
	return Standard_Integer(xoPar::id);
}

Standard_Integer 
tnbLib::airfoilLib::Type1::YoId()
{
	return Standard_Integer(yoPar::id);
}

Standard_Integer 
tnbLib::airfoilLib::Type1::ChordLenId()
{
	return Standard_Integer(chordLenPar::id);
}

Standard_Integer 
tnbLib::airfoilLib::Type1::MaxCambId()
{
	return Standard_Integer(maxCambPar::id);
}

Standard_Integer 
tnbLib::airfoilLib::Type1::MaxCambLocId()
{
	return Standard_Integer(maxCambLocPar::id);
}

Standard_Integer 
tnbLib::airfoilLib::Type1::LeadCambSteepId()
{
	return Standard_Integer(leadCambSteepPar::id);
}

Standard_Integer 
tnbLib::airfoilLib::Type1::LeadCambSteepTightId()
{
	return Standard_Integer(leadCambSteepTightPar::id);
}

Standard_Integer 
tnbLib::airfoilLib::Type1::LeadCambSteepWeightId()
{
	return Standard_Integer(leadCambSteepWeightPar::id);
}

Standard_Integer
tnbLib::airfoilLib::Type1::TrailCambSteepId()
{
	return Standard_Integer(trailCambSteepPar::id);
}

Standard_Integer
tnbLib::airfoilLib::Type1::TrailCambSteepTightId()
{
	return Standard_Integer(trailCambSteepTightPar::id);
}

Standard_Integer
tnbLib::airfoilLib::Type1::TrailCambSteepWeightId()
{
	return Standard_Integer(trailCambSteepWeightPar::id);
}

Standard_Integer
tnbLib::airfoilLib::Type1::MaxThickId()
{
	return Standard_Integer(maxThickPar::id);
}

Standard_Integer
tnbLib::airfoilLib::Type1::MaxThickLocId()
{
	return Standard_Integer(maxThickLocPar::id);
}

Standard_Integer
tnbLib::airfoilLib::Type1::LeadThickSteepId()
{
	return Standard_Integer(leadThickSteepPar::id);
}

Standard_Integer
tnbLib::airfoilLib::Type1::LeadThickSteepTightId()
{
	return Standard_Integer(leadThickSteepTightPar::id);
}

Standard_Integer
tnbLib::airfoilLib::Type1::LeadThickSteepWeightId()
{
	return Standard_Integer(leadThickSteepWeightPar::id);
}

Standard_Integer
tnbLib::airfoilLib::Type1::TrailThickSteepId()
{
	return Standard_Integer(trailThickSteepPar::id);
}

Standard_Integer
tnbLib::airfoilLib::Type1::TrailThickSteepTightId()
{
	return Standard_Integer(trailThickSteepTightPar::id);
}

Standard_Integer
tnbLib::airfoilLib::Type1::TrailThickSteepWeightId()
{
	return Standard_Integer(trailThickSteepWeightPar::id);
}

Standard_Real
tnbLib::airfoilLib::Type1::GetXo(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(XoId());
}

Standard_Real
tnbLib::airfoilLib::Type1::GetYo(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(YoId());
}

Standard_Real
tnbLib::airfoilLib::Type1::GetChordLen(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(ChordLenId());
}

Standard_Real
tnbLib::airfoilLib::Type1::GetMaxCamb(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(MaxCambId());
}

Standard_Real
tnbLib::airfoilLib::Type1::GetMaxCambLoc(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(MaxCambLocId());
}

Standard_Real
tnbLib::airfoilLib::Type1::GetLeadCambSteep(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(LeadCambSteepId());
}

Standard_Real
tnbLib::airfoilLib::Type1::GetLeadCambSteepTight(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(LeadCambSteepTightId());
}

Standard_Real
tnbLib::airfoilLib::Type1::GetLeadCambSteepWeight(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(LeadCambSteepWeightId());
}

Standard_Real
tnbLib::airfoilLib::Type1::GetTrailCambSteep(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(TrailCambSteepId());
}

Standard_Real
tnbLib::airfoilLib::Type1::GetTrailCambSteepTight(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(TrailCambSteepTightId());
}

Standard_Real
tnbLib::airfoilLib::Type1::GetTrailCambSteepWeight(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(TrailCambSteepWeightId());
}

Standard_Real
tnbLib::airfoilLib::Type1::GetMaxThick(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(MaxThickId());
}

Standard_Real
tnbLib::airfoilLib::Type1::GetMaxThickLoc(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(MaxThickLocId());
}

Standard_Real
tnbLib::airfoilLib::Type1::GetLeadThickSteep(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(LeadThickSteepId());
}

Standard_Real
tnbLib::airfoilLib::Type1::GetLeadThickSteepTight(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(LeadThickSteepTightId());
}

Standard_Real
tnbLib::airfoilLib::Type1::GetLeadThickSteepWeight(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(LeadThickSteepWeightId());
}

Standard_Real
tnbLib::airfoilLib::Type1::GetTrailThickSteep(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(TrailThickSteepId());
}

Standard_Real
tnbLib::airfoilLib::Type1::GetTrailThickSteepTight(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(TrailThickSteepTightId());
}

Standard_Real
tnbLib::airfoilLib::Type1::GetTrailThickSteepWeight(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(TrailThickSteepWeightId());
}

void tnbLib::airfoilLib::Type1::InsertXo
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

void tnbLib::airfoilLib::Type1::InsertYo
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

void tnbLib::airfoilLib::Type1::InsertChordLen
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

void tnbLib::airfoilLib::Type1::InsertMaxCamb
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(MaxCambId()) = x;
}

void tnbLib::airfoilLib::Type1::InsertMaxCambLoc
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(MaxCambLocId()) = x;
}

void tnbLib::airfoilLib::Type1::InsertLeadCambSteep
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(LeadCambSteepId()) = x;
}

void tnbLib::airfoilLib::Type1::InsertLeadCambSteepTight
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(LeadCambSteepTightId()) = x;
}

void tnbLib::airfoilLib::Type1::InsertLeadCambSteepWeight
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(LeadCambSteepWeightId()) = x;
}

void tnbLib::airfoilLib::Type1::InsertTrailCambSteep
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(TrailCambSteepId()) = x;
}

void tnbLib::airfoilLib::Type1::InsertTrailCambSteepTight
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(TrailCambSteepTightId()) = x;
}

void tnbLib::airfoilLib::Type1::InsertTrailCambSteepWeight
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(TrailCambSteepWeightId()) = x;
}

void tnbLib::airfoilLib::Type1::InsertMaxThick
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(MaxThickId()) = x;
}

void tnbLib::airfoilLib::Type1::InsertMaxThickLoc
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(MaxThickLocId()) = x;
}

void tnbLib::airfoilLib::Type1::InsertLeadThickSteep
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(LeadThickSteepId()) = x;
}

void tnbLib::airfoilLib::Type1::InsertLeadThickSteepTight
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(LeadThickSteepTightId()) = x;
}

void tnbLib::airfoilLib::Type1::InsertLeadThickSteepWeight
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(LeadThickSteepWeightId()) = x;
}

void tnbLib::airfoilLib::Type1::InsertTrailThickSteep
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(TrailThickSteepId()) = x;
}

void tnbLib::airfoilLib::Type1::InsertTrailThickSteepTight
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(TrailThickSteepTightId()) = x;
}

void tnbLib::airfoilLib::Type1::InsertTrailThickSteepWeight
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(TrailThickSteepWeightId()) = x;
}

std::tuple<tnbLib::airfoilLib::Type1::xoPar,
	tnbLib::airfoilLib::Type1::yoPar, 
	tnbLib::airfoilLib::Type1::chordLenPar, 
	tnbLib::airfoilLib::Type1::maxCambPar, 
	tnbLib::airfoilLib::Type1::maxCambLocPar, 
	tnbLib::airfoilLib::Type1::leadCambSteepPar, 
	tnbLib::airfoilLib::Type1::leadCambSteepTightPar, 
	tnbLib::airfoilLib::Type1::leadCambSteepWeightPar, 
	tnbLib::airfoilLib::Type1::trailCambSteepPar, 
	tnbLib::airfoilLib::Type1::trailCambSteepTightPar, 
	tnbLib::airfoilLib::Type1::trailCambSteepWeightPar, 
	tnbLib::airfoilLib::Type1::maxThickPar, 
	tnbLib::airfoilLib::Type1::maxThickLocPar, 
	tnbLib::airfoilLib::Type1::leadThickSteepPar, 
	tnbLib::airfoilLib::Type1::leadThickSteepTightPar, 
	tnbLib::airfoilLib::Type1::leadThickSteepWeightPar, 
	tnbLib::airfoilLib::Type1::trailThickSteepPar, 
	tnbLib::airfoilLib::Type1::trailThickSteepTightPar, 
	tnbLib::airfoilLib::Type1::trailThickSteepWeightPar
> tnbLib::airfoilLib::Type1::RetrieveParameters(const std::vector<Standard_Real>& xs)
{
	xoPar p0 = { GetXo(xs) };
	yoPar p1 = { GetYo(xs) };

	chordLenPar p2 = { GetChordLen(xs) };

	maxCambPar p3 = { GetMaxCamb(xs) };
	maxCambLocPar p4 = { GetMaxCambLoc(xs) };

	leadCambSteepPar p5 = { GetLeadCambSteep(xs) };
	leadCambSteepTightPar p6 = { GetLeadCambSteepTight(xs) };
	leadCambSteepWeightPar p7 = { GetLeadCambSteepWeight(xs) };
	trailCambSteepPar p8 = { GetTrailCambSteep(xs) };
	trailCambSteepTightPar p9 = { GetTrailCambSteepTight(xs) };
	trailCambSteepWeightPar p10 = { GetTrailCambSteepWeight(xs) };

	maxThickPar p11 = { GetMaxThick(xs) };
	maxThickLocPar p12 = { GetMaxThickLoc(xs) };

	leadThickSteepPar p13 = { GetLeadThickSteep(xs) };
	leadThickSteepTightPar p14 = { GetLeadThickSteepTight(xs) };
	leadThickSteepWeightPar p15 = { GetLeadThickSteepWeight(xs) };
	trailThickSteepPar p16 = { GetTrailThickSteep(xs) };
	trailThickSteepTightPar p17 = { GetTrailThickSteepTight(xs) };
	trailThickSteepWeightPar p18 = { GetTrailThickSteepWeight(xs) };

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
		std::move(p17),
		std::move(p18)
		);
	return std::move(t);
}

void tnbLib::airfoilLib::Type1::CheckVector(const std::vector<Standard_Real>& xs)
{
	if (xs.size() NOT_EQUAL Type1::nb_parameters)
	{
		FatalErrorIn(FunctionSIG)
			<< "the vector is incompatible with this section." << endl
			<< abort(FatalError);
	}
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type1::CreateXo
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type1::xoPar::id + 1);
	par->SetName(XoName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type1::CreateYo
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type1::yoPar::id + 1);
	par->SetName(YoName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type1::CreateChordLen
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type1::chordLenPar::id + 1);
	par->SetName(ChordLenName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type1::CreateMaxCamb
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type1::chordLenPar::id + 1);
	par->SetName(MaxCambName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type1::CreateMaxCambLoc
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type1::chordLenPar::id + 1);
	par->SetName(MaxCambLocName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type1::CreateLeadCambSteep
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type1::chordLenPar::id + 1);
	par->SetName(LeadCambSteepName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type1::CreateLeadCambSteepTight
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type1::chordLenPar::id + 1);
	par->SetName(LeadCambSteepTightName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type1::CreateLeadCambSteepWeight
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type1::chordLenPar::id + 1);
	par->SetName(LeadCambSteepWeightName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type1::CreateTrailCambSteep
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type1::chordLenPar::id + 1);
	par->SetName(TrailCambSteepName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type1::CreateTrailCambSteepTight
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type1::chordLenPar::id + 1);
	par->SetName(TrailCambSteepTightName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type1::CreateTrailCambSteepWeight
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type1::chordLenPar::id + 1);
	par->SetName(TrailCambSteepWeightName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type1::CreateMaxThick
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type1::chordLenPar::id + 1);
	par->SetName(MaxThickName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type1::CreateMaxThickLoc
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type1::chordLenPar::id + 1);
	par->SetName(MaxThickLocName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type1::CreateLeadThickSteep
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type1::chordLenPar::id + 1);
	par->SetName(LeadThickSteepName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type1::CreateLeadThickSteepTight
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type1::chordLenPar::id + 1);
	par->SetName(LeadThickSteepTightName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type1::CreateLeadThickSteepWeight
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type1::chordLenPar::id + 1);
	par->SetName(LeadThickSteepWeightName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type1::CreateTrailThickSteep
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type1::chordLenPar::id + 1);
	par->SetName(TrailThickSteepName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type1::CreateTrailThickSteepTight
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type1::chordLenPar::id + 1);
	par->SetName(TrailThickSteepTightName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type1::CreateTrailThickSteepWeight
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type1::chordLenPar::id + 1);
	par->SetName(TrailThickSteepWeightName());
	return std::move(par);
}

std::shared_ptr<tnbLib::airfoilLib::Type1::Parameters>
tnbLib::airfoilLib::Type1::CreateParChromosome
(
	const Standard_Real theXo,
	const Standard_Real theYo, 
	const Standard_Real theChordLen,
	const Standard_Real theMaxCamb,
	const Standard_Real theMaxCambLoc, 
	const Standard_Real theLeadCambSteep,
	const Standard_Real theLeadCambSteepTight, 
	const Standard_Real theLeadCambSteepWeight,
	const Standard_Real theTrailCambSteep, 
	const Standard_Real theTrailCambSteepTight, 
	const Standard_Real theTrailCambSteepWeight,
	const Standard_Real theMaxThick, 
	const Standard_Real theMaxThickLoc,
	const Standard_Real theLeadThickSteep, 
	const Standard_Real theLeadThickSteepTight, 
	const Standard_Real theLeadThickSteepWeight, 
	const Standard_Real theTrailThickSteep,
	const Standard_Real theTrailThickSteepTight,
	const Standard_Real theTrailThickSteepWeight
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
		Param p{ theYo,chordLenPar::name };
		pars.at(ChordLenId()) = std::move(p);
	}

	{
		Param p{ theYo,maxCambPar::name };
		pars.at(MaxCambId()) = std::move(p);
	}
	{
		Param p{ theYo,maxCambLocPar::name };
		pars.at(MaxCambLocId()) = std::move(p);
	}

	{
		Param p{ theYo,leadCambSteepPar::name };
		pars.at(LeadCambSteepId()) = std::move(p);
	}
	{
		Param p{ theYo,leadCambSteepTightPar::name };
		pars.at(LeadCambSteepTightId()) = std::move(p);
	}
	{
		Param p{ theYo,leadCambSteepWeightPar::name };
		pars.at(LeadCambSteepWeightId()) = std::move(p);
	}

	{
		Param p{ theYo,trailCambSteepPar::name };
		pars.at(TrailCambSteepId()) = std::move(p);
	}
	{
		Param p{ theYo,trailCambSteepTightPar::name };
		pars.at(TrailCambSteepTightId()) = std::move(p);
	}
	{
		Param p{ theYo,trailCambSteepWeightPar::name };
		pars.at(TrailCambSteepWeightId()) = std::move(p);
	}

	{
		Param p{ theYo,maxThickPar::name };
		pars.at(MaxThickId()) = std::move(p);
	}
	{
		Param p{ theYo,maxThickLocPar::name };
		pars.at(MaxThickLocId()) = std::move(p);
	}

	{
		Param p{ theYo,leadThickSteepPar::name };
		pars.at(LeadThickSteepId()) = std::move(p);
	}
	{
		Param p{ theYo,leadThickSteepTightPar::name };
		pars.at(LeadThickSteepTightId()) = std::move(p);
	}
	{
		Param p{ theYo,leadThickSteepWeightPar::name };
		pars.at(LeadThickSteepWeightId()) = std::move(p);
	}

	{
		Param p{ theYo,trailThickSteepPar::name };
		pars.at(TrailThickSteepId()) = std::move(p);
	}
	{
		Param p{ theYo,trailThickSteepTightPar::name };
		pars.at(TrailThickSteepTightId()) = std::move(p);
	}
	{
		Param p{ theYo,trailThickSteepWeightPar::name };
		pars.at(TrailThickSteepWeightId()) = std::move(p);
	}
	Parameters pchromRef = { std::move(pars) };
	auto pchrom = std::make_shared<Parameters>(std::move(pchromRef));
	return std::move(pchrom);
}