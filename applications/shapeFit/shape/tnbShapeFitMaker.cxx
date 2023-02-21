#include <PtdShapeFit_Shape.hxx>
#include <PtdShapeFit_Section.hxx>
#include <Cad_Shape.hxx>
#include <Geo_Serialization.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <gp_Ax1.hxx>
#include <gp_Pln.hxx>

namespace tnbLib
{

	static std::shared_ptr<PtdShapeFit_Shape> myShape;
	static std::shared_ptr<gp_Ax1> myAxis;

	static std::vector<std::pair<std::shared_ptr<PtdShapeFit_Section>, Standard_Real>> mySections;

	static std::shared_ptr<Cad_Shape> myModel;

	static unsigned short verbose = 0;
	static auto exeTag = false;
	static auto loadTag = false;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	auto createList()
	{

	}

	void checkFolder(const std::string& name)
	{
		if (NOT boost::filesystem::is_directory(name))
		{
			FatalErrorIn(FunctionSIG)
				<< "no {" << name << "} directory has been found!" << endl
				<< abort(FatalError);
		}
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed." << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);
		file::SaveTo(myModel, name + Cad_Shape::extension, verbose);
	}

	void loadSections()
	{
		checkFolder("sections");

		const auto currentPath = boost::filesystem::current_path();

		// change the current path [2/6/2023 Payvand]
		boost::filesystem::current_path(currentPath.string() + R"(\sections)");

		if (file::IsFile(boost::filesystem::current_path(), ".PATH"))
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), ".PATH").string();
			fileName fn(name + ".PATH");
			std::ifstream myFile;
			myFile.open(fn);
			if (myFile.fail())
			{
				FatalErrorIn(FunctionSIG)
					<< "failed to open the file: " << name + ".PATH" << endl
					<< abort(FatalError);
			}

			std::string address;
			std::getline(myFile, address);
			// change the current path [2/6/2023 Payvand]
			boost::filesystem::current_path(address);

			size_t i = 0;
			while (boost::filesystem::is_directory(boost::filesystem::path(std::to_string(i))))
			{
				std::shared_ptr<PtdShapeFit_Section> sect;
				Standard_Real loc;
				{ // loading the section [2/13/2023 Payvand]
					auto icurrentPath = boost::filesystem::current_path().string() + R"(\)" + std::to_string(i);
					auto name = file::GetSingleFile(icurrentPath, PtdShapeFit_Section::extension).string();
					std::string address = ".\\" + std::to_string(i) + "\\" + name + PtdShapeFit_Section::extension;
					sect = file::LoadFile<std::shared_ptr<PtdShapeFit_Section>>(address, verbose);
					if (NOT sect)
					{
						FatalErrorIn(FunctionSIG)
							<< "the section is null." << endl
							<< abort(FatalError);
					}
				}
				{
					auto icurrentPath = boost::filesystem::current_path().string() + R"(\)" + std::to_string(i) + R"(\plane)";
					auto name = file::GetSingleFile(icurrentPath, ".gpln").string();
					std::string address = ".\\" + std::to_string(i) + "\\plane\\" + name + ".gpln";
					auto pln = file::LoadFile<std::shared_ptr<gp_Pln>>(address, verbose);
					if (NOT pln)
					{
						FatalErrorIn(FunctionSIG)
							<< "the plane is null." << endl
							<< abort(FatalError);
					}
					loc = pln->Location().Distance(myAxis->Location());
				}

				auto paired = std::make_pair(std::move(sect), loc);
				mySections.push_back(std::move(paired));
				i++;
			}
		}
		else
		{
			size_t i = 0;
			while (boost::filesystem::is_directory(boost::filesystem::path(std::to_string(i))))
			{
				std::shared_ptr<PtdShapeFit_Section> sect;
				Standard_Real loc;
				{ // loading the section [2/13/2023 Payvand]
					auto icurrentPath = boost::filesystem::current_path().string() + R"(\)" + std::to_string(i);
					auto name = file::GetSingleFile(icurrentPath, PtdShapeFit_Section::extension).string();
					std::string address = ".\\" + std::to_string(i) + "\\" + name + PtdShapeFit_Section::extension;
					sect = file::LoadFile<std::shared_ptr<PtdShapeFit_Section>>(address, verbose);
					if (NOT sect)
					{
						FatalErrorIn(FunctionSIG)
							<< "the section is null." << endl
							<< abort(FatalError);
					}
				}
				{
					auto icurrentPath = boost::filesystem::current_path().string() + R"(\)" + std::to_string(i) + R"(\plane)";
					auto name = file::GetSingleFile(icurrentPath, ".gpln").string();
					std::string address = ".\\" + std::to_string(i) + "\\plane\\" + name + ".gpln";
					auto pln = file::LoadFile<std::shared_ptr<gp_Pln>>(address, verbose);
					if (NOT pln)
					{
						FatalErrorIn(FunctionSIG)
							<< "the plane is null." << endl
							<< abort(FatalError);
					}
					loc = pln->Location().Distance(myAxis->Location());
				}

				auto paired = std::make_pair(std::move(sect), loc);
				mySections.push_back(std::move(paired));
				i++;
			}
		}

		//- change back the current path
		boost::filesystem::current_path(currentPath);
	}

	void loadAxis()
	{
		checkFolder("axis");

		const auto currentPath = boost::filesystem::current_path();

		// change the current path [2/6/2023 Payvand]
		boost::filesystem::current_path(currentPath.string() + R"(\axis)");

		if (file::IsFile(boost::filesystem::current_path(), ".PATH"))
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), ".PATH").string();
			fileName fn(name + ".PATH");

			std::ifstream myFile;
			myFile.open(fn);
			if (myFile.is_open())
			{
				std::string address;
				std::getline(myFile, address);

				// change the current path [2/6/2023 Payvand]
				boost::filesystem::current_path(address);

				auto name = file::GetSingleFile(boost::filesystem::current_path(), ".axis3d").string();
				myAxis = file::LoadFile<std::shared_ptr<gp_Ax1>>(name + ".axis3d", verbose);
				if (NOT myAxis)
				{
					FatalErrorIn(FunctionSIG)
						<< " the axis is null." << endl
						<< abort(FatalError);
				}
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "the file is not open: " << name + ".PATH" << endl
					<< abort(FatalError);
			}
		}
		else
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), ".axis3d").string();
			myAxis = file::LoadFile<std::shared_ptr<gp_Ax1>>(name + ".axis3d", verbose);
			if (NOT myAxis)
			{
				FatalErrorIn(FunctionSIG)
					<< " the axis is null." << endl
					<< abort(FatalError);
			}
		}
		//- change back the current path
		boost::filesystem::current_path(currentPath);
	}

	void loadAxis(const std::string& name)
	{
		file::CheckExtension(name);
		myAxis = file::LoadFile<std::shared_ptr<gp_Ax1>>(name + ".axis3d", verbose);
		if (NOT myAxis)
		{
			FatalErrorIn(FunctionSIG)
				<< " the axis is null." << endl
				<< abort(FatalError);
		}
	}

	void loadShape()
	{
		checkFolder("shape");

		const auto currentPath = boost::filesystem::current_path();

		// change the current path [2/6/2023 Payvand]
		boost::filesystem::current_path(currentPath.string() + R"(\shape)");

		if (file::IsFile(boost::filesystem::current_path(), ".PATH"))
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), ".PATH").string();
			fileName fn(name + ".PATH");

			std::ifstream myFile;
			myFile.open(fn);
			if (myFile.is_open())
			{
				std::string address;
				std::getline(myFile, address);

				// change the current path [2/6/2023 Payvand]
				boost::filesystem::current_path(address);

				auto name = file::GetSingleFile(boost::filesystem::current_path(), PtdShapeFit_Shape::extension).string();
				myShape = file::LoadFile<std::shared_ptr<PtdShapeFit_Shape>>(name + PtdShapeFit_Shape::extension, verbose);
				if (NOT myShape)
				{
					FatalErrorIn(FunctionSIG)
						<< " the shape is null." << endl
						<< abort(FatalError);
				}
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "the file is not open: " << name + ".PATH" << endl
					<< abort(FatalError);
			}
		}
		else
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), PtdShapeFit_Shape::extension).string();
			myShape = file::LoadFile<std::shared_ptr<PtdShapeFit_Shape>>(name + PtdShapeFit_Shape::extension, verbose);
			if (NOT myShape)
			{
				FatalErrorIn(FunctionSIG)
					<< " the shape is null." << endl
					<< abort(FatalError);
			}
		}
		//- change back the current path
		boost::filesystem::current_path(currentPath);
	}

	void loadFiles()
	{
		if (boost::filesystem::is_directory("axis"))
		{
			loadAxis();
		}
		else
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), ".axis3d").string();
			loadAxis(name);
		}

		if (boost::filesystem::is_directory("axis"))
		{
			loadSections();
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "no 'section' directory has been found." << endl
				<< abort(FatalError);
		}

		if (boost::filesystem::is_directory("shape"))
		{
			loadShape();
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "no 'shape' directory has been found." << endl
				<< abort(FatalError);
		}
		loadTag = true;
	}

	void interpolate()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded." << endl
				<< abort(FatalError);
		}
		std::vector<std::shared_ptr<PtdShapeFit_Section>> sections;
		std::vector<Standard_Real> xs;
		for (const auto& x : mySections)
		{
			sections.push_back(x.first);
			xs.push_back(x.second);
		}
		//PAUSE;
		auto pars = myShape->CalcParameters(sections, *myAxis, xs);
		for (const auto& p : pars)
		{
			std::cout << std::endl;
			std::cout << "Parameters: " << std::endl;
			for (const auto& x : p->x)
			{
				std::cout << " - " << x.name << ": " << x.x << std::endl;
			}
		}
		//PAUSE;
		auto shape = myShape->CreateShape(pars, sections.at(0), *myAxis, xs);

		myModel = shape;

		exeTag = true;
		if (verbose)
		{
			Info << endl
				<< " the application is performed, successfully!" << endl;
		}
	}

	void extrapolate(std::vector<double> theXs)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded." << endl
				<< abort(FatalError);
		}
		std::vector<std::shared_ptr<PtdShapeFit_Section>> sections;
		std::vector<Standard_Real> xs;
		for (const auto& x : mySections)
		{
			sections.push_back(x.first);
			xs.push_back(x.second);
		}
		//PAUSE;
		auto pars = myShape->CalcParameters(sections, *myAxis, xs);
		for (const auto& p : pars)
		{
			std::cout << std::endl;
			std::cout << "Parameters: " << std::endl;
			for (const auto& x : p->x)
			{
				std::cout << " - " << x.name << ": " << x.x << std::endl;
			}
		}
		//PAUSE;
		std::vector<std::pair<std::shared_ptr<PtdShapeFit_Section::Parameters>, Standard_Real>> parsLocs;
		for (size_t i = 0; i < pars.size(); i++)
		{
			auto paired = std::make_pair(pars.at(i), xs.at(i));
			parsLocs.push_back(std::move(paired));
		}
		auto shape = myShape->CreateExtrapolated(parsLocs, sections.at(0), *myAxis, theXs);

		myModel = shape;

		exeTag = true;
		if (verbose)
		{
			Info << endl
				<< " the application is performed, successfully!" << endl;
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

	void setFunctions(const module_t& mod)
	{

		//- io functions
		mod->add(chaiscript::fun([]()-> void {loadFiles(); }), "loadFiles");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		//- settings

		mod->add(chaiscript::fun([](unsigned short i)->void {verbose = i; }), "setVerbose");

		// Operators [2/11/2023 Payvand]
		mod->add(chaiscript::fun([]()-> void {interpolate(); }), "interpolate");
		mod->add(chaiscript::fun([](std::vector<double> xs)-> void {extrapolate(xs); }), "extrapolate");
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
	//sysLib::init_gl_marine_integration_info();
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
			Info << " This application is aimed to create a shape fitting maker." << endl
				<< " - subdirectories: sections, axis, shape" << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name)" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " # operators: " << endl << endl

				<< " - interpolate()" << endl
				<< " - extrapolate(Xs)" << endl

				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			chai.add(chaiscript::bootstrap::standard_library::vector_type<std::vector<double>>("std_vector_double"));
			chai.add(chaiscript::vector_conversion<std::vector<double>>());

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			//std::string address = ".\\system\\mesh2dToPlt";

			try
			{
				fileName myFileName(file::GetSystemFile("tnbShapeFitMaker"));
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