#include <Cad_OpenCascadeRepair_Edge.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

#include <opencascade/TopoDS_Edge.hxx>
#include <opencascade/BRep_Tool.hxx>
#include <opencascade/BRepLib.hxx>
#include <opencascade/BRepLib_EdgeError.hxx>

unsigned short tnbLib::cadLib::OpenCascadeRepair_Edge::verbose(0);

void tnbLib::cadLib::OpenCascadeRepair_Edge::ApplySameRange()
{
	const auto& edge = Edge();

	if (verbose)
	{
		Info << endl;
		Info << " the SameRange flag checking..." << endl;
		Info << endl;
	}

	if (NOT BRep_Tool::SameRange(edge))
	{
		if (verbose)
		{
			Info << endl;
			Info << " the SameRange flag for the edge is false." << endl;
			Info << endl;
		}

		BRepLib::SameRange(edge);
	}
}

void tnbLib::cadLib::OpenCascadeRepair_Edge::ApplySameParameter()
{
	const auto& edge = Edge();

	if (verbose)
	{
		Info << endl;
		Info << " the SameRange flag checking..." << endl;
		Info << endl;
	}

	if (NOT BRep_Tool::SameParameter(edge))
	{
		if (verbose)
		{
			Info << endl;
			Info << " the SameParameter flag for the edge is false." << endl;
			Info << endl;
		}

		BRepLib::SameParameter(edge);
	}
}

void tnbLib::cadLib::OpenCascadeRepair_Edge::ApplyAll()
{
	ApplySameRange();
	ApplySameParameter();
}

void tnbLib::cadLib::OpenCascadeRepair_Edge::Perform(const repairAlg alg)
{
	switch (alg)
	{
	case repairAlg::sameRange:
		ApplySameRange();
		break;
	case repairAlg::sameParameter:
		ApplySameParameter();
		break;
	case repairAlg::all:
		ApplyAll();
		break;
	case repairAlg::none:
		break;
	default:
		FatalErrorIn(FunctionSIG)
			<< "unexpected repair algorithm has been detected!" << endl
			<< abort(FatalError);
		break;
	}
	if (verbose)
	{
		Info << endl;
		Info << " all algorithms are applied successfully!" << endl;
		Info << endl;
	}
	Change_IsDone() = Standard_True;
}