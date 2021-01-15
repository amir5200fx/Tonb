#pragma once
#ifndef _Marine_HsGraph_Header
#define _Marine_HsGraph_Header

#include <Global_Named.hxx>
#include <Global_Indexed.hxx>

#include <memory>

namespace tnbLib
{

	class Marine_HsGraph
		: public Global_Indexed
		, public Global_Named
	{

		/*Private Data*/

	protected:

		Marine_HsGraph();

		Marine_HsGraph(const Standard_Integer theIndex);

		Marine_HsGraph(const Standard_Integer theIndex, const word& theName);

	public:

		virtual ~Marine_HsGraph()
		{}
	};
}

#endif // !_Marine_HsGraph_Header
