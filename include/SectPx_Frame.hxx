#pragma once
#ifndef _SectPx_Frame_Header
#define _SectPx_Frame_Header

#include <SectPx_Entity.hxx>
#include <SectPx_ParsFwd.hxx>
#include <SectPx_PntsFwd.hxx>
#include <SectPx_MakersFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Registry;
	class SectPx_FieldFun;
	class SectPx_GeoMap;
	class SectPx_Coord;

	class SectPx_Frame
		: public SectPx_Entity
	{

	public:

		struct EntityMaker
		{

			EntityMaker(const std::shared_ptr<SectPx_Registry>&);

			std::shared_ptr<maker::Parameter> Par;
			std::shared_ptr<maker::Point> Pnt;
			std::shared_ptr<maker::GeometricMap> GeoMap;
			std::shared_ptr<maker::CmptProfile> CmptProfile;
			std::shared_ptr<maker::FieldFun> FieldFun;
		};

	private:

		/*Private Data*/

		std::shared_ptr<SectPx_Registry> theRegistry_;

		std::shared_ptr<EntityMaker> theMakers_;


		void AllocateMemory();

	public:

		template<class... _Types>
		SectPx_Frame(_Types&&... _Args)
			: SectPx_Entity(_Args...)
		{
			AllocateMemory();
		}

		const auto& Makers() const
		{
			return theMakers_;
		}

		const auto& ParameterMaker() const
		{
			return Makers()->Par;
		}

		const auto& PointMaker() const
		{
			return Makers()->Pnt;
		}

		const auto& GeometricMapMaker() const
		{
			return Makers()->GeoMap;
		}

		const auto& CmptProfileMaker() const
		{
			return Makers()->CmptProfile;
		}

		const auto& FieldFunMaker() const
		{
			return Makers()->FieldFun;
		}
	};
}

#endif // !_SectPx_Frame_Header
