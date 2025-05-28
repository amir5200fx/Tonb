#pragma once
#ifndef _Global_Verbose_Header
#define _Global_Verbose_Header
#include <Global_Module.hxx>
#include <Global_ChaiscriptFwd.hxx>

#include <cstdint>
#include <string>

#ifdef ERROR
#undef ERROR
#endif
namespace tnbLib
{
	// Verbosity levels
	enum class VerbosityLevel : uint8_t
	{
		ERROR = 0,
		WARNING = 1,
		INFO = 2,
		VERBOSE_INFO = 3,
		DEBUG = 4
	};

	namespace verbosity
	{
		extern TnbGlobal_EXPORT VerbosityLevel verbosity_level;
		extern TnbGlobal_EXPORT std::ostream* output_stream;
		extern TnbGlobal_EXPORT unsigned short info_level;
	}

	// Logging utility
	class Logger
	{
		/*Private Data*/

		static std::string get_level_string(VerbosityLevel);
		static std::string get_current_time();
	public:
		

		static void set_info_level(const unsigned short level) { verbosity::info_level = level; }
		static TnbGlobal_EXPORT void set_output_stream(std::ostream& stream);
		static TnbGlobal_EXPORT void set_verbosity(VerbosityLevel level);
		static TnbGlobal_EXPORT void log(VerbosityLevel, const std::string& category, const std::string& message);

		template<typename MessageFunc>
		static void log_lazy(const VerbosityLevel level, const std::string& category, MessageFunc func)
		{
			if (level <= verbosity::verbosity_level)
			{
				log(level, category, func());
			}
		}
	};
	extern TnbGlobal_EXPORT unsigned short verbose;

	namespace chai
	{
		TnbGlobal_EXPORT void add_verbose(const module_t&);
	}
}

// Macros for convenience
#define LOG_ERROR(category, msg) tnbLib::Logger::log(tnbLib::VerbosityLevel::ERROR, category, msg)
#define LOG_WARNING(category, msg) tnbLib::Logger::log(tnbLib::VerbosityLevel::WARNING, category, msg)
#define LOG_INFO(category, msg) tnbLib::Logger::log(tnbLib::VerbosityLevel::INFO, category, msg)
#define LOG_VERBOSE_INFO(category, msg) tnbLib::Logger::log(tnbLib::VerbosityLevel::VERBOSE_INFO, category, msg)
#define LOG_DEBUG(category, msg) tnbLib::Logger::log(tnbLib::VerbosityLevel::DEBUG, category, msg)

#define LOG_VERBOSE_INFO_LAZY(category, msgFunc) \
    tnbLib::Logger::log_lazy(tnbLib::VerbosityLevel::VERBOSE_INFO, category, msgFunc)

#define LOG_INFO_LAZY(category, msgFunc) \
    tnbLib::Logger::log_lazy(tnbLib::VerbosityLevel::INFO, category, msgFunc)
#define LOG_DEBUG_LAZY(category, msgFunc) \
    tnbLib::Logger::log_lazy(tnbLib::VerbosityLevel::DEBUG, category, msgFunc)
#define LOG_ERROR_LAZY(category, msgFunc) \
    tnbLib::Logger::log_lazy(tnbLib::VerbosityLevel::ERROR, category, msgFunc)
#define LOG_WARNING_LAZY(category, msgFunc) \
    tnbLib::Logger::log_lazy(tnbLib::VerbosityLevel::WARNING, category, msgFunc)
#endif