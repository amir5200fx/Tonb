#pragma once
#ifndef _SectPx_Par_Header
#define _SectPx_Par_Header

#include <SectPx_Child.hxx>
#include <SectPx_ParType.hxx>
#include <Ostream.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Parent;

	class SectPx_Par
		: public SectPx_Child
	{

		/*Private Data*/


		/*private functions and operators*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<SectPx_Child>(*this);
		}

	protected:

		template<class... _Types>
		SectPx_Par(_Types&&... _Args)
			: SectPx_Child(_Args...)
		{}

	public:

		TnbSectPx_EXPORT sectPxLib::regObjType RegObjType() const override;

		virtual sectPxLib::parType ParType() const = 0;

		TnbSectPx_EXPORT virtual Standard_Boolean IsFixed() const;

		TnbSectPx_EXPORT virtual Standard_Boolean IsFree() const;

		TnbSectPx_EXPORT virtual Standard_Boolean IsConstant() const;

		virtual Standard_Boolean IsComplete() const = 0;

		virtual Standard_Boolean InCycle(const std::shared_ptr<SectPx_Parent>&) const = 0;

		virtual Standard_Real Value() const = 0;

		TnbSectPx_EXPORT Standard_Real operator()() const;

		virtual void Print(Ostream& out) const = 0;


		/*friend std::shared_ptr<SectPx_Par> operator+(const std::shared_ptr<SectPx_Par>& p0, const std::shared_ptr<SectPx_Par>& p1);
		friend std::shared_ptr<SectPx_Par> operator-(const std::shared_ptr<SectPx_Par>& p0, const std::shared_ptr<SectPx_Par>& p1);
		friend std::shared_ptr<SectPx_Par> operator*(const std::shared_ptr<SectPx_Par>& p0, const std::shared_ptr<SectPx_Par>& p1);
		friend std::shared_ptr<SectPx_Par> operator/(const std::shared_ptr<SectPx_Par>& p0, const std::shared_ptr<SectPx_Par>& p1);*/

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_Par);
//BOOST_CLASS_EXPORT_KEY(tnbLib::SectPx_Par);

#include <SectPx_ParI.hxx>

#endif // !_SectPx_Par_Header
