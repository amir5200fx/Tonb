#include <PtdShapeFit2d_Airfoil_t2.hxx>

#include <PtdShapeFit_Par.hxx>

const char* tnbLib::airfoilLib::Type2::xoPar::name = "xo";
const char* tnbLib::airfoilLib::Type2::yoPar::name = "yo";

const char* tnbLib::airfoilLib::Type2::chordLenPar::name = "chordlen";

const char* tnbLib::airfoilLib::Type2::maxCambPar::name = "maxCamb";
const char* tnbLib::airfoilLib::Type2::maxCambLocPar::name = "maxCambLoc";

const char* tnbLib::airfoilLib::Type2::leadCambSteepPar::name = "leadCambSteep";
const char* tnbLib::airfoilLib::Type2::leadCambSteepTightPar::name = "leadCambSteepTight";
const char* tnbLib::airfoilLib::Type2::leadCambSteepWeightPar::name = "leadCambSteepWeight";

const char* tnbLib::airfoilLib::Type2::trailCambSteepPar::name = "trailCambSteep";
const char* tnbLib::airfoilLib::Type2::trailCambSteepTightPar::name = "trailCambSteepTight";
const char* tnbLib::airfoilLib::Type2::trailCambSteepWeightPar::name = "trailCambSteepWeight";

const char* tnbLib::airfoilLib::Type2::maxThickPar::name = "maxThick";
const char* tnbLib::airfoilLib::Type2::maxThickLocPar::name = "maxThickLoc";

const char* tnbLib::airfoilLib::Type2::leadThickSteepTight1Par::name = "leadThickSteepTight1";
const char* tnbLib::airfoilLib::Type2::leadThickSteepTight2Par::name = "leadThickSteepTight2";

const char* tnbLib::airfoilLib::Type2::trailThickSteepPar::name = "trailThickSteep";
const char* tnbLib::airfoilLib::Type2::trailThickSteepTightPar::name = "trailThickSteepTight";
const char* tnbLib::airfoilLib::Type2::trailThickSteepVelocityPar::name = "trailThickSteepVelocity";

std::map<Standard_Integer, const char*> tnbLib::airfoilLib::Type2::ParsMap;

namespace tnbLib
{

	class PtdShapeFit2d_AirfoilType2RunTime
	{

		/*Private Data*/

	public:

		// default constructor [4/28/2023 Payvand]

		PtdShapeFit2d_AirfoilType2RunTime()
		{
			SetConfig();
		}

		void SetConfig();

	};
}

void tnbLib::PtdShapeFit2d_AirfoilType2RunTime::SetConfig()
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
		auto paired = std::make_pair(airfoilLib::Type2::chordLenPar::id, airfoilLib::Type2::chordLenPar::name);
		airfoilLib::Type2::ParsMap.insert(std::move(paired));
	}

	{
		auto paired = std::make_pair(airfoilLib::Type2::maxCambPar::id, airfoilLib::Type2::maxCambPar::name);
		airfoilLib::Type2::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type2::maxCambLocPar::id, airfoilLib::Type2::maxCambLocPar::name);
		airfoilLib::Type2::ParsMap.insert(std::move(paired));
	}

	{
		auto paired = std::make_pair(airfoilLib::Type2::leadCambSteepPar::id, airfoilLib::Type2::leadCambSteepPar::name);
		airfoilLib::Type2::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type2::leadCambSteepTightPar::id, airfoilLib::Type2::leadCambSteepTightPar::name);
		airfoilLib::Type2::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type2::leadCambSteepWeightPar::id, airfoilLib::Type2::leadCambSteepWeightPar::name);
		airfoilLib::Type2::ParsMap.insert(std::move(paired));
	}

	{
		auto paired = std::make_pair(airfoilLib::Type2::trailCambSteepPar::id, airfoilLib::Type2::trailCambSteepPar::name);
		airfoilLib::Type2::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type2::trailCambSteepTightPar::id, airfoilLib::Type2::trailCambSteepTightPar::name);
		airfoilLib::Type2::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type2::trailCambSteepWeightPar::id, airfoilLib::Type2::trailCambSteepWeightPar::name);
		airfoilLib::Type2::ParsMap.insert(std::move(paired));
	}

	{
		auto paired = std::make_pair(airfoilLib::Type2::maxThickPar::id, airfoilLib::Type2::maxThickPar::name);
		airfoilLib::Type2::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type2::maxThickLocPar::id, airfoilLib::Type2::maxThickLocPar::name);
		airfoilLib::Type2::ParsMap.insert(std::move(paired));
	}

	{
		auto paired = std::make_pair(airfoilLib::Type2::leadThickSteepTight1Par::id, airfoilLib::Type2::leadThickSteepTight1Par::name);
		airfoilLib::Type2::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type2::leadThickSteepTight2Par::id, airfoilLib::Type2::leadThickSteepTight2Par::name);
		airfoilLib::Type2::ParsMap.insert(std::move(paired));
	}

	{
		auto paired = std::make_pair(airfoilLib::Type2::trailThickSteepPar::id, airfoilLib::Type2::trailThickSteepPar::name);
		airfoilLib::Type2::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type2::trailThickSteepTightPar::id, airfoilLib::Type2::trailThickSteepTightPar::name);
		airfoilLib::Type2::ParsMap.insert(std::move(paired));
	}
	{
		auto paired = std::make_pair(airfoilLib::Type2::trailThickSteepVelocityPar::id, airfoilLib::Type2::trailThickSteepVelocityPar::name);
		airfoilLib::Type2::ParsMap.insert(std::move(paired));
	}
}

