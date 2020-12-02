#pragma once
#ifndef _SectPx_Pnt_Header
#define _SectPx_Pnt_Header

#include <SectPx_Coord.hxx>
#include <SectPx_Parent.hxx>
#include <SectPx_PntType.hxx>

namespace tnbLib
{

	class SectPx_Pnt
		: public SectPx_Coord
		, public SectPx_Parent
	{

		/*Private Data*/

		friend boost::serialization::access;

		template<class Archive>
		void serialize(Archive &ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<SectPx_Coord>(*this);
			ar & boost::serialization::base_object<SectPx_Parent>(*this);
		}

	protected:

		template<class... _Types>
		SectPx_Pnt(_Types&&... _Args)
			: SectPx_Parent(_Args...)
		{}

	public:

		TnbSectPx_EXPORT virtual Standard_Boolean IsInner() const;

		TnbSectPx_EXPORT virtual Standard_Boolean IsOuter() const;

		TnbSectPx_EXPORT virtual Standard_Boolean IsMaster() const;

		TnbSectPx_EXPORT virtual Standard_Boolean IsSlave() const;

		virtual Standard_Boolean IsBoundary() const
		{
			return Standard_False;
		}

		virtual sectPxLib::pntType PntType() const = 0;

		TnbSectPx_EXPORT Standard_Boolean IsPnt() const override;

		TnbSectPx_EXPORT Standard_Boolean IsFrameRegObj() const override;

		TnbSectPx_EXPORT sectPxLib::regObjType RegObjType() const override;

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_Pnt);

#endif // !_SectPx_Pnt_Header
