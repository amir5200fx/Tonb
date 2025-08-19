#include <Cad2d_SubdivideCurve.hxx>

#include <Cad2d_IntsctEntity_Segment.hxx>
#include <Cad2d_IntsctEntity_TangSegment.hxx>
#include <Cad2d_CurveLength.hxx>
#include <Pln_Curve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const Standard_Real tnbLib::Cad2d_SubdivideCurve::DEFAULT_TOLERANCE = 1.0E-6;

namespace tnbLib
{

	namespace subdivide
	{

		static Standard_Real
			CalcLength
			(
				const Cad2d_IntsctEntity_Segment& ent,
				const std::shared_ptr<Pln_Curve>& curve,
				const std::shared_ptr<Cad2d_CurveLength>& alg
			)
		{
			return std::min
			(
				alg->CalcLength(curve, curve->FirstParameter(), ent.CharParameter()),
				alg->CalcLength(curve, ent.CharParameter(), curve->LastParameter())
			);
		}

		static Standard_Real 
			CalcLength
			(
				const Cad2d_IntsctEntity_TangSegment& ent,
				const std::shared_ptr<Pln_Curve>& curve, 
				const std::shared_ptr<Cad2d_CurveLength>& alg
			)
		{
			return std::abs(alg->CalcLength(curve, ent.Parameter0(), ent.Parameter1()));
		}
	}
}

void tnbLib::Cad2d_SubdivideCurve::Perform
(
	const std::vector<std::shared_ptr<Cad2d_IntsctEntity_Segment>>& theEntities
)
{
	if (NOT Parent())
	{
		FatalErrorIn(FunctionSIG)
			<< "no curve has been loaded." << endl
			<< abort(FatalError);
	}

	if (NOT CurveLength())
	{
		FatalErrorIn(FunctionSIG)
			<< "No curve length calculator algorithm has been loaded!" << endl
			<< abort(FatalError);
	}

	auto& curves = SubCurvesRef();
	auto curve = Parent();

	for (const auto& x : theEntities)
	{
		Debug_Null_Pointer(x);

		if (x->IsOrthogonal())
		{
			if (subdivide::CalcLength(*x, curve, CurveLength()) <= Tolerance())
			{
				continue;
			}

			auto[c0, c1] = curve->Split(x->CharParameter());

			if (NOT c0)
			{
				continue;
			}

			if (NOT c1)
			{
				continue;
			}

			Debug_Null_Pointer(c0);
			Debug_Null_Pointer(c1);

			curves.push_back(std::move(c0));

			curve = c1;
		}
		else
		{
			auto tang = std::dynamic_pointer_cast<Cad2d_IntsctEntity_TangSegment>(x);
			Debug_Null_Pointer(tang);

			if (subdivide::CalcLength(*tang, curve, CurveLength()) <= Tolerance())
			{// the entity is approximated as single point [2/9/2022 Amir]
				auto[c0, c1] = curve->Split(x->CharParameter());

				if (NOT c0)
				{
					continue;
				}

				if (NOT c1)
				{
					continue;
				}

				Debug_Null_Pointer(c0);
				Debug_Null_Pointer(c1);

				curves.push_back(std::move(c0));

				curve = c1;
			}
			else
			{
				auto[c0, c1, c2] = curve->Split(*tang);
				Debug_Null_Pointer(c1);

				if (c0)
				{
					curves.push_back(std::move(c0));
				}

				curves.push_back(std::move(c1));

				curve = c2;

				if (NOT curve)
				{
					break;
				}
			}
		}
	}

	if (curve)
	{
		curves.push_back(std::move(curve));
	}

	Change_IsDone() = Standard_True;
}