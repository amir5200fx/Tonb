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

				std::shared_ptr<Entity3d_Box> theBoundingBox_;

				Standard_Real theTol_;
				gp_Ax2d theAx_;
				Marine_BodyModelType theType_;


				//- private functions and operators

				TNB_SERIALIZATION(TnbMarine_EXPORT);

			public:


				//- default constructor

				Shape()
				{}


				//- public functions and operators

				const auto& GetShape() const
				{
					return theShape_;
				}

				const auto& PreciseBndBox() const
				{
					return theBoundingBox_;
				}

				const auto& Ax() const
				{
					return theAx_;
				}

				auto Tolerance() const
				{
					return theTol_;
				}

				auto ShapeType() const
				{
					return theType_;
				}

				void LoadShape(const std::shared_ptr<Cad_Shape>& theShape)
				{
					theShape_ = theShape;
				}

				void LoadPreciseBndBox(const std::shared_ptr<Entity3d_Box>& b)
				{
					theBoundingBox_ = b;
				}

				void SetTol(const Standard_Real tol)
				{
					theTol_ = tol;
				}

				void SetAx(const gp_Ax2d& ax)
				{
					theAx_ = ax;
				}

				void SetType(const Marine_BodyModelType t)
				{
					theType_ = t;
				}

			};
		}
	}
}

#endif // !_Marine_ShapeIO_Header
