#pragma once
#ifndef _SectPx_PairedInterface_Header
#define _SectPx_PairedInterface_Header

#include <SectPx_Interface.hxx>
#include <SectPx_PairedInterfaceAdaptor.hxx>

namespace tnbLib
{

	class SectPx_PairedInterface
		: public SectPx_Interface
		, public SectPx_PairedInterfaceAdaptor
	{

		/*Private Data*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive &ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<SectPx_Interface>(*this);
			ar & boost::serialization::base_object<SectPx_PairedInterfaceAdaptor>(*this);
		}

	protected:

		template<class... _Types>
		SectPx_PairedInterface(_Types&&... _Args)
			: SectPx_Interface(_Args...)
		{}

		void disJoint() override;

	public:

		static const std::shared_ptr<SectPx_PairedInterface> null;

		Standard_Boolean IsPaired() const override;
		
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_PairedInterface);

#endif // !_SectPx_PairedInterface_Header
