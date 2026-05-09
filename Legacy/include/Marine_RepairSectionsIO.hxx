#pragma once
#ifndef _Marine_RepairSectionsIO_Header
#define _Marine_RepairSectionsIO_Header

#include <Global_Serialization.hxx>
#include <Marine_Module.hxx>

#include <memory>

namespace tnbLib
{

	namespace marineLib
	{

		namespace io
		{

			// Forward Declarations
			class AnalysisSections;

			class RepairSections
			{

				/*Private Data*/

				std::shared_ptr<AnalysisSections> theAnalysis_;


			};
		}
	}
}

#endif // !_Marine_RepairSectionsIO_Header
