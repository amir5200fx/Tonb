#pragma once
#ifndef _SectPx_oneParFieldFun_Header
#define _SectPx_oneParFieldFun_Header

#include <SectPx_FieldFun.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Registry;

	class SectPx_oneParFieldFun
		: public SectPx_FieldFun
	{

		/*Private Data*/

		std::weak_ptr<SectPx_Par> thePar_;

	protected:

		template<class... _Types>
		SectPx_oneParFieldFun(_Types&&... _Args)
			: SectPx_FieldFun(_Args...)
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
				const std::shared_ptr<SectPx_Par>& thePar
			) const override;

		std::vector<std::shared_ptr<SectPx_Child>> RetrieveChildren() const override;

		void RemoveThisFromChilds() const override;

		void AddThisToChilds() const override;

		void AddThisToChild
		(
			const std::shared_ptr<SectPx_Par>& thePar
		) const override;

		void RemoveThisFromChild
		(
			const std::shared_ptr<SectPx_Par>& thePar
		) const override;

		void SetPar
		(
			const std::shared_ptr<SectPx_Par>& thePar
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

#include <SectPx_oneParFieldFunI.hxx>

#endif // !_SectPx_oneParFieldFun_Header
