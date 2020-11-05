#pragma once
#ifndef _SectPx_FieldCloud_Header
#define _SectPx_FieldCloud_Header

#include <SectPx_Cloud.hxx>
#include <SectPx_ParsFwd.hxx>

namespace tnbLib
{

	class SectPx_FieldCloud
		: public SectPx_Cloud
	{

		/*Private Data*/


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive &ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<SectPx_Cloud>(*this);
		}

	protected:

		template<class... _Types>
		SectPx_FieldCloud(_Types&&... _Args)
			: SectPx_Cloud(_Args...)
		{}

	public:

		
		
	};
}

#endif // !_SectPx_FieldCloud_Header
