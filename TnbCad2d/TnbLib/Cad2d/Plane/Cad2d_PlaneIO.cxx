#include <Cad2d_Plane.hxx>

#include <Entity2d_Chain.hxx>
#include <Geo_Tools.hxx>
#include <Pln_Edge.hxx>
#include <Pln_CmpEdge.hxx>
#include <Pln_Wire.hxx>

std::shared_ptr<tnbLib::Entity2d_Chain>
tnbLib::Cad2d_Plane::Polygon() const
{
	Debug_Null_Pointer(OuterWire());
	Debug_Null_Pointer(OuterWire()->CmpEdge());

	auto chain_p = std::make_shared<Entity2d_Chain>();
	auto& chain = *chain_p;
	for (const auto& x : OuterWire()->CmpEdge()->Edges())
	{
		Debug_Null_Pointer(x);
		const auto& poly = x->Mesh();
		if (NOT poly)
		{
			FatalErrorIn(FunctionSIG)
				<< "the edge has no mesh!" << endl
				<< abort(FatalError);
		}

		auto ch = Geo_Tools::RetrieveChain(*poly);
		Debug_Null_Pointer(ch);

		chain.Add(*ch);
	}

	if (InnerWires())
	{
		for (const auto& wire : *InnerWires())
		{
			Debug_Null_Pointer(wire);
			Debug_Null_Pointer(wire->CmpEdge());
			for (const auto& x : wire->CmpEdge()->Edges())
			{
				Debug_Null_Pointer(x);
				const auto& poly = x->Mesh();
				if (NOT poly)
				{
					FatalErrorIn(FunctionSIG)
						<< "the edge has no mesh!" << endl
						<< abort(FatalError);
				}

				auto ch = Geo_Tools::RetrieveChain(*poly);
				Debug_Null_Pointer(ch);

				chain.Add(*ch);
			}
		}
	}
	return std::move(chain_p);
}

void tnbLib::Cad2d_Plane::ExportToPlt
(
	OFstream & File
) const
{
	Debug_Null_Pointer(OuterWire());
	OuterWire()->ExportToPlt(File);

	if (InnerWires())
	{
		for (const auto& x : *InnerWires())
		{
			Debug_Null_Pointer(x);
			x->ExportToPlt(File);
		}
	}
}

void tnbLib::Cad2d_Plane::ExportToPlt(std::stringstream& theStream) const
{
	Debug_Null_Pointer(OuterWire());
	OuterWire()->ExportToPlt(theStream);

	if (InnerWires())
	{
		for (const auto& x : *InnerWires())
		{
			Debug_Null_Pointer(x);
			x->ExportToPlt(theStream);
		}
	}
}

void tnbLib::Cad2d_Plane::ExportToVtk(OFstream& theFile) const
{
	Debug_Null_Pointer(OuterWire());
	OuterWire()->ExportToVtk(theFile);

	if (InnerWires())
	{
		for (const auto& x : *InnerWires())
		{
			Debug_Null_Pointer(x);
			x->ExportToVtk(theFile);
		}
	}
}

void tnbLib::Cad2d_Plane::ExportToVtk(std::stringstream& theStream) const
{
	Debug_Null_Pointer(OuterWire());
	OuterWire()->ExportToVtk(theStream);

	if (InnerWires())
	{
		for (const auto& x : *InnerWires())
		{
			Debug_Null_Pointer(x);
			x->ExportToVtk(theStream);
		}
	}
}

TNB_SAVE_IMPLEMENTATION(tnbLib::Cad2d_Plane)
{
	ar & boost::serialization::base_object<Pln_Entity>(*this);
	ar & boost::serialization::base_object<cad2dLib::Plane_Auxillary>(*this);
	ar & boost::serialization::base_object<cad2dLib::Plane_Manager>(*this);

	ar & theOuter_;
	ar & theInner_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Cad2d_Plane)
{
	ar & boost::serialization::base_object<Pln_Entity>(*this);
	ar & boost::serialization::base_object<cad2dLib::Plane_Auxillary>(*this);
	ar & boost::serialization::base_object<cad2dLib::Plane_Manager>(*this);

	ar & theOuter_;
	ar & theInner_;
}