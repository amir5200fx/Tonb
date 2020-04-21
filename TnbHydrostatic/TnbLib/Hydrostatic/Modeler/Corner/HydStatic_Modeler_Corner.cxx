#include <HydStatic_Modeler_Corner.hxx>

#include <error.hxx>
#include <OSstream.hxx>

Standard_Boolean 
tnbLib::hydStcLib::Modeler_Corner::IsLess
(
	const std::shared_ptr<Modeler_Corner>& theCorner0,
	const std::shared_ptr<Modeler_Corner>& theCorner1
)
{
	Debug_Null_Pointer(theCorner0);
	Debug_Null_Pointer(theCorner1);

	return theCorner0->Index() < theCorner1->Index();
}