#pragma once
#ifndef _SectPx_Controller_Header
#define _SectPx_Controller_Header

#include <SectPx_Parent.hxx>

namespace tnbLib
{

	class SectPx_Controller
		: public SectPx_Parent
	{

		/*Private Data*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<SectPx_Parent>(*this);
		}

	protected:

		template<class... _Types>
		SectPx_Controller(_Types&&... _Args)
			: SectPx_Parent(_Args...)
		{}

	public:

		TnbSectPx_EXPORT virtual Standard_Boolean IsOnPole() const;

		TnbSectPx_EXPORT virtual Standard_Boolean IsOnSegment() const;

		TnbSectPx_EXPORT Standard_Boolean IsController() const override;

		TnbSectPx_EXPORT Standard_Boolean IsFrameRegObj() const override;

		TnbSectPx_EXPORT sectPxLib::regObjType RegObjType() const override;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_Controller);

#endif // !_SectPx_Controller_Header
