#include <SectPx_Frame.hxx>
#include <SectPx_Makers.hxx>
#include <SectPx_Pars.hxx>
#include <SectPx_FieldFuns.hxx>
#include <SectPx_Coord.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	typedef std::shared_ptr<SectPx_Frame> frame_t;

	typedef std::shared_ptr<maker::Parameter> parMaker_t;
	typedef std::shared_ptr<maker::FieldFun> fieldMaker_t;

	typedef std::shared_ptr<SectPx_Par> par_t;
	typedef std::shared_ptr<SectPx_FixedPar> fixed_t;
	typedef std::shared_ptr<SectPx_FreePar> free_t;
	typedef std::shared_ptr<SectPx_ConstPar> const_t;

	typedef std::shared_ptr<SectPx_FieldFun> fieldFun_t;
	typedef std::shared_ptr<sectPxLib::FieldFun_Expr> exprField_t;

	typedef std::shared_ptr<SectPx_Coord> coord_t;

	Pnt2d createGeoPoint(const double x, const double y)
	{
		Pnt2d p(x, y);
		return std::move(p);
	}

	auto createFree(const parMaker_t& m, const fieldFun_t& f)
	{
		auto t = std::dynamic_pointer_cast<SectPx_FreePar>(m->SelectParameter(m->CreateFree(f)));
		return std::move(t);
	}

	auto createFree(const parMaker_t& m, const word& name, const fieldFun_t& f)
	{
		auto t = std::dynamic_pointer_cast<SectPx_FreePar>(m->SelectParameter(m->CreateFree(name, f)));
		return std::move(t);
	}

	auto createFixed(const parMaker_t& m, const double x)
	{
		auto t = std::dynamic_pointer_cast<SectPx_FixedPar>(m->SelectParameter(m->CreateFixed(x)));
		return std::move(t);
	}

	auto createFixed(const parMaker_t& m, const word& name, const double x)
	{
		auto t = std::dynamic_pointer_cast<SectPx_FixedPar>(m->SelectParameter(m->CreateFixed(name, x)));
		return std::move(t);
	}

	auto createConstant(const parMaker_t& m, const double x)
	{
		auto t = std::dynamic_pointer_cast<SectPx_ConstPar>(m->SelectParameter(m->CreateConstant(x)));
		return std::move(t);
	}

	auto createConstant(const parMaker_t& m, const word& name, const double x)
	{
		auto t = std::dynamic_pointer_cast<SectPx_ConstPar>(m->SelectParameter(m->CreateConstant(name, x)));
		return std::move(t);
	}

	void removePar(const parMaker_t& m, const par_t& p)
	{
		auto t = m->RemoveParameter(p->Index());
		Debug_If_Condition(t NOT_EQUAL p);
	}

	/*par_t selectPar(const parMaker_t& m, const int id)
	{
		auto t = m->SelectParameter(id);
		return std::move(t);
	}*/

	auto createUniform(const fieldMaker_t& m, const par_t& p)
	{
		auto t = m->SelectFieldFun(m->CreateUniform(p));
		return std::move(t);
	}

	auto createMinus(const fieldMaker_t& m, const par_t& p)
	{
		auto t = m->SelectFieldFun(m->CreateInverse(p));
		return std::move(t);
	}

	auto createRead_x(const fieldMaker_t& m, const coord_t& pt)
	{
		auto t = m->SelectFieldFun(m->CreateReadingX(pt));
		return std::move(t);
	}

	auto createRead_y(const fieldMaker_t& m, const coord_t& pt)
	{
		auto t = m->SelectFieldFun(m->CreateReadingY(pt));
		return std::move(t);
	}

	auto createLinearForm(const fieldMaker_t& m, const fieldFun_t& f0, const fieldFun_t& f1, const par_t& t)
	{
		auto tt = m->SelectFieldFun(m->CreateLinearForm(f0, f1, t));
		return std::move(tt);
	}

	auto createExpr(const fieldMaker_t& m, const word& ex)
	{
		auto t = std::dynamic_pointer_cast<sectPxLib::FieldFun_Expr>(m->SelectFieldFun(m->CreateExpression(ex)));
		return std::move(t);
	}

	/*fieldFun_t selectField(const fieldMaker_t& m, const int id)
	{
		auto f = m->SelectFieldFun(id);
		return std::move(f);
	}*/

	void removeField(const fieldMaker_t& m, const fieldFun_t& f)
	{
		auto item = m->RemoveFieldFun(f->Index());
		Debug_If_Condition(item NOT_EQUAL f);
	}

	void addVariable(const exprField_t& f, const word& name, double& x)
	{
		if (NOT f->AddVariable(name, x))
		{
			FatalErrorIn(FunctionSIG)
				<< "the variable is not added!" << endl
				<< abort(FatalError);
		}
	}

	void addVariable(const exprField_t& f, const word& name, const fieldFun_t& x)
	{
		if (NOT f->AddVariable(name, *x))
		{
			FatalErrorIn(FunctionSIG)
				<< "the variable is not added!" << endl
				<< abort(FatalError);
		}
	}

	void addVariable(const exprField_t& f, const word& name, const fixed_t& x)
	{
		if (NOT f->AddVariable(name, *x))
		{
			FatalErrorIn(FunctionSIG)
				<< "the variable is not added!" << endl
				<< abort(FatalError);
		}
	}

	void addConstant(const exprField_t& f, const word& name, const double& x)
	{
		if (NOT f->AddConstant(name, x))
		{
			FatalErrorIn(FunctionSIG)
				<< "the variable is not added!" << endl
				<< abort(FatalError);
		}
	}

	void addConstant(const exprField_t& f, const word& name, const const_t& x)
	{
		if (NOT f->AddConstant(name, *x))
		{
			FatalErrorIn(FunctionSIG)
				<< "the variable is not added!" << endl
				<< abort(FatalError);
		}
	}

	void removeVariable(const exprField_t& f, const word& name)
	{
		if (NOT f->RemoveVariable(name))
		{
			FatalErrorIn(FunctionSIG)
				<< "the variable is not removed!" << endl
				<< abort(FatalError);
		}
	}

	void print(const frame_t& f)
	{
		f->PrintRegistry();
	}
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{
	typedef std::shared_ptr<chaiscript::Module> module_t;

	void setTypes(const module_t& mod)
	{
		mod->add(chaiscript::user_type<SectPx_Frame>(), "frame");
		mod->add(chaiscript::user_type<maker::Parameter>(), "paramMaker");
		mod->add(chaiscript::user_type<maker::FieldFun>(), "fieldFunMaker");

		mod->add(chaiscript::user_type<SectPx_FixedPar>(), "fixedPar");
		mod->add(chaiscript::user_type<SectPx_FreePar>(), "freePar");
		mod->add(chaiscript::user_type<SectPx_ConstPar>(), "constPar");
		mod->add(chaiscript::user_type<SectPx_Par>(), "par");

		mod->add(chaiscript::user_type<Pnt2d>(), "gPoint");
	}

	void setParameters(const module_t& mod)
	{
		mod->add(chaiscript::fun([](const parMaker_t& m, const fieldFun_t& f)-> auto {auto t = createFree(m, f); return std::move(t); }), "createFree");
		mod->add(chaiscript::fun([](const parMaker_t& m, const std::string& name, const fieldFun_t& f)-> auto {auto t = createFree(m, name, f); return std::move(t); }), "createFree");
		mod->add(chaiscript::fun([](const parMaker_t& m, const double x)-> auto {auto t = createFixed(m, x); }), "createFixed");
		mod->add(chaiscript::fun([](const parMaker_t& m, const std::string& name, const double x)-> auto {auto t = createFixed(m, name, x); return std::move(t); }), "createFixed");
		mod->add(chaiscript::fun([](const parMaker_t& m, const double x)-> auto {auto t = createConstant(m, x); return std::move(t); }), "createConstant");
		mod->add(chaiscript::fun([](const parMaker_t& m, const std::string& name, const double x)-> auto {auto t = createConstant(m, name, x); return std::move(t); }), "createConstant");
		//mod->add(chaiscript::fun([](const parMaker_t& m, const par_t& p)-> void {removePar(m, p); }), "remove");
		mod->add(chaiscript::fun([](const parMaker_t& m, const fixed_t& p)-> void {removePar(m, p); }), "remove");
		mod->add(chaiscript::fun([](const parMaker_t& m, const free_t& p)-> void {removePar(m, p); }), "remove");
		mod->add(chaiscript::fun([](const parMaker_t& m, const const_t& p)-> void {removePar(m, p); }), "remove");
	}

	void setField(const module_t& mod)
	{
		//mod->add(chaiscript::fun([](const fieldMaker_t& m, const par_t& p)-> auto {auto t = createUniform(m, p); return std::move(t); }), "createUniform");
		mod->add(chaiscript::fun([](const fieldMaker_t& m, const fixed_t& p)-> auto {auto t = createUniform(m, p); return std::move(t); }), "createUniform");
		mod->add(chaiscript::fun([](const fieldMaker_t& m, const free_t& p)-> auto {auto t = createUniform(m, p); return std::move(t); }), "createUniform");
		mod->add(chaiscript::fun([](const fieldMaker_t& m, const const_t& p)-> auto {auto t = createUniform(m, p); return std::move(t); }), "createUniform");
		//mod->add(chaiscript::fun([](const fieldMaker_t& m, const par_t& p)-> auto {auto t = createMinus(m, p); return std::move(t); }), "createMinus");
		mod->add(chaiscript::fun([](const fieldMaker_t& m, const fixed_t& p)-> auto {auto t = createMinus(m, p); return std::move(t); }), "createMinus");
		mod->add(chaiscript::fun([](const fieldMaker_t& m, const free_t& p)-> auto {auto t = createMinus(m, p); return std::move(t); }), "createMinus");
		mod->add(chaiscript::fun([](const fieldMaker_t& m, const const_t& p)-> auto {auto t = createMinus(m, p); return std::move(t); }), "createMinus");
		mod->add(chaiscript::fun([](const fieldMaker_t& m, const coord_t& pt)-> auto {auto t = createRead_x(m, pt); return std::move(t); }), "createReadX");
		mod->add(chaiscript::fun([](const fieldMaker_t& m, const coord_t& pt)-> auto {auto t = createRead_y(m, pt); return std::move(t); }), "createReadY");
		//mod->add(chaiscript::fun([](const fieldMaker_t& m, const fieldFun_t& f0, const fieldFun_t& f1, const par_t& t)-> auto {auto tt = createLinearForm(m, f0, f1, t); return std::move(tt); }), "createLinearForm");
		mod->add(chaiscript::fun([](const fieldMaker_t& m, const fieldFun_t& f0, const fieldFun_t& f1, const fixed_t& t)-> auto {auto tt = createLinearForm(m, f0, f1, t); return std::move(tt); }), "createLinearForm");
		mod->add(chaiscript::fun([](const fieldMaker_t& m, const fieldFun_t& f0, const fieldFun_t& f1, const free_t& t)-> auto {auto tt = createLinearForm(m, f0, f1, t); return std::move(tt); }), "createLinearForm");
		mod->add(chaiscript::fun([](const fieldMaker_t& m, const fieldFun_t& f0, const fieldFun_t& f1, const const_t& t)-> auto {auto tt = createLinearForm(m, f0, f1, t); return std::move(tt); }), "createLinearForm");
		mod->add(chaiscript::fun([](const fieldMaker_t& m, const std::string& ex)-> auto {auto t = createExpr(m, ex); return std::move(t); }), "createExpr");
	}

	void setFrame(const module_t& mod)
	{
		mod->add(chaiscript::fun([]() {auto t = std::make_shared<SectPx_Frame>(); return std::move(t); }), "newFrame");
		mod->add(chaiscript::fun([](const frame_t& f)-> void {print(f); }), "print");
		mod->add(chaiscript::fun([](const frame_t& f)-> auto {return f->ParameterMaker(); }), "getParamMaker");
		mod->add(chaiscript::fun([](const frame_t& f)-> auto {return f->FieldFunMaker(); }), "getFieldFunMaker");
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

			setTypes(mod);
			setFrame(mod);
			setParameters(mod);
			setField(mod);

			chai.add(mod);

			fileName myFileName("frameMaker");

			try
			{
				chai.eval_file(myFileName);
			}
			catch (const chaiscript::exception::eval_error& x)
			{
				std::cout << x.pretty_print();
				std::cout << '\n';
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

	return 0;
}