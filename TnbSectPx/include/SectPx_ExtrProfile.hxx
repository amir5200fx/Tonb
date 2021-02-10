#pragma once
#ifndef _SectPx_ExtrProfile_Header
#define _SectPx_ExtrProfile_Header

#include <Pnt2d.hxx>
#include <SectPx_Parent.hxx>
#include <SectPx_ExtrProfileType.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Par;

	class SectPx_ExtrProfile
		: public SectPx_Parent
	{

		/*Private Data*/

		//std::weak_ptr<SectPx_Par> theStart_;
		//std::weak_ptr<SectPx_Par> theEnd_;

		/*private functions and operators*/

		//TNB_SERIALIZATION(TnbSectPx_EXPORT);

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<SectPx_Parent>(*this);
		}


	protected:


		template<class... _Types>
		SectPx_ExtrProfile(_Types&&... _Args)
			: SectPx_Parent(_Args...)
		{}

	public:

		virtual std::shared_ptr<SectPx_Par> Start() const = 0;

		virtual std::shared_ptr<SectPx_Par> End() const = 0;

		TnbSectPx_EXPORT Standard_Boolean IsShapeRegObj() const override;

		TnbSectPx_EXPORT Standard_Real Lower() const;

		TnbSectPx_EXPORT Standard_Real Upper() const;

		TnbSectPx_EXPORT sectPxLib::regObjType RegObjType() const override;

		TnbSectPx_EXPORT Standard_Boolean IsExtrProfile() const override;

		virtual SectPx_ExtrProfileType ExtrProfileType() const = 0;

		virtual Standard_Real MinLower() const = 0;

		virtual Standard_Real MaxUpper() const = 0;

		virtual Standard_Integer NbPoints() const = 0;

		virtual Pnt2d Point(const Standard_Integer theIndex) const = 0;

		virtual std::vector<Standard_Real> X() const = 0;
	};
}


BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_ExtrProfile);

#endif // !_SectPx_ExtrProfile_Header
