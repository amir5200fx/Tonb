#include <Marine_Bodies.hxx>
#include <Marine_Models.hxx>
#include <StbGMaker_Model.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
#include <OFstream.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<StbGMaker_Model> stbModel_t;
	typedef std::shared_ptr<marineLib::Model_Hull> hull_t;
	typedef std::shared_ptr<marineLib::Model_Sail> sail_t;
	typedef std::shared_ptr<marineLib::Model_Tank> tank_t;
	typedef std::shared_ptr<Marine_Model> model_t;

	static stbModel_t stbModel;

	const auto& getStbModel()
	{
		if (NOT stbModel)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model has been loaded!" << endl
				<< abort(FatalError);
		}
		return stbModel;
	}

	std::string hasHull()
	{
		return ((bool)(getStbModel()->Hull()) ? ("YES") : ("NO"));
	}

	auto nbTanks()
	{
		return (int)getStbModel()->NbTanks();
	}

	auto nbSails()
	{
		return (int)getStbModel()->NbSails();
	}

	model_t getHull()
	{
		return getStbModel()->Hull();
	}

	model_t getTank(int i)
	{
		return getStbModel()->Tanks()[i];
	}


	//- io functions

	void loadStbModel(const std::string& name)
	{
		fileName fn(name);
		std::ifstream f(fn);
		boost::archive::polymorphic_text_iarchive oa(f);

		oa >> stbModel;
	}

	void save(const model_t& m, const std::string& name, const std::string& type = "model")
	{
		fileName fn(name);
		std::ofstream f(fn);
		boost::archive::polymorphic_text_oarchive oa(f);
		if (type == "model")
		{
			oa << m;
		}
		else if (type == "body")
		{
			if (m->IsHull())
			{
				auto hull = std::dynamic_pointer_cast<marineLib::Model_Hull>(m);
				if (hull)
				{
					const auto& b = hull->Body();
					if (b) Marine_Body::Save(oa, b);
				}
			}
			else if (m->IsTank())
			{
				auto tank = std::dynamic_pointer_cast<marineLib::Model_Tank>(m);
				if (tank)
				{
					const auto& b = tank->Body();
					if (b) Marine_Body::Save(oa, b);
				}
			}
			else
			{
				auto sail = std::dynamic_pointer_cast<marineLib::Model_ShapeSail>(m);
				if (sail)
				{
					const auto& b = sail->Body();
					if (sail)
					{
						const auto& b = sail->Body();
						if (b) Marine_Body::Save(oa, b);
					}
				}
			}
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "unrecognized command" << type << endl
				<< abort(FatalError);
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

		mod->add(chaiscript::fun([]()->auto{return nbTanks(); }), "getNbTanks");
		mod->add(chaiscript::fun([]()->auto {return nbSails(); }), "getNbSails");
		mod->add(chaiscript::fun([]()->auto {return hasHull(); }), "hasHull");

		mod->add(chaiscript::fun([]()->auto{return getHull(); }), "getHull");
		mod->add(chaiscript::fun([](int i)->auto{return getTank(i); }), "getTank");

		mod->add(chaiscript::fun([](const model_t& m, const std::string& name, const std::string& type)->void {save(m, name, type); }), "save");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadStbModel(name); }), "loadStbModel");
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

			chai.add(mod);

			fileName myFileName("selectBody");

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
		}
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

}