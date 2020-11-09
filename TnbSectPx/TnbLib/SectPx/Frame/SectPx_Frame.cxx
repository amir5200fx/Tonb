#include <SectPx_Frame.hxx>

#include <SectPx_Pnts.hxx>
#include <SectPx_Pars.hxx>
#include <SectPx_Registry.hxx>
#include <SectPx_Makers.hxx>
#include <SectPx_GeoMap_Intersection.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::SectPx_Frame::EntityMaker::EntityMaker
(
	const std::shared_ptr<SectPx_Registry>& theReg
)
{
	Par = std::make_shared<maker::Parameter>(theReg);
	Debug_Null_Pointer(Par);

	Pnt = std::make_shared<maker::Point>(theReg);
	Debug_Null_Pointer(Pnt);

	GeoMap = std::make_shared<maker::GeometricMap>(theReg);
	Debug_Null_Pointer(GeoMap);

	CmptProfile = std::make_shared<maker::CmptProfile>(theReg);
	Debug_Null_Pointer(CmptProfile);

	FieldFun = std::make_shared<maker::FieldFun>(theReg);
	Debug_Null_Pointer(FieldFun);
}

void tnbLib::SectPx_Frame::AllocateMemory()
{
	theRegistry_ = std::make_shared<SectPx_Registry>();
	Debug_Null_Pointer(theRegistry_);

	theMakers_ = std::make_shared<EntityMaker>(theRegistry_);
	Debug_Null_Pointer(theMakers_);
}

Standard_Integer 
tnbLib::SectPx_Frame::NbProfiles() const
{
	return CmptProfileMaker()->NbProfiles();
}

std::vector<std::shared_ptr<tnbLib::SectPx_ProfileQ>> 
tnbLib::SectPx_Frame::RetrieveProfilesQ() const
{
	std::vector<std::shared_ptr<SectPx_ProfileQ>> profiles;
	profiles.reserve(NbProfiles());

	for (const auto& x : CmptProfileMaker()->Profiles())
	{
		Debug_Null_Pointer(x.second);
		auto profile = x.second->RetrieveProfileQ();
		Debug_Null_Pointer(profile);
		profiles.push_back(std::move(profile));
	}
	return std::move(profiles);
}

std::map<std::string, std::shared_ptr<tnbLib::SectPx_FixedPar>> 
tnbLib::SectPx_Frame::RetrieveFixedParameters() const
{
	auto pars = ParameterMaker()->RetrieveFixedParameters();
	std::map<std::string, std::shared_ptr<SectPx_FixedPar>> parameters;
	for (const auto& x : pars)
	{
		Debug_Null_Pointer(x);

		auto fixed = std::dynamic_pointer_cast<SectPx_FixedPar>(x);
		Debug_Null_Pointer(fixed);

		auto paired = std::make_pair(x->Name(), std::move(fixed));
		auto insert = parameters.insert(std::move(paired));
		if (NOT insert.second)
		{
			FatalErrorIn(FunctionSIG)
				<< "duplicate data: " << x->Name() << endl
				<< abort(FatalError);
		}
	}
	return std::move(parameters);
}

void tnbLib::SectPx_Frame::MakeLineSegment()
{
	MakeLineSegment(Pnt2d(0, 0), Pnt2d(1, 1));
}

Standard_Integer 
tnbLib::SectPx_Frame::MakeLineSegment
(
	const Pnt2d & theP0,
	const Pnt2d & theP1
)
{
	const auto x0_id = ParameterMaker()->CreateConstant(theP0.X());
	const auto y0_id = ParameterMaker()->CreateConstant(theP0.Y());

	const auto x1_id = ParameterMaker()->CreateFixed(theP1.X());
	const auto y1_id = ParameterMaker()->CreateFixed(theP1.Y());

	const auto p0_id =
		PointMaker()->CreateOuterComponent
		(
			ParameterMaker()->SelectParameter(x0_id),
			ParameterMaker()->SelectParameter(y0_id)
		);
	const auto p1_id =
		PointMaker()->CreateOuterComponent
		(
			ParameterMaker()->SelectParameter(x1_id),
			ParameterMaker()->SelectParameter(y1_id)
		);

	const auto profMaker_id =
		CmptProfileMaker()->CreateCustomProfile
		(
			PointMaker()->SelectPnt(p0_id),
			PointMaker()->SelectPnt(p1_id)
		);
	return Registry()->LastId(SectPx_RegObjType::edge);
}

