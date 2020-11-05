#pragma once
#ifndef _SectPx_InterfaceMaker_Header
#define _SectPx_InterfaceMaker_Header

#include <SectPx_Maker.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Interface;
	class SectPx_Node;

	namespace maker
	{

		class Interface
			: public SectPx_Maker
		{

			/*Private Data*/


			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<SectPx_Maker>(*this);
			}


			Interface()
			{}

		public:

			Interface
			(
				const std::shared_ptr<SectPx_Registry>& theReg
			)
				: SectPx_Maker(theReg)
			{}


			std::shared_ptr<SectPx_Interface>
				SelectInterface
				(
					const Standard_Integer theIndex
				) const;

			std::shared_ptr<SectPx_Interface> RemoveInterface(const Standard_Integer theIndex) const;

			Standard_Integer
				CreateEmpty
				(
					const std::shared_ptr<SectPx_Node>& theNode
				) const;

			std::tuple<Standard_Integer, Standard_Integer>
				CreateJoint
				(
					const std::shared_ptr<SectPx_Node>& theNode0,
					const std::shared_ptr<SectPx_Node>& theNode1
				) const;


		};
	}
}

#endif // !_SectPx_InterfaceMaker_Header
