#pragma once
#ifndef _Global_Serialization_Header
#define _Global_Serialization_Header

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/export.hpp>

#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/weak_ptr.hpp>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>
//#include <boost/archive/polymorphic_text_iarchive.hpp>
//#include <boost/archive/polymorphic_text_oarchive.hpp>
//#include <boost/archive/polymorphic_iarchive.hpp>
//#include <boost/archive/polymorphic_oarchive.hpp>

#define TNB_iARCH_TYPE boost::archive::polymorphic_iarchive
#define TNB_oARCH_TYPE boost::archive::polymorphic_oarchive
#define TnbGlobal_EXPORT

#define DECLARE_SAVE_LOAD_HEADER(Export)	 														\
	template<class Archive> void save(Archive&, const unsigned int) const {}						\
	template<class Archive> void load(Archive&, const unsigned int) {}								\
	friend class boost::serialization::access;														\
	template<>																						\
	void Export save<TNB_oARCH_TYPE>(TNB_oARCH_TYPE & ar, const unsigned int version) const;		\
	template<>																						\
	void Export load<TNB_iARCH_TYPE>(TNB_iARCH_TYPE & ar, const unsigned int version);				\
	BOOST_SERIALIZATION_SPLIT_MEMBER()

#define DECLARE_SAVE_IMP(C)															\
template<>																			\
void C::save<TNB_oARCH_TYPE>(TNB_oARCH_TYPE & ar, const unsigned int version) const

#define DECLARE_LOAD_IMP(C) 									\
template<>														\
void C::load<TNB_iARCH_TYPE>(TNB_iARCH_TYPE & ar, const unsigned int version)	

#include <word.hxx>

namespace boost
{
	namespace serialization
	{

		template<class Archive>
		void save(Archive & ar, const tnbLib::word & g, const unsigned int version)
		{
			ar << (std::string)g;
		}

		template<class Archive>
		void load(Archive & ar, tnbLib::word & g, const unsigned int version)
		{
			std::string st;
			ar >> g;
			g = std::move(g);
		}
	}
}

BOOST_SERIALIZATION_SPLIT_FREE(tnbLib::word)

#endif // !_Global_Serialization_Header
