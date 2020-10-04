#pragma once
#ifndef _SectPx_FieldFunMaker_Header
#define _SectPx_FieldFunMaker_Header

#include <SectPx_Maker.hxx>
#include <OSstream.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Par;
	class SectPx_FieldFun;
	class SectPx_Coord;

	namespace maker
	{

		class FieldFun
			: public SectPx_Maker
		{

			/*Private Data*/

		public:

			explicit FieldFun
			(
				const std::shared_ptr<SectPx_Registry>& theRegistry
			)
				: SectPx_Maker(theRegistry)
			{}

			std::shared_ptr<SectPx_FieldFun> 
				SelectFieldFun
				(
					const Standard_Integer theIndex
				) const;

			std::shared_ptr<SectPx_FieldFun> 
				RemoveFieldFun
				(
					const Standard_Integer theIndex
				) const;

			Standard_Integer 
				CreateUniform
				(
					const std::shared_ptr<SectPx_Par>& thePar
				) const;

			Standard_Integer 
				CreateInverse
				(
					const std::shared_ptr<SectPx_Par>& thePar
				) const;

			Standard_Integer 
				CreateUniform
				(
					const std::shared_ptr<SectPx_FieldFun>& theField
				) const;

			Standard_Integer 
				CreateInverse
				(
					const std::shared_ptr<SectPx_FieldFun>& theField
				) const;

			Standard_Integer 
				CreateReadingX
				(
					const std::shared_ptr<SectPx_Coord>& theCoord
				) const;

			Standard_Integer
				CreateReadingY
				(
					const std::shared_ptr<SectPx_Coord>& theCoord
				) const;

			Standard_Integer 
				CreateExpression
				(
					const word& expr
				) const;

			Standard_Integer 
				CreateLinearForm
				(
					const std::shared_ptr<SectPx_FieldFun>& theF0,
					const std::shared_ptr<SectPx_FieldFun>& theF1, 
					const std::shared_ptr<SectPx_Par>& thePar
				) const;

			std::vector<std::shared_ptr<SectPx_FieldFun>> RetrieveFieldFuns() const;
		};
	}
}

#endif // !_SectPx_FieldFunMaker_Header
