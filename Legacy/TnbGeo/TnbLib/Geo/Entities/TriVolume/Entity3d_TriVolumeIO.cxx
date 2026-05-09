#include <Entity3d_TriVolume.hxx>

#include <Entity3d_TriShell.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Entity3d_TriVolume)
{
	ar& this->theOuter_;
	ar& this->theInners_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Entity3d_TriVolume)
{
	ar& this->theOuter_;
	ar& this->theInners_;
}

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