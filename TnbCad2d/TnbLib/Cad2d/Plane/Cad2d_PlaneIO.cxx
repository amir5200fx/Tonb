#include <Cad2d_Plane.hxx>

#include <Pln_Wire.hxx>

void tnbLib::Cad2d_Plane::ExportToPlt
(
	OFstream & File
) const
{
	Debug_Null_Pointer(OuterWire());
	OuterWire()->ExportToPlt(File);

	if (InnerWires())
	{
		for (const auto& x : *InnerWires())
		{
			Debug_Null_Pointer(x);
			x->ExportToPlt(File);
		}
	}
}