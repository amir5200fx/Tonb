#include <PtdModel_PropBladeNo1.hxx>

#include <PtdModel_Face.hxx>
#include <PtdModel_BladeInfo.hxx>
#include <PtdModel_BladeSectionQ.hxx>
#include <PtdModel_BladeView.hxx>
#include <PtdModel_BladeExpandedView.hxx>
#include <PtdModel_BladeFormMakersNo1.hxx>
#include <PtdModel_WrappedBladeSection.hxx>
#include <PtdModel_UnWrappedBladeSection.hxx>
#include <PtdModel_xPars.hxx>

std::shared_ptr<tnbLib::PtdModel_BladeExpandedView> 
tnbLib::PtdModel_PropBladeNo1::CreateExpandView
(
	const PtdModel_BladeSectionQ& theQ
) const
{
	const auto& xPars = xParameters();
	if (NOT xPars)
	{
		FatalErrorIn(FunctionSIG)
			<< "no xParameters has been found!" << endl
			<< abort(FatalError);
	}

	const auto xChord = xPars->SelectParameter(ptdModel::BladeFormNo1_Chord::TypeName_);
	const auto xSkew = xPars->SelectParameter(ptdModel::BladeFormNo1_Skew::TypeName_);

	const auto& xChordRef = *xChord;
	const auto& xSkewRef = *xSkew;

	auto t = std::make_shared<PtdModel_BladeExpandedView>();

	std::vector<Standard_Real> x;
	std::vector<Standard_Real> xs;
	std::vector<Standard_Real> tb, tf, yb, yf;

	const auto& Qf = theQ.Face();
	const auto& Qb = theQ.Back();
	const auto n = Qf.size();
	x.reserve(n);
	xs.reserve(n);
	tb.reserve(n);
	tf.reserve(n);
	yb.reserve(n);
	yf.reserve(n);


	for (size_t i = 0; i < Qf.size(); i++)
	{
		x.push_back(0.5*xChordRef[i] - (Qf[i].X() + xSkewRef[i]));
		xs.push_back(0.5*xChordRef[i] - Qf[i].X());

		tb.push_back(Qb[i].Y());
		tf.push_back(Qf[i].Y());

		yb.push_back(Qb[i].Y() + xPars->Xs()[i]);
		yf.push_back(Qf[i].Y() + xPars->Xs()[i]);
	}

	t->SetX(std::move(x));
	t->SetXs(std::move(xs));

	t->SetTb(std::move(tb));
	t->SetTf(std::move(tf));

	t->SetYb(std::move(yb));
	t->SetYf(std::move(yf));
	return std::move(t);
}

std::vector<std::shared_ptr<tnbLib::PtdModel_UnWrappedBladeSection>>
tnbLib::PtdModel_PropBladeNo1::CreateUnWrappedView() const
{
	if (NOT xParameters())
	{
		FatalErrorIn(FunctionSIG)
			<< "no xParameters has been found!" << endl
			<< abort(FatalError);
	}

	const auto& X = xParameters()->Xs();

	const auto xSkew = xParameters()->SelectParameter(ptdModel::BladeFormNo1_Skew::TypeName_);
	const auto xRake = xParameters()->SelectParameter(ptdModel::BladeFormNo1_Rake::TypeName_);
	const auto xPitch = xParameters()->SelectParameter(ptdModel::BladeFormNo1_Pitch::TypeName_);
	const auto xChord = xParameters()->SelectParameter(ptdModel::BladeFormNo1_Chord::TypeName_);

	const auto& xSkewRef = *xSkew;
	const auto& xRakeRef = *xRake;
	const auto& xPitchRef = *xPitch;
	const auto& xChordRef = *xChord;

	const auto& expandedViews = BladeView()->ExpandedViews();
	if (expandedViews.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "no expanded view has been found!" << endl
			<< abort(FatalError);
	}

	const auto nbSpans = expandedViews[0]->NbSpans();

	Debug_If_Condition(NOT xParameters()->NbSections());
	std::vector<std::shared_ptr<PtdModel_UnWrappedBladeSection>> bladeSections;
	bladeSections.reserve(xParameters()->NbSections());

	for (size_t section = 0; section < xParameters()->NbSections(); section++)
	{
		auto sk = xSkewRef[section];
		auto rk = xRakeRef[section];
		auto xpitch = xPitchRef[section];
		auto xchord = xChordRef[section];

		auto t = std::make_shared<PtdModel_UnWrappedBladeSection>();
		Debug_Null_Pointer(t);

		std::vector<Pnt3d> face;
		std::vector<Pnt3d> back;

		face.reserve(nbSpans);
		back.reserve(nbSpans);

		
		const auto& expandedView = expandedViews[section];
		
		const auto& Xs = expandedView->Xs();
		const auto& Tb = expandedView->Tb();
		const auto& Tf = expandedView->Tf();

		auto cosPitch = std::cos(xpitch);
		auto sinPitch = std::sin(xpitch);

		for (size_t i = 0; i < nbSpans; i++)
		{
			auto xs = Xs[i];
			auto tb = Tb[i];
			auto tf = Tf[i];
			
			Pnt3d ptBack
			(
				sk*cosPitch + xs * cosPitch - tb * sinPitch,
				X[section],
				sk*sinPitch + rk - xs * sinPitch - tb * cosPitch
			);
			Pnt3d ptFace
			(
				sk*cosPitch + xs * cosPitch - tf * sinPitch,
				X[section],
				sk*sinPitch + rk - xs * sinPitch - tf * cosPitch
			);

			back.push_back(std::move(ptBack));
			face.push_back(std::move(ptFace));
		}

		t->SetBack(std::move(back));
		t->SetFace(std::move(face));

		bladeSections.push_back(std::move(t));
	}
	return std::move(bladeSections);
}

