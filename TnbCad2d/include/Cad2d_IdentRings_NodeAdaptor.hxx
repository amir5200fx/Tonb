#pragma once
#ifndef _Cad2d_IdentRings_NodeAdaptor_Header
#define _Cad2d_IdentRings_NodeAdaptor_Header

#include <Standard_TypeDef.hxx>
#include <Cad2d_Module.hxx>

#include <vector>
#include <memory>
#include <map>

namespace tnbLib
{

	namespace cad2dLib
	{

		// Forward Declarations [1/24/2022 Amir]
		class IdentRings_Link;

		class IdentRings_NodeAdaptor
		{

			/*Private Data*/

			std::map<Standard_Integer, std::weak_ptr<IdentRings_Link>> theLinks_;

		protected:

			// default constructor [1/24/2022 Amir]

			IdentRings_NodeAdaptor()
			{}

			// constructors [1/24/2022 Amir]

		public:

			// public functions and operators [1/24/2022 Amir]

			const auto& Links() const
			{
				return theLinks_;
			}

			Standard_Integer NbLinks() const
			{
				return (Standard_Integer)theLinks_.size();
			}

			TnbCad2d_EXPORT Standard_Boolean IsOrphan() const;
			TnbCad2d_EXPORT Standard_Boolean IsManifold() const;
			TnbCad2d_EXPORT Standard_Boolean IsDangle() const;

			//Standard_Boolean HasPetal() const;
			TnbCad2d_EXPORT Standard_Boolean 
				Contains(const Standard_Integer theIndex) const;

			TnbCad2d_EXPORT std::shared_ptr<IdentRings_Link> 
				Remove(const Standard_Integer theIndex);

			TnbCad2d_EXPORT std::vector<std::shared_ptr<IdentRings_Link>> 
				RetrieveLinks() const;

			TnbCad2d_EXPORT void Insert
			(
				const Standard_Integer theIndex,
				const std::weak_ptr<IdentRings_Link>& theLink
			);

		};
	}
}

#endif // !_Cad2d_IdentRings_NodeAdaptor_Header
