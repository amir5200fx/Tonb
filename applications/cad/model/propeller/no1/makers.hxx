#pragma once
#ifndef _makers_Header
#define _makers_Header

#include <PtdModel_FormMaker.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{
	typedef std::shared_ptr<PtdModel_FormMaker> maker_t;

	extern std::shared_ptr<std::vector<maker_t>> myMakers;
}

#endif // !_makers_Header
