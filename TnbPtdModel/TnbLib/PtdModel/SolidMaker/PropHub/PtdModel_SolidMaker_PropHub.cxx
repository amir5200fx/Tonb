#include <PtdModel_SolidMaker_PropHub.hxx>

#include <PtdModel_Shape_PropHub.hxx>
#include <PtdModel_PropHub.hxx>
#include <PtdModel_HubFace.hxx>
#include <Cad_Shape.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo


#include <TopoDS_Shape.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS_Builder.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>

namespace tnbLib
{
	const Standard_Real ptdModel::SolidMaker_PropHub::DEFAULT_TOLERANCE(1.0E-6);
}

void tnbLib::ptdModel::SolidMaker_PropHub::Perform()
{
	const auto& hub = Hub();
	if (NOT hub)
	{
		FatalErrorIn(FunctionSIG)
			<< "no hub has been found!" << endl
			<< abort(FatalError);
	}

	const auto& faces = hub->Faces();
	if (faces.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "the face list is empty!" << endl
			<< abort(FatalError);
	}

	TopoDS_Compound compound;
	TopoDS_Builder builder;
	builder.MakeCompound(compound);

	for (const auto& x : faces)
	{
		Debug_Null_Pointer(x);

		const auto& geom = x->Surface();
		if (NOT geom)
		{
			FatalErrorIn(FunctionSIG)
				<< "null geometry of surface has been detected!" << endl
				<< abort(FatalError);
		}

		auto face = BRepBuilderAPI_MakeFace(geom, Tolerance());
		builder.Add(compound, face);
	}

	auto myShape = std::make_shared<Cad_Shape>(0, "hub", std::move(compound));
	auto myPropShape = std::make_shared<ptdModel::Shape_PropHub>(0, "hub", std::move(myShape));
	Debug_Null_Pointer(myPropShape);

	myPropShape->SetFaces(faces);

	SetShape(std::move(myPropShape));

	Change_IsDone() = Standard_True;
}