tnbLib::PtdShapeFit2d_AirfoilType2RunTime myPtdShapeFit2d_AirfoilType1RunTimeObj;

const unsigned int tnbLib::airfoilLib::Type2::nb_parameters = 18;
unsigned short tnbLib::airfoilLib::Type2::verbose(0);

const char* 
tnbLib::airfoilLib::Type2::ParName
(
	const Standard_Integer theIndex
) const
{
	return ParsMap.at(theIndex);
}

Standard_Integer 
tnbLib::airfoilLib::Type2::NbPars() const
{
	return Standard_Integer(nb_parameters);
}

std::shared_ptr<tnbLib::airfoilLib::Type2::Parameters>
tnbLib::airfoilLib::Type2::RetrieveParChromosome
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
		Param p{ GetLeadThickSteepTight1(theChromosome), leadThickSteepTight1Par::name };
		pars.at(LeadThickSteepTight1Id()) = std::move(p);
	}
	{
		Param p{ GetLeadThickSteepTight2(theChromosome), leadThickSteepTight1Par::name };
		pars.at(LeadThickSteepTight2Id()) = std::move(p);
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
		Param p{ GetTrailThickSteepVelocity(theChromosome),trailThickSteepVelocityPar::name };
		pars.at(TrailThickSteepVelocityId()) = std::move(p);
	}
	Parameters pchromRef = { std::move(pars) };
	auto pchrom = std::make_shared<Parameters>(std::move(pchromRef));
	return std::move(pchrom);
}

std::vector<std::shared_ptr<tnbLib::PtdShapeFit_Par>> 
tnbLib::airfoilLib::Type2::RetrieveParList() const
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

	pars.at(LeadThickSteepTight1Id()) = LeadThickSteepTight1();
	pars.at(LeadThickSteepTight2Id()) = LeadThickSteepTight2();

	pars.at(TrailThickSteepId()) = TrailThickSteep();
	pars.at(TrailThickSteepTightId()) = TrailThickSteepTight();
	pars.at(TrailThickSteepVelocityId()) = TrailThickSteepVelocity();
	return std::move(pars);
}

std::vector<Standard_Real> 
tnbLib::airfoilLib::Type2::RetrieveChromosome
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

		chromosome.at(LeadThickSteepTight1Id()) = pars.x.at(LeadThickSteepTight1Id()).x;
		chromosome.at(LeadThickSteepTight2Id()) = pars.x.at(LeadThickSteepTight2Id()).x;

		chromosome.at(TrailThickSteepId()) = pars.x.at(TrailThickSteepId()).x;
		chromosome.at(TrailThickSteepTightId()) = pars.x.at(TrailThickSteepTightId()).x;
		chromosome.at(TrailThickSteepVelocityId()) = pars.x.at(TrailThickSteepVelocityId()).x;

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

void tnbLib::airfoilLib::Type2::SetParameters
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
		Param x = { GetLeadThickSteepTight1(theXs),LeadThickSteepTight1Name() };
		pars.at(LeadThickSteepTight1Id()) = std::move(x);
	}
	{
		Param x = { GetLeadThickSteepTight2(theXs),LeadThickSteepTight2Name() };
		pars.at(LeadThickSteepTight2Id()) = std::move(x);
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
		Param x{ GetTrailThickSteepVelocity(theXs),TrailThickSteepVelocityName() };
		pars.at(TrailThickSteepVelocityId()) = std::move(x);
	}
	Parameters xPars = { std::move(pars) };
	ParsRef() = std::make_shared<Parameters>(std::move(xPars));
}

