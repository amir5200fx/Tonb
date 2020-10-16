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

	protected:

		template<class... _Types>
		SectPx_MasterPnt(_Types&&... _Args)
			: SectPx_TPnt(_Args...)
			, applyOverrider_(Standard_True)
		{}

	public:

		virtual Standard_Boolean IsComponent() const;

		virtual Standard_Boolean IsGeoField() const;

		virtual Standard_Boolean IsOffset() const;

		Standard_Boolean IsMaster() const override;

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

		void SetOverrider
		(
			const std::shared_ptr<SectPx_Overrider>& theOverrider
		);

		void SetApplyOverrider(const Standard_Boolean apply)
		{
			applyOverrider_ = apply;
		}
	};
}

#endif // !_SectPx_MasterPnt_Header
