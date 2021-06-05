#include <PtdModel_BladeFace.hxx>

#include <Pnt3d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <StdFail_NotDone.hxx>
#include <TColgp_Array2OfPnt.hxx>
#include <GeomAPI_PointsToBSplineSurface.hxx>
#include <Geom_BSplineSurface.hxx>

std::shared_ptr<tnbLib::PtdModel_BladeFace> 
tnbLib::PtdModel_BladeFace::CreateFace(std::vector<std::vector<Pnt3d>>& Qs)
{
	try
	{
		const auto nbSections = Qs.size();
		if (NOT nbSections)
		{
			FatalErrorIn(FunctionSIG)
				<< "no section has been found!" << endl
				<< abort(FatalError);
		}

		const auto nbSpans = Qs[0].size();
		if (NOT nbSpans)
		{
			FatalErrorIn(FunctionSIG)
				<< "no span has been found!" << endl
				<< abort(FatalError);
		}

		TColgp_Array2OfPnt Q(1, nbSections, 1, nbSpans);
		forThose(I, 0, nbSections - 1)
		{
			forThose(J, 0, nbSpans - 1)
			{
				Q.SetValue(I + 1, J + 1, Qs[I][J]);
			}
		}

		GeomAPI_PointsToBSplineSurface alg;
		alg.Interpolate(Q);

		Debug_If_Condition_Message(NOT alg.IsDone(), "interpolation is not performed");

		auto face = std::make_shared<PtdModel_BladeFace>(alg.Surface());
		return std::move(face);

	}
	catch (const StdFail_NotDone&)
	{
		FatalErrorIn(FunctionSIG)
			<< "unable to interpolate the surface!" << endl
			<< abort(FatalError);
	}
	return nullptr;
}