Standard_Integer
tnbLib::airfoilLib::Type2::XoId()
{
	return Standard_Integer(xoPar::id);
}

Standard_Integer
tnbLib::airfoilLib::Type2::YoId()
{
	return Standard_Integer(yoPar::id);
}

Standard_Integer
tnbLib::airfoilLib::Type2::ChordLenId()
{
	return Standard_Integer(chordLenPar::id);
}

Standard_Integer
tnbLib::airfoilLib::Type2::MaxCambId()
{
	return Standard_Integer(maxCambPar::id);
}

Standard_Integer
tnbLib::airfoilLib::Type2::MaxCambLocId()
{
	return Standard_Integer(maxCambLocPar::id);
}

Standard_Integer
tnbLib::airfoilLib::Type2::LeadCambSteepId()
{
	return Standard_Integer(leadCambSteepPar::id);
}

Standard_Integer
tnbLib::airfoilLib::Type2::LeadCambSteepTightId()
{
	return Standard_Integer(leadCambSteepTightPar::id);
}

Standard_Integer
tnbLib::airfoilLib::Type2::LeadCambSteepWeightId()
{
	return Standard_Integer(leadCambSteepWeightPar::id);
}

Standard_Integer
tnbLib::airfoilLib::Type2::TrailCambSteepId()
{
	return Standard_Integer(trailCambSteepPar::id);
}

Standard_Integer
tnbLib::airfoilLib::Type2::TrailCambSteepTightId()
{
	return Standard_Integer(trailCambSteepTightPar::id);
}

Standard_Integer
tnbLib::airfoilLib::Type2::TrailCambSteepWeightId()
{
	return Standard_Integer(trailCambSteepWeightPar::id);
}

Standard_Integer
tnbLib::airfoilLib::Type2::MaxThickId()
{
	return Standard_Integer(maxThickPar::id);
}

Standard_Integer
tnbLib::airfoilLib::Type2::MaxThickLocId()
{
	return Standard_Integer(maxThickLocPar::id);
}

Standard_Integer 
tnbLib::airfoilLib::Type2::LeadThickSteepTight1Id()
{
	return Standard_Integer(leadThickSteepTight1Par::id);
}

Standard_Integer
tnbLib::airfoilLib::Type2::LeadThickSteepTight2Id()
{
	return Standard_Integer(leadThickSteepTight2Par::id);
}

Standard_Integer 
tnbLib::airfoilLib::Type2::TrailThickSteepId()
{
	return Standard_Integer(trailThickSteepPar::id);
}

Standard_Integer
tnbLib::airfoilLib::Type2::TrailThickSteepTightId()
{
	return Standard_Integer(trailThickSteepTightPar::id);
}

Standard_Integer
tnbLib::airfoilLib::Type2::TrailThickSteepVelocityId()
{
	return Standard_Integer(trailThickSteepVelocityPar::id);
}

Standard_Real
tnbLib::airfoilLib::Type2::GetXo(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(XoId());
}

Standard_Real
tnbLib::airfoilLib::Type2::GetYo(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(YoId());
}

Standard_Real
tnbLib::airfoilLib::Type2::GetChordLen(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(ChordLenId());
}

Standard_Real
tnbLib::airfoilLib::Type2::GetMaxCamb(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(MaxCambId());
}

Standard_Real
tnbLib::airfoilLib::Type2::GetMaxCambLoc(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(MaxCambLocId());
}

Standard_Real
tnbLib::airfoilLib::Type2::GetLeadCambSteep(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(LeadCambSteepId());
}

Standard_Real
tnbLib::airfoilLib::Type2::GetLeadCambSteepTight(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(LeadCambSteepTightId());
}

Standard_Real
tnbLib::airfoilLib::Type2::GetLeadCambSteepWeight(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(LeadCambSteepWeightId());
}

Standard_Real
tnbLib::airfoilLib::Type2::GetTrailCambSteep(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(TrailCambSteepId());
}

Standard_Real
tnbLib::airfoilLib::Type2::GetTrailCambSteepTight(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(TrailCambSteepTightId());
}

