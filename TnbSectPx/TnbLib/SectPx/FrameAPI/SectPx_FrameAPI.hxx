#pragma once
#ifndef _SectPx_FrameAPI_Header
#define _SectPx_FrameAPI_Header

#include <Standard_TypeDef.hxx>
#include <SectPx_Module.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Frame;
	class SectPx_Par;
	class SectPx_FieldFun;

	class SectPx_FrameAPI
	{

	public:

		static TnbSectPx_EXPORT std::shared_ptr<SectPx_Frame> CreateFrame();

		static TnbSectPx_EXPORT std::shared_ptr<SectPx_Par> SelectParameter(const Standard_Integer theIndex, const std::shared_ptr<SectPx_Frame>& theFrame);
		static TnbSectPx_EXPORT std::shared_ptr<SectPx_Par> RemoveParameter(const Standard_Integer theIndex, const std::shared_ptr<SectPx_Frame>& theFrame);

		static TnbSectPx_EXPORT Standard_Integer CreateFreeParameter(const std::shared_ptr<SectPx_FieldFun>& theField, const std::shared_ptr<SectPx_Frame>& theFrame);
		static TnbSectPx_EXPORT Standard_Integer CreateFixedParameter(const Standard_Real x, const std::shared_ptr<SectPx_Frame>& theFrame);
		static TnbSectPx_EXPORT Standard_Integer CreateConstantParameter(const Standard_Real x, const std::shared_ptr<SectPx_Frame>& theFrame);

		static TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Par>> RetrieveFreeParameters(const std::shared_ptr<SectPx_Frame>&);
		static TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Par>> RetrieveFixedParameters(const std::shared_ptr<SectPx_Frame>&);
		static TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Par>> RetrieveConstantParameters(const std::shared_ptr<SectPx_Frame>&);
		static TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Par>> RetrieveParameters(const std::shared_ptr<SectPx_Frame>&);


		static TnbSectPx_EXPORT void Print(const std::shared_ptr<SectPx_Par>& p);
	};
}

#endif // !_SectPx_FrameAPI_Header
