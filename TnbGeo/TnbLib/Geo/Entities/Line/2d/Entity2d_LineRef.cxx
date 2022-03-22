#include <Entity2d_LineRef.hxx>

#include <Pnt2d.hxx>
#include <Dir2d.hxx>
#include <Vec2d.hxx>
#include <Entity_Line.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#ifdef Handle
#undef Handle
#endif // Handle
#include <CGAL\Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL\Line_2_Line_2_intersection.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::Point_2 Point_2;
typedef Kernel::Line_2 Line_2;
typedef Kernel::Direction_2 Direction_2;

Standard_Boolean tnbLib::gProcessor::IsIntersect
(
	const Entity2d_LineRef & theLine1, 
	const Entity2d_LineRef & theLine2
)
{
	Point_2 P(theLine1.P().X(), theLine1.P().Y());
	Point_2 Q(theLine2.P().X(), theLine2.P().Y());

	Direction_2 dirP(theLine1.Dir().X(), theLine1.Dir().Y());
	Direction_2 dirQ(theLine2.Dir().X(), theLine2.Dir().Y());

	Line_2 Lp(P, dirP);
	Line_2 Lq(Q, dirQ);

	return CGAL::do_intersect(Lp, Lq);
}

tnbLib::Pnt2d tnbLib::gProcessor::Intersect
(
	const Entity2d_LineRef & theLine0, 
	const Entity2d_LineRef & theLine1,
	const Standard_Real theTol
)
{
	Standard_Real denom = 
		theLine0.Dir().Crossed(theLine1.Dir());

	if (ABS(denom) <= theTol)
	{
		FatalErrorIn(FunctionSIG)
			<< " Two Lines are parallel"
			<< abort(FatalError);
	}

	gp_Vec2d vcr = gp_Vec2d(theLine0.P(), theLine1.P());
	gp_Vec2d Vec0(theLine0.Dir().XY());
	gp_Vec2d Vec1(theLine1.Dir().XY());

	Standard_Real nume = vcr.Crossed(Vec1);

	Standard_Real alf = nume / denom;

	const gp_Pnt2d& P0 = theLine0.P();

	Pnt2d IntPoint = P0.Translated(alf * Vec0);
	return std::move(IntPoint);
}

