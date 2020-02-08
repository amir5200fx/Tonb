#include <LegModel_DispNo1.hxx>

#include <Pnt2d.hxx>
#include <UnitSystem.hxx>
#include <LegModel_SectionCtrlPts.hxx>

#include <Geom2d_Line.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>

void tnbLib::LegModel_DispNo1_HullPatch::ApplyTightness()
{
	const LegModel_DispNo1_Dimensions& dimension = *this;

	forThose
	(
		Section,
		0,
		dimension.NbNetColumns() - 3
	)
	{
		auto section = std::dynamic_pointer_cast<LegModel_CorneredSectionCtrlPts>(xSection[Section]);
		Debug_Null_Pointer(section);

		ApplyTightness
		(
			*section,
			xTightness[Section]
		);
	}
}

void tnbLib::LegModel_DispNo1_HullPatch::ApplyFlare()
{
	const LegModel_DispNo1_Dimensions& dimension = *this;

	forThose
	(
		Section,
		0,
		dimension.NbNetColumns() - 3
	)
	{
		ApplyFlare(Section);
	}
}

void tnbLib::LegModel_DispNo1_HullPatch::ApplyRake()
{
	const LegModel_DispNo1_Dimensions& dimension = *this;

	forThose
	(
		Section,
		0,
		dimension.NbNetColumns() - 1
	)
	{
		auto section = std::dynamic_pointer_cast<LegModel_CorneredSectionCtrlPts>(xSection[Section]);
		Debug_Null_Pointer(section);

		ApplyRake
		(
			*section,
			xRake[Section]
		);
	}
}

void tnbLib::LegModel_DispNo1_HullPatch::ApplyForeFootShape()
{
	const LegModel_DispNo1_Dimensions& dimensions = *this;
	const LegModel_DispNo1_StemParams& Stem = *this;

	auto NbSections = dimensions.NbNetColumns();

	auto& ControlPoints1 = (*xSection[NbSections - 1]).Points();
	auto& ControlPoints3 = (*xSection[NbSections - 3]).Points();

	auto Root = ControlPoints1[0];

	auto P1 = ControlPoints1[1];
	auto P2 = ControlPoints3[0];

	auto NewP1 = Root + Stem.ForeFootShape()->Value() * (P1 - Root);
	auto NewP2 = Root + Stem.ForeFootShape()->Value() * (P2 - Root);

	ControlPoints1[1] = NewP1;

	ControlPoints1[0] = MEAN
	(
		NewP1,
		NewP2
	);

	Standard_Real
		dx,
		dz,
		zMax;

	dx = NewP2.X() - ControlPoints3[0].X();

	zMax = ControlPoints3[ControlPoints3.size() - 1].Z();

	forThose_Dec
	(
		Index,
		(Standard_Integer)ControlPoints3.size() - 2,
		0
	)
	{
		dz = zMax - ControlPoints3[Index].Z();

		ControlPoints3[Index].X() += (dz / zMax) * dx;
	}

	auto& ControlPoints2 = (*xSection[NbSections - 2]).Points();

	auto y1 = ControlPoints2[1].Y();

	ControlPoints2[0] = ControlPoints1[0];
	ControlPoints2[1] = ControlPoints1[1];

	ControlPoints2[1].Y() = y1;
	ControlPoints2[0].Y() = MEAN(ControlPoints3[1].Y(), y1);
}

void tnbLib::LegModel_DispNo1_HullPatch::ApplyParameters()
{
	CreateFlareProfile();

	ApplyTightness();

	ApplyFlare();

	ApplyRake();

	ApplyForeFootShape();
}

