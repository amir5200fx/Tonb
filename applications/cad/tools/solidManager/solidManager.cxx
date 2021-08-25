#include <Cad_TModel.hxx>
#include <TModel_CornerManager.hxx>
#include <TModel_SegmentManager.hxx>
#include <TModel_FaceManager.hxx>
#include <TModel_Vertex.hxx>
#include <TModel_Paired.hxx>
#include <TModel_Surface.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static bool loadTag = false;

	static unsigned short verbose(0);

	static std::shared_ptr<Cad_TModel> mySolid;

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

	void loadModel(const std::string& name)
	{
		fileName fn(name);
		if (verbose)
		{
			Info << endl;
			Info << " loading the model from, " << fn << endl;
			Info << endl;
		}
		std::ifstream myFile(fn);

		{//- timer scope
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			TNB_iARCH_FILE_TYPE ar(myFile);
			ar >> mySolid;
		}

		if (NOT mySolid)
		{
			FatalErrorIn(FunctionSIG)
				<< " the loaded model is null" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl;
			Info << " the model is loaded, from: " << name << ", successfully in " << global_time_duration << " ms." << endl;
			Info << endl;
		}

		loadTag = true;
	}

	void saveTo(const std::string& name)
	{
		fileName fn(name);
		std::ofstream myFile(fn);

		TNB_oARCH_FILE_TYPE ar(myFile);
		ar << mySolid;

		myFile.close();

		if (verbose)
		{
			Info << endl;
			Info << " the solid is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
		}
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
		return manager->SelectBlock(name);
	}

	auto selectBlock(const std::shared_ptr<TModel_SegmentManager>& manager, const std::string& name)
	{
		return manager->SelectBlock(name);
	}

	auto selectBlock(const std::shared_ptr<TModel_FaceManager>& manager, const std::string& name)
	{
		return manager->SelectBlock(name);
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

	auto selectEntity(const std::shared_ptr<Cad_BlockEntity<TModel_Vertex>>& block, int key)
	{
		return block->SelectEntity(key);
	}

	auto selectEntity(const std::shared_ptr<Cad_BlockEntity<TModel_Paired>>& block, int key)
	{
		return block->SelectEntity(key);
	}

	auto selectEntity(const std::shared_ptr<Cad_BlockEntity<TModel_Surface>>& block, int key)
	{
		return block->SelectEntity(key);
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
		mod->add(chaiscript::fun([](const std::string& name)->void {loadModel(name); }), "loadModel");
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");

		mod->add(chaiscript::fun([]()-> void {printNbCorners(); }), "printNbCorners");
		mod->add(chaiscript::fun([]()-> void {printNbSegments(); }), "printNbSegments");
		mod->add(chaiscript::fun([]()-> void {printNbFaces(); }), "printNbFaces");

		mod->add(chaiscript::fun([](const std::shared_ptr<TModel_CornerManager>& manager)-> void {printBlocks(manager); }), "printBlocks");
		mod->add(chaiscript::fun([](const std::shared_ptr<TModel_SegmentManager>& manager)-> void {printBlocks(manager); }), "printBlocks");
		mod->add(chaiscript::fun([](const std::shared_ptr<TModel_FaceManager>& manager)-> void {printBlocks(manager); }), "printBlocks");

		mod->add(chaiscript::fun([](const std::shared_ptr<Cad_BlockEntity<TModel_Vertex>>& block)-> void {printEntities(block); }), "printEntities");
		mod->add(chaiscript::fun([](const std::shared_ptr<Cad_BlockEntity<TModel_Paired>>& block)-> void {printEntities(block); }), "printEntities");
		mod->add(chaiscript::fun([](const std::shared_ptr<Cad_BlockEntity<TModel_Surface>>& block)-> void {printEntities(block); }), "printEntities");

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
	//FatalError.throwExceptions();

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
			Info << endl;
			Info << " This application is aimed to modify topology of a solid." << endl;
			Info << endl
				<< " Function list:" << endl
				<< " - loadModel(string)" << endl
				<< " - saveTo(string)" << endl << endl

				<< " IO functions: " << endl
				<< " - printNbCorners()" << endl
				<< " - printNbSegments()" << endl
				<< " - printNbFaces()" << endl << endl
				
				<< " - printBlocks(manager);        - manager: corners, segements, faces" << endl
				<< " - printEntities(block);        - block: corners, segements, faces" << endl

				<< endl
				<< " Operators: " << endl
				<< " - getCorners();                - it gives the corner manager" << endl
				<< " - getSegments();               - it gives the segment manager" << endl
				<< " - getFaces();                  - it gives the face manager" << endl
				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " - execute()" << endl
				<< endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			fileName myFileName("solidManager");

			try
			{
				chai.eval_file(myFileName);
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
		else
		{
			Info << " - No valid command is entered" << endl
				<< " - For more information use '--help' command" << endl;
			FatalError.exit();
		}
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

}