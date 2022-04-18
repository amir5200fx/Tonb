#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
namespace tnbLib
{

	template<class MeshPlnCurve>
	Entity2d_Box Mesh_PlnWire<MeshPlnCurve>::CalcParametricBoundingBox() const
	{
		const auto& curves = Curves();
		if (curves.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "there is no curve int the wire!" << endl
				<< abort(FatalError);
		}

		Debug_Null_Pointer(curves[0]);
		auto box = CalcBoundingBox(*curves.at(0));
		forThose(Index, 1, curves.size() - 1)
		{
			Debug_Null_Pointer(curves.at(Index));
			box = Entity2d_Box::Union(box, CalcBoundingBox(*curves.at(Index)));
		}
		return std::move(box);
	}

	template<class MeshPlnCurve>
	std::vector<std::shared_ptr<MeshPlnCurve>>
		Mesh_PlnWire<MeshPlnCurve>::RetrieveCurvesFrom
		(
			const std::vector<std::shared_ptr<Mesh_PlnWire>>& theWires
		)
	{
		std::vector<std::shared_ptr<MeshPlnCurve>> merged;
		Standard_Integer nbcurves = 0;
		for (const auto& x : theWires)
		{
			Debug_Null_Pointer(x);
			nbcurves += x->NbCurves();
		}
		merged.reserve(nbcurves);
		for (const auto& x : theWires)
		{
			Debug_Null_Pointer(x);

			const auto& curves = x->Curves();

			for (const auto& icurve : curves)
			{
				Debug_Null_Pointer(icurve);
				merged.push_back(icurve);
			}
		}
		return std::move(merged);
	}
}