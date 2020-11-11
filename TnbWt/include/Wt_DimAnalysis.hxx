#pragma once
#ifndef _Wt_DimAnalysis_Header
#define _Wt_DimAnalysis_Header

#include <wt/WContainerWidget.h>

namespace tnbLib
{

	namespace wt
	{

		namespace hydrostatic
		{

			class DimAnalysis
				: public Wt::WContainerWidget
			{

				/*Private Data*/

				Wt::WText* theTitile_;

			public:

				DimAnalysis();


			};
		}
	}
}

#endif // !_Wt_DimAnalysis_Header
