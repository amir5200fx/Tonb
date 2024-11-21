#pragma once
#ifndef _Global_Serialization_Header
#define _Global_Serialization_Header

#include <Global_CascadeTypes.hxx>

#ifndef BOOST_SERIALIZATION_DYN_LINK
#define BOOST_SERIALIZATION_DYN_LINK
#endif // !BOOST_SERIALIZATION_DYN_LINK

#ifndef BOOST_ALL_DYN_LINK
#define BOOST_ALL_DYN_LINK
#endif // !BOOST_ALL_DYN_LINK

#include <boost/serialization/config.hpp>
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
#include <boost/serialization/set.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/weak_ptr.hpp>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>

//#include <boost/archive/impl/archive_serializer_map.ipp>

#include <TnbError.hxx>
#include <OSstream.hxx>

#define TNB_iARCH_TYPE boost::archive::polymorphic_iarchive
#define TNB_oARCH_TYPE boost::archive::polymorphic_oarchive

#define TNB_iARCH_FILE_TYPE boost::archive::polymorphic_text_iarchive
#define TNB_oARCH_FILE_TYPE boost::archive::polymorphic_text_oarchive

#define TNB_SERIALIZATION(Export)	 														\
	template<class Archive> void save(Archive&, const unsigned int) const 							\
	{ FatalErrorIn(FunctionSIG) <<"not supposed to be called!"<< abort(FatalError); }				\
	template<class Archive> void load(Archive&, const unsigned int) 								\
	{ FatalErrorIn(FunctionSIG) <<"not supposed to be called!"<< abort(FatalError); }				\
	friend class boost::serialization::access;														\
	template<>																						\
	void Export save<TNB_oARCH_TYPE>(TNB_oARCH_TYPE & ar, const unsigned int version) const;		\
	template<>																						\
	void Export load<TNB_iARCH_TYPE>(TNB_iARCH_TYPE & ar, const unsigned int version);				\
	BOOST_SERIALIZATION_SPLIT_MEMBER()

#define TNB_SAVE_IMPLEMENTATION(C)															\
template<>																			\
void C::save<TNB_oARCH_TYPE>(TNB_oARCH_TYPE & ar, const unsigned int version) const

#define TNB_LOAD_IMPLEMENTATION(C) 									\
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
			ar >> st;
			g = std::move(st);
		}

		template<class Archive>
		void save(Archive& ar, const Standard_Real& x, const unsigned int file_version)
		{
			ar << x;
		}

		template<class Archive>
		void load(Archive& ar, Standard_Real& x, const unsigned int file_version)
		{
			ar >> x;
		}
	}
}

BOOST_SERIALIZATION_SPLIT_FREE(tnbLib::word)
BOOST_SERIALIZATION_SPLIT_FREE(Standard_Real)

#endif // !_Global_Serialization_Header
