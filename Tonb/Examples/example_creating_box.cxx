#include <Tnb_Examples.hxx>

#include <Pnt3d.hxx>
#include <Cad3d_TModel.hxx>
#include <CadModel_Box.hxx>
#include <Cad_Tools.hxx>
#include <Cad_EntityManager.hxx>
#include <Cad_BlockEntity.hxx>

void tnbLib::example_creating_box()
{
	auto p0 = Pnt3d(0.1, -0.35, 0.08);
	auto p1 = Pnt3d(1.02, 0.47, 2.083);

	auto sh = CadModel_Box(p0, p1);

	auto solid = Cad_Tools::MakeSolid(sh.Entity(), 1.0E-6);
	Debug_Null_Pointer(solid);

	solid->Faces()->Print(Standard_True);

	auto& faces = solid->Faces();
	auto block = faces->SelectBlock("Default Block Surface");

	if (block IS_EQUAL faces->Blocks().end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the Block is not in the solid" << endl
			<< abort(FatalError);
	}

	std::vector<Standard_Integer> indices;
	indices.push_back(1);
	indices.push_back(3);
	auto b = block->second->Split(indices);
	Debug_Null_Pointer(b);

	faces->Import("Block 1", b);

	solid->Faces()->Print(Standard_True);

	block->second->MoveFrom(*b);
	faces->RemoveBlock(faces->SelectBlock("Block 1"));

	solid->Faces()->Print(Standard_True);
}