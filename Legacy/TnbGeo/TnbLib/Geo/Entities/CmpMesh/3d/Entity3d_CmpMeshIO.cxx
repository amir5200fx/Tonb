#include <Entity3d_CmpMesh.hxx>

#include <Entity3d_PolyhedralMesh.hxx>
#include <Entity3d_CmpConnect_Brick.hxx>
#include <Entity3d_CmpConnect_Prism.hxx>
#include <Entity3d_CmpConnect_Tetrahedron.hxx>
#include <Entity3d_CmpConnect_Pyramid.hxx>
#include <Entity3d_Tetrahedralization.hxx>
#include <Entity3d_Hexahedralization.hxx>

void tnbLib::Entity3d_CmpMesh::ExportToPlt(OFstream& theFile) const
{
	auto coords = theCoords_;
	Standard_Integer max_size = 0;
	for (const auto& i: theIndices_)
	{
		if (i->NbCmpts() > max_size)
		{
			max_size = i->NbCmpts();
		}
	}
	if (max_size == 4)
	{
		std::vector<connectivity::quadruple> indices;
		indices.reserve(theIndices_.size());
		for (const auto& i: theIndices_)
		{
			auto components = i->Components();
			connectivity::quadruple q;
			q.Value(0) = components.at(0);
			q.Value(1) = components.at(1);
			q.Value(2) = components.at(2);
			q.Value(3) = components.at(3);
			indices.push_back(std::move(q));
		}
		auto tet = std::make_shared<Entity3d_Tetrahedralization>
		(std::move(coords), std::move(indices));
		Debug_Null_Pointer(tet);
		tet->ExportToPlt(theFile);
	}
	else if (max_size == 6)
	{
		NotImplemented;
	}
	else if (max_size == 8)
	{
		std::vector<connectivity::octuple> indices;
		indices.reserve(theIndices_.size());
		for (const auto& i: theIndices_)
		{
			auto components = i->Components();
			connectivity::octuple oct;
			if (components.size() == 4)
			{
				
			}
			else if (components.size() == 6)
			{
				oct.Value(0) = components.at(0);
				oct.Value(1) = components.at(1);
				oct.Value(2) = components.at(2);
				oct.Value(3) = components.at(2);

				oct.Value(4) = components.at(3);
				oct.Value(5) = components.at(4);
				oct.Value(6) = components.at(5);
				oct.Value(7) = components.at(5);
			}
			else if (components.size() == 8)
			{
				oct.Value(0) = components.at(0);
				oct.Value(1) = components.at(1);
				oct.Value(2) = components.at(2);
				oct.Value(3) = components.at(3);

				oct.Value(4) = components.at(4);
				oct.Value(5) = components.at(5);
				oct.Value(6) = components.at(6);
				oct.Value(7) = components.at(7);
			}
			indices.push_back(std::move(oct));
		}
		const auto hex = std::make_shared<Entity3d_Hexahedralization>(std::move(coords), std::move(indices));
		Debug_Null_Pointer(hex);
		hex->ExportToPlt(theFile);
	}
	else
	{
		FatalErrorIn(FunctionSIG) << "\n"
			<< "Unspecified type of element has been detected." << "\n"
			<< " - Size: " << max_size << "\n"
			<< abort(FatalError);
	}
}

void tnbLib::Entity3d_CmpMesh::ExportToVtk(std::fstream& outfile) const
{
	Entity3d_PolyhedralMesh polyhedral;
	polyhedral.Import(*this);
	polyhedral.ExportToVtk(outfile);
}