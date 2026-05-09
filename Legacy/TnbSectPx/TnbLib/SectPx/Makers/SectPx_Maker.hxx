#pragma once
#ifndef _SectPx_Maker_Header
#define _SectPx_Maker_Header

#include <SectPx_Entity.hxx>
#include <SectPx_Module.hxx>
#include <SectPx_ParRegistry.hxx>
#include <SectPx_FrameRegistry.hxx>
#include <SectPx_ShapeRegistry.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_ParRegistry;
	class SectPx_FrameRegistry;
	class SectPx_ShapeRegistry;

	template<class RegType>
	class SectPx_Maker
		: public SectPx_Entity
	{

		/*Private Data*/

		std::shared_ptr<RegType> theRegistry_;


		//TNB_SERIALIZATION(TnbSectPx_EXPORT);

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive &ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<SectPx_Entity>(*this);
			ar & theRegistry_;
		}


	protected:

		SectPx_Maker()
		{}

		SectPx_Maker
		(
			const std::shared_ptr<RegType>& theReg
		)
			: theRegistry_(theReg)
		{}


	public:

		const auto& Registry() const
		{
			return theRegistry_;
		}

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_Maker<SectPx_ParRegistry>);
BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_Maker<SectPx_FrameRegistry>);
BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_Maker<SectPx_ShapeRegistry>);

#endif // !_SectPx_Maker_Header
