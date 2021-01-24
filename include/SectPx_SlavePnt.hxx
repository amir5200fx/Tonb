#pragma once
#ifndef _SectPx_SlavePnt_Header
#define _SectPx_SlavePnt_Header

#include <SectPx_TPnt.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_MasterPnt;

	class SectPx_SlavePnt
		: public SectPx_TPnt
	{

		/*Private Data*/

		std::shared_ptr<SectPx_MasterPnt> theMaster_;

		TNB_SERIALIZATION(TnbSectPx_EXPORT);

	protected:

		SectPx_SlavePnt()
		{}

		TnbSectPx_EXPORT SectPx_SlavePnt
		(
			const std::shared_ptr<SectPx_MasterPnt>& theMaster
		);

		TnbSectPx_EXPORT SectPx_SlavePnt
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<SectPx_MasterPnt>& theMaster
		);

		TnbSectPx_EXPORT SectPx_SlavePnt
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<SectPx_MasterPnt>& theMaster
		);

	public:

		const auto& Master() const
		{
			return theMaster_;
		}

		TnbSectPx_EXPORT void SetMaster
		(
			const std::shared_ptr<SectPx_MasterPnt>& theMaster
		);

		TnbSectPx_EXPORT virtual Standard_Boolean IsEmpty() const;

		TnbSectPx_EXPORT Standard_Boolean IsSlave() const override;

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_SlavePnt);

#endif // !_SectPx_SlavePnt_Header