std::vector<std::shared_ptr<tnbLib::PtdModel_WrappedBladeSection>>
tnbLib::PtdModel_PropBladeNo1::CreateWrappedView() const
{
	if (NOT xParameters())
	{
		FatalErrorIn(FunctionSIG)
			<< "no xParameters has been found!" << endl
			<< abort(FatalError);
	}

	Debug_If_Condition(NOT xParameters()->NbSections());
	const auto nbSections = xParameters()->NbSections();

	const auto& X = xParameters()->Xs();

	const auto xSkew = xParameters()->SelectParameter(ptdModel::BladeFormNo1_Skew::TypeName_);
	const auto xRake = xParameters()->SelectParameter(ptdModel::BladeFormNo1_Rake::TypeName_);
	const auto xPitch = xParameters()->SelectParameter(ptdModel::BladeFormNo1_Pitch::TypeName_);
	const auto xChord = xParameters()->SelectParameter(ptdModel::BladeFormNo1_Chord::TypeName_);

	const auto& xSkewRef = *xSkew;
	const auto& xRakeRef = *xRake;
	const auto& xPitchRef = *xPitch;
	const auto& xChordRef = *xChord;

	const auto& expandedViews = BladeView()->ExpandedViews();
	if (expandedViews.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "no expanded view has been found!" << endl
			<< abort(FatalError);
	}

	const auto nbSpans = expandedViews[0]->NbSpans();

	Debug_If_Condition(NOT xParameters()->NbSections());
	std::vector<std::shared_ptr<PtdModel_WrappedBladeSection>> bladeSections;
	bladeSections.reserve(xParameters()->NbSections());

	for (size_t section = 0; section < nbSections; section++)
	{
		auto sk = xSkewRef[section];
		auto rk = xRakeRef[section];
		auto xpitch = xPitchRef[section];
		auto xchord = xChordRef[section];

		auto t = std::make_shared<PtdModel_WrappedBladeSection>();
		Debug_Null_Pointer(t);

		auto cosPitch = std::cos(xpitch);
		auto sinPitch = std::sin(xpitch);

		const auto& expandedView = expandedViews[section];

		const auto& Xs = expandedView->Xs();
		const auto& Tb = expandedView->Tb();
		const auto& Tf = expandedView->Tf();

		std::vector<Pnt3d> face;
		std::vector<Pnt3d> back;

		face.reserve(nbSpans);
		back.reserve(nbSpans);

		for (size_t i = 0; i < nbSpans; i++)
		{
			auto xs = Xs[i];
			auto tb = Tb[i];
			auto tf = Tf[i];

			auto omegab = -(-sk * cosPitch + xs * cosPitch + tb * sinPitch) / X[section];
			auto omegaf = -(-sk * cosPitch + xs * cosPitch + tf * sinPitch) / X[section];

			auto cosOmegab = std::cos(omegab);
			auto sinOmegab = std::sin(omegab);
			auto cosOmegaf = std::cos(omegaf);
			auto sinOmegaf = std::sin(omegaf);

			Pnt3d ptBack
			(
				X[section]*sinOmegab,
				X[section]*cosOmegab,
				sk*sinPitch + rk - xs * sinPitch - tb * cosPitch
			);
			Pnt3d ptFace
			(
				X[section]*sinOmegaf,
				X[section]*cosOmegaf,
				sk*sinPitch + rk - xs * sinPitch - tf * cosPitch
			);

			back.push_back(std::move(ptBack));
			face.push_back(std::move(ptFace));
		}

		t->SetBack(std::move(back));
		t->SetFace(std::move(face));

		bladeSections.push_back(std::move(t));
	}
	return std::move(bladeSections);
}