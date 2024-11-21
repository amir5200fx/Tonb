#include <Cad2d_CmptLib.hxx>

#include <Entity2d_Box.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Edge.hxx>
#include <Pln_CmpEdge.hxx>
#include <Pln_Wire.hxx>
#include <Pln_Tools.hxx>
#include <Cad2d_Plane.hxx>
#include <NumAlg_IntegFunc.hxx>
#include <NumAlg_AdaptiveInteg.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <Geo_CmptLib.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <opencascade/Geom2d_Curve.hxx>
#include <opencascade/Geom2d_BoundedCurve.hxx>

namespace tnbLib
{

	namespace cmptLib
	{

		class AreaIntegrand
			: public NumAlg_IntegFunc
		{

			/*Private Data*/

			const Geom2d_Curve& theEntity_;

			Standard_Real theY0_;

		public:

			AreaIntegrand(const Geom2d_Curve& theEntity, const Standard_Real y0)
				: theEntity_(theEntity)
				, theY0_(y0)
			{}

			const auto& Entity() const
			{
				return theEntity_;
			}

			auto Y0() const
			{
				return theY0_;
			}

			Standard_Real Value(const Standard_Real x) const override;
		};

		class xCentreIntegrand
			: public NumAlg_IntegFunc
		{

			/*Private Data*/

			const Geom2d_Curve& theEntity_;

		public:

			xCentreIntegrand(const Geom2d_Curve& theEntity)
				: theEntity_(theEntity)
			{}

			const auto& Entity() const
			{
				return theEntity_;
			}

			Standard_Real Value(const Standard_Real x) const override;
		};

		class yCentreIntegrand
			: public NumAlg_IntegFunc
		{

			/*Private Data*/

			const Geom2d_Curve& theEntity_;

		public:

			yCentreIntegrand(const Geom2d_Curve& theEntity)
				: theEntity_(theEntity)
			{}

			const auto& Entity() const
			{
				return theEntity_;
			}

			Standard_Real Value(const Standard_Real x) const override;
		};

		class MxIntegrand
			: public NumAlg_IntegFunc
		{

			/*Private Data*/

			const Geom2d_Curve& theEntity_;

			Standard_Real theY0_;

		public:

			MxIntegrand
			(
				const Geom2d_Curve& theEntity, 
				const Standard_Real y0
			)
				: theEntity_(theEntity)
				, theY0_(y0)
			{}

			const auto& Entity() const
			{
				return theEntity_;
			}

			auto Y0() const
			{
				return theY0_;
			}

			Standard_Real Value(const Standard_Real x) const override;
		};

		class MyIntegrand
			: public NumAlg_IntegFunc
		{

			/*Private Data*/

			const Geom2d_Curve& theEntity_;

			Standard_Real theX0_;

		public:

			MyIntegrand
			(
				const Geom2d_Curve& theEntity,
				const Standard_Real x0
			)
				: theEntity_(theEntity)
				, theX0_(x0)
			{}

			const auto& Entity() const
			{
				return theEntity_;
			}

			auto X0() const
			{
				return theX0_;
			}

			Standard_Real Value(const Standard_Real x) const override;
		};

		class IxIntegrand
			: public NumAlg_IntegFunc
		{

			/*Private Data*/

			const Geom2d_Curve& theEntity_;

			Standard_Real theYc_;

		public:

			IxIntegrand(const Geom2d_Curve& theEntity, const Standard_Real y0)
				: theEntity_(theEntity)
				, theYc_(y0)
			{}

			auto Yc() const
			{
				return theYc_;
			}

			const auto& Entity() const
			{
				return theEntity_;
			}

			Standard_Real Value(const Standard_Real x) const override;
		};

		class IyIntegrand
			: public NumAlg_IntegFunc
		{

			/*Private Data*/

			const Geom2d_Curve& theEntity_;

			Standard_Real theXc_;

		public:

			IyIntegrand(const Geom2d_Curve& theEntity, const Standard_Real x0)
				: theEntity_(theEntity)
				, theXc_(x0)
			{}

			auto Xc() const
			{
				return theXc_;
			}

			const auto& Entity() const
			{
				return theEntity_;
			}

			Standard_Real Value(const Standard_Real x) const override;
		};
	}
}

Standard_Real 
tnbLib::cmptLib::AreaIntegrand::Value
(
	const Standard_Real x
) const
{
	gp_Vec2d der;
	gp_Pnt2d pt;
	
	Entity().D1(x, pt, der);

	return (pt.Y() - Y0())*der.X();
	//return -pt.Y()*der.X();
}

