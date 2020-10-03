#pragma once
#ifndef _SectPx_ParameterFrame_Header
#define _SectPx_ParameterFrame_Header

#include <SectPx_ParsFwd.hxx>
#include <SectPx_MakersFwd.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Registry;

	namespace frame
	{

		class Parameter
		{

			/*Private Data*/

			std::shared_ptr<maker::Parameter> theParameter_;

		protected:

			Parameter(const std::shared_ptr<SectPx_Registry>& theReg);

		public:

			const auto& ParameterMaker() const
			{
				return theParameter_;
			}
		};
	}
}

#endif // !_SectPx_ParameterFrame_Header
