#include <Cad2d_Plane.hxx>
#include <Cad_EntityManager.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Edge.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>
#include <boost/filesystem.hpp>


namespace tnbLib
{

	typedef std::shared_ptr<Cad2d_Plane> plane_t;
	typedef std::shared_ptr<Cad_EntityManager<Pln_Edge>> sgmntManager_t;
	typedef std::shared_ptr<Cad_EntityManager<Pln_Vertex>> vtxManager_t;

	typedef std::shared_ptr<Cad_BlockEntity<Pln_Edge>> sgmntBlock_t;
	typedef std::shared_ptr<Cad_BlockEntity<Pln_Vertex>> vtxBlock_t;

	typedef typename Cad_EntityManager<Pln_Edge>::stringMapOfBlocks::const_iterator sgmntBlockIter;
	typedef typename Cad_EntityManager<Pln_Vertex>::stringMapOfBlocks::const_iterator vtxBlockIter;

	typedef typename Cad_BlockEntity<Pln_Edge>::indexedMap::const_iterator sgmntIter;
	typedef typename Cad_BlockEntity<Pln_Vertex>::indexedMap::const_iterator vtxIter;

	static unsigned short verbose = 0;
	static bool loaded = false;


	static std::vector<sgmntBlockIter> sgmntBlockSelected;
	static std::vector<vtxBlockIter> vtxBlockSelected;

	static std::vector<int> sgmntSelected;
	static std::vector<int> vtxSeleceted;

	static plane_t myPlane;

	void loadPlane(const std::string& name)
	{
		if (verbose)
		{
			Info << endl;
			Info << " loading the plane..." << endl;
			Info << endl;
		}

		std::fstream file;
		file.open(name, std::ios::in);

		if (file.fail())
		{
			FatalErrorIn(FunctionSIG)
				<< "file was not found: " << name << endl
				<< abort(FatalError);
		}

		boost::archive::polymorphic_text_iarchive ia(file);

		ia >> myPlane;

		loaded = true;

		if (verbose)
		{
			Info << endl;
			Info << " the plane has been loaded, successfully!" << endl;
			Info << endl;
		}
	}

	void saveTo(const std::string& name)
	{
		fileName fn(name);
		std::ofstream f(fn);

		boost::archive::polymorphic_text_oarchive oa(f);

		oa << myPlane;

		if (verbose)
		{
			Info << endl;
			Info << " the plane is saved, successfully!" << endl;
			Info << endl;
		}
	}

	const auto& getSegments()
	{
		return myPlane->Segments();
	}

	const auto& getVertices()
	{
		return myPlane->Corners();
	}

	void printSegmentBlocks()
	{
		const auto& blocks = getSegments()->Blocks();
		Info << endl;
		Info << " - nb. of blocks: " << blocks.size() << endl;
		Info << " - block list: " << endl;
		for (const auto& x : blocks)
		{
			Info << x.first << endl;
		}
		Info << endl;
	}

	void printVertexBlocks()
	{
		const auto& blocks = getVertices()->Blocks();
		Info << endl;
		Info << " - nb. of blocks: " << blocks.size() << endl;
		Info << " - block list: " << endl;
		for (const auto& x : blocks)
		{
			Info << x.first << endl;
		}
		Info << endl;
	}

	auto getBlock(const sgmntManager_t& t, const std::string& name)
	{
		auto t1 = t->SelectBlock(name)->second;
		return std::move(t1);
	}

	auto getBlock(const vtxManager_t& t, const std::string& name)
	{
		auto t1 = t->SelectBlock(name)->second;
		return std::move(t1);
	}

	void selectBlock(const sgmntManager_t& t, const std::string& name)
	{
		auto t1 = t->SelectBlock(name);
		sgmntBlockSelected.push_back(std::move(t1));
	}

	void selectBlock(const vtxManager_t& t, const std::string& name)
	{
		auto t1 = t->SelectBlock(name);
		vtxBlockSelected.push_back(std::move(t1));
	}

