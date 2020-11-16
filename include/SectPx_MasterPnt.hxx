#pragma once
#ifndef _SectPx_MasterPnt_Header
#define _SectPx_MasterPnt_Header

#include <SectPx_TPnt.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Overrider;

	class SectPx_MasterPnt
		: public SectPx_TPnt
	{

		/*Private Data*/

		std::shared_ptr<SectPx_Overrider> theOverrider_;

		Standard_Boolean applyOverrider_;


		DECLARE_SAVE_LOAD_HEADER(TnbSectPx_EXPORT);

	protected:

		template<class... _Types>
		SectPx_MasterPnt(_Types&&... _Args)
			: SectPx_TPnt(_Args...)
			, applyOverrider_(Standard_True)
		{}

	public:

		TnbSectPx_EXPORT virtual Standard_Boolean IsComponent() const;

		TnbSectPx_EXPORT virtual Standard_Boolean IsGeoField() const;

		TnbSectPx_EXPORT virtual Standard_Boolean IsOffset() const;

		TnbSectPx_EXPORT Standard_Boolean IsMaster() const override;

		Standard_Boolean HasOverrider() const
		{
			return (Standard_Boolean)theOverrider_;
		}

		Standard_Boolean ApplyOverrider() const
		{
			return applyOverrider_;
		}

		const auto& Overrider() const
		{
			return theOverrider_;
		}

		TnbSectPx_EXPORT void SetOverrider
		(
			const std::shared_ptr<SectPx_Overrider>& theOverrider
		);

		void SetApplyOverrider(const Standard_Boolean apply)
		{
			applyOverrider_ = apply;
		}
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_MasterPnt);

#endif // !_SectPx_MasterPnt_Header
