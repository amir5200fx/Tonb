#include <HydDyna_XFoil.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <vector>
#include <fstream>

namespace tnbLib
{

	int m_Iterations = 0;
	int s_IterLim = 100;
	bool m_bErrors = false;
	bool s_bAutoInitBL = true;

	static double reNumber = 100000;
	static double alpha = 0;
	static double mach = 0;
	static double nCrit = 9.0;
	static double maxAlpha = 15;
	static double alphaStep = 0.25;
	
	/*std::vector<double>*/double x[1000], y[1000], nx[1000], ny[1000];

	TNB_DEFINE_VERBOSE_OBJ;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setReNumber(double x)
	{
		reNumber = x;
		if (verbose)
		{
			Info << endl
				<< " - the Re number is set to: " << x << endl;
		}
	}

	void setMaxAlpha(double x)
	{
		maxAlpha = x;
		if (verbose)
		{
			Info << endl
				<< " - the max. angle is set to: " << x << endl;
		}
	}

	void setAngleStep(double x)
	{
		alphaStep = x;
		if (verbose)
		{
			Info << endl
				<< " - the angle step is set to: " << x << endl;
		}
	}

	int loadDataFile(const std::string& theName)
	{
		std::ifstream fs(theName);
		if (!fs)
		{
			std::cout << "Failed to open dat file" << std::endl;
			return -1;
		}
		std::string line;
		std::getline(fs, line);
		std::cout << "Foil name : " << line << std::endl;
		int cnt = 0;
		while (!fs.eof()) {
			std::getline(fs, line);

			line.erase(0, line.find_first_not_of(" \t"));
			const int endOfX = line.find_first_of(" \t");
			if (endOfX == -1) continue;

			std::string sx = line.substr(0, endOfX);
			std::string sy = line.substr(endOfX);

			x[cnt] = atof(sx.c_str());
			y[cnt] = atof(sy.c_str());
			//x.emplace_back(atof(sx.c_str()));
			//y.emplace_back(atof(sy.c_str()));
			cnt++;
		}
		return cnt;
	}
	
	bool iterate(const std::shared_ptr<XFoil>& foil)
	{
		if (!foil->viscal()) {
			foil->lvconv = false;
			std::cout
				<< "CpCalc: local speed too large\nCompressibility corrections invalid"
				<< std::endl;
			return false;
		}
		while (m_Iterations < s_IterLim && !foil->lvconv /*&& !s_bCancel*/) {
			if (foil->ViscousIter()) {
				// if (m_x0 && m_y0) {
				//  m_x0->append((double)m_Iterations);
				//  m_y0->append(foil->rmsbl);
				//}
				// if (m_x1 && m_y1) {
				//  m_x1->append((double)m_Iterations);
				//  m_y1->append(foil->rmxbl);
				//}
				m_Iterations++;
			}
			else
				m_Iterations = s_IterLim;
		}

		if (!foil->ViscalEnd()) {
			foil->lvconv = false;  // point is unconverged

			foil->setBLInitialized(false);
			foil->lipan = false;
			m_bErrors = true;
			return true;  // to exit loop
		}

		if (m_Iterations >= s_IterLim && !foil->lvconv) {
			if (s_bAutoInitBL) {
				foil->setBLInitialized(false);
				foil->lipan = false;
			}
			foil->fcpmin();  // Is it of any use ?
			return true;
		}
		if (!foil->lvconv) {
			m_bErrors = true;
			foil->fcpmin();  // Is it of any use ?
			return false;
		}
		else {
			// converged at last
			foil->fcpmin();  // Is it of any use ?
			return true;
		}
		return false;
	}

	int execute(const std::string& name)
	{
		int n = 0;

		std::stringstream ss;
		n = loadDataFile(name);
		if(verbose)
		{
			Info << "nb of points: " << n << endl;
		}
		if (n == -1) return 1;

		const auto foil = std::make_shared<XFoil>();

		if (!foil->initXFoilGeometry(n,x,y,nx,ny))
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "Initialization error!" << endl
				<< abort(FatalError);
		}
		if (!foil->initXFoilAnalysis(100000, 0, 0.0, 9.0, 1.0, 1.0, 1, 1, true, ss)) {
			FatalErrorIn(FunctionSIG) << endl
				<< "Initialization error!" << endl
				<< abort(FatalError);
		}
		for (double alpha = 0; alpha < maxAlpha; alpha += alphaStep) 
		{
			m_Iterations = 0;
			foil->setBLInitialized(false);
			foil->lipan = false;

			foil->setAlpha(alpha * 3.14159 / 180);
			foil->lalfa = true;
			foil->setQInf(1.0);
			std::cout << "alpha : " << alpha << std::endl;

			if (!foil->specal()) {
				std::cout << "Invalid Analysis Settings" << std::endl;
				return 1;
			}
			foil->lwake = false;
			foil->lvconv = false;

			while (!iterate(foil))
				;

			// std::cout << ss.str() << std::endl;

			if (foil->lvconv) {
				std::cout << "  converged after " << m_Iterations << " iterations"
					<< std::endl;
				std::cout << "  cl : " << foil->cl << ", cd : " << foil->cd
					<< ", cm : " << foil->cm << ", xcp : " << foil->xcp
					<< std::endl;
			}
			else {
				std::cout << "  unconverged" << std::endl;
			}
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

	void setFuns(const module_t& mod)
	{
		// io functions 

		// settings 

		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");
		mod->add(chaiscript::fun([](double x)-> void {setReNumber(x); }), "setReNumber");
		mod->add(chaiscript::fun([](double x)-> void {setAngleStep(x); }), "setAngleStep");
		mod->add(chaiscript::fun([](double x)-> void {setMaxAlpha(x); }), "setMaxAngle");

		// operators 
		mod->add(chaiscript::fun([](const std::string& name)-> void {execute(name); }), "execute");
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
			Info << " This application is aimed to calulate the lift and the drag of an airfoil." << endl << endl;
			
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int); Levels: 0, 1" << endl << endl

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
				fileName myFileName(file::GetSystemFile("tnbSolverXFoil"));

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