#include <Aft2d_AltrOptNodeSurface_PerpenDir.hxx>

#include <Aft2d_MetricPrcsrSurface.hxx>
#include <Aft_CorrOptNode_IterativeTools.hxx>
#include <Aft_SizeCorr_IterativeInfo.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const Standard_Integer tnbLib::Aft2d_AltrOptNodeSurface_PerpenDir::DEFAULT_MAX_LEV(5);
const Standard_Real tnbLib::Aft2d_AltrOptNodeSurface_PerpenDir::Perpendicular_Size(0.8660254037844);

Standard_Boolean 
tnbLib::Aft2d_AltrOptNodeSurface_PerpenDir::Iter
(
	const Standard_Integer theLev,
	const Pnt2d& theCentre
)
{
	if (theLev > MaxLevel())
	{
		return Standard_False;
	}

	if (NOT Aft_CorrOptNode_IterativeTools::Correct(*MetricMap(), theCentre, CorrectedRef(), Perpendicular_Size, *IterInfo()))
	{
		Aft_CorrOptNode_IterativeTools::Correct(*MetricMap(), CorrectedRef(), *Front(), *IterInfo());
		return Standard_True;
	}
	else
	{
		if (NOT Aft_CorrOptNode_IterativeTools::Correct(*MetricMap(), CorrectedRef(), *Front(), *IterInfo()))
		{
			return Standard_True;
		}
		return Iter(theLev + 1, theCentre);
	}
	return Standard_False;
}

void tnbLib::Aft2d_AltrOptNodeSurface_PerpenDir::Perform()
{
	Debug_Null_Pointer(IterInfo());
	Debug_Null_Pointer(Front());
	Debug_Null_Pointer(MetricMap());
	Debug_If_Condition(ElmSize() <= gp::Resolution());

	if (Iter(0, Front()->Centre()))
	{
		IsConvergedRef() = Standard_True;
	}
	else
	{
		IsConvergedRef() = Standard_False;
	}

	Change_IsDone() = Standard_True;
}