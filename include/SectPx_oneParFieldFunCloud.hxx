#pragma once
#ifndef _SectPx_oneParFieldFunCloud_Header
#define _SectPx_oneParFieldFunCloud_Header

#include <SectPx_FieldFunCloud.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_ParCloud;
	class SectPx_Registry;

	class SectPx_oneParFieldFunCloud
		: public SectPx_FieldFunCloud
	{

		/*Private Data*/

		std::weak_ptr<SectPx_ParCloud> thePar_;

	protected:

		template<class... _Types>
		SectPx_oneParFieldFunCloud(_Types&&... _Args)
			: SectPx_FieldFunCloud(_Args...)
		{}

	public:

		const auto& Par() const
		{
			return thePar_;
		}

		Standard_Integer NbChildren() const override;

		Standard_Boolean IsComplete() const override;

		Standard_Boolean HasChildren() const override;

		Standard_Boolean
			HasChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;

		std::vector<std::shared_ptr<SectPx_Child>>
			RetrieveChildren() const override;

		void RemoveThisFromChildren() const override;

		void AddThisToChildren() const override;

		void AddThisToChild
		(
			const std::shared_ptr<SectPx_Child>& thePar
		) const override;

		void RemoveThisFromChild
		(
			const std::shared_ptr<SectPx_Child>& thePar
		) const override;

		void SetPar
		(
			const std::shared_ptr<SectPx_ParCloud>& thePar
		);


		template<class FieldFun>
		static std::shared_ptr<FieldFun>
			Maker
			(
				const std::shared_ptr<SectPx_Registry>& theReg,
				const Standard_Integer theParId
			);
	};
}

#include <SectPx_oneParFieldFunCloudI.hxx>

#endif // !_SectPx_oneParFieldFunCloud_Header