void tnbLib::SectPx_Frame::MakeCorner()
{
	MakeCorner(Pnt2d(0, 0), Pnt2d(1, 1));
}

void tnbLib::SectPx_Frame::MakeCorner
(
	const Pnt2d & theP0, 
	const Pnt2d & theP1
)
{
	MakeCorner(Pnt2d(0, 0), Dir2d(1, 0), 0, Pnt2d(1, 1), Dir2d(0, -1), 0);
}

void tnbLib::SectPx_Frame::MakeCorner
(
	const Pnt2d & theP0,
	const Dir2d & theDir0, 
	const Standard_Real theAngl0, 
	const Pnt2d & theP1, 
	const Dir2d & theDir1, 
	const Standard_Real theAngl1
)
{
	const auto x0_id = ParameterMaker()->CreateConstant(theP0.X());
	const auto y0_id = ParameterMaker()->CreateConstant(theP0.Y());

	const auto x1_id = ParameterMaker()->CreateFixed(theP1.X());
	const auto y1_id = ParameterMaker()->CreateFixed(theP1.Y());

	const auto angl0_id = ParameterMaker()->CreateFixed(theAngl0);
	const auto angl1_id = ParameterMaker()->CreateFixed(theAngl1);

	const auto p0_id =
		PointMaker()->CreateOuterComponent
		(
			ParameterMaker()->SelectParameter(x0_id),
			ParameterMaker()->SelectParameter(y0_id)
		);
	const auto p1_id =
		PointMaker()->CreateOuterComponent
		(
			ParameterMaker()->SelectParameter(x1_id),
			ParameterMaker()->SelectParameter(y1_id)
		);

	const auto profMaker_id =
		CmptProfileMaker()->CreateCustomProfile
		(
			PointMaker()->SelectPnt(p0_id),
			PointMaker()->SelectPnt(p1_id)
		);

	const auto profMaker = CmptProfileMaker()->SelectProfile(profMaker_id);
	const auto edge_id = Registry()->LastId(SectPx_RegObjType::edge);

	const auto geoMap_id = GeometricMapMaker()->CreateIntersection
	(
		PointMaker()->SelectPnt(p0_id), 
		theDir0, 
		ParameterMaker()->SelectParameter(angl0_id),
		PointMaker()->SelectPnt(p1_id),
		theDir1, 
		ParameterMaker()->SelectParameter(angl1_id)
	);

	const auto gPnt_id = 
		PointMaker()->CreateField
		(
			GeometricMapMaker()->SelectGeoMap(geoMap_id)
		);

	profMaker->ImportPnt
	(
		PointMaker()->SelectPnt(gPnt_id),
		profMaker->SelectEdge(edge_id)
	);
}

void tnbLib::SectPx_Frame::MakeUShape()
{
	MakeUShape(Pnt2d(0, 0), Pnt2d(1, 0), 0.5);
}

void tnbLib::SectPx_Frame::PrintRegistry() const
{
	Debug_Null_Pointer(Registry());
	Registry()->Print(Info);
}

