#include <Global_Verbose.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

#include <chrono>
#include <iomanip>   // For std::put_time
#include <ctime>     // For std::localtime_s
#include <sstream>

unsigned short tnbLib::verbosity::info_level = 0;
tnbLib::VerbosityLevel tnbLib::verbosity::verbosity_level = tnbLib::VerbosityLevel::ERROR;
std::ostream* tnbLib::verbosity::output_stream = &std::cout;  // NOLINT(cppcoreguidelines-interfaces-global-init)

std::string tnbLib::Logger::get_level_string(const VerbosityLevel level)
{
	switch (level)
	{
	case VerbosityLevel::ERROR: return "ERROR";
	case VerbosityLevel::WARNING: return "WARNING";
	case VerbosityLevel::INFO: return "INFO";
	case VerbosityLevel::VERBOSE_INFO: return "VERBOSE_INFO";
	case VerbosityLevel::DEBUG: return "DEBUG";
	default:  // NOLINT(clang-diagnostic-covered-switch-default)
		return "UNKNOWN";
	}
}

std::string tnbLib::Logger::get_current_time()
{
	const auto now = std::chrono::system_clock::now();
	const std::time_t time = std::chrono::system_clock::to_time_t(now);

	std::tm tm{};
#if defined(_MSC_VER)  // Microsoft Visual C++
	if (localtime_s(&tm, &time) != 0)
	{
		FatalErrorIn(FunctionSIG) << "\n"
			<< "Failed to get local time using localtime_s" << "\n"
			<< abort(FatalError);
	}
#else  // POSIX (Linux/macOS)
	if (localtime_r(&time, &tm) == nullptr)
	{
		FatalErrorIn(FunctionSIG) << "\n"
			<< "Failed to get local time using localtime_r" << "\n"
			<< abort(FatalError);
	}
#endif

	std::stringstream ss;
	ss << std::put_time(&tm, "%c");  // Locale-specific date and time
	return ss.str();
}

void tnbLib::Logger::set_output_stream(std::ostream& stream)
{
	verbosity::output_stream = &stream;
}

void tnbLib::Logger::set_verbosity(const VerbosityLevel level)
{
	verbosity::verbosity_level = level;
}

void tnbLib::Logger::log(const VerbosityLevel level, const std::string& category, const std::string& message)
{
	if (level <= verbosity::verbosity_level)
	{
		*verbosity::output_stream << get_current_time() << "[" << get_level_string(level) << "] [" << category << "] "
			<< message
			<< "\n";
	}
}

unsigned short tnbLib::verbose(0);

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

void tnbLib::chai::add_verbose(const module_t& mod)
{
	mod->add(chaiscript::fun([](unsigned short i)-> void {verbose = i; }), "set_verbose");
}


