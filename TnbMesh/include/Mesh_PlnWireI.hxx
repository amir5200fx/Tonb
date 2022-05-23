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

	template<class CurveType>
	static auto 
		RetrieveIndicatorCurve
		(
			const std::vector<std::shared_ptr<CurveType>>& theWire
		)
	{
		Standard_Integer k = 0;
		std::shared_ptr<CurveType> c;
		for (const auto& x : theWire)
		{
			if (NOT x->IsSingular())
			{
				c = x;
				break;
			}
			k++;
		}
		auto t = std::make_pair(std::move(c), k);
		return std::move(t);
	}

	template<class CurveType>
	static auto MinTopoDistance(const Pnt2d& thePt, const std::shared_ptr<CurveType>& theC)
	{
		const auto[P0, P1] = theC->BoundCoords();
		return std::min(thePt.Distance(P0), thePt.Distance(P1));
	}

	template<class CurveType>
	static auto ReversePath(const std::shared_ptr<CurveType>& theC0, const std::shared_ptr<CurveType>& theC1)
	{
		const auto[P0, P1] = theC0->BoundCoords();
		return MinTopoDistance(P0, theC1) < MinTopoDistance(P1, theC1);
	}

	template<class MeshPlnCurve>
	inline void  Mesh_PlnWire<MeshPlnCurve>::OrientSingularCurves
	(
		std::vector<std::shared_ptr<MeshPlnCurve>>& theWire
	)
	{
		if (theWire.size() < 2)
		{
			return;
			/*FatalErrorIn(FunctionSIG)
				<< "invalid type of wire has been detected!" << endl
				<< abort(FatalError);*/
		}
		/*for (const auto& x : theWire)
		{
			std::cout << "is singular?" << x->IsSingular() << std::endl;
		}*/

		const auto[b, id] = RetrieveIndicatorCurve(theWire);
		if (NOT b)
		{
			FatalErrorIn(FunctionSIG)
				<< "no indicator curve has been found!" << endl
				<< abort(FatalError);
		}
		const auto n = theWire.size();
		auto i0 = id;
		auto i1 = (id + 1) % n;
		if (ReversePath(theWire.at(i0), theWire.at(i1)))
		{
			std::reverse(theWire.begin(), theWire.end());
		}

		for (Standard_Integer i = 0; i < n - 1; i++)
		{
			auto i0 = (id + i) % n;
			auto i1 = (id + i + 1) % n;

			Debug_Null_Pointer(theWire.at(i1));
			if (theWire.at(i1)->IsSingular())
			{
				theWire.at(i1)->OrientWith(theWire.at(i0));
			}
		}
	}
}