Standard_Real 
tnbLib::cmptLib::xCentreIntegrand::Value
(
	const Standard_Real x
) const
{
	gp_Vec2d der;
	gp_Pnt2d pt;

	Entity().D1(x, pt, der);

	return pt.Y()*der.X()*pt.X();
}

Standard_Real 
tnbLib::cmptLib::yCentreIntegrand::Value
(
	const Standard_Real x
) const
{
	gp_Vec2d der;
	gp_Pnt2d pt;

	Entity().D1(x, pt, der);

	return pt.Y()*der.X()*(0.5*pt.Y());
}

Standard_Real 
tnbLib::cmptLib::MxIntegrand::Value
(
	const Standard_Real x
) const
{
	gp_Vec2d der;
	gp_Pnt2d pt;

	Entity().D1(x, pt, der);

	const auto y = pt.Y() - Y0();
	return 0.5*(y)*pt.Y()*der.X();
}

Standard_Real 
tnbLib::cmptLib::MyIntegrand::Value
(
	const Standard_Real x
) const
{
	gp_Vec2d der;
	gp_Pnt2d pt;

	Entity().D1(x, pt, der);
	const auto dx = pt.X() - X0();
	return (dx)*pt.Y()*der.X();
}

Standard_Real 
tnbLib::cmptLib::IxIntegrand::Value
(
	const Standard_Real x
) const
{
	gp_Vec2d der;
	gp_Pnt2d pt;

	Entity().D1(x, pt, der);

	const auto y = pt.Y() - Yc();
	return (y*y)*pt.X()*der.Y();
}

Standard_Real 
tnbLib::cmptLib::IyIntegrand::Value
(
	const Standard_Real x
) const
{
	gp_Vec2d der;
	gp_Pnt2d pt;

	Entity().D1(x, pt, der);

	const auto dx = pt.X() - Xc();
	return (dx*dx)*pt.Y()*der.X();
}

Standard_Real 
tnbLib::Cad2d_CmptLib::Curvature
(
	const Handle(Geom2d_Curve)& theCurve, 
	const Standard_Real thePar
)
{
	Debug_Null_Pointer(theCurve);


#ifdef _DEBUG
	if (NOT Pln_Tools::IsBounded(theCurve))
	{
		FatalErrorIn(FunctionSIG)
			<< "the curve must be bounded!" << endl
			<< abort(FatalError);
	}

	if (NOT INSIDE(thePar, theCurve->FirstParameter(), theCurve->LastParameter()))
	{
		FatalErrorIn(FunctionSIG)
			<< "the parameter is not inside the span of the curve!" << endl
			<< " - parameter: " << thePar << endl
			<< " - first: " << theCurve->FirstParameter() << endl
			<< " - last: " << theCurve->LastParameter() << endl
			<< abort(FatalError);
	}
#endif // _DEBUG
	gp_Pnt2d Point;
	gp_Vec2d Vector1;
	gp_Vec2d Vector2;

	theCurve->D2(thePar, Point, Vector1, Vector2);
	return ABS(Vector1.Crossed(Vector2)) / (std::pow(Vector1.Magnitude(), 3));
}

Standard_Real 
tnbLib::Cad2d_CmptLib::AreaUnderCurve
(
	const Handle(Geom2d_Curve)& theCurve,
	const Standard_Real y0, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
#ifdef _DEBUG
	if (NOT Pln_Tools::IsBounded(theCurve))
	{
		FatalErrorIn("Standard_Real Cad2d_CmptLib::AreaUnderCurve(Args...)")
			<< "the curve must be bounded!" << endl
			<< abort(FatalError);
	}
#endif // _DEBUG

	cmptLib::AreaIntegrand fun(*theCurve, y0);
	NumAlg_AdaptiveInteg<cmptLib::AreaIntegrand> 
		integration
		(
			fun, theCurve->FirstParameter(),
			theCurve->LastParameter(),
			*theInfo
		);

	integration.Perform();
	Debug_If_Condition_Message(NOT integration.IsDone(), "the algorithm is not performed!");

	return theInfo->Result();
}

Standard_Real 
tnbLib::Cad2d_CmptLib::Mx
(
	const Handle(Geom2d_Curve)& theCurve, 
	const Standard_Real y0,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
#ifdef _DEBUG
	if (NOT Pln_Tools::IsBounded(theCurve))
	{
		FatalErrorIn("Standard_Real Cad2d_CmptLib::Mx(Args...)")
			<< "the curve must be bounded!" << endl
			<< abort(FatalError);
	}
#endif // _DEBUG

	cmptLib::MxIntegrand fun(*theCurve, y0);
	NumAlg_AdaptiveInteg<cmptLib::MxIntegrand>
		integration
		(
			fun, theCurve->FirstParameter(),
			theCurve->LastParameter(),
			*theInfo
		);

	integration.Perform();
	Debug_If_Condition_Message(NOT integration.IsDone(), "the algorithm is not performed!");

	return theInfo->Result();
}

