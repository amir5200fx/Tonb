#include <StbGMaker_Model.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_Models.hxx>
#include <Marine_Domain.hxx>
#include <Marine_WaterLib.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/filesystem.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<Marine_Body> body_t;
	typedef std::shared_ptr<StbGMaker_Model> model_t;
	typedef std::shared_ptr<Marine_Domain> domain_t;

	static model_t myModel;
	static domain_t myDomain;

	typedef std::shared_ptr<marineLib::Model_Hull> displacer_t;
	typedef std::shared_ptr<marineLib::Model_Tank> tank_t;
	typedef std::shared_ptr<marineLib::Model_Sail> sail_t;

	static displacer_t myDisplacer;
	static std::vector<tank_t> myTanks;
	static std::vector<sail_t> mySails;

	static unsigned short verbose(0);

	auto createDomain()
	{
		auto domain = Marine_WaterLib::Domain(*myDisplacer->Body());
		return std::move(domain);
	}

	auto getAllFilesNames(const boost::filesystem::path& p)
	{
		boost::filesystem::directory_iterator end_itr;

		std::vector<std::string> names;
		for (boost::filesystem::directory_iterator iter(p); iter != end_itr; iter++)
		{
			if (boost::filesystem::is_regular_file(iter->path()))
			{
				auto file = iter->path().filename().string();
				names.push_back(std::move(file));
			}
		}
		return std::move(names);
	}

	auto getSingleFile(const boost::filesystem::path& p)
	{
		auto files = getAllFilesNames(p);
		if (files.size())
		{
			return files[0];
		}
		return std::string();
	}

	void loadModel()
	{
		{ //- loading displacer part
			boost::filesystem::path dir("displacer");
			if (NOT boost::filesystem::is_directory(dir))
			{
				FatalErrorIn(FunctionSIG)
					<< "no 'displacer' directory has been found!" << endl
					<< abort(FatalError);
			}

			auto name = getSingleFile(dir);

			fileName fn(name);
			std::string address = ".\\displacer\\" + name;

			std::fstream file;

			file.open(address, std::ios::in);
			if (file.fail())
			{
				FatalErrorIn(FunctionSIG)
					<< "unable to open the file: " << address << endl
					<< abort(FatalError);
			}

			TNB_iARCH_FILE_TYPE ar(file);

			body_t body;
			{//- timer scope
				Global_Timer timer;
				timer.SetInfo(Global_TimerInfo_ms);

				ar >> body;
			}

			auto displacer = std::dynamic_pointer_cast<marineLib::Body_Displacer>(body);
			if (NOT displacer)
			{
				FatalErrorIn(FunctionSIG)
					<< "the body is not displacer!" << endl
					<< abort(FatalError);
			}

			myDisplacer = std::make_shared<marineLib::Model_Hull>(std::move(displacer));

			if (verbose)
			{
				Info << " The displacer has been loaded from: " << address << ", successfully in " << global_time_duration << " ms." << endl;
				Info << " - body's name: " << body->Name() << endl;
			}
		}

		{
			boost::filesystem::path dir("tanks");
			if (boost::filesystem::is_directory(dir))
			{
				size_t i = 0;
				while (boost::filesystem::is_directory(boost::filesystem::path(L"/tanks/" + std::to_wstring(i))))
				{
					auto name = getSingleFile(boost::filesystem::path(L"/tanks/" + std::to_wstring(i)));
					std::string address = ".\\tanks\\" + std::to_string(i) + "\\" + name;
					std::fstream file;
					file.open(address, ios::in);

					if (file.fail())
					{
						continue;
					}

					TNB_iARCH_FILE_TYPE ar(file);

					tank_t tank;
					{//- timer scope
						Global_Timer timer;
						timer.SetInfo(Global_TimerInfo_ms);

						ar >> tank;
					}

					if (verbose)
					{
						Info << " The tank has been loaded from: " << address << ", successfully in " << global_time_duration << " ms." << endl;
						Info << " - tank's name: " << tank->Name() << endl;
					}

					myTanks.push_back(std::move(tank));
				}

				if (verbose)
				{
					Info << endl
						<< " - nb. of tanks: " << myTanks.size() << endl;
				}
			}
			else
			{
				Info << endl
					<< " - no tanks have been detected." << endl;
			}
		}

		{
			boost::filesystem::path dir("sails");
			if (boost::filesystem::is_directory(dir))
			{
				size_t i = 0;
				while (boost::filesystem::is_directory(boost::filesystem::path(L"/sails/" + std::to_wstring(i))))
				{
					auto name = getSingleFile(boost::filesystem::path(L"/sails/" + std::to_wstring(i)));
					std::string address = ".\\sails\\" + std::to_string(i) + "\\" + name;
					std::fstream file;
					file.open(address, ios::in);

					if (file.fail())
					{
						continue;
					}

					TNB_iARCH_FILE_TYPE ar(file);

					sail_t sail;
					{//- timer scope
						Global_Timer timer;
						timer.SetInfo(Global_TimerInfo_ms);

						ar >> sail;
					}

					if (verbose)
					{
						Info << " The sail has been loaded from: " << address << ", successfully in " << global_time_duration << " ms." << endl;
						Info << " - tank's name: " << sail->Name() << endl;
					}

					mySails.push_back(std::move(sail));
				}

				if (verbose)
				{
					Info << endl
						<< " - nb. of sails: " << mySails.size() << endl;
				}
			}
			else
			{
				Info << endl
					<< " - no sails have been detected." << endl;
			}
		}

		myDomain = createDomain();

		if (verbose)
		{
			const auto& b = *myDomain->Dim();
			Info << " - domain's dimension: " << b << endl;
		}
	}

	void makeModel()
	{
		if (NOT myDisplacer)
		{
			FatalErrorIn(FunctionSIG)
				<< "no displacer has been loaded!" << endl
				<< abort(FatalError);
		}
		myModel = std::make_shared<StbGMaker_Model>();
		myModel->SetDomain(myDomain);
		myModel->SetHull(myDisplacer);

		if (myTanks.size())
		{
			myModel->SetTanks(myTanks);
		}

		if (mySails.size())
		{
			myModel->SetSail(mySails);
		}
	}

	void saveTo(const std::string& name)
	{
		fileName fn(name);
		std::ofstream f(fn);

		TNB_oARCH_FILE_TYPE oa(f);
		oa << myModel;

		if (verbose)
		{
			Info << endl;
			Info << " the model is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
		}
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
		mod->add(chaiscript::fun([]()->void {loadModel(); }), "loadModels");
		mod->add(chaiscript::fun([]()->void {makeModel(); }), "execute");
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([](int i)->void {verbose = i; }), "setVerbose");
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
			Info << endl;
			Info << " This application is aimed to create a stability model." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # I/O functions: " << endl
				<< " - loadModels()" << endl
				<< " - saveTo(string)" << endl << endl

				<< " # Settings: " << endl << endl
				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " # functions: " << endl << endl

				<< " - execute()" << endl
				<< endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);

			chai.add(mod);

			std::string address = ".\\system\\hydstcModelMaker";
			fileName myFileName(address);

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
}