	void combineBlocks(const sgmntManager_t& t, const std::string& name)
	{
		if (sgmntBlockSelected.size() < 2)
		{
			FatalErrorIn(FunctionSIG)
				<< "at least 2 segment blocks must be selected!" << endl
				<< abort(FatalError);
		}
		t->CombineBlocks(sgmntBlockSelected, name);
		sgmntBlockSelected.clear();
	}

	void combineBlocks(const vtxManager_t& t, const std::string& name)
	{
		if (vtxBlockSelected.size() < 2)
		{
			FatalErrorIn(FunctionSIG)
				<< "at least 2 vertex blocks must be selected!" << endl
				<< abort(FatalError);
		}
		t->CombineBlocks(vtxBlockSelected, name);
		vtxBlockSelected.clear();
	}

	void compactBlocks(const sgmntManager_t& t, const std::string& name)
	{
		t->CompactBlocks(name);
	}

	void compactBlocks(const vtxManager_t& t, const std::string& name)
	{
		t->CompactBlocks(name);
	}

	void compactBlocksWithSelected(const sgmntManager_t& t)
	{
		if (sgmntBlockSelected.size() NOT_EQUAL 1)
		{
			FatalErrorIn(FunctionSIG)
				<< "there must be a one selected block to call this function" << endl
				<< abort(FatalError);
		}
		t->CompactBlocksWith(sgmntBlockSelected[0]);
		sgmntBlockSelected.clear();
	}

	void compactBlocksWithSelected(const vtxManager_t& t)
	{
		if (vtxBlockSelected.size() NOT_EQUAL 1)
		{
			FatalErrorIn(FunctionSIG)
				<< "there must be a one selected block to call this function" << endl
				<< abort(FatalError);
		}
		t->CompactBlocksWith(vtxBlockSelected[0]);
		vtxBlockSelected.clear();
	}

	void renameBlock(const sgmntManager_t& t, const std::string& name)
	{
		if (sgmntBlockSelected.size() NOT_EQUAL 1)
		{
			FatalErrorIn(FunctionSIG)
				<< "there must be a one selected block to call this function" << endl
				<< abort(FatalError);
		}
		t->ReNameBlock(sgmntBlockSelected[0], name);
		sgmntBlockSelected.clear();
	}

	void renameBlock(const vtxManager_t& t, const std::string& name)
	{
		if (vtxBlockSelected.size() NOT_EQUAL 1)
		{
			FatalErrorIn(FunctionSIG)
				<< "there must be a one selected block to call this function" << endl
				<< abort(FatalError);
		}
		t->ReNameBlock(vtxBlockSelected[0], name);
		vtxBlockSelected.clear();
	}

	/*void compactBlocks(const sgmntManager_t& t, const std::string& name)
	{
		t->CompactBlocks(name);
	}

	void compactBlocks(const vtxManager_t& t, const std::string& name)
	{
		t->CompactBlocks(name);
	}*/


	//- blocks:
	void printBlock(const sgmntBlock_t& b)
	{
		const auto& entities = b->Entities();
		for (const auto& x : entities)
		{
			Info << x.first << endl;
		}
	}

	void printBlock(const vtxBlock_t& b)
	{
		const auto& entities = b->Entities();
		for (const auto& x : entities)
		{
			Info << x.first << endl;
		}
	}

	void selectEntity(const sgmntBlock_t& b, unsigned int i)
	{
		auto t = b->SelectEntity(i);
		sgmntSelected.push_back(t->first);
	}

	void selectEntity(const vtxBlock_t& b, unsigned int i)
	{
		auto item = b->SelectEntity(i);
		vtxSeleceted.push_back(item->first);
	}

	void split(const sgmntBlock_t& b, const std::string& name)
	{
		if (sgmntSelected.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "at least one segment must be selected to call this function" << endl
				<< abort(FatalError);
		}
		auto nb = b->Split(sgmntSelected);
		getSegments()->Import(name, nb);
	}

