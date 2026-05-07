#include <VoyageWP_PointDistb.hxx>

#include <VoyageWP_Offset.hxx>
#include <Entity2d_Polygon.hxx>
#include <TecPlot.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::VoyageWP_PointDistb::ExportToPlt(OFstream& theFile) const
{
	if (NOT IsDone())
	{
		FatalErrorIn(FunctionSIG)
			<< "the application is not performed." << endl
			<< abort(FatalError);
	}
	std::vector<Pnt2d> coords;
	for (const auto& x : theNodes_)
	{
		Debug_Null_Pointer(x);
		if (x->IsInterior())
		{
			auto node = std::dynamic_pointer_cast<InterNode>(x);
			Debug_Null_Pointer(node);
			{
				const auto& poly = node->Starboard()->Offsets();
				Debug_Null_Pointer(poly);
				for (const auto& p : poly->Points())
				{
					coords.emplace_back(p);
				}
			}
			{
				const auto& poly = node->Port()->Offsets();
				Debug_Null_Pointer(poly);
				for (const auto& p : poly->Points())
				{
					coords.emplace_back(p);
				}
			}
		}
		else
		{
			coords.emplace_back(x->Coord());
		}
	}
	Io::ExportPoints(coords, theFile);
	Debug_Null_Pointer(Offsets());
	Offsets()->ExportToPlt(theFile);
}