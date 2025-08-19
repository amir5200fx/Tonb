#include <Model_DisplNo1.hxx>

#include <Model_ParamProfile.hxx>
#include <Model_VesselProfiles.hxx>
#include <Model_CorneredSectionVessel.hxx>
#include <Geo_Tools.hxx>
#include <Pnt3d.hxx>
#include <Pnt2d.hxx>
#include <Dir2d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

//std::shared_ptr<tnbLib::modelLib::vesselLib::DeckProfileXs>
//tnbLib::Model_DisplNo1::CalcXSections() const
//{
//	const auto& dimens = Parameters().Dimensions();
//
//	auto nbSections = dimens.NbNetColumns();
//
//	// Excluding the stem pair [12/23/2022 Payvand]
//	nbSections--;
//	if (nbSections <= 4)
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "Invalid nb. of sections has been detected." << endl
//			<< abort(FatalError);
//	}
//
//	std::vector<Standard_Real> Xs(nbSections, 0.0);
//
//	const auto dx = dimens.LengthOnDeck()->Value() / (Standard_Real)(nbSections - 1);
//
//	nbSections++;
//
//	auto section = (Standard_Integer)0;
//	Xs.at(section) = 0;
//
//	section = nbSections - 1;
//	Xs.at(section) = std::min(nbSections * dx, dimens.LengthOnDeck()->Value());
//
//	section = nbSections - 2;
//	Xs.at(section) = std::min(nbSections * dx, dimens.LengthOnDeck()->Value());
//
//	const auto dxA = ((Standard_Real)1.0 - SMALL_TOL) * dx;
//	const auto dxF = ((Standard_Real)1.0 - SMALL_TOL) * dx;
//
//	const auto x0 = dxA;
//	const auto x1 = dimens.LengthOnDeck()->Value() - dxF;
//
//	const auto dx = (x1 - x0) / (Standard_Real)(nbSections - 4);
//
//	for (auto id = (Standard_Integer)0; id <= nbSections - 4; id++)
//	{
//		section = id + 1;
//		Xs.at(section) = id * dx + x0;
//	}
//	auto profileXs = std::make_shared<modelLib::vesselLib::DeckProfileXs>(std::move(Xs));
//	return std::move(profileXs);
//}

std::shared_ptr<tnbLib::modelLib::vesselLib::KeelProfileXs>
tnbLib::Model_DisplNo1::CalcYSections() const
{
	const auto& deck = Profiles().Deck();
	if (NOT deck)
	{
		FatalErrorIn(FunctionSIG)
			<< "no deck profile has been found." << endl
			<< abort(FatalError);
	}

	CheckKeelProfile(deck, FunctionSIG);

	auto xs = KeelXs();
	std::vector<Standard_Real> ys;
	ys.reserve(xs.size());

	for (auto x : xs)
	{
		auto y = deck->Value(x);
		ys.push_back(y);
	}
	auto profileXs = std::make_shared<modelLib::vesselLib::KeelProfileXs>(std::move(ys));
	return std::move(profileXs);
}

std::shared_ptr<tnbLib::modelLib::vesselLib::KeelProfileXs>
tnbLib::Model_DisplNo1::CalcZSections() const
{
	const auto& keel = Profiles().Keel();
	if (NOT keel)
	{
		FatalErrorIn(FunctionSIG)
			<< "no keel profile has been found." << endl
			<< abort(FatalError);
	}

	CheckKeelProfile(keel, FunctionSIG);

	const auto xs = KeelXs();
	std::vector<Standard_Real> zs;
	zs.reserve(xs.size());

	for (auto x : xs)
	{
		auto z = keel->Value(x);
		zs.push_back(z);
	}
	auto profileXs = std::make_shared<modelLib::vesselLib::KeelProfileXs>(std::move(zs));
	return std::move(profileXs);
}

