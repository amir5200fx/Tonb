#pragma once
#ifndef _Marine_ShapeIO_Header
#define _Marine_ShapeIO_Header

#include <Global_Serialization.hxx>
#include <Entity3d_BoxFwd.hxx>
#include <Marine_BodyModelType.hxx>
#include <Marine_Module.hxx>

#include <memory>

#include <gp_Ax2d.hxx>

namespace tnbLib
{

	// Forward Declarations 
	class Cad_Shape;

	namespace marineLib
	{

		namespace io
		{

			class Shape
			{

				/*Private Data*/

				std::shared_ptr<Cad_Shape> theShape_;

				Standard_Real theTol_;
				


				//- private functions and operators

				TNB_SERIALIZATION(TnbMarine_EXPORT);

			protected:


				//- default constructor

				Shape()
				{}

			public:

				static TnbMarine_EXPORT const std::string extention;

				//- public functions and operators

				const auto& GetShape() const
				{
					return theShape_;
				}		

				auto Tolerance() const
				{
					return theTol_;
				}	

				TnbMarine_EXPORT virtual std::shared_ptr<Entity3d_Box> BoundingBox() const;

				void LoadShape(const std::shared_ptr<Cad_Shape>& theShape)
				{
					theShape_ = theShape;
				}

				void SetTol(const Standard_Real tol)
				{
					theTol_ = tol;
				}		

			};
		}
	}
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::marineLib::io::Shape);

#endif // !_Marine_ShapeIO_Header
