#pragma once
#ifndef _SectPx_Registry_Header
#define _SectPx_Registry_Header

#include <SectPx_Entity.hxx>
#include <Geo_ItemCounter.hxx>
#include <SectPx_RegObjType.hxx>
#include <SectPx_Module.hxx>
#include <SectPx_ScatterRegistry.hxx>
#include <Ostream.hxx>

#include <map>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_RegObj;
	class SectPx_Par;

	class SectPx_Registry
		: public SectPx_Entity
		, public SectPx_ScatterRegistry
	{

		/*Private Data*/

		std::map<Standard_Integer, std::shared_ptr<SectPx_RegObj>>
			theObjects_;

		mutable Geo_ItemCounter theCounter_;


		//- private functions and operators


		TNB_SERIALIZATION(TnbSectPx_EXPORT);

		auto& Counter() const
		{
			return theCounter_;
		}

		TnbSectPx_EXPORT std::shared_ptr<SectPx_RegObj>
			RemoveFromMap
			(
				const Standard_Integer theIndex
			);

		TnbSectPx_EXPORT void Add
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<SectPx_RegObj>& theObj
		);

		TnbSectPx_EXPORT void Add
		(
			const Standard_Integer theIndex, 
			std::shared_ptr<SectPx_RegObj>&& theObj
		);

	protected:

		

	public:

		template<class... _Types>
		SectPx_Registry(_Types&&... _Args)
			: SectPx_Entity(_Args...)
		{}

		auto Size() const
		{
			return (Standard_Integer)theObjects_.size();
		}

		TnbSectPx_EXPORT Standard_Integer MaxIndex() const;

		inline Standard_Boolean
			IsContains
			(
				const std::shared_ptr<SectPx_RegObj>& theItem
			) const;

		TnbSectPx_EXPORT Standard_Integer
			Import
			(
				const std::shared_ptr<SectPx_RegObj>& theObj
			);

		TnbSectPx_EXPORT Standard_Integer
			Import
			(
				const word& theName,
				const std::shared_ptr<SectPx_RegObj>& theObj
			);

		TnbSectPx_EXPORT Standard_Integer
			Import
			(
				std::shared_ptr<SectPx_RegObj>&& theObj
			);

		TnbSectPx_EXPORT Standard_Integer
			Import
			(
				const word& theName,
				std::shared_ptr<SectPx_RegObj>&& theObj
			);

		TnbSectPx_EXPORT std::shared_ptr<SectPx_RegObj>
			Remove
			(
				const Standard_Integer theIndex
			);

		//- Throw an exception if not found the item
		TnbSectPx_EXPORT std::shared_ptr<SectPx_RegObj>
			SelectObj
			(
				const Standard_Integer theIndex
			) const;

		TnbSectPx_EXPORT std::shared_ptr<SectPx_RegObj>
			Find
			(
				const Standard_Integer theIndex
			) const;

		const auto& Objects() const
		{
			return theObjects_;
		}

		TnbSectPx_EXPORT void Remove
		(
			const std::shared_ptr<SectPx_RegObj>& theObj
		);

		TnbSectPx_EXPORT void Print(Ostream& out) const;

		inline Standard_Boolean
			Next
			(
				typename std::map<Standard_Integer, std::shared_ptr<SectPx_RegObj>>::iterator& it, 
				const sectPxLib::regObjType t
			) const;
	};

	namespace sectPxLib
	{
		TnbSectPx_EXPORT extern std::shared_ptr<SectPx_Registry> objRegistry;
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::SectPx_Registry);

#include <SectPx_RegistryI.hxx>
#include <SectPx_RegistryM.hxx>

#endif // !_SectPx_Registry_Header
