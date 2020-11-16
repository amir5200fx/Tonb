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

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive &ar, const unsigned int file_version);

		//DECLARE_SAVE_LOAD_HEADER(TnbSectPx_EXPORT);

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

		TnbSectPx_EXPORT Standard_Integer NbChildren() const override;

		TnbSectPx_EXPORT Standard_Boolean IsComplete() const override;

		TnbSectPx_EXPORT Standard_Boolean HasChildren() const override;

		TnbSectPx_EXPORT Standard_Boolean
			HasChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;

		TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Child>> RetrieveChildren() const override;

		TnbSectPx_EXPORT void RemoveThisFromChildren() const override;

		TnbSectPx_EXPORT void AddThisToChildren() const override;

		TnbSectPx_EXPORT void AddThisToChild
		(
			const std::shared_ptr<SectPx_Child>& thePar
		) const override;

		TnbSectPx_EXPORT void RemoveThisFromChild
		(
			const std::shared_ptr<SectPx_Child>& thePar
		) const override;

		TnbSectPx_EXPORT void SetPar
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

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_oneParFieldFun);

#include <SectPx_oneParFieldFunI.hxx>

#endif // !_SectPx_oneParFieldFun_Header
