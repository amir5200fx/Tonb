#pragma once
#ifndef _SectPx_InterfaceMaker_Header
#define _SectPx_InterfaceMaker_Header

#include <SectPx_Maker.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Interface;
	class SectPx_Node;
	class SectPx_FrameRegistry;

	namespace maker
	{

		class Interface
			: public SectPx_Maker<SectPx_FrameRegistry>
		{

			/*Private Data*/


			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<SectPx_Maker<SectPx_FrameRegistry>>(*this);
			}


			Interface()
			{}

		public:

			Interface
			(
				const std::shared_ptr<SectPx_FrameRegistry>& theReg
			)
				: SectPx_Maker<SectPx_FrameRegistry>(theReg)
			{}


			TnbSectPx_EXPORT std::shared_ptr<SectPx_Interface>
				SelectInterface
				(
					const Standard_Integer theIndex
				) const;

			TnbSectPx_EXPORT std::shared_ptr<SectPx_Interface> RemoveInterface(const Standard_Integer theIndex) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateEmpty
				(
					const std::shared_ptr<SectPx_Node>& theNode
				) const;

			TnbSectPx_EXPORT std::tuple<Standard_Integer, Standard_Integer>
				CreateJoint
				(
					const std::shared_ptr<SectPx_Node>& theNode0,
					const std::shared_ptr<SectPx_Node>& theNode1
				) const;


		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::maker::Interface);

#endif // !_SectPx_InterfaceMaker_Header