Standard_Real 
tnbLib::Cad2d_CmptLib::My
(
	const Handle(Geom2d_Curve)& theCurve,
	const Standard_Real x0,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
#ifdef _DEBUG
	if (NOT Pln_Tools::IsBounded(theCurve))
	{
		FatalErrorIn("Standard_Real Cad2d_CmptLib::My(Args...)")
			<< "the curve must be bounded!" << endl
			<< abort(FatalError);
	}
#endif // _DEBUG

	cmptLib::MyIntegrand fun(*theCurve, x0);
	NumAlg_AdaptiveInteg<cmptLib::MyIntegrand>
		integration
		(
			fun, theCurve->FirstParameter(),
			theCurve->LastParameter(),
			*theInfo
		);

	integration.Perform();
	Debug_If_Condition_Message(NOT integration.IsDone(), "the algorithm is not performed!");

	return theInfo->Result();
}

Standard_Real 
tnbLib::Cad2d_CmptLib::Ix
(
	const Handle(Geom2d_Curve)& theCurve, 
	const Standard_Real y0,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
#ifdef _DEBUG
	if (NOT Pln_Tools::IsBounded(theCurve))
	{
		FatalErrorIn("Standard_Real Cad2d_CmptLib::Ix(Args...)")
			<< "the curve must be bounded!" << endl
			<< abort(FatalError);
	}
#endif // _DEBUG

	cmptLib::IxIntegrand fun(*theCurve, y0);
	NumAlg_AdaptiveInteg<cmptLib::IxIntegrand>
		integration
		(
			fun, theCurve->FirstParameter(),
			theCurve->LastParameter(),
			*theInfo
		);

	integration.Perform();
	Debug_If_Condition_Message(NOT integration.IsDone(), "the algorithm is not performed!");

	return theInfo->Result();
}

Standard_Real
tnbLib::Cad2d_CmptLib::Iy
(
	const Handle(Geom2d_Curve)& theCurve,
	const Standard_Real x0,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
#ifdef _DEBUG
	if (NOT Pln_Tools::IsBounded(theCurve))
	{
		FatalErrorIn("Standard_Real Cad2d_CmptLib::Iy(Args...)")
			<< "the curve must be bounded!" << endl
			<< abort(FatalError);
	}
#endif // _DEBUG

	cmptLib::IyIntegrand fun(*theCurve, x0);
	NumAlg_AdaptiveInteg<cmptLib::IyIntegrand>
		integration
		(
			fun, theCurve->FirstParameter(),
			theCurve->LastParameter(),
			*theInfo
		);

	integration.Perform();
	Debug_If_Condition_Message(NOT integration.IsDone(), "the algorithm is not performed!");

	return theInfo->Result();
}

Standard_Real 
tnbLib::Cad2d_CmptLib::Area
(
	const Pln_Wire & theWire, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	Standard_Real sum = 0;

	const auto box = theWire.BoundingBox(0);
	const auto y0 = box.P0().Y();

	const auto& edges = theWire.Edges();
	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);

		const auto& geom = x->Curve()->Geometry();
		auto area = AreaUnderCurve(geom, y0, theInfo);

		sum += (x->Sense() ? -area : area);
	}
	return sum;
}

Standard_Real 
tnbLib::Cad2d_CmptLib::DiscreteArea
(
	const Pln_Wire & theWire
)
{
	const auto& edges = theWire.Edges();
	Standard_Real sum = 0;
	for (const auto& e : edges)
	{
		Debug_Null_Pointer(e);
		if (NOT e->Mesh())
		{
			FatalErrorIn(FunctionSIG)
				<< "the edge has no mesh!" << endl
				<< abort(FatalError);
		}
		const auto& poly = *e->Mesh();
		auto area = Geo_CmptLib::Area(poly);

		sum += (e->Sense() ? -area : area);
	}
	return sum;
}

