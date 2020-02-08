#include <LegModel_DispNo1.hxx>

#include <Pnt2d.hxx>
#include <Dir2d.hxx>
#include <LegModel_DispNo1_System.hxx>
#include <Entity_Line.hxx>
#include <Entity2d_LineRef.hxx>

namespace tnbLib
{

	void Assemble
	(
		const Standard_Real xSection,
		const std::vector<Pnt2d>& Points,
		LegModel_SectionCtrlPts& Section
	)
	{
		auto& ctrls = Section.Points();
		ctrls.reserve(Points.size());
		for (auto& x : Points)
		{
			ctrls.push_back(Pnt3d(xSection, x.X(), x.Y()));
		}
	}

	std::vector<Pnt2d> UniformDiscretLine
	(
		const Pnt2d& P0,
		const Pnt2d& P1,
		const Standard_Integer NbSegments
	)
	{
		std::vector<Pnt2d> Points(NbSegments + 1);

		Standard_Real du = (Standard_Real)1. / (Standard_Real)NbSegments;
		Standard_Integer Index = 0;
		for (auto& x : Points)
		{
			x = P0 + (Standard_Real)Index * du * (P1 - P0);
			Index++;
		}
		return std::move(Points);
	}

	void UniformDistributionPoints
	(
		const Pnt2d& P0,
		const Pnt2d& P1,
		const Pnt2d& P2,
		const Standard_Integer NbWidth,
		const Standard_Integer NbHeight,
		Standard_Integer& Corner,
		std::vector<Pnt2d>& Points
	)
	{
		Standard_Integer
			K = 0;

		std::vector<Pnt2d> Inner;

		Inner = UniformDiscretLine
		(
			P0,
			P1,
			NbWidth + 1
		);

		forThose
		(
			Index,
			0,
			NbWidth + 1
		)
		{
			Points[K++] = Inner[Index];
		}

		Inner = UniformDiscretLine
		(
			P1,
			P2,
			NbHeight + 1
		);

		forThose
		(
			Index,
			1,
			NbHeight + 1
		)
		{
			Points[K++] = Inner[Index];
		}
	}


	void CalcNbControlPoints
	(
		const Standard_Real Width,
		const Standard_Real Height,
		Standard_Integer MaxPoints,
		Standard_Integer& NbWidth,
		Standard_Integer& NbHeight
	)
	{
		Standard_Integer Reserved = 3;

		MaxPoints -= Reserved;

		if (MaxPoints < 2)
		{
			FatalErrorIn(FunctionSIG)
				<< " Invalid Nb. of control points"
				<< abort(FatalError);
		}

		if (Height > Width)
		{
			NbWidth = (Standard_Integer)((Width / (Width + Height)) * (Standard_Real)MaxPoints);

			NbHeight = MaxPoints - NbWidth;
		}
		else
		{
			NbHeight = (Standard_Integer)((Height / (Width + Height)) * (Standard_Real)MaxPoints);

			NbWidth = MaxPoints - NbHeight;
		}
	}
}

std::shared_ptr<tnbLib::LegModel_SectionCtrlPts>
tnbLib::LegModel_DispNo1_HullPatch::CreateRawSection
(
	const Standard_Integer Section,
	const Standard_Integer nbWidth,
	const Standard_Integer nbHeight
)
{
	auto xSection = xXCoords[Section];
	auto zSection = xZCoords[Section];
	auto SideSlope = xSideSlope[Section];
	auto DeadRise = xDeadRise[Section];
	auto Width = xYCoords[Section];
	auto Height = xDepth[Section] - zSection /*+ theXParameters_.Sheer().Value(Section)*/;

	auto MaxSideSlope = atan(leg_DispNo1::MAX_SIDESLOPE_COEFF * Width / Height);
	auto SideSlopeAngle = SideSlope * MaxSideSlope;

	xSideSlopeAngle[Section] = SideSlopeAngle;

	Pnt2d P0(0, zSection);
	Pnt2d P2(Width, zSection + Height);

	auto MaxDeadRiseHeight = leg_DispNo1::MAX_DEADRISE_COEFF * Height;
	auto MaxDeadRiseAngle = atan(MaxDeadRiseHeight / Width);

	Dir2d t0(cos(DeadRise * MaxDeadRiseAngle), sin(DeadRise * MaxDeadRiseAngle));
	Dir2d t2(-sin(SideSlopeAngle), -cos(SideSlopeAngle));

	Entity2d_LineRef Line0(P0, t0);
	Entity2d_LineRef Line2(P2, t2);

	Pnt2d IP = gProcessor::Intersect(Line0, Line2, (Standard_Real)1.0E-12);

	auto Corner = nbWidth + 1;
	std::vector<Pnt2d> Points(NbNetRows());

	UniformDistributionPoints
	(
		P0,
		IP,
		P2,
		nbWidth,
		nbHeight,
		Corner,
		Points
	);

	auto newSection = std::make_shared<LegModel_CorneredSectionCtrlPts>();
	Assemble
	(
		xSection,
		Points,
		*newSection
	);
	newSection->Corner() = Corner;

	return std::move(newSection);
}

