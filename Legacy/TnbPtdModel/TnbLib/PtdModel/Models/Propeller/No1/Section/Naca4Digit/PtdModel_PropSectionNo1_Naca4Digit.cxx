#include <PtdModel_PropSectionNo1_Naca4Digit.hxx>

#include <PtdModel_BladeInfo.hxx>
#include <PtdModel_BladeFormMakersNo1.hxx>
#include <PtdModel_BladeSectionQ.hxx>
#include <PtdModel_PropBlade.hxx>
#include <PtdModel_xPars.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <TecPlot.hxx>

namespace tnbLib
{
	//OFstream exportNacaFile(fileName("section.plt"));
}

std::shared_ptr<tnbLib::PtdModel_BladeSectionQ> 
tnbLib::ptdModel::PropSectionNo1_Naca4Digit::SectionQ
(
	const Standard_Integer section, 
	const PtdModel_PropBlade & theBlade
) const
{
	if (verbose)
	{
		Info << endl
			<< "************ Calculating section offsets ************" << endl;
	}
	const auto& bladeInfo = BladeInfo(theBlade);
	if (NOT bladeInfo)
	{
		FatalErrorIn(FunctionSIG)
			<< "no blade info has been found!" << endl
			<< abort(FatalError);
	}
	const auto nbSpans = bladeInfo->NbSpans();

	if (verbose)
	{
		Info << endl
			<< " - nb. of spans: " << nbSpans << endl;
	}
	if (nbSpans < 10)
	{
		FatalErrorIn(FunctionSIG)
			<< "Not enough nb. of spans has been detected!" << endl
			<< " nb. of spans: " << nbSpans << endl
			<< abort(FatalError);
	}

	const auto& xpars = xParameters(theBlade);
	if (NOT xpars)
	{
		FatalErrorIn(FunctionSIG)
			<< "no x-parameters has been found!" << endl
			<< abort(FatalError);
	}

	const auto chordList = xpars->SelectParameter(ptdModel::BladeFormNo1_Chord::TypeName_);
	const auto camberList = xpars->SelectParameter(ptdModel::BladeFormNo1_Camber::TypeName_);
	const auto camberMaxLocList = xpars->SelectParameter(ptdModel::BladeFormNo1_CamberLoc::TypeName_);
	const auto thickList = xpars->SelectParameter(ptdModel::BladeFormNo1_Thickness::TypeName_);

	const auto dx = M_PI / (Standard_Real)(nbSpans - 1);

	std::vector<Standard_Real> xs;
	xs.reserve(nbSpans);
	for (size_t i = 0; i < nbSpans - 1; i++)
	{
		xs.push_back(0.5*(1.0 - std::cos(i*dx)));
	}
	xs.push_back(1.0 - TrailEdgeGap());

	if (verbose > 1)
	{
		Info << " - xs: {" << endl;
		for (auto x : xs)
		{
			Info << " - " << x << endl;
		}
		Info << "}" << endl;
	}

	const auto xChord = (*chordList)[section];
	const auto xCamber = (*camberList)[section];
	const auto xCamberLoc = (*camberMaxLocList)[section];
	const auto xCamberLoc2 = xCamberLoc * xCamberLoc;
	const auto oneMinusxCamberLoc2 = (1.0 - xCamberLoc)*(1.0 - xCamberLoc);
	const auto xThick = (*thickList)[section] / 0.2;

	if (verbose > 1)
	{
		Info << endl;
		Info << " - chord: " << xChord 
			<< ", camber: " << xCamber 
			<< ", camberLoc: " << xCamberLoc 
			<< ", thick: " << xThick << endl;
		Info << endl;
	}

	Standard_Real yc, ypc;

	std::vector<Pnt2d> Tb, Tf;
	Tb.reserve(nbSpans);
	Tf.reserve(nbSpans);

	if (verbose)
	{
		Info << endl
			<< " - xCamberLoc: " << xCamberLoc << endl;
	}

	for (size_t i = 0; i < nbSpans; i++)
	{
		if (xs[i] <= xCamberLoc)
		{
			yc = xCamber * (2.0*xCamberLoc*xs[i] - xs[i] * xs[i]) / xCamberLoc2;
			ypc = xCamber * (2.0*xCamberLoc - 2.0*xs[i]) / xCamberLoc2;
		}
		else
		{
			yc = xCamber * ((1.0 - 2.0*xCamberLoc) + 2.0*xCamberLoc*xs[i] - xs[i] * xs[i]) / oneMinusxCamberLoc2;
			ypc = xCamber * (2.0*xCamberLoc - 2.0*xs[i]) / oneMinusxCamberLoc2;
		}

		auto x = xs[i];
		auto yt = xThick * (0.2969*std::sqrt(x) + x * (-0.126 + x * (-0.3516 + x * (0.2843 - 0.1015*x))));

		auto angle = std::atan(ypc);

		Pnt2d TbP(x*xChord - yt * std::sin(angle), -yc - yt * std::cos(angle));
		Pnt2d TfP(x*xChord + yt * std::sin(angle), -yc + yt * std::cos(angle));
		
		Tb.push_back(std::move(TbP));
		Tf.push_back(std::move(TfP));
	}

	if (verbose > 1)
	{
		Info << endl;
		Info << " - Tb: {" << endl;
		for (const auto& x : Tb)
		{
			Info << " - " << x << endl;
		}
		Info << "}" << endl;

		Info << endl;
		Info << " - Tf: {" << endl;
		for (const auto& x : Tf)
		{
			Info << " - " << x << endl;
		}
		Info << "}" << endl;
	}


	//Io::ExportCurve(Tb, exportNacaFile);
	//Io::ExportCurve(Tf, exportNacaFile);
	auto Q = std::make_shared<PtdModel_BladeSectionQ>(std::move(Tb), std::move(Tf));

	if (verbose)
	{
		Info << endl
			<< "************ Enf of the Calculating section offsets ************" << endl;
	}
	return std::move(Q);
}