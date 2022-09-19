#include <Cad_TModel.hxx>
#include <Cad_Tools.hxx>
#include <TModel_CornerManager.hxx>
#include <TModel_SegmentManager.hxx>
#include <TModel_FaceManager.hxx>
#include <TModel_Vertex.hxx>
#include <TModel_Paired.hxx>
#include <TModel_Surface.hxx>
#include <Global_Timer.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <vector>

namespace tnbLib
{

	static bool loadTag = false;
	static unsigned short verbose = 0;
	static const std::string extension = Cad_TModel::extension;

	static std::shared_ptr<Cad_TModel> mySolid;
	static std::string myFileName;

	void checkLoad()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model is loaded!" << endl
				<< abort(FatalError);
		}
	}

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);

		mySolid = file::LoadFile<std::shared_ptr<Cad_TModel>>(name + extension, verbose);
		if (NOT mySolid)
		{
			FatalErrorIn(FunctionSIG)
				<< " the solid file is null!" << endl
				<< abort(FatalError);
		}

		Cad_Tools::Connect(mySolid);

		loadTag = true;
	}

	void loadFile()
	{
		auto name = file::GetSingleFile(boost::filesystem::current_path(), extension).string();
		myFileName = name;
		loadFile(name);
	}

	void printNbCorners()
	{
		checkLoad();
		Info << endl
			<< " - nb. of corners: " << mySolid->NbCorners() << endl;
	}

	void printNbSegments()
	{
		checkLoad();
		Info << endl
			<< " - nb. of segments: " << mySolid->NbSegments() << endl;
	}

	void printNbFaces()
	{
		checkLoad();
		Info << endl
			<< " - nb. of faces: " << mySolid->NbFaces() << endl;
	}

	const auto& getCorners()
	{
		checkLoad();
		return mySolid->Corners();
	}

	const auto& getSegments()
	{
		checkLoad();
		return mySolid->Segments();
	}

	const auto& getFaces()
	{
		checkLoad();
		return mySolid->Faces();
	}

	void printBlocks(const std::shared_ptr<TModel_CornerManager>& manager)
	{
		Info << endl
			<< " - list of the corners:" << endl;
		auto blocks = manager->Blocks();
		for (const auto& x : blocks)
		{
			Info << x.first << endl;
		}
	}

	void printBlocks(const std::shared_ptr<TModel_SegmentManager>& manager)
	{
		Info << endl
			<< " - list of the segments:" << endl;
		auto blocks = manager->Blocks();
		for (const auto& x : blocks)
		{
			Info << x.first << endl;
		}
	}

	void printBlocks(const std::shared_ptr<TModel_FaceManager>& manager)
	{
		Info << endl
			<< " - list of the faces:" << endl;
		auto blocks = manager->Blocks();
		for (const auto& x : blocks)
		{
			Info << x.first << endl;
		}
	}

	auto selectBlock(const std::shared_ptr<TModel_CornerManager>& manager, const std::string& name)
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

	auto selectBlock(const std::shared_ptr<TModel_SegmentManager>& manager, const std::string& name)
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

	auto selectBlock(const std::shared_ptr<TModel_FaceManager>& manager, const std::string& name)
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

	void printEntities(const std::shared_ptr<Cad_BlockEntity<TModel_Vertex>>& block)
	{
		Info << endl
			<< " - list of the vertices: " << endl;
		auto entities = block->RetrieveEntities();
		for (const auto& x : entities)
		{
			Info << " id: " << x->Index() << ", name: " << x->Name() << endl;
		}
	}

	void printEntities(const std::map<word, std::shared_ptr<Cad_BlockEntity<TModel_Vertex>>>::const_iterator& block)
	{
		printEntities(block->second);
	}

	void printEntities(const std::shared_ptr<Cad_BlockEntity<TModel_Paired>>& block)
	{
		Info << endl
			<< " - list of the segments: " << endl;
		auto entities = block->RetrieveEntities();
		for (const auto& x : entities)
		{
			Info << " id: " << x->Index() << ", name: " << x->Name() << endl;
		}
	}

	void printEntities(const std::map<word, std::shared_ptr<Cad_BlockEntity<TModel_Paired>>>::const_iterator& block)
	{
		printEntities(block->second);
	}

	void printEntities(const std::shared_ptr<Cad_BlockEntity<TModel_Surface>>& block)
	{
		Info << endl
			<< " - list of the faces: " << endl;
		auto entities = block->RetrieveEntities();
		for (const auto& x : entities)
		{
			Info << " id: " << x->Index() << ", name: " << x->Name() << endl;
		}
	}

	void printEntities(const std::map<word, std::shared_ptr<Cad_BlockEntity<TModel_Surface>>>::const_iterator& block)
	{
		printEntities(block->second);
	}

	auto selectEntity(const std::shared_ptr<Cad_BlockEntity<TModel_Vertex>>& block, int key)
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

	auto selectEntity(const std::shared_ptr<Cad_BlockEntity<TModel_Paired>>& block, int key)
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

	auto selectEntity(const std::shared_ptr<Cad_BlockEntity<TModel_Surface>>& block, int key)
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
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "loadFile");
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");

		mod->add(chaiscript::fun([]()-> void {printNbCorners(); }), "printNbCorners");
		mod->add(chaiscript::fun([]()-> void {printNbSegments(); }), "printNbSegments");
		mod->add(chaiscript::fun([]()-> void {printNbFaces(); }), "printNbFaces");

		mod->add(chaiscript::fun([](const std::shared_ptr<TModel_CornerManager>& manager)-> void {printBlocks(manager); }), "printBlocks");
		mod->add(chaiscript::fun([](const std::shared_ptr<TModel_SegmentManager>& manager)-> void {printBlocks(manager); }), "printBlocks");
		mod->add(chaiscript::fun([](const std::shared_ptr<TModel_FaceManager>& manager)-> void {printBlocks(manager); }), "printBlocks");

		mod->add(chaiscript::fun([]()-> void {printBlocks(getFaces()); }), "printFaceBlocks");
		mod->add(chaiscript::fun([]()-> void {printBlocks(getSegments()); }), "printSegmentBlocks");
		mod->add(chaiscript::fun([]()-> void {printBlocks(getCorners()); }), "printCornerBlocks");

		mod->add(chaiscript::fun([](const std::map<word, std::shared_ptr<Cad_BlockEntity<TModel_Surface>>>::const_iterator& block)-> void {printEntities(block); }), "printEntities");
		mod->add(chaiscript::fun([](const std::map<word, std::shared_ptr<Cad_BlockEntity<TModel_Paired>>>::const_iterator& block)-> void {printEntities(block); }), "printEntities");
		mod->add(chaiscript::fun([](const std::map<word, std::shared_ptr<Cad_BlockEntity<TModel_Vertex>>>::const_iterator& block)-> void {printEntities(block); }), "printEntities");

		//- operators

		mod->add(chaiscript::fun([]()-> const auto& {return getCorners(); }), "getCorners");
		mod->add(chaiscript::fun([]()-> const auto& {return getSegments(); }), "getSegments");
		mod->add(chaiscript::fun([]()-> const auto& {return getFaces(); }), "getFaces");

		mod->add(chaiscript::fun([](const std::shared_ptr<TModel_CornerManager>& manager, const std::string& name)-> auto {return selectBlock(manager, name); }), "selectBlock");
		mod->add(chaiscript::fun([](const std::shared_ptr<TModel_SegmentManager>& manager, const std::string& name)-> auto {return selectBlock(manager, name); }), "selectBlock");
		mod->add(chaiscript::fun([](const std::shared_ptr<TModel_FaceManager>& manager, const std::string& name)-> auto {return selectBlock(manager, name); }), "selectBlock");

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

