#include <Cad_ColorApprxMetric.hxx>

#include <Mesh2d_Element.hxx>
#include <Mesh2d_Node.hxx>
#include <MeshBase_Tools.hxx>
#include <Cad_MetricCalculator.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Entity2d_Metric1.hxx>
#include <Adt_AvlTree.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom_Surface.hxx>

namespace tnbLib
{
	typedef std::vector<std::shared_ptr<Mesh2d_Element>> elementList;

	static void TrackRegion
	(
		const Mesh2d_Element& theElement,
		Adt_AvlTree<std::shared_ptr<Mesh2d_Element>>& theRegister,
		elementList& theList
	)
	{
		const auto n0 = theElement.Neighbor0().lock();
		if (n0 AND NOT theRegister.RemoveIgnoreWarning(n0))
		{
			theList.push_back(n0);
			TrackRegion(*n0, theRegister, theList);
		}

		const auto n1 = theElement.Neighbor1().lock();
		if (n1 AND NOT theRegister.RemoveIgnoreWarning(n1))
		{
			theList.push_back(n1);
			TrackRegion(*n1, theRegister, theList);
		}

		const auto n2 = theElement.Neighbor2().lock();
		if (n2 AND NOT theRegister.RemoveIgnoreWarning(n2))
		{
			theList.push_back(n2);
			TrackRegion(*n2, theRegister, theList);
		}
	}

	static std::vector<std::shared_ptr<elementList>> 
		TrackRegions
		(
			Adt_AvlTree<std::shared_ptr<Mesh2d_Element>>& blackElements
		)
	{
		std::vector<std::shared_ptr<elementList>> regions;
		while (blackElements.Size())
		{
			auto l = std::make_shared<elementList>();

			std::shared_ptr<Mesh2d_Element> root;
			blackElements.Root(root);
			blackElements.Remove(root);

			l->push_back(root);

			TrackRegion(*root, blackElements, *l);

			regions.push_back(std::move(l));
		}
		return std::move(regions);
	}

	static Standard_Boolean 
		IsDegenerated
		(
			const Mesh2d_Element& theElement,
			const Handle(Geom_Surface)& theGeometry, 
			const std::shared_ptr<Cad_MetricCalculator>& theCalculator,
			const Standard_Real theCriterion
		)
	{
		const auto& P0 = theElement.Node0()->Coord();
		const auto& P1 = theElement.Node1()->Coord();
		const auto& P2 = theElement.Node2()->Coord();

		auto m0 = theCalculator->CalcMetric(P0, theGeometry);
		if (m0.Determinant() < theCriterion) return Standard_True;

		auto m1 = theCalculator->CalcMetric(P1, theGeometry);
		if (m1.Determinant() < theCriterion) return Standard_True;

		auto m2 = theCalculator->CalcMetric(P2, theGeometry);
		if (m2.Determinant() < theCriterion) return Standard_True;

		return Standard_False;
	}

	static void 
		RegisterBlackElements
		(
			Adt_AvlTree<std::shared_ptr<Mesh2d_Element>>& theReg,
			const std::vector<std::shared_ptr<Mesh2d_Element>>& theElements,
			const Handle(Geom_Surface)& theGeometry, 
			const std::shared_ptr<Cad_MetricCalculator>& theCalculator,
			const Standard_Real theCriterion
		)
	{
		for (const auto& x : theElements)
		{
			Debug_Null_Pointer(x);
			if (IsDegenerated(*x, theGeometry, theCalculator, theCriterion))
			{
				theReg.Insert(x);
			}
		}
	}
}

void tnbLib::Cad_ColorApprxMetric::Perform()
{
	if (NOT Geometry())
	{
		FatalErrorIn(FunctionSIG)
			<< "no geometry has been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Approximation())
	{
		FatalErrorIn(FunctionSIG)
			<< "no approximation has been loaded!" << endl
			<< abort(FatalError);
	}

	auto mesh = MeshBase_Tools::MakeMesh(*Approximation());

	std::vector<std::pair<std::shared_ptr<Mesh2d_Element>, Standard_Integer>> marks(mesh.size());
	for (const auto& x : mesh)
	{
		auto paired = std::make_pair(x, 0);
		marks[Index_Of(x->Index())] = std::move(paired);
	}

	Adt_AvlTree<std::shared_ptr<Mesh2d_Element>> reg;
	reg.SetComparableFunction(&Mesh2d_Element::IsLess);

	RegisterBlackElements(reg, mesh, Geometry(), MetricCalculator(), Criterion());

	const auto regions = TrackRegions(reg);
	Debug_If_Condition_Message(reg.Size(), "the register must be empty!");

	Standard_Integer regionNb = 0;
	for (const auto& reg : regions)
	{
		Debug_Null_Pointer(reg);
		const auto& region = *reg;

		regionNb++;

		for (const auto& x : region)
		{
			marks[Index_Of(x->Index())].second = regionNb;
		}
	}

	theElements_ = std::move(marks);

	Change_IsDone() = Standard_True;
}