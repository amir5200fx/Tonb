#include <Entity3d_TriVolume.hxx>

#include <Entity3d_TriShell.hxx>

void tnbLib::Entity3d_TriVolume::ExportToPlt(OFstream& theFile) const
{
	theOuter_->ExportToPlt(theFile);
	if (theInners_)
	{
		for (const auto& x: *theInners_)
		{
			x->ExportToPlt(theFile);
		}
	}
}