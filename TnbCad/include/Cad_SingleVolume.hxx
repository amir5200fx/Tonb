#pragma once
#ifndef _Cad_SingleVolume_Header
#define _Cad_SingleVolume_Header

#include <Cad_Volume.hxx>

namespace tnbLib
{

	class Cad_SingleVolume
		: public Cad_Volume
	{

		/*Private Data*/

		std::shared_ptr<Cad_Solid> theSolid_;


		// Private functions and operators [6/13/2023 Payvand]

		TnbCad_EXPORT void Check();

		TNB_SERIALIZATION(TnbCad_EXPORT);


		// default constructor [6/13/2023 Payvand]

		Cad_SingleVolume()
		{}

	public:

		// default constructor [6/13/2023 Payvand]

		// constructors [6/13/2023 Payvand]

		TnbCad_EXPORT Cad_SingleVolume(const std::shared_ptr<Cad_Solid>& theSolid);

		TnbCad_EXPORT Cad_SingleVolume(std::shared_ptr<Cad_Solid>&& theSolid);

		TnbCad_EXPORT Cad_SingleVolume
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<Cad_Solid>& theSolid
		);

		TnbCad_EXPORT Cad_SingleVolume
		(
			const Standard_Integer theIndex,
			const word& theName,
			std::shared_ptr<Cad_Solid>&& theSolid
		);

		// Public functions and operators [6/13/2023 Payvand]

		const auto& Solid() const { return theSolid_; }

		TnbCad_EXPORT Standard_Integer 
			NbVolumes() const override;
		TnbCad_EXPORT std::shared_ptr<Cad_Solid> 
			Volume(const Standard_Integer theIndex) const override;

		TnbCad_EXPORT std::vector<std::shared_ptr<Cad_Solid>>
			Volumes() const override;

	};

}

BOOST_CLASS_EXPORT_KEY(tnbLib::Cad_SingleVolume);

#endif // !_Cad_SingleVolume_Header
