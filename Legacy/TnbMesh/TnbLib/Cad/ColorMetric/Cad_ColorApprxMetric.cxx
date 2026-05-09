#include <Cad_ColorApprxMetric.hxx>

#include <Mesh2d_Element.hxx>
#include <Mesh2d_Edge.hxx>
#include <Mesh2d_Node.hxx>
#include <MeshBase_Tools.hxx>
#include <Cad_MetricCalculator.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Entity2d_Metric1.hxx>
#include <Entity2d_Polygon.hxx>
#include <Entity2d_Box.hxx>
#include <Adt_AvlTree.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <opencascade/Geom_Surface.hxx>

#include <stack>

const Standard_Real tnbLib::Cad_ColorApprxMetric::DEFAULT_CRITERION(1.0E-6);

Standard_Integer 
tnbLib::Cad_ColorApprxMetric::NbElements() const
{
	CheckDone((*this));
	return (Standard_Integer)theElements_.size();
}

Standard_Integer 
tnbLib::Cad_ColorApprxMetric::Value
(
	const Standard_Integer theIndex
) const
{
	CheckDone((*this));
	Debug_Bad_Index(theIndex, 0, NbElements() - 1);
	return theElements_.at(theIndex).second;
}

Standard_Integer 
tnbLib::Cad_ColorApprxMetric::Value
(
	const Pnt2d & theCoord
) const
{
	CheckDone((*this));
//#ifdef _DEBUG
//	const auto& d = theApproximation_->BoundingBox();
//	Debug_Null_Pointer(d);
//	if (NOT d->IsInside(theCoord))
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "the coord is outside of the domain!" << endl
//			<< abort(FatalError);
//	}
//#endif // _DEBUG

	if (NOT theStart_)
	{
		theStart_ = LastItem(theElements_).first;
	}
	auto elm = MeshBase_Tools::ElementLocation(theStart_, theCoord);
	Debug_Null_Pointer(elm);
	theStart_ = elm;
	return Value(Index_Of(elm->Index()));
}

namespace tnbLib
{
	typedef std::vector<std::shared_ptr<Mesh2d_Element>> elementList;

	static void TrackRegion
	(
		const std::shared_ptr<Mesh2d_Element>& theElement,
		Adt_AvlTree<std::shared_ptr<Mesh2d_Element>>& theRegister,
		elementList& theList
	)
	{
		if (NOT theElement)
		{
			return;
		}
		std::stack<std::shared_ptr<Mesh2d_Element>> stk;
		stk.push(theElement);

		while (NOT stk.empty())
		{
			auto elm = stk.top();
			stk.pop();
			
			auto n0 = elm->Neighbor0().lock();
			if (n0)
			{
				if (NOT theRegister.RemoveIgnoreWarning(n0))
				{
					theList.push_back(n0);
					stk.push(std::move(n0));
				}
			}

			auto n1 = elm->Neighbor1().lock();
			if (n1)
			{
				if (NOT theRegister.RemoveIgnoreWarning(n1))
				{
					theList.push_back(n1);
					stk.push(std::move(n1));
				}
			}

			auto n2 = elm->Neighbor2().lock();
			if (n2)
			{
				if (NOT theRegister.RemoveIgnoreWarning(n2))
				{
					theList.push_back(n2);
					stk.push(std::move(n2));
				}
			}
		}
		/*std::cout << "inner" << std::endl;
		const auto n0 = theElement.Neighbor0().lock();
		if (n0)
		{
			if (NOT theRegister.RemoveIgnoreWarning(n0))
			{
				theList.push_back(n0);
				TrackRegion(*n0, theRegister, theList);
			}
		}

		const auto n1 = theElement.Neighbor1().lock();
		if (n1)
		{
			if (NOT theRegister.RemoveIgnoreWarning(n1))
			{
				theList.push_back(n1);
				TrackRegion(*n1, theRegister, theList);
			}	
		}

		const auto n2 = theElement.Neighbor2().lock();
		if (n2)
		{
			if (NOT theRegister.RemoveIgnoreWarning(n2))
			{
				theList.push_back(n2);
				TrackRegion(*n2, theRegister, theList);
			}	
		}*/


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

			TrackRegion(root, blackElements, *l);

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
			const Standard_Real theCriterion,
			const Standard_Real theCoeff
		)
	{
		const auto& P0 = theElement.Node0()->Coord();
		const auto& P1 = theElement.Node1()->Coord();
		const auto& P2 = theElement.Node2()->Coord();

		auto m0 = theCalculator->CalcMetric(P0, theGeometry);
		if (m0.Determinant()*theCoeff < theCriterion) return Standard_True;

		auto m1 = theCalculator->CalcMetric(P1, theGeometry);
		if (m1.Determinant()*theCoeff < theCriterion) return Standard_True;

		auto m2 = theCalculator->CalcMetric(P2, theGeometry);
		if (m2.Determinant()*theCoeff < theCriterion) return Standard_True;

		return Standard_False;
	}

