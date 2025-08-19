#include <Discret2d_PlnCurve.hxx>

#include <Discret2d_PlnCurve_Function.hxx>
#include <Discret_CurveInfo.hxx>
#include <Pln_Curve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	typedef Discret2d_PlnCurve::Segment Segment;

	void Subdivide
	(
		const std::shared_ptr<Pln_Curve>& theCurve,
		const Segment& theSeg,
		const std::shared_ptr<Discret2d_PlnCurve_Function>& theFun,
		const Standard_Integer theLev,
		const Standard_Integer theInitLev,
		const Standard_Integer theMaxLev,
		std::vector<Segment>& theSegs
	)
	{
		if (theLev < theInitLev)
		{
			Subdivide(theCurve, theSeg.Left(), theFun, theLev + 1, theInitLev, theMaxLev, theSegs);
			Subdivide(theCurve, theSeg.Right(), theFun, theLev + 1, theInitLev, theMaxLev, theSegs);
		}
		else
		{
			if (theLev > theMaxLev)
			{
				theSegs.push_back(theSeg);
				return;
			}

			if (theFun->Subdivide(theCurve, theSeg.X0, theSeg.X1))
			{
				Subdivide(theCurve, theSeg.Left(), theFun, theLev + 1, theInitLev, theMaxLev, theSegs);
				Subdivide(theCurve, theSeg.Right(), theFun, theLev + 1, theInitLev, theMaxLev, theSegs);
			}
			else
			{
				theSegs.push_back(theSeg);
				return;
			}
		}
	}
}

void tnbLib::Discret2d_PlnCurve::Subdivide(std::vector<Segment>& theSegs) const
{
	tnbLib::Subdivide
	(
		Curve(),
		Segment(U0(), U1()),
		Function(), 0,
		DiscretInfo()->MinSubdivide(),
		DiscretInfo()->MaxSubdivide(),
		theSegs
	);
}

void tnbLib::Discret2d_PlnCurve::Perform()
{
	if (NOT Curve())
	{
		FatalErrorIn(FunctionSIG)
			<< "no curve has been loaded." << endl
			<< abort(FatalError);
	}

	if (NOT DiscretInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "no info has been loaded." << endl
			<< abort(FatalError);
	}

	if (NOT Function())
	{
		FatalErrorIn(FunctionSIG)
			<< "no function has been loaded." << endl
			<< abort(FatalError);
	}

	std::vector<Segment> segments;
	Subdivide(segments);

	std::sort
	(
		segments.begin(), segments.end(),
		[](const Segment& s0, const Segment& s1)
		{return s0.Mean() < s1.Mean(); });

	std::vector<Standard_Real> xs;
	xs.reserve(segments.size() + 1);
	xs.push_back(segments.begin()->X0);
	for (const auto& x : segments)
	{
		xs.push_back(x.X1);
	}
	theMesh_ = std::make_shared<std::vector<Standard_Real>>(std::move(xs));

	Change_IsDone() = Standard_True;
}