Standard_Real 
tnbLib::Cad2d_CmptLib::xCentreProductArea
(
	const Handle(Geom2d_Curve)& theCurve, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
#ifdef _DEBUG
	if (NOT Pln_Tools::IsBounded(theCurve))
	{
		FatalErrorIn("Standard_Real Cad2d_CmptLib::xCentreProductArea(Args...)")
			<< "the curve must be bounded!" << endl
			<< abort(FatalError);
	}
#endif // _DEBUG

	cmptLib::xCentreIntegrand fun(*theCurve);
	NumAlg_AdaptiveInteg<cmptLib::xCentreIntegrand>
		integration
		(
			fun, theCurve->FirstParameter(),
			theCurve->LastParameter(),
			*theInfo
		);

	integration.Perform();
	Debug_If_Condition_Message(NOT integration.IsDone(), "the algorithm is not performed!");

	return theInfo->Result();
}

Standard_Real 
tnbLib::Cad2d_CmptLib::yCentreProductArea
(
	const Handle(Geom2d_Curve)& theCurve,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
#ifdef _DEBUG
	if (NOT Pln_Tools::IsBounded(theCurve))
	{
		FatalErrorIn("Standard_Real Cad2d_CmptLib::xCentreProductArea(Args...)")
			<< "the curve must be bounded!" << endl
			<< abort(FatalError);
	}
#endif // _DEBUG

	cmptLib::yCentreIntegrand fun(*theCurve);
	NumAlg_AdaptiveInteg<cmptLib::yCentreIntegrand>
		integration
		(
			fun, theCurve->FirstParameter(),
			theCurve->LastParameter(),
			*theInfo
		);

	integration.Perform();
	Debug_If_Condition_Message(NOT integration.IsDone(), "the algorithm is not performed!");

	return theInfo->Result();
}

tnbLib::Pnt2d 
tnbLib::Cad2d_CmptLib::Centre
(
	const Handle(Geom2d_Curve)& theCurve,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	const auto xbar = xCentreProductArea(theCurve, theInfo);
	const auto ybar = yCentreProductArea(theCurve, theInfo);

	const auto area = AreaUnderCurve(theCurve, 0, theInfo);

	Pnt2d pt(xbar / area, ybar / area);
	return std::move(pt);
}

tnbLib::Pnt2d 
tnbLib::Cad2d_CmptLib::Centre
(
	const Pln_Wire & theWire, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	Pnt2d sum;
	const auto& edges = theWire.Edges();
	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(x->Curve());

		sum += Centre(x->Curve()->Geometry(), theInfo);
	}
	sum /= (Standard_Real)edges.size();
	return std::move(sum);
}

Standard_Real 
tnbLib::Cad2d_CmptLib::Mx
(
	const Pln_Wire & theWire,
	const Standard_Real y0, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	Standard_Real sum = 0;

	const auto& edges = theWire.Edges();
	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(x->Curve());

		const auto& geom = x->Curve()->Geometry();
		auto ix = Mx(geom, y0, theInfo);

		sum += (x->Sense() ? -ix : ix);
	}
	return sum /*/ 3.0*/;
}

Standard_Real 
tnbLib::Cad2d_CmptLib::My
(
	const Pln_Wire & theWire,
	const Standard_Real x0, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	Standard_Real sum = 0;

	const auto& edges = theWire.Edges();
	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(x->Curve());

		const auto& geom = x->Curve()->Geometry();
		auto ix = My(geom, x0, theInfo);

		sum += (x->Sense() ? -ix : ix);
	}
	return sum /*/ 3.0*/;
}

Standard_Real 
tnbLib::Cad2d_CmptLib::Ix
(
	const Pln_Wire & theWire,
	const Standard_Real y0,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	Standard_Real sum = 0;

	const auto& edges = theWire.Edges();
	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(x->Curve());

		const auto& geom = x->Curve()->Geometry();
		auto ix = Ix(geom, y0, theInfo);

		sum += (x->Sense() ? ix : -ix);
	}
	return sum /*/ 3.0*/;
}

Standard_Real
tnbLib::Cad2d_CmptLib::Iy
(
	const Pln_Wire & theWire,
	const Standard_Real x0,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	Standard_Real sum = 0;

	const auto& edges = theWire.Edges();
	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(x->Curve());

		const auto& geom = x->Curve()->Geometry();
		auto ix = Iy(geom, x0, theInfo);

		sum += (x->Sense() ? -ix : ix);
	}
	return sum /*/ 3.0*/;
}

Standard_Real 
tnbLib::Cad2d_CmptLib::xCentre
(
	const Pln_Wire & theWire,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	Standard_Real sum = 0;

	const auto& edges = theWire.Edges();
	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(x->Curve());

		const auto& geom = x->Curve()->Geometry();

		auto xb = xCentreProductArea(geom, theInfo);
		sum += (x->Sense() ? -xb : xb);
	}

	return sum / Area(theWire, theInfo);
}

