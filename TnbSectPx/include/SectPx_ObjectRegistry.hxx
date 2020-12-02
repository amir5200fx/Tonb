#pragma once
#ifndef _SectPx_ObjectRegistry_Header
#define _SectPx_ObjectRegistry_Header

#include <SectPx_Entity.hxx>
#include <SectPx_Module.hxx>
#include <SectPx_RegistryM.hxx>

#include <map>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_RegObj;
	class SectPx_CountRegistry;
	class SectPx_ScatterRegistry;

	class SectPx_ObjectRegistry
		: public SectPx_Entity
	{

		/*Private Data*/

		std::map<Standard_Integer, std::shared_ptr<SectPx_RegObj>>
			theObjects_;

		std::shared_ptr<SectPx_CountRegistry> theCounter_;
		std::shared_ptr<SectPx_ScatterRegistry> theScatter_;


		//- private functions and operators


		TNB_SERIALIZATION(TnbSectPx_EXPORT);

		TnbSectPx_EXPORT Standard_Integer RetrieveIndex() const;

		TnbSectPx_EXPORT void ReturnToCounter(const Standard_Integer theIndex);

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

		virtual void CheckObjType
		(
			const std::shared_ptr<SectPx_RegObj>& theObj,
			const char* funcName
		) const = 0;


	protected:

		SectPx_ObjectRegistry()
		{}

		TnbSectPx_EXPORT SectPx_ObjectRegistry
		(
			const std::shared_ptr<SectPx_CountRegistry>& theCounter,
			const std::shared_ptr<SectPx_ScatterRegistry>& theScatter
		);

		TnbSectPx_EXPORT SectPx_ObjectRegistry
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<SectPx_CountRegistry>& theCounter,
			const std::shared_ptr<SectPx_ScatterRegistry>& theScatter
		);

	public:

		const auto& Scatter() const
		{
			return theScatter_;
		}

		const auto& Counter() const
		{
			return theCounter_;
		}

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
	};
}


BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_ObjectRegistry);

#include <SectPx_ObjectRegistryI.hxx>

#endif // !_SectPx_ObjectRegistry_Header
