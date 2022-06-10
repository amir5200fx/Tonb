#pragma once
#ifndef _SectPx_ConstPar_Header
#define _SectPx_ConstPar_Header

#include <SectPx_Par.hxx>
#include <SectPx_Value.hxx>

namespace tnbLib
{

	class SectPx_ConstPar
		: public SectPx_Par
	{

		/*Private Data*/

		Standard_Real theValue_;


		/*private functions and operators*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<SectPx_Par>(*this);
			ar & theValue_;
		}

	protected:

		SectPx_ConstPar()
		{}

	public:


		static TnbSectPx_EXPORT const char* typeName_;

		TnbSectPx_EXPORT explicit SectPx_ConstPar
		(
			const Standard_Real theValue
		);

		TnbSectPx_EXPORT SectPx_ConstPar
		(
			const Standard_Integer theIndex,
			const Standard_Real theValue
		);

		TnbSectPx_EXPORT SectPx_ConstPar
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Standard_Real theValue
		);

		auto X() const
		{
			return theValue_;
		}

		TnbSectPx_EXPORT word RegObjTypeName() const override;

		TnbSectPx_EXPORT sectPxLib::parType ParType() const override;

		TnbSectPx_EXPORT Standard_Boolean IsConstant() const override;

		TnbSectPx_EXPORT Standard_Boolean IsComplete() const override;

		TnbSectPx_EXPORT Standard_Boolean InCycle(const std::shared_ptr<SectPx_Parent>&) const override;

		TnbSectPx_EXPORT Standard_Real Value() const override;

		TnbSectPx_EXPORT void SetValue(const Standard_Real x);

		TnbSectPx_EXPORT void Print(Ostream& out) const override;
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::SectPx_ConstPar);

#endif // !_SectPx_ConstPar_Header
