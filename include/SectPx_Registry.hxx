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
	class SectPx_ParMaker;
	class SectPx_PntMaker;
	class SectPx_ProfileMaker;

	class SectPx_Registry
		: public SectPx_Entity
		, public SectPx_ScatterRegistry
	{

		friend class SectPx_ParMaker;
		friend class SectPx_PntMaker;
		friend class SectPx_ProfileMaker;

		/*Private Data*/

		std::map<Standard_Integer, std::shared_ptr<SectPx_RegObj>>
			theObjects_;

		mutable Geo_ItemCounter theCounter_;


		//- private functions and operators


		DECLARE_SAVE_LOAD_HEADER(TnbSectPx_EXPORT);

		auto& Counter() const
		{
			return theCounter_;
		}

		std::shared_ptr<SectPx_RegObj> 
			RemoveFromMap
			(
				const Standard_Integer theIndex
			);

		void Add
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<SectPx_RegObj>& theObj
		);

		void Add
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

		Standard_Boolean 
			IsContains
			(
				const std::shared_ptr<SectPx_RegObj>& theItem
			) const;

		Standard_Integer
			Import
			(
				const std::shared_ptr<SectPx_RegObj>& theObj
			);

		Standard_Integer
			Import
			(
				const word& theName,
				const std::shared_ptr<SectPx_RegObj>& theObj
			);

		Standard_Integer
			Import
			(
				std::shared_ptr<SectPx_RegObj>&& theObj
			);

		Standard_Integer
			Import
			(
				const word& theName,
				std::shared_ptr<SectPx_RegObj>&& theObj
			);

		std::shared_ptr<SectPx_RegObj>
			Remove
			(
				const Standard_Integer theIndex
			);

		//- Throw an exception if not found the item
		std::shared_ptr<SectPx_RegObj>
			SelectObj
			(
				const Standard_Integer theIndex
			) const;

		std::shared_ptr<SectPx_RegObj>
			Find
			(
				const Standard_Integer theIndex
			) const;

		const auto& Objects() const
		{
			return theObjects_;
		}

		void Remove
		(
			const std::shared_ptr<SectPx_RegObj>& theObj
		);

		void Print(Ostream& out) const;

		Standard_Boolean 
			Next
			(
				typename std::map<Standard_Integer, std::shared_ptr<SectPx_RegObj>>::iterator& it, 
				const sectPxLib::regObjType t
			) const;
	};

	namespace sectPxLib
	{
		extern std::shared_ptr<SectPx_Registry> objRegistry;
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::SectPx_Registry);

#include <SectPx_RegistryI.hxx>
#include <SectPx_RegistryM.hxx>

#endif // !_SectPx_Registry_Header
