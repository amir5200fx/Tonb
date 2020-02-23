#pragma once
#ifndef _Marine_Rgion_Header
#define _Marine_Rgion_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>

#include <memory>

namespace tnbLib
{

	class Marine_Rgion
		: public Global_Indexed
		, public Global_Named
		, public std::enable_shared_from_this<Marine_Rgion>
	{

		/*Private Data*/

	protected:

		Marine_Rgion();

		Marine_Rgion(const Standard_Integer theIndex);

		Marine_Rgion(const Standard_Integer theIndex, const word& theName);

	public:

		virtual ~Marine_Rgion()
		{}


	};
}

#endif // !_Marine_Rgion_Header
