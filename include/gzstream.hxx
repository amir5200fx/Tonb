#pragma once
#ifndef _gzstream_Header
#define _gzstream_Header

#include <iostream>
#include <fstream>
#include <zlib.h>

//#define GZSTREAM_NAMESPACE gzstream

#ifdef GZSTREAM_NAMESPACE
namespace GZSTREAM_NAMESPACE {
#endif

	// ----------------------------------------------------------------------------
	//    Internal classes to implement gzstream. See below for user classes.
	// ----------------------------------------------------------------------------

	// ----------------------------------------------------------------------------
	//    class gzstreambuf
	// ----------------------------------------------------------------------------

	class gzstreambuf
		: public std::streambuf
	{
	private:

		//------------------------------------

		static const int bufferSize = 47 + 256;
		// totals 512 bytes under g++ for igzstream at the end.

		//------------------------------------
		gzFile           file;
		char             buffer[bufferSize];
		char             opened;
		int              mode;


		//------------------------------------

		int flush_buffer();

	public:

		//------------------------------------

		gzstreambuf()
			: opened(0)
		{
			setp(buffer, buffer + (bufferSize - 1));
			setg(buffer + 4,     // beginning of putback area
				buffer + 4,     // read position
				buffer + 4);    // end position
		  // ASSERT: both input & output capabilities will not be used together
		}
		~gzstreambuf()
		{
			close();
		}

		//------------------------------------

		int is_open()
		{
			return opened;
		}
		gzstreambuf* open(const char* name, int open_mode);
		gzstreambuf* close();
		virtual int     overflow(int c = EOF);
		virtual int     underflow();
		virtual int     sync();
	};

	// ----------------------------------------------------------------------------
	//    class gzstreambase
	// ----------------------------------------------------------------------------

	class gzstreambase
		: virtual public std::ios
	{
	protected:

		//------------------------------------

		gzstreambuf buf;

	public:

		//------------------------------------

		gzstreambase()
		{
			init(&buf);
		}
		gzstreambase(const char* _name, int _open_mode);
		~gzstreambase();

		//------------------------------------

		void open(const char* _name, int _open_mode);
		void close();
		gzstreambuf* rdbuf()
		{
			return &buf;
		}
	};

	// ----------------------------------------------------------------------------
	// User classes. Use igzstream and ogzstream analogously to ifstream and
	// ofstream respectively. They read and write files based on the gz*
	// function interface of the zlib. Files are compatible with gzip compression.
	// ----------------------------------------------------------------------------

	// ----------------------------------------------------------------------------
	//    class igzstream
	// ----------------------------------------------------------------------------

	class igzstream
		: public std::istream
		, public gzstreambase
	{
	public:

		//------------------------------------

		igzstream()
			: std::istream(&buf)
		{}
		igzstream(const char*  _name,
			int          _open_mode = std::ios::in)
			: std::istream(&buf)
			, gzstreambase(_name, _open_mode)
		{}

		//------------------------------------

		gzstreambuf* rdbuf()
		{
			return gzstreambase::rdbuf();
		}
		void open(const char*  _name,
			int          _open_mode = std::ios::in)
		{
			gzstreambase::open(_name, _open_mode);
		}
	};

	// ----------------------------------------------------------------------------
	//    class ogzstream
	// ----------------------------------------------------------------------------

	class ogzstream
		: public gzstreambase
		, public std::ostream
	{
	public:

		//------------------------------------

		ogzstream()
			: std::ostream(&buf)
		{}
		explicit
			ogzstream(const char* _name,
				int         _open_mode = std::ios::out)
			: gzstreambase(_name, _open_mode)
			, std::ostream(&buf)
		{}

		//------------------------------------

		gzstreambuf* rdbuf()
		{
			return gzstreambase::rdbuf();
		}
		void open(const char*  _name,
			int          _open_mode = std::ios::out)
		{
			gzstreambase::open(_name, _open_mode);
		}
	};

#ifdef GZSTREAM_NAMESPACE
} // namespace GZSTREAM_NAMESPACE
#endif

#endif // !_gzstream_Header
