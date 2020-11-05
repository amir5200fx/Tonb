#pragma once
#ifndef _SectPx_TPnt_Header
#define _SectPx_TPnt_Header

#include <SectPx_Pnt.hxx>
#include <SectPx_TPntAdaptor.hxx>

namespace tnbLib
{

	class SectPx_TPnt
		: public SectPx_Pnt
		, public SectPx_TPntAdaptor
	{

		/*Private Data*/

		friend boost::serialization::access;

		template<class Archive>
		void serialize(Archive &ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<SectPx_Pnt>(*this);
			ar & boost::serialization::base_object<SectPx_TPntAdaptor>(*this);
		}

	protected:

		template<class... _Types>
		SectPx_TPnt(_Types&&... _Args)
		{}

	public:


	};
}

#endif // !_SectPx_TPnt_Header