int main(int argc, char *argv[])
{
	if (argc <= 1)
	{
		Info << " - No command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

	if (argc IS_EQUAL 2)
	{
		if (IsEqualCommand(argv[1], "--help"))
		{
			Info << " This application is aimed to read the topology of a solid." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl
				<< " - loadFile(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl
				<< " - setVerbose(unsigned int); Levels: 0, 1" << endl << endl

				<< " # IO functions: " << endl << endl
				<< " - printNbCorners()" << endl
				<< " - printNbSegments()" << endl
				<< " - printNbFaces()" << endl

				<< " - printFaceBlocks()" << endl
				<< " - printSegmentBlocks()" << endl
				<< " - printCornerBlocks()" << endl << endl

				<< " - printBlocks(manager);         - manager: corners, segements, faces" << endl
				<< " - printEntities(block);         - block: corners, segements, faces" << endl

				<< endl
				<< " # Operators: " << endl << endl
				<< " - getCorners();                 - it gives the corner manager" << endl
				<< " - getSegments();                - it gives the segment manager" << endl
				<< " - getFaces();                   - it gives the face manager" << endl << endl

				<< " - [manager].selectBlock(name);  - manager: corners, segements, faces" << endl
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
				auto address = file::GetSystemFile("tnbCadToolSolidManagerReader");
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