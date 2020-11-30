#pragma once
#ifndef _SectPx_Frame_Header
#define _SectPx_Frame_Header

#include <SectPx_Entity.hxx>
#include <SectPx_ParsFwd.hxx>
#include <SectPx_PntsFwd.hxx>
#include <SectPx_MakersFwd.hxx>
#include <Pnt2d.hxx>
#include <Dir2d.hxx>
#include <SectPx_FieldCloud_Naca4DigitFwd.hxx>
#include <Ostream.hxx>

#include <vector>
#include <map>

#include <string>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_FrameRegistry;
	class SectPx_ParRegistry;
	class SectPx_FieldFun;
	class SectPx_GeoMap;
	class SectPx_Coord;
	class SectPx_ProfileQ;

	class SectPx_Frame
		: public SectPx_Entity
	{

	public:

		struct EntityMaker
		{
			EntityMaker()
			{}

			EntityMaker
			(
				const std::shared_ptr<SectPx_ParRegistry>&, 
				const std::shared_ptr<SectPx_FrameRegistry>&
			);

			std::shared_ptr<maker::Parameter> Par;
			std::shared_ptr<maker::Point> Pnt;
			std::shared_ptr<maker::GeometricMap> GeoMap;
			std::shared_ptr<maker::CmptProfile> CmptProfile;
			std::shared_ptr<maker::FieldFun> FieldFun;

			TNB_SERIALIZATION(TnbSectPx_EXPORT);
		};

	private:

		/*Private Data*/

		std::shared_ptr<SectPx_ParRegistry> theParRegistry_;

		std::shared_ptr<SectPx_FrameRegistry> theFrameRegistry_;

		std::shared_ptr<EntityMaker> theMakers_;


		TNB_SERIALIZATION(TnbSectPx_EXPORT);

		TnbSectPx_EXPORT void AllocateMemory();


	protected:

		SectPx_Frame()
		{}

	public:

		SectPx_Frame
		(
			const std::shared_ptr<SectPx_ParRegistry>& theParReg
		);

		SectPx_Frame
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<SectPx_ParRegistry>& theParReg
		);

		SectPx_Frame
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const std::shared_ptr<SectPx_ParRegistry>& theParReg
		);

		const auto& ParRegistry() const
		{
			return theParRegistry_;
		}

		const auto& FrameRegistry() const
		{
			return theFrameRegistry_;
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

		TnbSectPx_EXPORT Standard_Integer NbProfiles() const;

		TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_ProfileQ>>
			RetrieveProfilesQ() const;

		TnbSectPx_EXPORT std::map<std::string, std::shared_ptr<SectPx_FixedPar>>
			RetrieveFixedParameters() const;

		TnbSectPx_EXPORT void MakeLineSegment();

		TnbSectPx_EXPORT Standard_Integer MakeLineSegment
		(
			const Pnt2d& theP0,
			const Pnt2d& theP1
		);

		TnbSectPx_EXPORT void MakeCorner();

		TnbSectPx_EXPORT void MakeCorner
		(
			const Pnt2d& theP0, 
			const Pnt2d& theP1
		);

		TnbSectPx_EXPORT void MakeCorner
		(
			const Pnt2d& theP0,
			const Dir2d& theDir0, 
			const Standard_Real theAngl0,
			const Pnt2d& theP1, 
			const Dir2d& theDir1,
			const Standard_Real theAngl1
		);

		TnbSectPx_EXPORT void MakeUShape();

		TnbSectPx_EXPORT void MakeUShape
		(
			const Pnt2d& theP0,
			const Pnt2d& theP1, 
			const Standard_Real w
		);

		TnbSectPx_EXPORT void PrintRegistry() const;
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::SectPx_Frame);

#endif // !_SectPx_Frame_Header