std::shared_ptr<tnbLib::modelLib::vesselLib::KeelProfileXs>
tnbLib::Model_DisplNo1::CalcxDepthSection() const
{
	const auto& depth = Profiles().Depth();
	if (NOT depth)
	{
		FatalErrorIn(FunctionSIG)
			<< "no depth profile has been found." << endl
			<< abort(FatalError);
	}

	CheckKeelProfile(depth, FunctionSIG);

	const auto xs = KeelXs();
	std::vector<Standard_Real> ds;
	ds.reserve(xs.size());

	for (auto x : xs)
	{
		auto d = depth->Value(x);
		ds.push_back(d);
	}
	auto profileXs = std::make_shared<modelLib::vesselLib::KeelProfileXs>(std::move(ds));
	return std::move(profileXs);
}

std::shared_ptr<tnbLib::modelLib::vesselLib::KeelProfileXs>
tnbLib::Model_DisplNo1::CalcxDeadrise() const
{
	const auto& deadrise = Profiles().Deadrise();
	if (NOT deadrise)
	{
		FatalErrorIn(FunctionSIG)
			<< "no deadrise profile has been found." << endl
			<< abort(FatalError);
	}

	CheckKeelProfile(deadrise, FunctionSIG);

	const auto xs = KeelXs();
	std::vector<Standard_Real> dr;
	dr.reserve(xs.size());

	for (auto x : xs)
	{
		dr.push_back(deadrise->Value(x));
	}
	auto profileXs = std::make_shared<modelLib::vesselLib::KeelProfileXs>(std::move(dr));
	return std::move(profileXs);
}

//std::shared_ptr<tnbLib::modelLib::vesselLib::KeelProfileXs>
//tnbLib::Model_DisplNo1::CalcxFlare() const
//{
//	const auto& flare = Profiles().Flare();
//	if (NOT flare)
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "no flare profile has been detected." << endl
//			<< abort(FatalError);
//	}
//
//	CheckKeelProfile(flare, FunctionSIG);
//
//	const auto xs = KeelXs();
//	std::vector<Standard_Real> fs;
//	fs.reserve(xs.size());
//
//	for (auto x : xs)
//	{
//		fs.push_back(flare->Value(x));
//	}
//	auto profileXs = std::make_shared<modelLib::vesselLib::KeelProfileXs>(std::move(fs));
//	return std::move(profileXs);
//}

std::shared_ptr<tnbLib::modelLib::vesselLib::KeelProfileXs>
tnbLib::Model_DisplNo1::CalcxSideslope() const
{
	const auto& sideSlope = Profiles().SideSlope();
	if (NOT sideSlope)
	{
		FatalErrorIn(FunctionSIG)
			<< "no sideSlope profile has been detected." << endl
			<< abort(FatalError);
	}

	CheckKeelProfile(sideSlope, FunctionSIG);

	const auto xs = KeelXs();
	std::vector<Standard_Real> sides;
	sides.reserve(xs.size());

	for (auto x : xs)
	{
		sides.push_back(sideSlope->Value(x));
	}
	auto profileXs = std::make_shared<modelLib::vesselLib::KeelProfileXs>(std::move(sides));
	return std::move(profileXs);
}

std::shared_ptr<tnbLib::modelLib::vesselLib::KeelProfileXs> 
tnbLib::Model_DisplNo1::CalcxTightness() const
{
	const auto& tightness = Profiles().Tightness();
	if (NOT tightness)
	{
		FatalErrorIn(FunctionSIG)
			<< "no tightness profile has been detected." << endl
			<< abort(FatalError);
	}

	CheckKeelProfile(tightness, FunctionSIG);

	const auto xs = KeelXs();
	std::vector<Standard_Real> ts;
	ts.reserve(xs.size());

	for (auto x : xs)
	{
		ts.push_back(tightness->Value(x));
	}
	auto profileXs = std::make_shared<modelLib::vesselLib::KeelProfileXs>(std::move(ts));
	return std::move(profileXs);
}

