#include <PtdModel_SolidMaker_PropBlades.hxx>

#include <PtdModel_Shape_PropBladeParent.hxx>
#include <PtdModel_Shape_PropBladeChild.hxx>
#include <PtdModel_Shape_PropBlades.hxx>
#include <Cad_Shape.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo


#include <corecrt_math_defines.h>

#include <gp_Trsf.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS_Builder.hxx>

namespace tnbLib
{
	Standard_Integer tnbLib::ptdModel::SolidMaker_PropBlades::DEFAULT_NB_BLADES(4);
}

void tnbLib::ptdModel::SolidMaker_PropBlades::Perform()
{
	if (NbBlades() < 2)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid nb. of blades has been detected!" << endl
			<< " nb. of blades: " << NbBlades() << endl
			<< abort(FatalError);
	}

	const auto& parent = Blade();
	if (NOT parent)
	{
		FatalErrorIn(FunctionSIG)
			<< "no parent blade has been found!" << endl
			<< abort(FatalError);
	}

	const auto& bladeShape = parent->Shape();
	if (NOT bladeShape)
	{
		FatalErrorIn(FunctionSIG)
			<< "no shape has been found!" << endl
			<< abort(FatalError);
	}

	const auto& ax = parent->Axis().Axis();

	const auto dTheta = 2.0*M_PI / (Standard_Real)NbBlades();

	TopoDS_Compound compound;
	TopoDS_Builder builder;

	builder.MakeCompound(compound);

	builder.Add(compound, bladeShape->Shape());

	std::vector<std::shared_ptr<ptdModel::Shape_PropBlade>> children;
	children.reserve(NbBlades() - 1);

	auto blades = std::make_shared<ptdModel::Shape_PropBlades>();
	Debug_Null_Pointer(blades);

	for (size_t blade = 1; blade < NbBlades(); blade++)
	{
		gp_Trsf rotate;
		rotate.SetRotation(ax, blade * dTheta);

		BRepBuilderAPI_Transform transf(rotate);
		transf.Perform(bladeShape->Shape(), Standard_True);

		auto shape = std::make_shared<Cad_Shape>(transf.Shape());
		auto child = std::make_shared<ptdModel::Shape_PropBladeChild>(0, "blade nb. " + std::to_string(blade), std::move(shape));
		children.push_back(std::move(child));

		builder.Add(compound, transf.Shape());
	}

	blades->SetParent(parent);
	blades->SetChildren(std::move(children));

	auto myBladesShape = std::make_shared<Cad_Shape>(0, "blades", std::move(compound));
	blades->SetShape(std::move(myBladesShape));

	theShape_ = std::move(blades);

	Change_IsDone() = Standard_True;
}