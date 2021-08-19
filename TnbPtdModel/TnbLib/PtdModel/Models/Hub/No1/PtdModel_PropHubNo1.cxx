#include <PtdModel_PropHubNo1.hxx>

#include <PtdModel_PropHubSection.hxx>
#include <PtdModel_HubCurves.hxx>
#include <PtdModel_HubFaces.hxx>
#include <Cad_Shape.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::PtdModel_PropHubNo1::PtdModel_PropHubNo1
(
	const std::shared_ptr<PtdModel_PropBlade>& theBlade, 
	const std::shared_ptr<PtdModel_PropHubPars>& thePars,
	const std::shared_ptr<PtdModel_PropHubSection>& theSection
)
	: PtdModel_PropHub(theBlade, thePars, theSection)
{
	//- empty body
}

tnbLib::PtdModel_PropHubNo1::PtdModel_PropHubNo1
(
	const Standard_Integer theIndex,
	const word & theName,
	const std::shared_ptr<PtdModel_PropBlade>& theBlade,
	const std::shared_ptr<PtdModel_PropHubPars>& thePars, 
	const std::shared_ptr<PtdModel_PropHubSection>& theSection
)
	: PtdModel_PropHub(theIndex, theName, theBlade, thePars, theSection)
{
	//- empty body
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <BRepPrimAPI_MakeRevolution.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS_Builder.hxx>
#include <Geom_Curve.hxx>
#include <Geom_SurfaceOfRevolution.hxx>
#include <gp_Ax1.hxx>

namespace tnbLib
{

	auto CreateFace(const std::shared_ptr<PtdModel_HubCurve>& theCurve, const gp_Ax1& ax)
	{
		Handle(Geom_SurfaceOfRevolution) surface = 
			new Geom_SurfaceOfRevolution(theCurve->Geometry(), ax);
		if (auto curve = std::dynamic_pointer_cast<ptdModel::HubCurve_Hub>(theCurve))
		{
			std::shared_ptr<PtdModel_HubFace> face = 
				std::make_shared<ptdModel::HubFace_Hub>(std::move(surface));
			return std::move(face);
		}
		else if (auto curve = std::dynamic_pointer_cast<ptdModel::HubCurve_Nose>(theCurve))
		{
			std::shared_ptr<PtdModel_HubFace> face = 
				std::make_shared<ptdModel::HubFace_Nose>(std::move(surface));
			return std::move(face);
		}
		else if (auto curve = std::dynamic_pointer_cast<ptdModel::HubCurve_Shaft>(theCurve))
		{
			std::shared_ptr<PtdModel_HubFace> face = 
				std::make_shared<ptdModel::HubFace_Shaft>(std::move(surface));
			return std::move(face);
		}
		else if (auto curve = std::dynamic_pointer_cast<ptdModel::HubCurve_Tail>(theCurve))
		{
			std::shared_ptr<PtdModel_HubFace> face = 
				std::make_shared<ptdModel::HubFace_Tail>(std::move(surface));
			return std::move(face);
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "unrecognized type of the hub curve has been detected!" << endl
				<< abort(FatalError);

			std::shared_ptr<PtdModel_HubFace> face;
			return face;
		}
	}
}

void tnbLib::PtdModel_PropHubNo1::Revolve()
{
	const auto& section = Section();
	if (NOT section)
	{
		FatalErrorIn(FunctionSIG)
			<< "no section has been loaded!" << endl
			<< abort(FatalError);
	}

	const auto curves = section->SectionCurves(*this);
	if (curves.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "no section curve has been found!" << endl
			<< abort(FatalError);
	}

	auto axis = gp_Ax1(gp_Pnt(0, 0, 0), gp::DZ());

	std::vector<std::shared_ptr<PtdModel_Face>> surfaces;
	surfaces.reserve(curves.size());

	for (const auto& x : curves)
	{
		auto face = CreateFace(x, axis);
		surfaces.push_back(std::move(face));
	}

	SetFaces(std::move(surfaces));
}