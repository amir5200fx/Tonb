#pragma once
#ifndef _Cad2d_Modeler_Wire_Header
#define _Cad2d_Modeler_Wire_Header

#include <Cad2d_Module.hxx>
#include <Global_TypeDef.hxx>

#include <memory>
#include <map>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Wire;

	namespace cad2dLib
	{

		class Modeler_Wire
		{

			/*Private Data*/

			std::map<Standard_Integer, std::shared_ptr<Pln_Wire>>
				theWires_;

		protected:

			TnbCad2d_EXPORT Modeler_Wire();

			TnbCad2d_EXPORT void InsertToWires
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Pln_Wire>& theWire
			);

		public:

			TnbCad2d_EXPORT Standard_Boolean
				IsContainWire
				(
					const Standard_Integer theIndex
				) const;

			TnbCad2d_EXPORT Standard_Boolean
				IsContain
				(
					const std::shared_ptr<Pln_Wire>& theWire
				) const;

			auto NbWires() const
			{
				return (Standard_Integer)theWires_.size();
			}

			const auto& Wires() const
			{
				return theWires_;
			}

			TnbCad2d_EXPORT std::shared_ptr<Pln_Wire>
				RemoveFromWires
				(
					const Standard_Integer theIndex
				);

		};
	}
}

#endif // !_Cad2d_Modeler_Wire_Header
