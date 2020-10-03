#pragma once
#ifndef _SectPx_RegistryFrame_Header
#define _SectPx_RegistryFrame_Header

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Registry;

	namespace frame
	{

		class Registry
		{

			/*Private Data*/

			std::shared_ptr<SectPx_Registry> theRegistry_;

		protected:

			Registry();

		public:

			const auto& Reg() const
			{
				return theRegistry_;
			}

		};
	}
}

#endif // !_SectPx_RegistryFrame_Header
