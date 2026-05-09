#pragma once
#ifndef _SectPx_FrameRegObj_Header
#define _SectPx_FrameRegObj_Header


#include <SectPx_RegObj.hxx>

namespace tnbLib
{

	class SectPx_FrameRegObj
		: public SectPx_RegObj
	{

		/*Private Data*/


		/*private functions and operators*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<SectPx_RegObj>(*this);
		}


	protected:

		template<class... _Types>
		SectPx_FrameRegObj(_Types&&... _Args)
			: SectPx_RegObj(_Args...)
		{}

	public:

		TnbSectPx_EXPORT Standard_Boolean IsFrameRegObj() const override;


	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_FrameRegObj);

#endif // !_SectPx_FrameRegObj_Header