	void split(const vtxBlock_t& b, const std::string& name)
	{
		if (vtxSeleceted.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "at least one segment must be selected to call this function" << endl
				<< abort(FatalError);
		}
		auto nb = b->Split(vtxSeleceted);
		getVertices()->Import(name, nb);
	}
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<chaiscript::Module> module_t;

	void setGlobals(const module_t& mod)
	{
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadPlane(name); }), "loadPlane");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		mod->add(chaiscript::fun([]()->void {printSegmentBlocks(); }), "printSegmentBlocks");
		mod->add(chaiscript::fun([]()->void {printVertexBlocks(); }), "printVertexBlocks");

		mod->add(chaiscript::fun([](const sgmntBlock_t& t)-> void {printBlock(t); }), "printBlock");
		mod->add(chaiscript::fun([](const vtxBlock_t& t)->void {printBlock(t); }), "printBlock");

		mod->add(chaiscript::fun([](unsigned short i)->void {verbose = i; }), "setVerbose");
	}

	void setSegment(const module_t& mod)
	{
		mod->add(chaiscript::fun([]()-> const sgmntManager_t& {return getSegments(); }), "getSegments");
		mod->add(chaiscript::fun([](const sgmntManager_t& t, const std::string& name)->void {selectBlock(t, name); }), "selectBlock");
		mod->add(chaiscript::fun([](const sgmntManager_t& t, const std::string& name)-> void {combineBlocks(t, name); }), "combineSelectedBlocks");
		mod->add(chaiscript::fun([](const sgmntManager_t& t, const std::string& name)-> void {compactBlocks(t, name); }), "compactAllBlocks");
		mod->add(chaiscript::fun([](const sgmntManager_t& t)-> void {compactBlocksWithSelected(t); }), "compactBlocksWithSelected");
		mod->add(chaiscript::fun([](const sgmntManager_t& t, const std::string& name)-> void {renameBlock(t, name); }), "renameSelectedBlock");

		mod->add(chaiscript::fun([](const sgmntManager_t& t, const std::string& name)-> auto {auto m = getBlock(t, name); return std::move(m); }), "getBlock");
		mod->add(chaiscript::fun([](const sgmntBlock_t& t, unsigned int i)-> void {selectEntity(t, i); }), "selectSegment");
		mod->add(chaiscript::fun([](const sgmntBlock_t& t, const std::string& name)-> void {split(t, name); }), "split");
	}

	void setCorners(const module_t& mod)
	{
		mod->add(chaiscript::fun([]()-> const vtxManager_t& {return getVertices(); }), "getCorners");
		mod->add(chaiscript::fun([](const vtxManager_t& t, const std::string& name)->void {selectBlock(t, name); }), "selectBlock");
		mod->add(chaiscript::fun([](const vtxManager_t& t, const std::string& name)-> void {combineBlocks(t, name); }), "combineSelectedBlocks");
		mod->add(chaiscript::fun([](const vtxManager_t& t, const std::string& name)-> void {compactBlocks(t, name); }), "compactAllBlocks");
		mod->add(chaiscript::fun([](const vtxManager_t& t)-> void {compactBlocksWithSelected(t); }), "compactBlocksWithSelected");
		mod->add(chaiscript::fun([](const vtxManager_t& t, const std::string& name)-> void {renameBlock(t, name); }), "renameSelectedBlock");

		mod->add(chaiscript::fun([](const vtxManager_t& t, const std::string& name)-> auto {auto m = getBlock(t, name); return std::move(m); }), "getBlock");
		mod->add(chaiscript::fun([](const vtxBlock_t& t, unsigned int i)-> void {selectEntity(t, i); }), "selectCorner");
		mod->add(chaiscript::fun([](const vtxBlock_t& t, const std::string& name)-> void {split(t, name); }), "split");
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
	FatalError.throwExceptions();

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
			Info << "this is help" << endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);
			setSegment(mod);
			setCorners(mod);

			chai.add(mod);

			fileName myFileName("topology");

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
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
	return 0;
}