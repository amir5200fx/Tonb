#include <TModel_Surface.hxx>

#include <TModel_Wire.hxx>
#include <TModel_GeneratedEdge.hxx>
#include <TModel_ParaCurve.hxx>
#include <Pln_Tools.hxx>
#include <Entity2d_Polygon.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::TModel_Surface)
{
	ar & boost::serialization::base_object<TModel_Entity>(*this);
	ar & boost::serialization::base_object<GModel_SurfaceGeometry>(*this);

	ar & theOuter_;
	ar & theInner_;

	ar & theParaBoundingBox_;

	ar & theOrientation_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::TModel_Surface)
{
	ar & boost::serialization::base_object<TModel_Entity>(*this);
	ar & boost::serialization::base_object<GModel_SurfaceGeometry>(*this);

	ar & theOuter_;
	ar & theInner_;

	ar & theParaBoundingBox_;

	ar & theOrientation_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::TModel_Surface);

void tnbLib::TModel_Surface::ExportPlaneCurvesToPlt(OFstream& File) const
{
	static const Standard_Integer nbSegs = 40;
	const auto& outer = Outer();
	if (NOT outer)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid surface has been detected: " << endl
			<< " - the surface has no outer boundary!" << endl
			<< abort(FatalError);
	}
	auto edges = outer->Edges();
	Debug_Null_Pointer(edges);
	for (const auto& x : *edges)
	{
		const auto& c = x->ParaCurve();
		Debug_Null_Pointer(c);
		auto pl = Pln_Tools::UniformDiscrete(c->Curve(), nbSegs);
		Debug_Null_Pointer(pl);
		pl->ExportToPlt(File);
	}

	if (Inner())
	{// Plot inner boundaries [12/12/2022 Payvand]
		for (const auto& x : *Inner())
		{
			auto edges = x->Edges();
			Debug_Null_Pointer(edges);
			for (const auto& e : *edges)
			{
				const auto& c = e->ParaCurve();
				Debug_Null_Pointer(c);
				auto pl = Pln_Tools::UniformDiscrete(c->Curve(), nbSegs);
				Debug_Null_Pointer(pl);
				pl->ExportToPlt(File);
			}
		}
	}
}