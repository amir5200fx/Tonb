#pragma once
#include <MeshPost_LaplacianSmoothing_AvgFun.hxx>
#include <MeshPost_LaplacianSmoothing_Info.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Standard_Real.hxx>

template<class MetricMap>
inline Standard_Real 
tnbLib::MeshPost_LaplacianSmoothing<MetricMap>::CalcWorstQuality
(
	const nodeType & theNode
) const
{
	Debug_Null_Pointer(QualityFun());
	auto worstQ = RealLast();
	for (const auto& x : theNode.RetrieveElements())
	{
		auto element = x.second.lock();
		Debug_Null_Pointer(element);

		auto quality = QualityFun()->CalcQuality(*element);
		if (quality < worstQ) worstQ = quality;
	}
	return worstQ;
}

template<class MetricMap>
inline void tnbLib::MeshPost_LaplacianSmoothing<MetricMap>::Perform()
{
	if (NOT AlgInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "no info has been loaded." << endl
			<< abort(FatalError);
	}
	if (NOT AvgFun())
	{
		FatalErrorIn(FunctionSIG)
			<< "no Avg. function has been loaded." << endl
			<< abort(FatalError);
	}
	if (NOT QualityFun())
	{
		FatalErrorIn(FunctionSIG)
			<< "no quality function has been loaded." << endl
			<< abort(FatalError);
	}
	if (NOT Nodes())
	{
		FatalErrorIn(FunctionSIG)
			<< "no node array has been loaded." << endl
			<< abort(FatalError);
	}
	if (verbose)
	{
		Info << " Laplacian smoothing has been started." << endl;
		Info << " - Nb. of levels: " << AlgInfo()->NbLevels() << ", Relaxation: " << AlgInfo()->UnderRelaxation() << endl;
		Info << endl;
	}

	const auto nbLevels = AlgInfo()->NbLevels();
	const auto ur = AlgInfo()->UnderRelaxation();

	for (size_t iter = 1; iter <= nbLevels; iter++)
	{
		if (verbose)
		{
			Info << " - Iter. nb. " << iter << endl;
		}
		for (const auto& x : *Nodes())
		{
			Debug_Null_Pointer(x);
			if (x->IsBoundary()) continue;

			auto worstQuality = CalcWorstQuality(*x);
			auto p0 = x->Coord();

			auto newCoord = AvgFun()->CalcAverage(x);
			x->SetCoord(p0 + ur * (newCoord - p0));

			if (CalcWorstQuality(*x) < worstQuality)
			{
				x->SetCoord(p0);
			}
		}
	}
	Change_IsDone() = Standard_True;
}