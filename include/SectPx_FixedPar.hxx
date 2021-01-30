#pragma once
#ifndef _SectPx_FixedPar_Header
#define _SectPx_FixedPar_Header

#include <SectPx_Par.hxx>
#include <SectPx_Value.hxx>

namespace tnbLib
{

	class SectPx_FixedPar
		: public SectPx_Par
	{

		/*Private Data*/

		sectPxLib::real theValue_;


		/*private functions and operators*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<SectPx_Par>(*this);
			ar & theValue_;
		}

		auto& ChangeValue()
		{
			return theValue_;
		}

	protected:

		SectPx_FixedPar()
		{}

	public:

		static TnbSectPx_EXPORT const char* typeName_;

		TnbSectPx_EXPORT explicit SectPx_FixedPar
		(
			const Standard_Real theValue
		);

		TnbSectPx_EXPORT SectPx_FixedPar
		(
			const Standard_Integer theIndex,
			const Standard_Real theValue
		);

		TnbSectPx_EXPORT SectPx_FixedPar
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Standard_Real theValue
		);

		auto X() const
		{
			return theValue_();
		}

		auto& X()
		{
			return theValue_();
		}

		TnbSectPx_EXPORT word RegObjTypeName() const override;

		TnbSectPx_EXPORT sectPxLib::parType ParType() const override;

		TnbSectPx_EXPORT Standard_Boolean IsFixed() const override;

		TnbSectPx_EXPORT Standard_Boolean IsComplete() const override;

		TnbSectPx_EXPORT Standard_Boolean InCycle() const override;

		TnbSectPx_EXPORT Standard_Real Value() const override;

		TnbSectPx_EXPORT void Print(Ostream& out) const override;

		Standard_Boolean IsChanged() const
		{
			return theValue_.IsChanged();
		}

		TnbSectPx_EXPORT void SetValue(const Standard_Real x);

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::SectPx_FixedPar);

#endif // !_SectPx_FixedPar_Header