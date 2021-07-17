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

		friend class boost::serialization::access;

	public:

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

			/*template <class Archive>
			void save(Archive&, const unsigned int) const
			{
			}

			template <class Archive>
			void load(Archive&, const unsigned int)
			{
			}*/

			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive& ar, const unsigned int version);

			/*template <>
			void save<TNB_oARCH_TYPE>(TNB_oARCH_TYPE& ar, const unsigned int version) const;
			template <>
			void load<TNB_iARCH_TYPE>(TNB_iARCH_TYPE& ar, const unsigned int version);
			template <class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				boost::serialization::split_member(ar, *this, file_version);
			};*/
		};

	private:

		/*Private Data*/

		

		std::map<Standard_Integer, Pair>
			theParents_;


		/*private functions and operators*/

		

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & theParents_;
		}

		TnbSectPx_EXPORT void Add
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<SectPx_Parent>& theParent
		);

	protected:

		SectPx_ParentAdaptor()
		{}

		TnbSectPx_EXPORT std::weak_ptr<SectPx_Parent>
			SelectParent
			(
				const Standard_Integer theIndex
			);

		TnbSectPx_EXPORT std::weak_ptr<SectPx_Parent>
			RemoveFromParents
			(
				const Standard_Integer theIndex
			);

		TnbSectPx_EXPORT void ImportToParents
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

		TnbSectPx_EXPORT Standard_Boolean 
			HasThisParent
			(
				const std::shared_ptr<SectPx_Parent>&
			) const;
	};
}

#include <SectPx_ParentAdaptorI.hxx>

#endif // !_SectPx_ParentAdaptor_Header