	static void 
		RegisterBlackElements
		(
			Adt_AvlTree<std::shared_ptr<Mesh2d_Element>>& theReg,
			const std::vector<std::shared_ptr<Mesh2d_Element>>& theElements,
			const Handle(Geom_Surface)& theGeometry, 
			const std::shared_ptr<Cad_MetricCalculator>& theCalculator,
			const Standard_Real theCriterion,
			const Standard_Real theCoeff
		)
	{
		for (const auto& x : theElements)
		{
			Debug_Null_Pointer(x);
			if (IsDegenerated(*x, theGeometry, theCalculator, theCriterion, theCoeff))
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

	if (NOT MetricCalculator())
	{
		FatalErrorIn(FunctionSIG)
			<< "no metric calculator has been loaded!" << endl
			<< abort(FatalError);
	}

	auto mesh = MeshBase_Tools::MakeMesh(*Approximation());

	std::vector<std::pair<std::shared_ptr<Mesh2d_Element>, Standard_Integer>> marks(mesh.size());
	for (const auto& x : mesh)
	{
		auto paired = std::make_pair(x, 0);
		marks.at(Index_Of(x->Index())) = std::move(paired);
	}

	Adt_AvlTree<std::shared_ptr<Mesh2d_Element>> reg;
	reg.SetComparableFunction(&Mesh2d_Element::IsLess);

	const auto weight = 1.0 / MaxDet();
	RegisterBlackElements(reg, mesh, Geometry(), MetricCalculator(), Criterion(), weight);

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
			marks.at(Index_Of(x->Index())).second = regionNb;
		}
	}
	theElements_ = std::move(marks);

	Change_IsDone() = Standard_True;
}

Standard_Real 
tnbLib::Cad_ColorApprxMetric::CalcCriterion
(
	const Standard_Real theMaxDet
)
{
	if (std::abs(theMaxDet) <= gp::Resolution())
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid value of max. det. has been detected!" << endl
			<< " - max. det: " << theMaxDet << endl
			<< abort(FatalError);
	}
	return 1.0 / theMaxDet;
}

void tnbLib::Cad_ColorApprxMetric::Check
(
	const Entity2d_Polygon & thePoly,
	const Cad_ColorApprxMetric & theApprox
)
{
	if (NOT theApprox.IsDone())
	{
		FatalErrorIn(FunctionSIG)
			<< "the application is not performed!" << endl
			<< abort(FatalError);
	}
	const auto& pts = thePoly.Points();
	const auto d = Entity2d_Box::BoundingBoxOf(theApprox.Approximation()->Points());
	//const auto& d = theApprox.Approximation()->BoundingBox();
	//Debug_Null_Pointer(d);
	for (const auto& x : pts)
	{
		if (NOT d.IsInside(x))
		{
			FatalErrorIn(FunctionSIG)
				<< "the coord is outside of the domain!" << endl
				<< abort(FatalError);
		}
	}
}