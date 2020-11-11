#pragma once
#ifndef _SectPx_ParentAdaptor_Header
#define _SectPx_ParentAdaptor_Header

#include <Standard_TypeDef.hxx>
#include <Global_Serialization.hxx>
#include <SectPx_Module.hxx>

#include <map>
#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Parent;
	class SectPx_ParTools;
	class SectPx_PntTools;

	class SectPx_ParentAdaptor
	{

		friend class SectPx_ParTools;
		friend class SectPx_PntTools;

		/*Private Data*/

		struct Pair
		{
			std::weak_ptr<SectPx_Parent> Parent;
			Standard_Integer K;


			Pair()
			{}

			Pair(const std::weak_ptr<SectPx_Parent>& theParent)
				: Parent(theParent)
				, K(1)
			{}

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int version)
			{
				
			}
			//DECLARE_SAVE_LOAD_HEADER(TnbSectPx_EXPORT);
		};

		std::map<Standard_Integer, Pair>
			theParents_;


		/*private functions and operators*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & theParents_;
		}

		void Add
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<SectPx_Parent>& theParent
		);

	protected:

		SectPx_ParentAdaptor()
		{}

		std::weak_ptr<SectPx_Parent>
			SelectParent
			(
				const Standard_Integer theIndex
			);

		std::weak_ptr<SectPx_Parent>
			RemoveFromParents
			(
				const Standard_Integer theIndex
			);

		void ImportToParents
		(
			const std::shared_ptr<SectPx_Parent>& theParent
		);

	public:

		auto NbParents() const
		{
			return (Standard_Integer)theParents_.size();
		}

		const auto& Parents() const
		{
			return theParents_;
		}
	};
}

#endif // !_SectPx_ParentAdaptor_Header
