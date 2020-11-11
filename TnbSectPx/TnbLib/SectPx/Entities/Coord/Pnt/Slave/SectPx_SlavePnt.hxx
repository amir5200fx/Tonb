#pragma once
#ifndef _SectPx_SlavePnt_Header
#define _SectPx_SlavePnt_Header

#include <SectPx_TPnt.hxx>

namespace tnbLib
{

	class SectPx_SlavePnt
		: public SectPx_TPnt
	{

		/*Private Data*/


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive &ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<SectPx_TPnt>(*this);
		}

	protected:

		template<class... _Types>
		SectPx_SlavePnt(_Types&&... _Args)
			: SectPx_TPnt(_Args...)
		{}

	public:

		virtual Standard_Boolean IsEmpty() const;

		Standard_Boolean IsSlave() const override;

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_SlavePnt);

#endif // !_SectPx_SlavePnt_Header
