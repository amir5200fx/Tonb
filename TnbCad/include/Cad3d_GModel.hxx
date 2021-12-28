#pragma once
#ifndef _Cad3d_GModel_Header
#define _Cad3d_GModel_Header

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

	class Cad3d_GModel
		: public Global_Indexed
		, public Global_Named
	{

		/*Private Data*/

		std::vector<std::shared_ptr<GModel_Surface>> theSurfaces_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbCad_EXPORT);


		//- default constructor

		Cad3d_GModel()
		{}

	public:

		static TnbCad_EXPORT const std::string extension;

		//- constructors

		Cad3d_GModel
		(
			const std::vector<std::shared_ptr<GModel_Surface>>& theSurfaces
		)
			: theSurfaces_(theSurfaces)
		{}

		Cad3d_GModel
		(
			std::vector<std::shared_ptr<GModel_Surface>>&& theSurfaces
		)
			: theSurfaces_(std::move(theSurfaces))
		{}

		Cad3d_GModel
		(
			const Standard_Integer theIndex, 
			const word& theName, 
			const std::vector<std::shared_ptr<GModel_Surface>>& theSurfaces
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
			, theSurfaces_(theSurfaces)
		{}

		Cad3d_GModel
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


	};
}

#endif // !_Cad3d_GModel_Header
