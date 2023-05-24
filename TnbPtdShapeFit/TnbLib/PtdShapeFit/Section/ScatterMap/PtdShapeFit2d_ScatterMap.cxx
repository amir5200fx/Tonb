#include <PtdShapeFit2d_ScatterMap.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

const std::string tnbLib::PtdShapeFit2d_ScatterMap::extension = ".pshapfitscatmap";

std::vector<std::pair<std::shared_ptr<tnbLib::Pln_Curve>, std::shared_ptr<typename tnbLib::PtdShapeFit2d_ScatterMap::ptList>>>
tnbLib::PtdShapeFit2d_ScatterMap::RetrieveCurves(const std::shared_ptr<Cad2d_Plane>&) const
{
	FatalErrorIn(FunctionSIG)
		<< "This is not supposed to be ccalled." << endl
		<< abort(FatalError);
	return std::vector<std::pair<std::shared_ptr<tnbLib::Pln_Curve>, std::shared_ptr<typename tnbLib::PtdShapeFit2d_ScatterMap::ptList>>>();
}