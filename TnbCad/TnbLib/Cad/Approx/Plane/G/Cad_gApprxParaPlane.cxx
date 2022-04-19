#include <Cad_gApprxParaPlane.hxx>

#include <GModel_Plane.hxx>
#include <GModel_ParaWire.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
std::vector<std::shared_ptr<tnbLib::GModel_ParaWire>> 
tnbLib::Cad_gApprxParaPlane::RetrieveWires
(
	const std::shared_ptr<tnbLib::GModel_Plane>& thePlane
)
{
	Debug_Null_Pointer(thePlane);
	std::vector<std::shared_ptr<GModel_ParaWire>> wires;
	wires.reserve(thePlane->NbHoles() + 1);
	wires.push_back(thePlane->OuterWire());
	if (thePlane->HasHole())
	{
		for (const auto& x : *thePlane->InnerWires())
		{
			wires.push_back(x);
		}
	}
	return std::move(wires);
}