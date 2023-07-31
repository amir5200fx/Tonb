#include <Cad2d_Plane.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Edge.hxx>
#include <Cad_EntityManager.hxx>
#include <Cad_BlockEntity.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static std::shared_ptr<Cad2d_Plane> myPlane;

	TNB_STANDARD_LOAD_SAVE_OBJECTS("model");
	TNB_STANDARD_LOAD_SAVE_POINTER_OBJECT(myPlane, model_directory, myPlane);

	void checkLoad()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model is loaded!" << endl
				<< abort(FatalError);
		}
	}

	void printNbCorners()
	{
		checkLoad();
		Info << endl
			<< " - nb. of corners: " << myPlane->NbCorners() << endl;
	}

	void printNbSegments()
	{
		checkLoad();
		Info << endl
			<< " - nb. of segments: " << myPlane->NbSegments() << endl;
	}

	const auto& getCorners()
	{
		checkLoad();
		return myPlane->Corners();
	}

	const auto& getSegments()
	{
		checkLoad();
		return myPlane->Segments();
	}

	void printBlocks(const std::shared_ptr<Cad_EntityManager<Pln_Vertex>>& manager)
	{
		Info << endl
			<< " - list of the corners:" << endl;
		auto blocks = manager->Blocks();
		for (const auto& x : blocks)
		{
			Info << x.first << endl;
		}
	}

	void printBlocks(const std::shared_ptr<Cad_EntityManager<Pln_Edge>>& manager)
	{
		Info << endl
			<< " - list of the segments:" << endl;
		auto blocks = manager->Blocks();
		for (const auto& x : blocks)
		{
			Info << x.first << endl;
		}
	}

	auto selectBlock(const std::shared_ptr<Cad_EntityManager<Pln_Vertex>>& manager, const std::string& name)
	{
		auto iter = manager->SelectBlock(name);
		if (iter IS_EQUAL manager->Blocks().end())
		{
			FatalErrorIn(FunctionSIG)
				<< " the item is not in the map!" << endl
				<< " - Name: " << name << endl
				<< abort(FatalError);
		}
		return std::move(iter);
	}

	auto selectBlock(const std::shared_ptr<Cad_EntityManager<Pln_Edge>>& manager, const std::string& name)
	{
		auto iter = manager->SelectBlock(name);
		if (iter IS_EQUAL manager->Blocks().end())
		{
			FatalErrorIn(FunctionSIG)
				<< " the item is not in the map!" << endl
				<< " - Name: " << name << endl
				<< abort(FatalError);
		}
		return std::move(iter);
	}

	void combineBlocks(const std::shared_ptr<Cad_EntityManager<Pln_Edge>>& manager, const std::vector<std::string>& blocks, const std::string& name)
	{
		std::vector<std::map<word, std::shared_ptr<Cad_BlockEntity<Pln_Edge>>>::const_iterator> blockIters;
		for (const auto& x : blocks)
		{
			blockIters.push_back(manager->SelectBlock(x));
		}
		manager->CombineBlocks(blockIters, name);
	}

	void combineBlocks(const std::shared_ptr<Cad_EntityManager<Pln_Vertex>>& manager, const std::vector<std::string>& blocks, const std::string& name)
	{
		std::vector<std::map<word, std::shared_ptr<Cad_BlockEntity<Pln_Vertex>>>::const_iterator> blockIters;
		for (const auto& x : blocks)
		{
			blockIters.push_back(manager->SelectBlock(x));
		}
		manager->CombineBlocks(blockIters, name);
	}

	void printEntities(const std::shared_ptr<Cad_BlockEntity<Pln_Vertex>>& block)
	{
		Info << endl
			<< " - list of the vertices: " << endl;
		auto entities = block->RetrieveEntities();
		for (const auto& x : entities)
		{
			Info << " id: " << x->Index() << ", name: " << x->Name() << endl;
		}
	}

	void printEntities(const std::map<word, std::shared_ptr<Cad_BlockEntity<Pln_Vertex>>>::const_iterator& block)
	{
		printEntities(block->second);
	}

	void printEntities(const std::shared_ptr<Cad_BlockEntity<Pln_Edge>>& block)
	{
		Info << endl
			<< " - list of the segments: " << endl;
		auto entities = block->RetrieveEntities();
		for (const auto& x : entities)
		{
			Info << " id: " << x->Index() << ", name: " << x->Name() << endl;
		}
	}

	void printEntities(const std::map<word, std::shared_ptr<Cad_BlockEntity<Pln_Edge>>>::const_iterator& block)
	{
		printEntities(block->second);
	}

	auto selectEntity(const std::shared_ptr<Cad_BlockEntity<Pln_Vertex>>& block, int key)
	{
		auto iter = block->SelectEntity(key);
		if (iter IS_EQUAL block->Entities().end())
		{
			FatalErrorIn(FunctionSIG)
				<< "the item is not in the map!" << endl
				<< " - key: " << key << endl
				<< abort(FatalError);
		}
		return std::move(iter);
	}

	auto selectEntity(const std::shared_ptr<Cad_BlockEntity<Pln_Edge>>& block, int key)
	{
		auto iter = block->SelectEntity(key);
		if (iter IS_EQUAL block->Entities().end())
		{
			FatalErrorIn(FunctionSIG)
				<< "the item is not in the map!" << endl
				<< " - key: " << key << endl
				<< abort(FatalError);
		}
		return std::move(iter);
	}

	void splitBlock(const std::shared_ptr<Cad_BlockEntity<Pln_Vertex>>& block, const std::vector<int>& ids, const std::string& name)
	{
		auto newBlock = block->Split(name, ids);
		getCorners()->Import(name, newBlock);
	}

	void splitBlock(const std::map<word, std::shared_ptr<Cad_BlockEntity<Pln_Vertex>>>::const_iterator& block, const std::vector<int>& ids, const std::string& name)
	{
		splitBlock(block->second, ids, name);
	}

	void splitBlock(const std::shared_ptr<Cad_BlockEntity<Pln_Edge>>& block, const std::vector<int>& ids, const std::string& name)
	{
		auto newBlock = block->Split(name, ids);
		getSegments()->Import(name, newBlock);
	}

	void splitBlock(const std::map<word, std::shared_ptr<Cad_BlockEntity<Pln_Edge>>>::const_iterator& block, const std::vector<int>& ids, const std::string& name)
	{
		auto iter = block->second;
		splitBlock(iter, ids, name);
	}

	void renameBlock(const std::map<word, std::shared_ptr<Cad_BlockEntity<Pln_Edge>>>::const_iterator& block, const std::string& name)
	{
		getSegments()->ReNameBlock(block, name);
	}

	void renameBlock(const std::map<word, std::shared_ptr<Cad_BlockEntity<Pln_Vertex>>>::const_iterator& block, const std::string& name)
	{
		getCorners()->ReNameBlock(block, name);
	}

	void compactBlocks(const std::shared_ptr<Cad_EntityManager<Pln_Edge>>& manager, const std::string& name)
	{
		manager->CompactBlocks(name);
	}

	void compactBlocks(const std::shared_ptr<Cad_EntityManager<Pln_Edge>>& manager, const std::map<word, std::shared_ptr<Cad_BlockEntity<Pln_Edge>>>::const_iterator& block)
	{
		manager->CompactBlocksWith(block);
	}

	void compactBlocks(const std::shared_ptr<Cad_EntityManager<Pln_Vertex>>& manager, const std::string& name)
	{
		manager->CompactBlocks(name);
	}

	void compactBlocks(const std::shared_ptr<Cad_EntityManager<Pln_Vertex>>& manager, const std::map<word, std::shared_ptr<Cad_BlockEntity<Pln_Vertex>>>::const_iterator& block)
	{
		manager->CompactBlocksWith(block);
	}

	void execute()
	{
		TNB_EXECUTE_TAG;
	}
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<chaiscript::Module> module_t;

	void setFunctions(const module_t& mod)
	{

		//- io functions
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadModel(name); }), "loadFile");
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");

		mod->add(chaiscript::fun([]()-> void {printNbCorners(); }), "printNbCorners");
		mod->add(chaiscript::fun([]()-> void {printNbSegments(); }), "printNbSegments");

		mod->add(chaiscript::fun([](const std::shared_ptr<Cad_EntityManager<Pln_Vertex>>& manager)-> void {printBlocks(manager); }), "printBlocks");
		mod->add(chaiscript::fun([](const std::shared_ptr<Cad_EntityManager<Pln_Edge>>& manager)-> void {printBlocks(manager); }), "printBlocks");

		mod->add(chaiscript::fun([]()-> void {printBlocks(getSegments()); }), "printSegmentBlocks");
		mod->add(chaiscript::fun([]()-> void {printBlocks(getCorners()); }), "printCornerBlocks");

		mod->add(chaiscript::fun([](const std::map<word, std::shared_ptr<Cad_BlockEntity<Pln_Edge>>>::const_iterator& block)-> void {printEntities(block); }), "printEntities");
		mod->add(chaiscript::fun([](const std::map<word, std::shared_ptr<Cad_BlockEntity<Pln_Vertex>>>::const_iterator& block)-> void {printEntities(block); }), "printEntities");

		//- operators

		mod->add(chaiscript::fun([]()-> const auto& {return getCorners(); }), "getCorners");
		mod->add(chaiscript::fun([]()-> const auto& {return getSegments(); }), "getSegments");

		mod->add(chaiscript::fun([](const std::shared_ptr<Cad_EntityManager<Pln_Vertex>>& manager, const std::string& name)-> auto {return selectBlock(manager, name); }), "selectBlock");
		mod->add(chaiscript::fun([](const std::shared_ptr<Cad_EntityManager<Pln_Edge>>& manager, const std::string& name)-> auto {return selectBlock(manager, name); }), "selectBlock");

		mod->add(chaiscript::fun([](const std::map<word, std::shared_ptr<Cad_BlockEntity<Pln_Edge>>>::const_iterator& block, const std::vector<int>& ids, const std::string& name)-> void {splitBlock(block, ids, name); }), "split");
		mod->add(chaiscript::fun([](const std::map<word, std::shared_ptr<Cad_BlockEntity<Pln_Vertex>>>::const_iterator& block, const std::vector<int>& ids, const std::string& name)-> void {splitBlock(block, ids, name); }), "split");

		mod->add(chaiscript::fun([](const std::shared_ptr<Cad_EntityManager<Pln_Edge>>& manager, const std::vector<std::string>& blocks, const std::string& name)-> void {combineBlocks(manager, blocks, name); }), "combine");
		mod->add(chaiscript::fun([](const std::shared_ptr<Cad_EntityManager<Pln_Vertex>>& manager, const std::vector<std::string>& blocks, const std::string& name)-> void {combineBlocks(manager, blocks, name); }), "combine");

		mod->add(chaiscript::fun([](const std::map<word, std::shared_ptr<Cad_BlockEntity<Pln_Edge>>>::const_iterator& block, const std::string& name)-> void {renameBlock(block, name); }), "rename");
		mod->add(chaiscript::fun([](const std::map<word, std::shared_ptr<Cad_BlockEntity<Pln_Vertex>>>::const_iterator& block, const std::string& name)-> void {renameBlock(block, name); }), "rename");

		mod->add(chaiscript::fun([](const std::shared_ptr<Cad_EntityManager<Pln_Edge>>& manager, const std::string& name)-> void {compactBlocks(manager, name); }), "compact");
		mod->add(chaiscript::fun([](const std::shared_ptr<Cad_EntityManager<Pln_Vertex>>& manager, const std::string& name)-> void {compactBlocks(manager, name); }), "compact");
		mod->add(chaiscript::fun([](const std::shared_ptr<Cad_EntityManager<Pln_Edge>>& manager, const std::map<word, std::shared_ptr<Cad_BlockEntity<Pln_Edge>>>::const_iterator& block)-> void {compactBlocks(manager, block); }), "compactWith");
		mod->add(chaiscript::fun([](const std::shared_ptr<Cad_EntityManager<Pln_Vertex>>& manager, const std::map<word, std::shared_ptr<Cad_BlockEntity<Pln_Vertex>>>::const_iterator& block)-> void {compactBlocks(manager, block); }), "compactWith");

		//- settings
		mod->add(chaiscript::fun([](unsigned short t)->void {setVerbose(t); }), "setVerbose");
	}

	std::string getString(char* argv)
	{
		std::string argument(argv);
		return std::move(argument);
	}

	Standard_Boolean IsEqualCommand(char* argv, const std::string& command)
	{
		auto argument = getString(argv);
		return argument IS_EQUAL command;
	}
}

