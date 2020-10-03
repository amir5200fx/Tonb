#include "global_scripts.hxx"

#include <word.hxx>

#include <chaiscript/chaiscript.hpp>

void tnbLib::global_scripts(chaiscript::ChaiScript & chai)
{
	auto mod = std::make_shared<chaiscript::Module>();

	mod->add(chaiscript::user_type<word>(), "word");
	mod->add(chaiscript::constructor<word()>(), "word");
	mod->add(chaiscript::constructor<word(const word&)>(), "word");
	mod->add(chaiscript::constructor<word(const char*, const bool)>(), "word");
	mod->add(chaiscript::constructor<word(const std::string&, const bool)>(), "word");

	mod->add(chaiscript::fun(static_cast<void (word::*)(const char*)>(&word::operator=)), "=");
	mod->add(chaiscript::fun(static_cast<void (word::*)(const std::string&)>(&word::operator=)), "=");

	chai.add(mod);
}