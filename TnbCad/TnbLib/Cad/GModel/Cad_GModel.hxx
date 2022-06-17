#pragma once
#ifndef _Cad_GModel_Header
#define _Cad_GModel_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Global_Serialization.hxx>
#include <Cad_Module.hxx>

#include <memory>
#include <vector>

class TopoDS_Shape;

namespace tnbLib
{

	// Forward Declarations
	class GModel_Surface;
	class Cad_Shape;

	class Cad_GModel
		: public Global_Indexed
		, public Global_Named
	{

		/*Private Data*/

		std::vector<std::shared_ptr<GModel_Surface>> theSurfaces_;
		std::shared_ptr<Cad_Shape> theShape_;

		//- private functions and operators

		TNB_SERIALIZATION(TnbCad_EXPORT);


		//- default constructor

		Cad_GModel()
		{}

	public:

		static TnbCad_EXPORT const std::string extension;

		//- constructors

		explicit Cad_GModel
		(
			const std::vector<std::shared_ptr<GModel_Surface>>& theSurfaces
		)
			: theSurfaces_(theSurfaces)
		{}

		Cad_GModel
		(
			const std::vector<std::shared_ptr<GModel_Surface>>& theSurfaces,
			const std::shared_ptr<Cad_Shape>& theShape
		)
			: theSurfaces_(theSurfaces)
			, theShape_(theShape)
		{}

		Cad_GModel
		(
			std::vector<std::shared_ptr<GModel_Surface>>&& theSurfaces,
			std::shared_ptr<Cad_Shape>&& theShape
		)
			: theSurfaces_(std::move(theSurfaces))
			, theShape_(std::move(theShape))
		{}

		Cad_GModel
		(
			const Standard_Integer theIndex, 
			const word& theName, 
			const std::vector<std::shared_ptr<GModel_Surface>>& theSurfaces
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
			, theSurfaces_(theSurfaces)
		{}

		Cad_GModel
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::vector<std::shared_ptr<GModel_Surface>>& theSurfaces,
			const std::shared_ptr<Cad_Shape>& theShape
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
			, theSurfaces_(theSurfaces)
			, theShape_(theShape)
		{}

		Cad_GModel
		(
			const Standard_Integer theIndex, 
			const word& theName, 
			std::vector<std::shared_ptr<GModel_Surface>>&& theSurfaces,
			std::shared_ptr<Cad_Shape>&& theShape
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
			, theSurfaces_(std::move(theSurfaces))
			, theShape_(std::move(theShape))
		{}


		//- public functions and operators

		auto NbSurfaces() const
		{
			return (Standard_Integer)theSurfaces_.size();
		}

		const auto& Surfaces() const
		{
			return theSurfaces_;
		}

		const auto& Shape() const
		{
			return theShape_;
		}

		void SetShape(const std::shared_ptr<Cad_Shape>& theShape)
		{
			theShape_ = theShape;
		}

		void SetShape(std::shared_ptr<Cad_Shape>&& theShape)
		{
			theShape_ = std::move(theShape);
		}

		TnbCad_EXPORT void SetFaces();

	};
}

#endif // !_Cad_GModel_Header
