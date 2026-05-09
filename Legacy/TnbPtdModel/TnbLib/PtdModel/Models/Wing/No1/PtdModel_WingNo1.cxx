#include <PtdModel_WingNo1.hxx>

#include <PtdModel_xPars.hxx>
#include <PtdModel_WingView.hxx>
#include <PtdModel_WingExpandedView.hxx>
#include <PtdModel_WingFormMakersNo1.hxx>
#include <PtdModel_WrappedWingSection.hxx>
#include <PtdModel_WingSectionQ.hxx>

std::shared_ptr<tnbLib::PtdModel_WingExpandedView> 
tnbLib::PtdModel_WingNo1::CreateExpandView(const Standard_Integer section, const PtdModel_WingSectionQ & theQ) const
{
	const auto& xPars = xParameters();
	if (NOT xPars)
	{
		FatalErrorIn(FunctionSIG)
			<< "no xParameters has been found!" << endl
			<< abort(FatalError);
	}

	const auto xChord = xPars->SelectParameter(ptdModel::WingFormNo1_Chord::TypeName_);
	const auto& xChordRef = *xChord;

	auto t = std::make_shared<PtdModel_WingExpandedView>();

	std::vector<Standard_Real> x;
	std::vector<Standard_Real> tb, tf, yb, yf;

	const auto& Qf = theQ.Upper().Points;
	const auto& Qb = theQ.Lower().Points;
	const auto n = Qf.size();
	x.reserve(n);
	tb.reserve(n);
	tf.reserve(n);
	yb.reserve(n);
	yf.reserve(n);


	for (size_t i = 0; i < Qf.size(); i++)
	{
		x.push_back(0.5*xChordRef[section] - Qf[i].X());

		tb.push_back(Qb[i].Y());
		tf.push_back(Qf[i].Y());

		yb.push_back(Qb[i].Y() + xPars->Xs()[section]);
		yf.push_back(Qf[i].Y() + xPars->Xs()[section]);
	}

	t->SetX(std::move(x));

	t->SetTb(std::move(tb));
	t->SetTf(std::move(tf));

	t->SetYb(std::move(yb));
	t->SetYf(std::move(yf));
	return std::move(t);
}

std::vector<std::shared_ptr<tnbLib::PtdModel_WrappedWingSection>> 
tnbLib::PtdModel_WingNo1::CreateWrappedView() const
{
	if (NOT xParameters())
	{
		FatalErrorIn(FunctionSIG)
			<< "no xParameters has been found!" << endl
			<< abort(FatalError);
	}

	const auto& X = xParameters()->Xs();
	const auto xChord = xParameters()->SelectParameter(ptdModel::WingFormNo1_Chord::TypeName_);
	const auto& xChordRef = *xChord;

	const auto& expandedViews = WingView()->ExpandedViews();
	if (expandedViews.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "no expanded view has been found!" << endl
			<< abort(FatalError);
	}

	const auto nbSpans = expandedViews[0]->NbSpans();

	Debug_If_Condition(NOT xParameters()->NbSections());
	std::vector<std::shared_ptr<PtdModel_WrappedWingSection>> bladeSections;
	bladeSections.reserve(xParameters()->NbSections());

	for (size_t section = 0; section < xParameters()->NbSections(); section++)
	{
		auto xchord = xChordRef[section];

		auto t = std::make_shared<PtdModel_WrappedWingSection>();
		Debug_Null_Pointer(t);

		std::vector<Pnt3d> face;
		std::vector<Pnt3d> back;

		face.reserve(nbSpans);
		back.reserve(nbSpans);


		const auto& expandedView = expandedViews[section];

		const auto& Xs = expandedView->X();
		const auto& Tb = expandedView->Tb();
		const auto& Tf = expandedView->Tf();

		for (size_t i = 0; i < nbSpans; i++)
		{
			auto xs = Xs[i];
			auto tb = Tb[i];
			auto tf = Tf[i];

			Pnt3d ptBack
			(
				xs,
				X[section],
				tb
			);
			Pnt3d ptFace
			(
				xs,
				X[section],
				tf
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