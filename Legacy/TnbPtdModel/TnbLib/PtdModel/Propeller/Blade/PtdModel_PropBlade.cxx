#include <PtdModel_PropBlade.hxx>

#include <Geo_xDistb.hxx>
#include <PtdModel_xPars.hxx>
#include <PtdModel_Form.hxx>
#include <PtdModel_Forms.hxx>
#include <PtdModel_Face.hxx>
#include <PtdModel_FormMaker.hxx>
#include <PtdModel_Profile.hxx>
#include <PtdModel_Profiles.hxx>
#include <PtdModel_BladeGlobalPars.hxx>
#include <PtdModel_BladeInfo.hxx>
#include <PtdModel_BladeView.hxx>
#include <PtdModel_WrappedBladeSection.hxx>
#include <PtdModel_UnWrappedBladeSection.hxx>
#include <PtdModel_BladeExpandedView.hxx>
#include <PtdModel_BladeFaces.hxx>
#include <PtdModel_PropSection.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::PtdModel_PropBlade::PtdModel_PropBlade
(
	const std::shared_ptr<PtdModel_BladeGlobalPars>& pars
)
{
	auto bladeInfo = std::make_shared<PtdModel_BladeInfo>();
	Debug_Null_Pointer(bladeInfo);

	bladeInfo->SetGlobals(pars);

	//bladeInfo->SetNbSections(DEFAULT_NB_SECTIONS);
	bladeInfo->SetNbSpans(DEFAULT_NB_SPANS);

	theBladeInfo_ = std::move(bladeInfo);
}

namespace tnbLib
{
	unsigned short PtdModel_PropBlade::verbose(0);

	const Standard_Integer PtdModel_PropBlade::DEFAULT_NB_SECTIONS = 10;
	const Standard_Integer PtdModel_PropBlade::DEFAULT_NB_SPANS = 55;
}

Standard_Integer 
tnbLib::PtdModel_PropBlade::NbSections() const
{
	if (NOT xDistb())
	{
		FatalErrorIn(FunctionSIG)
			<< "no spacing has been loaded!" << endl
			<< abort(FatalError);
	}
	return xDistb()->Size();
}

void tnbLib::PtdModel_PropBlade::CalcXParameters()
{
	if (NOT xDistb())
	{
		FatalErrorIn(FunctionSIG)
			<< "no spacing has been loaded!" << endl
			<< abort(FatalError);
	}

	auto xPars = std::make_shared<PtdModel_xPars>();
	Debug_Null_Pointer(xPars);

	auto xs = xDistb()->Values();
	xPars->SetXs(std::move(xs));

	const auto& profiles = Profiles();
	if (NOT profiles)
	{
		FatalErrorIn(FunctionSIG)
			<< "no profile has been found!" << endl
			<< abort(FatalError);
	}

	for (const auto& x : profiles->Profiles())
	{
		const auto& profile = x.second;
		Debug_Null_Pointer(profile);

		auto xValuesRef = profile->RetrieveValues(xDistb()->Values());
		auto xValues = std::make_shared<std::vector<Standard_Real>>(std::move(xValuesRef));

		xPars->SetParameter(x.first, std::move(xValues));
	}
	theParameters_ = std::move(xPars);
}

void tnbLib::PtdModel_PropBlade::CalcBladeView()
{
	if (NOT Section())
	{
		FatalErrorIn(FunctionSIG)
			<< "no section has been loaded!" << endl
			<< abort(FatalError);
	}

	auto bladeView = std::make_shared<PtdModel_BladeView>();
	Debug_Null_Pointer(bladeView);

	theBladeView_ = bladeView;

	std::vector<std::shared_ptr<PtdModel_BladeExpandedView>> expandedViews;
	expandedViews.reserve(NbSections());
	for (Standard_Integer section = 0; section < NbSections(); section++)
	{
		auto sectionQ = Section()->SectionQ(section, *this);
		Debug_Null_Pointer(sectionQ);

		auto expandedView = CreateExpandView(section, *sectionQ);
		expandedViews.push_back(std::move(expandedView));
	}

	bladeView->SetExpandedViews(std::move(expandedViews));

	auto unWrappedView = CreateUnWrappedView();
	bladeView->SetUnWrappedSections(std::move(unWrappedView));

	auto wrappedView = CreateWrappedView();
	bladeView->SetWrappedSections(std::move(wrappedView));
}

