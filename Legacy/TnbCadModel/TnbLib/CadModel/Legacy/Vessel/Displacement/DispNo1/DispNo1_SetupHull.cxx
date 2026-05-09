#include <LegModel_DispNo1.hxx>

#include <BSplCLib.hxx>
#include <Geom_BSplineSurface.hxx>
#include <TColStd_Array1OfReal.hxx>

void tnbLib::LegModel_DispNo1_HullPatch::SetupControlNet()
{
	Standard_Integer
		NbSections,
		NbRows,
		I = 0;

	NbSections = NbNetColumns();
	NbRows = NbNetRows();

	forThose
	(
		Section,
		0,
		NbSections - 1
	)
	{
		if (Section + 1 > NbSections - 2) I = 1;

		const auto& SectionPtr = xSection[Section];
		Debug_Null_Pointer(SectionPtr);

		const auto& ControlPoints = SectionPtr->Points();

		forThose
		(
			J,
			0,
			(NbRows - I) - 1
		)
		{
			SetControlPoint
			(
				Section,
				J + I,
				ControlPoints[J]
			);
		}
	}

	SetControlPoint(NbSections - 1, 0, CtrlNet->Value(NbSections, 2));
	SetControlPoint(NbSections - 2, 0, CtrlNet->Value(NbSections, 2));
}

namespace tnbLib
{

	static void UniformSurfaceMeshParameters
	(
		Standard_Integer nI,
		Standard_Integer nJ,
		std::vector<Standard_Real>& uKnots,
		std::vector<Standard_Real>& vKnots
	)
	{
		if (uKnots.size() != nI)
		{
			uKnots.resize(nI);
		}

		if (vKnots.size() != nJ)
		{
			vKnots.resize(nJ);
		}

		if (nI < 2)
		{
			FatalErrorIn(FunctionSIG)
				<< " Invalid Nb. of Control points in U direction"
				<< abort(FatalError);
		}

		if (nJ < 2)
		{
			FatalErrorIn(FunctionSIG)
				<< " Invalid Nb. of Control points in V direction"
				<< abort(FatalError);
		}

		auto du = (Standard_Real)1.0 / (Standard_Real)(nI - 1);
		auto dv = (Standard_Real)1.0 / (Standard_Real)(nJ - 1);

		uKnots[0] = (Standard_Real).0;

		forThose
		(
			Index,
			1,
			nI - 2
		)
		{
			uKnots[Index] = (Standard_Real)Index * du;
		}

		uKnots[nI - 1] = (Standard_Real)1.0;
		vKnots[0] = (Standard_Real).0;

		forThose
		(
			Index,
			1,
			nJ - 2
		)
		{
			vKnots[Index] = (Standard_Real)Index * dv;
		}
		vKnots[nJ - 1] = (Standard_Real)1.0;
	}

	static void SequenceKnots
	(
		const Standard_Integer Degree,
		const Standard_Integer MaxIndex,
		const std::vector<Standard_Real>& Parameters,
		std::vector<Standard_Real>& Knots
	)
	{
		Standard_Integer m = Degree + MaxIndex + 1;

		forThose
		(
			Index,
			0,
			Degree
		)
			Knots[Index] = (Standard_Real)0.0;

		forThose
		(
			Index,
			m - Degree,
			m
		)
			Knots[Index] = (Standard_Real)1.0;

		auto InvDegree =
			(Standard_Real)1.0 / (Standard_Real)Degree;

		forThose
		(
			Index,
			1,
			MaxIndex - Degree
		)
		{
			Standard_Real Sigma = (Standard_Real)0.0;

			forThose(i, Index, Index + Degree - 1)
				Sigma += Parameters[i];

			Knots[Index + Degree] = InvDegree * Sigma;
		}
	}
}

void tnbLib::LegModel_DispNo1_HullPatch::SetupPatch()
{
	std::vector<Standard_Real>
		uParameters,
		vParameters;

	Standard_Integer
		uDegree,
		vDegree,
		uMaxIndex,
		vMaxIndex;

	auto NbSections = NbNetColumns();
	auto NbRows = NbNetRows();

	UniformSurfaceMeshParameters
	(
		NbSections,
		NbRows,
		uParameters,
		vParameters
	);

	uDegree = vDegree = 3;

	uMaxIndex = NbSections - 1;
	vMaxIndex = NbRows - 1;

	std::vector<Standard_Real>
		uKnots(uMaxIndex + uDegree + 2),
		vKnots(vMaxIndex + vDegree + 2);

	SequenceKnots
	(
		uDegree,
		uMaxIndex,
		uParameters,
		uKnots
	);

	SequenceKnots
	(
		vDegree,
		vMaxIndex,
		vParameters,
		vKnots
	);

	TColStd_Array1OfReal Seq_uKnots(1, (Standard_Integer)uKnots.size());
	TColStd_Array1OfReal Seq_vKnots(1, (Standard_Integer)vKnots.size());

	forThose(Index, 0, uKnots.size() - 1)
		Seq_uKnots.SetValue(Index + 1, uKnots[Index]);

	forThose(Index, 0, vKnots.size() - 1)
		Seq_vKnots.SetValue(Index + 1, vKnots[Index]);

	auto uLength = BSplCLib::KnotsLength(Seq_uKnots);
	auto vLength = BSplCLib::KnotsLength(Seq_vKnots);

	TColStd_Array1OfReal uKnotVector(1, uLength);
	TColStd_Array1OfReal vKnotVector(1, vLength);
	TColStd_Array1OfInteger uMult(1, uLength);
	TColStd_Array1OfInteger vMult(1, vLength);

	BSplCLib::Knots(Seq_uKnots, uKnotVector, uMult);
	BSplCLib::Knots(Seq_vKnots, vKnotVector, vMult);

	Standard_Real ulMax = 0;
	Standard_Real vlMax = 0;

	const auto& Q = *CtrlNet;

	forThose
	(
		Section,
		1,
		NbSections
	)
	{
		Standard_Real vl = 0;
		forThose
		(
			J,
			2,
			NbRows
		)
		{
			const auto& P0 = Q.Value(Section, J - 1);
			const auto& P1 = Q.Value(Section, J);

			vl += P0.Distance(P1);
		}

		if (vl > vlMax) vlMax = vl;
	}

	forThose
	(
		J,
		1,
		NbRows
	)
	{
		Standard_Real ul = 0;
		forThose
		(
			Section,
			2,
			NbSections
		)
		{
			const auto& P0 = Q.Value(Section - 1, J);
			const auto& P1 = Q.Value(Section, J);

			ul += P0.Distance(P1);
		}

		if (ul > ulMax) ulMax = ul;
	}

	for (auto& x : uKnotVector)
		x *= ulMax;
	for (auto& x : vKnotVector)
		x *= vlMax;

	theHull_ =
		new Geom_BSplineSurface
		(
			*CtrlNet,
			uKnotVector,
			vKnotVector,
			uMult, vMult, uDegree, vDegree);
}