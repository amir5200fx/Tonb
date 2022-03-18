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

	class Cad_GModel
		: public Global_Indexed
		, public Global_Named
	{

		/*Private Data*/

		std::vector<std::shared_ptr<GModel_Surface>> theSurfaces_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbCad_EXPORT);


		//- default constructor

		Cad_GModel()
		{}

	public:

		static TnbCad_EXPORT const std::string extension;

		//- constructors

		Cad_GModel
		(
			const std::vector<std::shared_ptr<GModel_Surface>>& theSurfaces
		)
			: theSurfaces_(theSurfaces)
		{}

		Cad_GModel
		(
			std::vector<std::shared_ptr<GModel_Surface>>&& theSurfaces
		)
			: theSurfaces_(std::move(theSurfaces))
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
			std::vector<std::shared_ptr<GModel_Surface>>&& theSurfaces
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
			, theSurfaces_(std::move(theSurfaces))
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

	};
}

#endif // !_Cad_GModel_Header
