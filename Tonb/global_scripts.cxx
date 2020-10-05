#include "global_scripts.hxx"

#include <word.hxx>
#include <fileName.hxx>
#include <OFstream.hxx>

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

	mod->add(chaiscript::user_type<fileName>(), "fileName");
	mod->add(chaiscript::constructor<fileName()>(), "fileName");
	mod->add(chaiscript::constructor<fileName(const word&)>(), "fileName");
	mod->add(chaiscript::constructor<fileName(const std::string&)>(), "fileName");
	mod->add(chaiscript::constructor<fileName(const char*)>(), "fileName");

	mod->add(chaiscript::user_type<OFstream>(), "ofstream");
	mod->add(chaiscript::constructor<OFstream(const fileName&)>(), "ofstream");
	mod->add(chaiscript::constructor<OFstream(const fileName&, IOstream::streamFormat)>(), "ofstream");
	mod->add(chaiscript::constructor<OFstream(const fileName&, IOstream::streamFormat, IOstream::versionNumber)>(), "ofstream");
	mod->add(chaiscript::constructor<OFstream(const fileName&, IOstream::streamFormat, IOstream::versionNumber, IOstream::compressionType)>(), "ofstream");
	mod->add(chaiscript::constructor<OFstream(const fileName&, IOstream::streamFormat, IOstream::versionNumber, IOstream::compressionType, const bool)>(), "ofstream");

	chai.add(mod);
}