std::shared_ptr<tnbLib::Model_SectionVessel> 
tnbLib::Model_DisplNo1::CreateSection
(
	const SectionData& theData
) const
{
	const auto xSection = theData.x;
	const auto zSection = theData.z;
	const auto sideSlope = theData.sideSlope;
	const auto deadrise = theData.deadrise;
	const auto width = theData.width;
	const auto height = theData.height;

	const auto maxSideSlope = std::atan(MAX_SIDESLOPE_COEFF * width / height);
	const auto sideSlopeAngle = sideSlope * maxSideSlope;

	Pnt2d P0(0, zSection);
	Pnt2d P2(width, zSection + height);

	const auto maxDeadriseHeight = MAX_DEADRISE_COEFF * height;
	const auto maxDeadriseAngle = std::atan(maxDeadriseHeight / width);

	Dir2d t0(std::cos(deadrise * maxDeadriseAngle), std::sin(deadrise * maxDeadriseAngle));
	Dir2d t2(-std::sin(sideSlopeAngle), -std::cos(sideSlopeAngle));

	Entity2d_LineRef line0(P0, t0);
	Entity2d_LineRef line1(P2, t2);

	const auto intP = Geo_Tools::GetIntersectionPoint(Geo_Tools::Intersection_cgal(line0, line1));
}

void tnbLib::Model_DisplNo1::ApplyTightness
(
	const std::shared_ptr<Model_SectionVessel>& theSection,
	const Standard_Real theTightness
) const
{
	const auto nbCtrlPnts = (Standard_Integer)theSection->Points().size();
	auto section = std::dynamic_pointer_cast<Model_CorneredSectionVessel>(theSection);
	if (NOT section)
	{
		FatalErrorIn(FunctionSIG)
			<< "the section has no corner." << endl
			<< abort(FatalError);
	}

	const auto corner = section->CornerId();

	const auto nx = corner - (Standard_Integer)1;
	const auto du = (Standard_Real)1.0 / (Standard_Real)nx;

	const auto ny = (nbCtrlPnts - 1) - corner - 1;
	const auto dv = (Standard_Real)1.0 / (Standard_Real)ny;

	auto& pnts = section->PointsRef();

	if (theTightness <= (Standard_Real)0.5)
	{
		const auto& critPnt1 = pnts.at(1);
		const auto& critPnt2 = pnts.at(nbCtrlPnts - 2);

		const auto& p2 = pnts.at(corner);

		const auto t = (Standard_Real)1.0 - (Standard_Real)2.0 * theTightness;

		const auto newPos1 = critPnt1 + t * (p2 - critPnt1);

		forThose(Index, 0, nx - 1)
		{
			pnts.at(Index + 1) = 
				newPos1 + Index * du * (p2 - newPos1);
		}

		const auto newPos2 = critPnt2 + t * (p2 - critPnt2);

		forThose(Index, 0, ny - 1)
		{
			pnts.at(nbCtrlPnts - Index - 2) = 
				newPos2 + Index * dv * (p2 - newPos2);
		}
	}
	else
	{
		const auto& critPnt1 = pnts.at(corner - 1);
		const auto& critPnt2 = pnts.at(corner + 1);

		const auto t = (Standard_Real)2.0 * (theTightness - (Standard_Real)0.5);

		{
			const auto& p2 = pnts.at(0);

			const auto newPos1 = critPnt1 + t * (p2 - critPnt1);

			forThose(Index, 0, nx - 1)
			{
				pnts.at(corner - Index - 1) =
					newPos1 + Index * du * (p2 - newPos1);
			}
		}

		{
			const auto& p2 = pnts.at(nbCtrlPnts - 1);

			const auto newPos2 = critPnt2 + t * (p2 - critPnt2);

			forThose(Index, 0, ny - 1)
			{
				pnts.at(corner + Index + 1) = 
					newPos2 + Index * dv * (p2 - newPos2);
			}
		}
	}
}

void tnbLib::Model_DisplNo1::CheckDeckProfile
(
	const std::shared_ptr<Model_ParamProfile>& theProfile,
	const char* theFunName
) const
{
	if (NOT modelLib::vesselLib::is_deck_profile(theProfile))
	{
		FatalErrorIn(theFunName)
			<< "it's not a deck profile." << endl
			<< " - Profile: " << theProfile->Name() << endl
			<< abort(FatalError);
	}
}

void tnbLib::Model_DisplNo1::CheckKeelProfile
(
	const std::shared_ptr<Model_ParamProfile>& theProfile, 
	const char* theFunName
) const
{
	if (NOT modelLib::vesselLib::is_keel_profile(theProfile))
	{
		FatalErrorIn(theFunName)
			<< "it's not a keel profile." << endl
			<< " - Profile: " << theProfile->Name() << endl
			<< abort(FatalError);
	}
}