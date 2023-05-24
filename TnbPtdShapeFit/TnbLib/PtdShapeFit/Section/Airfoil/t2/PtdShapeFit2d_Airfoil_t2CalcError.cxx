#include <PtdShapeFit2d_Airfoil_t2.hxx>

#include <PtdShapeFit2d_ScatterMap.hxx>
#include <Cad2d_Plane.hxx>
#include <Pln_Wire.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Real 
tnbLib::airfoilLib::Type2::CalcError
(
	const std::vector<Standard_Real>& xs,
	const std::shared_ptr<PtdShapeFit2d_ScatterMap>& theMap
) const
{
	std::shared_ptr<Cad2d_Plane> shape;
	try
	{
		shape = RetrieveShape(xs);
	}
	catch (...)
	{
		return 1.0E20; // really big cost [4/30/2023 Payvand]
	}
	auto pairedList = theMap->RetrieveCurves(shape);

	//std::cout << "size= " << pairedList.size() << std::endl;
	Standard_Real sum = 0;
	for (const auto& paired : pairedList)
	{
		auto [curve, pnts] = paired;
		for (const auto& x : *pnts)
		{
			try
			{
				auto dis = PtdShapeFit_Section::CalcDistance(x, *curve);
				auto d2 = dis * dis;
				sum += d2;
			}
			catch (const Standard_Failure& ms)
			{
				if (verbose)
				{
					Info << ms.GetMessageString() << endl;
				}
			}
		}
	}
	return sum;
}