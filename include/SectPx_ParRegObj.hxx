#pragma once
#ifndef _SectPx_ParRegObj_Header
#define _SectPx_ParRegObj_Header

#include <SectPx_RegObj.hxx>

namespace tnbLib
{

	class SectPx_ParRegObj
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
		SectPx_ParRegObj(_Types&&... _Args)
			: SectPx_Entity(_Args...)
		{}

	public:

		Standard_Boolean IsParRegObj() const override;
	};
}


BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_ParRegObj);

#endif // !_SectPx_ParRegObj_Header
