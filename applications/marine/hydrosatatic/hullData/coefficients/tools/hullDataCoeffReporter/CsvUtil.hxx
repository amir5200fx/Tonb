#pragma once
#ifndef _CsvUtil_Header
#define _CsvUtil_Header


// This may look like C code, but it's really -*- C++ -*-
/*
 * Copyright (C) 2008 Emweb bv, Herent, Belgium.
 *
 * See the LICENSE file for terms of use.
 */

#include <iostream>

namespace Wt {
	class WAbstractItemModel;
}

/**
 * @addtogroup chartsexample
 */
 /*@{*/

 /*! \brief Utility function that reads a model from a CSV file.
  */
extern void readFromCsv(std::istream& f, Wt::WAbstractItemModel *model,
	int numRows = -1, bool firstLineIsHeaders = true);

#endif // !_CsvUtil_Header
