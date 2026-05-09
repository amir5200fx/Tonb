#include <IO_Scripts.hxx>

#include <TecPlot.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
#include <messageStream.hxx>

#include <Pnt2d.hxx>
#include <vector.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

void tnbLib::script::load_io_tecplot(chaiscript::ChaiScript& chai)
{
	auto mod = std::make_shared<chaiscript::Module>();

	mod->add(chaiscript::fun(static_cast<void (*)(const std::vector<Pnt2d>&, OFstream&)>(&Io::ExportCurve)), "tecPlot_exportCurve");

	chai.add(mod);
}