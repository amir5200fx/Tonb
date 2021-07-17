#include <BoundarySizeMap2d_SegmentTool.hxx>

void tnbLib::BoundarySizeMap2d_SegmentTool::CreateSizeMap(const std::vector<std::shared_ptr<Pln_Edge>>& theEdges)
{
	if (theEdges.empty())
	{
		return;
	}

	//! Retrieve sizes
	Standard_Real elemSize, minElemSize, spanAngle;
	RetrieveValues(elemSize, minElemSize, spanAngle);

	if (verbose)
	{
		Info << " - Target element size: " << elemSize << endl;
		Info << " - Min. element size: " << minElemSize << endl;
		Info << " - Span size angle: " << spanAngle << endl;
		Info << endl;
	}


}