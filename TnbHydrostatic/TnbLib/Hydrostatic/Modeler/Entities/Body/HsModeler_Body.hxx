#pragma once
#ifndef _HsModeler_Body_Header
#define _HsModeler_Body_Header

#include <HsModeler_Entity.hxx>

#include <TopoDS_Shape.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Geo_xDistb;

	class HsModeler_Body
		: public HsModeler_Entity
	{

		/*Private Data*/

		TopoDS_Shape theShape_;

		std::shared_ptr<Geo_xDistb> theSections_;

	protected:

		HsModeler_Body();

		HsModeler_Body(const Standard_Integer theIndex);

		HsModeler_Body(const Standard_Integer theIndex, const word& theName);


	public:

		const auto& Shape() const
		{
			return theShape_;
		}

		void SetShape(const TopoDS_Shape& theShape)
		{
			theShape_ = theShape;
		}
	};
}

#endif // !_HsModeler_Body_Header
