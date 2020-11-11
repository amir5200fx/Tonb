#pragma once
#ifndef _SectPx_NodeMaker_Header
#define _SectPx_NodeMaker_Header

#include <SectPx_Maker.hxx>
#include <OSstream.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Registry;
	class SectPx_Node;
	class SectPx_Pnt;

	namespace maker
	{

		class Node
			: public SectPx_Maker
		{

			/*Private Data*/


			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<SectPx_Maker>(*this);
			}


			Node()
			{}

		public:

			explicit Node
			(
				const std::shared_ptr<SectPx_Registry>& theRegistry
			)
				: SectPx_Maker(theRegistry)
			{}

			std::shared_ptr<SectPx_Node>
				SelectNode
				(
					const Standard_Integer theIndex
				) const;

			Standard_Integer
				CreateNode
				(
					const std::shared_ptr<SectPx_Pnt>& thePnt
				);

			std::shared_ptr<SectPx_Node>
				RemoveNode
				(
					const Standard_Integer theIndex
				);

			void Print(OSstream& out) const;

		};
	}

}

BOOST_CLASS_EXPORT_KEY(tnbLib::maker::Node);

#endif // !_SectPx_NodeMaker_Header
