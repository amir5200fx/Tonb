#pragma once
#ifndef _SectPx_nonParFieldFun_Header
#define _SectPx_nonParFieldFun_Header

#include <SectPx_FieldFun.hxx>

namespace tnbLib
{

	class SectPx_nonParFieldFun
		: public SectPx_FieldFun
	{

		/*Private Data*/


		/*private functions and operators*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<SectPx_FieldFun>(*this);
		}

	protected:

		template<class... _Types>
		SectPx_nonParFieldFun(_Types&&... _Args)
			: SectPx_FieldFun(_Args...)
		{}

	public:

		TnbSectPx_EXPORT Standard_Boolean IsComplete() const override;

		TnbSectPx_EXPORT Standard_Boolean HasChild
		(
			const std::shared_ptr<SectPx_Child>& thePar
		) const override;

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

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_nonParFieldFun);

#endif // !_SectPx_nonParFieldFun_Header
