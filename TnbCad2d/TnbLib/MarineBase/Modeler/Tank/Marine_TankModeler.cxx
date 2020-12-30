#include <Marine_TankModeler.hxx>

#include <Pln_Edge.hxx>
#include <Marine_Modeler_Tools.hxx>

void tnbLib::Marine_TankModeler::CheckCurveType
(
	const std::shared_ptr<Pln_Edge>& theEdge, 
	const char * name
) const
{
	marineLib::Modeler_Tools::CheckCurveType(theEdge->Curve(), marineLib::Modeler_Tools::CurveType::tank);
}