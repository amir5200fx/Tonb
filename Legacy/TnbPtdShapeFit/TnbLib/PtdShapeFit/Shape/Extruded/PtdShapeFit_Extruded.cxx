#include <PtdShapeFit_Extruded.hxx>

#include <PtdShapeFit_Tools.hxx>
#include <PtdShapeFit_Section.hxx>
#include <Cad_Shape.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::shared_ptr<tnbLib::Cad_Shape> 
tnbLib::PtdShapeFit_Extruded::CreateShape
(
	const std::vector<std::shared_ptr<PtdShapeFit_Section::Parameters>>& theParameters,
	const std::shared_ptr<PtdShapeFit_Section>& theSection, 
	const gp_Ax1& theAxis, 
	const std::vector<Standard_Real>& theLocs
) const
{
	std::vector<std::shared_ptr<Cad2d_Plane>> planes;
	planes.reserve(theParameters.size());
	for (const auto& x : theParameters)
	{
		auto chrom = theSection->RetrieveChromosome(x);
		auto pl = theSection->RetrieveShape(chrom);

		planes.push_back(std::move(pl));
	}
	try
	{
		auto shape = PtdShapeFit_Tools::MakeExtrudedShape(planes, theAxis, theLocs);
		return std::move(shape);
	}
	catch (const Standard_Failure& x)
	{
		FatalErrorIn(FunctionSIG)
			<< x.GetMessageString() << endl
			<< abort(FatalError);
		return nullptr;
	}
}