void tnbLib::SectPx_Frame::MakeUShape
(
	const Pnt2d & theP0, 
	const Pnt2d & theP1, 
	const Standard_Real w
)
{
	const auto x0_id = ParameterMaker()->CreateConstant("x0", theP0.X());
	const auto y0_id = ParameterMaker()->CreateConstant("y0", theP0.Y());

	const auto x1_id = ParameterMaker()->CreateFixed("length", theP1.X());
	const auto y1_id = ParameterMaker()->CreateConstant("y1", theP1.Y());

	const auto w_id = ParameterMaker()->CreateFixed("width", w);

	const auto p0_id =
		PointMaker()->CreateOuterComponent
		(
			ParameterMaker()->SelectParameter(x0_id),
			ParameterMaker()->SelectParameter(y0_id)
		);
	const auto p1_id =
		PointMaker()->CreateOuterComponent
		(
			ParameterMaker()->SelectParameter(x1_id),
			ParameterMaker()->SelectParameter(y1_id)
		);

	const auto profMaker_id =
		CmptProfileMaker()->CreateCustomProfile
		(
			PointMaker()->SelectPnt(p0_id),
			PointMaker()->SelectPnt(p1_id)
		);

	const auto profMaker = CmptProfileMaker()->SelectProfile(profMaker_id);
	const auto edge_id = Registry()->LastId(SectPx_RegObjType::edge);

	const auto t2_id = ParameterMaker()->CreateFixed("mid", 0.5);
	const auto t3_id = ParameterMaker()->CreateFixed("left corner", 0);
	const auto t4_id = ParameterMaker()->CreateFixed("right corner", 1);



	const auto x0f_id = FieldFunMaker()->CreateReadingX(PointMaker()->SelectPnt(p0_id));
	const auto x1f_id = FieldFunMaker()->CreateReadingX(PointMaker()->SelectPnt(p1_id));
	const auto x2f_id = FieldFunMaker()->CreateLinearForm
	(
		FieldFunMaker()->SelectFieldFun(x0f_id),
		FieldFunMaker()->SelectFieldFun(x1f_id), 
		ParameterMaker()->SelectParameter(t2_id)
	);
	
	const auto x2_id = ParameterMaker()->CreateFree(FieldFunMaker()->SelectFieldFun(x2f_id));

	const auto p2_id = PointMaker()->CreateInnerComponent
	(
		ParameterMaker()->SelectParameter(x2_id), 
		ParameterMaker()->SelectParameter(w_id)
	);

	const auto read_x3f_id = FieldFunMaker()->CreateReadingX(PointMaker()->SelectPnt(p0_id));
	const auto read_x4f_id = FieldFunMaker()->CreateReadingX(PointMaker()->SelectPnt(p1_id));

	const auto x3f_id = FieldFunMaker()->CreateLinearForm
	(
		FieldFunMaker()->SelectFieldFun(read_x3f_id), 
		FieldFunMaker()->SelectFieldFun(x2f_id),
		ParameterMaker()->SelectParameter(t3_id)
	);
	const auto x4f_id = FieldFunMaker()->CreateLinearForm
	(
		FieldFunMaker()->SelectFieldFun(x2f_id),
		FieldFunMaker()->SelectFieldFun(read_x4f_id), 
		ParameterMaker()->SelectParameter(t4_id)
	);

	const auto x3_id = ParameterMaker()->CreateFree(FieldFunMaker()->SelectFieldFun(x3f_id));
	const auto x4_id = ParameterMaker()->CreateFree(FieldFunMaker()->SelectFieldFun(x4f_id));

	const auto p3_id = PointMaker()->CreateInnerComponent
	(
		ParameterMaker()->SelectParameter(x3_id), 
		ParameterMaker()->SelectParameter(w_id)
	);
	const auto p4_id = PointMaker()->CreateInnerComponent
	(
		ParameterMaker()->SelectParameter(x4_id),
		ParameterMaker()->SelectParameter(w_id)
	);

	const auto[left2, right2] = 
		profMaker->ImportPnt
		(
			PointMaker()->SelectPnt(p2_id),
			profMaker->SelectEdge(edge_id)
		);

	profMaker->ImportPnt(PointMaker()->SelectPnt(p3_id), profMaker->SelectEdge(left2));
	profMaker->ImportPnt(PointMaker()->SelectPnt(p4_id), profMaker->SelectEdge(right2));
}