void tnbLib::LegModel_DispNo1_HullPatch::ApplyTightness
(
	LegModel_CorneredSectionCtrlPts & theSection, 
	const Standard_Real theTightness
)
{
	Pnt3d
		crit_point1,
		crit_point2,
		new_pos1,
		new_pos2,
		p2;

	Standard_Real
		t,
		du,
		dv;

	auto nbctrlpts =
		(Standard_Integer)theSection.Points().size();
	auto Corner =
		theSection.Corner();

	Standard_Integer
		nx,
		ny;

	nx = Corner - 1;
	du = (Standard_Real)1. / (Standard_Real)nx;

	ny = (nbctrlpts - 1) - Corner - 1;
	dv = (Standard_Real)1. / (Standard_Real)ny;

	auto& ControlPoints = theSection.Points();

	if (theTightness <= (Standard_Real)0.5)
	{
		crit_point1 = ControlPoints[1];
		crit_point2 = ControlPoints[nbctrlpts - 2];

		p2 = ControlPoints[Corner];

		t = (Standard_Real)1. - (Standard_Real)2.0 * theTightness;

		new_pos1 =
			crit_point1 + t * (p2 - crit_point1);

		forThose
		(
			Index,
			0,
			nx - 1
		)
		{
			ControlPoints[Index + 1] =
				new_pos1 + Index * du * (p2 - new_pos1);
		}

		new_pos2 = crit_point2 + t * (p2 - crit_point2);

		forThose
		(
			Index,
			0,
			ny - 1
		)
		{
			ControlPoints[nbctrlpts - Index - 2] =
				new_pos2 + Index * dv * (p2 - new_pos2);
		}
	}
	else
	{
		crit_point1 = ControlPoints[Corner - 1];
		crit_point2 = ControlPoints[Corner + 1];

		p2 = ControlPoints[0];

		t = (Standard_Real)2.0 * (theTightness - (Standard_Real)0.5);

		new_pos1 =
			crit_point1 + t * (p2 - crit_point1);

		forThose
		(
			Index,
			0,
			nx - 1
		)
		{
			ControlPoints[Corner - Index - 1] =
				new_pos1 + Index * du * (p2 - new_pos1);
		}

		p2 = ControlPoints[nbctrlpts - 1];

		new_pos2 = crit_point2 + t * (p2 - crit_point2);

		forThose
		(
			Index,
			0,
			ny - 1
		)
		{
			ControlPoints[Corner + Index + 1] =
				new_pos2 + Index * dv * (p2 - new_pos2);
		}
	}
}

void tnbLib::LegModel_DispNo1_HullPatch::ApplyFlare
(
	Standard_Integer Index
)
{
	if (xSection[Index] == NULL)
	{
		FatalErrorIn(FunctionSIG)
			<< " Empty Section"
			<< abort(FatalError);
	}

	auto section = std::dynamic_pointer_cast<LegModel_CorneredSectionCtrlPts>(xSection[Index]);
	Debug_Null_Pointer(section);
	auto& Section = *section;

	auto Corner = Section.Corner();
	auto NbPoints = (Standard_Integer)Section.Points().size();

	auto& CtrlPoints = Section.Points();

	if (Flares[Index].IsNull())
	{
		FatalErrorIn(FunctionSIG)
			<< " Found no Flare Profile for section "
			<< Index
			<< abort(FatalError);
	}

	Standard_Real zSection;
	Geom2dAPI_InterCurveCurve Intersection;

	forThose
	(
		J,
		Corner + 1,
		NbPoints - 2
	)
	{
		zSection = CtrlPoints[J].Z();

		Handle(Geom2d_Line) Line =
			new Geom2d_Line(gp_Pnt2d(0, zSection), gp_Vec2d(1, 0));

		Intersection.Init(Flares[Index], Line, 1.0e-6);

		if (NOT Intersection.NbPoints())
		{
			FatalErrorIn(FunctionSIG)
				<< " No Intersection has been found"
				<< abort(FatalError);
		}

		if (Intersection.NbPoints() != 1)
		{
			FatalErrorIn(FunctionSIG)
				<< " More than one intersection point has been found"
				<< abort(FatalError);
		}

		Pnt2d IP = Intersection.Point(1);

		CtrlPoints[J] =
			Pnt3d(CtrlPoints[J].X(), IP.X(), IP.Y());
	}
}

void tnbLib::LegModel_DispNo1_HullPatch::ApplyRake
(
	LegModel_CorneredSectionCtrlPts& theSection,
	const Standard_Real theRake
)
{
	auto NbPoints = (Standard_Integer)theSection.Points().size();
	auto& ControlPoints = theSection.Points();

	Standard_Real
		zSection,
		dx,
		dz;

	zSection = ControlPoints[NbPoints - 1].Z();

	dx = zSection * tan((Standard_Real)ConvertUnit(UnitSystem_Angle_deg, UnitSystem_Angle_rad) * theRake);

	forThose_Dec
	(
		Row,
		NbPoints - 2,
		0
	)
	{
		dz = zSection - ControlPoints[Row].Z();
		ControlPoints[Row].X() -= (dz / zSection) * dx;
	}
}