#include <Aft2d_BoundaryOfPlane.hxx>
#include <Aft2d_BoundaryOfPlaneAnIso.hxx>
#include <Aft2d_SolutionData.hxx>
#include <Aft2d_SolutionDataAnIso.hxx>
#include <Aft2d_OptNode_Calculator.hxx>
#include <Aft2d_OptNodeAnIso_Calculator.hxx>
#include <Aft2d_MetricPrcsr.hxx>
#include <Aft2d_MetricPrcsrAnIso.hxx>
#include <Aft_Tools.hxx>
#include <Aft2d_SegmentEdge.hxx>
#include <Aft2d_SegmentEdgeAnIso.hxx>
#include <Aft2d_Model.hxx>
#include <Aft2d_ModelAnIso.hxx>
#include <Cad2d_Plane.hxx>
#include <Global_File.hxx>
#include <Global_Timer.hxx>
#include <OSstream.hxx>
#include <TnbError.hxx>

namespace tnbLib
{

	static const std::string extension = Aft2d_SolutionDataBase::extension;

	static unsigned short verbose = 0;
	static bool loadTag = false;
	static bool exeTag = false;

	static std::shared_ptr<Aft2d_SolutionDataBase> mySoluData;
	static std::string myFileName;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);

		mySoluData = file::LoadFile<std::shared_ptr<Aft2d_SolutionDataBase>>(name + extension, verbose);
		if (NOT mySoluData)
		{
			FatalErrorIn(FunctionSIG)
				<< "the data solution file is null!" << endl
				<< abort(FatalError);
		}

		loadTag = true;
	}

	void loadFile()
	{
		auto name = file::GetSingleFile(boost::filesystem::current_path(), extension).string();
		myFileName = name;
		loadFile(name);
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);

		file::SaveTo(mySoluData, name + extension, verbose);
	}

	void saveTo()
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}
		saveTo(myFileName);
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded!" << endl
				<< abort(FatalError);
		}

		if (mySoluData->IsIso())
		{
			auto soluData = std::dynamic_pointer_cast<Aft2d_SolutionData>(mySoluData);
			Debug_Null_Pointer(soluData);

			const auto& boundaries = soluData->BoundaryEdges();
			if (boundaries.empty())
			{
				FatalErrorIn(FunctionSIG)
					<< "no boundary edge has been detected!" << endl
					<< abort(FatalError);
			}

			if (NOT soluData->NodeCalculator())
			{
				FatalErrorIn(FunctionSIG)
					<< "no node creator has been detected!" << endl
					<< abort(FatalError);
			}

			if (NOT soluData->Metric())
			{
				FatalErrorIn(FunctionSIG)
					<< "no metric processor has been found!" << endl
					<< abort(FatalError);
			}

			soluData->NodeCalculator()->SetMetricMap(soluData->Metric());

			Aft_Tools::Connect(boundaries);

			auto mesher = std::make_shared<Aft2d_Model>();
			mesher->LoadMetricMap(soluData->Metric());
			mesher->LoadBoundaryMetricMap(soluData->Metric());

			mesher->LoadBoundaryEdges(Aft_Tools::UpCast(soluData->BoundaryEdges()));
			mesher->LoadNodeCalculator(soluData->NodeCalculator());

			{// timer scope [12/22/2021 Amir]
				Global_Timer timer;
				timer.SetInfo(Global_TimerInfo_s);

				mesher->Perform();
			}



			const auto& elemMap = mesher->RetrieveElements();
			std::vector<std::shared_ptr<Aft2d_Element>> elements;
			elements.reserve(elemMap.size());
			for (const auto& x : elemMap)
			{
				elements.push_back(x.second);
			}

			soluData->SetElements(std::move(elements));

			if (verbose)
			{
				Info << " - the application is performed, successfully!" << endl;
				Info << " - Nb. of generated elements: " << mesher->NbElements() << ", in " << global_time_duration << " seconds." << endl;
			}
		}
		else if (mySoluData->IsAnIso())
		{
			auto soluData = std::dynamic_pointer_cast<Aft2d_SolutionDataAnIso>(mySoluData);
			Debug_Null_Pointer(soluData);

			const auto& boundaries = soluData->BoundaryEdges();
			if (boundaries.empty())
			{
				FatalErrorIn(FunctionSIG)
					<< "no boundary edge has been detected!" << endl
					<< abort(FatalError);
			}

			if (NOT soluData->NodeCalculator())
			{
				FatalErrorIn(FunctionSIG)
					<< "no node creator has been detected!" << endl
					<< abort(FatalError);
			}

			if (NOT soluData->Metric())
			{
				FatalErrorIn(FunctionSIG)
					<< "no metric processor has been found!" << endl
					<< abort(FatalError);
			}

			soluData->NodeCalculator()->SetMetricMap(soluData->Metric());

			Aft_Tools::Connect(boundaries);

			auto mesher = std::make_shared<Aft2d_ModelAnIso>();
			mesher->LoadMetricMap(soluData->Metric());
			mesher->LoadBoundaryMetricMap(soluData->Metric());

			mesher->LoadBoundaryEdges(Aft_Tools::UpCast(soluData->BoundaryEdges()));
			mesher->LoadNodeCalculator(soluData->NodeCalculator());

			{// timer scope [12/22/2021 Amir]
				Global_Timer timer;
				timer.SetInfo(Global_TimerInfo_s);

				mesher->Perform();
			}



			const auto& elemMap = mesher->RetrieveElements();
			std::vector<std::shared_ptr<Aft2d_ElementAnIso>> elements;
			elements.reserve(elemMap.size());
			for (const auto& x : elemMap)
			{
				elements.push_back(x.second);
			}

			soluData->SetElements(std::move(elements));

			if (verbose)
			{
				Info << " - the application is performed, successfully!" << endl;
				Info << " - Nb. of generated elements: " << mesher->NbElements() << ", in " << global_time_duration << " seconds." << endl;
			}
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "Unspecified type of data has been detected!" << endl
				<< abort(FatalError);
		}

		exeTag = true;
	}
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<chaiscript::Module> module_t;

	void setFuns(const module_t& mod)
	{
		// io functions [12/21/2021 Amir]
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "loadFile");

		// settings [12/21/2021 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		// operators [12/21/2021 Amir]
		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");
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
			Info << " This application is aimed to create plane boundary info." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int); Levels: 0, 1, 2" << endl << endl

				<< " # Operators:" << endl << endl

				<< " - execute()" << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFuns(mod);

			chai.add(mod);

			try
			{
				fileName myFileName(file::GetSystemFile("tnbMeshPlaneAft"));

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
	return 1;
}