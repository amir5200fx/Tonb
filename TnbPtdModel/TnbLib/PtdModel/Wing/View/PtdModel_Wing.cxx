#include <PtdModel_Wing.hxx>

#include <Geo_CosineDistb.hxx>
#include <PtdModel_Face.hxx>
#include <PtdModel_xPars.hxx>
#include <PtdModel_Profile.hxx>
#include <PtdModel_Profiles.hxx>
#include <PtdModel_FormMaker.hxx>
#include <PtdModel_WingGlobalPars.hxx>
#include <PtdModel_Forms.hxx>
#include <PtdModel_WingSection.hxx>
#include <PtdModel_WingView.hxx>
#include <PtdModel_WingInfo.hxx>
#include <PtdModel_WingExpandedView.hxx>
#include <PtdModel_WrappedWingSection.hxx>


void tnbLib::PtdModel_Wing::CalcXParameters()
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

void tnbLib::PtdModel_Wing::CalcWingView()
{
	if (NOT Section())
	{
		FatalErrorIn(FunctionSIG)
			<< "no section has been loaded!" << endl
			<< abort(FatalError);
	}

	auto wingView = std::make_shared<PtdModel_WingView>();
	Debug_Null_Pointer(wingView);

	theWingView_ = wingView;

	std::vector<std::shared_ptr<PtdModel_WingExpandedView>> expandedViews;
	expandedViews.reserve(NbSections());

	for (Standard_Integer section = 0; section < NbSections(); section++)
	{
		auto sectionQ = Section()->SectionQ(section, *this);
		Debug_Null_Pointer(sectionQ);

		auto expandedView = CreateExpandView(section, *sectionQ);
		expandedViews.push_back(std::move(expandedView));
	}

	wingView->SetExpandedViews(std::move(expandedViews));

	auto wrappedView = CreateWrappedView();

	wingView->SetWrappedSections(std::move(wrappedView));
}

void tnbLib::PtdModel_Wing::CreateFaces()
{
	if (NOT WingInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "no info has been found!" << endl
			<< abort(FatalError);
	}

	const auto nbSections = WingInfo()->NbSections();
	const auto nbSpans = WingInfo()->NbSpans();

	const auto& wrappedSections = WingView()->WrappedSections();

	std::vector<std::vector<Pnt3d>> Qs;
	Qs.reserve(nbSections);
	for (size_t section = 0; section < nbSections; section++)
	{
		Debug_Bad_Index(section, 0, wrappedSections.size() - 1);
		const auto& wrappedSection = wrappedSections[section];

		const auto& pts = wrappedSection->Face();

		std::vector<Pnt3d> Q;
		Q.reserve(nbSpans);
		for (size_t i = 0; i < nbSpans; i++)
		{
			Debug_Bad_Index(i, 0, pts.size() - 1);
			Q.push_back(pts[i]);
		}
		Qs.push_back(std::move(Q));
	}

	theLower_ = PtdModel_Face::CreateFace(Qs);

	std::vector<std::vector<Pnt3d>> Qs1;
	Qs1.reserve(nbSections);
	for (size_t section = 0; section < nbSections; section++)
	{
		Debug_Bad_Index(section, 0, wrappedSections.size() - 1);
		const auto& wrappedSection = wrappedSections[section];

		const auto& pts = wrappedSection->Back();

		std::vector<Pnt3d> Q;
		Q.reserve(nbSpans);
		for (size_t i = 0; i < nbSpans; i++)
		{
			Debug_Bad_Index(i, 0, pts.size() - 1);
			Q.push_back(pts[i]);
		}
		Qs1.push_back(std::move(Q));
	}

	theUpper_ = PtdModel_Face::CreateFace(Qs1);
}

namespace tnbLib
{
	const Standard_Integer PtdModel_Wing::DEFAULT_NB_SECTIONS = 10;
	const Standard_Integer PtdModel_Wing::DEFAULT_NB_SPANS = 25;
}

tnbLib::PtdModel_Wing::PtdModel_Wing
(
	const std::shared_ptr<PtdModel_WingGlobalPars>& pars
)
{
	auto wingInfo = std::make_shared<PtdModel_WingInfo>();
	Debug_Null_Pointer(wingInfo);

	wingInfo->SetLength(pars);
	wingInfo->SetNbSections(DEFAULT_NB_SECTIONS);
	wingInfo->SetNbSpans(DEFAULT_NB_SPANS);

	theWingInfo_ = std::move(wingInfo);
}

Standard_Integer
tnbLib::PtdModel_Wing::NbSections() const
{
	if (NOT xDistb())
	{
		FatalErrorIn(FunctionSIG)
			<< "no spacing has been loaded!" << endl
			<< abort(FatalError);
	}
	return xDistb()->Size();
}

void tnbLib::PtdModel_Wing::Perform()
{
	if (NOT WingInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "no blade info has been found!" << endl
			<< abort(FatalError);
	}

	if (NOT WingInfo()->Forms())
	{
		FatalErrorIn(FunctionSIG)
			<< "no blade form has been created!" << endl
			<< "- please make sure the form maker has been imported." << endl
			<< abort(FatalError);
	}

	CalcXParameters();

	CalcWingView();

	CreateFaces();

	Change_IsDone() = Standard_True;
}

void tnbLib::PtdModel_Wing::SetxDistb(const std::shared_ptr<Geo_xDistb>& d)
{
	theDistb_ = d;
	theWingInfo_->SetNbSections(theDistb_->Size());
}

void tnbLib::PtdModel_Wing::SetxDistb(std::shared_ptr<Geo_xDistb>&& d)
{
	theDistb_ = std::move(d);
	theWingInfo_->SetNbSections(theDistb_->Size());
}

void tnbLib::PtdModel_Wing::SetSection(const std::shared_ptr<PtdModel_WingSection>& sect)
{
	theSection_ = sect;
}

void tnbLib::PtdModel_Wing::SetSection(std::shared_ptr<PtdModel_WingSection>&& sect)
{
	theSection_ = std::move(sect);
}


void tnbLib::PtdModel_Wing::ImportMakers
(
	const std::vector<std::shared_ptr<PtdModel_FormMaker>>& theMakers
)
{
	if (NOT WingInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "no info has been found!" << endl
			<< abort(FatalError);
	}

	const auto& globalPars = WingInfo()->Globals();
	if (NOT globalPars)
	{
		FatalErrorIn(FunctionSIG)
			<< "no global parameters has been found!" << endl
			<< abort(FatalError);
	}

	auto wingForm = std::make_shared<PtdModel_Forms>();
	Debug_Null_Pointer(wingForm);

	auto bladeProfiles = std::make_shared<PtdModel_Profiles>();
	Debug_Null_Pointer(bladeProfiles);

	for (const auto& maker : theMakers)
	{
		Debug_Null_Pointer(maker);

		auto form = maker->CreateForm();
		Debug_Null_Pointer(form);

		auto profile = maker->CreateProfile(globalPars, form);
		Debug_Null_Pointer(profile);

		wingForm->Import(std::move(form));
		bladeProfiles->Import(std::move(profile));
	}

	WingInfo()->SetForms(std::move(wingForm));
	theProfiles_ = std::move(bladeProfiles);
}

std::shared_ptr<tnbLib::ptdModel::io::Wing> 
tnbLib::PtdModel_Wing::MakeIO() const
{
	auto obj = std::make_shared<ptdModel::io::Wing>();
	obj->SetLower(LowerPatch());
	obj->SetUpper(UpperPatch());

	return std::move(obj);
}