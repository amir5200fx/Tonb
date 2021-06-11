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

	theBladeInfo_ = std::move(bladeInfo);
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

	std::vector<std::shared_ptr<PtdModel_BladeExpandedView>> expandedViews;
	expandedViews.reserve(NbSections());
	for (Standard_Integer section = 0; section < NbSections(); section++)
	{
		auto sectionQ = Section()->SectionQ(section, *this);
		Debug_Null_Pointer(sectionQ);

		auto expandedView = CreateExpandView(*sectionQ);
		expandedViews.push_back(std::move(expandedView));
	}

	auto unWrappedView = CreateUnWrappedView();
	auto wrappedView = CreateWrappedView();

	bladeView->SetExpandedViews(std::move(expandedViews));
	bladeView->SetUnWrappedSections(std::move(unWrappedView));
	bladeView->SetWrappedSections(std::move(wrappedView));

	theBladeView_ = std::move(bladeView);
}

void tnbLib::PtdModel_PropBlade::CreateFaces()
{
	if (NOT BladeInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "no info has been found!" << endl
			<< abort(FatalError);
	}

	const auto nbSections = BladeInfo()->NbSections();
	const auto nbSpans = BladeInfo()->NbSpans();

	const auto& wrappedSections = BladeView()->WrappedSections();

	std::vector<std::vector<Pnt3d>> Qs;
	Qs.reserve(nbSections);
	for (size_t section = 0; section < nbSections; section++)
	{
		Debug_Bad_Index(section, 0, wrappedSections.size() - 1);
		const auto& wrappedSection = wrappedSections[section];

		const auto& pts = wrappedSection->Face();

		auto& Q = Qs[section];
		Q.reserve(nbSpans);
		for (size_t i = 0; i < nbSpans; i++)
		{
			Debug_Bad_Index(i, 0, pts.size() - 1);
			Q.push_back(pts[i]);
		}
	}

	theFace_ = PtdModel_Face::CreateFace(Qs);

	for (size_t section = 0; section < nbSections; section++)
	{
		Debug_Bad_Index(section, 0, wrappedSections.size() - 1);
		const auto& wrappedSection = wrappedSections[section];

		const auto& pts = wrappedSection->Back();

		auto& Q = Qs[section];
		for (size_t i = 0; i < nbSpans; i++)
		{
			Debug_Bad_Index(i, 0, pts.size() - 1);
			Q.push_back(pts[i]);
		}
	}

	theBack_ = PtdModel_Face::CreateFace(Qs);
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