std::shared_ptr<tnbLib::LegModel_SectionCtrlPts>
tnbLib::LegModel_DispNo1_HullPatch::CreateRawStem() const
{
	auto Section = NbNetColumns() - 1;

	auto xSection = xXCoords[Section];
	auto Width = (Standard_Real)0.0;
	auto Height = DepthAtBow()->Value();

	Pnt2d P0;
	Pnt2d P1((Standard_Real)0.0, Height);

	auto MaxPoints = NbNetRows() - 1;

	std::vector<Pnt2d> Points = UniformDiscretLine
	(
		P0,
		P1,
		MaxPoints - 1
	);

	auto newSection = std::make_shared<LegModel_CorneredSectionCtrlPts>();
	Assemble
	(
		xSection,
		Points,
		*newSection
	);
	newSection->Corner() = 1;

	return std::move(newSection);
}

std::shared_ptr<tnbLib::LegModel_SectionCtrlPts>
tnbLib::LegModel_DispNo1_HullPatch::CreateRawStemPaired()
{
	auto Section = NbNetColumns() - 2;

	auto xSection = xXCoords[Section];
	auto ySection = xYCoords[Section];
	auto SideSlope = xSideSlope[Section];
	auto Height = DepthAtBow()->Value();

	auto MaxSideSlope = atan(leg_DispNo1::MAX_SIDESLOPE_COEFF * ySection / Height);
	auto SideSlopeAngle = SideSlope * MaxSideSlope;

	xSideSlopeAngle[Section] = SideSlopeAngle;

	auto dy = tan(SideSlopeAngle) * Height;
	auto y0 = MIN(ySection, ySection - dy);

	y0 = MAX(y0, ySection * leg_DispNo1::MIN_DIST_COEFF);

	Pnt2d P0(y0, (Standard_Real)0.0);
	Pnt2d P1(ySection, Height);

	auto MaxPoints = NbNetRows() - 1;

	std::vector<Pnt2d> Points = UniformDiscretLine(P0, P1, MaxPoints - 1);

	auto newSection = std::make_shared<LegModel_CorneredSectionCtrlPts>();
	Assemble
	(
		xSection,
		Points,
		*newSection
	);
	newSection->Corner() = 1;

	return std::move(newSection);
}

void tnbLib::LegModel_DispNo1_HullPatch::CreateRawSections()
{
	const LegModel_DispNo1_Dimensions& dimensions = *this;

	auto NbSections = dimensions.NbNetColumns();
	Standard_Integer
		NbWidth,
		NbHeight;

	CalcNbControlPoints
	(
		dimensions.BeamOnDeck()->Value(),
		MEAN(dimensions.DepthAtBow()->Value(), dimensions.DepthAtTransom()->Value()),
		dimensions.NbNetRows(),
		NbWidth,
		NbHeight
	);

	if (NbHeight < 0 || NbWidth < 0)
	{
		FatalErrorIn(FunctionSIG)
			<< " Invalid Nb. of Inner control points"
			<< abort(FatalError);
	}

	forThose
	(
		Section,
		0,
		NbSections - 3
	)
	{
		SetSection
		(
			Section,
			CreateRawSection(Section, NbWidth, NbHeight)
		);
	}

	SetSection(NbSections - 2, CreateRawStemPaired());
	SetSection(NbSections - 1, CreateRawStem());
}