Standard_Real
tnbLib::airfoilLib::Type2::GetTrailCambSteepWeight(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(TrailCambSteepWeightId());
}

Standard_Real
tnbLib::airfoilLib::Type2::GetMaxThick(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(MaxThickId());
}

Standard_Real
tnbLib::airfoilLib::Type2::GetMaxThickLoc(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(MaxThickLocId());
}

Standard_Real 
tnbLib::airfoilLib::Type2::GetLeadThickSteepTight1(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(LeadThickSteepTight1Id());
}

Standard_Real
tnbLib::airfoilLib::Type2::GetLeadThickSteepTight2(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(LeadThickSteepTight2Id());
}

Standard_Real 
tnbLib::airfoilLib::Type2::GetTrailThickSteep(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(TrailThickSteepId());
}

Standard_Real
tnbLib::airfoilLib::Type2::GetTrailThickSteepTight(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(TrailThickSteepTightId());
}

Standard_Real
tnbLib::airfoilLib::Type2::GetTrailThickSteepVelocity(const std::vector<Standard_Real>& xs)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	return xs.at(TrailThickSteepVelocityId());
}

void tnbLib::airfoilLib::Type2::InsertXo
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

void tnbLib::airfoilLib::Type2::InsertYo
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

void tnbLib::airfoilLib::Type2::InsertChordLen
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

void tnbLib::airfoilLib::Type2::InsertMaxCamb
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

void tnbLib::airfoilLib::Type2::InsertMaxCambLoc
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

void tnbLib::airfoilLib::Type2::InsertLeadCambSteep
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

void tnbLib::airfoilLib::Type2::InsertLeadCambSteepTight
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

void tnbLib::airfoilLib::Type2::InsertLeadCambSteepWeight
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

void tnbLib::airfoilLib::Type2::InsertTrailCambSteep
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

void tnbLib::airfoilLib::Type2::InsertTrailCambSteepTight
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

void tnbLib::airfoilLib::Type2::InsertTrailCambSteepWeight
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

void tnbLib::airfoilLib::Type2::InsertMaxThick
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

void tnbLib::airfoilLib::Type2::InsertMaxThickLoc
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

void tnbLib::airfoilLib::Type2::InsertLeadThickSteepTight1
(
	const Standard_Real x, 
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(LeadThickSteepTight1Id()) = x;
}

void tnbLib::airfoilLib::Type2::InsertLeadThickSteepTight2
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(LeadThickSteepTight2Id()) = x;
}

void tnbLib::airfoilLib::Type2::InsertTrailThickSteep
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

void tnbLib::airfoilLib::Type2::InsertTrailThickSteepTight
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

void tnbLib::airfoilLib::Type2::InsertTrailThickSteepVelocity
(
	const Standard_Real x,
	std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	CheckVector(xs);
#endif // _DEBUG
	xs.at(TrailThickSteepVelocityId()) = x;
}

std::tuple<tnbLib::airfoilLib::Type2::xoPar, 
	tnbLib::airfoilLib::Type2::yoPar, 
	tnbLib::airfoilLib::Type2::chordLenPar, 
	tnbLib::airfoilLib::Type2::maxCambPar, 
	tnbLib::airfoilLib::Type2::maxCambLocPar, 
	tnbLib::airfoilLib::Type2::leadCambSteepPar, 
	tnbLib::airfoilLib::Type2::leadCambSteepTightPar, 
	tnbLib::airfoilLib::Type2::leadCambSteepWeightPar, 
	tnbLib::airfoilLib::Type2::trailCambSteepPar, 
	tnbLib::airfoilLib::Type2::trailCambSteepTightPar, 
	tnbLib::airfoilLib::Type2::trailCambSteepWeightPar, 
	tnbLib::airfoilLib::Type2::maxThickPar, 
	tnbLib::airfoilLib::Type2::maxThickLocPar, 
	tnbLib::airfoilLib::Type2::leadThickSteepTight1Par, 
	tnbLib::airfoilLib::Type2::leadThickSteepTight2Par, 
	tnbLib::airfoilLib::Type2::trailThickSteepPar, 
	tnbLib::airfoilLib::Type2::trailThickSteepTightPar, 
	tnbLib::airfoilLib::Type2::trailThickSteepVelocityPar> 
	tnbLib::airfoilLib::Type2::RetrieveParameters(const std::vector<Standard_Real>& xs)
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

	leadThickSteepTight1Par p13 = { GetLeadThickSteepTight1(xs) };
	leadThickSteepTight2Par p14 = { GetLeadThickSteepTight2(xs) };
	trailThickSteepPar p15 = { GetTrailThickSteep(xs) };
	trailThickSteepTightPar p16 = { GetTrailThickSteepTight(xs) };
	trailThickSteepVelocityPar p17 = { GetTrailThickSteepVelocity(xs) };

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