using namespace tnbLib;

int main(int argc, char* argv[])
{
	if (argc <= 1)
	{
		Info << " - No command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

	execute();

	if (argc IS_EQUAL 2)
	{
		if (IsEqualCommand(argv[1], "--help"))
		{
			Info << " This application is aimed to manage the topology of a plane." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl
				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl
				<< " - setVerbose(unsigned int); Levels: 0, 1" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - printNbCorners()" << endl
				<< " - printNbSegments()" << endl << endl

				<< " - printSegmentBlocks()" << endl
				<< " - printCornerBlocks()" << endl << endl

				<< " - printBlocks(manager);         - manager: corners, segements" << endl
				<< " - printEntities(block);         - block: corners, segements" << endl

				<< endl
				<< " # Operators: " << endl << endl

				<< " - getCorners();                 - it gives the corner manager" << endl
				<< " - getSegments();                - it gives the segment manager" << endl << endl

				<< " - [manager].selectBlock(name);  - manager: corners, segements" << endl
				<< " - [manager].combine(block names, name);" << endl
				<< " - [manager].compact(name);" << endl
				<< " - [manager].compactWith(block); - block: corners, segements" << endl
				<< " - [block].rename(name);" << endl
				<< " - [block].split(ids, name); " << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			chai.add(chaiscript::bootstrap::standard_library::vector_type<std::vector<int>>("std_vector_int"));
			chai.add(chaiscript::vector_conversion<std::vector<int>>());

			chai.add(chaiscript::bootstrap::standard_library::vector_type<std::vector<std::string>>("std_vector_string"));
			chai.add(chaiscript::vector_conversion<std::vector<std::string>>());

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			try
			{
				auto address = file::GetSystemFile("tnbCadToolPlaneManager");
				fileName myFileName(address);

				chai.eval_file(myFileName);
				return 0;
			}
			catch (const chaiscript::exception::eval_error& x)
			{
				Info << x.pretty_print() << endl;
			}
			catch (const error& x)
			{
				Info << x.message() << endl;
			}
			catch (const std::exception& x)
			{
				Info << x.what() << endl;
			}
		}
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
	return 1;
}