void tnbLib::PtdModel_PropBlade::CreateFaces()
{
	if (verbose)
	{
		Info << endl
			<< "*********** Creating Faces ************" << endl;
	}
	if (NOT BladeInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "no info has been found!" << endl
			<< abort(FatalError);
	}

	const auto nbSections = NbSections();
	const auto nbSpans = BladeInfo()->NbSpans();

	const auto& wrappedSections = BladeView()->WrappedSections();

	if (verbose)
	{
		Info << endl
			<< " retrieving the face offsets..." << endl;
	}
	std::vector<std::vector<Pnt3d>> Qs;
	Qs.reserve(nbSections);
	for (size_t section = 0; section < nbSections; section++)
	{
		if (verbose > 1)
		{
			Info << endl
				<< " - section nb. " << section << endl;
		}
		Debug_Bad_Index(section, 0, wrappedSections.size() - 1);
		const auto& wrappedSection = wrappedSections[section];

		const auto& pts = wrappedSection->Face();

		if (verbose > 1)
		{
			Info << endl
				<< " - face offsets: " << endl;
			for (const auto& x : pts)
			{
				Info << " - " << x << endl;
			}
			Info << endl;
		}
		std::vector<Pnt3d> Q;
		Q.reserve(nbSpans);
		for (size_t i = 0; i < nbSpans; i++)
		{
			Debug_Bad_Index(i, 0, pts.size() - 1);
			Q.push_back(pts[i]);
		}
		Qs.push_back(std::move(Q));
	}
	auto gFace = PtdModel_Face::CreateFace(Qs);
	theFace_ = std::make_shared<ptdModel::BladeFace_Press>(std::move(gFace));

	if (verbose)
	{
		Info << endl
			<< " retrieving the back offsets..." << endl;
	}
	std::vector<std::vector<Pnt3d>> Qs1;
	Qs1.reserve(nbSections);
	for (size_t section = 0; section < nbSections; section++)
	{
		if (verbose > 1)
		{
			Info << endl
				<< " - section nb. " << section << endl;
		}
		Debug_Bad_Index(section, 0, wrappedSections.size() - 1);
		const auto& wrappedSection = wrappedSections[section];

		const auto& pts = wrappedSection->Back();

		if (verbose > 1)
		{
			Info << endl
				<< " - back offsets: " << endl;
			for (const auto& x : pts)
			{
				Info << " - " << x << endl;
			}
			Info << endl;
		}
		std::vector<Pnt3d> Q;
		Q.reserve(nbSpans);
		for (size_t i = 0; i < nbSpans; i++)
		{
			Debug_Bad_Index(i, 0, pts.size() - 1);
			Q.push_back(pts[i]);
		}
		Qs1.push_back(std::move(Q));
	}

	auto gBack = PtdModel_Face::CreateFace(Qs1);
	theBack_ = std::make_shared<ptdModel::BladeFace_Suct>(std::move(gBack));

	if (verbose)
	{
		Info << endl
			<< "*********** End of the Creating Faces ************" << endl;
	}
}

void tnbLib::PtdModel_PropBlade::Perform()
{
	if (NOT BladeInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "no blade info has been found!" << endl
			<< abort(FatalError);
	}

	if (NOT BladeInfo()->BladeForm())
	{
		FatalErrorIn(FunctionSIG)
			<< "no blade form has been created!" << endl
			<< "- please make sure the form maker has been imported." << endl
			<< abort(FatalError);
	}

	CalcXParameters();

	CalcBladeView();

	CreateFaces();

	Change_IsDone() = Standard_True;
}

void tnbLib::PtdModel_PropBlade::SetxDistb
(
	const std::shared_ptr<Geo_xDistb>& theDistb
)
{
	theDistb_ = theDistb;
}

void tnbLib::PtdModel_PropBlade::SetxDistb
(
	std::shared_ptr<Geo_xDistb>&& theDistb
)
{
	theDistb_ = std::move(theDistb);
}

void tnbLib::PtdModel_PropBlade::SetSection
(
	const std::shared_ptr<PtdModel_PropSection>& theSection
)
{
	theSection_ = theSection;
}

void tnbLib::PtdModel_PropBlade::SetSection
(
	std::shared_ptr<PtdModel_PropSection>&& theSection
)
{
	theSection_ = std::move(theSection);
}

void tnbLib::PtdModel_PropBlade::ImportMakers
(
	const std::vector<std::shared_ptr<PtdModel_FormMaker>>& theMakers
)
{
	if (NOT BladeInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "no info has been found!" << endl
			<< abort(FatalError);
	}

	const auto& globalPars = BladeInfo()->Globals();
	if (NOT globalPars)
	{
		FatalErrorIn(FunctionSIG)
			<< "no global parameters has been found!" << endl
			<< abort(FatalError);
	}

	auto bladeForm = std::make_shared<PtdModel_Forms>();
	Debug_Null_Pointer(bladeForm);

	auto bladeProfiles = std::make_shared<PtdModel_Profiles>();
	Debug_Null_Pointer(bladeProfiles);

	for (const auto& maker : theMakers)
	{
		Debug_Null_Pointer(maker);

		auto form = maker->CreateForm();
		Debug_Null_Pointer(form);

		auto profile = maker->CreateProfile(globalPars, form);
		Debug_Null_Pointer(profile);

		bladeForm->Import(std::move(form));
		bladeProfiles->Import(std::move(profile));
	}

	BladeInfo()->SetBladeForm(std::move(bladeForm));
	theProfiles_ = std::move(bladeProfiles);
}