void tnbLib::airfoilLib::Type2::CheckVector(const std::vector<Standard_Real>& xs)
{
	if (xs.size() NOT_EQUAL Type2::nb_parameters)
	{
		FatalErrorIn(FunctionSIG)
			<< "the vector is incompatible with this section." << endl
			<< abort(FatalError);
	}
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type2::CreateXo
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type2::xoPar::id + 1);
	par->SetName(XoName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type2::CreateYo
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type2::yoPar::id + 1);
	par->SetName(YoName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type2::CreateChordLen
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type2::chordLenPar::id + 1);
	par->SetName(ChordLenName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type2::CreateMaxCamb
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type2::chordLenPar::id + 1);
	par->SetName(MaxCambName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type2::CreateMaxCambLoc
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type2::chordLenPar::id + 1);
	par->SetName(MaxCambLocName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type2::CreateLeadCambSteep
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type2::chordLenPar::id + 1);
	par->SetName(LeadCambSteepName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type2::CreateLeadCambSteepTight
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type2::chordLenPar::id + 1);
	par->SetName(LeadCambSteepTightName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type2::CreateLeadCambSteepWeight
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type2::chordLenPar::id + 1);
	par->SetName(LeadCambSteepWeightName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type2::CreateTrailCambSteep
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type2::chordLenPar::id + 1);
	par->SetName(TrailCambSteepName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type2::CreateTrailCambSteepTight
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type2::chordLenPar::id + 1);
	par->SetName(TrailCambSteepTightName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type2::CreateTrailCambSteepWeight
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type2::chordLenPar::id + 1);
	par->SetName(TrailCambSteepWeightName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type2::CreateMaxThick
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type2::chordLenPar::id + 1);
	par->SetName(MaxThickName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type2::CreateMaxThickLoc
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type2::chordLenPar::id + 1);
	par->SetName(MaxThickLocName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par> 
tnbLib::airfoilLib::Type2::CreateLeadThickSteepTight1
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type2::chordLenPar::id + 1);
	par->SetName(LeadThickSteepTight1Name());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type2::CreateLeadThickSteepTight2
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type2::chordLenPar::id + 1);
	par->SetName(LeadThickSteepTight2Name());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type2::CreateTrailThickSteep
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type2::chordLenPar::id + 1);
	par->SetName(TrailThickSteepName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type2::CreateTrailThickSteepTight
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type2::chordLenPar::id + 1);
	par->SetName(TrailThickSteepTightName());
	return std::move(par);
}

std::shared_ptr<tnbLib::PtdShapeFit_Par>
tnbLib::airfoilLib::Type2::CreateTrailThickSteepVelocity
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	auto par = std::make_shared<PtdShapeFit_Par>(theLower, theUpper);
	par->SetIndex((int)Type2::chordLenPar::id + 1);
	par->SetName(TrailThickSteepVelocityName());
	return std::move(par);
}

std::shared_ptr<tnbLib::airfoilLib::Type2::Parameters> 
tnbLib::airfoilLib::Type2::CreateParChromosome
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
	const Standard_Real theLeadThickSteepTight1, 
	const Standard_Real theLeadThickSteepTight2,
	const Standard_Real theTrailThickSteep, 
	const Standard_Real theTrailThickSteepTight,
	const Standard_Real theTrailThickSteepVelocity
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
		Param p{ theYo,leadThickSteepTight1Par::name };
		pars.at(LeadThickSteepTight1Id()) = std::move(p);
	}
	{
		Param p{ theYo,leadThickSteepTight2Par::name };
		pars.at(LeadThickSteepTight2Id()) = std::move(p);
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
		Param p{ theYo,trailThickSteepVelocityPar::name };
		pars.at(TrailThickSteepVelocityId()) = std::move(p);
	}
	Parameters pchromRef = { std::move(pars) };
	auto pchrom = std::make_shared<Parameters>(std::move(pchromRef));
	return std::move(pchrom);
}