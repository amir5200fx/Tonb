#include <Cad_tEdgeMakerInfo_Relative.hxx>

#include <opencascade/Precision.hxx>

#include <Entity3d_Box.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const Standard_Real tnbLib::Cad_tEdgeMakerInfo_Relative::DEFAULT_TOLERANCE = Precision::Confusion();

Standard_Real 
tnbLib::Cad_tEdgeMakerInfo_Relative::Tolerance() const
{
	Debug_Null_Pointer(Domain());
	return theTolerance_ * Domain()->Diameter();
}