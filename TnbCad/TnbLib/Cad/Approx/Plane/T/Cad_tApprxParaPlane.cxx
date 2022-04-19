#include <Cad_tApprxParaPlane.hxx>

#include <TModel_Plane.hxx>
#include <TModel_ParaWire.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

//template<>
//std::vector<std::shared_ptr<tnbLib::TModel_ParaWire>>
//tnbLib::Cad_tApprxParaPlane::RetrieveWires
//(
//	const std::shared_ptr<tnbLib::TModel_Plane>& thePlane
//)
//{
//	Debug_Null_Pointer(thePlane);
//	auto wires = thePlane->RetrieveWires();
//	return std::move(wires);
//}