Standard_Real 
tnbLib::Cad2d_CmptLib::yCentre
(
	const Pln_Wire & theWire, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	Standard_Real sum = 0;

	const auto& edges = theWire.Edges();
	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(x->Curve());

		const auto& geom = x->Curve()->Geometry();

		auto xb = yCentreProductArea(geom, theInfo);
		sum += (x->Sense() ? -xb : xb);
	}

	return sum / Area(theWire, theInfo);
}

Standard_Real 
tnbLib::Cad2d_CmptLib::xCentreProductArea
(
	const Pln_Wire & theWire, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	Standard_Real sum = 0;

	const auto& edges = theWire.Edges();
	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(x->Curve());

		const auto& geom = x->Curve()->Geometry();

		auto xb = xCentreProductArea(geom, theInfo);
		sum += (x->Sense() ? -xb : xb);
	}

	return sum;
}

Standard_Real 
tnbLib::Cad2d_CmptLib::yCentreProductArea
(
	const Pln_Wire & theWire, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	Standard_Real sum = 0;

	const auto& edges = theWire.Edges();
	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(x->Curve());

		const auto& geom = x->Curve()->Geometry();

		auto xb = yCentreProductArea(geom, theInfo);
		sum += (x->Sense() ? -xb : xb);
	}

	return sum;
}

Standard_Real 
tnbLib::Cad2d_CmptLib::Area
(
	const Cad2d_Plane & thePlane,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	const auto& outer = thePlane.OuterWire();
	if (NOT outer)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid plane has been detected!" << endl
			<< abort(FatalError);
	}
	auto area = Area(*outer, theInfo);
	if (thePlane.InnerWires())
	{
		for (const auto& x : *thePlane.InnerWires())
		{
#ifdef _DEBUG
			auto iArea = Area(*x, theInfo);
			if (iArea > 0.0)
			{
				FatalErrorIn(FunctionSIG)
					<< "the inner wire area is not less than zero!" << endl
					<< abort(FatalError);
			}
			area += iArea;
#else
			area += Area(*x, theInfo);
#endif // _DEBUG

		}
	}
	return area;
}

tnbLib::Pnt2d 
tnbLib::Cad2d_CmptLib::Centre
(
	const Cad2d_Plane & thePlane, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	auto centre = Centre(*thePlane.OuterWire(), theInfo);

	if (const auto& inners = thePlane.InnerWires())
	{
		auto area = Area(*thePlane.OuterWire(), theInfo);
		Debug_If_Condition(area < 0);

		auto productArea = area * centre;
		auto totArea = area;

		for (const auto& x : *inners)
		{
			centre = Centre(*x, theInfo);
			area = Area(*x, theInfo);
			Debug_If_Condition(area > 0);

			productArea += area * centre;
			totArea += area;
		}
		auto c = productArea / totArea;
		return std::move(c);
	}
	else
	{	
		return std::move(centre);
	}
}

Standard_Real 
tnbLib::Cad2d_CmptLib::DiscreteArea
(
	const Cad2d_Plane & thePlane
)
{
	const auto& outer = thePlane.OuterWire();
	if (NOT outer)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid plane has been detected!" << endl
			<< abort(FatalError);
	}
	auto area = DiscreteArea(*outer);
	if (thePlane.InnerWires())
	{
		for (const auto& x : *thePlane.InnerWires())
		{
			auto iarea = DiscreteArea(*x);
			if (iarea > 0)
			{
				FatalErrorIn(FunctionSIG)
					<< "invalid value for the inner wire area has been detected!" << endl
					<< abort(FatalError);
			}
			area += iarea;
		}
	}
	return area;
}

//Standard_Real 
//tnbLib::Cad2d_CmptLib::Iv
//(
//	const Pln_Wire & theWire, 
//	const gp_Ax2d & theAx,
//	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
//)
//{
//	auto wire = std::dynamic_pointer_cast<Pln_Wire>(theWire.Copy());
//	Debug_Null_Pointer(wire);
//
//	auto t = Transform(gp::OX2d(), theAx);
//	return Iy(*wire, 0, theInfo);
//}

gp_Trsf2d 
tnbLib::Cad2d_CmptLib::Transform
(
	const gp_Ax2d & theCurrent,
	const gp_Ax2d & theTarget
)
{
	gp_Trsf2d t;
	t.SetTransformation(theCurrent, theTarget);

	return std::move(t);
}